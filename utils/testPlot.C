void testPlot()
{
  SetAtlasStyle();
  auto file0 = TFile::Open("OutputROOT.nominal.root");
  auto file1 = TFile::Open("OutputROOT.Fit_with_Lp0c2.root");
  TGraphErrors* tg_nominal = (TGraphErrors*)file0->Get("tg_lp");

  TGraphErrors* tg_lp = (TGraphErrors*)file1->Get("tg_lp");
  TGraphErrors* tg_c1 = (TGraphErrors*)file1->Get("tg_c1");
  TGraphErrors* tg_c2 = (TGraphErrors*)file1->Get("tg_c2");

  TGraphErrors* tg_A1 = new TGraphErrors(4);
  TGraphErrors* tg_A2 = new TGraphErrors(4);
  TGraphErrors* tg_A3 = new TGraphErrors(4);

  double* xp = tg_lp->GetX();
  double* lp = tg_lp->GetY();
  double* c1 = tg_c1->GetY();
  double* c2 = tg_c2->GetY();
  double* lpErr = tg_lp->GetEY();
  double* c1Err = tg_c1->GetEY();
  double* c2Err = tg_c2->GetEY();

  double A[3] = { 20, 83, 131 };
  double l_A_Err[3];
  // double rr0[4]={-0.968,-0.990,-0.987,-0.983}; // <c1,c2> only
  double rr0[4] = { -0.882, -0.966, -0.978, -0.969 }; // <lp,c2> only

  double rr1[4] = { -0.161, -0.955, -0.784, -0.968 }; // <lp,c1>
  double rr2[4] = { 0.118, 0.877, 0.365, 0.903 };     // <lp,c2>
  double rr3[4] = { -0.986, -0.980, -0.860, -0.982 }; // <c1,c2>

  for (int i = 0; i < 4; ++i) {
    tg_A1->SetPoint(i, xp[i], lp[i] + c1[i] * pow(20, 1.0 / 3.0) + c2[i] * pow(20, 2.0 / 3.0));
    tg_A2->SetPoint(i, xp[i], lp[i] + c1[i] * pow(83, 1.0 / 3.0) + c2[i] * pow(83, 2.0 / 3.0));
    tg_A3->SetPoint(i, xp[i], lp[i] + c1[i] * pow(131, 1.0 / 3.0) + c2[i] * pow(131, 2.0 / 3.0));

    // 3x3
    // for (int j=0; j<3; ++j) {
    //     l_A_Err[j] = 0;
    //     l_A_Err[j] += pow(lpErr[i],2) + pow(A[j],2./3.)*pow(c1Err[i],2) + pow(A[j],4.0/3.0)*pow(c2Err[i],2);
    //     l_A_Err[j] += 2*pow(A[j],1./3.)*lpErr[i]*c1Err[i]*rr1[i];
    //     l_A_Err[j] += 2*pow(A[j],2./3.)*lpErr[i]*c2Err[i]*rr2[i];
    //     l_A_Err[j] += 2*pow(A[j],1./3.)*pow(A[j],2./3.)*c1Err[i]*c2Err[i]*rr3[i];
    //     l_A_Err[j] = sqrt(l_A_Err[j]);
    // }
    // 2x2
    // for (int j=0; j<3; ++j) {
    //     l_A_Err[j] = 0;
    //     l_A_Err[j] += pow(A[j],2./3.)*pow(c1Err[i],2) + pow(A[j],4.0/3.0)*pow(c2Err[i],2);
    //     l_A_Err[j] += 2*pow(A[j],1./3.)*pow(A[j],2./3.)*c1Err[i]*c2Err[i]*rr0[i];
    //     l_A_Err[j] = sqrt(l_A_Err[j]);
    // }
    for (int j = 0; j < 3; ++j) {
      l_A_Err[j] = 0;
      l_A_Err[j] += pow(lpErr[i], 2) + pow(A[j], 4.0 / 3.0) * pow(c2Err[i], 2);
      l_A_Err[j] += 2 * pow(A[j], 2. / 3.) * lpErr[i] * c2Err[i] * rr0[i];
      l_A_Err[j] = sqrt(l_A_Err[j]);
    }

    tg_A1->SetPointError(i, 0, l_A_Err[0]);
    tg_A2->SetPointError(i, 0, l_A_Err[1]);
    tg_A3->SetPointError(i, 0, l_A_Err[2]);
  }
  tg_A1->SetMarkerColor(kAzure);
  tg_A1->SetLineColor(kAzure);
  tg_A2->SetMarkerColor(kMagenta);
  tg_A2->SetLineColor(kMagenta);
  tg_A3->SetMarkerColor(kOrange);
  tg_A3->SetLineColor(kOrange);
  tg_A1->SetMarkerStyle(kFullSquare);
  tg_A2->SetMarkerStyle(kFullSquare);
  tg_A3->SetMarkerStyle(kFullSquare);
  tg_A1->SetLineWidth(2);
  tg_A2->SetLineWidth(2);
  tg_A3->SetLineWidth(2);

  TCanvas* canvas = new TCanvas("canvas", "Production Length", 600, 600 * 0.75);
  gStyle->SetEndErrorSize(7);
  tg_nominal->GetYaxis()->SetRangeUser(0, 14);
  tg_nominal->SetTitle(";z;Production Length [fm]");
  tg_nominal->Draw("APE");
  tg_A1->Draw("PSAME");
  tg_A2->Draw("PSAME");
  tg_A3->Draw("PSAME");
  tg_nominal->Draw("PSAME");
  myText(0.5, 0.8, kBlack, "L(A) = L_{p} + c_{1}A^{1/3} + c_{2}A^{2/3}", 22);
  myMarkerText(0.28, 0.34, tg_nominal->GetMarkerColor(), tg_nominal->GetMarkerStyle(), "L = L_{p}, with c_{1}=c_{2}=0", 1, 22);
  myMarkerText(0.28, 0.30, tg_A1->GetMarkerColor(), tg_A1->GetMarkerStyle(), "L(A = 20)", 1, 22);
  myMarkerText(0.28, 0.26, tg_A2->GetMarkerColor(), tg_A2->GetMarkerStyle(), "L(A = 83)", 1, 22);
  myMarkerText(0.28, 0.22, tg_A3->GetMarkerColor(), tg_A3->GetMarkerStyle(), "L(A = 131)", 1, 22);
  canvas->Print("TestingNewModel1_New.pdf");

  auto rp1 = myTGraphErrorsDivide(tg_A1, tg_nominal);
  auto rp2 = myTGraphErrorsDivide(tg_A2, tg_nominal);
  auto rp3 = myTGraphErrorsDivide(tg_A3, tg_nominal);

  rp1->SetMarkerStyle(tg_A1->GetMarkerStyle());
  rp1->SetMarkerColor(tg_A1->GetMarkerColor());
  rp1->SetLineColor(tg_A1->GetMarkerColor());
  rp2->SetMarkerStyle(tg_A2->GetMarkerStyle());
  rp2->SetMarkerColor(tg_A2->GetMarkerColor());
  rp2->SetLineColor(tg_A2->GetMarkerColor());
  rp3->SetMarkerStyle(tg_A3->GetMarkerStyle());
  rp3->SetMarkerColor(tg_A3->GetMarkerColor());
  rp3->SetLineColor(tg_A3->GetMarkerColor());
  rp1->SetLineWidth(2);
  rp2->SetLineWidth(2);
  rp3->SetLineWidth(2);

  for (int i = 0; i < 4; ++i) {
    double x = 0, y = 0;
    tg_A1->GetPoint(i, x, y);
    tg_A1->SetPoint(i, x + 0.01, y);
    tg_A2->GetPoint(i, x, y);
    tg_A2->SetPoint(i, x + 0.02, y);
    tg_A3->GetPoint(i, x, y);
    tg_A3->SetPoint(i, x + 0.03, y);
  }

  for (int i = 0; i < 4; ++i) {
    double x = 0, y = 0;
    rp1->GetPoint(i, x, y);
    rp1->SetPoint(i, x + 0.01, y);
    rp2->GetPoint(i, x, y);
    rp2->SetPoint(i, x + 0.02, y);
    rp3->GetPoint(i, x, y);
    rp3->SetPoint(i, x + 0.03, y);
  }

  TCanvas* c3 = new TCanvas("c3", "example", 600, 600);
  c3->SetFillColor(0);
  c3->SetFrameFillStyle(0);
  TPad* pad1 = new TPad("pad1", "pad1", 0, 0.4, 1, 1);
  pad1->SetBottomMargin(0);
  pad1->Draw();
  pad1->cd();
  tg_nominal->GetXaxis()->SetLimits(0.25, 1);
  tg_nominal->GetYaxis()->SetRangeUser(0.01, 14);
  tg_nominal->Draw("APE");
  tg_A1->Draw("PSAME");
  tg_A2->Draw("PSAME");
  tg_A3->Draw("PSAME");
  myText(0.5, 0.875, kBlack, "L(A) = L_{p} + c_{2}A^{2/3}", 22);
  myMarkerText(0.55, 0.8, tg_nominal->GetMarkerColor(), tg_nominal->GetMarkerStyle(), "L = L_{p}, with c_{1}=c_{2}=0", 1.25, 22);
  myMarkerText(0.55, 0.75, tg_A1->GetMarkerColor(), tg_A1->GetMarkerStyle(), "L(A = 20)", 1.25, 22);
  myMarkerText(0.55, 0.70, tg_A2->GetMarkerColor(), tg_A2->GetMarkerStyle(), "L(A = 83)", 1.25, 22);
  myMarkerText(0.55, 0.65, tg_A3->GetMarkerColor(), tg_A3->GetMarkerStyle(), "L(A = 131)", 1.25, 22);
  c3->cd();
  TPad* pad2 = new TPad("pad2", "pad2", 0, 0, 1, 0.4);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();
  rp1->GetYaxis()->SetRangeUser(0.27, 1.55);
  rp1->GetXaxis()->SetLimits(0.25, 1);
  rp1->GetXaxis()->SetTitleOffset(2.5);
  rp1->SetTitle(";z;L(A)/L(0)");
  rp1->Draw("APE");
  rp2->Draw("PSAME");
  rp3->Draw("PSAME");
  c3->Print("Plot-Fit_with_Lp0c2.pdf");

  return;

  TCanvas* canvas2 = new TCanvas("canvas2", "canvas2", 600, 600 * 0.75);
  TGraph* nomChiSq = (TGraph*)file0->Get("tg_chisquared");
  TGraph* varChiSq = (TGraph*)file1->Get("tg_chisquared");
  double value, foo;
  for (int i = 0; i < 4; ++i) {
    nomChiSq->GetPoint(i, foo, value);
    value = value / 4;
    nomChiSq->SetPoint(i, foo, value);
    varChiSq->GetPoint(i, foo, value);
    value = value / 3;
    varChiSq->SetPoint(i, foo, value);
  }
  nomChiSq->SetMarkerStyle(kOpenCircle);
  varChiSq->SetMarkerStyle(kOpenSquare);
  nomChiSq->SetTitle(";z;#chi^{2}/ndf");
  nomChiSq->GetYaxis()->SetRangeUser(0, 2.5);
  nomChiSq->Draw("APE");
  varChiSq->Draw("PSAME");
  myMarkerText(0.24, 0.26, nomChiSq->GetMarkerColor(), nomChiSq->GetMarkerStyle(), "Nominal", 1, 22);
  myMarkerText(0.24, 0.22, varChiSq->GetMarkerColor(), varChiSq->GetMarkerStyle(), "Test model", 1, 22);
  canvas2->Print("TestingNewModel1_New_Chi2ndf.pdf");

  TCanvas* canvas3 = new TCanvas("canvas3", "canvas3", 600, 600 * 0.75);
  tg_c2->SetTitle(";z;c_{j}");
  tg_c2->GetYaxis()->SetRangeUser(-1, 6);
  tg_lp->SetMarkerStyle(kFullCircle);
  tg_lp->SetMarkerColor(kBlack);
  tg_lp->SetLineColor(kBlack);
  tg_c1->SetMarkerStyle(kFullCircle);
  tg_c1->SetMarkerColor(kRed);
  tg_c1->SetLineColor(kRed);
  tg_c2->SetMarkerStyle(kFullCircle);
  tg_c2->SetMarkerColor(kBlue);
  tg_c2->SetLineColor(kBlue);
  // tg_c1->Draw("APE");
  tg_c2->Draw("APE");
  tg_lp->Draw("PSAME");
  myMarkerText(0.24, 0.88, tg_lp->GetMarkerColor(), tg_lp->GetMarkerStyle(), "L_{p}^{0}", 1, 22);
  // myMarkerText(0.24,0.84,tg_c1->GetMarkerColor(),tg_c1->GetMarkerStyle(),"c_{1}",1,22);
  myMarkerText(0.24, 0.84, tg_c2->GetMarkerColor(), tg_c2->GetMarkerStyle(), "c_{2}", 1, 22);
  canvas3->Print("TestingNewModel1_c1c2.pdf");
}