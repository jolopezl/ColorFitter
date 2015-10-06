#ifndef IFIT_H
#define IFIT_H

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

//
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

// 
#include "model.h"
#include "dataHandler.h"

double fermi(double,double,int);
void callModel(double, double*);
double chisq(double*);
void fcn(int&, double*, double&, double*, int);
void ifit(bool,bool,bool,int,int,double,std::string);
void modelplot(TMinuit*, std::string, int, int, double, double, double,std::string);
int test();

#endif