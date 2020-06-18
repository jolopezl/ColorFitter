void PlotMultiplicity() {
  // SetAtlasStyle();
  // gStyle->SetEndErrorSize(7);
  TGraphErrors* tg_Ne = new TGraphErrors(9);
  TGraphErrors* tg_Kr = new TGraphErrors(9);
  TGraphErrors* tg_Xe = new TGraphErrors(9);
  TGraphErrors* tg_Ne_tot = new TGraphErrors(9);
  TGraphErrors* tg_Kr_tot = new TGraphErrors(9);
  TGraphErrors* tg_Xe_tot = new TGraphErrors(9);
  TGraphErrors* tg_Ne_tot_down = new TGraphErrors(9);
  TGraphErrors* tg_Kr_tot_down = new TGraphErrors(9);
  TGraphErrors* tg_Xe_tot_down = new TGraphErrors(9);
  TGraphErrors* tg_Ne_tot_up = new TGraphErrors(9);
  TGraphErrors* tg_Kr_tot_up = new TGraphErrors(9);
  TGraphErrors* tg_Xe_tot_up = new TGraphErrors(9);

  tg_Ne->SetPoint(0, 0.1782, 0.8947);
  tg_Ne->SetPoint(1, 0.2478, 0.8918);
  tg_Ne->SetPoint(2, 0.3467, 0.8850);
  tg_Ne->SetPoint(3, 0.4465, 0.8784);
  tg_Ne->SetPoint(4, 0.5470, 0.8887);
  tg_Ne->SetPoint(5, 0.6470, 0.8839);
  tg_Ne->SetPoint(6, 0.7469, 0.8594);
  tg_Ne->SetPoint(7, 0.8462, 0.8609);
  tg_Ne->SetPoint(8, 0.9393, 0.7754);
  tg_Ne_tot->SetPoint(0, 0.1782, 0.8947);
  tg_Ne_tot->SetPoint(1, 0.2478, 0.8918);
  tg_Ne_tot->SetPoint(2, 0.3467, 0.8850);
  tg_Ne_tot->SetPoint(3, 0.4465, 0.8784);
  tg_Ne_tot->SetPoint(4, 0.5470, 0.8887);
  tg_Ne_tot->SetPoint(5, 0.6470, 0.8839);
  tg_Ne_tot->SetPoint(6, 0.7469, 0.8594);
  tg_Ne_tot->SetPoint(7, 0.8462, 0.8609);
  tg_Ne_tot->SetPoint(8, 0.9393, 0.7754);
  tg_Ne->SetPointError(0, 0, 0.0113);
  tg_Ne->SetPointError(1, 0, 0.0075);
  tg_Ne->SetPointError(2, 0, 0.0090);
  tg_Ne->SetPointError(3, 0, 0.0112);
  tg_Ne->SetPointError(4, 0, 0.0137);
  tg_Ne->SetPointError(5, 0, 0.0163);
  tg_Ne->SetPointError(6, 0, 0.0189);
  tg_Ne->SetPointError(7, 0, 0.0228);
  tg_Ne->SetPointError(8, 0, 0.0270);
  tg_Ne_tot->SetPointError(0, 0, 0.0354);
  tg_Ne_tot->SetPointError(1, 0, 0.0341);
  tg_Ne_tot->SetPointError(2, 0, 0.0326);
  tg_Ne_tot->SetPointError(3, 0, 0.0318);
  tg_Ne_tot->SetPointError(4, 0, 0.0322);
  tg_Ne_tot->SetPointError(5, 0, 0.0336);
  tg_Ne_tot->SetPointError(6, 0, 0.0412);
  tg_Ne_tot->SetPointError(7, 0, 0.0454);
  tg_Ne_tot->SetPointError(8, 0, 0.0409);

  tg_Kr->SetPoint(0, 0.1782, 0.8294);
  tg_Kr->SetPoint(1, 0.2474, 0.7748);
  tg_Kr->SetPoint(2, 0.3461, 0.7551);
  tg_Kr->SetPoint(3, 0.4465, 0.7354);
  tg_Kr->SetPoint(4, 0.5464, 0.7151);
  tg_Kr->SetPoint(5, 0.6472, 0.6970);
  tg_Kr->SetPoint(6, 0.7469, 0.6687);
  tg_Kr->SetPoint(7, 0.8459, 0.6271);
  tg_Kr->SetPoint(8, 0.9391, 0.5414);
  tg_Kr_tot->SetPoint(0, 0.1782, 0.8294);
  tg_Kr_tot->SetPoint(1, 0.2474, 0.7748);
  tg_Kr_tot->SetPoint(2, 0.3461, 0.7551);
  tg_Kr_tot->SetPoint(3, 0.4465, 0.7354);
  tg_Kr_tot->SetPoint(4, 0.5464, 0.7151);
  tg_Kr_tot->SetPoint(5, 0.6472, 0.6970);
  tg_Kr_tot->SetPoint(6, 0.7469, 0.6687);
  tg_Kr_tot->SetPoint(7, 0.8459, 0.6271);
  tg_Kr_tot->SetPoint(8, 0.9391, 0.5414);
  tg_Kr->SetPointError(0, 0, 0.0107);
  tg_Kr->SetPointError(1, 0, 0.0066);
  tg_Kr->SetPointError(2, 0, 0.0078);
  tg_Kr->SetPointError(3, 0, 0.0095);
  tg_Kr->SetPointError(4, 0, 0.0115);
  tg_Kr->SetPointError(5, 0, 0.0136);
  tg_Kr->SetPointError(6, 0, 0.0156);
  tg_Kr->SetPointError(7, 0, 0.0176);
  tg_Kr->SetPointError(8, 0, 0.0207);
  tg_Kr_tot->SetPointError(0, 0, 0.0328);
  tg_Kr_tot->SetPointError(1, 0, 0.0320);
  tg_Kr_tot->SetPointError(2, 0, 0.0298);
  tg_Kr_tot->SetPointError(3, 0, 0.0301);
  tg_Kr_tot->SetPointError(4, 0, 0.0279);
  tg_Kr_tot->SetPointError(5, 0, 0.0308);
  tg_Kr_tot->SetPointError(6, 0, 0.0328);
  tg_Kr_tot->SetPointError(7, 0, 0.0400);
  tg_Kr_tot->SetPointError(8, 0, 0.0360);

  tg_Xe->SetPoint(0, 0.1781, 0.7843);
  tg_Xe->SetPoint(1, 0.2478, 0.7184);
  tg_Xe->SetPoint(2, 0.3463, 0.7048);
  tg_Xe->SetPoint(3, 0.4464, 0.7012);
  tg_Xe->SetPoint(4, 0.5473, 0.6632);
  tg_Xe->SetPoint(5, 0.6473, 0.6460);
  tg_Xe->SetPoint(6, 0.7458, 0.6303);
  tg_Xe->SetPoint(7, 0.8458, 0.5576);
  tg_Xe->SetPoint(8, 0.9410, 0.5035);
  tg_Xe_tot->SetPoint(0, 0.1781, 0.7843);
  tg_Xe_tot->SetPoint(1, 0.2478, 0.7184);
  tg_Xe_tot->SetPoint(2, 0.3463, 0.7048);
  tg_Xe_tot->SetPoint(3, 0.4464, 0.7012);
  tg_Xe_tot->SetPoint(4, 0.5473, 0.6632);
  tg_Xe_tot->SetPoint(5, 0.6473, 0.6460);
  tg_Xe_tot->SetPoint(6, 0.7458, 0.6303);
  tg_Xe_tot->SetPoint(7, 0.8458, 0.5576);
  tg_Xe_tot->SetPoint(8, 0.9410, 0.5035);
  tg_Xe->SetPointError(0, 0, 0.0124);
  tg_Xe->SetPointError(1, 0, 0.0075);
  tg_Xe->SetPointError(2, 0, 0.0088);
  tg_Xe->SetPointError(3, 0, 0.0111);
  tg_Xe->SetPointError(4, 0, 0.0131);
  tg_Xe->SetPointError(5, 0, 0.0155);
  tg_Xe->SetPointError(6, 0, 0.0180);
  tg_Xe->SetPointError(7, 0, 0.0198);
  tg_Xe->SetPointError(8, 0, 0.0238);
  tg_Xe_tot->SetPointError(0, 0, 0.0330);
  tg_Xe_tot->SetPointError(1, 0, 0.0324);
  tg_Xe_tot->SetPointError(2, 0, 0.0297);
  tg_Xe_tot->SetPointError(3, 0, 0.0271);
  tg_Xe_tot->SetPointError(4, 0, 0.0269);
  tg_Xe_tot->SetPointError(5, 0, 0.0271);
  tg_Xe_tot->SetPointError(6, 0, 0.0293);
  tg_Xe_tot->SetPointError(7, 0, 0.0395);
  tg_Xe_tot->SetPointError(8, 0, 0.0412);

  for (int i = 0; i < 9; ++i) {
    tg_Ne_tot_up->GetX()[i] = tg_Ne_tot->GetX()[i];
    tg_Ne_tot_up->GetEX()[i] = tg_Ne_tot->GetEX()[i];
    tg_Ne_tot_up->GetY()[i] = tg_Ne_tot->GetY()[i] + tg_Ne_tot->GetEY()[i];
    tg_Ne_tot_up->GetEY()[i] = tg_Ne_tot->GetEY()[i];
    tg_Kr_tot_up->GetX()[i] = tg_Kr_tot->GetX()[i];
    tg_Kr_tot_up->GetEX()[i] = tg_Kr_tot->GetEX()[i];
    tg_Kr_tot_up->GetY()[i] = tg_Kr_tot->GetY()[i] + tg_Kr_tot->GetEY()[i];
    tg_Kr_tot_up->GetEY()[i] = tg_Kr_tot->GetEY()[i];
    tg_Xe_tot_up->GetX()[i] = tg_Xe_tot->GetX()[i];
    tg_Xe_tot_up->GetEX()[i] = tg_Xe_tot->GetEX()[i];
    tg_Xe_tot_up->GetY()[i] = tg_Xe_tot->GetY()[i] + tg_Xe_tot->GetEY()[i];
    tg_Xe_tot_up->GetEY()[i] = tg_Xe_tot->GetEY()[i];
    }
    for (int i=0; i<9; ++i) {
        tg_Ne_tot_down->GetX()[i] = tg_Ne_tot->GetX()[i];
        tg_Ne_tot_down->GetEX()[i] = tg_Ne_tot->GetEX()[i];
        tg_Ne_tot_down->GetY()[i] = tg_Ne_tot->GetY()[i] - tg_Ne_tot->GetEY()[i];
        tg_Ne_tot_down->GetEY()[i] = tg_Ne_tot->GetEY()[i];
        tg_Kr_tot_down->GetX()[i] = tg_Kr_tot->GetX()[i];
        tg_Kr_tot_down->GetEX()[i] = tg_Kr_tot->GetEX()[i];
        tg_Kr_tot_down->GetY()[i] = tg_Kr_tot->GetY()[i] - tg_Kr_tot->GetEY()[i];
        tg_Kr_tot_down->GetEY()[i] = tg_Kr_tot->GetEY()[i];
        tg_Xe_tot_down->GetX()[i] = tg_Xe_tot->GetX()[i];
        tg_Xe_tot_down->GetEX()[i] = tg_Xe_tot->GetEX()[i];
        tg_Xe_tot_down->GetY()[i] = tg_Xe_tot->GetY()[i] - tg_Xe_tot->GetEY()[i];
        tg_Xe_tot_down->GetEY()[i] = tg_Xe_tot->GetEY()[i];
    }

    tg_Ne->SetMarkerColor(kBlack);
    tg_Ne_tot->SetMarkerColor(kBlack);
    tg_Ne->SetLineColor(kBlack);
    tg_Ne_tot->SetLineColor(kBlack);

    tg_Kr->SetMarkerColor(kRed+1);
    tg_Kr_tot->SetMarkerColor(kRed+1);
    tg_Kr->SetLineColor(kRed+1);
    tg_Kr_tot->SetLineColor(kRed+1);

    tg_Xe->SetMarkerColor(kAzure);
    tg_Xe_tot->SetMarkerColor(kAzure);
    tg_Xe->SetLineColor(kAzure);
    tg_Xe_tot->SetLineColor(kAzure);

    tg_Ne->SetMarkerStyle(kFullCircle);
    tg_Ne_tot->SetMarkerStyle(kFullCircle);
    tg_Kr->SetMarkerStyle(kFullSquare);
    tg_Kr_tot->SetMarkerStyle(kFullSquare);
    tg_Xe->SetMarkerStyle(kFullTriangleUp);
    tg_Xe_tot->SetMarkerStyle(kFullTriangleUp);

    tg_Ne->SetLineWidth(2);
    tg_Ne_tot->SetLineWidth(2);
    tg_Kr->SetLineWidth(2);
    tg_Kr_tot->SetLineWidth(2);
    tg_Xe->SetLineWidth(2);
    tg_Xe_tot->SetLineWidth(2);

    tg_Ne->SetMarkerSize(1.4);
    tg_Ne_tot->SetMarkerSize(1.4);
    tg_Kr->SetMarkerSize(1.4);
    tg_Kr_tot->SetMarkerSize(1.4);
    tg_Xe->SetMarkerSize(1.4);
    tg_Xe_tot->SetMarkerSize(1.4);

    TCanvas *c1 = new TCanvas("c1","c1 title",600,600);
    tg_Ne->GetXaxis()->SetNdivisions(505);
    tg_Ne->GetYaxis()->SetRangeUser(0.4,1);
    tg_Ne->GetXaxis()->SetLimits(0.1,1);
    tg_Ne->GetYaxis()->SetTitle("R_{M}");
    tg_Ne->GetYaxis()->SetTitleOffset(1.6);
    tg_Ne->GetXaxis()->SetTitle("z_{h}");
    tg_Ne->Draw("APE");
    tg_Ne_tot->Draw("SAME Z");
    tg_Kr->Draw("PSAME");
    tg_Kr_tot->Draw("SAME Z");
    tg_Xe->Draw("PSAME");
    tg_Xe_tot->Draw("SAME Z");
    TLatex *text1 =  new TLatex();
    text1->SetNDC();
    text1->SetTextFont(62);
    text1->SetTextSize(0.03);
    text1->DrawLatex(0.18,0.9,"HERMES Collaboration, Nuclear Physics B 780 (2007) 1-27");
        
    const char *myFunc = "pol4";
    TF1 *ff_Ne_tot = new TF1("ff_Ne_tot",myFunc,0.1,0.99);
    TF1 *ff_Kr_tot = new TF1("ff_Kr_tot",myFunc,0.1,0.99);
    TF1 *ff_Xe_tot = new TF1("ff_Xe_tot",myFunc,0.1,0.99);
    TF1 *ff_Ne_tot_up = new TF1("ff_Ne_tot_up",myFunc,0.1,0.99);
    TF1 *ff_Kr_tot_up = new TF1("ff_Kr_tot_up",myFunc,0.1,0.99);
    TF1 *ff_Xe_tot_up = new TF1("ff_Xe_tot_up",myFunc,0.1,0.99);
    TF1 *ff_Ne_tot_down = new TF1("ff_Ne_tot_down",myFunc,0.1,0.99);
    TF1 *ff_Kr_tot_down = new TF1("ff_Kr_tot_down",myFunc,0.1,0.99);
    TF1 *ff_Xe_tot_down = new TF1("ff_Xe_tot_down",myFunc,0.1,0.99);

    ff_Ne_tot->SetLineColor(tg_Ne_tot->GetLineColor());
    ff_Kr_tot->SetLineColor(tg_Kr_tot->GetLineColor());
    ff_Xe_tot->SetLineColor(tg_Xe_tot->GetLineColor());
    ff_Ne_tot->SetLineStyle(kDashed); ff_Ne_tot->SetLineWidth(2);
    ff_Kr_tot->SetLineStyle(kDashed); ff_Kr_tot->SetLineWidth(2);
    ff_Xe_tot->SetLineStyle(kDashed); ff_Xe_tot->SetLineWidth(2);

    ff_Ne_tot_up->SetLineColor(tg_Ne_tot->GetLineColor());
    ff_Kr_tot_up->SetLineColor(tg_Kr_tot->GetLineColor());
    ff_Xe_tot_up->SetLineColor(tg_Xe_tot->GetLineColor());
    ff_Ne_tot_up->SetLineStyle(kDashed); ff_Ne_tot->SetLineWidth(2);
    ff_Kr_tot_up->SetLineStyle(kDashed); ff_Kr_tot->SetLineWidth(2);
    ff_Xe_tot_up->SetLineStyle(kDashed); ff_Xe_tot->SetLineWidth(2);

    ff_Ne_tot_down->SetLineColor(tg_Ne_tot->GetLineColor());
    ff_Kr_tot_down->SetLineColor(tg_Kr_tot->GetLineColor());
    ff_Xe_tot_down->SetLineColor(tg_Xe_tot->GetLineColor());
    ff_Ne_tot_down->SetLineStyle(kDashed); ff_Ne_tot->SetLineWidth(2);
    ff_Kr_tot_down->SetLineStyle(kDashed); ff_Kr_tot->SetLineWidth(2);
    ff_Xe_tot_down->SetLineStyle(kDashed); ff_Xe_tot->SetLineWidth(2);

    tg_Ne_tot->Fit("ff_Ne_tot");
    tg_Kr_tot->Fit("ff_Kr_tot");
    tg_Xe_tot->Fit("ff_Xe_tot");

    tg_Ne_tot_down->Fit("ff_Ne_tot_down");
    tg_Kr_tot_down->Fit("ff_Kr_tot_down");
    tg_Xe_tot_down->Fit("ff_Xe_tot_down");
    tg_Ne_tot_up->Fit("ff_Ne_tot_up");
    tg_Kr_tot_up->Fit("ff_Kr_tot_up");
    tg_Xe_tot_up->Fit("ff_Xe_tot_up");

    // ff_Ne_tot->Draw("SAME");
    // ff_Kr_tot->Draw("SAME");
    // ff_Xe_tot->Draw("SAME");

    TGraphErrors *tg_Ne_intp = new TGraphErrors(4);
    TGraphErrors *tg_Kr_intp = new TGraphErrors(4);
    TGraphErrors *tg_Xe_intp = new TGraphErrors(4);
    tg_Ne_intp->SetMarkerStyle(kOpenCircle);
    tg_Kr_intp->SetMarkerStyle(kOpenSquare);
    tg_Xe_intp->SetMarkerStyle(kOpenTriangleUp);
    tg_Ne_intp->SetMarkerSize(tg_Ne_tot->GetMarkerSize());
    tg_Kr_intp->SetMarkerSize(tg_Kr_tot->GetMarkerSize());
    tg_Xe_intp->SetMarkerSize(tg_Xe_tot->GetMarkerSize());
    tg_Ne_intp->SetMarkerColor(tg_Ne_tot->GetMarkerColor());
    tg_Kr_intp->SetMarkerColor(tg_Kr_tot->GetMarkerColor());
    tg_Xe_intp->SetMarkerColor(tg_Xe_tot->GetMarkerColor());
    tg_Ne_intp->SetLineColor(tg_Ne_tot->GetLineColor());
    tg_Kr_intp->SetLineColor(tg_Kr_tot->GetLineColor());
    tg_Xe_intp->SetLineColor(tg_Xe_tot->GetLineColor());
    tg_Ne_intp->SetLineWidth(tg_Ne_tot->GetLineWidth());
    tg_Kr_intp->SetLineWidth(tg_Kr_tot->GetLineWidth());
    tg_Xe_intp->SetLineWidth(tg_Xe_tot->GetLineWidth());

    double xp[4] = {0.31,0.54,0.75,0.94};
    for (int i=0; i<4; ++i) {
        tg_Ne_intp->SetPoint(i,xp[i],ff_Ne_tot->Eval(xp[i]));
        tg_Kr_intp->SetPoint(i,xp[i],ff_Kr_tot->Eval(xp[i]));
        tg_Xe_intp->SetPoint(i,xp[i],ff_Xe_tot->Eval(xp[i]));
        tg_Ne_intp->SetPointError(i,0,0.5*(ff_Ne_tot_up->Eval(xp[i]) - ff_Ne_tot_down->Eval(xp[i])));
        tg_Kr_intp->SetPointError(i,0,0.5*(ff_Kr_tot_up->Eval(xp[i]) - ff_Kr_tot_down->Eval(xp[i])));
        tg_Xe_intp->SetPointError(i,0,0.5*(ff_Xe_tot_up->Eval(xp[i]) - ff_Xe_tot_down->Eval(xp[i])));


        cout << "Interpolated point " << i << endl;
        cout << "RM (Ne) = " << ff_Ne_tot->Eval(xp[i]) << " +/- " << 0.5*(ff_Ne_tot_up->Eval(xp[i]) - ff_Ne_tot_down->Eval(xp[i])) << endl;
        cout << "RM (Kr) = " << ff_Kr_tot->Eval(xp[i]) << " +/- " << 0.5*(ff_Kr_tot_up->Eval(xp[i]) - ff_Kr_tot_down->Eval(xp[i])) << endl;
        cout << "RM (Xe) = " << ff_Xe_tot->Eval(xp[i]) << " +/- " << 0.5*(ff_Xe_tot_up->Eval(xp[i]) - ff_Xe_tot_down->Eval(xp[i])) << endl;

    }

    tg_Ne_intp->SetFillColorAlpha(kBlack,0.5);
    tg_Kr_intp->SetFillColorAlpha(kBlack,0.5);
    tg_Xe_intp->SetFillColorAlpha(kBlack,0.5);

    tg_Ne_intp->Draw("SAME PZ");
    tg_Kr_intp->Draw("SAME PZ");
    tg_Xe_intp->Draw("SAME PZ");

    // tg_Kr_tot_down->Draw("*SAME");
    // ff_Kr_tot_down->Draw("SAME");
    // tg_Kr_tot_up->Draw("*SAME");
    // ff_Kr_tot_up->Draw("SAME");

    // Perform interpolation

    TLegend *ll = new TLegend(0.2,0.2,0.35,0.55);
    ll->SetBorderSize(0);  // no border
    ll->SetFillStyle(0);
    ll->SetFillColor(0);   // Legend background should be white
    // ll->SetTextFont(42);
    ll->SetTextSize(0.03); // Increase entry font size! 
    ll->AddEntry(tg_Ne,"Ne data","pe");
    ll->AddEntry(tg_Kr,"Kr data","pe");
    ll->AddEntry(tg_Xe,"Xe data","pe");
    ll->AddEntry(ff_Ne_tot,"Ne interpolation","l");
    ll->AddEntry(ff_Kr_tot,"Kr interpolation","l");
    ll->AddEntry(ff_Xe_tot,"Xe interpolation","l");
    ll->Draw();

    TLegend *ll2 = new TLegend(0.45,0.2,0.6,0.375);
    ll2->SetBorderSize(0);  // no border
    ll2->SetFillStyle(0);
    ll2->SetFillColor(0);   // Legend background should be white
    ll2->SetTextSize(0.03); // Increase entry font size! 
    ll2->AddEntry(tg_Ne_intp,"Ne interpolated","pe");
    ll2->AddEntry(tg_Kr_intp,"Kr interpolated","pe");
    ll2->AddEntry(tg_Xe_intp,"Xe interpolated","pe");
    ll2->Draw();

    c1->Print("Plot_HERMES_data_RM.pdf");
}
