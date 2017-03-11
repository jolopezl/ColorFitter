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

    leg->Clear(); leg->SetNColumns(1);
    TCanvas *c2 = new TCanvas();
    const char *key2 = "tg_lp";
    auto tg1 = (TGraphErrors*) fin["BL30"]->Get(key2); tg1->SetMarkerStyle(20); tg1->SetMarkerColor(kAzure); tg1->SetLineColor(kAzure); 
    auto tg2 = (TGraphErrors*) fin["BL40"]->Get(key2); tg2->SetMarkerStyle(24); tg2->SetMarkerColor(kAzure - 1); tg2->SetLineColor(kAzure - 1); 
    auto tg3 = (TGraphErrors*) fin["BL30.fixedLp"]->Get(key2); tg3->SetMarkerStyle(21); tg3->SetMarkerColor(kOrange); tg3->SetLineColor(kOrange); 
    auto tg4 = (TGraphErrors*) fin["BL40.fixedLp"]->Get(key2); tg4->SetMarkerStyle(25); tg4->SetMarkerColor(kOrange - 1); tg4->SetLineColor(kOrange - 1); 

    // Remember to apply scale factors
    double SF[4] = {9.31,8.40,7.94,7.05};
    for (int i = 0; i < 4; ++i) {
        double x,y, xerr, yerr;
        tg1->GetPoint(i, x, y);
        xerr = tg1->GetErrorX(i);
        yerr = tg1->GetErrorY(i);
        tg1->SetPoint(i, x, y*SF[i]/8.4);
        tg1->SetPointError(i, xerr, yerr*SF[i]/8.4);
        tg2->GetPoint(i, x, y);
        xerr = tg2->GetErrorX(i);
        yerr = tg2->GetErrorY(i);
        tg2->SetPoint(i, x, y*SF[i]/8.4);
        tg2->SetPointError(i, xerr, yerr*SF[i]/8.4);
        tg3->GetPoint(i, x, y);
        xerr = tg3->GetErrorX(i);
        yerr = tg3->GetErrorY(i);
        tg3->SetPoint(i, x, y*SF[i]/8.4);
        tg3->SetPointError(i, xerr, yerr*SF[i]/8.4);
        tg4->GetPoint(i, x, y);
        xerr = tg4->GetErrorX(i);
        yerr = tg4->GetErrorY(i);
        tg4->SetPoint(i, x, y*SF[i]/8.4);
        tg4->SetPointError(i, xerr, yerr*SF[i]/8.4);
    }

    const char* lund = "[0]*x*(log(1/(x*x))-1+x*x)/(1-x*x)";
    const char* lundlin = "([0]+2*[1]-2*x*[1])/(2*[2])";
    const char* lunelinfull = "([0]+2*[1]-2*x*[1]+[1]*(sqrt( 1+[3]*[3]/([1]*[1]))-1) )/(2*[2])";
    TF1 *flund = new TF1("flund","[0]*x*(log(1/(x*x))-1+x*x)/(1-x*x)", -0.01, 1.01);
    // ZVTX = (MP + 2*NU - 2*Z*NU)/(2*KAPPA)
    TF1* fg1 = new TF1("fg1", lund,-0.1,1.1);
    TF1* fg2 = new TF1("fg2", lund,-0.1,1.1);
    TF1* fg3 = new TF1("fg3", lund,-0.1,1.1);
    TF1* fg4 = new TF1("fg4", lund,-0.1,1.1);
    // TF1* fg = new TF1("fg", "([0]+2*[1]-2*x*[1]+[1]*(sqrt( 1+[3]*[3]/([1]*[1]))-1) )/(2*[2])",0,1);
