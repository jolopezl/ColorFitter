#define PROTON_MASS 0.938 // PDG value in GeV^2

std::pair<TF1*,TGraphAsymmErrors*> GetFunctionAndBand_LSM(const double kappa = 1.0, const double zh = 0.94, const double xBj = 0.2) {
    // [0] Kappa
    // [1] Proton mass
    // [2] z
    // [3] xBj
    TF1 *fcn = new TF1("fcn","1/[0]*(0.5*[1] + (x/(2*[1]*[3]))*(1 - [2]) + 0.5*(x/(2*[1]*[3]))*(TMath::Sqrt(1 + 2*[1]*[3]/(x/(2*[1]*[3]))) - 1))",1,30);
    TF1 *fcn_up = new TF1("fcn_up","1/[0]*(0.5*[1] + (x/(2*[1]*[3]))*(1 - [2]) + 0.5*(x/(2*[1]*[3]))*(TMath::Sqrt(1 + 2*[1]*[3]/(x/(2*[1]*[3]))) - 1))",1,30);
    TF1 *fcn_down = new TF1("fcn_down","1/[0]*(0.5*[1] + (x/(2*[1]*[3]))*(1 - [2]) + 0.5*(x/(2*[1]*[3]))*(TMath::Sqrt(1 + 2*[1]*[3]/(x/(2*[1]*[3]))) - 1))",1,30);
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
    double step = (30 - 1.1)/(double)np;
    double xnu = 1.1;
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
    factor[1] = 9.31;
    factor[2] = 8.40;
    factor[3] = 7.94;
    factor[4] = 7.05;
    std::map<int,double> lp;
    lp[1] = 8.156268928;
    lp[2] = 6.11454026;
    lp[3] = 4.45823924;
    lp[4] = 2.352734198;
    std::map<int,double> lpErr;
    lpErr[1] = 1.755056688;
    lpErr[2] = 0.9419261488;
    lpErr[3] = 0.7686297028;
    lpErr[4] = 0.4509430001;
    // [0] l0/beta0gamma0
    // [1] proton mass
    // [2] xBj
    TF1 *fcnRel = new TF1("fcnRel","[0]*TMath::Sqrt(x/(4*TMath::Power([1],2)*TMath::Power([2],2)) - 1)",1.1,30);
    TF1 *fcnRel_up = new TF1("fcnRel_up","[0]*TMath::Sqrt(x/(4*TMath::Power([1],2)*TMath::Power([2],2)) - 1)",1.1,30);
    TF1 *fcnRel_down = new TF1("fcnRel_down","[0]*TMath::Sqrt(x/(4*TMath::Power([1],2)*TMath::Power([2],2)) - 1)",1.1,30);

    fcnRel->SetParameter(0, lp[zbin]/factor[zbin]); // from estimatiosn file in Excel
    // fcnRel->SetParameter(0, 4.46/7.94); // from estimatiosn file in Excel
    fcnRel->SetParameter(1, 0.938); // PDG value in GeV^2
    fcnRel->SetParameter(2, xBj);

    fcnRel_up->SetParameter(0, lp[zbin]/factor[zbin]); // from estimatiosn file in Excel
    // fcnRel_up->SetParameter(0, (lp[zbin] + lpErr[zbin])/factor[zbin]); // from estimatiosn file in Excel
    fcnRel_up->SetParameter(1, 0.938); // PDG value in GeV^2
    fcnRel_up->SetParameter(2, xBj + 0.1);

    fcnRel_down->SetParameter(0, lp[zbin]/factor[zbin]); // from estimatiosn file in Excel
    // fcnRel_down->SetParameter(0, (lp[zbin] - lpErr[zbin])/factor[zbin]); // from estimatiosn file in Excel
    fcnRel_down->SetParameter(1, 0.938); // PDG value in GeV^2
    fcnRel_down->SetParameter(2, xBj - 0.1);
    const int np = 1000;
    TGraphErrors *g0 = new TGraphErrors(np);
    TGraphErrors *g1 = new TGraphErrors(np);
    TGraphErrors *g2 = new TGraphErrors(np);
    double step = (30 - 2)/(double)np;
    double xnu = 1.1;
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
    fcnRel->SetLineColor(kRed+1);
    bbRel->SetFillColorAlpha(kRed+1,0.5);
    return std::make_pair(fcnRel, bbRel);
}

