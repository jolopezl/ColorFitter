#include "ifit.h"

#include <time.h>

// const double SYSTEMATIC_DPT2 = 0.04;


const int ZDIM  = 4;
const int Q2DIM = 1;
double zbin[ZDIM]      = {0.32, 0.53, 0.75, 0.94}; // pi+
double zbinw[ZDIM]     = {0.20,0.22,0.22,0.16}; // Approx.
// double zbin[ZDIM]      = {0.32, 0.53, 0.75, 0.95}; // pi-
// double zbinw[ZDIM]     = {0.20,0.22,0.22, 0.16+0.05}; // Approx.
// double binratios[ZDIM] = {0.469058,0.290631,0.0789474,0}; // Computed with 1M events
double func_array[2] = {0,0};
double zzz[6] = {0,0,0,0,0,0};
double errorzzz[6] = {0,0,0,0,0,0};
double xxx[6] = {0,0,0,0,0,0};
double pT2[3] = {0,0,0};
double Rm[3] = {0,0,0};

/* values from python/interpolate.py */
// PI+
double binratios[ZDIM] = {0.482203,0.461464,0.249762,0}; // PI+ no cuts
double rm[3][4] = 
{ {0.893189114368,0.885454096825,0.880935853275,0.798520384419},
  {0.78747612087,0.744660997913,0.679028679486,0.551673817154},
  {0.736762500635,0.684223383665,0.619689942725,0.498076090992} };
double rmerr[3][4] =
{ {0.0594409344724,0.0515307622582,0.0634878265064,0.0682394907588},
  {0.0542930099596,0.0447182315218,0.05222907333,0.0527700155986},
  {0.0535218789044,0.0411665583174,0.0503850083386,0.0529182285411} };
double rmerrstat[3][4] =
{ {0.00854270357306,0.0130038108586,0.0205705417395,0.0297430417983},
  {0.00720625779696,0.011650000993,0.0172864610215,0.0235603208711},
  {0.00912856753222,0.0140599568342,0.0205578877811,0.027635417296}};

// PI-
/*
double binratios[ZDIM] = {0.359961,0.320395,0.0869321,0}; // PI- no cuts
double rm[3][4] = 
{ {0.885935982744,0.875522790678,0.885865846771,0.801608365614},
  {0.778946938187,0.736093541044,0.71029494015,0.591222317512},
  {0.733427597524,0.693235411861,0.638260246474,0.542999201533}};
double rmerr[3][4] = 
{ {0.0705191510151,0.0524430996896,0.0849834597638,0.0958307524956},
  {0.0681263662457,0.0445115353199,0.0743614206518,0.0806936013706},
  {0.066787550373,0.0450438092897,0.0741953749576,0.0821750839267}};
double rmerrstat[3][4] =
{ {0.00926217293666,0.0149677556729,0.0245997184635,0.0336987437848},
  {0.00840692796654,0.0139179331634,0.0204641850967,0.0275495017666},
  {0.010502759355,0.0165367281117,0.0247813693329,0.0336919619725}};
*/

// I would like this not to be global, it's already a pointer, but fcn does not have more arguments ¿?
Model *m = new Model("default"); 

void callModel(const double A,double *par){
  // qhat, lp, pre-hadron cross-section, log behaviour, energy loss
  std::vector<double> my_pars = {par[0],par[1],par[2],par[3],par[4]};
  double nucleus = (double) A*A*A;
  m->SetParameters(my_pars);
  m->Compute(nucleus);
  func_array[0] = m->Get1(); 
  func_array[1] = m->Get2();
}

// I will write the Chi-Squared and some other functions here
double chisq(double *par){
  double chisq = 0.0;
  double delta = 0.0;
  callModel(xxx[0],par);
  pT2[0] = func_array[0];
  Rm[0] = func_array[1];
  callModel(xxx[1],par);
  pT2[1] = func_array[0];
  Rm[1] = func_array[1];
  callModel(xxx[2],par);
  pT2[2] = func_array[0];
  Rm[2] = func_array[1];
  delta = (zzz[0]-pT2[0])/errorzzz[0];
  chisq += delta*delta;
  delta = (zzz[1]-pT2[1])/errorzzz[1];
  chisq += delta*delta;
  delta = (zzz[2]-pT2[2])/errorzzz[2];
  chisq += delta*delta;
  delta = (zzz[3]-Rm[0])/errorzzz[3];
  chisq += delta*delta;
  delta = (zzz[4]-Rm[1])/errorzzz[4];
  chisq += delta*delta;
  delta = (zzz[5]-Rm[2])/errorzzz[5];
  chisq += delta*delta;
  return chisq;
}

