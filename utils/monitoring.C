void monitoring() {
    // TFile::Open("monitoring.root","OLD");
    gROOT->SetStyle("Plain");
    gStyle->SetOptStat();
    gStyle->SetOptFit(); 

    TCanvas *c = new TCanvas();
    c->SetLogy();

    // PRODUCTION LENGTH
    TH1F* h1pl = new TH1F("h1pl","Neon;L_{P}[fm];",   60,0,60);
    TH1F* h2pl = new TH1F("h2pl","Krypton;L_{P}[fm];",60,0,60);
    TH1F* h3pl = new TH1F("h3pl","Xenon;L_{P}[fm];",  60,0,60);
    tree->Project("h1pl","production_length","nucleus==20  && zbin==3");
    tree->Project("h2pl","production_length","nucleus==83  && zbin==3");
    tree->Project("h3pl","production_length","nucleus==131 && zbin==3");
    h1pl->Fit("expo");
    h2pl->Fit("expo");
    h3pl->Fit("expo");
    h1pl->Draw(); c->Print("production_length_A20.pdf");
    h2pl->Draw(); c->Print("production_length_A83.pdf");
    h3pl->Draw(); c->Print("production_length_A131.pdf");

    // QUARK IN-MEDIUM PATH LENGTH
    TH1F* h1ppl = new TH1F("h1ppl","Neon;L_{h}[fm];",   20,0,20);
    TH1F* h2ppl = new TH1F("h2ppl","Krypton;L_{h}[fm];",20,0,20);
    TH1F* h3ppl = new TH1F("h3ppl","Xenon;L_{h}[fm];",  20,0,20);
    tree->Project("h1ppl","parton_length","nucleus==20  && zbin==3");
    tree->Project("h2ppl","parton_length","nucleus==83  && zbin==3");
    tree->Project("h3ppl","parton_length","nucleus==131 && zbin==3");
    h1ppl->Draw(); c->Print("parton_length_A20.pdf");
    h2ppl->Draw(); c->Print("parton_length_A83.pdf");
    h3ppl->Draw(); c->Print("parton_length_A131.pdf");

    // HADRON IN-MEDIUM PATH LENGTH
    TH1F* h1hl = new TH1F("h1hl","Neon;L_{h}[fm];",   20,0,20);
    TH1F* h2hl = new TH1F("h2hl","Krypton;L_{h}[fm];",20,0,20);
    TH1F* h3hl = new TH1F("h3hl","Xenon;L_{h}[fm];",  20,0,20);
    tree->Project("h1hl","hadron_length","nucleus==20  && zbin==3");
    tree->Project("h2hl","hadron_length","nucleus==83  && zbin==3");
    tree->Project("h3hl","hadron_length","nucleus==131 && zbin==3");
    // c->SetLogy();
    h1hl->Draw(); c->Print("hadron_length_A20.pdf");
    h2hl->Draw(); c->Print("hadron_length_A83.pdf");
    h3hl->Draw(); c->Print("hadron_length_A131.pdf");

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
    tree->Draw("hadron_length:parton_length","zbin==3 && nucleus==20 && hadron_length > 0","COLZ");
    c1->Print("hadron_parton_A20.pdf");
    tree->Draw("hadron_length:parton_length","zbin==3 && nucleus==83 && hadron_length > 0","COLZ");
    c1->Print("hadron_parton_A83.pdf");
    tree->Draw("hadron_length:parton_length","zbin==3 && nucleus==131 && hadron_length > 0","COLZ");
    c1->Print("hadron_parton_A131.pdf");
    tree->Draw("xp:yp","zbin==3 && nucleus==20","COLZ");
    c1->Print("xpyp_A20.pdf");
    tree->Draw("xp:yp","zbin==3 && nucleus==83","COLZ");
    c1->Print("xpyp_A83.pdf");
    tree->Draw("xp:yp","zbin==3 && nucleus==131","COLZ");
    c1->Print("xpyp_A131.pdf");
    tree->Draw("xp:zp","zbin==3 && nucleus==20","COLZ");
    c1->Print("xpzp_A20.pdf");
    tree->Draw("xp:zp","zbin==3 && nucleus==83","COLZ");
    c1->Print("xpzp_A83.pdf");
    tree->Draw("xp:zp","zbin==3 && nucleus==131","COLZ");
    c1->Print("xpzp_A131.pdf");
    tree->Draw("yp:zp","zbin==3 && nucleus==20","COLZ");
    c1->Print("ypzp_A20.pdf");
    tree->Draw("yp:zp","zbin==3 && nucleus==83","COLZ");
    c1->Print("ypzp_A83.pdf");
    tree->Draw("yp:zp","zbin==3 && nucleus==131","COLZ");
    c1->Print("ypzp_A131.pdf");
}