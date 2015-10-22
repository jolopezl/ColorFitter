#ifndef MODEL_H
#define MODEL_H

#include "TH1.h"
#include "TRandom3.h"
#include "Math/Interpolator.h"
#include "Math/WrappedTF1.h"
#include "Math/GSLIntegrator.h"

class Model {
private:
  // private members
  std::string m_ModelName;
  double m_dPt2;
  double m_Rm;
  // physical input parameters
  double m_qhat;
  double m_lp; // production lenght
  double m_sigma_ph; // prehadron cross section
  double m_dlog; // log description?
  double m_dz; // energy loss parameter
  // for the nuclear density
  double m_rho0 = 0.170; // nucleons/fm^3
  double m_a = 0.5; //fm should be 0.54 fm
  double m_c = 0.0; // to be solved
  // some assistance for the energy loss part
  int m_iz;
  double m_zbinwidth;
  double m_binratio; // with SetParameters??
  bool m_DoEnergyLoss;
  bool m_DoLogBehavior;
  bool m_DoFermiMotion;
  // For Fermi momentum
  double m_xB;
  double m_zbinvalue;
  // tools
  std::vector<double> m_c_interpolation;
  // Other parameters
  int m_maxmcSteps = 100000; // number of mc steps in the calculation
  double m_density_threshold = 0.005;
  // private methods
  double Density(double, double, double, double);
  double FindR(double, double);
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
  void Initialization();
  void Compute(double);
  double Get1();
  double Get2();
  double GetC(int);
  std::vector<double> GetResult();
  double Fermi(int inucleus);
};

#endif