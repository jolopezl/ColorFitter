void plot()
{
  // read the input data
  auto fref = TFile::Open("OutputROOT.20200707.BL30_piplus.root");
  auto tg_lp_ref = (TGraphErrors*)fref->Get("tg_lp");
  auto f = TFile::Open("OutputROOT.20200804.BL30NN_piplus.root");
  auto tg_lp = (TGraphErrors*)f->Get("tg_lp");
  auto tg_c1 = (TGraphErrors*)f->Get("tg_c1");
  auto tg_c2 = (TGraphErrors*)f->Get("tg_c2");
  // setup the plot
  double A[4] = { 4.0026, 20.1797, 83.7980, 131.2930 };
  std::vector<TGraphErrors*> tg;
  for (int i = 0; i < 4; ++i) {
    tg.push_back(new TGraphErrors(4));
    for (int j = 0; j < 4; ++j) {
      double x = 0;
      double yval = 0;
      double yerr = 0;
      x = tg_lp->GetX()[j];
      yval = tg_lp->GetY()[j];
      yval += tg_c1->GetY()[j] * std::pow(A[i], 1. / 3.);
      yval += tg_c2->GetY()[j] * std::pow(A[i], 2. / 3.);
      yerr += std::pow(tg_lp->GetEY()[j], 2);
      yerr += std::pow(tg_c1->GetEY()[j] * std::pow(A[i], 1. / 3.), 2);
      yerr += std::pow(tg_c2->GetEY()[j] * std::pow(A[i], 2. / 3.), 2);
      yerr += 2 * std::pow(A[i], 1. / 3.) * tg_lp->GetEY()[j] * tg_c1->GetEY()[j] * (-0.950);
      yerr += 2 * std::pow(A[i], 2. / 3.) * tg_lp->GetEY()[j] * tg_c2->GetEY()[j] * (0.6);
      yerr += 2 * std::pow(A[i], 1. / 3.) * std::pow(A[i], 2. / 3.) * tg_c1->GetEY()[j] * tg_c2->GetEY()[j] * (-0.950);
      yerr = std::sqrt(yerr);
      tg[i]->SetPoint(j, x, yval);
      tg[i]->SetPointError(j, 0, yerr);
      std::cout << i << ", point " << j << ", x = " << x << ", y = " << yval << ", yerr = " << yerr << std::endl;
    }
  }

  int colors[4] = { kAzure, kViolet, kPink, kOrange };
  for (int i = 0; i < 4; ++i) {
    tg[i]->SetMarkerStyle(i + 21);
    tg[i]->SetMarkerColor(colors[i]);
    tg[i]->SetLineColor(colors[i]);
    tg[i]->SetLineWidth(2);
  }

  tg_lp_ref->SetTitle(";z_{h};L_{c} (fm)");
  tg_lp_ref->SetLineWidth(2);
  // tg_lp_ref->GetYaxis()->SetRangeUser(0.001, 15);
  tg_lp_ref->GetXaxis()->SetLimits(0, 1);
  tg_lp_ref->GetXaxis()->SetNdivisions(505);

  // TCanvas* cnv_lc = new TCanvas("cnv_lc", "cnv_lc", 800, 600);
  TCanvas* cnvrp = new TCanvas("cnvrp", "example", 600, 600);
  cnvrp->SetFillColor(0);
  cnvrp->SetFrameFillStyle(0);
  TPad* pad1 = new TPad("pad1", "pad1", 0, 0.4, 1, 1);
  pad1->SetBottomMargin(0);
  pad1->Draw();
  pad1->cd();
  // Draw plots here
  tg_lp_ref->Draw("APEL");
  tg[0]->Draw("PLSAME");
  tg[1]->Draw("PLSAME");
  tg[2]->Draw("PLSAME");
  tg[3]->Draw("PLSAME");
  tg_lp_ref->Draw("PSAME");

  TLegend* leg = new TLegend(0.2, 0.6, 0.35, 0.92);
  leg->SetTextFont(43);
  leg->SetTextSize(20);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->AddEntry(tg_lp_ref, "L_{c} - Baseline model", "pel");
  leg->AddEntry(tg[0], "L_{c}(He)", "pel");
  leg->AddEntry(tg[1], "L_{c}(Ne)", "pel");
  leg->AddEntry(tg[2], "L_{c}(Kr)", "pel");
  leg->AddEntry(tg[3], "L_{c}(Xe)", "pel");
  leg->Draw();

  // ATLASLabel(0.2, 0.85, "Internal");
  // myMarkerText(0.3, 0.3, g_two_subevent_resolution->GetMarkerColor(), g_two_subevent_resolution->GetMarkerStyle(), "2-subevent method", 1.25, 22);
  // myMarkerText(0.3, 0.24, g_three_subevent_resolution_AP->GetMarkerColor(), g_three_subevent_resolution_AP->GetMarkerStyle(), "3-subevent method for FCal in side A", 1.25, 22);
  // myMarkerText(0.3, 0.18, g_three_subevent_resolution_AN->GetMarkerColor(), g_three_subevent_resolution_AN->GetMarkerStyle(), "3-subevent method for FCal in side C", 1.25, 22);

  cnvrp->cd();
  TPad* pad2 = new TPad("pad2", "pad2", 0, 0, 1, 0.4);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();
  // Draw ratio
  TGraphErrors* rps[4];
  for (int i = 0; i < 4; i++) {
    rps[i] = myTGraphErrorsDivide(tg[i], tg_lp_ref);
    // for (int p = 0; p < 4; p++)
    //   rps[i]->GetEY()[p] = 0;
    rps[i]->SetMarkerStyle(tg[i]->GetMarkerStyle());
    rps[i]->SetMarkerColor(tg[i]->GetMarkerColor());
    rps[i]->SetLineColor(tg[i]->GetLineColor());
  }
  rps[0]->GetYaxis()->SetTitle("L_{c}(A^{1/3})/L_{c}");
  rps[0]->GetXaxis()->SetTitle("z_{h}");
  rps[0]->GetXaxis()->SetTitleOffset(3);
  // rps[0]->GetYaxis()->SetRangeUser(0.96, 1.14);
  rps[0]->GetYaxis()->SetNdivisions(505);
  rps[0]->GetXaxis()->SetLimits(0, 1);
  rps[0]->GetXaxis()->SetNdivisions(505);
  rps[0]->Draw("APEL");
  rps[1]->Draw("PLSAME");
  rps[2]->Draw("PLSAME");
  rps[3]->Draw("PLSAME");
  TLine* l = new TLine(0, 1, 1, 1);
  l->SetLineStyle(kDashed);
  l->Draw("SAME");
  cnvrp->Print("plot_ratios.pdf");
}