void fcn(int &NPAR, double *gin, double &f, double *par, int iflag) {
  f = chisq(par);
}

std::vector<myResult*> ifit(myConfig *config) {
  std::vector<myResult*> vResult;
  myResult *result = new myResult();
  m->Initialization();
  m->DoEnergyLoss(config->m_energyloss);
  m->DoLogBehavior(config->m_logbehavior);
  // m->DoFermiMotion(config->m_fermimotion);
  // This is for Jlab
  // xxx[0]=pow(12.0107,1./3.); // C
  // xxx[1]=pow(55.845,1./3.);  // Fe
  // xxx[2]=pow(207.2,1./3.); // Pb
  // This is for HERMES
  xxx[0]=1.1*pow(20.1797,1./3.); // Ne
  xxx[1]=1.1*pow(83.7980,1./3.);  // Kr
  xxx[2]=1.1*pow(131.293,1./3.); // Xe
  xxx[3]=xxx[0];
  xxx[4]=xxx[1];
  xxx[5]=xxx[2];
  double input_value=0;
  double input_error=0;
  for (int i=0; i<3; ++i) {
    double A = pow(xxx[i],3.0);
    std::cout << "Value of c " << m->GetC((int) A) << " for A " << (int) A << std::endl;
  }
  // dataHandler called here:
  auto fc = dataHandler(config);
  // Here the rest of the code
  // TFile *fout = new TFile("fullfit.root","RECREATE");
  for (int iQ2=0; iQ2<Q2DIM; ++iQ2) { // There is only one bin in Q2 for HERMES
    for (int iz=0; iz<ZDIM; ++iz) {
      // Selects and specific z bin to fit.
      if ((config->m_zBinOfInterest != -1) && ((config->m_zBinOfInterest-1) != iz)) {
        std::cout << "Ignoring this bin" << std::endl;
        continue;
      }
      std::cout << "z-bin #" << iz+1 << " z-bin center = " << zbin[iz] << std::endl;
      m->SetBinRatio(iz,zbinw[iz],binratios[iz]); // For energy loss
      // m->SetFermiValues(xB,zbin[iz]);
      // std::cout << "Working Q^2-bin #" << iQ2+1 << "/" << Q2DIM << " and z-bin #" << iz+1 << "/" << ZDIM << std::endl;
      // std::cout << "Progress is " << 100*(iQ2+1)*(iz+1)/((double)(Q2DIM*ZDIM)) << "%" << std::endl;
      TRandom3 r;
      r.SetSeed(std::time(0));
      for (int a=0; a<3; ++a) {
        if (config->m_special_run) {
          if (config->m_subtraction) {
            input_value = fc[a]->m_value_corrected[iz];
            // input_error = fc[a]->m_stat_corrected[iz];
            input_error = fc[a]->m_err_corrected[iz];
          }
          else {
            input_value = fc[a]->m_value[iz];
            // input_error = fc[a]->m_stat[iz];
            input_error = fc[a]->m_err[iz];
          }
          zzz[a] = r.Gaus(input_value,input_error);
          errorzzz[a] = input_error;
          zzz[a+3] = r.Gaus(rm[a][iz],rmerrstat[a][iz]);
          errorzzz[a+3] = rmerrstat[a][iz];
        }
        else if (config->m_stat_only) {
          if (config->m_subtraction) {
            zzz[a] = fc[a]->m_value_corrected[iz];
            errorzzz[a] = fc[a]->m_stat_corrected[iz];
          }
          else {
            zzz[a] = fc[a]->m_value[iz];
            errorzzz[a] = fc[a]->m_stat[iz];
          }
          zzz[a+3] = rm[a][iz];
          errorzzz[a+3] = rmerrstat[a][iz];
        }
        else { // normal run
          if (config->m_subtraction) {
            zzz[a] = fc[a]->m_value_corrected[iz];
            errorzzz[a] = fc[a]->m_err_corrected[iz];
          }
          else {
            zzz[a] = fc[a]->m_value[iz];
            errorzzz[a] = fc[a]->m_err[iz];
          }
          zzz[a+3] = rm[a][iz];
          errorzzz[a+3] = rmerr[a][iz];
        }
      }
      TMinuit *gMinuit = new TMinuit(5);  //initialize TMinuit with a maximum of 5 params
      gMinuit->SetFCN(fcn);      
      double arglist[10];
      int ierflg = 0;      
      arglist[0] = 1;
      gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);
      arglist[0] = 3;
      gMinuit->mnexcm("SET PRI", arglist ,1,ierflg);      
      // Set starting values and step sizes for parameters
      // double vstart[] = {0.7, 1.6, 20.,2.5,0.0};
      double vstart[] = {0.4775, 1.6, 20.,2.5,0.0};
      double step[]   = {0.01,0.01, 1.,0.5,0.00001};
      double lim_lo[] = {0.,0.0001,-60.,0.1,-0.001}; // negative limit on cross section models inelastic bin migration
      //double lim_lo[] = {0.,0.1,-60.,0.1,0.0}; // negative limit on cross section models inelastic bin migration                   
      double lim_hi[] = {10.,50.,500.,1000.0,10.};
      gMinuit->mnparm(0, "a1", vstart[0], step[0], lim_lo[0],lim_hi[0],ierflg); // q-hat
      gMinuit->mnparm(1, "a2", vstart[1], step[1], lim_lo[1],lim_hi[1],ierflg); // production length
      gMinuit->mnparm(2, "a3", vstart[2], step[2], lim_lo[2],lim_hi[2],ierflg); // prehadron cross section
      gMinuit->mnparm(3, "a4", vstart[3], step[3], lim_lo[3],lim_hi[3],ierflg); // parameter needed for log description
      gMinuit->mnparm(4, "a5", vstart[4], step[4], lim_lo[4],lim_hi[4],ierflg); // z shift due to energy loss      
      if (!config->m_qhat)        gMinuit->FixParameter(0); // q-hat
      if (!config->m_lp)          gMinuit->FixParameter(2); // production length
      if (!config->m_preh)        gMinuit->FixParameter(3); // prehadron cross section
      if (!config->m_logbehavior) gMinuit->FixParameter(3); // Log description
      if (!config->m_energyloss)  gMinuit->FixParameter(4); // Energy Loss
      // Now ready for minimization step
      arglist[0] = 500;
      arglist[1] = 1.;
      gMinuit->mnexcm("MIGRAD", arglist, 5,ierflg);      
      // Print results
      double amin,edm,errdef;
      int nvpar,nparx,icstat;
      gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
      gMinuit->mnprin(3,amin);
      std::string bin_info = config->m_comment; // dummy value for HERMES
      double xB = -1; // dummy value for HERMES
      double Q2 = -1; // dummy value for HERMES
      modelplot(gMinuit,bin_info,iQ2,iz,Q2,xB,zbin[iz],config->m_output_fit,result);
      vResult.push_back(result);
      // fout->Write();
      delete(gMinuit);
    }
  // End of loop over z-bins
  }
  std::cout << "iFit has finished" << std::endl;
  return vResult;
}

