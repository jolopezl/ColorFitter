#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "dataHandler.h"

class myData; // I would like to remove this fordward declaration

//void modelplot(TMinuit*, std::string, int, int, double, double, double,double*,double*,double*);
void doDataPlots(myData*,myData*, myData*, myData*);

void UTFSMLabel(double,double,const char*);
void AddLabel(double,double,const char*);

#endif