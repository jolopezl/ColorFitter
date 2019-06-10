float zcentr[4] = { 0.32, 0.53, 0.75, 0.94 };
float pt2_neon[4] = { 0.0069, 0.0063, -0.0015, -0.0037 };
float pt2_kripton[4] = { 0.021, 0.0224, 0.0085, 0.0115 };
float pt2_xenon[4] = { 0.0274, 0.0296, 0.0144, 0.0073 };
// float pt2_err_neon[4]     = {0.002747726333,0.005152669211,0.01350888596,0.02077666961};
// float pt2_err_kripton[4]  = {0.002946183973,0.005444263036,0.01360477857,0.02106038936};
// float pt2_err_xenon[4]    = {0.003243454948,0.005979130372,0.01442289846,0.02177360788};
float pt2_err_neon[4] = { 0.002747726333, 0.005152669211, 0.5 * 0.01350888596, 0.5 * 0.02077666961 };
float pt2_err_kripton[4] = { 0.002946183973, 0.005444263036, 0.5 * 0.01360477857, 0.5 * 0.02106038936 };
float pt2_err_xenon[4] = { 0.003243454948, 0.005979130372, 0.5 * 0.01442289846, 0.5 * 0.02177360788 };

float rm_neon[4] = { 0.893189114368, 0.885454096825, 0.880935853275, 0.798520384419 };
float rm_kripton[4] = { 0.78747612087, 0.744660997913, 0.679028679486, 0.551673817154 };
float rm_xenon[4] = { 0.736762500635, 0.684223383665, 0.619689942725, 0.498076090992 };
float rm_err_neon[4] = { 0.0594409344724, 0.0515307622582, 0.0634878265064, 0.0682394907588 };
float rm_err_kripton[4] = { 0.0542930099596, 0.0447182315218, 0.05222907333, 0.0527700155986 };
float rm_err_xenon[4] = { 0.0535218789044, 0.0411665583174, 0.0503850083386, 0.0529182285411 };

