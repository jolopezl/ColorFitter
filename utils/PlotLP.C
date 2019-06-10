void PlotLP()
{
  SetAtlasStyle();

  // TFile *fin = TFile::Open("OutputROOT.20180806.BLE30.root", "READ");
  TFile* fin[4];
  fin[0] = new TFile("OutputROOT.20181229.BL.root", "READ");
  fin[1] = new TFile("OutputROOT.20181229.BL30.root", "READ");
  fin[2] = new TFile("OutputROOT.20181229.BLE.root", "READ");
  fin[3] = new TFile("OutputROOT.20181229.BLE30.root", "READ");

  TGraphErrors* tg[4];
  tg[0] = (TGraphErrors*)fin[0]->Get("tg_lp");
  tg[1] = (TGraphErrors*)fin[1]->Get("tg_lp");
  tg[2] = (TGraphErrors*)fin[2]->Get("tg_lp");
  tg[3] = (TGraphErrors*)fin[3]->Get("tg_lp");

  tg[0]->SetMarkerStyle(23);
  tg[1]->SetMarkerStyle(22);
  tg[2]->SetMarkerStyle(21);
  tg[3]->SetMarkerStyle(20);

  const int kModel = 1; // define nominal model
  TGraphAsymmErrors* model = new TGraphAsymmErrors(4);
  for (int i = 0; i < 4; ++i) {
    double x(-99), y(-99);
    tg[kModel]->GetPoint(i, x, y);
    model->SetPoint(i, x, y);
    model->GetEYhigh()[i] = tg[kModel]->GetEY()[i];
    model->GetEYlow()[i] = tg[kModel]->GetEY()[i];
  }

  model->SetMarkerSize(1.5);
  model->SetMarkerStyle(20);
  // model->SetLineWidth(2);
  model->GetXaxis()->SetLimits(0.0, 1.0);
  model->GetXaxis()->SetNdivisions(505);
  // model->GetYaxis()->SetRangeUser(0.0001,16);
  model->GetYaxis()->SetRangeUser(0.1, 70);
  model->SetTitle(";#it{z};#it{L}_{p} (fm)");
  model->GetXaxis()->CenterTitle();
  model->GetYaxis()->CenterTitle();

  /** Compute variants bar **/
  TGraphErrors* variants = new TGraphErrors(4);
  variants->SetMarkerStyle(kStar);
  for (int i = 0; i < 4; ++i) {
    variants->GetX()[i] = model->GetX()[i];
    variants->GetY()[i] = 0;

    double rms = 0;
    for (int j = 0; j < 4; ++j) {
      variants->GetY()[i] += tg[j]->GetY()[i];
      rms += TMath::Power(tg[j]->GetEY()[i], 2);
    }
    variants->GetY()[i] /= 4;
    rms /= 4;
    rms = TMath::Sqrt(rms);
    variants->GetEY()[i] = rms;
    variants->GetEX()[i] = 0.015;
  }
  variants->SetFillColorAlpha(kYellow, 1);

  const bool APPLY_KINEMATIC_CORRECTION = true;
  if (APPLY_KINEMATIC_CORRECTION) {
    // Remember to apply scale factors
    double SF[4] = { 9.31, 8.40, 7.94, 7.05 };
    double SFref = 7.94;
    // double SF[4] = {8.40,8.40,8.40,8.40};
    for (int i = 0; i < 4; ++i) {
      // model_uncorrected->GetY()[i] *= SF[i]/SFref;
      // model_uncorrected->GetEY()[i] = 0; // *= SF[i]/SFref;
      model->GetY()[i] *= SF[i] / SFref;
      // model->GetEY()[i] *= SF[i]/SFref;
      model->GetEYhigh()[i] *= SF[i] / SFref;
      model->GetEYlow()[i] *= SF[i] / SFref;
    }
  }

  /** Lund String Model Fitting **/
  /** CORRECT FOR SHIFT to X (light cone fraction) **/

  double nuList[4] = { 14.4, 13.1, 12.4, 10.7 };
  double Q2List[4] = { 2.4, 2.4, 2.4, 2.2 };

  const bool APPLY_Z_SHIFT = kTRUE;
  if (APPLY_Z_SHIFT) {
    for (int i = 0; i < 4; ++i) {
      double z = model->GetX()[i];
      double mt = 0.14;
      double nu = nuList[i];
      double Q2 = Q2List[i];
      double M = 0.938;
      double x = z;
      x *= (1 + TMath::Sqrt(1 - TMath::Power(mt / (z * nu), 2)));
      x /= (M / nu + 1 + TMath::Sqrt(1 + Q2 / TMath::Power(nu, 2)));
      model->GetX()[i] = x;
      // model->GetEX()[i] = 0.5*fabs(x - z);
      double shift = fabs(x - z);
      model->SetPointEXlow(i, 0);
      model->SetPointEXhigh(i, shift);
      // model_uncorrected->GetX()[i] = x;
      // model_uncorrected->GetEX()[i] = 0.5*fabs(x - z);
      cout << x - z << endl;
      variants->GetX()[i] = x;
    }
  }

  TGraphErrors* model_uncorrected = (TGraphErrors*)fin[kModel]->Get("tg_lp");
  TGraphErrors* model_syst = (TGraphErrors*)fin[kModel]->Get("tg_lp");
  model_uncorrected->SetMarkerStyle(kOpenCircle);
  for (int i = 0; i < 4; ++i) {
    model_syst->GetX()[i] = model->GetX()[i];
    double dy = fabs(model_syst->GetY()[i] - model->GetY()[i]);
    model_syst->GetEY()[i] = dy;
    model_syst->GetEX()[i] = variants->GetEX()[i];
  }
  model_syst->SetLineColor(kBlack);
  model_syst->SetLineWidth(2);
  /*
        Fitting to production length models
    */

  const char* LundLog = "[0]*x*(log(1/(x*x))-1+x*x)/(1-x*x)";                       // Bialas paper
  const char* LundLogFull = "(([1]+2*[2])/(2*[0]))*x*(log(1/(x*x))-1+x*x)/(1-x*x)"; // Bialas paper
  const char* LundLinearShort = "([0]+2*[1]-2*x*[1])/(2*[2])";
  const char* LundLinearLong = "(0.5*[0] + [1]*(0.5 + 0.5*sqrt(1 + [3]*[3]/([1]*[1])) - x))/[2]";

  TF1* fg0 = new TF1("fg1", LundLinearLong, 0, 1.2);
  fg0->SetParName(0, "MP");
  fg0->FixParameter(0, 0.938); // 0.9 GeV
  fg0->SetParName(1, "NU");
  fg0->FixParameter(1, 13.1);
  fg0->SetParName(2, "KAPPA");
  fg0->SetParameter(2, 1.0);
  fg0->SetParName(3, "Q2");
  fg0->FixParameter(3, 2.4);

  TF1* fg1 = new TF1("fg1", "1/(2*[0]) * ((1-x)*([1] + 2*[2]) - TMath::Power([3],2)/(x*([1] + 2*[2])))", 0, 1.2);
  fg1->SetParName(0, "KAPPA");
  fg1->SetParName(1, "MP");
  fg1->SetParName(2, "NU");
  fg1->SetParName(3, "mT");
  fg1->SetParameter(0, 1);
  fg1->FixParameter(1, 0.938);
  fg1->FixParameter(2, 12.4);
  // fg1->FixParameter(3, 0.14);
  double mass_trans = TMath::Sqrt(0.14 * 0.14 + 0.25);
  fg1->FixParameter(3, mass_trans);

  TF1* fg2 = new TF1("fg2", LundLogFull, 0, 1);
  fg2->SetParName(0, "KAPPA");
  fg2->SetParName(1, "MP");
  fg2->SetParName(2, "NU");
  fg2->SetParameter(0, 1);
  fg2->FixParameter(1, 0.938);
  fg2->FixParameter(2, 12.4);

  // model->SetLineWidth(2);
  // variants->SetLineWidth(2);
  fg1->SetLineWidth(2);
  fg2->SetLineWidth(2);
  fg1->SetLineColor(kAzure);
  fg2->SetLineColor(kRed);
  fg1->SetFillColorAlpha(kAzure, 0.3);
  fg2->SetFillColorAlpha(kRed, 0.3);

  fg1->SetNpx(10000);
  fg2->SetNpx(10000);

  const bool PLOT_MODELS_ONLY = kFALSE;
  if (PLOT_MODELS_ONLY) {
    TCanvas* c1 = new TCanvas("c1", "title", 800, 600);
    fg1->GetYaxis()->SetRangeUser(0, 100);
    fg1->SetTitle(";#it{z};#it{L}_{p} (fm)");
    fg1->Draw();
    fg2->Draw("SAME");
    fg0->Draw("SAME");
    c1->SetLogy();
    TLegend* leg = new TLegend(0.2, 0.75, 0.35, 0.92);
    leg->SetTextFont(42);
    leg->SetTextSize(0.03);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->AddEntry(fg0, "Lund String Model (struck quark) - with #it{z} = #it{E}/#nu", "l");
    leg->AddEntry(fg1, "Lund String Model (struck quark) - with #it{z} = #it{p}^{+}/P^{+}", "l");
    leg->AddEntry(fg2, "Bialas #it{et. al.} - with #it{z} = #it{p}^{+}/P^{+}", "l");
    leg->Draw();
    c1->Print("figure_models_lp.pdf");
    return;
  }

  int npoints = 500;
  model->Fit("fg1", "EMN0", "", 0.2, 0.96);
  TH1F* h1 = new TH1F("h1", "auxs", npoints + 1, 0, 1);
  auto gg1 = TH1TOTGraph(h1);
  TGraphErrors* grint1 = new TGraphErrors(99);
  grint1->SetTitle("Fitted line with .6827 conf. band");
  for (int i = 0; i < npoints; i++)
    grint1->SetPoint(i, gg1->GetX()[i], 0);
  //Compute the confidence intervals at the x points of the created graph
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint1, 0.6827);
  grint1->SetLineColor(kAzure);
  grint1->SetFillColorAlpha(kAzure, 0.4);
  // gStyle->SetHatchesLineWidth(2);
  // gStyle->SetHatchesSpacing(1);
  // grint1->SetFillStyle(3365);

  cout << "Lund Log Full" << endl;
  model->Fit("fg2", "EMN0", "", 0.25, 0.95);
  cout << "END Lund Log Full" << endl;

  TH1F* h2 = new TH1F("h2", "auxs", npoints + 1, 0, 1);
  auto gg2 = TH1TOTGraph(h2);
  TGraphErrors* grint2 = new TGraphErrors(99);
  grint2->SetTitle("Fitted line with .6827 conf. band");
  for (int i = 0; i < npoints; i++)
    grint2->SetPoint(i, gg2->GetX()[i], 0);
  //Compute the confidence intervals at the x points of the created graph
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint2, 0.6827);
  grint2->SetLineColor(kRed);
  grint2->SetFillColorAlpha(kRed, 0.4);
  // grint2->SetFillStyle(3356);

  grint1->SetLineWidth(2);
  grint2->SetLineWidth(2);

  cout << "Chi^2 = " << fg1->GetChisquare() << endl;
  cout << "NDF = " << fg1->GetNDF() << endl;
  cout << "Chi^2/NDF = " << fg1->GetChisquare() / fg1->GetNDF() << endl;
  cout << "p-value = " << fg1->GetProb() << endl;
  cout << "Chi^2 = " << fg2->GetChisquare() << endl;
  cout << "NDF = " << fg2->GetNDF() << endl;
  cout << "Chi^2/NDF = " << fg2->GetChisquare() / fg2->GetNDF() << endl;
  cout << "p-value = " << fg2->GetProb() << endl;

  // gStyle->SetEndErrorSize(8);
  TCanvas* c2 = new TCanvas("c2", "c2 title", 800, 600);

  model->Draw("APEZ");
  variants->Draw("SAME5");
  fg1->Draw("SAME");
  fg2->Draw("SAME");
  grint2->Draw("SAME 3");
  fg2->Draw("SAME");
  grint1->Draw("SAME 3");
  fg1->Draw("SAME");
  model->Draw("PSAMEZ");

  // model_uncorrected->Draw("PSAME");

  // model_syst->Draw("||");

  // TLegend* leg = new TLegend(0.2,0.2,0.35,0.35);
  TLegend* leg = new TLegend(0.2, 0.75, 0.35, 0.92);
  // leg->SetNColumns(2);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  // leg->AddEntry(model,"BLE30","pe");
  // leg->AddEntry(grint2,Form("Bialas #it{et. al.}, #chi^{2}/dof = %.3f",fg2->GetChisquare()/fg2->GetNDF()),"fl");
  // leg->AddEntry(grint1,Form("Linear Form, #chi^{2}/dof = %.3f, #kappa = %.3f #pm %.3f GeV/fm",fg1->GetChisquare()/fg1->GetNDF(),fg1->GetParameter(2),fg1->GetParError(2)),"fl");
  // leg->AddEntry(grint1,Form("Linear Form, #chi^{2}/dof = %.2f, #kappa = %.1f #pm %.1f GeV/fm",fg1->GetChisquare()/fg1->GetNDF(),fg1->GetParameter(2),fg1->GetParError(2)),"fl");

  // leg->AddEntry(grint1,Form("Lund String Model (struck quark), #chi^{2}/dof = %.2f, #kappa = %.2f #pm %.2f GeV/fm",fg1->GetChisquare()/fg1->GetNDF(),fg1->GetParameter(0),fg1->GetParError(0)),"fl");
  leg->AddEntry(grint1, Form("Lund string model, #chi^{2}/dof = %.2f, #kappa = %.2f #pm %.2f GeV/fm", fg1->GetChisquare() / fg1->GetNDF(), fg1->GetParameter(0), fg1->GetParError(0)), "fl");
  leg->AddEntry(grint2, Form("Bialas #it{et. al.}, #chi^{2}/dof = %.2f, #kappa = %.2f #pm %.2f GeV/fm", fg2->GetChisquare() / fg2->GetNDF(), fg2->GetParameter(0), fg2->GetParError(0)), "fl");

  // leg->AddEntry(grint1, "Lund String Model (struck quark)","fl");//   Form("Linear Form, #chi^{2}/dof = %.2f, #kappa = %.1f #pm %.1f GeV/fm",fg1->GetChisquare()/fg1->GetNDF(),fg1->GetParameter(0),fg1->GetParError(0)),"fl");
  // leg->AddEntry(grint2, "Bialas #it{et. al.}","fl");//Form("Bialas #it{et. al.}, #chi^{2}/dof = %.2f, #kappa = %.1f #pm %.1f GeV/fm",fg2->GetChisquare()/fg2->GetNDF(),fg2->GetParameter(1),fg2->GetParError(1)),"fl");
  if (kModel == 1)
    leg->AddEntry(model, "BL30", "pe");
  if (kModel == 3)
    leg->AddEntry(model, "BLE30", "pe");
  // leg->AddEntry(model,"BLE30 (corrected for kinematics)","pe");
  // leg->AddEntry(model_uncorrected,"BLE30 (uncorrected for kinematics)","pe");

  leg->Draw();

  // myText(0.2, 0.86, kBlack, "L_{p} = #frac{1}{2#kappa}#(){M_{p}+#nu#(){1+#sqrt{1+(Q/#nu)^{2}}} - 2#nuz}",0.04);
  // myText(0.2, 0.78, kBlack, "#kappa = 0.98 #pm 0.09 GeV/fm, #chi^{2}/dof = 1.09",0.04);
  // myText(0.2, 0.86, kBlack, "#LTQ^{2}#GT = 2.4 GeV^{2}, #LT#nu#GT = 13.1 GeV",0.04);
  myText(0.22, 0.23, kBlack, "#LTQ^{2}#GT = 2.4 GeV^{2}, #LT#nu#GT = 12.4 GeV", 0.045); // z-bin #3

  c2->SetLogy();

  //    myText(0.2, 0.4, kBlack, "Fit uncorrected for kinematics", 0.05, 0);
  c2->Print("figure_models_lundfit_lp.pdf");
}
