#include "main.h"
#include "MultiGaus.h"
#include <TMatrixD.h>
#include <TVectorD.h>
#include <TF2.h>
#include <TH2.h>

#define RUN 1

int demoPlots(); // Do plots and studies of the model
int demoPlots2D(); // Do fancier plots and studies of the model
int computeSimpleFit(const bool, const bool, const double);                           // A simple fits trusted.
int computeSimpleFit2(const std::string, const bool, const double);
int computeComplexFit(int argc, char *argv[]);    // A fit with a complex configuration
int printInteractionPoints();

double fcn_gaus_2d_cov(double *x, double *par);
int ComputeBand(int);

int average_density();
int plotTool();
int monitoring();


// ************ main function ************ //
int main(int argc, char *argv[]) {
    // demoPlots();
    // printInteractionPoints();
    // ********  EnergyLoss, Subtraction, Correlation                  
    // computeSimpleFit(true, true, 0.0);
    // computeSimpleFit(true, true,  0.0);
    // computeSimpleFit(true, true, -0.5);
    // computeSimpleFit(true, true, -1.0);
    // ComputeBand();
    // demoPlots();
    // int foo = average_density();
    // computeSimpleFit(false,true,0.0);
    // MODEL TYPE, do subtraction, value
    // computeSimpleFit2(argv[1], true, -1.0);
    long conv = strtol(argv[1], nullptr, 10);
    // long nn = strtol(argv[2], nullptr,10);
    ComputeBand(conv);
    
    // computeSimpleFit2("BL30",  true, 0.0);
    // computeSimpleFit2("BL35",  true, 0.0);
    // computeSimpleFit2("BL40",  true, 0.0);
    // computeSimpleFit2("BLE",   true, 0.0);
    // computeSimpleFit2("BLE30", true, 0.0);
    // computeSimpleFit2("BLE35", true, 0.0);
    // computeSimpleFit2("BLE40", true, 0.0);
    // computeSimpleFit2("BL", true, 0.0);
    // monitoring();
}

int monitoring() {
    Model *model = new Model("Monitoring");
    model->DoMonitoring(true);
    model->Initialization();
    // model->DoFixedLp(true);
    model->DoEnergyLoss(false);
    model->SetMaxMonteCarloSteps(1e5); // 1e6, 1e7
    model->MonitoringStart();
    double q0_values[4] = {2.21,2.57,1.15,1.19};
    double lp_values[4] = {8.15,6.11,4.45,2.35};
    double A[3];
    A[0] = 20.1797; // Ne
    A[1] = 83.7980; // Kr
    A[2] = 131.293; // Xe
    for (int zbin=0; zbin<4; ++zbin) {
        model->defineZbin(zbin+1);
        model->SetParameters("q0", q0_values[zbin]);
        model->SetParameters("lp", lp_values[zbin]);
        model->SetParameters("sigma", 30.);
        for (int i=0; i<3; ++i) {
            std::cout << "Calling A = " << A[i] << std::endl;
            model->Compute(A[i]);
        }
    }
    model->MonitoringFinish();
    return 0;
}

int plotTool() {
    myConfig *config = new myConfig();
    config->m_subtraction = true;
    config->m_correlation = -0.5;
    config->correctionPlots = true;
    auto fc = dataHandler(config);
    //int foo = average_density();
    //computeSimpleFit(false,true,0.0);
    // MODEL TYPE, do subtraction, value
    computeSimpleFit2("BL", true, 0.0);
    return 0;
}

