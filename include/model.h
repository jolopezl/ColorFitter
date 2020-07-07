#ifndef MODEL_H
#define MODEL_H

#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"
#include "TRandom3.h"
#include "Math/Interpolator.h"
#include "Math/WrappedTF1.h"
#include "Math/GSLIntegrator.h"

#include "dataFormat.h"

class Model
{
 public:
  // public members
  Model(std::string);
  Model();
  ~Model();
  void SetParameters(std::vector<double>);
  void SetParameters(std::string, double);
  void SetTestParameter(double, double);
  void SetBinRatio(int, double, double);
  void SetFermiValues(double, double);
  void SetMaxMonteCarloSteps(int);
  void DoEnergyLoss(bool, int);
  void DoEnergyLoss(bool);
  void DoEnergyLossWeighted(bool);
  void DoLogBehavior(bool);
  void DoFermiMotion(bool);
  void DoFixedLp(bool);
  void DoCascade(bool);
  void DoMonitoring(bool);
  void Initialization();
  int Compute(const double);
  void InteractionPoint(double&, double&, double&, const double);
  double GetR(const double, const double);
  double GetC(double);
  double Fermi(int inucleus);

  void setZ(double z) { m_zbinvalue = z; }

  double Get1() const { return m_dPt2; };
  double Get2() const { return m_Rm; };
  double Get3() const { return m_average_density; };
  double Get4() const { return m_multip_density; };
  double GetAverageLength() const { return m_average_length; }
  std::vector<double> GetResultVector();
  ModelOutput GetResultStruct();
  void GetResult(double&, double&);

  // Monitoring code
  bool m_doMonitoring = false;
  TFile* fout;
  TTree* tree;
  void MonitoringStart();
  void MonitoringFinish();
  double m_production_length;
  double m_parton_length;
  double m_hadron_length;
  int m_nucleus;
  double m_computed_R;
  int m_zin_monitoring;
  double m_xp, m_yp, m_zp, m_rr;
  double m_theta, m_phi, m_rs;
  double m_normalized_energy_loss;
  double m_multiplicative_factor;
  void defineZbin(int foo) { m_zin_monitoring = foo; }

 private:
  // private methods
  double Density(const double, const double, const double, const double);
  double FindR(const double, const double);
  void SortProductionLength(double&);
  double ApplyEnergyLoss(double&);
  double ApplyImprovedEnergyLoss(double&, const double&);
  //void InteractionPoint(double &, double &, double &, const double);
  void ApplyLogBehavior(double&, double);
  double Average_density_interpolation(const double&);
  // private members
  std::string m_ModelName;

  int kBINS;
  double m_dPt2;
  double m_Rm;
  double m_average_density;
  double m_multip_density;
  double m_average_length;
  double m_average_parton_length;
  // physical input parameters
  double m_q0;
  double m_lp;       // production lenght
  double m_sigma_ph; // prehadron cross section
  double m_dlog;     // log description?
  double m_dz;       // energy loss parameter
  double m_cascade;

  // two new parameters August 30, 2017
  // now used to implement improved energy loss model Feb 19, 2020
  double m_coeff_1; // critical length
  double m_coeff_2; // shape parameter

  // for the nuclear density
  double m_rho0 = 0.170; // nucleons/fm^3
  double m_a = 0.5;      //fm should be 0.54 fm
  // double m_c = 0.0; // to be solved
  TRandom3* m_random3;
  // some assistance for the energy loss part
  int m_iz;
  double m_zbinwidth;
  double m_binratio; // with SetParameters??
  double m_A13 = -1, m_A23 = -1;
  bool m_DoEnergyLoss;
  bool m_DoEnergyLossWeighted;
  bool m_DoLogBehavior;
  bool m_DoFermiMotion;
  bool m_doCascade;
  bool m_doFixedLp;
  // For Fermi momentum
  double m_xB;
  double m_zbinvalue;
  // tools
  std::vector<double> m_c_interpolation;
  // Other parameters
  // int m_maxmcSteps = 100000; // number of mc steps in the calculation
  int m_maxmcSteps = 50000; // number of mc steps in the calculation
  double m_density_threshold = 0.005;
  int irun = -1;

  TGraph g_c_interp;
};

#endif
