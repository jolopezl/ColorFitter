#define PROTON_MASS 0.938 // PDG value in GeV^2

// const double string = 1;
double yMin = 0.3, yMax = 99;
double xMin = 5, xMax = 110;

TGraph* ExtrapolationImproved(int zbin) {
    std::map<int,double> L0;
    L0[0] = -99;
    // BLE30
    L0[1] = 6.93319 / 9.24;
    L0[2] = 4.95501 / 8.40;
    L0[3] = 2.79043 / 7.94;
    L0[4] = 1.38668 / 7.14;
    // BL30
    // L0[1] = 6.8853  / 9.24;
    // L0[2] = 5.91803 / 8.40;
    // L0[3] = 4.29427 / 7.94;
    // L0[4] = 2.31287 / 7.14;

    /* 
        Mother function with the values of x_bj(nu)
        Taken from DIS simulation in PYTHIA
    */
    TF1 *fcn = new TF1("fcn", "([0]+[1]*x+[2]*pow(x,2)) + exp([3]+[4]*x)", 1, 100);
    fcn->SetParameter(0,  1.08904e-01);
    fcn->SetParameter(1, -1.26225e-03);
    fcn->SetParameter(2,  5.35460e-06);
    fcn->SetParameter(3, -1.40235e+00);
    fcn->SetParameter(4, -1.25454e-01);

    TF1 *fcnRel = new TF1("fcnRel","[0]*TMath::Sqrt(x/(2*[1]*[2]) - 1)",2,150);
    TF1 *fcnRel_up = new TF1("fcnRel_up","[0]*TMath::Sqrt(x/(2*[1]*[2]) - 1)",2,150);
    TF1 *fcnRel_down = new TF1("fcnRel_down","[0]*TMath::Sqrt(x/(2*[1]*[2]) - 1)",2,150);
    fcnRel->SetParName(0, "coeff");
    fcnRel->SetParName(1, "Mp");
    fcnRel->SetParName(2, "xBj");
    fcnRel->SetParameter(0, L0[zbin]);
    fcnRel->SetParameter(1, 0.938); // PDG value in GeV^2

    TGraph *tg = new TGraph(120);
    double xBj = 0.1;
    for (int nu = 1; nu < 121; ++nu) {
        xBj = fcn->Eval(nu);
        fcnRel->SetParameter(2, xBj);
        // cout << nu << "\t" << fcnRel->Eval(nu) << endl;
        tg->SetPoint(nu,nu,fcnRel->Eval(nu));
    }
    tg->GetYaxis()->SetTitle("#it{L}_{p} (fm)");
    tg->GetXaxis()->SetTitle("#it{#nu} (GeV)");
    tg->GetXaxis()->SetTitleOffset(1.1);
    tg->SetMaximum(yMax); 
    tg->SetMinimum(yMin); 
    tg->GetXaxis()->SetLimits(xMin,xMax);
    tg->GetXaxis()->CenterTitle();
    tg->GetYaxis()->CenterTitle();
    tg->SetLineWidth(2);
    return tg;
}

