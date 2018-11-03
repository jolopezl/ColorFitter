int ReadTextToTree() {
    SetAtlasStyle();

    TFile *ff = TFile::Open("Output.root","RECREATE");
    TTree *tree = new TTree("tree","Q2, nu, xB tree");
    // tree->ReadFile("values_Q2nu.dat","Q2:NU:XB");
    // TH2F *hQ2NU_full = new TH2F("hQ2NU_full",";#nu (GeV);#it{Q}^{2} (GeV^{2})",100,0,100,100,1,30);
    // TH2F *hQ2NU_cut = new TH2F("hQ2NU_cut",";#nu (GeV);#it{Q}^{2} (GeV^{2})",100,0,100,100,1,30);
    // tree->Project("hQ2NU_full","Q2:NU");
    // tree->Project("hQ2NU_cut","Q2:NU","XB < 0.11 && XB > 0.095");
    // TCanvas *c1 = new TCanvas("c1", "c1 title",1200,600);
    // c1->Divide(2,1);
    // c1->cd(1);
    // hQ2NU_full->Draw("COL");
    // c1->cd(2);
    // hQ2NU_cut->Draw("COL");
    // myText(0.3, 0.8, kBlack, "0.095 < #it{x}_{Bj} < 0.11",0.05);

    tree->ReadFile("values_pion.dat","ZE:ZL");
    TH1F *hZE = new TH1F("hZE",";z;evts",30,0,1.5);
    TH1F *hZL = new TH1F("hZL",";z;evts",30,0,1.5);
    tree->Project("hZE","ZE");
    tree->Project("hZL","ZL");
    hZE->SetLineColor(kBlack);
    hZL->SetLineColor(kRed);
    TCanvas *c1 = new TCanvas("c1","title",800,600);
    hZL->Draw();
    hZE->Draw("SAME");
    c1->SetLogy();
    return 0;
}
