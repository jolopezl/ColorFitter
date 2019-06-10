float zcentr[4] = { 0.32, 0.53, 0.75, 0.94 };
float pt2_neon[4] = { 0.0069, 0.0063, -0.0015, -0.0037 };
float pt2_err_neon[4] = { 0.002747726333, 0.005152669211, 0.01350888596, 0.02077666961 };
float pt2_kripton[4] = { 0.021, 0.0224, 0.0085, 0.0115 };
float pt2_err_kripton[4] = { 0.002946183973, 0.005444263036, 0.01360477857, 0.02106038936 };
float pt2_xenon[4] = { 0.0274, 0.0296, 0.0144, 0.0073 };
float pt2_err_xenon[4] = { 0.003243454948, 0.005979130372, 0.01442289846, 0.02177360788 };

float rm_neon[4] = { 0.893189114368, 0.885454096825, 0.880935853275, 0.798520384419 };
float rm_kripton[4] = { 0.78747612087, 0.744660997913, 0.679028679486, 0.551673817154 };
float rm_xenon[4] = { 0.736762500635, 0.684223383665, 0.619689942725, 0.498076090992 };
float rm_err_neon[4] = { 0.0594409344724, 0.0515307622582, 0.0634878265064, 0.0682394907588 };
float rm_err_kripton[4] = { 0.0542930099596, 0.0447182315218, 0.05222907333, 0.0527700155986 };
float rm_err_xenon[4] = { 0.0535218789044, 0.0411665583174, 0.0503850083386, 0.0529182285411 };

