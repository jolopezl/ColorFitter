#define PROTON_MASS 0.938 // PDG value in GeV^2

std::pair<TF1*,TGraphAsymmErrors*> GetFunctionAndBand_LSM(const double kappa = 1.0, const double zh = 0.94, const double xBj = 0.2) {
    // [0] Kappa
    // [1] Proton mass
    // [2] z
    // [3] xBj
    TF1 *fcn = new TF1("fcn","1/[0]*(0.5*[1] + x*(1 - [2]) + 0.5*x*(TMath::Sqrt(1 + 2*[1]*[3]/x) - 1))",2,150);
    TF1 *fcn_up = new TF1("fcn_up","1/[0]*(0.5*[1] + x*(1 - [2]) + 0.5*x*(TMath::Sqrt(1 + 2*[1]*[3]/x) - 1))",2,150);
    TF1 *fcn_down = new TF1("fcn_down","1/[0]*(0.5*[1] + x*(1 - [2]) + 0.5*x*(TMath::Sqrt(1 + 2*[1]*[3]/x) - 1))",2,150);
    fcn->SetParameter(0, kappa);
    fcn->SetParameter(1, PROTON_MASS);
    fcn->SetParameter(2, zh);
    fcn->SetParameter(3, xBj);
    fcn_up->SetParameter(0, kappa);
    fcn_up->SetParameter(1, PROTON_MASS); 
    fcn_up->SetParameter(2, zh);
    fcn_up->SetParameter(3, xBj + 0.1);
    fcn_down->SetParameter(0, kappa);
    fcn_down->SetParameter(1, PROTON_MASS);
    fcn_down->SetParameter(2, zh);
    fcn_down->SetParameter(3, xBj - 0.1);
    // fcn_up->Draw("SAME");
    // fcn_down->Draw("SAME");
    const int np = 1000;
    TGraphErrors *g0 = new TGraphErrors(np);
    TGraphErrors *g1 = new TGraphErrors(np);
    TGraphErrors *g2 = new TGraphErrors(np);
    double step = (150 - 2)/(double)np;
    double xnu = 2;
    for (int i=0; i<np; ++i) {
        xnu = xnu + i*step;
        g0->SetPoint(i, xnu, fcn->Eval(xnu));
        g1->SetPoint(i, xnu, fcn_up->Eval(xnu));
        g2->SetPoint(i, xnu, fcn_down->Eval(xnu));
        g0->SetPointError(i, 0, 0);
        g1->SetPointError(i, 0, 0);
        g2->SetPointError(i, 0, 0);
    }
    TGraphAsymmErrors *bb = myMakeBand(g0,g1,g2);
    fcn->SetLineColor(kAzure);
    bb->SetFillColorAlpha(kAzure, 0.5);
    return std::make_pair(fcn, bb);
}

