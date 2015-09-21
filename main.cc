#include "main.h"

const bool ENERGYLOSS   = false; // true or false
const bool LOGBEHAVIOR  = false; // true or false
const bool FERMIMOTION  = false; // true or false
const int  Q2XBINTOFIT  = -1; // someone in between 1 and 16 of Q2,x bins. -1 fits all.
const int  ZBINTOFIT    = -1; // someone in between 1 and 10 of z bins. -1 fits all.

int main() {
  // test(); // Test of Model Class
  // auto fc = dataHandler(); // This is just a test of dataHandler()
  std::cout << "Running iFit now" << std::endl;
  ifit(ENERGYLOSS,LOGBEHAVIOR,FERMIMOTION,Q2XBINTOFIT,ZBINTOFIT);
  std::cout << "Running iFit ended" << std::endl;
  return 0;
}
