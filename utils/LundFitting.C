void LundFitting()
{
  SetAtlasStyle();
  // std::string models[12] = {"BL","BL30","BL40","BLE","BLE30","BLE40",
  //                           "BL.fixedLp","BL30.fixedLp","BL40.fixedLp","BLE.fixedLp","BLE30.fixedLp","BLE40.fixedLp"};

  TFile* fin = TFile::Open("OutputROOT.20180806.BLE30.root", "READ");

  auto tg1 = (TGraphErrors*)fin->Get("tg_lp");

  // std::map<std::string,TFile*> fin;
  // for (int i = 0; i < 12; ++i) {
  //     std:string ifile = "testFit"+models[i]+".root";
  //     fin[models[i]] = TFile::Open(ifile.c_str(), "READ");
  // }
  // std::string plotsNames[7] = {"tg_q0","tg_lp","tg_cs","tg_dlog","tg_dz","tg_casc","tg_chisq"};

  // gStyle->SetEndErrorSize(5);
  // gStyle->SetErrorX(0.);

  // const char *key2 = "tg_lp";
  // auto tg1 = (TGraphErrors*) fin["BL30"]->Get(key2); tg1->SetMarkerStyle(20); tg1->SetMarkerColor(kAzure); tg1->SetLineColor(kAzure);
  // auto tg2 = (TGraphErrors*) fin["BL40"]->Get(key2); tg2->SetMarkerStyle(24); tg2->SetMarkerColor(kAzure - 1); tg2->SetLineColor(kAzure - 1);
  // auto tg3 = (TGraphErrors*) fin["BL30.fixedLp"]->Get(key2); tg3->SetMarkerStyle(21); tg3->SetMarkerColor(kOrange); tg3->SetLineColor(kOrange);
  // auto tg4 = (TGraphErrors*) fin["BL40.fixedLp"]->Get(key2); tg4->SetMarkerStyle(25); tg4->SetMarkerColor(kOrange - 1); tg4->SetLineColor(kOrange - 1);

  // Remember to apply scale factors
  double SF[4] = { 9.31, 8.40, 7.94, 7.05 };
  double SFref = 7.05;
  // double SF[4] = {8.40,8.40,8.40,8.40};
  for (int i = 0; i < 4; ++i) {
    tg1->GetY()[i] *= SF[i] / SFref;
    tg1->GetEY()[i] *= SF[i] / SFref;
  }
  tg1->SetMarkerSize(1.5);

  const char* LundLog = "[0]*x*(log(1/(x*x))-1+x*x)/(1-x*x)";
  const char* LundLinearShort = "([0]+2*[1]-2*x*[1])/(2*[2])";
  // const char* LundLinearLong = "([0]+2*[1]-2*x*[1]+[1]*(sqrt(1+[3]*[3]/([1]*[1]))-1))/(2*[2])";
  const char* LundLinearLong = "(0.5*[0] + [1]*(0.5 + 0.5*sqrt(1 + [3]*[3]/([1]*[1])) - x))/[2]";

  TF1* fg1 = new TF1("fg1", LundLinearLong, 0.5, 0.96);
  fg1->SetParName(0, "MP");
  fg1->FixParameter(0, 0.938272); // 0.9 GeV
  fg1->SetParName(1, "NU");
  fg1->FixParameter(1, 13.1);
  fg1->SetParName(2, "KAPPA");
  fg1->SetParameter(2, 1.0);
  fg1->SetParName(3, "Q2");
  fg1->FixParameter(3, 2.4);

  TF1* fg2 = new TF1("fg2", LundLog, 0.25, 0.96);
  fg2->SetParName(0, "F(Q2,NU)");
  fg2->SetParameter(0, 1); // 0.9 GeV

  // tg1->SetMarkerColor(kBlack);
  // tg1->SetLineColor(kBlack);
  // tg1->SetLineWidth(2);

  int npoints = 500;

  tg1->Fit("fg1", "EMN0", "", 0.5, 0.96);

  TH1F* h1 = new TH1F("h1", "auxs", npoints + 1, 0.5, 0.96);
  auto gg1 = TH1TOTGraph(h1);
  TGraphErrors* grint1 = new TGraphErrors(99);
  grint1->SetTitle("Fitted line with .6827 conf. band");
  for (int i = 0; i < npoints; i++)
    grint1->SetPoint(i, gg1->GetX()[i], 0);
  //Compute the confidence intervals at the x points of the created graph
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint1, 0.6827);
  grint1->SetLineColor(kBlue + 1);
  grint1->SetFillColorAlpha(kBlue + 1, 0.25);
  gStyle->SetHatchesLineWidth(4);
  // grint1->SetFillStyle(3365);

  tg1->Fit("fg2", "EMN0", "", 0.25, 0.95);

  TH1F* h2 = new TH1F("h2", "auxs", npoints + 1, 0.25, 0.96);
  auto gg2 = TH1TOTGraph(h2);
  TGraphErrors* grint2 = new TGraphErrors(99);
  grint2->SetTitle("Fitted line with .6827 conf. band");
  for (int i = 0; i < npoints; i++)
    grint2->SetPoint(i, gg2->GetX()[i], 0);
  //Compute the confidence intervals at the x points of the created graph
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint2, 0.6827);
  grint2->SetLineColor(kRed + 1);
  grint2->SetFillColorAlpha(kRed + 1, 0.25);
  // grint2->SetFillStyle(3356);

  tg1->GetXaxis()->SetLimits(0.0, 1.0);
  tg1->GetXaxis()->SetNdivisions(505);
  tg1->GetYaxis()->SetRangeUser(0.0001, 12.0);
  tg1->SetTitle(";z;L_{p} [fm]");

  // gStyle->SetEndErrorSize(7.0);
  fg1->SetLineColor(kBlue + 1);
  fg2->SetLineColor(kRed + 1);
  // fg1->SetLineWidth(5);
  // fg2->SetLineWidth(5);

  TCanvas* c2 = new TCanvas("c2", "c2 title", 800, 600);
  tg1->Draw("APE");

  fg1->Draw("SAME");
  fg2->Draw("SAME");

  grint2->Draw("SAME 3");
  fg2->Draw("SAME");
  grint1->Draw("SAME 3");
  fg1->Draw("SAME");

  tg1->Draw("PSAME");

  cout << "Chi^2 = " << fg1->GetChisquare() << endl;
  cout << "NDF = " << fg1->GetNDF() << endl;
  cout << "Chi^2/NDF = " << fg1->GetChisquare() / fg1->GetNDF() << endl;
  cout << "p-value = " << fg1->GetProb() << endl;

  cout << "Chi^2 = " << fg2->GetChisquare() << endl;
  cout << "NDF = " << fg2->GetNDF() << endl;
  cout << "Chi^2/NDF = " << fg2->GetChisquare() / fg2->GetNDF() << endl;
  cout << "p-value = " << fg2->GetProb() << endl;

  TLegend* leg = new TLegend(0.2, 0.2, 0.35, 0.35);
  // leg->SetNColumns(2);
  leg->SetTextFont(43);
  leg->SetTextSize(18);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->AddEntry(tg1, "BL30", "pe");
  leg->AddEntry(fg1, Form("Linear fit, #chi^{2}/dof = %.3f, #kappa = %.3f #pm %.3f GeV/fm", fg1->GetChisquare() / fg1->GetNDF(), fg1->GetParameter(2), fg1->GetParError(2)), "l");
  leg->AddEntry(fg2, Form("Log form fit, #chi^{2}/dof = %.3f", fg2->GetChisquare() / fg2->GetNDF()), "l");
  leg->Draw();

  // myText(0.2, 0.86, kBlack, "L_{p} = #frac{1}{2#kappa}#(){M_{p}+#nu#(){1+#sqrt{1+(Q/#nu)^{2}}} - 2#nuz}",0.04);
  // myText(0.2, 0.78, kBlack, "#kappa = 0.98 #pm 0.09 GeV/fm, #chi^{2}/dof = 1.09",0.04);
  myText(0.2, 0.86, kBlack, "#LTQ^{2}#GT = 2.4 GeV^{2}, #LT#nu#GT = 13.1 GeV", 0.04);
  // (log(1/(x*x))-1+x*x)/(1-x*x)
  // myText(0.2, 0.86, kBlack, "L_{p} = f(Q^{2},#nu) z_{h} #frac{log(1/z_{h}^{2}) - 1 + z_{h}^{2}}{1-z_{h}^{2}} ",0.04);
  // myText(0.2, 0.78, kBlack, "f(Q^{2},#nu) = 17.6 #pm 1.63 fm, #chi^{2}/dof = 2.43",0.04);
  // 1.75622e+01   1.62663e+00

  c2->Print("test2.pdf");
}
