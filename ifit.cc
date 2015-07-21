#include "ifit.h"

double SYSTEMATIC_DPT2 = 0.04;
double SYSTEMATIC_RM = 0.03;
int ZDIM = 4;

// At the beggining I will do everything here

/****************     This is the input data
z_h dPt2 Error Rm Error
Nucleus #1
0.313333  0.0064  0.0013  0.870164  0.0321384
0.536667  0.0067  0.0022  0.872621  0.0310056
0.75      -0.0088 0.0044  0.856658  0.0374072
0.94      -0.0131 0.0073  0.788588  0.0356487
SetData
Nucleus #2
0.313333  0.0205  0.0015  0.736377  0.0313015
0.536667  0.0228  0.0025  0.695501  0.0273214
0.75      0.0012  0.0051  0.635427  0.0327105
0.94      0.0021  0.009   0.539358  0.0269801
SetData
Nucleus #3
0.313333  0.0269  0.0019  0.668259  0.0332506
0.536667  0.03    0.0033  0.632413  0.0268708
0.75      0.0071  0.0067  0.594249  0.0284847
0.94      -0.0021 0.0116  0.459519  0.0264920

**********************************************/

/* HERMES data */
double zbin[4] = {0.32, 0.53, 0.75, 0.94};

double dPt2_zbin[3][4] =
{
  {0.32, 0.53, 0.75, 0.94},
  {0.31, 0.54, 0.75, 0.94},
  {0.31, 0.54, 0.75, 0.94}
};

double dPt2_values[3][4] =
{
  {0.0064, 0.0067, -0.0088, -0.0131},
  {0.0205, 0.0228, 0.0012, 0.0021},
  {0.0269, 0.0300, 0.0071, -0.0021}
};

double dPt2_errors[3][4] = 
{
  {0.0013, 0.0022, 0.0044, 0.0073},
  {0.0015, 0.0025, 0.0051, 0.0090},
  {0.0019, 0.0033, 0.0067, 0.0116}
};

double RM_zbin[3][4] =
{
  {0.32, 0.53, 0.75, 0.94},
  {0.31, 0.54, 0.75, 0.94},
  {0.31, 0.54, 0.75, 0.94}
};


double RM_values[3][4] =
{
  {0.870164,0.872621,0.856658,0.788588},
  {0.736377,0.695501,0.635427,0.539358},
  {0.668259,0.632413,0.594249,0.459519}
};

double RM_errors[3][4] = 
{
  {0.0321384,0.0310056,0.0374072,0.0356487},
  {0.0313015,0.0273214,0.0327105,0.0269801},
  {0.0332506,0.0268708,0.0284847,0.0264920}
};


/* Jlab data 
double zbin[10] = {0.05,0.15,0.25,0.35,0.45,0.55,0.65,0.75,0.85,0.95};

double dPt2_values[3][10] = {
{0.000371518,0.00863379,0.0151782,0.0141445,0.0133822,0.00665999,0.00857385,-6.41318e-05,0.0142515,0.0168077},
{0.000856483,0.0160724,0.0315945,0.0280917,0.0266616,0.0288261,0.022009,0.0191083,0.0326184,0.0449803},
{0.0014003,0.0215559,0.041029,0.0356387,0.0351237,0.0300144,0.0243309,0.0355309,0.0165417,0.0410554}
};

double dPt2_errors[3][10] = {
{8.62358e-05,0.000212014,0.000534801,0.000913602,0.00142702,0.00526272,0.00285298,0.0102465,0.0279433,0.0159634},
{7.82608e-05,0.00020264,0.00053443,0.000900986,0.00124469,0.00448796,0.00300828,0.00957407,0.0151779,0.0172},
{9.45994e-05,0.000259157,0.000697902,0.00130221,0.00179537,0.00335751,0.00401528,0.00965185,0.0411052,0.019054}
};

double RM_values[3][10] = {
{1.13479,0.962451,0.889687,0.860711,0.849438,0.853472,0.827186,0.710289,0.724836,0.699427},
{1.12019,0.857052,0.715913,0.66561,0.638018,0.609745,0.566012,0.495528,0.464202,0.425779},
{0.958637,0.717765,0.572328,0.52392,0.492814,0.489257,0.445196,0.315524,0.363646,0.285614}
};

double RM_errors[3][10] = {
{0.00409792,0.00267193,0.00378442,0.00488795,0.00618195,0.0124229,0.00915825,0.102163,0.0290839,0.0364005},
{0.00366706,0.00218369,0.00280078,0.00353991,0.00429012,0.00686596,0.0259369,0.0344201,0.0145574,0.0165368},
{0.0036491,0.0021428,0.00271263,0.00337343,0.00426634,0.0180179,0.00614704,0.0619927,0.0136452,0.0209563}
};
*/

double func_array[2] = {0,0};

double zzz[6],errorzzz[6],xxx[6];

double fermi(double f) {
  // To be included
  return 0.0;
}

Model *m = new Model("default");

