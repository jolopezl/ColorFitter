TStyle* AtlasStyle()
{
  TStyle* atlasStyle = new TStyle("ATLAS", "Atlas style");

  // use plain black on white colors
  Int_t icol = 0; // WHITE
  atlasStyle->SetFrameBorderMode(icol);
  atlasStyle->SetFrameFillColor(icol);
  atlasStyle->SetCanvasBorderMode(icol);
  atlasStyle->SetCanvasColor(icol);
  atlasStyle->SetPadBorderMode(icol);
  atlasStyle->SetPadColor(icol);
  atlasStyle->SetStatColor(icol);
  //atlasStyle->SetFillColor(icol); // don't use: white fill color for *all* objects

  // set the paper & margin sizes
  atlasStyle->SetPaperSize(20, 26);

  // set margin sizes
  atlasStyle->SetPadTopMargin(0.05);
  atlasStyle->SetPadRightMargin(0.05);
  atlasStyle->SetPadBottomMargin(0.16);
  atlasStyle->SetPadLeftMargin(0.16);

  // set title offsets (for axis label)
  atlasStyle->SetTitleXOffset(1.4);
  atlasStyle->SetTitleYOffset(1.4);

  // use large fonts
  //Int_t font=72; // Helvetica italics
  Int_t font = 42; // Helvetica
  Double_t tsize = 0.07;
  atlasStyle->SetTextFont(font);

  atlasStyle->SetTextSize(tsize);
  atlasStyle->SetLabelFont(font, "x");
  atlasStyle->SetTitleFont(font, "x");
  atlasStyle->SetLabelFont(font, "y");
  atlasStyle->SetTitleFont(font, "y");
  atlasStyle->SetLabelFont(font, "z");
  atlasStyle->SetTitleFont(font, "z");

  atlasStyle->SetLabelSize(tsize, "x");
  atlasStyle->SetTitleSize(tsize, "x");
  atlasStyle->SetLabelSize(tsize, "y");
  atlasStyle->SetTitleSize(tsize, "y");
  atlasStyle->SetLabelSize(tsize, "z");
  atlasStyle->SetTitleSize(tsize, "z");

  // use bold lines and markers
  atlasStyle->SetMarkerStyle(20);
  atlasStyle->SetMarkerSize(1.2);
  atlasStyle->SetHistLineWidth(2.);
  atlasStyle->SetLineStyleString(2, "[12 12]"); // postscript dashes

  // get rid of X error bars
  //atlasStyle->SetErrorX(0.001);
  // get rid of error bar caps
  atlasStyle->SetEndErrorSize(0.);

  // do not display any of the standard histogram decorations
  atlasStyle->SetOptTitle(0);
  //atlasStyle->SetOptStat(1111);
  atlasStyle->SetOptStat(0);
  //atlasStyle->SetOptFit(1111);
  atlasStyle->SetOptFit(0);

  // put tick marks on top and RHS of plots
  atlasStyle->SetPadTickX(1);
  atlasStyle->SetPadTickY(1);

  return atlasStyle;
}

void SetAtlasStyle()
{
  static TStyle* atlasStyle = 0;
  std::cout << "\nApplying ATLAS style settings...\n"
            << std::endl;
  if (atlasStyle == 0)
    atlasStyle = AtlasStyle();
  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();
}

void myText(Double_t x, Double_t y, Color_t color, const char* text)
{

  Double_t tsize = 0.05;
  TLatex l; // l.SetTextAlign(12); l.SetTextSize(tsize);
  l.SetNDC();
  l.SetTextColor(color);
  l.DrawLatex(x, y, text);
}

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

float betagamma[4] = { 9.31, 8.40, 7.94, 7.05 };
float betagamma2norm = 8.40;

