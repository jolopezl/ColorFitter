// Broadening results as a function of z:
//    D<pt^2>_He^pi+(GeV^2)  Value  Stat. error  Sys. uncertainty 
// z-bin# 1  -0.0005  0.0021  0.0009
// z-bin# 2  0.0004  0.0037  0.0021
// z-bin# 3  -0.0073  0.0076  0.0076
// z-bin# 4  -0.0094  0.0123  0.0110
//    D<pt^2>_Ne^pi+(GeV^2)  Value  Stat. error  Sys. uncertainty 
// z-bin# 1  0.0064  0.0013  0.0008
// z-bin# 2  0.0067  0.0022  0.0019
// z-bin# 3  -0.0088  0.0044  0.0069
// z-bin# 4  -0.0131  0.0073  0.0103
//    D<pt^2>_Kr^pi+(GeV^2)  Value  Stat. error  Sys. uncertainty 
// z-bin# 1  0.0205  0.0015  0.0011
// z-bin# 2  0.0228  0.0025  0.0023
// z-bin# 3  0.0012  0.0051  0.0066
// z-bin# 4  0.0021  0.0090  0.0095
//    D<pt^2>_Xe^pi+(GeV^2)  Value  Stat. error  Sys. uncertainty 
// z-bin# 1  0.0269  0.0019  0.0013
// z-bin# 2  0.0300  0.0033  0.0026
// z-bin# 3  0.0071  0.0067  0.0069
// z-bin# 4  -0.0021  0.0116  0.0082

