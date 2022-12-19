#include "main.h"
#include "MultiGaus.h"
#include <TF2.h>
#include <TH2.h>

#define RUN 1

// ************ main function ************ //
int main(int argc, char* argv[])
{
  std::string particle = "lambda";
  std::string model = "BL30" + particle; // Name for the model you are runing
  myConfig* config = new myConfig();     // create a configuration to call the fitter
  config->m_particletype = particle;     //
  config->m_subtraction = false;         // subtract Helium background
  config->m_correlation = 0.0;           // without correlation
  config->fixedLp = false;               // true: to use fixed production length, false: exponential distribution
  config->m_preh = true;                // true: fit the prehadron cross section - false: don't fit the prehadron cross section
  config->m_initial_sigma = 30.0;        // legacy, now input is from pdg cross sections
  config->m_energyloss = false;          // do energy loss
  config->m_testing = false;             // active testing parameters
  config->m_Q2BinOfInterest = -1;        // do not change
  config->m_zBinOfInterest = -1;         // value in between 1 and 4
  config->m_input_pt = "hermesData.txt"; // ONLY FOR HERMES
  config->writeCorrectedValues = false;  // text file from dataHandler
  config->correctionPlots = false;       // from dataHandler
  config->outputPlots = true;            // model and data, very useful
  config->doMINOSErrors = false;         // usually false
  
  config->m_cascade = true;
  
  config->Update();


  // Call the fitter with the configured setup
  std::cout << "Running iFit now:" << std::endl;
  std::vector<myResult> resultCont = ifit(config);
  std::cout << "Fit is done." << std::endl;

  // Call the data handler to output results
  OutputResultsToFile(model, resultCont);

  std::cout << "I am done here" << std::endl;
  resultCont.clear();
  std::cout << "Results container cleared" << std::endl;

  return 0; // done

  ///// **** Access to other methods **** /////
  // runColorFitter(true, true,  0.0); // EnergyLoss, Subtraction, Correlation
  // runColorFitter(true, true, -0.5);
  // runColorFitter(true, true, -1.0);
  // runColorFitterVariant(argv[1], true, 0); // If you want to pass the model variant from execution "$ ifit.exe BLE30"
  // runColorFitterVariant("BL", true, 0.0); // Model variant (known), subtraction (true or false), correlation (usually zero)
  // runColorFitterVariant("BL25",  true, 0.0);
  // runColorFitterVariant("BL30",  true, 0.0);
  // runColorFitterVariant("BLE",  true, 0.0);
  // runColorFitterVariant("BL40",  true, 0.0);
  // runColorFitterVariant("BLE",   true, 0.0);
  // runColorFitterVariant("BLE25", true, 0.0);
  // runColorFitterVariant("BLE30", true, 0.0);
  // runColorFitterVariant("BLE40", true, 0.0);
  // runColorFitterVariant("BLE35", true, 0.0);
  // runColorFitterVariant("BLE40", true, 0.0);
  // runColorFitterVariant("BL", true, 0.0);
  // runColorFitterVariant("BLC", true, 0.0);
  // runColorFitterVariant("BL25", true, 0);
  // runColorFitterVariant("BLEf30", true, 0);
  // monitoring();
  // demoPlots(true); // fixed lp
  // demoPlots(false); // exp lp
  // printInteractionPoints();
  // ComputeBand();
}

int monitoring()
{
  constexpr int ZDIM = 4;
  double binratios[ZDIM] = { 0.214848, 0.432318, 0.440678, 0.125506 }; // PI+ with cuts !!
  double zbinw[ZDIM] = { 0.2, 0.2, 0.2, 0.2 };                         // Exact !!

  Model* model = new Model("Monitoring");
  model->DoMonitoring(true);
  model->Initialization();
  // model->DoFixedLp(true);
  model->DoEnergyLoss(true);

  model->SetMaxMonteCarloSteps(1e6); // 1e6, 1e7
  model->MonitoringStart();
  double q0_values[4] = { 2.21, 2.57, 1.15, 1.19 };
  double lp_values[4] = { 8.15, 6.11, 4.45, 2.35 };
  double A[3];
  A[0] = 20.1797; // Ne
  A[1] = 83.7980; // Kr
  A[2] = 131.293; // Xe
                  // for (int zbin=3; zbin<4; ++zbin) {
  int zbin = 2;
  model->defineZbin(zbin + 1);
  model->SetBinRatio(zbin, zbinw[zbin], binratios[zbin]); // For energy loss
  model->SetParameters("q0", q0_values[zbin]);
  model->SetParameters("lp", lp_values[zbin]);
  model->SetParameters("sigma", 30.);
  model->SetTestParameter(0, 0, 0);
  // for (int i=0; i<3; ++i) {
  int i = 1;
  std::cout << "Calling A = " << A[i] << std::endl;
  model->Compute(A[i]);
  // }
  // }
  model->MonitoringFinish();
  return 0;
}

