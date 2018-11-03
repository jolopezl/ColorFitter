void testLund() {
    SetAtlasStyle();
    TFile *fin = TFile::Open("OutputROOT.BL.root");
    auto model = (TGraphErrors*)fin->Get("tg_lp");
    
    TF1 *fg1 = nullptr;
    fg1 = new TF1("fg1","1/(2*[0]) * ((1-x)*([1] + 2*[2]) - TMath::Power([3],2)/(x*([1] + 2*[2])))",0,1);
    fg1->SetParName(0, "KAPPA");
    fg1->SetParName(1, "MP");
    fg1->SetParName(2, "NU");
    fg1->SetParName(3, "mT");
    fg1->SetParameter(0, 1);
    fg1->FixParameter(1, 0.938);
    fg1->FixParameter(2, 5.1036610);
    fg1->FixParameter(3, 0.14);
    // fg1->SetParLimits(3,0.09,0.2);

    const char* LundLogFull = "(([1]+2*[2])/(2*[0]))*x*(log(1/(x*x))-1+x*x)/(1-x*x)"; // Bialas paper 
    TF1* fg2 = new TF1("fg2", LundLogFull, 0, 1);
    fg2->SetParName(0,"KAPPA");
    fg2->SetParName(1,"MP");
    fg2->SetParName(2,"NU");
    fg2->SetParameter(0,1);
    fg2->FixParameter(1,0.938);
    fg2->FixParameter(2,5.1036610);

    int npoints = 500;
    model->Fit("fg1", "EMN0", "", 0.2, 0.96);
    TH1F *h1 = new TH1F("h1","auxs",npoints+1,0,1);
    auto gg1 = TH1TOTGraph(h1);
    TGraphErrors *grint1 = new TGraphErrors(99);
    grint1->SetTitle("Fitted line with .6827 conf. band");
    for (int i=0; i<npoints; i++)
        grint1->SetPoint(i, gg1->GetX()[i], 0);
    //Compute the confidence intervals at the x points of the created graph
    (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint1,0.6827);
    grint1->SetLineColor(kAzure);
    grint1->SetFillColorAlpha(kAzure,0.4);
    // gStyle->SetHatchesLineWidth(2);
    // gStyle->SetHatchesSpacing(1);
    // grint1->SetFillStyle(3365);
    cout << "Lund Log Full" << endl;
    model->Fit("fg2", "EMN0", "", 0.25, 0.95);
    cout << "END Lund Log Full" << endl;

    TH1F *h2 = new TH1F("h2","auxs",npoints+1,0,1);
    auto gg2 = TH1TOTGraph(h2);
    TGraphErrors *grint2 = new TGraphErrors(99);
    grint2->SetTitle("Fitted line with .6827 conf. band");
    for (int i=0; i<npoints; i++)
        grint2->SetPoint(i, gg2->GetX()[i], 0);
    //Compute the confidence intervals at the x points of the created graph
    (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint2,0.6827);
    grint2->SetLineColor(kRed);
    grint2->SetFillColorAlpha(kRed,0.4);
    // grint2->SetFillStyle(3356);

    grint1->SetLineWidth(2);
    grint2->SetLineWidth(2);

    fg1->SetLineWidth(2);
    fg2->SetLineWidth(2);
    fg1->SetLineColor(kAzure);
    fg2->SetLineColor(kRed);
    fg1->SetFillColorAlpha(kAzure,0.3);
    fg2->SetFillColorAlpha(kRed,0.3);

    model->SetMarkerSize(1.5);
    model->SetMarkerStyle(20);
    model->GetXaxis()->SetLimits(0.0,1.0);
    model->GetXaxis()->SetNdivisions(505);
    // model->GetYaxis()->SetRangeUser(0.0001,16);
    model->GetYaxis()->SetRangeUser(0.1,70);
    model->SetTitle(";z;L_{p} [fm]");

    TCanvas *c1 = new TCanvas("c1","plot of Lp",800,600);
    model->Draw("APE"); 
    // variants->Draw("SAME5");
    fg1->Draw("SAME");
    fg2->Draw("SAME");
    grint2->Draw("SAME 3");
    fg2->Draw("SAME");
    grint1->Draw("SAME 3");
    fg1->Draw("SAME");
    model->Draw("PSAME"); 


    TLegend* leg = new TLegend(0.2,0.75,0.35,0.92);
    // leg->SetNColumns(2);
    leg->SetTextFont(42);
    leg->SetTextSize(0.03);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    // leg->AddEntry(model,"BLE30","pe");
    // leg->AddEntry(grint2,Form("Bialas #it{et. al.}, #chi^{2}/dof = %.3f",fg2->GetChisquare()/fg2->GetNDF()),"fl");
    // leg->AddEntry(grint1,Form("Linear Form, #chi^{2}/dof = %.3f, #kappa = %.3f #pm %.3f GeV/fm",fg1->GetChisquare()/fg1->GetNDF(),fg1->GetParameter(2),fg1->GetParError(2)),"fl");
    // leg->AddEntry(grint1,Form("Linear Form, #chi^{2}/dof = %.2f, #kappa = %.1f #pm %.1f GeV/fm",fg1->GetChisquare()/fg1->GetNDF(),fg1->GetParameter(2),fg1->GetParError(2)),"fl");

    leg->AddEntry(grint1,Form("Lund String Model (struck quark), #chi^{2}/dof = %.2f, #kappa = %.2f #pm %.2f GeV/fm",fg1->GetChisquare()/fg1->GetNDF(),fg1->GetParameter(0),fg1->GetParError(0)),"fl");
    leg->AddEntry(grint2,Form("Bialas #it{et. al.}, #chi^{2}/dof = %.2f, #kappa = %.2f #pm %.2f GeV/fm",fg2->GetChisquare()/fg2->GetNDF(),fg2->GetParameter(0),fg2->GetParError(0)),"fl");

    // leg->AddEntry(grint1, "Lund String Model (struck quark)","fl");//   Form("Linear Form, #chi^{2}/dof = %.2f, #kappa = %.1f #pm %.1f GeV/fm",fg1->GetChisquare()/fg1->GetNDF(),fg1->GetParameter(0),fg1->GetParError(0)),"fl");
    // leg->AddEntry(grint2, "Bialas #it{et. al.}","fl");//Form("Bialas #it{et. al.}, #chi^{2}/dof = %.2f, #kappa = %.1f #pm %.1f GeV/fm",fg2->GetChisquare()/fg2->GetNDF(),fg2->GetParameter(1),fg2->GetParError(1)),"fl");
    leg->AddEntry(model,"BL JLab Data - 2 < Q^{2} < 2.5 GeV^{2}, 0.19 < X_{B} < 0.28","pe");

    leg->Draw();

    c1->SetLogy();
    c1->Print("testlund_jlab.pdf");
}
