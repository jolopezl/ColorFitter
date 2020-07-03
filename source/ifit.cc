#include "ifit.h"
#include "dataFormat.h"

#include <TFile.h>
#include <TGraph.h>
#include <TMatrixD.h>
#include <TVectorD.h>

#include <time.h>

const int ZDIM = 4;
const int Q2DIM = 1;
double zbin[ZDIM] = { 0.31, 0.54, 0.75, 0.94 }; // pi+
double zbinw[ZDIM] = { 0.2, 0.2, 0.2, 0.2 };    // Exact !!

double func_array[5] = { 0, 0, 0, 0, 0 };

double pT2[4] = { 0, 0, 0 };
double Rm[4] = { 0, 0, 0 };

double SIG[4];
double SIG1[4] = { 27.075, 25.604, 25.109, 24.946 }; // interpolated cross-section for pi+
double SIG2[4] = { 29.669, 27.653, 26.929, 26.717 }; // interpolated cross-section for pi-
double SIG3[4] = { 17.281, 17.265, 17.264, 17.267 }; // interpolated cross-section for K+
double PROD_LEN_INTERP[4] = { 9.61702, 6.60402, 3.85302, 1.36402 };

double binratios[ZDIM] = { 0.214848, 0.432318, 0.440678, 0.125506 }; // PI+ with cuts !!

// I would like this not to be global, it's already a pointer, but fcn does not have more arguments ¿?
Model* m;
ModelOutput model_output;

const int DIM = 24;
double zzz[DIM];
double errorzzz[DIM];
double xxx[8]; // 8 points per fit, 4 targets per observable
TMatrixD V(DIM, DIM);
TVectorD data(DIM);
TVectorD model(DIM);

void callModel(const double A13, double q0, double lp, double sig, double eloss, double dkt2)
{
  m->SetParameters("q0", q0);
  m->SetParameters("lp", lp);
  m->SetParameters("sigma", sig);
  m->SetParameters("dz", eloss);
  m->SetTestParameter(dkt2, 0.0); // new coefficients
  m->Compute(std::pow(A13, 3));
  func_array[0] = m->Get1();             // pt-broadening
  func_array[1] = m->Get2();             // multiplicity ratio
  func_array[2] = m->Get3();             // average density
  func_array[3] = m->Get4();             // average multiplicity
  func_array[4] = m->GetAverageLength(); // average length
  model_output = m->GetResultStruct();   // get the full output
}

// I will write the Chi-Squared and some other functions here
double chisq(double* par)
{
  double chisq = 0.0;
  // PI+
  callModel(xxx[0], par[0], par[1], par[4], par[7], par[8]);
  model(0) = func_array[0];
  model(4) = func_array[1];
  callModel(xxx[1], par[0], par[1], par[4], par[7], par[8]);
  model(1) = func_array[0];
  model(5) = func_array[1];
  callModel(xxx[2], par[0], par[1], par[4], par[7], par[8]);
  model(2) = func_array[0];
  model(6) = func_array[1];
  callModel(xxx[3], par[0], par[1], par[4], par[7], par[8]);
  model(3) = func_array[0];
  model(7) = func_array[1];
  // PI-
  callModel(xxx[0], par[0], par[2], par[5], par[7], par[8]);
  model(0 + 8) = func_array[0];
  model(4 + 8) = func_array[1];
  callModel(xxx[1], par[0], par[2], par[5], par[7], par[8]);
  model(1 + 8) = func_array[0];
  model(5 + 8) = func_array[1];
  callModel(xxx[2], par[0], par[2], par[5], par[7], par[8]);
  model(2 + 8) = func_array[0];
  model(6 + 8) = func_array[1];
  callModel(xxx[3], par[0], par[2], par[5], par[7], par[8]);
  model(3 + 8) = func_array[0];
  model(7 + 8) = func_array[1];
  // K+
  callModel(xxx[0], par[0], par[3], par[6], par[7], par[8]);
  model(0 + 16) = func_array[0];
  model(4 + 16) = func_array[1];
  callModel(xxx[1], par[0], par[3], par[6], par[7], par[8]);
  model(1 + 16) = func_array[0];
  model(5 + 16) = func_array[1];
  callModel(xxx[2], par[0], par[3], par[6], par[7], par[8]);
  model(2 + 16) = func_array[0];
  model(6 + 16) = func_array[1];
  callModel(xxx[3], par[0], par[3], par[6], par[7], par[8]);
  model(3 + 16) = func_array[0];
  model(7 + 16) = func_array[1];

  chisq = (data - model) * (V * (data - model)); // Uses matrix form for the Chi^2
  return chisq;
}

