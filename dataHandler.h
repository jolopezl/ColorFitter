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

//
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "graphics.h"

class myData {
private:
  std::string m_name;
public:
  std::vector<double> m_zbin = {0.32, 0.53, 0.75, 0.94};
  std::vector<double> m_wbin = {(0.53-0.32)/2.0,(0.75-0.53)/2.0,(0.94-0.75)/2.0,(0.94-0.75)/2.0};
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
  void applyCorrection(myData*);
  void fill(int,double,double,double);
  void doTGraphErrors();
};

std::vector<myData*> dataHandler();
void conv2double(std::vector<std::string>,double&,double&,double&);
double pow2(double);

void doDataPlots(myData*,myData*, myData*, myData*);

void UTFSMLabel(double,double,const char*);
void AddLabel(double,double,const char*);

#endif