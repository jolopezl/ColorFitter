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
#include "TH1.h"

//
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

// 
#include "model.h"

double fermi(double);
void callModel(double, double*);
double chisq(double*);
void fcn(int&, double*, double&, double*, int);
void ifit();
void modelplot(TMinuit*, std::string, int, int);
int test();

#endif