void fcn(int& NPAR, double* gin, double& f, double* par, int iflag)
{
  f = chisq(par);
}

std::vector<myResult> ifit(myConfig* config)
{
  std::vector<myResult> resultCont;
  m = new Model("default");
  m->Initialization();
  m->DoEnergyLoss(config->m_energyloss, ZDIM);
  m->DoEnergyLossWeighted(config->m_energylossWeighted);
  m->DoLogBehavior(config->m_logbehavior);
  m->DoCascade(config->m_cascade);
  m->DoFixedLp(config->fixedLp);

  xxx[0] = std::cbrt(4.0026);  // Helium
  xxx[1] = std::cbrt(20.1797); // Neon
  xxx[2] = std::cbrt(83.7980); // Krypton
  xxx[3] = std::cbrt(131.293); // Xenon

  for (int i = 0; i < 4; ++i) {
    double A = pow(xxx[i], 3.0);
    std::cout << "Value of c " << m->GetC((int)A) << " for A " << (int)A << std::endl;
  }

  TFile* fInputData = new TFile("HERMES_InputData.root", "READ");
  std::pair<TGraphErrors*, TGraphErrors*> tgePIP;
  std::pair<TGraphErrors*, TGraphErrors*> tgePIM;
  std::pair<TGraphErrors*, TGraphErrors*> tgeKP;

  for (int iQ2 = 0; iQ2 < Q2DIM; ++iQ2) { // There is only one bin in Q2 for HERMES
    for (int iz = 0; iz < ZDIM; ++iz) {
      std::cout << "******************************************" << std::endl;
      std::cout << "****** Fitting now z-bin #" << iz + 1 << " z-bin center = " << zbin[iz] << std::endl;
      std::cout << "******************************************" << std::endl;
      if ((config->m_zBinOfInterest != -1) &&
          ((config->m_zBinOfInterest - 1) != iz)) {
        std::cout << "Ignoring this bin" << std::endl;
        continue;
      }
      tgePIP.first = (TGraphErrors*)fInputData->Get(Form("tg_pt_piplus_slice_0_zbin_%d", iz));
      tgePIP.second = (TGraphErrors*)fInputData->Get(Form("tg_RM_piplus_slice_0_zbin_%d", iz));
      tgePIM.first = (TGraphErrors*)fInputData->Get(Form("tg_pt_piminus_slice_0_zbin_%d", iz));
      tgePIM.second = (TGraphErrors*)fInputData->Get(Form("tg_RM_piminus_slice_0_zbin_%d", iz));
      tgeKP.first = (TGraphErrors*)fInputData->Get(Form("tg_pt_Kplus_slice_0_zbin_%d", iz));
      tgeKP.second = (TGraphErrors*)fInputData->Get(Form("tg_RM_Kplus_slice_0_zbin_%d", iz));
      if (tgePIP.first == nullptr || tgePIP.second == nullptr ||
          tgePIM.first == nullptr || tgePIM.second == nullptr ||
          tgeKP.first == nullptr || tgeKP.second == nullptr) {
        std::cerr << "Wrong 1!!" << std::endl;
      }

      // Fill the data points for PI+
      zzz[0] = tgePIP.first->GetY()[0];
      zzz[1] = tgePIP.first->GetY()[1];
      zzz[2] = tgePIP.first->GetY()[2];
      zzz[3] = tgePIP.first->GetY()[3];
      zzz[4] = tgePIP.second->GetY()[0];
      zzz[5] = tgePIP.second->GetY()[1];
      zzz[6] = tgePIP.second->GetY()[2];
      zzz[7] = tgePIP.second->GetY()[3];
      errorzzz[0] = tgePIP.first->GetEY()[0];
      errorzzz[1] = tgePIP.first->GetEY()[1];
      errorzzz[2] = tgePIP.first->GetEY()[2];
      errorzzz[3] = tgePIP.first->GetEY()[3];
      errorzzz[4] = tgePIP.second->GetEY()[0];
      errorzzz[5] = tgePIP.second->GetEY()[1];
      errorzzz[6] = tgePIP.second->GetEY()[2];
      errorzzz[7] = tgePIP.second->GetEY()[3];
      // Fill the data points for PI-
      zzz[0 + 8] = tgePIM.first->GetY()[0];
      zzz[1 + 8] = tgePIM.first->GetY()[1];
      zzz[2 + 8] = tgePIM.first->GetY()[2];
      zzz[3 + 8] = tgePIM.first->GetY()[3];
      zzz[4 + 8] = tgePIM.second->GetY()[0];
      zzz[5 + 8] = tgePIM.second->GetY()[1];
      zzz[6 + 8] = tgePIM.second->GetY()[2];
      zzz[7 + 8] = tgePIM.second->GetY()[3];
      errorzzz[0 + 8] = tgePIM.first->GetEY()[0];
      errorzzz[1 + 8] = tgePIM.first->GetEY()[1];
      errorzzz[2 + 8] = tgePIM.first->GetEY()[2];
      errorzzz[3 + 8] = tgePIM.first->GetEY()[3];
      errorzzz[4 + 8] = tgePIM.second->GetEY()[0];
      errorzzz[5 + 8] = tgePIM.second->GetEY()[1];
      errorzzz[6 + 8] = tgePIM.second->GetEY()[2];
      errorzzz[7 + 8] = tgePIM.second->GetEY()[3];
      // Fill the data points for K+
      zzz[0 + 16] = tgeKP.first->GetY()[0];
      zzz[1 + 16] = tgeKP.first->GetY()[1];
      zzz[2 + 16] = tgeKP.first->GetY()[2];
      zzz[3 + 16] = tgeKP.first->GetY()[3];
      zzz[4 + 16] = tgeKP.second->GetY()[0];
      zzz[5 + 16] = tgeKP.second->GetY()[1];
      zzz[6 + 16] = tgeKP.second->GetY()[2];
      zzz[7 + 16] = tgeKP.second->GetY()[3];
      errorzzz[0 + 16] = tgeKP.first->GetEY()[0];
      errorzzz[1 + 16] = tgeKP.first->GetEY()[1];
      errorzzz[2 + 16] = tgeKP.first->GetEY()[2];
      errorzzz[3 + 16] = tgeKP.first->GetEY()[3];
      errorzzz[4 + 16] = tgeKP.second->GetEY()[0];
      errorzzz[5 + 16] = tgeKP.second->GetEY()[1];
      errorzzz[6 + 16] = tgeKP.second->GetEY()[2];
      errorzzz[7 + 16] = tgeKP.second->GetEY()[3];

      m->setZ(zbin[iz]);
      m->SetBinRatio(iz, zbinw[iz], binratios[iz]); // For energy loss

      for (int i = 0; i < DIM; ++i) {
        data(i) = zzz[i];
        V(i, i) = std::pow(errorzzz[i], 2);
      }

      std::cout << "**** ERROR MATRIX for this bin ****" << std::endl;
      V.Print();
      std::cout << "**** INV. ERROR MATRIX for this bin ****" << std::endl;
      V.Invert();
      V.Print();
      std::cout << "**** DATA VECTOR for this bin ****" << std::endl;
      data.Print();

      TMinuit* gMinuit = new TMinuit(9); //initialize TMinuit with a maximum of N params
      gMinuit->SetFCN(fcn);
      double arglist[10];
      int ierflg = 0;
      arglist[0] = 1;
      gMinuit->mnexcm("SET ERR", arglist, 1, ierflg);
      arglist[0] = 3;
      gMinuit->mnexcm("SET PRI", arglist, 1, ierflg);

      gMinuit->mnparm(0, "Q0", 2.0, 0.01, 0, 10, ierflg);                   // q-hat
      gMinuit->mnparm(1, "LP(PIP)", 1.6, 0.01, 0.0001, 40, ierflg);         // production length
      gMinuit->mnparm(2, "LP(PIM)", 1.6, 0.01, 0.0001, 40, ierflg);         // production length
      gMinuit->mnparm(3, "LP(KP)", 1.6, 0.01, 0.0001, 40, ierflg);          // production length
      gMinuit->mnparm(4, "SIG(PIP)", SIG1[iz], 0.01, 0.0001, 100, ierflg);  // prehadron cross section
      gMinuit->mnparm(5, "SIG(PIM)", SIG2[iz], 0.01, 0.0001, 100, ierflg);  // prehadron cross section
      gMinuit->mnparm(6, "SIG(KP)", SIG3[iz], 0.01, 0.0001, 100, ierflg);   // prehadron cross section
      gMinuit->mnparm(7, "ELOSS", 0, 0.01, -2, 14, ierflg);                 // z shift due to energy loss
      gMinuit->mnparm(8, "DELTA-KT2", -0.025, 0.0001, -0.05, 0.05, ierflg); // delta kt

      // Parameter fixing
      if (!config->m_preh) {
        gMinuit->FixParameter(4); // prehadron cross section
        gMinuit->FixParameter(5); // prehadron cross section
        gMinuit->FixParameter(6); // prehadron cross section
      }
      gMinuit->FixParameter(7); // Energy Loss

      // Now ready for minimization step
      arglist[0] = 500;
      arglist[1] = 1.;
      gMinuit->mnexcm("MIGRAD", arglist, 8, ierflg);

      std::cout << "Completed MIGRAD for iz " << iz << " with ierflg " << ierflg << std::endl;
      if (ierflg) {
        std::cerr << "Check the output of your fit, something went wrong with bin-#" << iz + 1 << std::endl;
      }

      // gMinuit->mnexcm("HESSE", arglist, 8,ierflg)
      /*
      std::cout << "STARTING TO SEARCH FOR A FIT IMPROVEMENT" << std::endl;
      gMinuit->FixParameter(0);
      gMinuit->FixParameter(1);
      gMinuit->Release(7);
      gMinuit->mnexcm("MIGRAD", arglist, 8,ierflg);
      gMinuit->mnexcm("HESSE", arglist, 8,ierflg);
      */
      // gMinuit->mnexcm("IMPROVE", arglist, 8,ierflg);
      // if (config->doMINOSErrors == true) {
      //   double p0[10];
      //   std::vector<int> parVec = { 1, 2, 8 };
      //   for (const auto& p : parVec) {
      //     p0[1] = p; // Use external parameter number
      //     gMinuit->mnexcm("MINOS", p0, 6, ierflg);
      //   }
      //   double eplus, eminus, eparab, gcc;
      //   for (const auto& p : parVec) {
      //     gMinuit->mnerrs(p - 1, eplus, eminus, eparab, gcc); // use internal parameter number
      //     std::cout << "MINOS Errors for parameter " << p - 1 << " eplus = " << eplus << ", eminus = " << eminus << ", eparab = " << eparab << ", and gcc = " << gcc << std::endl;
      //   }
      // }

      // Print results
      double amin, edm, errdef;
      int nvpar, nparx, icstat;
      gMinuit->mnstat(amin, edm, errdef, nvpar, nparx, icstat);
      gMinuit->mnprin(3, amin);
      std::string bin_info = config->m_comment; // dummy value for HERMES
      double xB = -1;                           // dummy value for HERMES
      double Q2 = -1;                           // dummy value for HERMES
      myResult result = myResult();
      modelplot(gMinuit, config, bin_info, iQ2, iz, Q2, xB, zbin[iz], config->m_output_fit, result);
      resultCont.push_back(result);

      // if (iz == (ZDIM - 1)) {
      //   TFile* fout = TFile::Open("correlation_test.root", "RECREATE");
      //   int number_of_points = 50;
      //   TGraph* gr_contours[5];
      //   for (int i = 0; i < 1; ++i) {
      //     int nsigma = i + 1;
      //     gMinuit->SetErrorDef(nsigma * nsigma);
      //     gr_contours[i] = (TGraph*)gMinuit->Contour(number_of_points, 1, 7);
      //     gr_contours[i]->SetName(Form("contour_%d", i));
      //     gr_contours[i]->Write();
      //     break;
      //   }
      //   fout->Close();
      // }
      delete (gMinuit);
    }
    // End of loop over z-bins
  }
  std::cout << "iFit has finished" << std::endl;
  return resultCont;
}