int computeSimpleFit2(const std::string model, const bool iSubt, const double iCorr) {
    myConfig *config = new myConfig();
    int Q2Int = -1;
    int izInt = -1; // 4 for bin #83
    config->m_subtraction = iSubt; // false;
    config->m_correlation = iCorr; // for physics -1.0 < rho < 0.0

    config->fixedLp = false;
    if (config->fixedLp == true) {
        config->m_output_fit = "testFit"+model+".fixedLp.csv";
    }
    else {
        config->m_output_fit = "testFit"+model+".csv";
    }

    if (model == "BLC") {
       config->m_output_fit = "testFit"+model+".csv";
       config->m_cascade = true;
//        if (config->fixedLp == true) "testFit"+model+"fixedLp.csv";
    }
    else if (model == "BL40") {
        config->m_preh = false;
        config->m_initial_sigma = 40.0;
    }
    else if (model == "BL30") {
        config->m_preh = false;
        config->m_initial_sigma = 30.0;
    }
    else if (model == "BL35") {
        config->m_preh = false;
        config->m_initial_sigma = 35.0;
    }
    else if (model == "BL30C") {
        config->m_preh = false;
        config->m_initial_sigma = 30.0;
        config->m_cascade = true;
    }
    else if (model == "BLE") {
        config->m_energyloss = true;
    }
    else if (model == "BLE40") {
        config->m_preh = false;
        config->m_initial_sigma = 40.0;
        config->m_energyloss = true;
    }
    else if (model == "BLE30") {
        config->m_preh = false;
        config->m_initial_sigma = 30.0;
        config->m_energyloss = true;
    }
    else if (model == "BLE35") {
        config->m_preh = false;
        config->m_initial_sigma = 35.0;
        config->m_energyloss = true;
    }
    else if (model == "BL") {
        config->m_preh = true;
        config->m_initial_sigma = 30.0;
        config->m_energyloss = false;
    }
    else {return -1;}
    config->m_Q2BinOfInterest   = Q2Int; // value in between 1 and Q2DIM of Q2,x bins. -1 fits all.
    config->m_zBinOfInterest    = izInt; // value in between 1 and ZDIM of z bins. -1 fits all.
    config->m_input_pt          = "hermesData.txt";
    config->writeCorrectedValues = false; // text file from dataHandler
    config->correctionPlots      = false; // from dataHandler
    config->outputPlots          = true; // model and data
    config->doMINOSErrors        = false; // usually false
    config->Update();

    std::cout << "Running iFit now:" << std::endl;
    config->m_testing = false;
    std::vector<myResult> resultCont = ifit(config);

    std::cout << "Fit is done." << std::endl;

    const int fNzbins = 4; // 10 for JLab and 4 for HERMES !

    double z[fNzbins], q0[fNzbins], lp[fNzbins], sigma[fNzbins], dz[fNzbins], c1[fNzbins], c2[fNzbins], cascade[fNzbins];
    double zErr[fNzbins], q0Err[fNzbins], lpErr[fNzbins], sigmaErr[fNzbins], dzErr[fNzbins], c1Err[fNzbins], c2Err[fNzbins], cascade_err[fNzbins];
    double chisquared[fNzbins];
    if (resultCont.size() != fNzbins) {
        std::cout << "I cannot produce a ROOT output file." << std::endl;
        return 0;
    }
    else {
        std::cout << "I will produce a ROOT out file..." << std::endl;
        for (int i=0; i<fNzbins; ++i) {
            std::cout << "Fetching result container for element " << i << std::endl;
            z[i] = resultCont.at(i).m_zbin;         zErr[i] = 0;
            q0[i] = resultCont.at(i).m_qhat;        q0Err[i] = resultCont.at(i).m_qhat_err;
            lp[i] = resultCont.at(i).m_lp;          lpErr[i] = resultCont.at(i).m_lp_err;
            sigma[i] = resultCont.at(i).m_sigma_ph; sigmaErr[i] = resultCont.at(i).m_sigma_ph_err;
            dz[i] = resultCont.at(i).m_dz;          dzErr[i] = resultCont.at(i).m_dz_err;
            c1[i] = resultCont.at(i).m_c1;          c1Err[i] = resultCont.at(i).m_c1_err;
            c2[i] = resultCont.at(i).m_c2;          c2Err[i] = resultCont.at(i).m_c2_err;
            cascade[i] = resultCont.at(i).m_cascade;          cascade_err[i] = resultCont.at(i).m_cascade;
            chisquared[i] = resultCont.at(i).m_chi2;
            std::cout << "z = " << z[i] << std::endl;
        }
        std::string ffout = "OutputROOT.20180806."+model+".root";
        TFile *OutputROOT = new TFile(ffout.c_str(), "RECREATE");
        std::cout << "Output file created" << std::endl;
        OutputROOT->cd();
        std::cout << "Making plots of everything" << std::endl;
        TGraphErrors *tg_q0 = new TGraphErrors(fNzbins, z, q0, zErr, q0Err); tg_q0->SetName("tg_q0"); tg_q0->SetTitle(";z;q_{0} [GeV^{2}fm^{2}]");
        TGraphErrors *tg_lp = new TGraphErrors(fNzbins, z, lp, zErr, lpErr); tg_lp->SetName("tg_lp"); tg_lp->SetTitle(";z;L_{p} [fm]");
        TGraphErrors *tg_sigma = new TGraphErrors(fNzbins, z, sigma, zErr, sigmaErr); tg_sigma->SetName("tg_sigma"); tg_sigma->SetTitle(";z;#sigma [mbarn]");
        TGraphErrors *tg_dz = new TGraphErrors(fNzbins, z, dz, zErr, dzErr); tg_dz->SetName("tg_dz");
        TGraphErrors *tg_c1 = new TGraphErrors(fNzbins, z, c1, zErr, c1Err); tg_c1->SetName("tg_c1");
        TGraphErrors *tg_c2 = new TGraphErrors(fNzbins, z, c2, zErr, c2Err); tg_c2->SetName("tg_c2");
        TGraphErrors *tg_cascade = new TGraphErrors(fNzbins, z, cascade, zErr, cascade_err); tg_cascade->SetName("tg_cascade");
        TGraph *tg_chisquared = new TGraph(fNzbins, z, chisquared); tg_chisquared->SetName("tg_chisquared");
        std::cout << "Writing first set of plots" << std::endl;
        tg_q0->Write();
        tg_lp->Write();
        tg_sigma->Write();
        tg_dz->Write();
        tg_c1->Write();
        tg_c2->Write();
        tg_cascade->Write();
        tg_chisquared->Write();
        std::cout << "Creating model plots" << std::endl;
        TGraphErrors *tg_model_pT[fNzbins];
        TGraphErrors *tg_model_Rm[fNzbins];
        TGraphErrors *tg_model_pT_extrapolation[fNzbins];
        TGraphErrors *tg_model_pT_extrapolation_up[fNzbins];
        TGraphErrors *tg_model_pT_extrapolation_down[fNzbins];
        TGraphErrors *tg_model_Rm_extrapolation[fNzbins];
        TGraphErrors *tg_model_Rm_extrapolation_up[fNzbins];
        TGraphErrors *tg_model_Rm_extrapolation_down[fNzbins];
        std::string title = ";A^{1/3};#Delta#LTp_{t}^{2}#GT";
        for (int i=0; i<fNzbins; ++i) {
            std::cout << "Creating model plots for element " << i << std::endl;
            title = ";A^{1/3};#Delta#LTp_{t}^{2}#GT";
            tg_model_pT[i] = &(resultCont.at(i).m_tg_pT); tg_model_pT[i]->SetName(Form("tg_model_pT_%d",i)); tg_model_pT[i]->SetTitle(title.c_str());
            tg_model_pT_extrapolation[i] = &(resultCont.at(i).m_tg_pT_extrapolation); tg_model_pT_extrapolation[i]->SetName(Form("tg_model_pT_extrapolation_%d",i)); tg_model_pT_extrapolation[i]->SetTitle(title.c_str());
            tg_model_pT_extrapolation_up[i] = &(resultCont.at(i).m_tg_pT_extrapolation_up); tg_model_pT_extrapolation_up[i]->SetName(Form("tg_model_pT_extrapolation_up_%d",i)); tg_model_pT_extrapolation_up[i]->SetTitle(title.c_str());
            tg_model_pT_extrapolation_down[i] = &(resultCont.at(i).m_tg_pT_extrapolation_down); tg_model_pT_extrapolation_down[i]->SetName(Form("tg_model_pT_extrapolation_down_%d",i)); tg_model_pT_extrapolation_down[i]->SetTitle(title.c_str());
            
            title = ";A^{1/3};R_{M}";
            tg_model_Rm[i] = &(resultCont.at(i).m_tg_Rm); tg_model_Rm[i]->SetName(Form("tg_model_Rm_%d",i)); tg_model_Rm[i]->SetTitle(title.c_str());
            tg_model_Rm_extrapolation[i] = &(resultCont.at(i).m_tg_Rm_extrapolation); tg_model_Rm_extrapolation[i]->SetName(Form("tg_model_Rm_extrapolation_%d",i)); tg_model_Rm_extrapolation[i]->SetTitle(title.c_str());
            tg_model_Rm_extrapolation_up[i] = &(resultCont.at(i).m_tg_Rm_extrapolation_up); tg_model_Rm_extrapolation_up[i]->SetName(Form("tg_model_Rm_extrapolation_up_%d",i)); tg_model_Rm_extrapolation_up[i]->SetTitle(title.c_str());
            tg_model_Rm_extrapolation_down[i] = &(resultCont.at(i).m_tg_Rm_extrapolation_down); tg_model_Rm_extrapolation_down[i]->SetName(Form("tg_model_Rm_extrapolation_down_%d",i)); tg_model_Rm_extrapolation_down[i]->SetTitle(title.c_str());

            tg_model_pT[i]->Write();
            tg_model_Rm[i]->Write();
            tg_model_pT_extrapolation[i]->Write();
            tg_model_pT_extrapolation_up[i]->Write();
            tg_model_pT_extrapolation_down[i]->Write();
            tg_model_Rm_extrapolation[i]->Write();
            tg_model_Rm_extrapolation_up[i]->Write();
            tg_model_Rm_extrapolation_down[i]->Write();
        }
        std::cout << "Done." << std::endl;
        OutputROOT->Close();
    }
    return 0;
}


