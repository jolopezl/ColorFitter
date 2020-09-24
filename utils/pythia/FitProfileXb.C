int FitProfileXb() {
    // SetAtlasStyle();
    TFile *fin = TFile::Open("Output.root", "READ");
    TProfile *prof = dynamic_cast<TProfile*>(fin->Get("prof"));
    TProfile *prof2 = dynamic_cast<TProfile*>(fin->Get("prof2"));

    prof->SetTitle(";#it{#nu} (GeV);#it{x}_{B}");
    prof->GetYaxis()->CenterTitle();
    prof->GetXaxis()->CenterTitle();

    TF1 *fcn = new TF1("fcn", "([0]+[1]*x+[2]*pow(x,2)) + exp([3]+[4]*x)", 1, 100);
    fcn->SetParameter(0,  1.08904e-01);
    fcn->SetParameter(1, -1.26225e-03);
    fcn->SetParameter(2,  5.35460e-06);
    fcn->SetParameter(3, -1.40235e+00);
    fcn->SetParameter(4, -1.25454e-01);

    TCanvas *c = new TCanvas("c","c title",600,600);
    prof2->Fit(fcn);
    prof2->Draw();
    // prof2->Draw("*SAME");

    c->SetLogy();
    return 0;
}