// this will be moved away someday to graphics.cc
void modelplot(TMinuit* g, myConfig* config, std::string bin_info,
               int iQ2x, int iz, double Q2, double xB, double z,
               std::string filename, myResult& result)
{

  /* should be read from gMinuit */
  // double correlation_matrix[2][2];
  // gMinuit->mnemat(&correlation_matrix[0][0], 4);
  // std::cout << correlation_matrix[0][0] << "\t" << correlation_matrix[0][1] << std::endl;
  // std::cout << correlation_matrix[1][0] << "\t" << correlation_matrix[1][1] << std::endl;

  // double correlation_factor[4] = {0.557,0.321,-0.074,-0.056};
  // TRandom3* rr = new TRandom3(); // this forces all gRandom uses to be TRandom3 instead of TRandom, the default.
  // rr->SetSeed(9234);

  double z1[4][3], x1[4], errorz1[4][3];
  double z2[4][3], x2[4], errorz2[4][3];
  x1[0] = xxx[0];
  x1[1] = xxx[1];
  x1[2] = xxx[2];
  x1[3] = xxx[3];

  x2[0] = xxx[0];
  x2[1] = xxx[1];
  x2[2] = xxx[2];
  x2[3] = xxx[3];

  z1[0][0] = zzz[0];
  z1[1][0] = zzz[1];
  z1[2][0] = zzz[2];
  z1[3][0] = zzz[3];
  z2[0][0] = zzz[4];
  z2[1][0] = zzz[5];
  z2[2][0] = zzz[6];
  z2[3][0] = zzz[7];
  z1[0][1] = zzz[0 + 8];
  z1[1][1] = zzz[1 + 8];
  z1[2][1] = zzz[2 + 8];
  z1[3][1] = zzz[3 + 8];
  z2[0][1] = zzz[4 + 8];
  z2[1][1] = zzz[5 + 8];
  z2[2][1] = zzz[6 + 8];
  z2[3][1] = zzz[7 + 8];
  z1[0][2] = zzz[0 + 16];
  z1[1][2] = zzz[1 + 16];
  z1[2][2] = zzz[2 + 16];
  z1[3][2] = zzz[3 + 16];
  z2[0][2] = zzz[4 + 16];
  z2[1][2] = zzz[5 + 16];
  z2[2][2] = zzz[6 + 16];
  z2[3][2] = zzz[7 + 16];

  errorz1[0][0] = errorzzz[0];
  errorz1[1][0] = errorzzz[1];
  errorz1[2][0] = errorzzz[2];
  errorz1[3][0] = errorzzz[3];
  errorz2[0][0] = errorzzz[4];
  errorz2[1][0] = errorzzz[5];
  errorz2[2][0] = errorzzz[6];
  errorz2[3][0] = errorzzz[7];
  errorz1[0][1] = errorzzz[0 + 8];
  errorz1[1][1] = errorzzz[1 + 8];
  errorz1[2][1] = errorzzz[2 + 8];
  errorz1[3][1] = errorzzz[3 + 8];
  errorz2[0][1] = errorzzz[4 + 8];
  errorz2[1][1] = errorzzz[5 + 8];
  errorz2[2][1] = errorzzz[6 + 8];
  errorz2[3][1] = errorzzz[7 + 8];
  errorz1[0][2] = errorzzz[0 + 16];
  errorz1[1][2] = errorzzz[1 + 16];
  errorz1[2][2] = errorzzz[2 + 16];
  errorz1[3][2] = errorzzz[3 + 16];
  errorz2[0][2] = errorzzz[4 + 16];
  errorz2[1][2] = errorzzz[5 + 16];
  errorz2[2][2] = errorzzz[6 + 16];
  errorz2[3][2] = errorzzz[7 + 16];

  double val = 0;
  double err = 0;
  double xlolim = 0;
  double xuplim = 0;
  int iuint = 0;
  int NPAR = 9;
  TString chnam;
  double par[NPAR], par_errors[NPAR];

  std::ostringstream out;
  for (int parNo = 0; parNo < NPAR; ++parNo) {
    out << "a" << parNo;
    chnam = (TString)out.str();
    out.flush();
    g->mnpout(parNo, chnam, val, err, xlolim, xuplim, iuint);
    par[parNo] = val;
    par_errors[parNo] = err;
  }

  const double chisquared = chisq(par);
  result.m_zbin = z;
  result.m_q0 = par[0];
  result.m_lp1 = par[1];
  result.m_lp2 = par[2];
  result.m_lp3 = par[3];
  result.m_sig1 = par[4];
  result.m_sig2 = par[5];
  result.m_sig3 = par[6];
  result.m_dz = par[7];
  result.m_dkt2 = par[8];
  result.m_q0_err = par_errors[0];
  result.m_lp1_err = par_errors[1];
  result.m_lp2_err = par_errors[2];
  result.m_lp3_err = par_errors[3];
  result.m_sig1_err = par_errors[4];
  result.m_sig2_err = par_errors[5];
  result.m_sig3_err = par_errors[6];
  result.m_dz_err = par_errors[7];
  result.m_dkt2_err = par_errors[8];
  result.m_chi2 = chisquared;

  // At this point, we know the parameters, so let's write them out
  bool doCSVFile = true;
  std::string myDelimeter;
  if (doCSVFile) {
    myDelimeter = ";";
  } else {
    myDelimeter = "\t";
  }
  std::ofstream fout;
  fout.open(filename, std::ios::out | std::ios::app);
  fout.precision(10);
  if (iz == 0)
    fout << bin_info << "\n";
  if (Q2 != -1 && xB != -1) {
    fout << iQ2x << myDelimeter << iz << myDelimeter;
    fout << Q2 << myDelimeter << xB << myDelimeter;
  }
  fout << z << myDelimeter;
  for (int i = 0; i < NPAR; ++i) {
    fout << par[i] << myDelimeter;
  }
  for (int i = 0; i < NPAR; ++i) {
    fout << par_errors[i] << myDelimeter;
  }
  fout << chisquared << myDelimeter;
  fout << pT2[0] << myDelimeter << pT2[1] << myDelimeter << pT2[2] << pT2[3] << myDelimeter;
  fout << Rm[0] << myDelimeter << Rm[1] << myDelimeter << Rm[2] << Rm[3] << "\n";
  fout.close();
  if (config->outputPlots) { // plots
    std::cout << "Now doing fit plots with model " << std::endl;
    double q0 = result.m_q0;
    double lp[3] = { result.m_lp1, result.m_lp2, result.m_lp3 };
    double lp_err[3] = { result.m_lp1_err, result.m_lp2_err, result.m_lp3_err };
    double sig[3] = { result.m_sig1, result.m_sig2, result.m_sig3 };
    double eloss = result.m_dz;
    double deltakT2 = result.m_dkt2;

    for (int i = 0; i < 3; ++i) {
      std::vector<double> pt_fit;
      std::vector<double> pt_fit_up;
      std::vector<double> pt_fit_down;
      std::vector<double> pt_fiterr;
      std::vector<double> pt_x;
      std::vector<double> rm_fit;
      std::vector<double> rm_fit_up;
      std::vector<double> rm_fit_down;
      std::vector<double> rm_fiterr;
      std::vector<double> rm_x;
      std::vector<double> average_density_fit;
      std::vector<double> multiplicity_density_fit;
      std::vector<double> average_length_fit;
      std::vector<double> average_parton_length_fit;

      std::vector<double> d_pT_dq0;
      std::vector<double> d_pT_dL;
      // int i = 0;
      double x = 1.0;
      double dx = (6.0 - 1.0) / 25;
      while (x < 6.0) {
        std::cout << "Modelplot for A^1/3 = " << x << std::endl;
        callModel(x, q0, lp[i], sig[i], eloss, deltakT2);
        double pT2 = func_array[0];
        double RM = func_array[1];
        double average_density = func_array[2];
        double multiplicty_density = func_array[3];
        // double average_length = func_array[4];
        average_density_fit.push_back(model_output.average_density);
        multiplicity_density_fit.push_back(model_output.average_multiplicity_density);
        average_length_fit.push_back(model_output.average_production_length);
        average_parton_length_fit.push_back(model_output.average_parton_length);
        pt_fit.push_back(pT2);
        pt_fiterr.push_back(0);
        pt_x.push_back(x);
        rm_fit.push_back(RM);
        rm_fiterr.push_back(0);
        rm_x.push_back(x);
        /* return also the plots for model uncertainties */
        d_pT_dq0.push_back(pT2 / q0);
        d_pT_dL.push_back(q0 * average_density);
        /** We will keep the uncertainties to first order only **/
        /** higher orders do not agree with Toy MC, so something can be wrongly derived **/
        double uncertainty = 0;
        // uncertainty += pow(pT2 / q0 * result.m_q0_err, 2) + pow(z * result.m_dkt2_err, 2);
        uncertainty += pow((pT2 / q0 - z * z * result.m_dkt2) * result.m_q0_err, 2);
        uncertainty += pow(z * z * result.m_dkt2_err, 2);
        uncertainty = sqrt(uncertainty);
        pt_fit_up.push_back(pT2 + uncertainty);
        pt_fit_down.push_back(pT2 - uncertainty);
        double uncertainty2 = 0;
        uncertainty2 += pow(multiplicty_density * lp_err[i], 2);
        uncertainty2 = sqrt(uncertainty2);
        rm_fit_up.push_back(RM + uncertainty2);
        rm_fit_down.push_back(RM - uncertainty2);
        std::cout << "Average density " << average_density << std::endl;
        std::cout << "PT2 = " << pT2 << " +/- " << uncertainty << " (GeV^2)" << std::endl;
        std::cout << "RM = " << RM << " +/- " << uncertainty2 << std::endl;
        // i++;
        x += dx;
      }
      const double zeros[3] = { 0, 0, 0 };
      const int npoints = pt_x.size();
      result.m_tg_data_pT.push_back(TGraphErrors(4, x1, z1[i], zeros, errorz1[i]));
      result.m_tg_data_Rm.push_back(TGraphErrors(4, x2, z2[i], zeros, errorz2[i]));
      result.m_tg_pT.push_back(TGraphErrors(4, x1, pT2, zeros, zeros));
      result.m_tg_Rm.push_back(TGraphErrors(4, x2, Rm, zeros, zeros));
      result.m_tg_average_density.push_back(TGraph(npoints, pt_x.data(), average_density_fit.data()));
      result.m_tg_multiplicity_density.push_back(TGraph(npoints, pt_x.data(), multiplicity_density_fit.data()));
      result.m_tg_average_length.push_back(TGraph(npoints, pt_x.data(), average_length_fit.data()));
      result.m_tg_average_parton_length.push_back(TGraph(npoints, pt_x.data(), average_parton_length_fit.data()));
      result.m_tg_pT_extrapolation.push_back(TGraphErrors(npoints, pt_x.data(), pt_fit.data(), pt_fiterr.data(), pt_fiterr.data()));
      result.m_tg_pT_extrapolation_up.push_back(TGraphErrors(npoints, pt_x.data(), pt_fit_up.data(), pt_fiterr.data(), pt_fiterr.data()));
      result.m_tg_pT_extrapolation_down.push_back(TGraphErrors(npoints, pt_x.data(), pt_fit_down.data(), pt_fiterr.data(), pt_fiterr.data()));
      result.m_tg_Rm_extrapolation.push_back(TGraphErrors(npoints, rm_x.data(), rm_fit.data(), rm_fiterr.data(), rm_fiterr.data()));
      result.m_tg_Rm_extrapolation_up.push_back(TGraphErrors(npoints, rm_x.data(), rm_fit_up.data(), rm_fiterr.data(), rm_fiterr.data()));
      result.m_tg_Rm_extrapolation_down.push_back(TGraphErrors(npoints, rm_x.data(), rm_fit_down.data(), rm_fiterr.data(), rm_fiterr.data()));
    }
  }
}