void PlotMomentumBroadening() {
    SetAtlasStyle();

    TGraphErrors *tg_He = new TGraphErrors(4);
    TGraphErrors *tg_Ne = new TGraphErrors(4);
    TGraphErrors *tg_Kr = new TGraphErrors(4);
    TGraphErrors *tg_Xe = new TGraphErrors(4);

    TGraphErrors *tg_He_syst = new TGraphErrors(4);
    TGraphErrors *tg_Ne_syst = new TGraphErrors(4);
    TGraphErrors *tg_Kr_syst = new TGraphErrors(4);
    TGraphErrors *tg_Xe_syst = new TGraphErrors(4);
    
    tg_He->SetPoint(0,0.32,-0.0005);
    tg_He->SetPoint(1,0.54,0.0004);
    tg_He->SetPoint(2,0.75,-0.0073);
    tg_He->SetPoint(3,0.94,-0.0094);
    tg_He->SetPointError(0,0,0.0021);
    tg_He->SetPointError(1,0,0.0037);
    tg_He->SetPointError(2,0,0.0076);
    tg_He->SetPointError(3,0,0.0123);
    tg_He_syst->SetPoint(0,0.32,-0.0005);
    tg_He_syst->SetPoint(1,0.54,0.0004);
    tg_He_syst->SetPoint(2,0.75,-0.0073);
    tg_He_syst->SetPoint(3,0.94,-0.0094);
    tg_He_syst->SetPointError(0,0,0.0009);
    tg_He_syst->SetPointError(1,0,0.0021);
    tg_He_syst->SetPointError(2,0,0.0076);
    tg_He_syst->SetPointError(3,0,0.0110);

    tg_Ne->SetPoint(0,0.32,0.0064);
    tg_Ne->SetPoint(1,0.54,0.0067);
    tg_Ne->SetPoint(2,0.75,-0.0088);
    tg_Ne->SetPoint(3,0.94,-0.0131);
    tg_Ne->SetPointError(0,0,0.0013);
    tg_Ne->SetPointError(1,0,0.0022);
    tg_Ne->SetPointError(2,0,0.0044);
    tg_Ne->SetPointError(3,0,0.0073);
    tg_Ne_syst->SetPoint(0,0.32,0.0064);
    tg_Ne_syst->SetPoint(1,0.54,0.0067);
    tg_Ne_syst->SetPoint(2,0.75,-0.0088);
    tg_Ne_syst->SetPoint(3,0.94,-0.0131);
    tg_Ne_syst->SetPointError(0,0,0.0008);
    tg_Ne_syst->SetPointError(1,0,0.0019);
    tg_Ne_syst->SetPointError(2,0,0.0069);
    tg_Ne_syst->SetPointError(3,0,0.0103);

    tg_Kr->SetPoint(0,0.31,0.0205);
    tg_Kr->SetPoint(1,0.54,0.0228);
    tg_Kr->SetPoint(2,0.75,0.0012);
    tg_Kr->SetPoint(3,0.94,0.0021);
    tg_Kr->SetPointError(0,0,0.0015);
    tg_Kr->SetPointError(1,0,0.0025);
    tg_Kr->SetPointError(2,0,0.0051);
    tg_Kr->SetPointError(3,0,0.0090);
    tg_Kr_syst->SetPoint(0,0.31,0.0205);
    tg_Kr_syst->SetPoint(1,0.54,0.0228);
    tg_Kr_syst->SetPoint(2,0.75,0.0012);
    tg_Kr_syst->SetPoint(3,0.94,0.0021);
    tg_Kr_syst->SetPointError(0,0,0.0011);
    tg_Kr_syst->SetPointError(1,0,0.0023);
    tg_Kr_syst->SetPointError(2,0,0.0066);
    tg_Kr_syst->SetPointError(3,0,0.0095);

    tg_Xe->SetPoint(0,0.31,0.0269);
    tg_Xe->SetPoint(1,0.54,0.0300);
    tg_Xe->SetPoint(2,0.75,0.0071);
    tg_Xe->SetPoint(3,0.94,-0.0021);
    tg_Xe->SetPointError(0,0,0.0019);
    tg_Xe->SetPointError(1,0,0.0033);
    tg_Xe->SetPointError(2,0,0.0067);
    tg_Xe->SetPointError(3,0,0.0116);
    tg_Xe_syst->SetPoint(0,0.31,0.0269);
    tg_Xe_syst->SetPoint(1,0.54,0.0300);
    tg_Xe_syst->SetPoint(2,0.75,0.0071);
    tg_Xe_syst->SetPoint(3,0.94,-0.0021);
    tg_Xe_syst->SetPointError(0,0,0.0013);
    tg_Xe_syst->SetPointError(1,0,0.0026);
    tg_Xe_syst->SetPointError(2,0,0.0069);
    tg_Xe_syst->SetPointError(3,0,0.0082);

    // Add uncertainties
    const bool ADD_UNCERTAINTIES = true;
    if (ADD_UNCERTAINTIES) {
        double e1, e2;
        for (int i=0; i<4; ++i) {
            e1 = tg_He->GetEY()[i];
            e2 = tg_He_syst->GetEY()[i];
            tg_He_syst->GetEY()[i] = TMath::Sqrt(e1*e1 + e2*e2);
            e1 = tg_Ne->GetEY()[i];
            e2 = tg_Ne_syst->GetEY()[i];
            tg_Ne_syst->GetEY()[i] = TMath::Sqrt(e1*e1 + e2*e2);
            e1 = tg_Kr->GetEY()[i];
            e2 = tg_Kr_syst->GetEY()[i];
            tg_Kr_syst->GetEY()[i] = TMath::Sqrt(e1*e1 + e2*e2);
            e1 = tg_Xe->GetEY()[i];
            e2 = tg_Xe_syst->GetEY()[i];
            tg_Xe_syst->GetEY()[i] = TMath::Sqrt(e1*e1 + e2*e2);
        }
    }

    tg_He->SetMarkerColor(kOrange+10);
    tg_He_syst->SetMarkerColor(kOrange+10);
    tg_He->SetLineColor(kOrange+10);
    tg_He_syst->SetLineColor(kOrange+10);

    tg_Ne->SetMarkerColor(kBlack);
    tg_Ne_syst->SetMarkerColor(kBlack);
    tg_Ne->SetLineColor(kBlack);
    tg_Ne_syst->SetLineColor(kBlack);

    tg_Kr->SetMarkerColor(kRed+1);
    tg_Kr_syst->SetMarkerColor(kRed+1);
    tg_Kr->SetLineColor(kRed+1);
    tg_Kr_syst->SetLineColor(kRed+1);

    tg_Xe->SetMarkerColor(kAzure);
    tg_Xe_syst->SetMarkerColor(kAzure);
    tg_Xe->SetLineColor(kAzure);
    tg_Xe_syst->SetLineColor(kAzure);

    tg_He->SetMarkerStyle(kFullTriangleDown);
    tg_He_syst->SetMarkerStyle(kFullTriangleDown);
    tg_Ne->SetMarkerStyle(kFullCircle);
    tg_Ne_syst->SetMarkerStyle(kFullCircle);
    tg_Kr->SetMarkerStyle(kFullSquare);
    tg_Kr_syst->SetMarkerStyle(kFullSquare);
    tg_Xe->SetMarkerStyle(kFullTriangleUp);
    tg_Xe_syst->SetMarkerStyle(kFullTriangleUp);

    tg_He->SetLineWidth(2);
    tg_He_syst->SetLineWidth(2);
    tg_Ne->SetLineWidth(2);
    tg_Ne_syst->SetLineWidth(2);
    tg_Kr->SetLineWidth(2);
    tg_Kr_syst->SetLineWidth(2);
    tg_Xe->SetLineWidth(2);
    tg_Xe_syst->SetLineWidth(2);

    tg_He->SetMarkerSize(1.4);
    tg_He_syst->SetMarkerSize(1.4);
    tg_Ne->SetMarkerSize(1.4);
    tg_Ne_syst->SetMarkerSize(1.4);
    tg_Kr->SetMarkerSize(1.4);
    tg_Kr_syst->SetMarkerSize(1.4);
    tg_Xe->SetMarkerSize(1.4);
    tg_Xe_syst->SetMarkerSize(1.4);

    gStyle->SetEndErrorSize(7);
    TCanvas *c1 = new TCanvas("c1","c1 title",600,600);
    tg_Xe_syst->GetXaxis()->SetNdivisions(505);
    tg_Xe_syst->GetYaxis()->SetRangeUser(-0.03,0.04);
    tg_Xe_syst->GetXaxis()->SetLimits(0.1,1);
    tg_Xe_syst->GetYaxis()->SetTitle("#Delta p_{T}^{2} [GeV^{2}]");
    tg_Xe_syst->GetYaxis()->SetTitleOffset(1.6);
    tg_Xe_syst->GetXaxis()->SetTitle("z_{h}");
    tg_Xe_syst->Draw("APEZ");
    tg_Xe->Draw("||");
    tg_Kr_syst->Draw("PSAME Z");
    tg_Kr->Draw("||");
    tg_Ne_syst->Draw("PSAME Z");
    tg_Ne->Draw("||");
    // tg_He_syst->Draw("PSAME Z");
    // tg_He->Draw("||");
    // Extra pad for inset
    TLatex *text1 =  new TLatex();
    text1->SetNDC();
    text1->SetTextFont(62);
    text1->SetTextSize(0.03);
    text1->DrawLatex(0.18,0.9,"HERMES Collaboration, Phys. Lett. B 684 (2010) 114-118");
    // myText(0.2,0.9,kBlack,"HERMES Collaboration, Physics Letters B 684 (2010) 114-118",0.03);
    TLegend *ll = new TLegend(0.2,0.55,0.35,0.75);
    ll->SetBorderSize(0);  // no border
    ll->SetFillStyle(0);
    ll->SetFillColor(0);   // Legend background should be white
    // ll->SetTextFont(42);
    ll->SetTextSize(0.03); // Increase entry font size! 
    ll->AddEntry(tg_He,"He","pe");
    ll->AddEntry(tg_Ne,"Ne","pe");
    ll->AddEntry(tg_Kr,"Kr","pe");
    ll->AddEntry(tg_Xe,"Xe","pe");
    ll->Draw();
    c1->cd(1);
    double subpad_x0 = 0.25;
    double subpad_y0 = 0.17;
    double subpad_dx0 = 0.35;
    double subpad_dy0 = 0.35;
    TPad *subpad = new TPad("subpad","",subpad_x0,subpad_y0,subpad_x0+subpad_dx0,subpad_y0+subpad_dy0);
    // subpad->SetPadLeftMargin(0.13);
    subpad->SetFillStyle(4000);
    subpad->Draw();
    subpad->cd();
    tg_He_syst->GetYaxis()->SetLabelSize(0.07);
    tg_He_syst->GetYaxis()->SetNdivisions(505);
    tg_He_syst->GetXaxis()->SetLabelSize(0.07);
    tg_He_syst->GetXaxis()->SetNdivisions(505);
    tg_He_syst->GetYaxis()->SetRangeUser(-0.03,0.04);
    tg_He_syst->GetXaxis()->SetLimits(0.1,1);
    tg_He_syst->Draw("APEZ");
    tg_He->Draw("||");
    TLine *line = new TLine(0.1,0,1,0);
    line->Draw();

    c1->Print("Plot_HERMES_data_pT.pdf");


    for (int i=0; i<4; ++i) {
        cout << tg_Xe->GetX()[i] << "\t" << fabs(tg_Xe->GetEY()[i]/tg_Xe->GetY()[i] * 100) << " %" <<  endl;
    }

}
