void PlotQhatPerA()
{
    SetAtlasStyle();

    // TFile *fin = TFile::Open("OutputROOT.20180806.BLE30.root", "READ");
    TFile *fin[4];
    fin[0] = new TFile("OutputROOT.20191105.BL.root", "READ");
    fin[1] = new TFile("OutputROOT.20191105.BL30.root", "READ");
    fin[2] = new TFile("OutputROOT.20191105.BLE.root", "READ");
    fin[3] = new TFile("OutputROOT.20191105.BLE30.root", "READ");

    TGraphErrors *tg_lp[4][4];
    TGraphErrors *tg_q0[4];
    TGraphErrors *tg_qhat[4];

    for (int i = 0; i < 4; ++i)
    { // loop over models
        for (int j = 0; j < 4; ++j)
        {
            tg_lp[i][j] = new TGraphErrors(4);
        }
        tg_q0[i] = new TGraphErrors(4);
        tg_qhat[i] = new TGraphErrors(4);
    }

    for (int i = 0; i < 4; ++i)
    {
        tg_lp[i][0] = (TGraphErrors *)fin[i]->Get("tg_average_density_0");
        tg_lp[i][1] = (TGraphErrors *)fin[i]->Get("tg_average_density_1");
        tg_lp[i][2] = (TGraphErrors *)fin[i]->Get("tg_average_density_2");
        tg_lp[i][3] = (TGraphErrors *)fin[i]->Get("tg_average_density_3");
    }

    tg_q0[0] = (TGraphErrors *)fin[0]->Get("tg_q0");
    tg_q0[1] = (TGraphErrors *)fin[1]->Get("tg_q0");
    tg_q0[2] = (TGraphErrors *)fin[2]->Get("tg_q0");
    tg_q0[3] = (TGraphErrors *)fin[3]->Get("tg_q0");

    const double factor = 0.1 * 3. / (4. * 3.141592); // to be removed!!

    for (int i = 0; i < 4; ++i)
    { // loop over models
        for (int iz = 0; iz < 4; ++iz)
        { // loop over z-bin points
            tg_qhat[i]->GetX()[iz] = tg_q0[i]->GetX()[iz];
            // 20.1797, 83.7980, 131.293
            tg_qhat[i]->GetY()[iz] = tg_q0[i]->GetY()[iz] * tg_lp[i][iz]->Eval(pow(83.7980,1/3.));
            tg_qhat[i]->GetEY()[iz] = tg_q0[i]->GetEY()[iz] * tg_lp[i][iz]->Eval(pow(83.7980,1/3.));
            // tg_qhat[i]->GetY()[iz] /= factor;
            // tg_qhat[i]->GetEY()[iz] /= factor;
        }
        // All done
    }

    const int kModel = 1;
    TGraphErrors *model;
    model = tg_qhat[kModel]; // selects BLE30

    /** Compute variants bar **/
    TGraphErrors *variants = new TGraphErrors(4);
    variants->SetMarkerStyle(kStar);
    for (int i = 0; i < 4; ++i)
    {
        variants->GetX()[i] = model->GetX()[i];
        variants->GetY()[i] = 0;

        double rms = 0;
        for (int j = 0; j < 4; ++j)
        {
            variants->GetY()[i] += tg_qhat[j]->GetY()[i];
            rms += TMath::Power(tg_qhat[j]->GetEY()[i], 2);
        }
        variants->GetY()[i] /= 3;
        rms /= 3;
        rms = TMath::Sqrt(rms);
        variants->GetEY()[i] = rms;
        variants->GetEX()[i] = 0.015;
    }
    variants->SetFillColorAlpha(kYellow, 0.3);

    // Set drawing attributes
    model->SetTitle(";#it{z};#it{#hat{q}} (GeV^{2}/fm)");
    model->GetXaxis()->CenterTitle();
    model->GetYaxis()->CenterTitle();
    model->GetXaxis()->SetLimits(0, 1);
    model->GetXaxis()->SetNdivisions(505);
    // model->GetYaxis()->SetRangeUser(-0.3,1);
    model->GetYaxis()->SetRangeUser(-0.015, 0.11);
    model->GetYaxis()->SetNdivisions(505);

    // model->SetMarkerStyle(22);

    TCanvas *c1 = new TCanvas("c1", "title", 800, 600);
    model->Draw("APE");

    double theoretical_qhat = 0.075;
    double lxmin = 0.85;
    double lxmax = 0.99;
    TLine *line = new TLine(lxmin, theoretical_qhat, lxmax, theoretical_qhat);
    line->SetLineStyle(2);
    line->Draw("SAME");

    double average_qhat = 0;
    double average_qhat_err = 0;
    double weight = 0;
    for (int i = 0; i < 4; ++i)
    {
        average_qhat += model->GetY()[i] / model->GetEY()[i];
        weight += 1 / model->GetEY()[i];
        average_qhat_err += TMath::Power(model->GetEY()[i], 2);
    }
    average_qhat /= weight;
    average_qhat_err = TMath::Sqrt(average_qhat_err) / 4;

    TLine *lineAve = new TLine(0.2, average_qhat, 0.99, average_qhat);
    lineAve->SetLineStyle(1);
    lineAve->Draw("SAME");

    TBox *boxAve = new TBox(0.2, average_qhat - average_qhat_err, 0.99, average_qhat + average_qhat_err);
    boxAve->SetLineStyle(2);
    boxAve->SetFillColorAlpha(kAzure, 0.3);
    boxAve->Draw("SAME");

    TLine *line2 = new TLine(0.2, 0.015, 0.99, 0.015);
    line2->SetLineStyle(3);
    line2->Draw("SAME");

    TBox *box = new TBox(lxmin, theoretical_qhat - 0.005, lxmax, theoretical_qhat + 0.015);
    box->SetLineStyle(2);
    box->SetFillColorAlpha(13, 1);
    box->Draw("SAME");

    // variants->Draw("SAME5");
    // model->Draw("PSAME");

    box->Draw("SAME");
    line->Draw("SAME");

    model->Draw("PSAME");

    // box->Draw("SAME");
    // line->Draw("SAME");

    // TLine *line_average = new TLine(lxmin, average, lxmax, average);
    // line_average->SetLineWidth(4);
    // line_average->Draw("SAME");

    TLegend *leg = new TLegend(0.2, 0.7, 0.35, 0.7 + 0.2266666667);
    // leg->SetNColumns(2);
    leg->SetTextFont(42);
    leg->SetTextSize(0.04);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->AddEntry(model, "Data", "ep");
    leg->AddEntry(lineAve, Form("Average #it{#hat{q}} = %.3f +/- %.3f GeV^{2}/fm", average_qhat, average_qhat_err), "fl");
    leg->AddEntry(line2, "arXiv:1907.11808", "fl");
    leg->AddEntry(box, "p+Pb, JHEP03(2013)122", "fl");
    leg->Draw();

    // myText(0.25, 0.6, kBlack, "#hat{q} = #frac{#Deltap_{T}^{2}}{L_{p}}",0.045); // z-bin #3
    // myText(0.8, 0.9, kBlack, "BL30",0.045); // z-bin #3
    // AddLabel(0.2, 0.81, "Fixed cross section #sigma_{ph} = 30 [mb]")

    c1->Print("figure_qhat.pdf");

    /* Compute strong coupling constant from energy loss, qhat and production length */
    /* 
        - Delta E_loss = alpha_S/4 * qhat * L^2

    double qhat = 0; // q-hat computed from BLE30
    double qhat_err = 0;

    qhat += model->GetY()[4]/model->GetEY()[4];
    cout << qhat << endl;
    qhat += model[1]->GetY()[4]/model[1]->GetEY()[4];
    qhat += model[2]->GetY()[4]/model[2]->GetEY()[4];

    sumw = 0;
    sumw += 1/model->GetEY()[4];
    sumw += 1/model[1]->GetEY()[4];
    sumw += 1/model[2]->GetEY()[4];

    qhat /= sumw;

    qhat_err += TMath::Power(model->GetEY()[4],2);
    qhat_err += TMath::Power(model[1]->GetEY()[4],2);
    qhat_err += TMath::Power(model[2]->GetEY()[4],2); // q-hat computed from BLE30
    qhat_err = TMath::Sqrt(qhat_err);

    double lp = tg_lp[3]->GetY()[4]; // Choosing BLE30
    double lp_err = tg_lp[3]->GetEY()[4]; // Choosing BLE30

    cout << "q-hat = " << qhat << " +/- " << qhat_err << " (GeV^2/fm)" << endl;
    cout << "lp = " << lp << " +/- " << lp_err << " (fm)" << endl;

    double alpha_S = 0;
    alpha_S = 0.25 * 0.03 / (qhat * lp*lp);

    cout << "Alpha_S = " << alpha_S << endl;     */
}
