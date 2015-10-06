#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <iostream>

class myConfig {
public:
  bool m_energyloss   = false; // true or false
  bool m_logbehavior  = false; // true or false
  bool m_fermimotion  = false; // true or false
  bool m_subtraction  = false;
  double m_correlation = 0.0;
  int  m_Q2BinOfInterest   = -1; // someone in between 1 and Q2DIM of Q2,x bins. -1 fits all.
  int  m_zBinOfInterest    = -1; // someone in between 1 and ZDIM of z bins. -1 fits all.
  std::string m_output = "testFit.txt";
  myConfig();
  ~myConfig();
};

#endif