#include "main.h"

// const bool ENERGYLOSS   = false; // true or false
// const bool LOGBEHAVIOR  = false; // true or false
// const bool FERMIMOTION  = false; // true or false
// const int  Q2XBINTOFIT  = -1; // someone in between 1 and Q2DIM of Q2,x bins. -1 fits all.
// const int  ZBINTOFIT    = -1; // someone in between 1 and ZDIM of z bins. -1 fits all.

// const double correlation = -1.0; // correlation between systematics of A/Helium for data subtraction

int main(int argc, char *argv[]) {
  myConfig *config = new myConfig(); // now everything can be read from the command line
  config->m_energyloss        = false; // true or false
  config->m_logbehavior       = false; // true or false
  config->m_fermimotion       = false; // true or false
  config->m_subtraction       = false;
  config->m_correlation       = 0.0;
  config->m_Q2BinOfInterest   = -1; // someone in between 1 and Q2DIM of Q2,x bins. -1 fits all.
  config->m_zBinOfInterest    = -1; // someone in between 1 and ZDIM of z bins. -1 fits all.
  config->m_output            = "testFit.txt";
  // test(); // Test of Model Class
  /*
    Run dataHandler alone allows to see how original data is transformed.
    Also gives plots of original data points.
  */
  // double correlation = 0.0;
  // auto fc = dataHandler(correlation); // This is just a test of dataHandler()
  /* Run of main program ifit */
  // float correlation = 0.0;
  // std::string filename = "testModel.txt";
  // std::cout << argv[0] << argv[1] << argv[2] << std::endl;
  // std::string filename = argv[1];
  // double correlation = std::stod(argv[2]);
  std::cout << "Running iFit now:" << std::endl;
  // ifit(ENERGYLOSS,LOGBEHAVIOR,FERMIMOTION,Q2XBINTOFIT,ZBINTOFIT,correlation,filename);
  ifit(config);
  std::cout << "Running iFit ended" << std::endl;
  plotFitOutput(config->m_output);
  return 0;
}
