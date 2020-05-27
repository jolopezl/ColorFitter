#include <TMatrixD.h>
#include <TMatrixDSym.h>
#include <TMatrixDSymEigen.h>
#include <TVectorD.h>
#include <TRandom.h>
#include <TMath.h>

void MultiGaus(const TVectorD& parMeans, const TMatrixDSym& covMatrix, TVectorD& genPars);

void conv2double(std::vector<std::string>, double&, double&, double&);
double pow2(double);
double fcn_gaus_2d_cov(double* x, double* par);