/*    fg1->SetParName(0,"MP"); fg1->FixParameter(0,0.938272); // 0.9 GeV
    fg1->SetParName(1,"NU"); fg1->FixParameter(1,13.1);
    fg1->SetParName(2,"KAPPA"); fg1->SetParameter(2,1.0);
    fg1->SetParName(0,"MP"); fg1->FixParameter(0,0.938272); // 0.9 GeV
    fg2->SetParName(1,"NU"); fg2->FixParameter(1,13.1);
    fg2->SetParName(2,"KAPPA"); fg2->SetParameter(2,1.0);
    fg2->SetParName(0,"MP"); fg2->FixParameter(0,0.938272); // 0.9 GeV
    fg2->SetParName(1,"NU"); fg2->FixParameter(1,13.1);
    fg3->SetParName(2,"KAPPA"); fg3->SetParameter(2,1.0);
    fg3->SetParName(0,"MP"); fg3->FixParameter(0,0.938272); // 0.9 GeV
    fg3->SetParName(1,"NU"); fg3->FixParameter(1,13.1);
    fg3->SetParName(2,"KAPPA"); fg3->SetParameter(2,1.0);
    fg4->SetParName(2,"KAPPA"); fg4->SetParameter(2,1.0);
    fg4->SetParName(0,"MP"); fg4->FixParameter(0,0.938272); // 0.9 GeV
    fg4->SetParName(1,"NU"); fg4->FixParameter(1,13.1);
    fg4->SetParName(2,"KAPPA"); fg4->SetParameter(2,1.0);*/
    // fg->SetParName(3,"Q2"); fg->FixParameter(3,2.4);

    tg1->Fit("fg1","EMN","",0.2,1.0);
    tg2->Fit("fg2","EMN","",0.2,1.0);
    tg3->Fit("fg3","EMN","",0.2,1.0);
    tg4->Fit("fg4","EMN","",0.2,1.0);

    /*std::cout << "BL30.expLp \t Chi^2/ndf = " << fg1->GetChisquare()/fg1->GetNDF() << "\t KAPPA = " << fg1->GetParameter(2) << " +/- " << fg1->GetParError(2) << std::endl;
    std::cout << "BL40.expLp \t Chi^2/ndf = " << fg2->GetChisquare()/fg2->GetNDF() << "\t KAPPA = " << fg2->GetParameter(2) << " +/- " << fg2->GetParError(2) << std::endl;
    std::cout << "BL30.fixedLp \t Chi^2/ndf = " << fg3->GetChisquare()/fg3->GetNDF() << "\t KAPPA = " << fg3->GetParameter(2) << " +/- " << fg3->GetParError(2) << std::endl;
    std::cout << "BL40.fixedLp \t Chi^2/ndf = " << fg4->GetChisquare()/fg4->GetNDF() << "\t KAPPA = " << fg4->GetParameter(2) << " +/- " << fg4->GetParError(2) << std::endl;*/

    std::cout << "BL30.expLp \t Chi^2/ndf = " << fg1->GetChisquare()/fg1->GetNDF() << "\t f(Q^2,nu) = " << fg1->GetParameter(0) << " +/- " << fg1->GetParError(0) << std::endl;
    std::cout << "BL40.expLp \t Chi^2/ndf = " << fg2->GetChisquare()/fg2->GetNDF() << "\t f(Q^2,nu) = " << fg2->GetParameter(0) << " +/- " << fg2->GetParError(0) << std::endl;
    std::cout << "BL30.fixedLp \t Chi^2/ndf = " << fg3->GetChisquare()/fg3->GetNDF() << "\t f(Q^2,nu) = " << fg3->GetParameter(0) << " +/- " << fg3->GetParError(0) << std::endl;
    std::cout << "BL40.fixedLp \t Chi^2/ndf = " << fg4->GetChisquare()/fg4->GetNDF() << "\t f(Q^2,nu) = " << fg4->GetParameter(0) << " +/- " << fg4->GetParError(0) << std::endl;

    fg1->SetLineColor(tg1->GetLineColor());
    fg2->SetLineColor(tg2->GetLineColor());
    fg3->SetLineColor(tg3->GetLineColor());
    fg4->SetLineColor(tg4->GetLineColor());

    tg1->Draw("APE"); fg1->Draw("SAME");
    tg2->Draw("PSAME"); fg2->Draw("SAME");
    tg3->Draw("PSAME"); fg3->Draw("SAME");
    tg4->Draw("PSAME"); fg4->Draw("SAME");

    TLegend* leg2 = new TLegend(0.65,0.7,0.95,0.9);
    // leg2->SetNColumns(2);
    leg2->SetColumnSeparation(.7);
    leg2->SetTextFont(43);
    leg2->SetTextSize(22);
    leg2->SetBorderSize(0);
    leg2->SetFillStyle(0);
    leg2->AddEntry(tg1,"BL30");
    leg2->AddEntry(tg2,"BL40");
    leg2->AddEntry(tg3,"BL30.fixedLp");
    leg2->AddEntry(tg4,"BL40.fixedLp");
    leg2->Draw();

    c2->Print("test2.pdf");




}