int plotTool()
{
  /* 
        Just plot the results of the He subtraction in pt-broadening, only useful for HERMES
        This is done by passing correctionPlots=true in the config 
    */
  myConfig* config = new myConfig();
  config->m_subtraction = true;
  config->m_correlation = -0.5;
  config->correctionPlots = true;
  auto fc = dataHandler(config);
  return 0;
}

int runColorFitterVariant(const std::string model, const bool iSubt, const double iCorr)
{
  /*
        Set up different model variants defined by model
        BL, BL30, BLE, BLE30, etc.
        Helful to run multiple model variants at once from main()
    */

  int Q2Int = -1;
  int izInt = -1; // 4 for bin #83

  myConfig* config = new myConfig();
  config->m_subtraction = iSubt; // false;
  config->m_correlation = iCorr; // for physics -1.0 < rho < 0.0

  config->fixedLp = false;
  if (config->fixedLp == true) {
    config->m_output_fit = "testFit" + model + ".fixedLp.csv";
  } else {
    config->m_output_fit = "testFit" + model + ".csv";
  }

  if (model == "BL") {
    config->m_preh = true;
    config->m_initial_sigma = 30.0;
    config->m_energyloss = false;
  } else if (model == "BL25") {
    config->m_preh = false;
    config->m_initial_sigma = 25.0;
  } else if (model == "BL30") {
    config->m_preh = false;
    config->m_initial_sigma = 30.0;
  } else if (model == "BL35") {
    config->m_preh = false;
    config->m_initial_sigma = 35.0;
  } else if (model == "BL40") {
    config->m_preh = false;
    config->m_initial_sigma = 40.0;
  } else if (model == "BLE") {
    config->m_energyloss = true;
  } else if (model == "BLE25") {
    config->m_preh = false;
    config->m_initial_sigma = 25.0;
    config->m_energyloss = true;
  } else if (model == "BLE30") {
    config->m_preh = false;
    config->m_initial_sigma = 30.0;
    config->m_energyloss = true;
    config->m_testing = true;
  } else if (model == "BLE35") {
    config->m_preh = false;
    config->m_initial_sigma = 35.0;
    config->m_energyloss = true;
  } else if (model == "BLE40") {
    config->m_preh = false;
    config->m_initial_sigma = 40.0;
    config->m_energyloss = true;
  } else if (model == "BLE30C") {
    config->m_preh = false;
    config->m_initial_sigma = 30.0;
    config->m_energyloss = true;
    config->m_cascade = true;
  } else if (model == "BLC") {
    config->m_preh = true;
    config->m_initial_sigma = 30.0;
    config->m_energyloss = false;
    config->m_cascade = true;
  } else if (model == "BL30C") {
    config->m_preh = false;
    config->m_initial_sigma = 30.0;
    config->m_cascade = true;
  } else if (model == "BLC") {
    config->m_output_fit = "testFit" + model + ".csv";
    config->m_cascade = true;
    //        if (config->fixedLp == true) "testFit"+model+"fixedLp.csv";
  } else if (model == "BLEf30") {
    config->m_preh = false;
    config->m_initial_sigma = 30.0;
    config->m_energyloss = true;
    // config->m_energyloss_fixed = true;
  } else {
    return -1;
  }
  config->m_Q2BinOfInterest = Q2Int;     // value in between 1 and Q2DIM of Q2,x bins. -1 fits all.
  config->m_zBinOfInterest = izInt;      // value in between 1 and ZDIM of z bins. -1 fits all.
  config->m_input_pt = "hermesData.txt"; // ONLY FOR HERMES
  config->writeCorrectedValues = false;  // text file from dataHandler
  config->correctionPlots = false;       // from dataHandler
  config->outputPlots = true;            // model and data, very useful
  config->doMINOSErrors = false;         // usually false
  config->Update();

  std::cout << "Running iFit now:" << std::endl;
  config->m_testing = false;
  std::vector<myResult> resultCont = ifit(config);

  std::cout << "Fit is done." << std::endl;
  /* Call output handler needs model name and result container */
  OutputResultsToFile(model, resultCont);
  return 0;
}

