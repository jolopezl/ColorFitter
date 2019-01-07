int ReadTextToTree() {

    TFile *ff = TFile::Open("Output.root","RECREATE");
/*
    TTree *tree = new TTree("tree","Q2, nu, xB, W2 tree");
    tree->ReadFile("values_Q2nu.dat","Q2:NU:XB:W2");
    TH2F *hQ2NU_full = new TH2F("hQ2NU_full",";#nu (GeV);#it{Q}^{2} (GeV^{2})",100,0,100,100,1,30);
    TH2F *hQ2NU_cut = new TH2F("hQ2NU_cut",";#nu (GeV);#it{Q}^{2} (GeV^{2})",100,0,100,100,1,30);
    tree->Project("hQ2NU_full","Q2:NU");
    tree->Project("hQ2NU_cut","Q2:NU","XB < 0.11 && XB > 0.095");
    // TCanvas *c1 = new TCanvas("c1", "c1 title",1200,600);
    // c1->Divide(2,1);
    // c1->cd(1);
    // hQ2NU_full->Draw("COL");
    // c1->cd(2);
    // hQ2NU_cut->Draw("COL");
    // myText(0.3, 0.8, kBlack, "0.095 < #it{x}_{Bj} < 0.11",0.05);

    TProfile *prof = new TProfile("prof",";#it{#nu} (GeV);#it{x}_{B}",121,0,120);
    TProfile *prof2 = new TProfile("prof2",";#it{#nu} (GeV);#it{x}_{B}",121,0,120);
    tree->Draw("XB:NU>>prof","","PROF");
    tree->Draw("XB:NU>>prof2","W2>2","PROF");

    prof->Write();
    prof2->Write();
*/

    TTree *tree2 = new TTree("tree2","tree2");
    tree2->ReadFile("values_pion.dat","ZH:ZL:XB:Q2:NU");
    // TH1F *hZE = new TH1F("hZE",";z;evts",30,0,1.5);
    // TH1F *hZL = new TH1F("hZL",";z;evts",30,0,1.5);
    // TProfile *prof_L0 = new TProfile("prof_L0",";#it{#nu} (GeV);#it{L} (fm)",121,0,120);
    // tree2->Draw("L0:NU>>prof_L0","","PROF");

//    double zbin[ZDIM]      = {0.31, 0.54, 0.75, 0.94}; // pi+
//    double zbinw[ZDIM]     = {0.20,0.22,0.22,0.16}; // Approx.

    const int kNBINS = 5;
    const double kBINS[kNBINS+1] = {0, 0.185, 0.435, 0.645, 0.855, 0.9825};
    TH1D *hMultiplicity = new TH1D("hMultiplicity", ";z_{h};Events",kNBINS,kBINS);

    tree2->Project("hMultiplicity", "ZH");

    hMultiplicity->Draw();

    for (int i=1; i<=kNBINS; ++i) {
        cout << Form("N(%d) = ",i) << hMultiplicity->GetBinContent(i) << endl;
    }
    for (int i=1; i<kNBINS; ++i) {
        cout << Form("N(%d)/N(%d) = ",i+1,i) << hMultiplicity->GetBinContent(i+1)/hMultiplicity->GetBinContent(i) << endl;
    }

    // prof_L0->Write();
    // tree->Project("hZE","ZE");
    // tree->Project("hZL","ZL");
    // hZE->SetLineColor(kBlack);
    // hZL->SetLineColor(kRed);
    // TCanvas *c1 = new TCanvas("c1","title",800,600);
    // hZL->Draw();
    // hZE->Draw("SAME");
    // c1->SetLogy();
    return 0;
}