// **************** Compute a Simple Fit **************** //
int computeSimpleFit(const bool tEnergyLoss, const bool tSubtraction, const double tCorrelation) {
    myConfig *config = new myConfig();
    // bins of interest
    int Q2Int = -1;
    int izInt = -1;
    // defauls
    bool input_energyloss     = tEnergyLoss;
    bool input_subtraction    = tSubtraction;
    double input_correlation  = tCorrelation;
    config->m_energyloss        = input_energyloss;  // false;
    config->m_subtraction       = input_subtraction; // false;
    config->m_correlation       = input_correlation; // for physics -1.0 < rho < 0.0
    config->m_energylossWeighted = false;
    // Production lenght behaviour
    config->fixedLp = false;
    // Pre-hadron cross section
    config->m_preh              = false; // usually true
    config->m_initial_sigma     = 35.0;  // do it < 40 mbarns
    // more.
    config->m_Q2BinOfInterest   = Q2Int; // value in between 1 and Q2DIM of Q2,x bins. -1 fits all.
    config->m_zBinOfInterest    = izInt; // value in between 1 and ZDIM of z bins. -1 fits all.
    config->m_output_fit        = "testFit2p.csv";
    config->m_input_pt          = "hermesData.txt";
    config->writeCorrectedValues = false; // text file from dataHandler
    config->correctionPlots      = false; // from dataHandler
    config->outputPlots          = false; // model and data
    config->doMINOSErrors = false; // usually false
    config->Update();
    std::cout << "Running iFit now:" << std::endl;
    auto fitOutput = ifit(config);
    return 0;
}

