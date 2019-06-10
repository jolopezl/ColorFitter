void monitoring()
{
  // TFile::Open("monitoring.root","OLD");
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat();
  gStyle->SetOptFit();

  TCanvas* c = new TCanvas();
  c->SetLogy();

  // PRODUCTION LENGTH
  TH1F* h1pl = new TH1F("h1pl", "Neon;L_{P}[fm];", 60, 0, 60);
  TH1F* h2pl = new TH1F("h2pl", "Krypton;L_{P}[fm];", 60, 0, 60);
  TH1F* h3pl = new TH1F("h3pl", "Xenon;L_{P}[fm];", 60, 0, 60);
  tree->Project("h1pl", "production_length", "nucleus==20  && zbin==3");
  tree->Project("h2pl", "production_length", "nucleus==83  && zbin==3");
  tree->Project("h3pl", "production_length", "nucleus==131 && zbin==3");
  h1pl->Fit("expo");
  h2pl->Fit("expo");
  h3pl->Fit("expo");
  h1pl->Draw();
  c->Print("adist_production_length_A020.pdf");
  h2pl->Draw();
  c->Print("adist_production_length_A083.pdf");
  h3pl->Draw();
  c->Print("adist_production_length_A131.pdf");

  // QUARK IN-MEDIUM PATH LENGTH
  TH1F* h1ppl = new TH1F("h1ppl", "Neon;L_{q}[fm];", 20, 0, 20);
  TH1F* h2ppl = new TH1F("h2ppl", "Krypton;L_{q}[fm];", 20, 0, 20);
  TH1F* h3ppl = new TH1F("h3ppl", "Xenon;L_{q}[fm];", 20, 0, 20);
  tree->Project("h1ppl", "parton_length", "nucleus==20  && zbin==3");
  tree->Project("h2ppl", "parton_length", "nucleus==83  && zbin==3");
  tree->Project("h3ppl", "parton_length", "nucleus==131 && zbin==3");
  h1ppl->Draw();
  c->Print("adist_parton_length_A020.pdf");
  h2ppl->Draw();
  c->Print("adist_parton_length_A083.pdf");
  h3ppl->Draw();
  c->Print("adist_parton_length_A131.pdf");

  // HADRON IN-MEDIUM PATH LENGTH
  TH1F* h1hl = new TH1F("h1hl", "Neon;L_{h}[fm];", 20, 0, 20);
  TH1F* h2hl = new TH1F("h2hl", "Krypton;L_{h}[fm];", 20, 0, 20);
  TH1F* h3hl = new TH1F("h3hl", "Xenon;L_{h}[fm];", 20, 0, 20);
  tree->Project("h1hl", "hadron_length", "nucleus==20  && zbin==3");
  tree->Project("h2hl", "hadron_length", "nucleus==83  && zbin==3");
  tree->Project("h3hl", "hadron_length", "nucleus==131 && zbin==3");
  // c->SetLogy();
  h1hl->Draw();
  c->Print("adist_hadron_length_A020.pdf");
  h2hl->Draw();
  c->Print("adist_hadron_length_A083.pdf");
  h3hl->Draw();
  c->Print("adist_hadron_length_A131.pdf");

  // gStyle->SetOptStat();
  // TCanvas* c3 = new TCanvas();
  // h1hl->SetFillColor(2);
  // h2hl->SetFillColor(3);
  // h3hl->SetFillColor(4);
  // h3hl->SetTitle("");
  // h3hl->Draw();
  // h2hl->Draw("SAME");
  // h1hl->Draw("SAME");
  // c3->Print("hadron_length_all.pdf");

  // CORRELATIONS
  TCanvas* c1 = new TCanvas();
  c1->cd();
  // c1->SetLogz();
  tree->Draw("hadron_length:parton_length", "zbin==3 && nucleus==20 && hadron_length > 0", "COLZ");
  c1->Print("corr_hadron_parton_A020.pdf");
  tree->Draw("hadron_length:parton_length", "zbin==3 && nucleus==83 && hadron_length > 0", "COLZ");
  c1->Print("corr_hadron_parton_A083.pdf");
  tree->Draw("hadron_length:parton_length", "zbin==3 && nucleus==131 && hadron_length > 0", "COLZ");
  c1->Print("corr_hadron_parton_A131.pdf");
  tree->Draw("xp:yp", "zbin==3 && nucleus==20", "COLZ");
  c1->Print("corr_xpyp_A020.pdf");
  tree->Draw("xp:yp", "zbin==3 && nucleus==83", "COLZ");
  c1->Print("corr_xpyp_A083.pdf");
  tree->Draw("xp:yp", "zbin==3 && nucleus==131", "COLZ");
  c1->Print("corr_xpyp_A131.pdf");
  tree->Draw("xp:zp", "zbin==3 && nucleus==20", "COLZ");
  c1->Print("corr_xpzp_A020.pdf");
  tree->Draw("xp:zp", "zbin==3 && nucleus==83", "COLZ");
  c1->Print("corr_xpzp_A083.pdf");
  tree->Draw("xp:zp", "zbin==3 && nucleus==131", "COLZ");
  c1->Print("corr_xpzp_A131.pdf");
  tree->Draw("yp:zp", "zbin==3 && nucleus==20", "COLZ");
  c1->Print("corr_ypzp_A020.pdf");
  tree->Draw("yp:zp", "zbin==3 && nucleus==83", "COLZ");
  c1->Print("corr_ypzp_A083.pdf");
  tree->Draw("yp:zp", "zbin==3 && nucleus==131", "COLZ");
  c1->Print("corr_ypzp_A131.pdf");
  // tree->Draw("parton_length:xp","zbin==3 && nucleus==20","COLZ");  c1->Print("corr_partonxp_A020.pdf");
  // tree->Draw("parton_length:xp","zbin==3 && nucleus==83","COLZ");  c1->Print("corr_partonxp_A083.pdf");
  // tree->Draw("parton_length:xp","zbin==3 && nucleus==131","COLZ"); c1->Print("corr_partonxp_A131.pdf");
  // tree->Draw("parton_length:yp","zbin==3 && nucleus==20","COLZ");  c1->Print("corr_partonyp_A020.pdf");
  // tree->Draw("parton_length:yp","zbin==3 && nucleus==83","COLZ");  c1->Print("corr_partonyp_A083.pdf");
  // tree->Draw("parton_length:yp","zbin==3 && nucleus==131","COLZ"); c1->Print("corr_partonyp_A131.pdf");
  tree->Draw("parton_length:zp", "zbin==3 && nucleus==20", "COLZ");
  c1->Print("corr_partonzp_A020.pdf");
  tree->Draw("parton_length:zp", "zbin==3 && nucleus==83", "COLZ");
  c1->Print("corr_partonzp_A083.pdf");
  tree->Draw("parton_length:zp", "zbin==3 && nucleus==131", "COLZ");
  c1->Print("corr_partonzp_A131.pdf");
  tree->Draw("parton_length:zp", "zbin==3 && nucleus==20 && hadron_length > 0", "COLZ");
  c1->Print("corr_partonzp_hl0_A020.pdf");
  tree->Draw("parton_length:zp", "zbin==3 && nucleus==83 && hadron_length > 0", "COLZ");
  c1->Print("corr_partonzp_hl0_A083.pdf");
  tree->Draw("parton_length:zp", "zbin==3 && nucleus==131 && hadron_length > 0", "COLZ");
  c1->Print("corr_partonzp_hl0_A131.pdf");
  // tree->Draw("hadron_length:xp","zbin==3 && nucleus==20 && hadron_length > 0","COLZ");  c1->Print("corr_hadronxp_A020.pdf");
  // tree->Draw("hadron_length:xp","zbin==3 && nucleus==83 && hadron_length > 0","COLZ");  c1->Print("corr_hadronxp_A083.pdf");
  // tree->Draw("hadron_length:xp","zbin==3 && nucleus==131 && hadron_length > 0","COLZ"); c1->Print("corr_hadronxp_A131.pdf");
  // tree->Draw("hadron_length:yp","zbin==3 && nucleus==20 && hadron_length > 0","COLZ");  c1->Print("corr_hadronyp_A020.pdf");
  // tree->Draw("hadron_length:yp","zbin==3 && nucleus==83 && hadron_length > 0","COLZ");  c1->Print("corr_hadronyp_A083.pdf");
  // tree->Draw("hadron_length:yp","zbin==3 && nucleus==131 && hadron_length > 0","COLZ"); c1->Print("corr_hadronyp_A131.pdf");
  tree->Draw("hadron_length:zp", "zbin==3 && nucleus==20", "COLZ");
  c1->Print("corr_hadronzp_A020.pdf");
  tree->Draw("hadron_length:zp", "zbin==3 && nucleus==83", "COLZ");
  c1->Print("corr_hadronzp_A083.pdf");
  tree->Draw("hadron_length:zp", "zbin==3 && nucleus==131", "COLZ");
  c1->Print("corr_hadronzp_A131.pdf");
  tree->Draw("hadron_length:zp", "zbin==3 && nucleus==20 && hadron_length > 0", "COLZ");
  c1->Print("corr_hadronzp_hl0_A020.pdf");
  tree->Draw("hadron_length:zp", "zbin==3 && nucleus==83 && hadron_length > 0", "COLZ");
  c1->Print("corr_hadronzp_hl0_A083.pdf");
  tree->Draw("hadron_length:zp", "zbin==3 && nucleus==131 && hadron_length > 0", "COLZ");
  c1->Print("corr_hadronzp_hl0_A131.pdf");
}