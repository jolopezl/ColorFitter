#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "dataHandler.h"

#include "model.h"
#include "configuration.h"

class myData; // I would like to remove this fordward declaration
// class myConfig;

//void modelplot(TMinuit*, std::string, int, int, double, double, double,double*,double*,double*);
void doDataPlots(myConfig*,myData*,myData*, myData*, myData*);
void plotFitOutput(std::string);

void UTFSMLabel(double,double,const char*);
void AddLabel(double,double,const char*);

#endif