std::pair<TF1*,TGraphAsymmErrors*> GetFunctionAndBand(const int zbin = 4, const double xBj = 0.2) {

    std::map<int,double> factor;
    // m ~ sqrt(Q2)
    factor[1] = 9.24;
    factor[2] = 8.40;
    factor[3] = 7.94;
    factor[4] = 7.14;
    // m ~ log (Q2)
    // factor[1] = 16.41;
    // factor[2] = 14.93;
    // factor[3] = 14.12;
    // factor[4] = 13.52;
    std::map<int,double> lp;
    lp[1] = 6.93319;//8.156268928;
    lp[2] = 4.95501;//6.11454026;
    lp[3] = 2.79043;//4.45823924;
    lp[4] = 1.38668;//2.352734198;
    std::map<int,double> lpErr;
    lpErr[1] = 2.47533;
    lpErr[2] = 1.42262;
    lpErr[3] = 1.0399;
    lpErr[4] = 1.02507;
    // [0] l0/beta0gamma0
    // [1] proton mass
    // [2] xBj
    TF1 *fcnRel = new TF1("fcnRel","[0]*TMath::Sqrt(x/(2*[1]*[2]) - 1)",2,150);
    TF1 *fcnRel_up = new TF1("fcnRel_up","[0]*TMath::Sqrt(x/(2*[1]*[2]) - 1)",2,150);
    TF1 *fcnRel_down = new TF1("fcnRel_down","[0]*TMath::Sqrt(x/(2*[1]*[2]) - 1)",2,150);
    fcnRel->SetParName(0, "coeff");
    fcnRel->SetParName(1, "Mp");
    fcnRel->SetParName(2, "xBj");
    fcnRel->SetParameter(0, lp[zbin]/factor[zbin]); // from estimatiosn file in Excel
    fcnRel->SetParameter(1, 0.938); // PDG value in GeV^2
    fcnRel->SetParameter(2, xBj);

    fcnRel_up->SetParName(0, "coeff");
    fcnRel_up->SetParName(1, "Mp");
    fcnRel_up->SetParName(2, "xBj");
    fcnRel_up->SetParameter(0, lp[zbin]/factor[zbin]); // from estimatiosn file in Excel
    // fcnRel_up->SetParameter(0, (lp[zbin] + lpErr[zbin])/factor[zbin]); // from estimatiosn file in Excel
    fcnRel_up->SetParameter(1, 0.938); // PDG value in GeV^2
    fcnRel_up->SetParameter(2, xBj + 0.1);

    fcnRel_down->SetParName(0, "coeff");
    fcnRel_down->SetParName(1, "Mp");
    fcnRel_down->SetParName(2, "xBj");
    fcnRel_down->SetParameter(0, 2.35/7.05); // from estimatiosn file in Excel
    fcnRel_down->SetParameter(0, lp[zbin]/factor[zbin]); // from estimatiosn file in Excel
    // fcnRel_down->SetParameter(0, (lp[zbin] - lpErr[zbin])/factor[zbin]); // from estimatiosn file in Excel
    fcnRel_down->SetParameter(1, 0.938); // PDG value in GeV^2
    fcnRel_down->SetParameter(2, xBj - 0.1);
    const int np = 1000;
    TGraphErrors *g0 = new TGraphErrors(np);
    TGraphErrors *g1 = new TGraphErrors(np);
    TGraphErrors *g2 = new TGraphErrors(np);
    double step = (150 - 2)/(double)np;
    double xnu = 2;
    for (int i=0; i<np; ++i) {
        xnu = xnu + i*step;
        g0->SetPoint(i, xnu, fcnRel->Eval(xnu));
        g1->SetPoint(i, xnu, fcnRel_up->Eval(xnu));
        g2->SetPoint(i, xnu, fcnRel_down->Eval(xnu));
        g0->SetPointError(i, 0, 0);
        g1->SetPointError(i, 0, 0);
        g2->SetPointError(i, 0, 0);
    }
    TGraphAsymmErrors *bbRel = myMakeBand(g0,g1,g2);
    fcnRel->SetLineColor(kBlack);
    bbRel->SetFillColorAlpha(kBlack,0.5);
    return std::make_pair(fcnRel, bbRel);
}