void makeFigure2()
{
  SetAtlasStyle(43, 22);
  gStyle->SetEndErrorSize(0);

  const char* variantname = "BL30";

  TFile* fin = TFile::Open(Form("OutputROOT.20181107.%s.root", variantname));
  TFile* fin_uncertainties = TFile::Open("./OutputROOT_ToyMC_ModelUncertianties.root");
  std::pair<TGraphErrors*, TGraphErrors*> tg[4];
  std::pair<TGraphErrors*, TGraphErrors*> tg_up[4];
  std::pair<TGraphErrors*, TGraphErrors*> tg_down[4];
  std::pair<TGraphErrors*, TGraphErrors*> tg_toy_up[4];
  std::pair<TGraphErrors*, TGraphErrors*> tg_toy_down[4];
  std::pair<TGraphAsymmErrors*, TGraphAsymmErrors*> band[4];
  for (int i = 0; i < 4; ++i) {
    tg[i].first = (TGraphErrors*)fin->Get(Form("tg_model_pT_extrapolation_%d", i));
    tg_up[i].first = (TGraphErrors*)fin->Get(Form("tg_model_pT_extrapolation_up_%d", i));
    tg_down[i].first = (TGraphErrors*)fin->Get(Form("tg_model_pT_extrapolation_down_%d", i));
    // tg_toy_up[i].first = (TGraphErrors*) fin_uncertainties->Get(Form("tg_model_toy_fitted_up_PT2_%d",i));
    // tg_toy_down[i].first = (TGraphErrors*) fin_uncertainties->Get(Form("tg_model_toy_fitted_down_PT2_%d",i));
    tg[i].second = (TGraphErrors*)fin->Get(Form("tg_model_Rm_extrapolation_%d", i));
    tg_up[i].second = (TGraphErrors*)fin->Get(Form("tg_model_Rm_extrapolation_up_%d", i));
    tg_down[i].second = (TGraphErrors*)fin->Get(Form("tg_model_Rm_extrapolation_down_%d", i));
    // tg_toy_up[i].second = (TGraphErrors*) fin_uncertainties->Get(Form("tg_model_toy_fitted_up_RM_%d",i));
    // tg_toy_down[i].second = (TGraphErrors*) fin_uncertainties->Get(Form("tg_model_toy_fitted_down_RM_%d",i));
    // band[i].first = myMakeBand(tg[i].first,tg_toy_up[i].first,tg_toy_down[i].first);
    // band[i].second = myMakeBand(tg[i].second,tg_toy_up[i].second,tg_toy_down[i].second);
    band[i].first = myMakeBand(tg[i].first, tg_up[i].first, tg_down[i].first);
    band[i].second = myMakeBand(tg[i].second, tg_up[i].second, tg_down[i].second);
    tg[i].first->SetLineColor(kAzure);
    tg[i].first->SetLineWidth(3);
    band[i].first->SetFillColorAlpha(kAzure, 0.5);
    tg[i].second->SetLineColor(kRed + 1);
    tg[i].second->SetLineWidth(3);
    band[i].second->SetFillColorAlpha(kRed + 1, 0.5);
  }
  /** data points **/
  std::pair<TGraphErrors*, TGraphErrors*> data[4];
  data[0].first = (TGraphErrors*)fin->Get("tg_data_pT_0");
  data[1].first = (TGraphErrors*)fin->Get("tg_data_pT_1");
  data[2].first = (TGraphErrors*)fin->Get("tg_data_pT_2");
  data[3].first = (TGraphErrors*)fin->Get("tg_data_pT_3");
  data[0].second = (TGraphErrors*)fin->Get("tg_data_Rm_0");
  data[1].second = (TGraphErrors*)fin->Get("tg_data_Rm_1");
  data[2].second = (TGraphErrors*)fin->Get("tg_data_Rm_2");
  data[3].second = (TGraphErrors*)fin->Get("tg_data_Rm_3");

  float xval[3] = { 2.9947753767563916, 4.813606330683598, 5.590790378970299 };
  float xerr[3] = { 0, 0, 0 };
  for (int i = 0; i < 4; ++i) {
    float yval1[4] = { pt2_neon[i], pt2_kripton[i], pt2_xenon[i] };
    float yerr1[4] = { pt2_err_neon[i], pt2_err_kripton[i], pt2_err_xenon[i] };
    float yval2[4] = { rm_neon[i], rm_kripton[i], rm_xenon[i] };
    float yerr2[4] = { rm_err_neon[i], rm_err_kripton[i], rm_err_xenon[i] };
    // data[i].first = new TGraphErrors(3,xval,yval1,xerr,yerr1);
    data[i].first->GetYaxis()->SetRangeUser(-0.028, 0.049);
    data[i].first->GetYaxis()->SetNdivisions(505);
    // data[i].second = new TGraphErrors(3,xval,yval2,xerr,yerr2);
    data[i].second->GetYaxis()->SetRangeUser(0.01, 1.199);
    data[i].second->GetYaxis()->SetNdivisions(505);
    data[i].first->GetYaxis()->SetTitle("#Delta #LT #it{p}_{T}^{2} #GT (GeV^{2})");
    data[i].first->GetYaxis()->SetTitle("#Delta #it{p}_{T}^{2} (GeV^{2})");
    data[i].first->GetXaxis()->SetTitle("#it{A}^{1/3}");
    data[i].second->GetYaxis()->SetTitle("#it{R}_{M}");
    data[i].second->GetXaxis()->SetTitle("#it{A}^{1/3}");

    data[i].first->GetXaxis()->CenterTitle();
    data[i].first->GetYaxis()->CenterTitle();
    data[i].first->GetYaxis()->SetTitleOffset(2.8);
    data[i].second->GetXaxis()->CenterTitle();
    data[i].second->GetYaxis()->SetTitleOffset(2.8);
    data[i].second->GetXaxis()->SetTitleOffset(2);
    data[i].second->GetYaxis()->CenterTitle();

    data[i].first->SetMarkerStyle(20);
    data[i].second->SetMarkerStyle(21);
    // data[i].first->SetMarkerSize(7);
    // data[i].second->SetMarkerSize(7);
    data[i].first->GetXaxis()->SetLimits(2.50001, 5.4);
    data[i].second->GetXaxis()->SetLimits(2.50001, 5.4);
  }

  // gStyle->SetEndErrorSize(5);
  float small = 1e-5;
  ;
  float big = 0.25;
  TCanvas* c1 = new TCanvas("c1", "c1 title", 1000, 500);
  // c1->SetRightMargin(0.09);
  c1->SetLeftMargin(0.22);
  c1->SetBottomMargin(0.17);
  c1->Divide(4, 2, 0, 0);
  for (int i = 0; i < 4; ++i) {
    c1->cd(i + 1);
    data[i].first->Draw("AP");
    band[i].first->Draw("3SAME");
    tg[i].first->Draw("CLSAME");
    data[i].first->Draw("PSAME");
  }
  for (int i = 0; i < 4; ++i) {
    c1->cd(4 + i + 1);
    data[i].second->Draw("AP");
    band[i].second->Draw("3SAME");
    tg[i].second->Draw("CLSAME");
    data[i].second->Draw("PSAME");
  }
  c1->cd(1);
  myText(0.35, 0.9, 1, "#it{z} = 0.32", 22);
  c1->cd(2);
  myText(0.15, 0.9, 1, "#it{z} = 0.53", 22);
  c1->cd(3);
  myText(0.15, 0.9, 1, "#it{z} = 0.75", 22);
  c1->cd(4);
  myText(0.15, 0.9, 1, "#it{z} = 0.94", 22);

  c1->cd(1);
  TLegend* legend = new TLegend(0.38, 0.1, 0.65, 0.35);
  legend->SetBorderSize(0); // no border
  legend->SetFillStyle(0);
  legend->SetFillColor(0); // Legend background should be white
  legend->SetTextFont(43);
  legend->SetTextSize(22); // Increase entry font size!
  legend->AddEntry(data[0].first, "Data", "pe");
  legend->AddEntry(tg[0].first, Form("Fit result %s", variantname), "L");
  legend->Draw();
  c1->cd(5);
  TLegend* legend2 = new TLegend(0.38, 0.3, 0.65, 0.5);
  legend2->SetBorderSize(0); // no border
  legend2->SetFillStyle(0);
  legend2->SetFillColor(0); // Legend background should be white
  legend2->SetTextFont(43);
  legend2->SetTextSize(22); // Increase entry font size!
  legend2->AddEntry(data[0].second, "Data", "pe");
  legend2->AddEntry(tg[0].second, Form("Fit result %s", variantname), "L");
  legend2->Draw();

  // c1->SetGrayscale(kTRUE);
  c1->Print(Form("modelplot_%s.pdf", variantname));
}