void PlotEstimations(const double xBj = 0.04) {
    SetAtlasStyle(43,22);

    TF1 *LogLund1 = new TF1("LogLund","((0.938 + 2*x)/(2*[1]))*[0]*(log(1/([0]*[0]))-1+[0]*[0])/(1-[0]*[0])",0,140); // LogLund(nu)
    TF1 *LogLund2 = new TF1("LogLund","((0.938 + 2*x)/(2*[1]))*[0]*(log(1/([0]*[0]))-1+[0]*[0])/(1-[0]*[0])",0,140); // LogLund(nu)
    TF1 *LogLund3 = new TF1("LogLund","((0.938 + 2*x)/(2*[1]))*[0]*(log(1/([0]*[0]))-1+[0]*[0])/(1-[0]*[0])",0,140); // LogLund(nu)
    TF1 *LogLund4 = new TF1("LogLund","((0.938 + 2*x)/(2*[1]))*[0]*(log(1/([0]*[0]))-1+[0]*[0])/(1-[0]*[0])",0,140); // LogLund(nu)

    LogLund1->SetParameter(0,0.32);
    LogLund2->SetParameter(0,0.53);
    LogLund3->SetParameter(0,0.75);
    LogLund4->SetParameter(0,0.94);

    LogLund1->SetParameter(1, 1.0); // kappa as in standard lund string model
    LogLund2->SetParameter(1, 1.0); // kappa as in standard lund string model
    LogLund3->SetParameter(1, 1.0); // kappa as in standard lund string model
    LogLund4->SetParameter(1, 1.0); // kappa as in standard lund string model

    LogLund1->SetLineColor(kRed+1);
    LogLund2->SetLineColor(kRed+1);
    LogLund3->SetLineColor(kRed+1);
    LogLund4->SetLineColor(kRed+1);


    TF1 *fg1 = new TF1("fg1","1/(2*[0]) * ((1-[2])*([1] + 2*x) - TMath::Power([3],2)/([2]*([1] + 2*x)))",0,140);
    TF1 *fg2 = new TF1("fg2","1/(2*[0]) * ((1-[2])*([1] + 2*x) - TMath::Power([3],2)/([2]*([1] + 2*x)))",0,140);
    TF1 *fg3 = new TF1("fg3","1/(2*[0]) * ((1-[2])*([1] + 2*x) - TMath::Power([3],2)/([2]*([1] + 2*x)))",0,140);
    TF1 *fg4 = new TF1("fg4","1/(2*[0]) * ((1-[2])*([1] + 2*x) - TMath::Power([3],2)/([2]*([1] + 2*x)))",0,140);
    // fg1->SetParName(0, "KAPPA");
    // fg1->SetParName(1, "MP");
    // fg1->SetParName(2, "z");
    // fg1->SetParName(3, "mT");

    fg1->SetParameter(0, 1);
    fg1->FixParameter(1, 0.938);
    fg1->FixParameter(2, 0.32);
    fg1->FixParameter(3, 0.14);

    fg2->SetParameter(0, 1);
    fg2->FixParameter(1, 0.938);
    fg2->FixParameter(2, 0.53);
    fg2->FixParameter(3, 0.14);

    fg3->SetParameter(0, 1);
    fg3->FixParameter(1, 0.938);
    fg3->FixParameter(2, 0.75);
    fg3->FixParameter(3, 0.14);

    fg4->SetParameter(0, 1);
    fg4->FixParameter(1, 0.938);
    fg4->FixParameter(2, 0.94);
    fg4->FixParameter(3, 0.14);

    fg1->SetLineColor(kAzure);
    fg2->SetLineColor(kAzure);
    fg3->SetLineColor(kAzure);
    fg4->SetLineColor(kAzure);
    fg1->SetLineStyle(kDashed);
    fg2->SetLineStyle(kDashed);
    fg3->SetLineStyle(kDashed);
    fg4->SetLineStyle(kDashed);

    cout << fg1->Eval(10) << endl;
    cout << fg1->Eval(100) << endl;

    cout << LogLund1->Eval(10) << endl;
    cout << LogLund1->Eval(100) << endl;

    TCanvas *c1 = new TCanvas("c1","Lp Estimations",1000,300);
    c1->SetLeftMargin(0.2);
    c1->SetBottomMargin(0.17);
    c1->Divide(4,1,0,0);

    c1->cd(1);
    auto b1 = ExtrapolationImproved(1);
    b1->Draw("AL");
    LogLund1->Draw("SAME");
    fg1->Draw("SAME");

    myText(0.28,0.25,kBlack,"#it{z} = 0.32",16);
    c1->cd(1)->SetLogy();

    c1->cd(2);
    auto b2 = ExtrapolationImproved(2);
    b2->Draw("AL");
    LogLund2->Draw("SAME");
    fg2->Draw("SAME");

    myText(0.15,0.27,kBlack,"#it{z} = 0.53",16);
    c1->cd(2)->SetLogy(); 

    c1->cd(3);
    auto b3 = ExtrapolationImproved(3);
    b3->Draw("AL");
    LogLund3->Draw("SAME");
    fg3->Draw("SAME");

    myText(0.15,0.27,kBlack,"#it{z} = 0.75",16);
    c1->cd(3)->SetLogy(); 

    c1->cd(4);
    auto b4 = ExtrapolationImproved(4);
    b4->Draw("AL");
    LogLund4->Draw("SAME");
    fg4->Draw("SAME");

    myText(0.15,0.27,kBlack,"#it{z} = 0.94",16);
    c1->cd(4)->SetLogy(); 

    myLineText(0.15, 0.88, 0.06, kRed+1, "Lund String Model (Bialas et. al.)", 1, 14);
    myLineText(0.15, 0.80, 0.06, kAzure, "Lund String Model (Struck quark)", kDashed, 14);
    myLineText(0.15, 0.72, 0.06, kBlack, "Relativistic Extrapolation", 1, 14);
    // myText(0.25,0.9,kBlack,"#it{z} = 0.94, #it{x}_{B} = 0.2",0.04);
    // myBoxText(0.15,0.82,0.05,kBlue,"Lund String Model",kBlack,2,3444,16);
    // myBoxText(0.15,0.76,0.05,kRed,"Relativistic Extrapolation",kBlack,2,3444,16);

    c1->SaveAs("PlotEstimationsImproved.pdf");
}
