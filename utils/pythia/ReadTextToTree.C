int ReadTextToTree() {
    TTree *tree = new TTree("tree","tree");
    tree->ReadFile("pythia_run_output.txt","ZH:XB:Q2:NU:W2");
    const int kNBINS = 5;
    const double kBINS[kNBINS+1] = {0, 0.2, 0.4, 0.6, 0.8, 1};
    TH1D *hist_dNdz = new TH1D("hist_dNdz", ";z_{h};Events",kNBINS,kBINS);
    tree->Project("hist_dNdz", "ZH", "Q2>1 && W2>10 && NU/27.6 < 0.85"); // Apply HERMES cuts on the fly
    hist_dNdz->Draw();
    for (int i=1; i<=kNBINS; ++i) {
        double b = hist_dNdz->GetBinContent(i);
        cout << Form("N(%d) = ",i) << b << endl;
    }
    for (int i=1; i<kNBINS; ++i) {
        double r = hist_dNdz->GetBinContent(i+1)/hist_dNdz->GetBinContent(i);
        cout << Form("N(%d)/N(%d) = ",i+1,i) << r << endl;
    }
    return 0;
}