void callModel(double A,double *par){
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
  //calculate chisquare
  double chisq = 0;
  double delta;
  chisq = 0.;
  callModel(xxx[0],par);
  delta = (zzz[0]-func_array[0])/errorzzz[0];
  chisq += delta*delta;
  callModel(xxx[1],par);
  delta = (zzz[1]-func_array[0])/errorzzz[1];
  chisq += delta*delta;
  callModel(xxx[2],par);
  delta = (zzz[2]-func_array[0])/errorzzz[2];
  chisq += delta*delta;
  callModel(xxx[3],par);
  delta = (zzz[3]-func_array[1])/errorzzz[3];
  chisq += delta*delta;
  callModel(xxx[4],par);
  delta = (zzz[4]-func_array[1])/errorzzz[4];
  chisq += delta*delta;
  callModel(xxx[5],par);
  delta = (zzz[5]-func_array[1])/errorzzz[5];
  chisq += delta*delta;
  return chisq;
}

void fcn(int &NPAR, double *gin, double &f, double *par, int iflag) {
  f = chisq(par);
}

void ifit(){
  m->Initialization();
  // This is for Jlab
  // xxx[0]=pow(12.0107,1./3.); // C
  // xxx[1]=pow(55.845,1./3.);  // Fe
  // xxx[2]=pow(207.2,1./3.); // Pb
  // This is for HERMES
  xxx[0]=pow(20.1797,1./3.); // Ne
  xxx[1]=pow(83.798,1./3.);  // Kr
  xxx[2]=pow(131.293,1./3.); // Xe
  xxx[3]=xxx[0];
  xxx[4]=xxx[1];
  xxx[5]=xxx[2];
  std::cout << "Starting iFit at " << std::endl; // I would like to print time here
  // Here the rest of the code
  TFile *fout = new TFile("fullfit.root","RECREATE");
  // for the future ---> here I have only one Q2 bin so do it thiking on multiple bins
  // I think now I will interpolate RM values from data to be in the same z-bins that dPt2
  //#pragma omp parallel for 
  for (int iz=0; iz<ZDIM; ++iz) {
    std::cout << "Working for bin #" << iz+1 << " of " << ZDIM << std::endl;
    for (int a=0; a<3; ++a) {
      zzz[a] = (dPt2_values[a][iz]-fermi(a)); // fermi is now returning zero
      zzz[a+3] = RM_values[a][iz]; // this ones need interpolation
      errorzzz[a] = sqrt(pow(dPt2_errors[a][iz],2)+pow(SYSTEMATIC_DPT2*dPt2_values[a][iz],2));
      errorzzz[a+3] = sqrt(pow(RM_errors[a][iz],2)+pow(SYSTEMATIC_RM*RM_values[a][iz],2));
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
    double vstart[] = {0.7, 1.6, 20.,2.5,0.0};
    double step[]   = {0.03,0.8,3.,0.5,0.005};
    double lim_lo[] = {0.,0.0001,-60.,0.1,-0.001}; // negative limit on cross section models inelastic bin migration                   
    double lim_hi[] = {1000.,50.,1000.,1000.0,1000.};
    gMinuit->mnparm(0, "a1", vstart[0], step[0], lim_lo[0],lim_hi[0],ierflg); // q-hat
    gMinuit->mnparm(1, "a2", vstart[1], step[1], lim_lo[1],lim_hi[1],ierflg); // production length
    gMinuit->mnparm(2, "a3", vstart[2], step[2], lim_lo[2],lim_hi[2],ierflg); // prehadron cross section
    gMinuit->mnparm(3, "a4", vstart[3], step[3], lim_lo[3],lim_hi[3],ierflg); // parameter needed for log description
    gMinuit->mnparm(4, "a5", vstart[4], step[4], lim_lo[4],lim_hi[4],ierflg); // z shift due to energy loss      
    //gMinuit->FixParameter(0);
    gMinuit->FixParameter(3);
    gMinuit->FixParameter(4);
    // Now ready for minimization step
    arglist[0] = 500;
    arglist[1] = 1.;
    gMinuit->mnexcm("MIGRAD", arglist, 5,ierflg);      
    // Print results
    double amin,edm,errdef;
    int nvpar,nparx,icstat;
    gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
    gMinuit->mnprin(3,amin);
    modelplot(0,iz);
    fout->Write();
  }
  
  std::cout << "iFit has finished" << std::endl;
  //return 0;
}

void modelplot(int iQ2x, int iz){
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
    gMinuit->mnpout(parNo, chnam, val, err, xlolim, xuplim, iuint);
    par[parNo]=val;
    par_errors[parNo]=err;
  }
  double chisquared = chisq(par);
  /* I don't know what this piece of code is does
  // Now make the plots of lpA for C, Fe, and Pb, with the final parameters, only for the first bin:
  if(doC_lpA_plot==0){
    doC_lpA_plot=1; // turn it on
    callModel(xxx[0],par);
    doC_lpA_plot=-1; // turn it off and keep it off (or could set it to 2 to accumulate, and change "if" to include 2 as a possibility)
  }
  if(doFe_lpA_plot==0){
    doFe_lpA_plot=1; // turn it on
    callModel(xxx[1],par);
    doFe_lpA_plot=-1; // turn it off and keep it off
  }
  if(doPb_lpA_plot==0){
    doPb_lpA_plot=1; // turn it on
    callModel(xxx[2],par);
    doPb_lpA_plot=-1; // turn it off and keep it off
  }
  */
  // At this point, we know the parameters, so let's write them out
  std::ofstream fout;
  fout.open("Fit_output", std::ios::out | std::ios::app);
  fout << iQ2x <<iz <<"\t";
  fout << zbin[iz] << "\t";
  fout <<par[0]<<"\t"<<par[1]<<"\t"<<par[2]<<"\t"<<par[3]<<"\t"<<par[4]<<"\t";
  fout <<par_errors[0]<<"\t"<<par_errors[1]<<"\t"<<par_errors[2]<<"\t"<<par_errors[3]<<"\t"<<par_errors[4]<<"\t"<<chisquared<<"\n"; 
  //fout<<C_deltaE<<" "<<Fe_deltaE<<" "<<Pb_deltaE<<" \n";
  fout.close();
  int nbins = 40;
  double pt_fit[40];
  double pt_fiterr[40];
  double pt_x[40];
  double mr_fit[40];
  double mr_fiterr[40];
  double mr_x[40];
  for (int i=0;i<nbins; ++i) {
    callModel(i/6.,par);
    pt_fit[i]=func_array[0];
    pt_fiterr[i]=0.;
    pt_x[i] = i/6.;
    mr_fit[i]=func_array[1];
    mr_fiterr[i]=0.;
    mr_x[i] = i/6.;
  }
  std::string mrname;
  std::string ptname;
  std::ostringstream out_mr, out_pt;
  out_mr << "mr" << iQ2x << iz;
  mrname = out_mr.str();
  out_pt << "pt" << iQ2x << iz;
  ptname = out_pt.str();
  TCanvas *c1 = new TCanvas(ptname.c_str(),"pT Broadening",800,600);
  TCanvas *c2 = new TCanvas(mrname.c_str(),"Multiplicity Ratio",800,600);
  c1->SetGrid();c2->SetGrid();
  TGraphErrors *pt_broadening = new TGraphErrors(3,x1,z1,errorz1,errorz1);
  TGraphErrors *ptfit = new TGraphErrors(nbins,pt_x,pt_fit,pt_fiterr,pt_fiterr);
  TGraphErrors *mult_ratio = new TGraphErrors(3,x2,z2,errorz2,errorz2);
  TGraphErrors *mrfit = new TGraphErrors(nbins,mr_x,mr_fit,mr_fiterr,mr_fiterr);
  // pt_broadening->GetXaxis()->SetTitle("A^{1/3}");
  // pt_broadening->GetYaxis()->SetTitle("<#{Delta}P_{T}^{2}>");
  // mult_ratio->GetXaxis()->SetTitle("A^{1/3}");
  // mult_ratio->GetYaxis()->SetTitle("R_{m}");
  c1->cd();
  // TH1 *frame1 = c1->DrawFrame(2.,0.,6.2,0.065);
  // frame1->SetTitle(out_pt.str().c_str());
  // frame1->GetXaxis()->SetTitle("A^{1/3}");
  // frame1->GetYaxis()->SetTitle("<#Delta P_{T}^{2}>");
  // c1->Update();
  pt_broadening->SetTitle(out_pt.str().c_str());
  pt_broadening->GetXaxis()->SetTitle("A^{1/3}");
  pt_broadening->GetYaxis()->SetTitle("<#Delta P_{T}^{2}>");
  pt_broadening->SetMarkerColor(kBlue);
  pt_broadening->SetMarkerStyle(21);
  pt_broadening->Draw("APE");
  ptfit->SetLineColor(kBlue);
  ptfit->SetMarkerStyle(21);
  ptfit->Draw("L SAME");
  c1->Write();
  out_pt << ".pdf";
  c1->Print(out_pt.str().c_str());
  // Now do multiplicity ratio plot
  c2->cd();
  // TH1 *frame2 = c2->DrawFrame(2.,0.,6.2,1.2);
  // frame2->SetTitle(out_mr.str().c_str());
  // frame2->GetXaxis()->SetTitle("A^{1/3}");
  // frame2->GetYaxis()->SetTitle("R_{m}");
  // c2->Update();
  mult_ratio->SetTitle(out_mr.str().c_str());
  mult_ratio->GetXaxis()->SetTitle("A^{1/3}");
  mult_ratio->GetYaxis()->SetTitle("R_{m}");
  mult_ratio->SetMarkerColor(kBlue);
  mult_ratio->SetMarkerStyle(21);
  mult_ratio->Draw("APE");
  mrfit->SetLineColor(kBlue);
  mrfit->SetMarkerStyle(21);
  mrfit->Draw("L SAME");
  c2->Write();
  out_mr << ".pdf";
  c2->Print(out_mr.str().c_str());
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
  delete(m);
  return 0;
}