// **** computations of the model **** //
double fcn_gaus_2d_cov(double *x, double *par) {
    /* par = q0, l, sigma_q0, sigma_l, correlation */
    TMatrixD SIGMA(2,2);
    TVectorD X(2);
    X(0) = x[0] - par[0];
    X(1) = x[1] - par[1];
    SIGMA(0,0) = pow(par[2],2);
    SIGMA(1,1) = pow(par[3],2);
    SIGMA(0,1) = par[2]*par[3]*par[4];
    SIGMA(1,0) = SIGMA(0,1);
    double det = SIGMA.Determinant();
    SIGMA.Invert();
    double ans = exp(-0.5*X*(SIGMA*X));
    ans /= 2*M_PI*sqrt(det);
    return ans;
}

int ComputeBand(int zbin = 1) {
    // x is A^1/3

    int MCSTEPS = 2500;
    std::cout << "ComputeBand will use " << MCSTEPS << " MCSTEPS" << std::endl;

    Model *model = new Model("ComputeBand");
    model->Initialization();
    model->DoFixedLp(false);
    model->DoEnergyLoss(true);

    // If not here, model returns a bug, it is set in ifit when running the fitting
    int iz = zbin-1;
    const int ZDIM = 4;
    double zbinw[ZDIM]     = {0.20,0.22,0.22,0.16}; // Approx.
    double binratios[ZDIM] = {0.482203,0.461464,0.249762,0}; // PI+ no cuts
    model->SetBinRatio(iz,zbinw[iz],binratios[iz]);

    int StatusCode;
    double PT2, RM;
    double A13 = 2.5;
    double A13Max = 6.0;
    double dA13 = (A13Max - 2.5)/70;
    double q0, lp, dz;

    // A13 = x/10.;
    int nabins = 70;
    
    TFile *fout = new TFile(Form("ToyMC_A13_%d_bin_%d.root",nabins,zbin),"RECREATE");
    TTree *tree = new TTree("tree", "Tree of ToyMC");
    tree->Branch("zbin", &zbin, "zbin/I");
    tree->Branch("A13", &A13, "A13/D");
    tree->Branch("PT2", &PT2, "PT2/D");
    tree->Branch("RM", &RM, "RM/D");
    tree->Branch("q0", &q0, "q0/D");
    tree->Branch("lp", &lp, "lp/D");
    tree->Branch("dz", &dz, "dz/D");
    tree->Branch("StatusCode", &StatusCode, "StatusCode/I");
    // Setup for the Toy MC with random generation
    int nDim = 3;
    TVectorD parMeans(nDim);
    TVectorD parErrors(nDim);
    TMatrixDSym covMatrix(nDim);
    TVectorD genPars(nDim);
    // Numbers obtained from fit to BLE30
    if (zbin == 1) {
        parMeans(0) = 2.32139e+00;
        parMeans(1) = 6.93319e+00;
        parMeans(2) = -6.16009e-04;
        parErrors(0) = 3.34446e-01;
        parErrors(1) = 2.47533e+00;
        parErrors(2) = 2.97718e-02;
        covMatrix(0,0) = parErrors(0)*parErrors(0); covMatrix(0,1) = -0.781*parErrors(0)*parErrors(1); covMatrix(0,2) = 0.738*parErrors(0)*parErrors(2);
        covMatrix(1,0) = covMatrix(0,1);            covMatrix(1,1) = parErrors(1)*parErrors(1);        covMatrix(1,2) = -0.945*parErrors(1)*parErrors(2);
        covMatrix(2,0) = covMatrix(0,2);            covMatrix(2,1) = covMatrix(1,2);                   covMatrix(2,2) = parErrors(2)*parErrors(2);
    }
    if (zbin == 2) {
        parMeans(0) = 2.78111e+00;
        parMeans(1) = 4.95501e+00;
        parMeans(2) = -1.82998e-02;
        parErrors(0) = 5.41974e-01;
        parErrors(1) = 1.42262e+00;
        parErrors(2) = 2.97642e-02;
        covMatrix(0,0) = parErrors(0)*parErrors(0); covMatrix(0,1) = -0.592*parErrors(0)*parErrors(1); covMatrix(0,2) = -0.563*parErrors(0)*parErrors(2);
        covMatrix(1,0) = covMatrix(0,1);            covMatrix(1,1) = parErrors(1)*parErrors(1);        covMatrix(1,2) = 0.951*parErrors(1)*parErrors(2);
        covMatrix(2,0) = covMatrix(0,2);            covMatrix(2,1) = covMatrix(1,2);                   covMatrix(2,2) = parErrors(2)*parErrors(2);
    }
    if (zbin == 3) {
        parMeans(0) = 1.45245e+00;
        parMeans(1) = 2.79043e+00;
        parMeans(2) = -3.88610e-02;
        parErrors(0) = 1.44045e+00;
        parErrors(1) = 1.03990e+00;
        parErrors(2) = 3.51889e-02;
        covMatrix(0,0) = parErrors(0)*parErrors(0); covMatrix(0,1) = -0.203*parErrors(0)*parErrors(1); covMatrix(0,2) = -0.196*parErrors(0)*parErrors(2);
        covMatrix(1,0) = covMatrix(0,1);            covMatrix(1,1) = parErrors(1)*parErrors(1);        covMatrix(1,2) = 0.963*parErrors(1)*parErrors(2);
        covMatrix(2,0) = covMatrix(0,2);            covMatrix(2,1) = covMatrix(1,2);                   covMatrix(2,2) = parErrors(2)*parErrors(2);
    }
    if (zbin ==4) {
        parMeans(0) = 1.71481e+00;
        parMeans(1) = 1.38668e+00;
        parMeans(2) = -2.39079e-02;
        parErrors(0) = 3.16320e+00;
        parErrors(1) = 1.02507e+00;
        parErrors(2) = 3.32699e-02;
        covMatrix(0,0) = parErrors(0)*parErrors(0); covMatrix(0,1) = -0.255*parErrors(0)*parErrors(1); covMatrix(0,2) = -0.250*parErrors(0)*parErrors(2);
        covMatrix(1,0) = covMatrix(0,1);            covMatrix(1,1) = parErrors(1)*parErrors(1);        covMatrix(1,2) = 0.978*parErrors(1)*parErrors(2);
        covMatrix(2,0) = covMatrix(0,2);            covMatrix(2,1) = covMatrix(1,2);                   covMatrix(2,2) = parErrors(2)*parErrors(2);
    }
    covMatrix.Print();
    TMatrixD invCovMatrix = covMatrix;
    double determinant;
    invCovMatrix.Invert(&determinant);
    std::cout << "Computign z-bin #" << zbin << std::endl;
    while (A13 <= A13Max) {
        PT2 = 0;
        RM = 0;
        double nucleus = pow(A13, 3);
        std::cout << "Running Toy MC for A^1/3 = " << A13 << std::endl;
        for (int mc=0; mc<MCSTEPS; ++mc) {
            if (mc%100 == 0) {std::cout << "MC Step = " << mc+1 << " of " << MCSTEPS << std:: endl;}
            while (true) {
                MultiGaus(parMeans, covMatrix, genPars);
                q0 = genPars(0);
                lp = genPars(1);
                dz = genPars(2);
                if (q0 > 0 && lp > 0) {
                     break;
                }
                // std::cout << "Searching for a new random set of parameters within the physics limits" << std::endl;
            }
            model->SetParameters("q0", q0);
            model->SetParameters("lp", lp);
            model->SetParameters("sigma", 30);
            model->SetParameters("dz", dz);
            StatusCode = model->Compute(nucleus);
            PT2 = model->Get1();
            RM = model->Get2();
            tree->Fill();
        }
        A13 += dA13; // go to next nucleus
    }
    tree->Write();
    fout->Close();
    return 0;
}


