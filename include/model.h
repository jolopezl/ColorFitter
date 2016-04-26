#ifndef MODEL_H
#define MODEL_H

#include "TH1.h"
#include "TRandom3.h"
#include "Math/Interpolator.h"
#include "Math/WrappedTF1.h"
#include "Math/GSLIntegrator.h"

using vector_d = std::vector<double>;

class Model {
public:
  // public members
  Model(std::string);
  Model();
  ~Model();
  void SetParameters(std::vector<double>);
  void SetParameters(std::string,double);
  void SetBinRatio(int,double,double);
  void SetFermiValues(double,double);
  void DoEnergyLoss(bool);
  void DoLogBehavior(bool);
  void DoFermiMotion(bool);
  void DoFixedLp(bool);
  void DoCascade(bool);
  void Initialization();
  int Compute(const double);
  void InteractionPoint(double &, double &, double &, const double);
  double GetR(const double, const double);
  double Get1();
  double Get2();
  double GetC(int);
  vector_d GetResult();
  void GetResult(double&,double&);
  double Fermi(int inucleus);
private:
  // private methods
  double Density(const double, const double, const double, const double);
  double FindR(const double, const double);
  // private members
  std::string m_ModelName;
  double m_dPt2;
  double m_Rm;
  // physical input parameters
  double m_q0;
  double m_lp; // production lenght
  double m_sigma_ph; // prehadron cross section
  double m_dlog; // log description?
  double m_dz; // energy loss parameter
  double m_cascade;
  // for the nuclear density
  double m_rho0 = 0.170; // nucleons/fm^3
  double m_a = 0.5; //fm should be 0.54 fm
  // double m_c = 0.0; // to be solved
  // some assistance for the energy loss part
  int m_iz;
  double m_zbinwidth;
  double m_binratio; // with SetParameters??
  bool m_DoEnergyLoss;
  bool m_DoLogBehavior;
  bool m_DoFermiMotion;
  bool m_doCascade;
  bool m_doFixedLp;
  // For Fermi momentum
  double m_xB;
  double m_zbinvalue;
  // tools
  vector_d m_c_interpolation;
  // Other parameters
  int m_maxmcSteps = 100000; // number of mc steps in the calculation
  double m_density_threshold = 0.005;
  int irun = -1;
};

#endif