void PlotEstimations_forQ2(const double xBj = 0.2) {
    SetAtlasStyle(43,22);

    const double string = 1;

    double yMin=0.5, yMax=80;


    TCanvas *c1 = new TCanvas("c1","Lp Estimations",1000,300);
    c1->SetLeftMargin(0.2);
    c1->SetBottomMargin(0.17);

    c1->Divide(4,1,0,0);

    c1->cd(1);
    auto bl = GetFunctionAndBand(1,xBj);
    bl.second->Draw("A3");
    bl.second->GetYaxis()->SetTitle("L_{p} [fm]");
    bl.second->GetXaxis()->SetTitle("Q^{2} [GeV^{2}]");
    bl.second->GetXaxis()->SetTitleOffset(1.1);
    bl.second->SetMaximum(yMax); 
    bl.second->SetMinimum(yMin); 
    bl.second->GetXaxis()->SetLimits(1.1,29.9);
    bl.second->GetYaxis()->CenterTitle();
    bl.second->GetXaxis()->CenterTitle();
    bl.first->Draw("SAME");
    auto lund = GetFunctionAndBand_LSM(string, 0.32,xBj);
    lund.second->Draw("3");
    lund.first->Draw("SAME");

    myText(0.28,0.25,kBlack,"z_{h} = 0.32, x_{B} = 0.2 #pm 0.1",16);
    c1->cd(1)->SetLogy(); 

    c1->cd(2);
    bl = GetFunctionAndBand(2,xBj);
    bl.second->Draw("A3");
    bl.second->GetYaxis()->SetTitle("L_{p} [fm]");
    bl.second->GetXaxis()->SetTitle("Q^{2} [GeV^{2}]");
    bl.second->GetXaxis()->SetTitleOffset(1.1);
    bl.second->SetMaximum(yMax); 
    bl.second->SetMinimum(yMin); 
    bl.second->GetXaxis()->SetLimits(1.1,29.9);
    bl.second->GetYaxis()->CenterTitle();
    bl.second->GetXaxis()->CenterTitle();
    bl.first->Draw("SAME");
    lund = GetFunctionAndBand_LSM(string, 0.53, xBj);
    lund.second->Draw("3");
    lund.first->Draw("SAME");

    myText(0.15,0.25,kBlack,"z_{h} = 0.53, x_{B} = 0.2 #pm 0.1",16);
    c1->cd(2)->SetLogy(); 

    c1->cd(3);
    bl = GetFunctionAndBand(3,xBj);
    bl.second->Draw("A3");
    bl.second->GetYaxis()->SetTitle("L_{p} [fm]");
    bl.second->GetXaxis()->SetTitle("Q^{2} [GeV^{2}]");
    bl.second->GetXaxis()->SetTitleOffset(1.1);
    bl.second->SetMaximum(yMax); 
    bl.second->SetMinimum(yMin); 
    bl.second->GetXaxis()->SetLimits(1.1,29.9);
    bl.second->GetYaxis()->CenterTitle();
    bl.second->GetXaxis()->CenterTitle();
    bl.first->Draw("SAME");
    lund = GetFunctionAndBand_LSM(string, 0.75, xBj);
    lund.second->Draw("3");
    lund.first->Draw("SAME");

    myText(0.15,0.25,kBlack,"z_{h} = 0.75, x_{B} = 0.2 #pm 0.1",16);
    c1->cd(3)->SetLogy(); 

    c1->cd(4);
    bl = GetFunctionAndBand(4,xBj);
    bl.second->GetYaxis()->SetTitle("L_{p} [fm]");
    bl.second->GetXaxis()->SetTitle("Q^{2} [GeV^{2}]");
    bl.second->GetXaxis()->SetTitleOffset(1.1);
    bl.second->SetMaximum(yMax); 
    bl.second->SetMinimum(yMin); 
    bl.second->GetXaxis()->SetLimits(1.1,29.9);
    bl.second->GetYaxis()->CenterTitle();
    bl.second->GetXaxis()->CenterTitle();
    bl.second->Draw("A3");    
    bl.first->Draw("SAME");
    lund = GetFunctionAndBand_LSM(string, 0.94, xBj);
    lund.second->Draw("3");
    lund.first->Draw("SAME");

    myText(0.15,0.25,kBlack,"z_{h} = 0.94, x_{B} = 0.2 #pm 0.1",16);
    c1->cd(4)->SetLogy(); 

    myLineText(0.15, 0.88, 0.06, kAzure, "Lund String Model", 1, 16);
    myLineText(0.15, 0.80, 0.06, kRed+1, "Relativistic Extrapolation", 1, 16);

    // myText(0.25,0.9,kBlack,"z_{h} = 0.94, x_{B} = 0.2",0.04);
    // myBoxText(0.15,0.82,0.05,kBlue,"Lund String Model",kBlack,1,3444,16);
    // myBoxText(0.15,0.76,0.05,kRed,"Relativistic Extrapolation",kBlack,1,3444,16);

    c1->SaveAs("PlotEstimations_forQ2.pdf");
}
