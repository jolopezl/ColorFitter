void PlotQhat()
{
  SetAtlasStyle();

  // TFile *fin = TFile::Open("OutputROOT.20180806.BLE30.root", "READ");
  TFile* fin[4];
  fin[0] = new TFile("OutputROOT.20181229.BL.root", "READ");
  fin[1] = new TFile("OutputROOT.20181229.BL30.root", "READ");
  fin[2] = new TFile("OutputROOT.20181229.BLE.root", "READ");
  fin[3] = new TFile("OutputROOT.20181229.BLE30.root", "READ");

  TGraphErrors* tg_lp[4];
  TGraphErrors* tg_q0[4];
  TGraphErrors* tg_pt[4][4];
  TGraphErrors* tg_qhat[3][4]; // A13, models

  for (int i = 0; i < 4; ++i) { // loop over models
    tg_lp[i] = new TGraphErrors(4);
    tg_q0[i] = new TGraphErrors(4);
    tg_pt[0][i] = new TGraphErrors(3);
    tg_pt[1][i] = new TGraphErrors(3);
    tg_pt[2][i] = new TGraphErrors(3);
    tg_pt[3][i] = new TGraphErrors(3);
    tg_qhat[0][i] = new TGraphErrors(4);
    tg_qhat[1][i] = new TGraphErrors(4);
    tg_qhat[2][i] = new TGraphErrors(4);
  }

  tg_lp[0] = (TGraphErrors*)fin[0]->Get("tg_lp");
  tg_lp[1] = (TGraphErrors*)fin[1]->Get("tg_lp");
  tg_lp[2] = (TGraphErrors*)fin[2]->Get("tg_lp");
  tg_lp[3] = (TGraphErrors*)fin[3]->Get("tg_lp");

  tg_q0[0] = (TGraphErrors*)fin[0]->Get("tg_q0");
  tg_q0[1] = (TGraphErrors*)fin[1]->Get("tg_q0");
  tg_q0[2] = (TGraphErrors*)fin[2]->Get("tg_q0");
  tg_q0[3] = (TGraphErrors*)fin[3]->Get("tg_q0");

  for (int i = 0; i < 4; ++i) {      // loop over models
    for (int iz = 0; iz < 4; ++iz) { // loop over z-bin points
      tg_pt[iz][i] = (TGraphErrors*)fin[i]->Get(Form("tg_model_pT_%d", iz));
    }
  }

  const double factor = 0.1 * 3. / (4. * 3.141592); // to be removed!!

  const double correlation[4] = { 0.55, 0.55, 0.55, 0.55 };

  for (int i = 0; i < 4; ++i) {      // loop over models
    for (int iz = 0; iz < 4; ++iz) { // loop over z-bin points
      for (int nucl = 0; nucl < 3; ++nucl) {
        // double zz = tg_lp[i]->GetX()[iz];
        tg_qhat[nucl][i]->GetX()[iz] = tg_lp[i]->GetX()[iz];
        double pt = tg_pt[iz][i]->GetY()[nucl];
        double lp = tg_lp[i]->GetY()[iz];
        double lperr = tg_lp[i]->GetEY()[iz];
        double q0 = tg_q0[i]->GetY()[iz];
        double q0err = tg_q0[i]->GetEY()[iz];
        double pterr = TMath::Sqrt(TMath::Power(pt / q0, 2) * TMath::Power(q0err, 2));

        tg_qhat[nucl][i]->GetY()[iz] = pt / lp;
        double qhaterrsq = TMath::Power(pt / lp, 2) * (TMath::Power(pterr / pt, 2) + TMath::Power(lperr / lp, 2) - 2 * correlation[iz] * lperr * pterr / (lp * pt)); // Missing correlation!!??
        tg_qhat[nucl][i]->GetEY()[iz] = TMath::Sqrt(qhaterrsq);

        tg_qhat[nucl][i]->GetY()[iz] /= factor;
        tg_qhat[nucl][i]->GetEY()[iz] /= factor;
      }
    }
    // All done
  }

  double offset = 0.06;
  offset = offset / 2;
  for (int i = 0; i < 4; ++i) {
    for (int iz = 0; iz < 4; ++iz) {
      tg_qhat[0][i]->GetX()[iz] -= offset;
      tg_qhat[1][i]->GetX()[iz] -= 0;
      tg_qhat[2][i]->GetX()[iz] += offset;
    }
  }

  const int kModel = 3;
  TGraphErrors* model[3];
  model[0] = tg_qhat[0][kModel]; // selects BLE30
  model[1] = tg_qhat[1][kModel]; // selects BLE30
  model[2] = tg_qhat[2][kModel]; // selects BLE30

  cout << model[0]->GetMean(2) << endl;
  cout << model[1]->GetMean(2) << endl;
  cout << model[2]->GetMean(2) << endl;

  // Get full average:
  double average = 0;
  double average_err = 0;
  double sumw = 0;
  for (int i = 0; i < 4; ++i) {
    average += model[0]->GetY()[i] / model[0]->GetEY()[i];
    average += model[1]->GetY()[i] / model[1]->GetEY()[i];
    average += model[2]->GetY()[i] / model[2]->GetEY()[i];
    sumw += 1 / model[0]->GetEY()[i];
    sumw += 1 / model[1]->GetEY()[i];
    sumw += 1 / model[2]->GetEY()[i];
    average_err += TMath::Power(model[0]->GetEY()[i], 2);
    average_err += TMath::Power(model[1]->GetEY()[i], 2);
    average_err += TMath::Power(model[2]->GetEY()[i], 2);
  }
  average /= sumw;
  average_err = TMath::Sqrt(average_err);
  cout << average << " +/- " << average_err << endl;

  /** Compute variants bar **/
  TGraphErrors* variants[3];
  for (int i = 0; i < 3; ++i) {
    variants[i] = new TGraphErrors(4);
    variants[i]->SetMarkerStyle(kStar);
    for (int iz = 0; iz < 4; ++iz) {
      variants[i]->GetX()[iz] = model[i]->GetX()[iz];
      variants[i]->GetY()[iz] = 0;
      double rms = 0;
      for (int j = 0; j < 4; ++j) {
        variants[i]->GetY()[iz] += tg_qhat[i][j]->GetY()[iz];
        rms += TMath::Power(tg_qhat[i][j]->GetEY()[iz], 2);
      }
      variants[i]->GetY()[iz] /= 4;
      rms /= 4;
      rms = TMath::Sqrt(rms);
      variants[i]->GetEY()[iz] = rms;
      variants[i]->GetEX()[iz] = 0.015; // 0.015;
    }
    variants[i]->SetFillColorAlpha(kYellow, 1);
  }

  // Set drawing attributes
  model[0]->SetTitle(";#it{z};#it{#hat{q}} (GeV^{2}/fm)");
  model[0]->GetXaxis()->CenterTitle();
  model[0]->GetYaxis()->CenterTitle();
  model[0]->GetXaxis()->SetLimits(0, 1);
  model[0]->GetXaxis()->SetNdivisions(505);
  // model[0]->GetYaxis()->SetRangeUser(-0.3,1);
  model[0]->GetYaxis()->SetRangeUser(-0.15, 0.55);
  model[0]->GetYaxis()->SetNdivisions(505);

  model[0]->SetMarkerStyle(22);
  model[1]->SetMarkerStyle(29);
  model[2]->SetMarkerStyle(23);

  TCanvas* c1 = new TCanvas("c1", "title", 800, 600);
  model[0]->Draw("APE");
  model[1]->Draw("PSAME");
  model[2]->Draw("PSAME");

  double theoretical_qhat = 0.075;
  double lxmin = 0.85;
  double lxmax = 0.99;
  TLine* line = new TLine(lxmin, theoretical_qhat, lxmax, theoretical_qhat);
  line->SetLineStyle(2);
  line->Draw("SAME");

  TBox* box = new TBox(lxmin, theoretical_qhat - 0.005, lxmax, theoretical_qhat + 0.015);
  box->SetLineStyle(2);
  box->SetFillColorAlpha(13, 1);
  box->Draw("SAME");

  variants[0]->Draw("SAME5");
  variants[1]->Draw("SAME5");
  variants[2]->Draw("SAME5");
  // model->Draw("PSAME");
  // model_corrected->Draw("PSAME");

  box->Draw("SAME");
  line->Draw("SAME");

  model[0]->Draw("PSAME");
  model[1]->Draw("PSAME");
  model[2]->Draw("PSAME");

  // box->Draw("SAME");
  // line->Draw("SAME");

  // TLine *line_average = new TLine(lxmin, average, lxmax, average);
  // line_average->SetLineWidth(4);
  // line_average->Draw("SAME");

  TLegend* leg = new TLegend(0.2, 0.7, 0.35, 0.7 + 0.2266666667);
  // leg->SetNColumns(2);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->AddEntry(model[0], "Neon", "ep");
  leg->AddEntry(model[1], "Krypton", "ep");
  leg->AddEntry(model[2], "Xenon", "ep");
  leg->AddEntry(box, "p+Pb, JHEP03(2013)122", "fl");
  leg->Draw();

  // myText(0.25, 0.6, kBlack, "#hat{q} = #frac{#Deltap_{T}^{2}}{L_{p}}",0.045); // z-bin #3
  myText(0.8, 0.9, kBlack, "BLE30", 0.045); // z-bin #3
  // AddLabel(0.2, 0.81, "Fixed cross section #sigma_{ph} = 30 [mb]")

  c1->Print("figure_qhat.pdf");

  /* Compute strong coupling constant from energy loss, qhat and production length */
  /* 
        - Delta E_loss = alpha_S/4 * qhat * L^2
    */
  double qhat = 0; // q-hat computed from BLE30
  double qhat_err = 0;

  qhat += model[0]->GetY()[4] / model[0]->GetEY()[4];
  cout << qhat << endl;
  qhat += model[1]->GetY()[4] / model[1]->GetEY()[4];
  qhat += model[2]->GetY()[4] / model[2]->GetEY()[4];

  sumw = 0;
  sumw += 1 / model[0]->GetEY()[4];
  sumw += 1 / model[1]->GetEY()[4];
  sumw += 1 / model[2]->GetEY()[4];

  qhat /= sumw;

  qhat_err += TMath::Power(model[0]->GetEY()[4], 2);
  qhat_err += TMath::Power(model[1]->GetEY()[4], 2);
  qhat_err += TMath::Power(model[2]->GetEY()[4], 2); // q-hat computed from BLE30
  qhat_err = TMath::Sqrt(qhat_err);

  double lp = tg_lp[3]->GetY()[4];      // Choosing BLE30
  double lp_err = tg_lp[3]->GetEY()[4]; // Choosing BLE30

  cout << "q-hat = " << qhat << " +/- " << qhat_err << " (GeV^2/fm)" << endl;
  cout << "lp = " << lp << " +/- " << lp_err << " (fm)" << endl;

  double alpha_S = 0;
  alpha_S = 0.25 * 0.03 / (qhat * lp * lp);

  cout << "Alpha_S = " << alpha_S << endl;
}
