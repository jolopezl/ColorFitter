void compPythiaDSS()
{
  TTree* tree = new TTree("tree", "tree");
  tree->ReadFile("pythia_run_output.txt", "ZH:XB:Q2:NU:W2");

  TFile fdss("esteban/d3sigma.root", "READ");
  auto dss = (TGraph*)fdss.Get("Graph");

  TH1F* h1 = new TH1F("h1", ";z_{h};d#sigma/dz_{h}", 36, 0.1, 1);
  tree->Project("h1", "ZH", "Q2>1 && W2>10 && NU/27.6 < 0.85");

  TH1* h2 = new TH1F("h2", ";z_{h};d#sigma/dz_{h}", 36, 0.1, 1);
  for (int i = 1; i <= 100; i++) {
    h2->SetBinContent(i, dss->Eval(h2->GetBinCenter(i)));
    h2->SetBinError(i, 0);
  }

  h1->Scale(1 / h1->Integral());
  h2->Scale(1 / h2->Integral());

  h2->SetLineColor(kRed);
  h1->GetYaxis()->SetTitle("Normalized counts");
  h1->GetYaxis()->SetTitleOffset(2);
  h1->GetYaxis()->SetRangeUser(0.00011, 9);
  h1->GetXaxis()->SetRangeUser(0.1, 1);
  h2->GetXaxis()->SetRangeUser(0.1, 1);

  auto tg1 = TH1TOTGraph(h1);
  auto tg2 = TH1TOTGraph(h2);
  tg2->SetLineColor(kRed);
  tg1->GetYaxis()->SetTitle("Normalized counts");
  tg1->GetYaxis()->SetTitleOffset(2);
  tg1->GetXaxis()->SetLimits(0.1, 1);
  tg2->GetXaxis()->SetLimits(0.1, 1);

  TCanvas* cnvrp = new TCanvas("cnvrp", "example", 600, 600);
  cnvrp->SetFillColor(0);
  cnvrp->SetFrameFillStyle(0);
  TPad* pad1 = new TPad("pad1", "pad1", 0, 0.4, 1, 1);
  pad1->SetBottomMargin(0);
  pad1->Draw();
  pad1->cd();
  // Draw plots here
  h1->DrawNormalized("HIST");
  h2->DrawNormalized("SAME");
  // tg1->Draw("APE");
  // tg2->Draw("PSAME");
  pad1->SetLogy();

  TLegend* leg = new TLegend(0.2, 0.7, 0.35, 0.92);
  leg->SetTextFont(43);
  leg->SetTextSize(20);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->AddEntry(h1, "Pythia6 w/HERMES cuts (untuned)", "l");
  leg->AddEntry(h2, "DSS (by E. Molina)", "l");
  leg->Draw();

  cnvrp->cd();
  TPad* pad2 = new TPad("pad2", "pad2", 0, 0, 1, 0.4);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();
  // Draw ratio
  auto rp = myTGraphErrorsDivide(TH1TOTGraph(h1), TH1TOTGraph(h2));
  rp->SetTitle(";z_{h};Pythia/DSS");
  rp->GetYaxis()->SetTitleOffset(2);
  rp->GetXaxis()->SetTitleOffset(3);
  rp->GetYaxis()->SetRangeUser(0.01, 1.99);
  rp->GetXaxis()->SetLimits(0.1, 1);
  rp->GetYaxis()->SetNdivisions(505);
  rp->SetMarkerStyle(kCross);
  rp->Draw("APE");
  TLine* l = new TLine(0.1, 1, 1, 1);
  l->SetLineStyle(kDashed);
  l->Draw("SAME");
  cnvrp->Print("plot_ratios.pdf");
}