// **************** Compute a Simple Fit **************** //
int runColorFitter(const bool tEnergyLoss, const bool tSubtraction, const double tCorrelation)
{
  /*
        Generic function to configure the fitter
        Initially used to study the impact of different correlations on the Helium subtraction
        This will be deprecated for future data
    */
  myConfig* config = new myConfig();
  const std::string model = "BL_test";
  // bins of interest
  int Q2Int = -1;
  int izInt = -1;
  // defauls
  bool input_energyloss = tEnergyLoss;
  bool input_subtraction = tSubtraction;
  double input_correlation = tCorrelation;
  config->m_energyloss = input_energyloss;   // false;
  config->m_subtraction = input_subtraction; // false;
  config->m_correlation = input_correlation; // for physics -1.0 < rho < 0.0
  config->m_energylossWeighted = false;
  // Production lenght behaviour
  config->fixedLp = false;
  // Pre-hadron cross section
  config->m_preh = false;         // usually true
  config->m_initial_sigma = 35.0; // do it < 40 mbarns
  // more.
  config->m_Q2BinOfInterest = Q2Int; // value in between 1 and Q2DIM of Q2,x bins. -1 fits all.
  config->m_zBinOfInterest = izInt;  // value in between 1 and ZDIM of z bins. -1 fits all.
  config->m_output_fit = "testFit2p.csv";
  config->m_input_pt = "hermesData.txt";
  config->writeCorrectedValues = false; // text file from dataHandler
  config->correctionPlots = false;      // from dataHandler
  config->outputPlots = false;          // model and data
  config->doMINOSErrors = false;        // usually false
  config->Update();
  std::cout << "Running iFit now:" << std::endl;
  auto fitOutput = ifit(config);
  OutputResultsToFile(model, fitOutput);
  return 0;
}

