#include "main.h"

int main(int argc, char *argv[]) {
  myConfig *config = new myConfig();

  config->m_energyloss        = false;
  config->m_logbehavior       = false;
  config->m_fermimotion       = false;
  config->m_subtraction       = false;
  config->m_correlation       = -1.0; // for physics -1.0 < rho < 0.0
  config->m_Q2BinOfInterest   = -1;   // value in between 1 and Q2DIM of Q2,x bins. -1 fits all.
  config->m_zBinOfInterest    = -1;   // value in between 1 and ZDIM of z bins. -1 fits all.
  config->m_output_fit        = "testFit.txt";
  config->m_input_pt          = "hermesData.txt";
  // config->m_comment           = "test of iFit";

  std::ostringstream foo;
  foo << "iFit: energy loss: " << config->m_energyloss;
  foo << " He subtraction: " << config->m_subtraction;
  foo << " correlation = " << config->m_correlation;
  config->m_comment           = foo.str();

  std::cout << "Running iFit now:" << std::endl;
  ifit(config);
  std::cout << "Running iFit ended" << std::endl;
  plotFitOutput(config->m_output_fit);

  // test(); // Test of Model Class
  // auto fc = dataHandler(config->m_correlation); // This is just a test of dataHandler()

  return 0;
}