double fermi(double m_xB, double m_zbinvalue, int inucleus)
{
  // Computes the contribution of fermi momentum broadening to
  // pT broadening using Boris's formula
  double avgFermi; // <(Fermi momentum)**2>
  //.033 Pb
  //.028 Fe
  //.029 C
  //.023 D
  // From Taya's study, not completely final:
  //0.019 Pb
  //0.014 Fe
  //0.015 C
  //0.002 D
  avgFermi = -999.;
  //  if(inucleus==0){avgFermi=0.029-.023;} // Carbon
  //  if(inucleus==1){avgFermi=0.028-.023;} // Iron
  //  if(inucleus==2){avgFermi=0.033-.023;} // Lead
  if (inucleus == 0)
    avgFermi = 0.015 - .002; // Carbon
  if (inucleus == 1)
    avgFermi = 0.014 - .002; // Iron
  if (inucleus == 2)
    avgFermi = 0.019 - .002; // Lead
  if (avgFermi == -999.) {
    std::cout << "Fermi error" << std::endl;
  }
  // x=Q2/2Mnu
  //  Double_t x = Q2_lo[iQ2nu][iz][0]/2.+Q2_hi[iQ2nu][iz][0]/2.;
  //x=x/(2.*0.9385);
  //x=x/(nu_lo[iQ2nu][iz][0]/2.+nu_hi[iQ2nu][iz][0]/2.);
  // The part below is for the data when it is read in as x, not as nu.
  double x = m_xB;
  double z_h = m_zbinvalue;
  double result = 0.6666666 * x * x * z_h * z_h * avgFermi;
  return result;
}