int ComputeBand(int zbin = 1)
{
  double SIG1[4] = { 27.075, 25.604, 25.109, 24.946 }; // interpolated cross-section for pi+
  double SIG2[4] = { 29.669, 27.653, 26.929, 26.717 }; // interpolated cross-section for pi-
  double SIG3[4] = { 17.281, 17.265, 17.264, 17.267 }; // interpolated cross-section for K+
  /*
        Function created to study the model uncertainties
        It is called from main and takes time, usually a cluster
        It needs to know the parameters from a given model variant, 
        those values are not read from file and must be set by hand - see below
    */
  // x is A^1/3
  int TOY_MC_STEPS = 1500;
  std::cout << "ComputeBand will use " << TOY_MC_STEPS << " TOY_MC_STEPS" << std::endl;

  Model* model = new Model("ComputeBand");
  model->Initialization();
  model->DoFixedLp(false);
  model->DoEnergyLoss(true);

  // If not here, model returns a bug, it is set in ifit when running the fitting
  int iz = zbin - 1;
  const int ZDIM = 4;
  double zbinw[ZDIM] = { 0.2, 0.2, 0.2, 0.2 };                  // Approx.
  double binratios[ZDIM] = { 0.482203, 0.461464, 0.249762, 0 }; // PI+ no cuts
  model->SetBinRatio(iz, zbinw[iz], binratios[iz]);

  int StatusCode;
  double PT2, RM;
  double A13 = 1.0;
  double A13Max = 6.0;
  double A13Step = 0.5;
  double q0, lp, kt2;

  // A13 = x/10.;
  int nabins = 12;

  TFile* fout = new TFile(Form("ToyMC_A13_%d_bin_%d.root", nabins, zbin), "RECREATE");
  TTree* tree = new TTree("tree", "Tree of ToyMC");
  tree->Branch("zbin", &zbin, "zbin/I");
  tree->Branch("A13", &A13, "A13/D");
  tree->Branch("PT2", &PT2, "PT2/D");
  tree->Branch("RM", &RM, "RM/D");
  tree->Branch("q0", &q0, "q0/D");
  tree->Branch("lp", &lp, "lp/D");
  tree->Branch("kt2", &kt2, "kt2/D");
  tree->Branch("StatusCode", &StatusCode, "StatusCode/I");
  // Setup for the Toy MC with random generation
  int nDim = 3;
  TVectorD parMeans(nDim);
  TVectorD parErrors(nDim);
  TMatrixDSym covMatrix(nDim);
  TVectorD genPars(nDim);
  // Numbers obtained from fit to BL30
  if (zbin == 1) {
    parMeans(0) = 2.91532e+00;
    parMeans(1) = 7.27808e+00;
    parMeans(2) = -2.78996e-02;
    parErrors(0) = 2.49939e-01;
    parErrors(1) = 8.01199e-01;
    parErrors(2) = 5.49546e-03;
    covMatrix(0, 0) = parErrors(0) * parErrors(0);
    covMatrix(0, 1) = -0.462 * parErrors(0) * parErrors(1);
    covMatrix(0, 2) = 0.772 * parErrors(0) * parErrors(2);
    covMatrix(1, 0) = covMatrix(0, 1);
    covMatrix(1, 1) = parErrors(1) * parErrors(1);
    covMatrix(1, 2) = -0.103 * parErrors(1) * parErrors(2);
    covMatrix(2, 0) = covMatrix(0, 2);
    covMatrix(2, 1) = covMatrix(1, 2);
    covMatrix(2, 2) = parErrors(2) * parErrors(2);
  }
  if (zbin == 2) {
    parMeans(0) = 3.18725e+00;
    parMeans(1) = 5.62317e+00;
    parMeans(2) = -6.39949e-03;
    parErrors(0) = 4.65714e-01;
    parErrors(1) = 4.66257e-01;
    parErrors(2) = 3.42707e-03;
    covMatrix(0, 0) = parErrors(0) * parErrors(0);
    covMatrix(0, 1) = -0.244 * parErrors(0) * parErrors(1);
    covMatrix(0, 2) = -0.811 * parErrors(0) * parErrors(2);
    covMatrix(1, 0) = covMatrix(0, 1);
    covMatrix(1, 1) = parErrors(1) * parErrors(1);
    covMatrix(1, 2) = 0.046 * parErrors(1) * parErrors(2);
    covMatrix(2, 0) = covMatrix(0, 2);
    covMatrix(2, 1) = covMatrix(1, 2);
    covMatrix(2, 2) = parErrors(2) * parErrors(2);
  }
  if (zbin == 3) {
    parMeans(0) = 1.26238e+00;
    parMeans(1) = 4.26355e+00;
    parMeans(2) = -5.78123e-03;
    parErrors(0) = 1.22416e+00;
    parErrors(1) = 3.79033e-01;
    parErrors(2) = 4.60122e-03;
    covMatrix(0, 0) = parErrors(0) * parErrors(0);
    covMatrix(0, 1) = 0.045 * parErrors(0) * parErrors(1);
    covMatrix(0, 2) = 0.826 * parErrors(0) * parErrors(2);
    covMatrix(1, 0) = covMatrix(0, 1);
    covMatrix(1, 1) = parErrors(1) * parErrors(1);
    covMatrix(1, 2) = 0.006 * parErrors(1) * parErrors(2);
    covMatrix(2, 0) = covMatrix(0, 2);
    covMatrix(2, 1) = covMatrix(1, 2);
    covMatrix(2, 2) = parErrors(2) * parErrors(2);
  }
  if (zbin == 4) {
    parMeans(0) = 1.20334e+00;
    parMeans(1) = 2.09546e+00;
    parMeans(2) = -3.99590e-03;
    parErrors(0) = 2.62821e+00;
    parErrors(1) = 2.41538e-01;
    parErrors(2) = 4.81277e-03;
    covMatrix(0, 0) = parErrors(0) * parErrors(0);
    covMatrix(0, 1) = -0.034 * parErrors(0) * parErrors(1);
    covMatrix(0, 2) = -0.850 * parErrors(0) * parErrors(2);
    covMatrix(1, 0) = covMatrix(0, 1);
    covMatrix(1, 1) = parErrors(1) * parErrors(1);
    covMatrix(1, 2) = 0.004 * parErrors(1) * parErrors(2);
    covMatrix(2, 0) = covMatrix(0, 2);
    covMatrix(2, 1) = covMatrix(1, 2);
    covMatrix(2, 2) = parErrors(2) * parErrors(2);
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
    for (int mc = 0; mc < TOY_MC_STEPS; ++mc) {
      if (mc % 100 == 0) {
        std::cout << "MC Step = " << mc + 1 << " of " << TOY_MC_STEPS << std::endl;
      }
      while (true) {
        // std::cout << "Generating point with " << std::endl;
        // for (int i = 0; i<3; ++i) {
        // std::cout << "parMeans(" << i << ") = " << parMeans(i) << std::endl;
        // }
        MultiGaus(parMeans, covMatrix, genPars);
        q0 = genPars(0);
        lp = genPars(1);
        kt2 = genPars(2);
        // std::cout << "q0 = " << q0 << std::endl;
        // std::cout << "lp = " << lp << std::endl;
        // std::cout << "kt2 = " << kt2 << std::endl;
        if (q0 > 0 && lp > 0) {
          //   std::cout << "Point found" << std::endl;
          break;
        }
        // std::cout << "Searching for a new random set of parameters within the physics limits" << std::endl;
      }
      model->SetParameters("q0", q0);
      model->SetParameters("lp", lp);
      model->SetParameters("sigma", SIG1[iz]);
      model->SetTestParameter(kt2, 0.0, 0.0);
      StatusCode = model->Compute(nucleus);
      PT2 = model->Get1();
      RM = model->Get2();
      tree->Fill();
    }
    A13 += A13Step; // go to next nucleus
  }
  tree->Write();
  fout->Close();
  return 0;
}