double fermi(double m_xB, double m_zbinvalue, int inucleus) {
  // Computes the contribution of fermi momentum broadening to 
  // pT broadening using Boris's formula
  double avgFermi;// <(Fermi momentum)**2>
  //.033 Pb
  //.028 Fe
  //.029 C
  //.023 D
  // From Taya's study, not completely final: 
  //0.019 Pb
  //0.014 Fe
  //0.015 C
  //0.002 D
  avgFermi=-999.;
  //  if(inucleus==0){avgFermi=0.029-.023;} // Carbon
  //  if(inucleus==1){avgFermi=0.028-.023;} // Iron
  //  if(inucleus==2){avgFermi=0.033-.023;} // Lead
  if (inucleus == 0) avgFermi=0.015-.002; // Carbon
  if (inucleus == 1) avgFermi=0.014-.002; // Iron
  if (inucleus == 2) avgFermi=0.019-.002; // Lead
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
  double result = 0.6666666*x*x*z_h*z_h*avgFermi;
  return result; 
}

// For testing only
int test() {
  std::vector<std::string> atoms = {"Carbon","Iron","Lead"};
  std::vector<double> masses = {12.0107,55.845,207.2};
  std::vector<double> parms = {0.2, 7.0, 1.0,2.5,0.0}; //{ 0.2, 7.,1.0 }
  Model *m = new Model("default");
  m->SetParameters(parms);
  m->Initialization();
  std::vector<double> foo;
  double nucleus;
  double nu[3]={20.1797,83.798,131.293};
  for (int i=0; i<3; ++i){
    nucleus = (double) nu[i];
    m->Compute(nucleus);
    std::cout << nu[i] << "\t" << m->Get1() << "\t" << m->Get2() << std::endl;
  }
  for (int i=1; i<=6; ++i){
    nucleus = (double) i*i*i;
    m->Compute(nucleus);
    std::cout << i << "\t" << m->Get1() << "\t" << m->Get2() << std::endl;
  }
  delete(m);
  return 0;
}

