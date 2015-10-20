#include "main.h"

int main(int argc, char *argv[]) {

  myConfig *config = new myConfig();

  double input_energyloss  = std::stoi(argv[1]);
  double input_subtraction = std::stoi(argv[2]);
  double input_correlation = std::stod(argv[3]);

  config->m_special_run       = false; // for computing multiple values of the parameters
  config->m_stat_only         = false;
  config->m_energyloss        = input_energyloss; // false;
  config->m_logbehavior       = false;
  config->m_fermimotion       = false;
  config->m_subtraction       = input_subtraction; // false;
  config->m_correlation       = input_correlation; // -1.0; // for physics -1.0 < rho < 0.0
  config->m_Q2BinOfInterest   = -1;   // value in between 1 and Q2DIM of Q2,x bins. -1 fits all.
  config->m_zBinOfInterest    = -1;   // value in between 1 and ZDIM of z bins. -1 fits all.
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
    mcMax=2;
  }
  std::vector<myResult*> res;
  for (int mc=0; mc<mcMax; mc++) {
    res = ifit(config);
    // use res
    std::cout << "Nothing to do with res" << std::endl;
    // clear res
    res.clear();
  }
  std::cout << "Running iFit ended" << std::endl;
  plotFitOutput(config->m_output_fit);

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