int printInteractionPoints()
{
  /*
        Prints interaction points
    */
  Model* model = new Model("InteractionPoints");
  model->Initialization();
  double x = 0., y = 0., z = 0.;
  int A = 12;
  double A13 = pow(A, 1 / 3.); // carbon
  double cutoff = 0.005;
  double R = model->GetR(A13, cutoff);
  std::cout << "Interaction Points for A = " << A << " density cutoff = " << cutoff << std::endl;
  for (int i = 0; i < 10; ++i) {
    model->InteractionPoint(x, y, z, R);
    std::cout << x << "\t" << y << "\t" << z << std::endl;
  }
  return 0;
}

// ************ This is used for model plots ************ //
int demoPlots(bool do_fixed_lp)
{
  /*
        Make those plots of pT vs A^1/3 as a demonstration of the model
        Used to study fixed vs exp distribution for L
    */
  TFile* fout = nullptr;
  if (do_fixed_lp) {
    fout = new TFile("DemoPlots.fixedLp.root", "RECREATE");
  } else {
    fout = new TFile("DemoPlots.ExpLp.root", "RECREATE");
  }
  Model* model = new Model("demoPlots");
  model->Initialization();
  model->DoFixedLp(do_fixed_lp);
  model->SetParameters("q0", 1);
  // To run and produce full list of files at once.
  std::string str;
  std::string filename;
  std::vector<double> lpList = { 1, 3, 5, 10, 20 };
  for (const auto& lp : lpList) {
    TGraph* tg1 = new TGraph(230);
    TGraph* tg2 = new TGraph(230);
    for (int nucleus = 12; nucleus <= 241; ++nucleus) {
      std::cout << "Computing " << nucleus << " of 241 for lp = " << lp << std::endl;
      model->SetParameters("lp", lp); //* <------!!! *//
      model->Compute(nucleus);        //* <------!!! *//
      //* Print to file **//
      // std::ofstream fout;
      // filename = "input-exp-fixed-lp="+str+".txt";
      // fout.open(filename, std::ios::out | std::ios::app);
      // fout.precision(10);
      // fout << pow(nucleus,1./3.) << "\t" << model->Get1() << "\t" << model->Get2() << "\n";
      // fout.close();
      tg1->SetPoint(nucleus - 12, pow(nucleus, 1. / 3.), model->Get1());
      tg2->SetPoint(nucleus - 12, pow(nucleus, 1. / 3.), model->Get2());
      str = boost::lexical_cast<std::string>(lp);
    }
    std::string name1 = "pT2_lp_" + str;
    std::string name2 = "RM_lp_" + str;
    tg1->SetName(name1.c_str());
    tg2->SetName(name2.c_str());
    tg1->SetTitle(";#it{A}^{1/3};#Delta#it{p}_{T}^{2} (GeV^{2})");
    tg2->SetTitle(";#it{A}^{1/3};#it{R}_{M}");
    tg1->Write();
    tg2->Write();
    delete tg1;
    delete tg2;
  }
  fout->Close();
  return 0;
}

// ************ This is used for model plots ************ //
int demoPlots2D()
{
  Model* model = new Model("demoPlots2D");
  model->Initialization();
  model->DoFixedLp(true);
  model->SetParameters("q0", 1.5);
  model->SetParameters("density threshold", 0.0005);
  float step_lp = (20.0 - 1.0) / 25;
  int setp_nucl = (int)(240 - 12) / 25;
  for (int nucleus = 12; nucleus <= 240; nucleus += setp_nucl) {
    for (float lp = 1.0; lp <= 20; lp += step_lp) {
      model->SetParameters("lp", lp);
      model->Compute(nucleus);
      std::cout << pow(nucleus, 1. / 3.) << '\t' << lp << '\t' << model->Get1() << std::endl;
    }
  }
  return 0;
}
