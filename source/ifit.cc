#include "ifit.h"

#include <time.h>
#include "TMatrixD.h"
#include "TVectorD.h"

const double SYSTEMATIC_DPT2 = 0.04;
const double SYSTEMATIC_RM = 0.03;
const int ZDIM = 10;
const int Q2DIM = 16;
double zbin[ZDIM] = { 0.05, 0.15, 0.25, 0.35, 0.45, 0.55, 0.65, 0.75, 0.85, 0.95 }; // pi+
double zbinw[ZDIM] = { 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1 };          // Approx.
double binratios[ZDIM] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

double values[6] = { 0, 0, 0, 0, 0, 0 };
double errors[6] = { 0, 0, 0, 0, 0, 0 };
double xxx[6] = { 0, 0, 0, 0, 0, 0 };

double ModelResultArray[4] = { 0, 0, 0, 0 };
double pT2[3] = { 0, 0, 0 };
double Rm[3] = { 0, 0, 0 };

Model* m;

const int DIM = 6;
TMatrixD V(DIM, DIM);
TVectorD data(DIM);
TVectorD model(DIM);

void callModel(const double A13, double* par)
{
  // qhat, lp, pre-hadron cross-section, log behaviour, energy loss, cascade
  std::vector<double> my_pars = { par[0], par[1], par[2],
                                  par[3], par[4], par[5] };
  double nucleus = (double)A13 * A13 * A13;
  m->SetParameters(my_pars);
  m->SetTestParameter(par[6], par[7]); // new coefficients
  m->Compute(nucleus);
  ModelResultArray[0] = m->Get1();
  ModelResultArray[1] = m->Get2();
  ModelResultArray[2] = m->Get3();
  ModelResultArray[3] = m->Get4();
}

