TFile *fout;

void analysis(int,int);

void simple() {
    fout = TFile::Open("OutputROOT_ToyMC_ModelUncertianties.root","RECREATE");
    analysis(1,1);
    analysis(1,2);
    analysis(1,3);
    analysis(1,4);
    analysis(2,1);
    analysis(2,2);
    analysis(2,3);
    analysis(2,4);
    fout->Close();
}

void analysis(int opt=1, int zbin=1) {
    TH1::SetDefaultSumw2();
    SetAtlasStyle();

    TFile *data = TFile::Open("OutputROOT.BL30-Nominal.root","READ");
    TGraphErrors *tg_data = nullptr;
    TGraphErrors *tg_model = nullptr;
    TGraphErrors *tg_model_up = nullptr;
    TGraphErrors *tg_model_down = nullptr;
    if (opt == 1) {
        tg_data = (TGraphErrors*) data->Get(Form("tg_model_pT_%d",zbin-1));
        tg_model = (TGraphErrors*) data->Get(Form("tg_model_pT_extrapolation_%d",zbin-1));
        tg_model_up = (TGraphErrors*) data->Get(Form("tg_model_pT_extrapolation_up_%d",zbin-1));
        tg_model_down = (TGraphErrors*) data->Get(Form("tg_model_pT_extrapolation_down_%d",zbin-1));
    }
    else {
        tg_data = (TGraphErrors*) data->Get(Form("tg_model_Rm_%d",zbin-1));
        tg_model = (TGraphErrors*) data->Get(Form("tg_model_Rm_extrapolation_%d",zbin-1));
        tg_model_up = (TGraphErrors*) data->Get(Form("tg_model_Rm_extrapolation_up_%d",zbin-1));
        tg_model_down = (TGraphErrors*) data->Get(Form("tg_model_Rm_extrapolation_down_%d",zbin-1));
    }

    tg_model->SetLineColor(kCyan);
    tg_model_up->SetLineColor(kCyan); tg_model_up->SetLineStyle(kDashed);
    tg_model_down->SetLineColor(kCyan); tg_model_down->SetLineStyle(kDashed);
    auto model_band = myMakeBand(tg_model, tg_model_up, tg_model_down);
    model_band->SetFillColorAlpha(kOrange,0.5);

    TFile *toymc = TFile::Open("ToyMC_FullSimUI.root","READ");
    auto tree = (TTree*) toymc->Get("tree");

    int nbins = 20;
    double lim_lo = 2.45;
    double lim_hi = 6.05;

    TCut selection = Form("zbin == %d && StatusCode == 0",zbin);
    TProfile *pfx;
    TH2F *hist;
    
    if (opt == 1) {
        pfx = new TProfile("pfx",";A^{1/3};Profile of p_{T}^{2}",nbins,lim_lo,lim_hi);
        hist = new TH2F("hist","p_{T}^{2} vs A^{1/3;A^{1/3};p_{T}^{2} [GeV^{2}]",nbins,lim_lo,lim_hi,250,-0.03,0.05);
        tree->Project("pfx","PT2:A13",selection,"PROF");
        tree->Project("hist","PT2:A13",selection);
    }
    else {
        pfx = new TProfile("pfx",";A^{1/3};Profile of R_{M}",nbins,lim_lo,lim_hi);
        hist = new TH2F("hist","R_{M} vs A^{1/3};A^{1/3};R_{M}",nbins,lim_lo,lim_hi,250,0.3,1.1);
        tree->Project("pfx","RM:A13", selection,"PROF");
        tree->Project("hist","RM:A13", selection);
    }
    pfx->SetMarkerStyle(kStar);

    TF1 *func = new TF1("func","gaus",-1,2); func->SetLineColor(kRed);
    TF1 *func_left = new TF1("func_left","gaus",0,0.05);
    TF1 *func_right = new TF1("func_right","gaus",0,0.05);
    TF1 *total = new TF1("total","gaus(0)+gaus(3)",0,0.05);

    double cut_lo, cut_hi;
    // TH1F *temp = new TH1F("temp",";p_{T}^{2} [GeV^{2}];Entries",100,0,0.05);
    
    TH1F *h_distributions[nbins];
    double xloerr[nbins];
    double xhierr[nbins];
    double xcent[nbins];

    TH1F *h_distributions_aux = nullptr;
    if (opt==1) {h_distributions_aux = new TH1F("h_distributions_aux",";R_{M};Entries",50,0.4,1.1);}
    else {h_distributions_aux = new TH1F("h_distributions_aux",";p_{T}^2 [GeV^{2}];Entries",50,-0.05,0.05);}
    
    TCanvas *c0 = new TCanvas("c0","c0 title",1200,1200);
    c0->Divide(4,4,0,0);
    for (int i=0; i < nbins; ++i) {
        c0->cd(i+1);
        auto help = c0->cd(i+1)->DrawFrame(1,0.4,129,1);
        int abin=i+1;
        cut_lo = hist->GetXaxis()->GetBinLowEdge(abin);
        cut_hi = hist->GetXaxis()->GetBinUpEdge(abin);

        if (opt==1) {tree->Project("h_distributions_aux","PT2", Form("A13 > %f && A13 < %f && zbin==%d && StatusCode == 0", cut_lo, cut_hi, zbin));}
        else {tree->Project("h_distributions_aux","RM", Form("A13 > %f && A13 < %f && zbin==%d && StatusCode == 0", cut_lo, cut_hi, zbin));}

        double h_lo = h_distributions_aux->GetMean() - 3.5*h_distributions_aux->GetRMS();
        double h_hi = h_distributions_aux->GetMean() + 3.5*h_distributions_aux->GetRMS();

        const char* hist_name = Form("h_distributions_zbin%d_A_%d",zbin,abin);
        if (opt==1) {h_distributions[i] = new TH1F(hist_name,";R_{M};Entries",50,h_lo,h_hi);}
        else {h_distributions[i] = new TH1F(hist_name,";p_{T}^{2} [GeV^{2}];Entries",50,h_lo,h_hi);}
        if (opt==1) {tree->Project(hist_name,"PT2", Form("A13 > %f && A13 < %f && zbin==%d && StatusCode == 0", cut_lo, cut_hi, zbin));}
        else {tree->Project(hist_name,"RM", Form("A13 > %f && A13 < %f && zbin==%d && StatusCode == 0", cut_lo, cut_hi, zbin));}

        TH1F *temp = h_distributions[i];
        temp->Scale(100/temp->Integral());
        temp->GetYaxis()->SetTitle("100/Entries");
        temp->SetLineWidth(1);
        temp->SetMinimum(0.01);
        temp->SetMaximum(9.9);
        // temp->GetXaxis()->SetLimits(0.411,0.99);
        temp->GetYaxis()->SetTitleOffset(4);
        temp->GetXaxis()->SetTitleOffset(4);
        temp->Draw();

        /* find first non-empty bin */
        double xmin = 0, xmax = 0;
        for (int ib=1; ib < 101; ++ib) {if (temp->GetBinContent(ib) != 0) {xmin = temp->GetBinCenter(ib); break;}}
        for (int ib=100; ib > 0; --ib) {if (temp->GetBinContent(ib) != 0) {xmax = temp->GetBinCenter(ib); break;}}

        xmin = temp->GetMean() - 2*temp->GetRMS();
        xmax = temp->GetMean() + 2*temp->GetRMS();

        temp->Fit("func","Q","",xmin,xmax);
        // temp->Fit("func","Q");
        xloerr[i] = pfx->GetBinContent(abin) + func->GetParameter(2);
        xhierr[i] = pfx->GetBinContent(abin) - func->GetParameter(2);
        xcent[i] = hist->GetXaxis()->GetBinCenter(abin);
        myText(0.2,0.7,kBlack,Form("#splitline{#splitline{Gaussian fit}{mean = %.3f}}{#splitline{sigma = %.3f}{#chi^{2}/ndf = %.1f/%d}}",
            func->GetParameter(1),func->GetParameter(2),func->GetChisquare(),func->GetNDF()),16);
        myText(0.7,0.7,kBlack,Form("#splitline{Histogram}{#splitline{mean = %.3f}{RMS = %.3f}}",temp->GetMean(),temp->GetRMS()),16);
    }
    c0->Print(Form("hist_temp_zbin%d.pdf",zbin));

    TGraph *tg_model_toy_uncertainty_up = new TGraph(nbins,xcent,xhierr);
    TGraph *tg_model_toy_uncertainty_down = new TGraph(nbins,xcent,xloerr);
    tg_model_toy_uncertainty_up->SetLineColor(kMagenta);
    tg_model_toy_uncertainty_down->SetLineColor(kMagenta);
    // tg_model_toy_uncertainty_up->SetLineWidth(1);
    // tg_model_toy_uncertainty_down->SetLineWidth(1);

    TCanvas *c1 = new TCanvas("c1","c1 title",600,450);
    TH1 *h1 = nullptr;
    if (opt==1) {
        h1 = c1->DrawFrame(lim_lo,-0.03,lim_hi,0.05);
        h1->SetTitle(";A^{1/3};P_{T}^{2}");
    }
    else {
        h1 = c1->DrawFrame(lim_lo,0.3,lim_hi,1.1);
        h1->SetTitle(";A^{1/3};R_{M}");
    }
    hist->Draw("COL SAME");
    // pfx->Draw("SAME");
    // model_band->Draw("3SAME");
    tg_model->Draw("SAME");
    // tg_model_up->Draw("SAME");
    // tg_model_down->Draw("SAME");
    tg_data->Draw("PSAME");
    tg_model_toy_uncertainty_up->Draw("LSAME");
    tg_model_toy_uncertainty_down->Draw("LSAME");
    TF1* ff_up = nullptr;
    TF1* ff_down = nullptr;
    if (opt == 1) {
        ff_up = new TF1("ff_up", "[0] + [1]*x + [2]*pow(x,2)", 2.5,6); ff_up->SetLineStyle(kDashed);
        ff_down = new TF1("ff_down", "[0] + [1]*x + [2]*pow(x,2)", 2.5,6); ff_down->SetLineStyle(kDashed);
    }
    else {
        ff_up = new TF1("ff_up", "[0]*TMath::Exp(-[1]*x)", 2.5,6); ff_up->SetLineStyle(kDashed);
        ff_down = new TF1("ff_down", "[0]*TMath::Exp(-[1]*x)", 2.5,6); ff_down->SetLineStyle(kDashed);
    }
    tg_model_toy_uncertainty_up->Fit("ff_up","","SAME");
    tg_model_toy_uncertainty_down->Fit("ff_down","","SAME");
    myText(0.2,0.9,kBlack,Form("z-bin #%d",zbin),22);
    c1->Print(Form("plot_result_zbin%d.pdf",zbin));

    TCanvas *c2 = new TCanvas("c2","c2 title",600,450);
    TH1 *h2 = nullptr;
    if (opt==1) {
        h2 = c2->DrawFrame(lim_lo,-0.03,lim_hi,0.05);
        h2->SetTitle(";A^{1/3};P_{T}^{2}");
    }
    else {
        h2 = c2->DrawFrame(lim_lo,0.3,lim_hi,1.1);
        h2->SetTitle(";A^{1/3};R_{M}");
    }
    tg_model->Draw("SAME");

    const int magic_number = 26;
    TGraphErrors *tg_model_toy_fitted_up = new TGraphErrors(magic_number);
    TGraphErrors *tg_model_toy_fitted_down = new TGraphErrors(magic_number);
    double *x = tg_model->GetX();
    for (int i=0; i<magic_number; ++i) {
        tg_model_toy_fitted_up->SetPoint(i, x[i], ff_up->Eval(x[i]));
        tg_model_toy_fitted_down->SetPoint(i, x[i], ff_down->Eval(x[i]));
    }
    auto band = myMakeBand(tg_model,tg_model_toy_fitted_up,tg_model_toy_fitted_down);
    band->SetFillColorAlpha(kOrange,0.5);
    band->Draw("3SAME");
    c2->Print(Form("plot_result_band_zbin%d.pdf",zbin));

    if (opt == 1) {
        tg_model_toy_fitted_up->SetName(Form("tg_model_toy_fitted_up_PT2_%d",zbin-1));
        tg_model_toy_fitted_down->SetName(Form("tg_model_toy_fitted_down_PT2_%d",zbin-1));
    }
    else {
        tg_model_toy_fitted_up->SetName(Form("tg_model_toy_fitted_up_RM_%d",zbin-1));
        tg_model_toy_fitted_down->SetName(Form("tg_model_toy_fitted_down_RM_%d",zbin-1));
    }
    fout->cd();
    tg_model_toy_fitted_up->Write();
    tg_model_toy_fitted_down->Write();
}