// For testing only
int test()
{
  std::vector<std::string> atoms = { "Carbon", "Iron", "Lead" };
  std::vector<double> masses = { 12.0107, 55.845, 207.2 };
  std::vector<double> parms = { 0.2, 7.0, 1.0, 2.5, 0.0 }; //{ 0.2, 7.,1.0 }
  Model* m = new Model("default");
  m->SetParameters(parms);
  m->Initialization();
  std::vector<double> foo;
  double nucleus;
  double nu[3] = { 20.1797, 83.798, 131.293 };
  for (int i = 0; i < 3; ++i) {
    nucleus = (double)nu[i];
    m->Compute(nucleus);
    std::cout << nu[i] << "\t" << m->Get1() << "\t" << m->Get2() << std::endl;
  }
  for (int i = 1; i <= 6; ++i) {
    nucleus = (double)i * i * i;
    m->Compute(nucleus);
    std::cout << i << "\t" << m->Get1() << "\t" << m->Get2() << std::endl;
  }
  delete (m);
  return 0;
}

// function to compite the model given a set of parameters and print the output to the screen
void justCompute(myConfig* config)
{
  Model* model = new Model("toy");
  model->Initialization();
  model->DoEnergyLoss(config->m_energyloss, ZDIM);
  model->DoLogBehavior(config->m_logbehavior);
  const double A_Ne = pow(20.1797, 1. / 3.); // Ne
  const double A_Kr = pow(83.7980, 1. / 3.); // Kr
  const double A_Xe = pow(131.293, 1. / 3.); // Xe
  const double foo[3] = { pow(A_Ne, 3.0), pow(A_Kr, 3.0), pow(A_Xe, 3.0) };
  const std::vector<double> parms = { 0.2, 7.0, 1.0, 2.5, 0.0, 0.0 };
  model->SetParameters(parms);
  for (int i = 0; i < 3; ++i) {
    model->Compute(foo[i]);
    std::cout << i << "\t" << m->Get1() << "\t" << m->Get2() << std::endl;
  }
}
