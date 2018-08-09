#include "MultiGaus.h"

void MultiGaus(const TVectorD& parMeans, const TMatrixDSym& covMatrix, TVectorD& genPars)
{
  int nPars = parMeans.GetNrows();
  if(nPars <= 0) {
    Error("MultiGaus", "Must have >0 pars");
    return;
  }
  if(covMatrix.GetNrows() != nPars) {
    Error("MultiGaus", "parMeans.GetNrows() != covMatrix.GetNrows()");
    return;
  }
 
  // Check that covMatrix is symmetric
  for(int iRow = 0; iRow < nPars; iRow++) {
    for(int iCol = iRow; iCol < nPars; iCol++) {
      if(covMatrix(iRow, iCol) != covMatrix(iCol, iRow)) {
        Error("MultiGaus", "malformed cov matrix at row %d, col %d", iRow, iCol);
        return;
      }
    }
  }

  genPars.ResizeTo(nPars);

  TMatrixDSymEigen eigenvariances(covMatrix);
  TVectorD rotParMeans = eigenvariances.GetEigenVectors() * parMeans;
  for(int iPar = 0; iPar < nPars; iPar++) {
    double variance = eigenvariances.GetEigenValues()[iPar];
    // check for positive-definiteness of covMatrix
    if(variance < 0) {
      Error("MultiGaus", "Got a negative eigenvariance (%f) on iPar = %d", variance, iPar);
    }
    genPars[iPar] = gRandom->Gaus(rotParMeans[iPar], sqrt(variance));
  }
  genPars = eigenvariances.GetEigenVectors() * genPars;
}

double ChiSquare(double x, double ndf)
{
  return TMath::Power(0.5, ndf/2.0) / TMath::Gamma(ndf/2.0) *
         TMath::Power(x, ndf/2.0 - 1.0) * TMath::Exp(-x/2.0);
}