// *** prints interaction points *** //
int printInteractionPoints() {
    Model *model = new Model("InteractionPoints");
    model->Initialization();
    double x=0.,y=0.,z=0.;
    int A = 12;
    double A13 = pow(A,1/3.); // carbon
    double cutoff = 0.005;
    double R=model->GetR(A13,cutoff);
    std::cout << "Interaction Points for A = " << A << " density cutoff = " << cutoff << std::endl;
    for (int i = 0; i < 10; ++i) {
        model->InteractionPoint(x,y,z,R);
        std::cout << x << "\t" << y << "\t" << z << std::endl;
    }
    return 0;
}

int average_density() {
    Model *model = new Model("AverageDensityComputation");
    model->Initialization();
    model->SetParameters("lp", 3.1); // z=0.75
    float xxx[3];
    xxx[0]=pow(20.1797,1./3.); // Ne   here goes A^1/3
    xxx[1]=pow(83.7980,1./3.); // Kr
    xxx[2]=pow(131.293,1./3.); // Xe
    {
        int i = 2;
        std::cout << "A13 = " << xxx[i] << std::endl;
        model->Compute(xxx[i]);
    }
    return 0;
}

// ************ This is used for model plots ************ //
int demoPlots() {
    Model *model = new Model("demoPlots");
    model->Initialization();
    model->DoFixedLp(true); 
    model->SetParameters("q0", 1.0);
    // To run and produce full list of files at once.
    std::vector<double> lpList = {1.0,2.0,3.0,4.0,5.0,7.0,9.0,10.0,20.0};
    for (const auto &lp : lpList) {
        for (int nucleus = 12; nucleus <= 240; ++nucleus) {
            std::cout << "Computing " << nucleus << " of 240 for lp = " << lp << std::endl;
            model->SetParameters("lp", lp);   //* <------!!! *//
            model->Compute(nucleus);          //* <------!!! *//
            //* Print to file **//
            std::ofstream fout;
            std::string str = boost::lexical_cast<std::string>(lp);
            std::string filename = "input-exp-fixed-lp="+str+".txt";
            fout.open(filename, std::ios::out | std::ios::app);
            fout.precision(10);
            fout << pow(nucleus,1./3.) << '\t' << model->Get1() << '\n';
            fout.close();
        }
    }
    return 0;
    // std::vector<std::string> foo;
    // std::for_each(
    //     std::execution::par_unseq,
    //     foo.begin(),
    //     foo.end(),
    //     [](auto&& item)
    //     {
    //         //do stuff with item
    //     });
    // std::for_each(std::execution::par_unseq,lpList.begin(),lpList.end(),
    //     [](auto&& item) {
    //         for (int nucleus = 12; nucleus <= 240; ++nucleus) {
    //             std::cout << "Computing " << nucleus << " of 240 for lp = " << lp << std::endl;
    //             model->SetParameters("lp", lp);   //* <------!!! *//
    //             model->Compute(nucleus);          //* <------!!! *//
    //             //* Print to file **//
    //             std::ofstream fout;
    //             std::string str = boost::lexical_cast<std::string>(lp);
    //             std::string filename = "input-exp-lp="+str+".txt";
    //             fout.open(filename, std::ios::out | std::ios::app);
    //             fout.precision(10);
    //             fout << pow(nucleus,1./3.) << '\t' << model->Get1() << '\n';
    //             fout.close();
    //         }
    //     }
    // )
}

