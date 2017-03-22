void LundFitting() {
    SetAtlasStyle();
    std::string models[12] = {"BL","BL30","BL40","BLE","BLE30","BLE40",
                              "BL.fixedLp","BL30.fixedLp","BL40.fixedLp","BLE.fixedLp","BLE30.fixedLp","BLE40.fixedLp"};

    std::map<std::string,TFile*> fin;
    for (int i = 0; i < 12; ++i) {
        std:string ifile = "testFit"+models[i]+".root";
        fin[models[i]] = TFile::Open(ifile.c_str(), "READ");
    }
    std::string plotsNames[7] = {"tg_q0","tg_lp","tg_cs","tg_dlog","tg_dz","tg_casc","tg_chisq"};

    // gStyle->SetEndErrorSize(5);
    // gStyle->SetErrorX(0.);

    TCanvas *c2 = new TCanvas();
    const char *key2 = "tg_lp";
    auto tg1 = (TGraphErrors*) fin["BL30"]->Get(key2); tg1->SetMarkerStyle(20); tg1->SetMarkerColor(kAzure); tg1->SetLineColor(kAzure); 
    auto tg2 = (TGraphErrors*) fin["BL40"]->Get(key2); tg2->SetMarkerStyle(24); tg2->SetMarkerColor(kAzure - 1); tg2->SetLineColor(kAzure - 1); 
    auto tg3 = (TGraphErrors*) fin["BL30.fixedLp"]->Get(key2); tg3->SetMarkerStyle(21); tg3->SetMarkerColor(kOrange); tg3->SetLineColor(kOrange); 
    auto tg4 = (TGraphErrors*) fin["BL40.fixedLp"]->Get(key2); tg4->SetMarkerStyle(25); tg4->SetMarkerColor(kOrange - 1); tg4->SetLineColor(kOrange - 1); 

    // Remember to apply scale factors
    // double SF[4] = {9.31,8.40,7.94,7.05};
    double SF[4] = {8.40,8.40,8.40,8.40};
    for (int i = 0; i < 4; ++i) {
        double x,y, xerr, yerr;
        tg1->GetPoint(i, x, y);
        xerr = 0;//tg1->GetErrorX(i);
        yerr = tg1->GetErrorY(i);
        tg1->SetPoint(i, x, y*SF[i]/8.4);
        tg1->SetPointError(i, xerr, yerr*SF[i]/8.4);
        tg2->GetPoint(i, x, y);
        xerr = 0;//tg2->GetErrorX(i);
        yerr = tg2->GetErrorY(i);
        tg2->SetPoint(i, x, y*SF[i]/8.4);
        tg2->SetPointError(i, xerr, yerr*SF[i]/8.4);
        tg3->GetPoint(i, x, y);
        xerr = 0;//tg3->GetErrorX(i);
        yerr = tg3->GetErrorY(i);
        tg3->SetPoint(i, x, y*SF[i]/8.4);
        tg3->SetPointError(i, xerr, yerr*SF[i]/8.4);
        tg4->GetPoint(i, x, y);
        xerr = 0;//tg4->GetErrorX(i);
        yerr = tg4->GetErrorY(i);
        tg4->SetPoint(i, x, y*SF[i]/8.4);
        tg4->SetPointError(i, xerr, yerr*SF[i]/8.4);
    }

    const char* LundLog = "[0]*x*(log(1/(x*x))-1+x*x)/(1-x*x)";
    const char* LundLinearShort = "([0]+2*[1]-2*x*[1])/(2*[2])";
    // const char* LundLinearLong = "([0]+2*[1]-2*x*[1]+[1]*(sqrt(1+[3]*[3]/([1]*[1]))-1))/(2*[2])";
    const char* LundLinearLong = "([0] + [1]*(1 - x) + [1]*(sqrt(1 + [3]*[3]/([1]*[1])) - x))/(2*[2])";

    TF1* fg1 = new TF1("fg1", LundLinearLong, 0.0, 1.0);
    fg1->SetParName(0,"MP"); fg1->FixParameter(0,0.938272); // 0.9 GeV
    fg1->SetParName(1,"NU"); fg1->FixParameter(1,13.1);
    fg1->SetParName(2,"KAPPA"); fg1->SetParameter(2,1.0);
    fg1->SetParName(3,"Q2"); fg1->FixParameter(3,2.4);

    TF1* fg2 = new TF1("fg2", LundLog, 0.0, 1.0);
    fg2->SetParName(0,"F(Q2,NU)"); fg2->SetParameter(0,1); // 0.9 GeV

    tg1->SetMarkerColor(kBlack);
    tg1->SetLineColor(kBlack); 
    fg1->SetLineStyle(2);     fg1->SetLineColor(kBlue);
    fg2->SetLineStyle(2);     fg2->SetLineColor(kRed);

    tg1->Fit("fg1", "EMN", "", 0.0, 1.0);
    tg1->Fit("fg2", "EMN", "", 0.0, 1.0);

    tg1->GetXaxis()->SetLimits(0.0,1.0);
    tg1->Draw("APE"); 
    fg1->Draw("SAME");
    fg2->Draw("SAME");

    cout << "Chi^2 = " << fg1->GetChisquare() << endl;
    cout << "NDF = " << fg1->GetNDF() << endl;
    cout << "Chi^2/NDF = " << fg1->GetChisquare()/fg1->GetNDF() << endl;
    cout << "p-value = " << fg1->GetProb() << endl;

    cout << "Chi^2 = " << fg2->GetChisquare() << endl;
    cout << "NDF = " << fg2->GetNDF() << endl;
    cout << "Chi^2/NDF = " << fg2->GetChisquare()/fg2->GetNDF() << endl;
    cout << "p-value = " << fg2->GetProb() << endl;

    TLegend* leg = new TLegend(0.2,0.2,0.4,0.6);
    // leg->SetNColumns(2);
    leg->SetTextFont(43);
    leg->SetTextSize(22);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->AddEntry(tg1,"BL30","pe");
    leg->AddEntry(fg1,"Linear Fit, #kappa=0.98#pm 0.09, #chi^{2}/NDF=2.1","l");
    leg->AddEntry(fg2,"Log Fit fit, #chi^{2}/NDF=3.2","l");
    leg->Draw();

    c2->Print("test2.pdf");


}