// function to compite the model given a set of parameters and print the output to the screen
void justCompute(myConfig* config) {
  Model* model = new Model("toy");
  m->Initialization();
  m->DoEnergyLoss(config->m_energyloss);
  m->DoLogBehavior(config->m_logbehavior);
  double A_Ne = 1.1*pow(20.1797,1./3.); // Ne
  double A_Kr = 1.1*pow(83.7980,1./3.); // Kr
  double A_Xe = 1.1*pow(131.293,1./3.); // Xe
  double foo = 0.0;
  foo = pow(A_Ne,3.0);
  std::vector<double> parms = {0.2, 7.0, 1.0,2.5,0.0};
  m->SetParameters(parms);
  m->Compute(foo);
}

// this will be moved away someday to graphics.cc
void modelplot(TMinuit *g,
               std::string bin_info,
               int iQ2x, int iz, double Q2,
               double xB, double z,  
               std::string filename,
               myResult *result){
  double z1[3],x1[3],errorz1[3];  
  double z2[3],x2[3],errorz2[3];
  z1[0]=zzz[0];z1[1]=zzz[1];z1[2]=zzz[2];
  z2[0]=zzz[3];z2[1]=zzz[4];z2[2]=zzz[5];
  x1[0]=xxx[0];x1[1]=xxx[1];x1[2]=xxx[2];
  x2[0]=xxx[3];x2[1]=xxx[4];x2[2]=xxx[5];
  errorz1[0]=errorzzz[0];errorz1[1]=errorzzz[1];errorz1[2]=errorzzz[2];
  errorz2[0]=errorzzz[3];errorz2[1]=errorzzz[4];errorz2[2]=errorzzz[5];
  double val=0; 
  double err=0; 
  double xlolim=0; 
  double xuplim=0; 
  int iuint=0;
  int NPAR=5;
  TString chnam;
  double par[NPAR], par_errors[NPAR];
  std::ostringstream out;
  for (int parNo=0; parNo<NPAR; ++parNo) {
    out << "a" << parNo;
    chnam = (TString) out.str();
    out.flush();
    g->mnpout(parNo, chnam, val, err, xlolim, xuplim, iuint);
    par[parNo]=val;
    par_errors[parNo]=err;
  }
  double chisquared = chisq(par);
  // add values to result obj
  result->m_zbin = z;
  result->m_qhat = par[0];
  result->m_lp = par[1];
  result->m_sigma_ph = par[2];
  result->m_dz = par[3];
  // par[4] log parm
  result->m_qhat_err = par_errors[0];
  result->m_lp_err = par_errors[1];
  result->m_sigma_ph_err = par_errors[2];
  result->m_dz_err = par_errors[3];
  // par_errors[4] log parm err
  result->m_chi2 = chisquared;
  // At this point, we know the parameters, so let's write them out
  std::ofstream fout;
  fout.open(filename, std::ios::out | std::ios::app);
  fout.precision(10);
  if (iz == 0) fout << bin_info << "\n";
  if (Q2!=-1 && xB!=-1) {
    fout << iQ2x << "\t" << iz << "\t";
    fout << Q2 << "\t" << xB << "\t";
  }
  fout << z << "\t";
  for (int i=0; i<5; ++i){
    fout << par[i] << "\t";
  }
  for (int i=0; i<5; ++i){
    fout << par_errors[i] << "\t";
  }
  fout << chisquared << "\t";
  fout << pT2[0] << "\t" << pT2[1] << "\t" << pT2[2] << "\t";
  fout << Rm[0] << "\t" << Rm[1] << "\t" << Rm[2] << "\n"; 
  fout.close();
  // int nbins = 40;
  // double pt_fit[40];
  // double pt_fiterr[40];
  // double pt_x[40];
  // double mr_fit[40];
  // double mr_fiterr[40];
  // double mr_x[40];
  // for (int i=11;i<nbins; ++i) {
  //   callModel(i/6.,par);
  //   pt_fit[i]=func_array[0];
  //   pt_fiterr[i]=0.;
  //   pt_x[i] = i/6.;
  //   mr_fit[i]=func_array[1];
  //   mr_fiterr[i]=0.;
  //   mr_x[i] = i/6.;
  // }
  // std::string basename = filename;
  // basename.erase(basename.find_last_of("."), std::string::npos);
  // std::string mrname;
  // std::string ptname;
  // std::ostringstream out_mr, out_pt;
  // out_mr << basename << "_plot_" << "mr_" << iQ2x << "_" << iz;
  // mrname = out_mr.str();
  // out_pt << basename << "_plot_" << "pt_" << iQ2x << "_" << iz;
  // ptname = out_pt.str();
  // TCanvas *c1 = new TCanvas(ptname.c_str(),"pT Broadening",800,600);
  // TCanvas *c2 = new TCanvas(mrname.c_str(),"Multiplicity Ratio",800,600);
  // c1->SetGrid();c2->SetGrid();
  // TGraphErrors *pt_broadening = new TGraphErrors(3,x1,z1,errorz1,errorz1);
  // TGraphErrors *ptfit = new TGraphErrors(nbins,pt_x,pt_fit,pt_fiterr,pt_fiterr);
  // TGraphErrors *mult_ratio = new TGraphErrors(3,x2,z2,errorz2,errorz2);
  // TGraphErrors *mrfit = new TGraphErrors(nbins,mr_x,mr_fit,mr_fiterr,mr_fiterr);
  // c1->cd();
  // pt_broadening->SetTitle(out_pt.str().c_str());
  // pt_broadening->GetXaxis()->SetTitle("A^{1/3}");
  // pt_broadening->GetYaxis()->SetTitle("#Delta #LT p_{t}^{2} #GT");
  // pt_broadening->GetYaxis()->SetTitleOffset(1.5);
  // pt_broadening->SetMarkerColor(kRed);
  // pt_broadening->SetMarkerStyle(21);
  // pt_broadening->SetLineWidth(2);
  // const int fontAxesSize = 28;
  // const int fontAxesCode = 43;
  // pt_broadening->GetXaxis()->SetTitleFont(fontAxesCode);
  // pt_broadening->GetXaxis()->SetTitleSize(fontAxesSize);
  // pt_broadening->GetXaxis()->SetLabelFont(fontAxesCode);
  // pt_broadening->GetXaxis()->SetLabelSize(fontAxesSize);
  // pt_broadening->GetYaxis()->SetTitleFont(fontAxesCode);
  // pt_broadening->GetYaxis()->SetTitleSize(fontAxesSize);
  // pt_broadening->GetYaxis()->SetLabelFont(fontAxesCode);
  // pt_broadening->GetYaxis()->SetLabelSize(fontAxesSize);
  // pt_broadening->Draw("APE");
  // ptfit->SetLineColor(kRed);
  // ptfit->SetMarkerStyle(21);
  // ptfit->SetLineWidth(2);
  // ptfit->Draw("L SAME");
  // c1->Write();
  // out_pt << ".C";
  // c1->Print(out_pt.str().c_str());
  // // Now do multiplicity ratio plot
  // c2->cd();
  // mult_ratio->SetTitle(out_mr.str().c_str());
  // mult_ratio->GetXaxis()->SetTitle("A^{1/3}");
  // mult_ratio->GetYaxis()->SetTitle("R_{m}");
  // mult_ratio->GetYaxis()->SetTitleOffset(1.5);
  // mult_ratio->SetMarkerColor(kBlue);
  // mult_ratio->SetMarkerStyle(21);
  // mult_ratio->SetLineWidth(2);
  // mult_ratio->GetXaxis()->SetTitleFont(fontAxesCode);
  // mult_ratio->GetXaxis()->SetTitleSize(fontAxesSize);
  // mult_ratio->GetXaxis()->SetLabelFont(fontAxesCode);
  // mult_ratio->GetXaxis()->SetLabelSize(fontAxesSize);
  // mult_ratio->GetYaxis()->SetTitleFont(fontAxesCode);
  // mult_ratio->GetYaxis()->SetTitleSize(fontAxesSize);
  // mult_ratio->GetYaxis()->SetLabelFont(fontAxesCode);
  // mult_ratio->GetYaxis()->SetLabelSize(fontAxesSize);
  // mult_ratio->Draw("APE");
  // mrfit->SetLineColor(kBlue);
  // mrfit->SetMarkerStyle(21);
  // mrfit->SetLineWidth(2);
  // mrfit->Draw("L SAME");
  // c2->Write();
  // out_mr << ".C";
  // c2->Print(out_mr.str().c_str());
}
