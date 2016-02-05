#include "main.h"

#define RUN 1

int demoPlots(); // Do plots and studies of the model
int demoPlots2D(); // Do fancier plots and studies of the model
int computeSimpleFit();                           // A simple fits trusted.
int computeComplexFit(int argc, char *argv[]);    // A fit with a complex configuration
int printInteractionPoints();


// ************ main function ************ //
int main(int argc, char *argv[]) {
  demoPlots();
  // printInteractionPoints();
}

// *** prints interaction points *** //
int printInteractionPoints() {
  Model *model = new Model("InteractionPoints");
  model->Initialization();
  double x=0.,y=0.,z=0.;
  int A = 12;
  double AAux         = 1.1*pow(A,1/3.); // carbon
  double cutoff = 0.005;
  double R=model->GetR(AAux,cutoff);
  std::cout << "Interaction Points for A = " << A << " density cutoff = " << cutoff << std::endl;
  for (int i = 0; i < 10; ++i) {
    model->InteractionPoint(x,y,z,R);
    std::cout << x << "\t" << y << "\t" << z << std::endl;
  }
  return 0;
}

// ************ This is used for model plots ************ //
int demoPlots() {
  Model *model = new Model("demoPlots");
  model->Initialization();
  model->DoFixedLp(true); 
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
  model->SetParameters("qhat", 1.5);
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

// **************** Compute a Simple Fit **************** //
int computeSimpleFit() {
  myConfig *config = new myConfig();
  // bins of interest
  int Q2Int = -1;
  int izInt = -1;
  // defauls
  int input_energyloss     = 0;
  int input_subtraction    = 1;
  double input_correlation = 0.0;
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
  // Write configuration to file
  std::ostringstream foo;
  foo << "iFit Info: Energy Loss: " << config->m_energyloss;
  foo << " - He subtraction: "      << config->m_subtraction;
  foo << " with correlation = "     << config->m_correlation;
  config->m_comment = foo.str();
  std::cout << "Running iFit now:" << std::endl;
  auto fitOutput = ifit(config);
  return 0;
}

// **************** Compute a _fancy_ Fit **************** //
int computeComplexFit(int argc, char *argv[]) {
  myConfig *config = new myConfig();
  // bins to fit
  int Q2Int  = -1;
  int izInt  =  3;
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
