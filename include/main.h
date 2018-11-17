#ifndef MAIN_H
#define MAIN_H

#include "model.h"
#include "ifit.h"
#include "dataHandler.h"
#include "configuration.h"

#include "TFile.h"
#include "TTree.h"
#include "TRandom3.h"

#include <stdlib.h>

int demoPlots(); // Do plots and studies of the model
int demoPlots2D(); // Do fancier plots and studies of the model
int runColorFitter(const bool, const bool, const double);
int runColorFitterVariant(const std::string, const bool, const double);
int printInteractionPoints();
int ComputeBand(int);
int plotTool();
int monitoring();

#endif
