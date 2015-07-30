#include "ifit.h"

const double SYSTEMATIC_DPT2 = 0.04;
const double SYSTEMATIC_RM = 0.03;

int ZDIM = 10;
int Q2DIM = 16;

double zbinw = 0.1;
double zbin[10] = {0.05,0.15,0.25,0.35,0.45,0.55,0.65,0.75,0.85,0.95}; // hide this?
double dPt2_values[3][10];
double dPt2_errors[3][10];
double RM_values[3][10];
double RM_errors[3][10];
double binratios[10] = {0,0,0,0,0,0,0,0,0,0};
double func_array[2] = {0,0};
double zzz[6],errorzzz[6],xxx[6];

double fermi(double f) {
  // To be included
  return 0.0;
}

// I would like this not to be global, it's already a pointer, but fcn does not have more arguments ¿?
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

void ifit(bool ENERGYLOSS, bool LOGBEHAVIOR, bool FERMIMOTION, int Q2XBINTOFIT, int ZBINTOFIT) {
  m->Initialization();
  m->DoEnergyLoss(ENERGYLOSS);
  m->DoLogBehavior(LOGBEHAVIOR);
  m->DoFermiMotion(FERMIMOTION);
  // This is for Jlab
  xxx[0]=pow(12.0107,1./3.); // C
  xxx[1]=pow(55.845,1./3.);  // Fe
  xxx[2]=pow(207.2,1./3.); // Pb
  // This is for HERMES
  // xxx[0]=pow(20.1797,1./3.); // Ne
  // xxx[1]=pow(83.798,1./3.);  // Kr
  // xxx[2]=pow(131.293,1./3.); // Xe
  xxx[3]=xxx[0];
  xxx[4]=xxx[1];
  xxx[5]=xxx[2];
  std::cout << "Starting iFit at " << std::endl;
  // Here the rest of the code
  TFile *fout = new TFile("fullfit.root","RECREATE");
  // Adding the read to multiple Q2 bins
  std::string line = "";
  std::string bin_info = "";
  std::ifstream infile1;
  std::ifstream infile2;
  std::ifstream infile3;
  infile1.open("broadening.txt");
  infile2.open("multiplicities.txt");
  infile3.open("binratios.txt");
  std::vector<std::string> words = {};
  std::string foo = "";
  for (int i=1; i<=2; ++i) { // read two dummy lines
    std::getline(infile1,foo);
    std::getline(infile2,foo);
  }
  for (int iQ2=0; iQ2<Q2DIM; ++iQ2) {
    // Read 12 lines
    // L#1      bin ifo
    // L#2-L#11 data
    // L#12     blank line
    std::getline(infile1,line);
    std::getline(infile2,line); // read the bin_info of other file, cross check?
    bin_info = line;
    for (int idx=0; idx<10; ++idx) {
      // read data
      std::getline(infile1, line); // broadening
      boost::split(words, line, boost::is_any_of(" "), boost::token_compress_on);
      // Casting string as double:
      // Alternatives
      // boost::lexical_cast<double>
      // std::stod
      // atof
      dPt2_values[0][idx] = boost::lexical_cast<double>(words.at(1));
      dPt2_errors[0][idx] = boost::lexical_cast<double>(words.at(2));
      dPt2_values[1][idx] = boost::lexical_cast<double>(words.at(3));
      dPt2_errors[1][idx] = boost::lexical_cast<double>(words.at(4));
      dPt2_values[2][idx] = boost::lexical_cast<double>(words.at(5));
      dPt2_errors[2][idx] = boost::lexical_cast<double>(words.at(6));
      words.clear();
      std::getline(infile2, line); // multiplicity
      boost::split(words, line, boost::is_any_of(" "), boost::token_compress_on);
      RM_values[0][idx] = boost::lexical_cast<double>(words.at(1));
      RM_errors[0][idx] = boost::lexical_cast<double>(words.at(2));
      RM_values[1][idx] = boost::lexical_cast<double>(words.at(3));
      RM_errors[1][idx] = boost::lexical_cast<double>(words.at(4));
      RM_values[2][idx] = boost::lexical_cast<double>(words.at(5));
      RM_errors[2][idx] = boost::lexical_cast<double>(words.at(6));
      words.clear();
      std::getline(infile3, line);
      binratios[idx] = boost::lexical_cast<double>(line);
    }
    std::getline(infile1,line); // skip empty line
    std::getline(infile2,line); // skip empty line
    // Grab bin info data
    words.clear();
    boost::split(words,bin_info,boost::is_any_of("< "),boost::token_compress_on);
    double Q2lo = std::stod(words.at(0));
    double Q2hi = std::stod(words.at(2));
    double xBlo = std::stod(words.at(3));
    double xBhi = std::stod(words.at(5));
    // Selects an specific Q2,x bin if desired.
    if ((Q2XBINTOFIT != -1) && ((Q2XBINTOFIT-1) != iQ2)) continue;
    // Main Loop over z-bins
    for (int iz=0; iz<ZDIM; ++iz) {
      // Selects and specific z bin to fit.
      if ((ZBINTOFIT != -1) && ((ZBINTOFIT-1) != iz)) continue;
      m->SetBinRatio(iz,zbinw,binratios[iz]); // For energy loss
      m->SetFermiValues((xBhi-xBlo)/2.0,zbin[iz]);
      std::cout << "Working Q^2-bin #" << iQ2+1 << "/" << Q2DIM << " and z-bin #" << iz+1 << "/" << ZDIM << std::endl;
      std::cout << "Bin info " << bin_info << std::endl;
      std::cout << "Progress is " << 100*(iQ2+1)*(iz+1)/((double)(Q2DIM*ZDIM)) << "%" << std::endl;
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
      //gMinuit->FixParameter(0); // Q-HAT
      if (!LOGBEHAVIOR) gMinuit->FixParameter(3); // Log description
      if (!ENERGYLOSS)  gMinuit->FixParameter(4); // Energy Loss
      // Now ready for minimization step
      arglist[0] = 500;
      arglist[1] = 1.;
      gMinuit->mnexcm("MIGRAD", arglist, 5,ierflg);      
      // Print results
      double amin,edm,errdef;
      int nvpar,nparx,icstat;
      gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
      gMinuit->mnprin(3,amin);
      modelplot(gMinuit,bin_info,iQ2,iz,(Q2hi-Q2lo)/2.0,(xBhi-xBlo)/2.0,zbin[iz]);
      fout->Write();
      delete(gMinuit);
    }
  // End of loop over z-bins
  }
  infile1.close();
  infile2.close();
  infile3.close();
  std::cout << "iFit has finished" << std::endl;
  //return 0;
}

void modelplot(TMinuit *g, std::string bin_info, int iQ2x, int iz, double Q2, double xB, double z){
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
  fout.precision(10);
  if (iz == 0) fout << bin_info << "\n";
  fout << iQ2x << "\t" << iz << "\t";
  fout << Q2 << "\t" << xB << "\t" << z << "\t";
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
  out_mr << "mr_" << iQ2x << "_" << iz;
  mrname = out_mr.str();
  out_pt << "pt_" << iQ2x << "_" << iz;
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