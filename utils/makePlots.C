void makePlots() {
    SetAtlasStyle();
    std::string models[12] = {"BL","BL30","BL40","BLE","BLE30","BLE40",
                              "BL.fixedLp","BL30.fixedLp","BL40.fixedLp","BLE.fixedLp","BLE30.fixedLp","BLE40.fixedLp"};

    std::map<std::string,TFile*> fin;
    for (int i = 0; i < 12; ++i) {
        std:string ifile = "testFit"+models[i]+".root";
        fin[models[i]] = TFile::Open(ifile.c_str(), "READ");
    }
    std::string plotsNames[7] = {"tg_q0","tg_lp","tg_cs","tg_dlog","tg_dz","tg_casc","tg_chisq"};

    gStyle->SetEndErrorSize(5);
    // gStyle->SetErrorX(0.);

    TLegend* leg = new TLegend(0.4,0.6,0.7,0.82);
    leg->SetNColumns(2);
    leg->SetColumnSeparation(.7);
    leg->SetTextFont(43);
    leg->SetTextSize(22);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    // leg->Draw();
    TGraphErrors *gr[12];
    TCanvas *c1 = new TCanvas();
    const char *key = "tg_chisq";
    for (int i = 0; i < 12; ++i) {
        gr[i] = (TGraphErrors*) fin[models[i]]->Get(key);
        if (i < 6) {
            gr[i]->SetMarkerColor(kAzure - i);
            gr[i]->SetLineColor(kAzure - i);
            if (i == 0) {gr[i]->Draw("APE");}
            else {gr[i]->Draw("PSAME");}
        }
        else {
            gr[i]->SetMarkerStyle(21);
            gr[i]->SetMarkerColor(kOrange - i + 6);
            gr[i]->SetLineColor(kOrange - i + 6);
            if (i == 0) {gr[i]->Draw("APE");}
            else {gr[i]->Draw("PSAME");}
        }
        leg->AddEntry(gr[i],models[i].c_str(),"cl");
    }
    leg->Draw();
    c1->Print("test.pdf");

    // leg->Clear(); leg->SetNColumns(1);
    // TCanvas *c2 = new TCanvas();
    // const char *key2 = "tg_q0";
    // auto tg1 = (TGraphErrors*) fin["BL30"]->Get(key2); tg1->SetMarkerStyle(20); tg1->SetMarkerColor(kAzure); tg1->SetLineColor(kAzure); 
    // auto tg2 = (TGraphErrors*) fin["BL40"]->Get(key2); tg2->SetMarkerStyle(24); tg2->SetMarkerColor(kAzure - 1); tg2->SetLineColor(kAzure - 1); 
    // auto tg3 = (TGraphErrors*) fin["BL30.fixedLp"]->Get(key2); tg3->SetMarkerStyle(21); tg3->SetMarkerColor(kOrange); tg3->SetLineColor(kOrange); 
    // auto tg4 = (TGraphErrors*) fin["BL40.fixedLp"]->Get(key2); tg4->SetMarkerStyle(25); tg4->SetMarkerColor(kOrange - 1); tg4->SetLineColor(kOrange - 1); 

    // tg1->Draw("APE");
    // tg2->Draw("PSAME");
    // tg3->Draw("PSAME");
    // tg4->Draw("PSAME");
    // leg->AddEntry(tg1,"BL30");
    // leg->AddEntry(tg2,"BL40");
    // leg->AddEntry(tg3,"BL30.fixedLp");
    // leg->AddEntry(tg4,"BL40.fixedLp");
    // leg->Draw();

    // c2->Print("test2.pdf");




}
