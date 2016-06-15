#include "main.h"

#define RUN 1

int demoPlots(); // Do plots and studies of the model
int demoPlots2D(); // Do fancier plots and studies of the model
int computeSimpleFit(const bool, const bool, const double);                           // A simple fits trusted.
int computeSimpleFit2(const std::string, const bool, const double);
int computeComplexFit(int argc, char *argv[]);    // A fit with a complex configuration
int printInteractionPoints();
int computeBand();
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
  // computeBand();
  // demoPlots();
  // int foo = average_density();
  computeSimpleFit(false,true,0.0);
  // MODEL TYPE, do subtraction, value
  // computeSimpleFit2("BL30", true, 0.0);
  monitoring();
}

int monitoring() {
  Model *model = new Model("Monitoring");
  model->DoMonitoring(true);
  model->Initialization();
  // model->DoFixedLp(true);
  model->DoEnergyLoss(false);
  model->SetMaxMonteCarloSteps(1e5);
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
  int Q2Int = 3;
  int izInt = 3;
  config->m_subtraction = iSubt; // false;
  config->m_correlation = iCorr; // for physics -1.0 < rho < 0.0
  if (model == "BL") {
    config->m_output_fit = "testFitBL.csv";
  }
  else if (model == "BLE") {
    config->m_output_fit = "testFitBLE.csv";
    config->m_energyloss = true;
  }
  else if (model == "BL40") {
    config->m_preh = false;
    config->m_input_pt = 40.0;
    config->m_output_fit = "testFitBL40.csv";
  }
  else if (model == "BLE40") {
    config->m_output_fit = "testFitBL40.csv";
    config->m_preh = false;
    config->m_input_pt = 40.0;
    config->m_energyloss = true;
  }
  config->m_Q2BinOfInterest   = Q2Int; // value in between 1 and Q2DIM of Q2,x bins. -1 fits all.
  config->m_zBinOfInterest    = izInt; // value in between 1 and ZDIM of z bins. -1 fits all.
  config->m_input_pt          = "hermesData.txt";
  config->writeCorrectedValues = false; // text file from dataHandler
  config->correctionPlots      = false; // from dataHandler
  config->outputPlots          = true; // model and data
  config->doMINOSErrors = false; // usually false
  config->Update();
  std::cout << "Running iFit now:" << std::endl;
  auto fitOutput = ifit(config);
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
  config->m_initial_sigma     = 30.0;  // do it < 40 mbarns
  // more.
  config->m_Q2BinOfInterest   = Q2Int; // value in between 1 and Q2DIM of Q2,x bins. -1 fits all.
  config->m_zBinOfInterest    = izInt; // value in between 1 and ZDIM of z bins. -1 fits all.
  config->m_output_fit        = "testFitBL30.csv";
  config->m_input_pt          = "hermesData.txt";
  config->writeCorrectedValues = false; // text file from dataHandler
  config->correctionPlots      = false; // from dataHandler
  config->outputPlots          = true; // model and data
  config->doMINOSErrors = false; // usually false
  config->Update();
  std::cout << "Running iFit now:" << std::endl;
  auto fitOutput = ifit(config);
  return 0;
}

// **** computations of the model **** //
int computeBand() {
  Model *model = new Model("computeBand");
  model->Initialization();
  model->DoFixedLp(false);
  // Calculated values for z=0.75 with 3P Fit
  const double values[] = {1.39305676,  3.02980576,  19.51217989}; // qhat, lp, cross-section
  const double errors[] = {1.71818655,  4.670434572, 26.69759973};
  double qhat = -1.0, lp = -1.0, sigma = -1.0;
  TRandom3 random;
  double nucleus   = 83.7980;
  double delta_pT2 = -1.0;
  double Rm        = -1.0;
  double acc1 = 0., acc2 = 0;
  int sc = -1; // status code

  TFile *fout = new TFile("fullfit2.root","RECREATE");
  TTree *tree = new TTree("tree", "fits");
  tree->Branch("qhat",  &qhat,      "qhat/D"  );
  tree->Branch("lp",    &lp,        "lp/D"    );
  tree->Branch("sigma", &sigma,     "sigma/D" );
  tree->Branch("pT2",   &delta_pT2, "pT2/D"   );
  tree->Branch("Rm",    &Rm,        "Rm/D"    );
  tree->Branch("SC",    &sc,        "SC/I"    );

  int mcsteps = 5000;
  for (int i = 0; i < mcsteps; i++) {
    qhat  = random.Gaus(values[0], errors[0]/2.0);
    lp    = random.Gaus(values[1], errors[1]/2.0);
    sigma = random.Gaus(values[2], errors[2]/2.0);
    model->SetParameters("q0",     qhat  );
    model->SetParameters("lp",       lp    );
    model->SetParameters("sigma", sigma );
    sc = model->Compute(nucleus);
    // if (sc == 1) continue;
    delta_pT2 = model->Get1();
    Rm = model->Get2();
    // std::cout << "         QHAT VALUE=" << values[0] << "+/-" << errors[0] << " SORTED=" << parameter[0] << std::endl;
    // std::cout << "           LP VALUE=" << values[1] << "+/-" << errors[1] << " SORTED=" << parameter[1] << std::endl;
    // std::cou t << "CROSS-SECTION VALUE=" << values[2] << "+/-" << errors[2] << " SORTED=" << parameter[2] << std::endl;
    // std::cout << i << "\t" << delta_pT2 << "\t" << Rm << std::endl;
    tree->Fill();
    acc1+=delta_pT2;
    acc2+=Rm;
  }
  delta_pT2 = acc1/mcsteps;
  Rm = acc2/mcsteps;
  std::cout << "AVERAGE VALUES " << delta_pT2 << "\t" << Rm << std::endl;
  tree->Write();
  fout->Write();
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
  // model->DoFixedLp(true); 
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
      std::string filename = "input-exp-lp="+str+".txt";
      fout.open(filename, std::ios::out | std::ios::app);
      fout.precision(10);
      fout << pow(nucleus,1./3.) << '\t' << model->Get1() << '\n';
      fout.close();
    }
  }
  return 0;
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
        std::cout << "Info:       z-bin    = " << v->m_zbin << std::endl;
        std::cout << "Info: Value q-hat    = " << v->m_qhat << std::endl;
        std::cout << "Info: Value l_p      = " << v->m_lp << std::endl;
        std::cout << "Info: Value sigma_ph = " << v->m_sigma_ph << std::endl;
        std::cout << "Info: Value dz       = " << v->m_dz << std::endl;
        std::cout << "Info: Error q-hat    = " << v->m_qhat_err << std::endl;
        std::cout << "Info: Error l_p      = " << v->m_lp_err << std::endl;
        std::cout << "Info: Error sigma_ph = " << v->m_sigma_ph_err << std::endl;
        std::cout << "Info: Error dz       = " << v->m_dz_err << std::endl;
        std::cout << "Info:       chi2     = " << v->m_chi2 << std::endl;
        f.m_zbin = v->m_zbin;
        f.m_qhat = v->m_qhat;
        f.m_lp = v->m_lp;
        f.m_sigma_ph = v->m_sigma_ph;
        f.m_dz = v->m_dz;
        f.m_qhat_err = v->m_qhat_err;
        f.m_lp_err = v->m_lp_err;
        f.m_sigma_ph_err = v->m_sigma_ph_err;
        f.m_dz_err = v->m_dz_err;
        f.m_chi2 = v->m_chi2;
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
