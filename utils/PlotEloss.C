void PlotEloss() {
    SetAtlasStyle();

    // TFile *fin = TFile::Open("OutputROOT.20180806.BLE30.root", "READ");
    TFile *fin[3];
    // fin[0] = new TFile("backup-201911-4/OutputROOT.20181229.BLE.root","READ");
    // fin[1] = new TFile("backup-201911-4/OutputROOT.20181229.BLE30.root","READ");
    // fin[2] = new TFile("backup-201911-4/OutputROOT.20181229.BLE40.root","READ");
    fin[0] = new TFile("OutputROOT.20200218.BLE.root","READ");
    fin[1] = new TFile("OutputROOT.20200221.BLE30.root","READ");
    fin[2] = new TFile("OutputROOT.20200221.BLE30.root","READ");

    TGraphErrors *tg[3];
    tg[0] = (TGraphErrors*) fin[0]->Get("tg_dz");
    tg[1] = (TGraphErrors*) fin[1]->Get("tg_dz");
    tg[2] = (TGraphErrors*) fin[2]->Get("tg_dz");

    tg[0]->SetMarkerStyle(23);
    tg[1]->SetMarkerStyle(22);
    tg[2]->SetMarkerStyle(21);

    /** Convert to Energy Loss **/
    double NU[4] = {14.50,13.10,12.40,10.80};
    for (int i=0; i<4; ++i) {
        for (int j=0; j<3; ++j) {
            tg[j]->GetY()[i] *= NU[i];
            tg[j]->GetEY()[i] *= NU[i];
        }
    }

    auto model = tg[1]; // Choose BLE30 as nominal;
    model->SetMarkerSize(1.5);
    model->SetMarkerStyle(20);
    model->GetXaxis()->SetLimits(0.0,1.0);
    model->GetXaxis()->SetNdivisions(505);
    model->GetYaxis()->SetRangeUser(-2.4,1.49);
    model->SetTitle(";#it{z}_{h};#it{E}_{Loss} (GeV)");
    model->GetXaxis()->CenterTitle();
    model->GetYaxis()->CenterTitle();

    /** Compute variants bar **/
    TGraphErrors *variants = new TGraphErrors(4);
    variants->SetMarkerStyle(kStar);
    for (int i=0; i<4; ++i) {
        variants->GetX()[i] = model->GetX()[i];
        variants->GetY()[i] = 0;

        double rms = 0;
        for (int j=0; j<3; ++j) {
            variants->GetY()[i] += tg[j]->GetY()[i];
            rms += TMath::Power(tg[j]->GetEY()[i], 2);
        }
        variants->GetY()[i] /= 3;
        rms /= 3;
        rms = TMath::Sqrt(rms);
        variants->GetEY()[i] = rms;
        variants->GetEX()[i] = 0.015;
    }
    variants->SetFillColorAlpha(kYellow,0.5);

    /** Get average energy loss **/
    double Eloss = 0;
    double ElossErr = 0;
    double Sum = 0;
    for (int i=0; i<4; ++i) {
        Eloss += model->GetY()[i]/model->GetEY()[i];
        Sum += 1/model->GetEY()[i];
        ElossErr += TMath::Power(model->GetEY()[i],2);
    }
    Eloss /= Sum;
    ElossErr = TMath::Sqrt(ElossErr);
    cout << "Average energy loss = " << Eloss << "+/-" << ElossErr << " GeV" << endl;

    TLine *line = new TLine(0.5, Eloss, 0.98, Eloss);
    line->SetLineWidth(4);

    TBox *box = new TBox(0.5,Eloss-ElossErr,0.98,Eloss+ElossErr);
    box->SetLineStyle(2);
    box->SetLineWidth(2);
    box->SetFillColorAlpha(13,0.5);

    TCanvas *c1 = new TCanvas("c1","title",800,600);
    model->Draw("APE");
    // tg[0]->Draw("PSAME");
    // tg[1]->Draw("PSAME");
    // tg[2]->Draw("PSAME");
    variants->Draw("SAME5");
    model->Draw("PSAME");
    // model_corrected->Draw("PSAME");
    line->Draw("SAME");
    // box->Draw("SAME");

    TLegend* leg = new TLegend(0.2,0.2,0.35,0.2+0.113);
    // leg->SetNColumns(2);
    leg->SetTextFont(42);
    leg->SetTextSize(0.04);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->AddEntry(model,"BLE30","pe");
    leg->AddEntry(line,Form("#bar{#it{E}_{Loss}}(#it{z}_{h} > 0.5) = %.0f MeV ", Eloss*1000), "l");
    leg->Draw();

    c1->Print("figure_models_eloss.pdf");

}
