#include "main.h"

const bool ENERGYLOSS   = false; // true or false
const bool LOGBEHAVIOR  = false; // true or false
const bool FERMIMOTION  = false; // true or false
const int  Q2XBINTOFIT  = -1; // someone in between 1 and Q2DIM of Q2,x bins. -1 fits all.
const int  ZBINTOFIT    = -1; // someone in between 1 and ZDIM of z bins. -1 fits all.

// const double correlation = -1.0; // correlation between systematics of A/Helium for data subtraction

int main(int argc, char *argv[]) {
  // test(); // Test of Model Class
  /*
    Run dataHandler alone allows to see how original data is transformed.
    Also gives plots of original data points.
  */
  // auto fc = dataHandler(correlation); // This is just a test of dataHandler()
  /* Run of main program ifit */
  std::string filename = argv[1];
  double correlation = std::stod(argv[2]);
  std::cout << "Running iFit now" << std::endl;
  ifit(ENERGYLOSS,LOGBEHAVIOR,FERMIMOTION,Q2XBINTOFIT,ZBINTOFIT,correlation,filename);
  std::cout << "Running iFit ended" << std::endl;
  plotFitOutput(filename);
  return 0;
}