void makeFigure(int plot = 2)
{
  SetAtlasStyle(43, 32);
  gStyle->SetEndErrorSize(0);
  TFile* fin = TFile::Open("OutputROOT.20180806.BL30.root");
  TFile* fin_uncertainties = TFile::Open("OutputROOT_ToyMC_ModelUncertianties.root");
  TGraphErrors* tg[4];
  TGraphErrors* tg_up[4];
  TGraphErrors* tg_down[4];
  TGraphErrors* tg_toy_up[4];
  TGraphErrors* tg_toy_down[4];
  TGraphAsymmErrors* band[4];
  for (int i = 0; i < 4; ++i) {
    if (plot == 1) {
      tg[i] = (TGraphErrors*)fin->Get(Form("tg_model_pT_extrapolation_%d", i));
      tg_up[i] = (TGraphErrors*)fin->Get(Form("tg_model_pT_extrapolation_up_%d", i));
      tg_down[i] = (TGraphErrors*)fin->Get(Form("tg_model_pT_extrapolation_down_%d", i));
      tg_toy_up[i] = (TGraphErrors*)fin_uncertainties->Get(Form("tg_model_toy_fitted_up_PT2_%d", i));
      tg_toy_down[i] = (TGraphErrors*)fin_uncertainties->Get(Form("tg_model_toy_fitted_down_PT2_%d", i));
    } else {
      tg[i] = (TGraphErrors*)fin->Get(Form("tg_model_Rm_extrapolation_%d", i));
      tg_up[i] = (TGraphErrors*)fin->Get(Form("tg_model_Rm_extrapolation_up_%d", i));
      tg_down[i] = (TGraphErrors*)fin->Get(Form("tg_model_Rm_extrapolation_down_%d", i));
      tg_toy_up[i] = (TGraphErrors*)fin_uncertainties->Get(Form("tg_model_toy_fitted_up_RM_%d", i));
      tg_toy_down[i] = (TGraphErrors*)fin_uncertainties->Get(Form("tg_model_toy_fitted_down_RM_%d", i));
    }
    band[i] = myMakeBand(tg[i], tg_toy_up[i], tg_toy_down[i]);
    tg[i]->SetLineColor(kRed);
    tg[i]->SetLineWidth(2);
    tg_up[i]->SetLineColor(kRed);
    tg_up[i]->SetLineWidth(2);
    tg_up[i]->SetLineStyle(kDashed);
    tg_down[i]->SetLineColor(kRed);
    tg_down[i]->SetLineWidth(2);
    tg_down[i]->SetLineStyle(kDashed);
    band[i]->SetFillColorAlpha(kOrange, 0.75);
    tg_toy_up[i]->SetLineWidth(2);
    tg_toy_up[i]->SetLineStyle(kDashed);
    tg_toy_down[i]->SetLineWidth(2);
    tg_toy_down[i]->SetLineStyle(kDashed);
  }

  /** data points **/
  TGraphErrors* data[4];
  float xval[3] = { 2.9947753767563916, 4.813606330683598, 5.590790378970299 };
  float xerr[3] = { 0, 0, 0 };
  for (int i = 0; i < 4; ++i) {
    float yval1[4] = { pt2_neon[i], pt2_kripton[i], pt2_xenon[i] };
    float yerr1[4] = { pt2_err_neon[i], pt2_err_kripton[i], pt2_err_xenon[i] };
    float yval2[4] = { rm_neon[i], rm_kripton[i], rm_xenon[i] };
    float yerr2[4] = { rm_err_neon[i], rm_err_kripton[i], rm_err_xenon[i] };
    if (plot == 1) {
      data[i] = new TGraphErrors(3, xval, yval1, xerr, yerr1);
      if (i == 0 || i == 1) {
        data[i]->GetYaxis()->SetRangeUser(-0.028, 0.039);
      } else {
        data[i]->GetYaxis()->SetRangeUser(-0.028, 0.039);
      }
    } else {
      data[i] = new TGraphErrors(3, xval, yval2, xerr, yerr2);
      data[i]->GetYaxis()->SetRangeUser(0.31, 1.099);
    }
  }
  if (plot == 1) {
    data[0]->GetYaxis()->SetTitle("#Delta #LT p_{T}^{2} #GT [GeV^{2}]");
  } else {
    data[0]->GetYaxis()->SetTitle("R_{M}");
  }
  data[0]->GetYaxis()->SetTitleOffset(2.5);
  data[3]->GetXaxis()->SetTitle("A^{1/3}");
  data[3]->GetXaxis()->SetTitleOffset(2);

  float small = 1e-5;
  ;
  float big = 0.25;
  TCanvas* c1 = new TCanvas("c1", "c1 title", 800, 800);
  c1->SetLeftMargin(0.21);
  c1->SetBottomMargin(0.15);
  // c1->Divide(2,2,small,small);
  // c1->Divide(2,2,0,0);
  c1->DivideSquare(4, 0, 0);
  for (int i = 0; i < 4; ++i) {
    // pad[i]->cd();
    c1->cd(i + 1);
    // if (i == 0) {
    //     gPad->SetBottomMargin(small);
    //     gPad->SetRightMargin(small);
    //     gPad->SetLeftMargin(big);
    //     gPad->SetTopMargin(big);
    // }
    // else if (i == 1) {
    //     gPad->SetTopMargin(big);
    //     gPad->SetBottomMargin(small);
    //     gPad->SetLeftMargin(small);
    //     gPad->SetRightMargin(big);
    // }
    // else if (i == 2) {
    //     gPad->SetBottomMargin(big);
    //     gPad->SetTopMargin(small);
    //     gPad->SetRightMargin(small);
    //     gPad->SetLeftMargin(big);
    // }
    // else if (i == 3) {
    //     gPad->SetBottomMargin(big);
    //     gPad->SetTopMargin(small);
    //     gPad->SetLeftMargin(small);
    //     gPad->SetRightMargin(big);
    // }
    // if (i==0) data[i]->Draw();
    data[i]->Draw("AP");
    band[i]->Draw("3SAME");
    tg[i]->Draw("CLSAME");
    data[i]->Draw("PSAME");
    // tg_up[i]->Draw("CLSAME");
    // tg_down[i]->Draw("CLSAME");
    // tg_toy_up[i]->Draw("CLSAME");
    // tg_toy_down[i]->Draw("CLSAME");
  }

  c1->cd(1);
  myText(0.3, 0.925, 1, "z-bin #1", 22);
  myMarkerText(0.35, 0.2, kWhite, kFullCircle, "Data", 1, 22);
  myMarkerText(0.3325, 0.2, kBlack, kFullCircle, "", 1, 22);
  myBoxText(0.35, 0.14, 0.05, kOrange, "BL30 + MC Uncertainties", kRed);
  // myLineText(0.35, 0.08, 0.05, kRed, "Analytical Uncertainties",kDashed);
  // myBoxText(0.35, 0.08, 0.0, kWhite, "Analytical Uncertainties",kWhite);
  c1->cd(2);
  myText(0.075, 0.925, 1, "z-bin #2", 22);
  c1->cd(3);
  myText(0.3, 0.925, 1, "z-bin #3", 22);
  c1->cd(4);
  myText(0.075, 0.925, 1, "z-bin #4", 22);
  if (plot == 1) {
    c1->Print("modelplot_pT2_Symm.pdf");
  } else {
    c1->Print("modelplot_Rm_Symm.pdf");
  }
}
