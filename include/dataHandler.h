#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <iostream>
#include <sstream> // for ostringstream
#include <string>
#include <fstream>
#include "TFile.h"
#include "TMinuit.h"
#include "TString.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TH1.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"

//
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "graphics.h"
#include "configuration.h"
#include "MultiGaus.h"

class myResult
{
  /*
    Class storing the resulting parameters of the fit
    This should come out from ifit(), and be built from the minuit object
    */
 private:
  std::string m_name = "default result";

 public:
  double m_zbin{ -99 };
  double m_q0{ -99 };
  double m_lp1{ -99 };
  double m_lp2{ -99 };
  double m_lp3{ -99 };
  double m_sig1{ -99 };
  double m_sig2{ -99 };
  double m_sig3{ -99 };
  double m_dz{ -99 };
  double m_q0_err{ -99 };
  double m_lp1_err{ -99 };
  double m_lp2_err{ -99 };
  double m_lp3_err{ -99 };
  double m_sig1_err{ -99 };
  double m_sig2_err{ -99 };
  double m_sig3_err{ -99 };
  double m_dz_err{ -99 };
  double m_chi2{ -99 };
  double m_dkt2{ -99 };
  double m_dkt2_err{ -99 };

  std::vector<TGraphErrors> m_tg_pT;
  std::vector<TGraphErrors> m_tg_Rm;
  std::vector<TGraphErrors> m_tg_data_pT;
  std::vector<TGraphErrors> m_tg_data_Rm;
  std::vector<TGraphErrors> m_tg_pT_extrapolation;
  std::vector<TGraphErrors> m_tg_pT_extrapolation_up;
  std::vector<TGraphErrors> m_tg_pT_extrapolation_down;
  std::vector<TGraphErrors> m_tg_Rm_extrapolation;
  std::vector<TGraphErrors> m_tg_Rm_extrapolation_up;
  std::vector<TGraphErrors> m_tg_Rm_extrapolation_down;
  std::vector<TGraph> m_tg_average_density;
  std::vector<TGraph> m_tg_multiplicity_density;
  std::vector<TGraph> m_tg_average_length;
  std::vector<TGraph> m_tg_average_parton_length;
  // constructor
  myResult();
  ~myResult();
};

class myData
{
 private:
  std::string m_name;

 public:
  std::vector<double> m_zbin = { 0.32, 0.53, 0.75, 0.94 };
  std::vector<double> m_wbin = { 0.20 / 2.0, 0.22 / 2.0, 0.22 / 2.0, 0.16 / 2.0 };
  std::vector<double> m_value;
  std::vector<double> m_value_corrected;
  std::vector<double> m_stat;
  std::vector<double> m_stat_corrected;
  std::vector<double> m_syst;
  std::vector<double> m_syst_corrected;
  std::vector<double> m_err;
  std::vector<double> m_err_corrected;
  std::vector<TGraphErrors*> m_tge; //m_tge[6];
  myData(std::string);
  ~myData();
  void applyCorrection(myData*, double);
  void fill(int, double, double, double);
  void doTGraphErrors();
  std::string name();
};

std::vector<myData*> dataHandler(myConfig*);
bool OutputResultsToFile(const std::string, std::vector<myResult>);

#endif
