#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "TMath.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TMath.h"
#include "TString.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TBenchmark.h"
#include "TF1.h"
#include "LHAPDF/LHAPDF.h"

using namespace std;
using namespace LHAPDF;

/*LHAPDF: SETTING PDF*/
LHAPDF::PDF *pdf;

/*PHYSICAL CONSTANTS*/

const double Pi        = 3.14159265358979323846;
const double lamQCD    = 0.047089;                // lambda_QCD**2 in GeV**2
const double hbarc     = 0.197326963;             // GeV.fm
const double alpha_qed = 1./137;
const double m_p       = 0.938272;
const double e_fund    = 0.303*sqrt(hbarc);       // sqrt(GeV*fm)

int nf; 
char PDFTOUSE[30];
char target[10];
double E = 0.;                                 //Energy of the incoming electron in GeV

/*---------------------PARTON DISTRIBUTION FUNCTION---------------------------------*/

double f_q_h(double xx, double Q2, int flavour)
{
  double result = pdf->xfxQ2(flavour,xx,Q2);
  //cout<<"f_q: "<<result<<endl;
  return result/xx;
}

/*-------------------------FRAGMENTATION FUNCTION---------------------------------*/

double D_q(double z, double flavour)
{
  /*Kretzer: FF for q -> Pi+*/
  //if(flavour==2 || flavour==-1){return 0.65184*pow(z,-0.829)*pow(1-z,0.949);}
  //else{return 0.652174*pow(z,-0.829)*pow(1-z,1.949);}


  /*From Stratmann, De Florian y Sassot: FF for q -> Pi+*/
  if(flavour==2)
    {return (1.118735*pow(1 - z,1.2) + 5.918107*pow(1 - z,5.71) + (-0.96688*pow(1 - z,2.19) - 7.541676*pow(1 - z,8.99))*pow(z,0.351))/pow(z,0.228);}

  else if(flavour==-2||flavour==1)
    {return 0.966881*(1 + 7.8*pow(1 - z,6.8))*pow(1 - z,2.19)*pow(z,0.123);}

  else if(flavour==-1)
    {return (1.132923*pow(1-z,1.2) + 5.993165*pow(1-z,5.71) + (-0.966881*pow(1-z,2.19) - 7.541676*pow(1-z,8.99))*pow(z,0.411))/pow(z,0.288);}

  else if(flavour==3||flavour==-3)
    {return 0.813998*(1 + 7.8*pow(1 - z,6.8))*pow(1 - z,2.19)*pow(z,0.123);}
}

/*THEORETICAL CROSS SECTION*/
double d3sigma_Q2NuZh(double Zh, double *par)
{
  // Q2 -> par[0]
  // Nu -> par[1]
  // Zh -> x[0]

  double result = 0.;
  double eq2    = 0;
  double y      = par[1]/E;
  double Xb     = par[0]/(2.*m_p*par[1]);

  for(int flavour=-nf ; flavour<=nf ; flavour++)
    {
      if(flavour == 2 || flavour == -2){eq2 = 4./9;}
      else if(flavour == 1 || flavour == -1 || flavour == 3 || flavour == -3){eq2 = 1./9;}

      if(flavour!=0)
	{
	  //From "Unpolarised transverse momentum dependent distribution and fragmentation functions from SIDIS multiplicities", Anselmino et al. Eq (2.1) Integrated in Pt2
	  //Changed the variable Xb for Nu
	  result += (Xb/par[1])*2*Pi*pow(alpha_qed/par[0],2)*(1+pow(1-y,2))*eq2*f_q_h(Xb,par[0],flavour)*D_q(Zh,flavour);
	}
    }
 
  return result*pow(hbarc,2); //hbarc^2 provides the normalization factor so the result is [fm^2/GeV^3]  
}

void plot(double Q2, double Nu)
{

  TFile ftarget("d3sigma.root","RECREATE");

  int array_size = 2;
  int nbin = 100;

  double par[array_size];
  par[0] = Q2;
  par[1] = Nu;

  double zh = 0.1; 
  double dzh = (1.-0.1)/nbin;

  /*--------------------------------------*/
  double zhval[nbin],dddsigma[nbin];
  for(int i = 0; i<nbin; i++)
    {
      zhval[i]=zh + i*dzh;
      dddsigma[i]=d3sigma_Q2NuZh(zhval[i],par);
    }

  TGraph *gr1 = new TGraph(nbin,zhval,dddsigma);
  ftarget.cd();
  gr1->Write();
}


int main(int argc,char *argv[])
{
  double Q2, Nu;


  /*Setting the energy*/
  cout<<"Choose the energy of the beam: "<<endl;
  cin>>E;
  cout<<"Choose the PDF set to use like CT14nlo, CT14lo, CJ15nlo ..."<<endl;
  scanf("%s",PDFTOUSE);
  cout<<"Choose the quarks that'll be taking into account: "<<endl;
  cin>>nf;
  cout<<"Choose Q2"<<endl;
  cin>>Q2;
  cout<<"Choose Nu"<<endl;
  cin>>Nu;

  /*SETTING THE PDF*/
  // pdf = LHAPDF::mkPDF(PDFTOUSE);
  pdf = LHAPDF::mkPDF(11000); // CT10nlo

  plot(Q2,Nu);

  return 0;
}
