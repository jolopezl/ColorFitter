#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <iostream>
#include <sstream>
#include <vector>

class myConfig
{
 public:
  bool m_special_run = false;
  bool m_stat_only = false;
  bool m_energyloss = false; // true or false
  bool m_energylossWeighted = false;
  bool m_logbehavior = false; // true or false
  bool m_fermimotion = false; // true or false
  bool m_cascade = false;
  bool m_qhat = true;
  bool m_lp = true;
  bool m_preh = true;
  bool m_testing = false;
  double m_initial_sigma = 40.0;
  bool m_subtraction = true;
  double m_correlation = 0.0;
  int m_Q2BinOfInterest = -1; // someone in between 1 and Q2DIM of Q2,x bins. -1 fits all.
  int m_zBinOfInterest = -1;  // someone in between 1 and ZDIM of z bins. -1 fits all.
  std::string m_output_fit = "testFit.txt";
  std::string m_input_pt = "hermesData.txt";
  std::string m_comment = "bin_info comment";

  bool doMINOSErrors = false;

  bool outputPlots = false;
  bool writeCorrectedValues = false;
  bool correctionPlots = false;
  bool fixedLp = false;

  bool monitoring = false;

  myConfig();
  ~myConfig();
  void Update();
  std::vector<float> getMassNumbers() const { return kMASSNUMBER; }

 private:
  std::vector<float> kMASSNUMBER = { 12.0107, 55.845, 207.2 }; // C, Fe, Pb For JLab
  // constexpr float kMASSNUMBER[3] = { 20.1797, 83.7980, 131.293 }; // For HERMES
};

#endif