// ************ This is used for model plots ************ //
int demoPlots2D() {
    Model *model = new Model("demoPlots2D");
    model->Initialization();
    model->DoFixedLp(true);
    model->SetParameters("q0", 1.5);
    model->SetParameters("density threshold", 0.0005);
    float step_lp = (20.0-1.0)/25;
    int setp_nucl = (int)(240-12)/25;
    for (int nucleus = 12; nucleus <= 240; nucleus += setp_nucl) {
        for (float lp = 1.0; lp <= 20; lp += step_lp) {
            model->SetParameters("lp", lp);
            model->Compute(nucleus);
            std::cout << pow(nucleus,1./3.) << '\t' << lp << '\t' << model->Get1() << std::endl;
        }
    }
    return 0;
}

// **************** Compute a _fancy_ Fit **************** //
int computeComplexFit(int argc, char *argv[]) {
    myConfig *config = new myConfig();
    // bins to fit
    int Q2Int  = 1;
    int izInt  = 3;
    // defaults
    int input_energyloss  = 0;
    int input_subtraction = 1;
    double input_correlation = 0.0;
    int max_run = 1; 

    if (argc == 4) {
        input_energyloss  = std::stoi(argv[1]);
        input_subtraction = std::stoi(argv[2]);
        input_correlation = std::stod(argv[3]);
        max_run = std::stoi(argv[4]);
        config->m_special_run = true;
    }
    else if (argc == 3) {
        input_energyloss  = std::stoi(argv[1]);
        input_subtraction = std::stoi(argv[2]);
        input_correlation = std::stod(argv[3]);
        max_run = 1; 
        config->m_special_run = false;
    }
    else if (argc < 3) {
        // defaults
        input_energyloss  = 0;
        input_subtraction = 1;
        input_correlation = 0.0;
        max_run = 1; 
    }

    config->m_stat_only         = false;
    config->m_energyloss        = input_energyloss; // false;
    config->m_logbehavior       = false;
    config->m_fermimotion       = false;
    config->m_subtraction       = input_subtraction; // false;
    config->m_correlation       = input_correlation; // -1.0; // for physics -1.0 < rho < 0.0
    config->m_Q2BinOfInterest   = Q2Int;   // value in between 1 and Q2DIM of Q2,x bins. -1 fits all.
    config->m_zBinOfInterest    = izInt;   // value in between 1 and ZDIM of z bins. -1 fits all.
    config->m_output_fit        = "testFit.txt";
    config->m_input_pt          = "hermesData.txt";
    // config->Update();

    std::ostringstream foo;
    foo << "iFit: energy loss: " << config->m_energyloss;
    foo << " He subtraction: " << config->m_subtraction;
    foo << " correlation = " << config->m_correlation;
    config->m_comment           = foo.str();

    std::cout << "Running iFit now:" << std::endl;
    int mcMax=1; // this will control how many times I will average
    if (config->m_special_run) {
        mcMax=max_run;
        // Do everything
        myResult f;
        TFile *out_file = TFile::Open("output.root","RECREATE");
        TTree* tt = new TTree("tree","tree");
        tt->Branch("zbin",         &f.m_zbin,         "zbin/D");
        tt->Branch("qhat",         &f.m_qhat,         "q-hat/D");
        tt->Branch("lp",           &f.m_lp,           "lp/D");
        tt->Branch("sigma_ph",     &f.m_sigma_ph,     "sigma_ph/D");
        tt->Branch("dz",           &f.m_dz,           "dz/D");
        tt->Branch("qhat_err",     &f.m_qhat_err,     "qhat_err/D");
        tt->Branch("lp_err",       &f.m_lp_err,       "lp_err/D");
        tt->Branch("sigma_ph_err", &f.m_sigma_ph_err, "sigma_ph_err/D");
        tt->Branch("dz_err",       &f.m_dz_err,       "dz_err/D");
        tt->Branch("chi2",         &f.m_chi2,         "chi2/D");
        for (int mc=1; mc<=mcMax; mc++) {
            auto fitOutput = ifit(config);
            int count = 1;
            for (const auto &v : fitOutput) {
                std::cout << "Info: Run #" << mc << " element " << count << " of " << (int)fitOutput.size() << std::endl;
                std::cout << "Info:       z-bin    = " << v.m_zbin << std::endl;
                std::cout << "Info: Value q-hat    = " << v.m_qhat << std::endl;
                std::cout << "Info: Value l_p      = " << v.m_lp << std::endl;
                std::cout << "Info: Value sigma_ph = " << v.m_sigma_ph << std::endl;
                std::cout << "Info: Value dz       = " << v.m_dz << std::endl;
                std::cout << "Info: Error q-hat    = " << v.m_qhat_err << std::endl;
                std::cout << "Info: Error l_p      = " << v.m_lp_err << std::endl;
                std::cout << "Info: Error sigma_ph = " << v.m_sigma_ph_err << std::endl;
                std::cout << "Info: Error dz       = " << v.m_dz_err << std::endl;
                std::cout << "Info:       chi2     = " << v.m_chi2 << std::endl;
                f.m_zbin = v.m_zbin;
                f.m_qhat = v.m_qhat;
                f.m_lp = v.m_lp;
                f.m_sigma_ph = v.m_sigma_ph;
                f.m_dz = v.m_dz;
                f.m_qhat_err = v.m_qhat_err;
                f.m_lp_err = v.m_lp_err;
                f.m_sigma_ph_err = v.m_sigma_ph_err;
                f.m_dz_err = v.m_dz_err;
                f.m_chi2 = v.m_chi2;
                tt->Fill();
                count++;
            }
        }
        tt->Print();
        out_file->Write();
        out_file->Close();
    }
    else {
        // run only once and do nothing else
        auto fitOutput = ifit(config);
    }
    std::cout << "Running iFit ended" << std::endl;
    // commnt plotFitOutput if doing special things
    // plotFitOutput(config->m_output_fit);

    // test(); // Test of Model Class
    // auto fc = dataHandler(config); // This is just a test of dataHandler()
    // double zbin[4] = {0.32, 0.53, 0.75, 0.94};
    // for (int a=0; a<3; ++a) {
    //   for (int iz=0; iz<4; ++iz) {
    //     std::cout << zbin[iz] << "\t" << fc[a]->m_value[iz] << "\t" << 0.0 << "\t" << fc[a]->m_err[iz] << std::endl;
    //   }
    // }
    return 0;
}