void PlotEstimations(const double xBj = 0.2) {
    SetAtlasStyle(43,22);
    const double string = 1;

    double yMin=0.6, yMax=80;

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
    auto bl = GetFunctionAndBand(1,xBj);
    bl.second->Draw("A3");
    bl.second->GetYaxis()->SetTitle("L_{p} [fm]");
    bl.second->GetXaxis()->SetTitle("#nu [GeV]");
    bl.second->GetXaxis()->SetTitleOffset(1.1);
    bl.second->SetMaximum(yMax); 
    bl.second->SetMinimum(yMin); 
    bl.second->GetXaxis()->SetLimits(0.01,109);
    bl.second->GetXaxis()->SetNdivisions(505);
    bl.second->GetYaxis()->CenterTitle();
    bl.second->GetXaxis()->CenterTitle();
    bl.first->Draw("SAME");

    LogLund1->Draw("SAME");
    fg1->Draw("SAME");

    myText(0.28,0.25,kBlack,"z = 0.32, x_{B} = 0.2 #pm 0.1",16);
    c1->cd(1)->SetLogy();

    c1->cd(2);
    bl = GetFunctionAndBand(2,xBj);
    bl.second->Draw("A3");
    bl.second->GetYaxis()->SetTitle("L_{p} [fm]");
    bl.second->GetXaxis()->SetTitle("#nu [GeV]");
    bl.second->GetXaxis()->SetTitleOffset(1.1);
    bl.second->SetMaximum(yMax); 
    bl.second->SetMinimum(yMin); 
    bl.second->GetXaxis()->SetLimits(0.01,109);
    bl.second->GetXaxis()->SetNdivisions(505);
    bl.second->GetXaxis()->CenterTitle();
    bl.second->GetXaxis()->CenterTitle();
    bl.first->Draw("SAME");

    LogLund2->Draw("SAME");
    fg2->Draw("SAME");

    myText(0.15,0.27,kBlack,"z = 0.53, x_{B} = 0.2 #pm 0.1",16);
    c1->cd(2)->SetLogy(); 

    c1->cd(3);
    bl = GetFunctionAndBand(3,xBj);
    bl.second->Draw("A3");
    bl.second->GetYaxis()->SetTitle("L_{p} [fm]");
    bl.second->GetXaxis()->SetTitle("#nu [GeV]");
    bl.second->GetXaxis()->SetTitleOffset(1.1);
    bl.second->SetMaximum(yMax); 
    bl.second->SetMinimum(yMin); 
    bl.second->GetXaxis()->SetLimits(0.01,109);
    bl.second->GetXaxis()->SetNdivisions(505);
    bl.second->GetXaxis()->CenterTitle();
    bl.second->GetXaxis()->CenterTitle();
    bl.first->Draw("SAME");

    LogLund3->Draw("SAME");
    fg3->Draw("SAME");

    myText(0.15,0.27,kBlack,"z = 0.75, x_{B} = 0.2 #pm 0.1",16);
    c1->cd(3)->SetLogy(); 

    c1->cd(4);
    bl = GetFunctionAndBand(4,xBj);
    bl.second->Draw("A3");
    bl.second->GetYaxis()->SetTitle("L_{p} [fm]");
    bl.second->GetXaxis()->SetTitle("#nu [GeV]");
    bl.second->GetXaxis()->SetTitleOffset(1.1);
    bl.second->SetMaximum(yMax); 
    bl.second->SetMinimum(yMin); 
    bl.second->GetXaxis()->SetLimits(0.01,109);
    bl.second->GetXaxis()->SetNdivisions(505);
    bl.second->GetXaxis()->CenterTitle();
    bl.second->GetXaxis()->CenterTitle();
    bl.first->Draw("SAME");

    LogLund4->Draw("SAME");
    fg4->Draw("SAME");

    myText(0.15,0.27,kBlack,"z = 0.94, x_{B} = 0.2 #pm 0.1",16);
    c1->cd(4)->SetLogy(); 

    myLineText(0.15, 0.88, 0.06, kRed+1, "Lund String Model (Bialas et. al.)", 1, 14);
    myLineText(0.15, 0.80, 0.06, kAzure, "Lund String Model (struck quark)", kDashed, 14);
    myLineText(0.15, 0.72, 0.06, kBlack, "Relativistic Extrapolation", 1, 14);
    // myText(0.25,0.9,kBlack,"z = 0.94, x_{B} = 0.2",0.04);
    // myBoxText(0.15,0.82,0.05,kBlue,"Lund String Model",kBlack,2,3444,16);
    // myBoxText(0.15,0.76,0.05,kRed,"Relativistic Extrapolation",kBlack,2,3444,16);

    c1->SaveAs("PlotEstimations.pdf");
}