// I will write the Chi-Squared and some other functions here
double chisq(double* par)
{
  double chisq = 0.0;
  callModel(xxx[0], par);
  pT2[0] = ModelResultArray[0];
  Rm[0] = ModelResultArray[1];
  callModel(xxx[1], par);
  pT2[1] = ModelResultArray[0];
  Rm[1] = ModelResultArray[1];
  callModel(xxx[2], par);
  pT2[2] = ModelResultArray[0];
  Rm[2] = ModelResultArray[1];

  model(0) = pT2[0];
  model(1) = pT2[1];
  model(2) = pT2[2];
  model(3) = Rm[0];
  model(4) = Rm[1];
  model(5) = Rm[2];

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
  // m->DoFermiMotion(config->m_fermimotion);
  // This is for Jlab
  xxx[0] = pow(12.0107, 1. / 3.); // C
  xxx[1] = pow(55.845, 1. / 3.);  // Fe
  xxx[2] = pow(207.2, 1. / 3.);   // Pb
  // This is for HERMES
  // xxx[0] = pow(20.1797,1./3.); // Ne   here goes A^1/3
  // xxx[1] = pow(83.7980,1./3.); // Kr
  // xxx[2] = pow(131.293,1./3.); // Xe
  xxx[3] = xxx[0];
  xxx[4] = xxx[1];
  xxx[5] = xxx[2];
  // double input_value = 0;
  // double input_error = 0;
  for (int i = 0; i < 3; ++i) {
    double A = pow(xxx[i], 3.0);
    std::cout << "Value of c " << m->GetC((int)A) << " for A " << (int)A << std::endl;
  }
  // This is for HERMES
  // std::cout << "Calling dataHandler" << std::endl;
  // auto fc = dataHandler(config);
  // std::cout << "dataHandler run succesfuly" << std::endl;
  // TFile *fout = new TFile("fullfit.root","RECREATE");

  TFile* fInputData = new TFile("InputData-JLab.root", "READ");
  std::pair<TGraphErrors*, TGraphErrors*> tge;

  for (int iQ2 = 0; iQ2 < Q2DIM; ++iQ2) { // There is only one bin in Q2 for HERMES
    for (int iz = 0; iz < ZDIM; ++iz) {
      std::cout << "z-bin #" << iz + 1 << " z-bin center = " << zbin[iz] << std::endl;
      if ((config->m_zBinOfInterest != -1) &&
          ((config->m_zBinOfInterest - 1) != iz)) {
        std::cout << "Ignoring this bin" << std::endl;
        continue;
      }
      if ((config->m_Q2BinOfInterest != -1) &&
          ((config->m_Q2BinOfInterest - 1) != iQ2)) {
        std::cout << "Ignoring this bin" << std::endl;
        continue;
      }
      tge.first = (TGraphErrors*)fInputData->Get(Form("tge_PT2_slice_%d_zbin_%d", iQ2 + 1, iz + 1));
      tge.second = (TGraphErrors*)fInputData->Get(Form("tge_RM_slice_%d_zbin_%d", iQ2 + 1, iz + 1));
      double* p1 = tge.first->GetY();
      double* p2 = tge.second->GetY();
      double* pe1 = tge.first->GetEY();
      double* pe2 = tge.second->GetEY();
      values[0] = p1[0];
      values[1] = p1[1];
      values[2] = p1[2];
      values[3] = p2[0];
      values[4] = p2[1];
      values[5] = p2[2];
      errors[0] = sqrt(pow(pe1[0], 2) + pow(SYSTEMATIC_DPT2 * p1[0], 2));
      errors[1] = sqrt(pow(pe1[1], 2) + pow(SYSTEMATIC_DPT2 * p1[1], 2));
      errors[2] = sqrt(pow(pe1[2], 2) + pow(SYSTEMATIC_DPT2 * p1[2], 2));
      errors[3] = sqrt(pow(pe2[0], 2) + pow(SYSTEMATIC_RM * p2[0], 2));
      errors[4] = sqrt(pow(pe2[1], 2) + pow(SYSTEMATIC_RM * p2[1], 2));
      errors[5] = sqrt(pow(pe2[2], 2) + pow(SYSTEMATIC_RM * p2[2], 2));

      m->SetBinRatio(iz, zbinw[iz], binratios[iz]); // For energy loss

      data(0) = values[0];
      data(1) = values[1];
      data(2) = values[2];
      data(3) = values[3];
      data(4) = values[4];
      data(5) = values[5];

      V(0, 0) = TMath::Power(errors[0], 2);
      V(1, 1) = TMath::Power(errors[1], 2);
      V(2, 2) = TMath::Power(errors[2], 2);
      V(3, 3) = TMath::Power(errors[3], 2);
      V(4, 4) = TMath::Power(errors[4], 2);
      V(5, 5) = TMath::Power(errors[5], 2);

      const double rho = 0;
      V(0, 3) = rho * errors[0] * errors[3];
      V(1, 4) = rho * errors[1] * errors[4];
      V(2, 5) = rho * errors[2] * errors[5];
      V(3, 0) = V(0, 3);
      V(4, 1) = V(1, 4);
      V(5, 2) = V(2, 5);

      V.Print();
      V.Invert();
      V.Print();
      data.Print();

      TMinuit* gMinuit = new TMinuit(8); //initialize TMinuit with a maximum of N params
      gMinuit->SetFCN(fcn);
      double arglist[10];
      int ierflg = 0;
      arglist[0] = 1;
      gMinuit->mnexcm("SET ERR", arglist, 1, ierflg);
      arglist[0] = 3;
      gMinuit->mnexcm("SET PRI", arglist, 1, ierflg);
      const double sigma0 = config->m_initial_sigma;
      double vstart[] = { 0.4775, 1.6, sigma0, 2.5, 0.0, 0.2 };
      double step[] = { 0.01, 0.01, 0.01, 0.5, 0.00001, 0.01 };
      double lim_lo[] = { 0., 0.0001, -0.01, 0.1, -1.0, -0.1 };
      double lim_hi[] = { 10., 400., 400., 100.0, 1.0, 10.0 };
      if (false) {
        lim_lo[4] = -10.0;
        lim_hi[4] = +10.0;
      }
      // gMinuit->mnparm(0, "Q0",    2.286, step[0], lim_lo[0],lim_hi[0],ierflg); // q-hat
      gMinuit->mnparm(0, "Q0", 0.7, step[0], lim_lo[0], lim_hi[0], ierflg);           // q-hat
      gMinuit->mnparm(1, "LP", 1.6, step[1], lim_lo[1], lim_hi[1], ierflg);           // production length
      gMinuit->mnparm(2, "SIGMA", vstart[2], step[2], lim_lo[2], lim_hi[2], ierflg);  // prehadron cross section
      gMinuit->mnparm(3, "DLOG", vstart[3], step[3], lim_lo[3], lim_hi[3], ierflg);   // parameter needed for log description
      gMinuit->mnparm(4, "DZ", vstart[4], step[4], lim_lo[4], lim_hi[4], ierflg);     // z shift due to energy loss
      gMinuit->mnparm(5, "CASCAD", vstart[5], step[5], lim_lo[5], lim_hi[5], ierflg); // Cascade parameter
      // New parameters that should be treated perturbatively
      gMinuit->mnparm(6, "C1", 0, 0.0001, -10, 10, ierflg); // new coeff 1
      gMinuit->mnparm(7, "C2", 0, 0.0001, -10, 10, ierflg); // new coeff 2
      // Parameter fixing
      if (!config->m_qhat)
        gMinuit->FixParameter(0); // q-hat
      if (!config->m_lp)
        gMinuit->FixParameter(1); // production length
      if (!config->m_preh)
        gMinuit->FixParameter(2); // prehadron cross section
      if (!config->m_logbehavior)
        gMinuit->FixParameter(3); // Log description
      if (!config->m_energyloss)
        gMinuit->FixParameter(4); // Energy Loss
      if (!config->m_cascade)
        gMinuit->FixParameter(5); // Cascade Parameter
      if (!config->m_testing)
        gMinuit->FixParameter(6);
      if (!config->m_testing)
        gMinuit->FixParameter(7);

      /* Testing new parameters */
      // gMinuit->SetParameter(0,2.286);
      // gMinuit->FixParameter(0);
      gMinuit->FixParameter(6);
      gMinuit->FixParameter(7);
      /**************************/

      // Now ready for minimization step
      arglist[0] = 500;
      arglist[1] = 1.;
      gMinuit->mnexcm("MIGRAD", arglist, 8, ierflg);
      // gMinuit->mnexcm("HESSE", arglist, 8,ierflg);
      /*
            std::cout << "STARTING TO SEARCH FOR A FIT IMPROVEMENT" << std::endl;
            gMinuit->FixParameter(0);
            gMinuit->FixParameter(1);
            gMinuit->Release(7);
            gMinuit->mnexcm("MIGRAD", arglist, 8,ierflg);
            gMinuit->mnexcm("HESSE", arglist, 8,ierflg);
*/
      // gMinuit->mnexcm("IMPROVE", arglist, 8,ierflg);
      // double p0[10];
      // p0[1]=1; gMinuit->mnexcm("MINOS", p0, 6,ierflg);
      // p0[1]=2; gMinuit->mnexcm("MINOS", p0, 6,ierflg);
      // p0[1]=7; gMinuit->mnexcm("MINOS", p0, 6,ierflg);
      // p0[1]=8; gMinuit->mnexcm("MINOS", p0, 6,ierflg);
      if (config->doMINOSErrors == true) {
        double p0[10];
        for (int i = 1; i <= 3; i++) {
          p0[1] = i;
          gMinuit->mnexcm("MINOS", p0, 6, ierflg);
        }
      }
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
      // fout->Write();
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
  TRandom3* rr = new TRandom3(); // this forces all gRandom uses to be TRandom3 instead of TRandom, the default.
  rr->SetSeed(9234);

  double z1[3], x1[3], errorz1[3];
  double z2[3], x2[3], errorz2[3];
  z1[0] = values[0];
  z1[1] = values[1];
  z1[2] = values[2];
  z2[0] = values[3];
  z2[1] = values[4];
  z2[2] = values[5];
  x1[0] = xxx[0];
  x1[1] = xxx[1];
  x1[2] = xxx[2];
  x2[0] = xxx[3];
  x2[1] = xxx[4];
  x2[2] = xxx[5];
  errorz1[0] = errors[0];
  errorz1[1] = errors[1];
  errorz1[2] = errors[2];
  errorz2[0] = errors[3];
  errorz2[1] = errors[4];
  errorz2[2] = errors[5];
  double val = 0;
  double err = 0;
  double xlolim = 0;
  double xuplim = 0;
  int iuint = 0;
  int NPAR = 8;
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
  result.m_qhat = par[0];
  result.m_lp = par[1];
  result.m_sigma_ph = par[2];
  result.m_log = par[3];
  result.m_dz = par[4];
  result.m_cascade = par[5];
  result.m_c1 = par[6];
  result.m_c2 = par[7];
  result.m_qhat_err = par_errors[0];
  result.m_lp_err = par_errors[1];
  result.m_sigma_ph_err = par_errors[2];
  result.m_log_err = par_errors[3];
  result.m_dz_err = par_errors[4];
  result.m_cascade = par_errors[5];
  result.m_c1_err = par_errors[6];
  result.m_c2_err = par_errors[7];
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
  fout << pT2[0] << myDelimeter << pT2[1] << myDelimeter << pT2[2] << myDelimeter;
  fout << Rm[0] << myDelimeter << Rm[1] << myDelimeter << Rm[2] << "\n";
  fout.close();
  if (config->outputPlots) { // plots
    std::cout << "Now doing fit plots with model " << std::endl;
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

    double q0 = result.m_qhat;
    std::vector<double> d_pT_dq0;
    std::vector<double> d_pT_dL;

    int i = 0;
    double x = 2.5;
    double dx = (6.2 - 2.5) / 25;
    while (x < 6.2) {
      std::cout << "Modelplot for A^1/3 = " << x << std::endl;
      callModel(x, par);

      double pT2 = ModelResultArray[0];
      double RM = ModelResultArray[1];
      double average_density = ModelResultArray[2];
      double multiplicty_density = ModelResultArray[3];

      average_density_fit.push_back(average_density);
      multiplicity_density_fit.push_back(multiplicty_density);

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
      uncertainty += pow(pT2 / q0 * result.m_qhat_err, 2);
      // uncertainty += pow(q0*average_density*result.m_lp_err, 2);
      // uncertainty += 2*pT2*average_density*correlation_factor[iz];
      uncertainty = sqrt(uncertainty);
      pt_fit_up.push_back(pT2 + uncertainty);
      pt_fit_down.push_back(pT2 - uncertainty);

      double uncertainty2 = 0;
      uncertainty2 += pow(multiplicty_density * (result.m_lp_err), 2);
      uncertainty2 = sqrt(uncertainty2);
      // uncertainty2 += 9*pow(RM,2)*pow(average_density,2)*pow(result.m_lp_err,2);
      // uncertainty2 = 3*RM*0.11*result.m_lp_err;
      // uncertainty2 = sqrt(uncertainty2);
      rm_fit_up.push_back(RM + uncertainty2);
      rm_fit_down.push_back(RM - uncertainty2);

      std::cout << "Average density " << average_density << std::endl;

      std::cout << "p_T^2 = " << pT2 << " +/- " << uncertainty << "GeV^2" << std::endl;
      std::cout << "R_M = " << RM << " +/- " << uncertainty2 << std::endl;
      /*
            TH1F *histo = new TH1F("histo",";R_{M};Counts",25,0.5,1);
            int MCSTEPS = 50;
            for (int im = 0; im < MCSTEPS; ++im) {
                par[1] = rr->Gaus(result.m_lp,result.m_lp_err);
                callModel(x,par);
                histo->Fill(ModelResultArray[1]);
            }
            TCanvas *c = new TCanvas("c","title",600,450);
            histo->Draw();
            c->Print(Form("hist_zbin_%d_A13_%.1f.pdf",iz,x));
            uncertainty2 = histo->GetStdDev(1);
            rm_fit_up.push_back(RM + uncertainty2);
            rm_fit_down.push_back(RM - uncertainty2);
            histo=nullptr; delete histo;
            c=nullptr; delete c;
*/
      /* done */
      i++;
      x += dx;
    }

    result.m_tg_data_pT = TGraphErrors(3, x1, z1, errorz1, errorz1);
    result.m_tg_data_Rm = TGraphErrors(3, x2, z2, errorz2, errorz2);

    double zeros[3] = { 0, 0, 0 };
    result.m_tg_pT = TGraphErrors(3, x1, pT2, zeros, zeros);
    result.m_tg_Rm = TGraphErrors(3, x2, Rm, zeros, zeros);

    int npoints = pt_x.size();
    result.m_tg_average_density = TGraph(npoints, pt_x.data(), average_density_fit.data());
    result.m_tg_multiplicity_density = TGraph(npoints, pt_x.data(), multiplicity_density_fit.data());
    result.m_tg_pT_extrapolation = TGraphErrors(npoints, pt_x.data(), pt_fit.data(), pt_fiterr.data(), pt_fiterr.data());
    result.m_tg_pT_extrapolation_up = TGraphErrors(npoints, pt_x.data(), pt_fit_up.data(), pt_fiterr.data(), pt_fiterr.data());
    result.m_tg_pT_extrapolation_down = TGraphErrors(npoints, pt_x.data(), pt_fit_down.data(), pt_fiterr.data(), pt_fiterr.data());
    result.m_tg_Rm_extrapolation = TGraphErrors(npoints, rm_x.data(), rm_fit.data(), rm_fiterr.data(), rm_fiterr.data());
    result.m_tg_Rm_extrapolation_up = TGraphErrors(npoints, rm_x.data(), rm_fit_up.data(), rm_fiterr.data(), rm_fiterr.data());
    result.m_tg_Rm_extrapolation_down = TGraphErrors(npoints, rm_x.data(), rm_fit_down.data(), rm_fiterr.data(), rm_fiterr.data());
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
