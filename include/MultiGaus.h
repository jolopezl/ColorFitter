#include <TMatrixD.h>
#include <TMatrixDSym.h>
#include <TMatrixDSymEigen.h>
#include <TVectorD.h>
#include <TRandom.h>
#include <TMath.h>

void MultiGaus(const TVectorD& parMeans, const TMatrixDSym& covMatrix, TVectorD& genPars);