void makeFigure()
{
  gROOT->Reset();
  gROOT->ForceStyle();
  SetAtlasStyle();
  /** model lines **/
  string filename1[6][4];
  string filename2[6][4];
  string basename[6] = { "BL", "BLE", "BL40", "BL30", "BLE40", "BLE40" };
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 6; ++j) {
      filename1[j][i] = "testFit" + basename[j] + "_plot_pt_0_" + std::to_string(i) + ".txt";
      filename2[j][i] = "testFit" + basename[j] + "_plot_mr_0_" + std::to_string(i) + ".txt";
    }
  }

  TGraph* model_pt[6][4];
  TGraph* model_rm[6][4];
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 6; ++j) {
      model_pt[j][i] = new TGraph(filename1[j][i].c_str());
      model_rm[j][i] = new TGraph(filename2[j][i].c_str());
    }
  }
  /** data points **/
  TGraphErrors* data_pt[4];
  TGraphErrors* data_pt_normalized[4];
  TGraphErrors* data_rm[4];
  float xval[3] = { 2.9947753767563916, 4.813606330683598, 5.590790378970299 };
  float xerr[3] = { 0, 0, 0 };
  for (int i = 0; i < 4; ++i) {
    float yval[4] = { pt2_neon[i], pt2_kripton[i], pt2_xenon[i] };
    float yerr[4] = { pt2_err_neon[i], pt2_err_kripton[i], pt2_err_xenon[i] };
    data_pt[i] = new TGraphErrors(3, xval, yval, xerr, yerr);
    data_pt[i]->GetYaxis()->SetRangeUser(-0.035, 0.035);
    float yval2[4] = { rm_neon[i], rm_kripton[i], rm_xenon[i] };
    float yerr2[4] = { rm_err_neon[i], rm_err_kripton[i], rm_err_xenon[i] };
    data_rm[i] = new TGraphErrors(3, xval, yval2, xerr, yerr2);
    data_rm[i]->GetYaxis()->SetRangeUser(-0.035, 0.035);
    data_rm[i]->GetYaxis()->SetRangeUser(0.35, 1.05);

    float yval_normalized[3] = { 0., 0., 0. };
    for (int k = 0; k < 3; ++k) {
      yval_normalized[k] = yval[k] * betagamma[i] / betagamma2norm;
      std::cout << "y = " << yval[k] << " changed to y = " << yval_normalized[k] << std::endl;
    }
    data_pt_normalized[i] = new TGraphErrors(3, xval, yval_normalized, xerr, yerr);
    data_pt_normalized[i]->SetMarkerStyle(25);
  }
  /** color and labels **/
  int colors[6] = { 1, 2, 3, 4, 6, 9 };
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 6; ++j) {
      model_pt[j][i]->SetLineColor(colors[j]);
      model_pt[j][i]->SetLineWidth(2);
      model_rm[j][i]->SetLineColor(colors[j]);
      model_rm[j][i]->SetLineWidth(2);
    }
  }
  /** drawing **/

  data_pt[0]->GetYaxis()->SetTitle("#Delta #LT p_{t}^{2} #GT [GeV^{2}]");
  data_pt[0]->GetYaxis()->SetTitleOffset(1.75);
  data_pt[3]->GetXaxis()->SetTitle("A^{1/3}");
  data_pt[3]->GetXaxis()->SetTitleOffset(1.25);
  data_rm[0]->GetYaxis()->SetTitle("R_{m}");
  data_rm[0]->GetYaxis()->SetTitleOffset(1.75);
  data_rm[3]->GetXaxis()->SetTitle("A^{1/3}");
  data_rm[3]->GetXaxis()->SetTitleOffset(1.25);

  float small = 1e-5;
  ;
  float big = 0.25;
  /** MODELPLOT PT2 **/
  TCanvas* c1 = new TCanvas("c1", "c1 title", 800, 800);
  c1->Divide(2, 2, small, small);
  for (int i = 0; i < 4; ++i) {
    // pad[i]->cd();
    c1->cd(i + 1);
    if (i == 0) {
      gPad->SetBottomMargin(small);
      gPad->SetRightMargin(small);
      gPad->SetLeftMargin(big);
      gPad->SetTopMargin(big);
    } else if (i == 1) {
      gPad->SetTopMargin(big);
      gPad->SetBottomMargin(small);
      gPad->SetLeftMargin(small);
      gPad->SetRightMargin(big);
    } else if (i == 2) {
      gPad->SetBottomMargin(big);
      gPad->SetTopMargin(small);
      gPad->SetRightMargin(small);
      gPad->SetLeftMargin(big);
    } else if (i == 3) {
      gPad->SetBottomMargin(big);
      gPad->SetTopMargin(small);
      gPad->SetLeftMargin(small);
      gPad->SetRightMargin(big);
    }
    // if (i==0) data[i]->Draw();
    data_pt[i]->Draw("AP");
    data_pt_normalized[i]->Draw("PSAME");
    for (int j = 0; j < 6; ++j) {
      // if (j==3)
      // if (j == 0) model[j][i]->Draw();
      model_pt[j][i]->Draw("SAME");
    }
  }
  c1->cd(1);
  myText(0.3, 0.65, 1, "z-bin #1");
  c1->cd(2);
  myText(0.075, 0.65, 1, "z-bin #2");
  c1->cd(3);
  myText(0.3, 0.9, 1, "z-bin #3");
  c1->cd(4);
  myText(0.075, 0.9, 1, "z-bin #4");
  c1->cd(3);
  float x0 = 0.3;
  float y0 = 0.3;
  float x1 = x0 + 0.55;
  float y1 = y0 + 0.175;
  TLegend* leg = new TLegend(x0, y0, x1, y1);
  leg->SetNColumns(2);
  leg->SetTextFont(43);
  leg->SetTextSize(28);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  for (int i = 0; i < 6; ++i) {
    leg->AddEntry(model_pt[i][0], basename[i].c_str(), "cl");
  }
  leg->Draw();
  c1->Print("modelplot_pt.pdf");

  /** MODELPLOT RM **/
  TCanvas* c2 = new TCanvas("c2", "c2 title", 800, 800);
  c2->Divide(2, 2, small, small);
  for (int i = 0; i < 4; ++i) {
    // pad[i]->cd();
    c2->cd(i + 1);
    if (i == 0) {
      gPad->SetBottomMargin(small);
      gPad->SetRightMargin(small);
      gPad->SetLeftMargin(big);
      gPad->SetTopMargin(big);
    } else if (i == 1) {
      gPad->SetTopMargin(big);
      gPad->SetBottomMargin(small);
      gPad->SetLeftMargin(small);
      gPad->SetRightMargin(big);
    } else if (i == 2) {
      gPad->SetBottomMargin(big);
      gPad->SetTopMargin(small);
      gPad->SetRightMargin(small);
      gPad->SetLeftMargin(big);
    } else if (i == 3) {
      gPad->SetBottomMargin(big);
      gPad->SetTopMargin(small);
      gPad->SetLeftMargin(small);
      gPad->SetRightMargin(big);
    }
    // if (i==0) data[i]->Draw();
    data_rm[i]->Draw("AP");
    for (int j = 0; j < 6; ++j) {
      // if (j == 0) model[j][i]->Draw();
      model_rm[j][i]->Draw("SAME");
    }
  }
  c2->cd(1);
  myText(0.3, 0.65, 1, "z-bin #1");
  c2->cd(2);
  myText(0.075, 0.65, 1, "z-bin #2");
  c2->cd(3);
  myText(0.3, 0.9, 1, "z-bin #3");
  c2->cd(4);
  myText(0.075, 0.9, 1, "z-bin #4");
  c2->cd(3);
  // float x0 = 0.3;
  // float y0 = 0.3;
  // float x1 = x0 + 0.55;
  // float y1 = y0 + 0.175;
  // TLegend* leg = new TLegend(x0,y0,x1,y1);
  // leg->SetNColumns(2);
  // leg->SetTextFont(43);
  // leg->SetTextSize(28);
  // leg->SetBorderSize(0);
  // leg->SetFillStyle(0);
  // for (int i = 0; i < 6; ++i) {
  //     leg->AddEntry(model_rm[i][0],basename[i].c_str(),"cl");
  // }
  leg->Draw();
  c2->Print("modelplot_rm.pdf");
  std::cout << "Remember to cut margins with `pdfcrop --margins '10 10 10 10' input.pdf`" << std::endl;
}