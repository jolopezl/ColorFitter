void plot () {

    SetAtlasStyle();

    double nu[8] = {4.00,7.00,4.00,9.00,32.50,37.50,140.00,150.00};
    double Q2[8] = {3.00,7.00,1.00,2.00,12.00,8.00,45.00,27.00};
    double bg[8] = {2.08,2.45,3.87,6.28,9.33,13.22,20.85,28.85};
    double zh[4] = {0.32, 0.53, 0.75, 0.94};

    double z00[8] = {1.92,2.26,3.57,5.79,8.59,12.17,19.20,26.57};
    double z01[8] = {1.58,1.86,2.95,4.78,7.10,10.06,15.86,21.96};
    double z02[8] = {1.21,1.43,2.26,3.66,5.44,7.71,12.15,16.82};
    double z03[8] = {0.71,0.83,1.32,2.14,3.18,4.50,7.10,9.82};

    double z10[8] = {3.69,6.67,3.25,6.69,23.64,26.39,99.19,103.67};
    double z11[8] = {2.85,5.20,2.41,4.80,16.81,18.51,69.79,72.17};
    double z12[8] = {1.97,3.66,1.53,2.82,9.66,10.26,38.99,39.17};
    double z13[8] = {1.21,2.33,0.77,1.11,3.49,3.14,12.39,10.67};

    TGraph *g00 = new TGraph(8,nu,z00); g00->SetTitle("Plot of L_{p};#nu [GeV];L_{p} [fm]"); g00->SetMarkerColor(kRed);
    TGraph *g01 = new TGraph(8,nu,z01); g01->SetTitle("Plot of L_{p};#nu [GeV];L_{p} [fm]"); g01->SetMarkerColor(kRed);
    TGraph *g02 = new TGraph(8,nu,z02); g02->SetTitle("Plot of L_{p};#nu [GeV];L_{p} [fm]"); g02->SetMarkerColor(kRed);
    TGraph *g03 = new TGraph(8,nu,z03); g03->SetTitle("Plot of L_{p};#nu [GeV];L_{p} [fm]"); g03->SetMarkerColor(kRed);
    
    TGraph *g10 = new TGraph(8,nu,z10); g10->SetTitle("Plot of L_{p};#nu [GeV];L_{p} [fm]"); g10->SetMarkerColor(kBlue);
    TGraph *g11 = new TGraph(8,nu,z11); g11->SetTitle("Plot of L_{p};#nu [GeV];L_{p} [fm]"); g11->SetMarkerColor(kBlue);
    TGraph *g12 = new TGraph(8,nu,z12); g12->SetTitle("Plot of L_{p};#nu [GeV];L_{p} [fm]"); g12->SetMarkerColor(kBlue);
    TGraph *g13 = new TGraph(8,nu,z13); g13->SetTitle("Plot of L_{p};#nu [GeV];L_{p} [fm]"); g13->SetMarkerColor(kBlue);

    // TCanvas *c0 = new TCanvas(); c0->cd(); g00->Draw("AP");  g10->Draw("PSAME");
    // TCanvas *c1 = new TCanvas(); c1->cd(); g01->Draw("AP");  g11->Draw("PSAME");
    // TCanvas *c2 = new TCanvas(); c2->cd(); g02->Draw("AP");  g12->Draw("PSAME");
    // TCanvas *c3 = new TCanvas(); c3->cd(); g03->Draw("AP");  g13->Draw("PSAME");

    TLegend* leg = new TLegend(0.2,0.6,0.6,0.75);
    leg->SetTextFont(43);
    leg->SetTextSize(22);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->AddEntry(g00,"#beta#gamma method","p");
    leg->AddEntry(g10,"Lund string model estimation","p");

    // TCanvas *c = new TCanvas(); c->Divide(2,2);
    // c->cd(1); c->cd(1)->SetLogx(); c->cd(1)->SetLogy(); g10->Draw("AP");  g00->Draw("PSAME"); myText(0.3,0.8,1,"z_{h} = 0.32",0.07); leg->Draw();
    // c->cd(2); c->cd(2)->SetLogx(); c->cd(2)->SetLogy(); g11->Draw("AP");  g01->Draw("PSAME"); myText(0.3,0.8,1,"z_{h} = 0.53",0.07);
    // c->cd(3); c->cd(3)->SetLogx(); c->cd(3)->SetLogy(); g12->Draw("AP");  g02->Draw("PSAME"); myText(0.3,0.8,1,"z_{h} = 0.75",0.07);
    // c->cd(4); c->cd(4)->SetLogx(); c->cd(4)->SetLogy(); g13->Draw("AP");  g03->Draw("PSAME"); myText(0.3,0.8,1,"z_{h} = 0.94",0.07);
    // c->Print("summary.pdf");

    float small = 1e-5;;
    float big = 0.2;
    TCanvas* c1 = new TCanvas("c1","c1 title",800,800);
    c1->Divide(2,2,small,small);
    for (int i=0; i<4; ++i) {
        // pad[i]->cd();
        c1->cd(i+1);
        if (i == 0) {
            gPad->SetBottomMargin(small);
            gPad->SetRightMargin(small);
            gPad->SetLeftMargin(big);
            gPad->SetTopMargin(big);
        }
        else if (i == 1) {
            gPad->SetTopMargin(big);
            gPad->SetBottomMargin(small);
            gPad->SetLeftMargin(small);
            gPad->SetRightMargin(big);
        }
        else if (i == 2) {
            gPad->SetBottomMargin(big);
            gPad->SetTopMargin(small);
            gPad->SetRightMargin(small);
            gPad->SetLeftMargin(big);
        }
        else if (i == 3) {
            gPad->SetBottomMargin(big);
            gPad->SetTopMargin(small);
            gPad->SetLeftMargin(small);
            gPad->SetRightMargin(big);
        }
    }
    double yMin=0.5, yMax=150;
    g10->SetMaximum(yMax); 
    g10->SetMinimum(yMin); 
    g11->SetMaximum(yMax); 
    g11->SetMinimum(yMin); 
    g12->SetMaximum(yMax); 
    g12->SetMinimum(yMin); 
    g13->SetMaximum(yMax); 
    g13->SetMinimum(yMin); 
    c1->cd(1); c1->cd(1)->SetLogx(); c1->cd(1)->SetLogy(); g10->Draw("AP"); g00->Draw("PSAME"); leg->Draw();
    c1->cd(2); c1->cd(2)->SetLogx(); c1->cd(2)->SetLogy(); g11->Draw("AP"); g01->Draw("PSAME");
    c1->cd(3); c1->cd(3)->SetLogx(); c1->cd(3)->SetLogy(); g12->Draw("AP"); g02->Draw("PSAME");
    c1->cd(4); c1->cd(4)->SetLogx(); c1->cd(4)->SetLogy(); g13->Draw("AP"); g03->Draw("PSAME");
    c1->cd(1); myText(0.31,0.675,kBlack,"z-bin #1",22);
    c1->cd(2); myText(0.05,0.675,kBlack,"z-bin #2",22);
    c1->cd(3); myText(0.31,0.9,kBlack,"z-bin #3",22);
    c1->cd(4); myText(0.05,0.9,kBlack,"z-bin #4",22);
    c1->Print("summary.pdf");

}
