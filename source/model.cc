#include "model.h"

Model::Model() : m_ModelName("Default"),
                 m_dPt2(0.0),
                 m_Rm(0.0),
                 m_q0(1.5),
                 m_lp(3.5),
                 m_sigma_ph(40.0), // prehadron cross section
                 m_dlog(0.0),      // log description?
                 m_dz(0.0),        // energy loss parameter
                 m_cascade(0.0),
                 m_coeff_1(0),
                 m_coeff_2(0),
                 m_DoEnergyLoss(false),
                 m_DoLogBehavior(false),
                 m_DoFermiMotion(false),
                 m_doCascade(false),
                 m_doFixedLp(false)
{
  std::cout << "Model created: " << m_ModelName << std::endl;
}

Model::Model(std::string name) : m_ModelName(name),
                                 m_dPt2(0.0),
                                 m_Rm(0.0),
                                 m_q0(1.5),
                                 m_lp(3.5),
                                 m_sigma_ph(40.0), // prehadron cross section
                                 m_dlog(0.0),      // log description?
                                 m_dz(0.0),        // energy loss parameter
                                 m_cascade(0.0),
                                 m_coeff_1(0),
                                 m_coeff_2(0),
                                 m_DoEnergyLoss(false),
                                 m_DoLogBehavior(false),
                                 m_DoFermiMotion(false),
                                 m_doCascade(false),
                                 m_doFixedLp(false)
{
  std::cout << "Model created: " << m_ModelName << std::endl;
}

Model::~Model()
{
  std::cout << "Model destructed: " << m_ModelName << std::endl;
}

std::vector<double> Model::GetResult()
{
  std::vector<double> output = { m_dPt2, m_Rm };
  return output;
}

void Model::GetResult(double& dPT2, double& Rm)
{
  dPT2 = m_dPt2;
  Rm = m_Rm;
}

void Model::DoEnergyLoss(bool foo, int N)
{
  m_DoEnergyLoss = foo;
  kBINS = N;
}
void Model::DoEnergyLoss(bool foo)
{
  m_DoEnergyLoss = foo;
  kBINS = 4; // think something smarter
}
void Model::DoEnergyLossWeighted(bool foo) { m_DoEnergyLossWeighted = foo; }
void Model::DoLogBehavior(bool foo) { m_DoLogBehavior = foo; }
void Model::DoFermiMotion(bool foo) { m_DoFermiMotion = foo; }
void Model::DoFixedLp(bool foo) { m_doFixedLp = foo; }
void Model::DoCascade(bool foo) { m_doCascade = foo; }
void Model::DoMonitoring(bool foo) { m_doMonitoring = foo; }
void Model::SetMaxMonteCarloSteps(int value) { m_maxmcSteps = value; }

void Model::SetParameters(std::vector<double> parms)
{
  m_q0 = parms.at(0);
  m_lp = parms.at(1);
  m_sigma_ph = parms.at(2);
  m_dlog = parms.at(3);
  m_dz = parms.at(4);
  m_cascade = parms.at(5);
}

void Model::SetParameters(std::string parameter, double value)
{
  if (parameter == "q0")
    m_q0 = value;
  else if (parameter == "lp")
    m_lp = value;
  else if (parameter == "sigma")
    m_sigma_ph = value;
  else if (parameter == "dlog")
    m_dlog = value;
  else if (parameter == "dz")
    m_dz = value;
  else if (parameter == "cascade")
    m_cascade = value;
  else if (parameter == "density threshold")
    m_density_threshold = value;
  else
    std::cout << "Not a valid parameter name" << std::endl;
}

void Model::SetTestParameter(double c1, double c2)
{
  m_coeff_1 = c1;
  m_coeff_2 = c2;
}

void Model::SetBinRatio(int diz, double dbinw, double dbinratio)
{
  m_iz = diz;
  m_zbinwidth = dbinw;
  m_binratio = dbinratio;
}

void Model::SetFermiValues(double xb, double z)
{
  m_xB = xb;
  m_zbinvalue = z;
}

void Model::Initialization()
{
  m_c_interpolation = { 0, 0, 0, 0, 1.321, 1.46802, 1.61163, 1.74843, 1.875, 1.98877, 2.09042, 2.18148, 2.26346, 2.33789, 2.40628,
                        2.47014, 2.531, 2.59013, 2.64781, 2.70407, 2.75897, 2.81252, 2.86478, 2.91577, 2.96554, 3.01412, 3.06154, 3.10785, 3.15309, 3.19728,
                        3.24048, 3.2827, 3.324, 3.3644, 3.40394, 3.44263, 3.48049, 3.51755, 3.55382, 3.58934, 3.62412, 3.65819, 3.69156, 3.72426, 3.75632,
                        3.78774, 3.81856, 3.8488, 3.87848, 3.90762, 3.93624, 3.96436, 3.99202, 4.01922, 4.04599, 4.07236, 4.09834, 4.12396, 4.14924, 4.1742,
                        4.19887, 4.22326, 4.24739, 4.2713, 4.295, 4.31851, 4.34183, 4.36497, 4.38793, 4.41071, 4.43331, 4.45574, 4.47799, 4.50007, 4.52198,
                        4.54371, 4.56528, 4.58669, 4.60793, 4.629, 4.64992, 4.67068, 4.69128, 4.71172, 4.73201, 4.75214, 4.77213, 4.79197, 4.81166, 4.8312,
                        4.8506, 4.86986, 4.88897, 4.90795, 4.92679, 4.94549, 4.96406, 4.9825, 5.00081, 5.01899, 5.03704, 5.05497, 5.07277, 5.09045, 5.10801,
                        5.12546, 5.14278, 5.15999, 5.17709, 5.19407, 5.21095, 5.22771, 5.24437, 5.26093, 5.27738, 5.29373, 5.30998, 5.32613, 5.34218, 5.35814,
                        5.37401, 5.38978, 5.40547, 5.42106, 5.43657, 5.452, 5.46734, 5.4826, 5.49778, 5.51288, 5.5279, 5.54283, 5.55769, 5.57247, 5.58717,
                        5.6018, 5.61634, 5.63082, 5.64521, 5.65953, 5.67378, 5.68796, 5.70206, 5.71609, 5.73005, 5.74393, 5.75775, 5.7715, 5.78518, 5.79879,
                        5.81233, 5.82581, 5.83922, 5.85256, 5.86584, 5.87905, 5.89221, 5.90529, 5.91832, 5.93128, 5.94419, 5.95703, 5.96981, 5.98253, 5.9952,
                        6.00781, 6.02035, 6.03285, 6.04528, 6.05767, 6.06999, 6.08226, 6.09448, 6.10665, 6.11876, 6.13083, 6.14284, 6.1548, 6.16671, 6.17858,
                        6.19039, 6.20216, 6.21388, 6.22555, 6.23718, 6.24877, 6.2603, 6.2718, 6.28325, 6.29466, 6.30603, 6.31736, 6.32864, 6.33989, 6.35109,
                        6.36226, 6.37339, 6.38449, 6.39554, 6.40656, 6.41755, 6.4285, 6.43941, 6.4503, 6.46114, 6.47196, 6.48275, 6.4935, 6.50423, 6.51492,
                        6.52559, 6.53623, 6.54684, 6.55742, 6.56798, 6.57851, 6.58901, 6.5995, 6.60995, 6.62039, 6.6308, 6.64119, 6.65156, 6.66191, 6.67224,
                        6.68254, 6.69284, 6.70311, 6.71336, 6.7236, 6.73382, 6.74403, 6.75422, 6.7644, 6.77456, 6.78471, 6.79485, 6.80498, 6.8151, 6.8252,
                        6.8353, 6.84539, 6.85547, 6.86554, 6.8756, 6.88566, 6.89571, 6.90576, 6.9158, 6.92584, 6.93588, 6.94591, 6.95594, 6.96597, 6.976 };
  m_random3 = new TRandom3(); // this forces all gRandom uses to be TRandom3 instead of TRandom, the default.
}

double Model::FindR(const double A, const double density_threshold)
{
  double r = 0.0;
  double eps = 1.0e-4;
  while (Density(A, 0., 0., r) >= density_threshold) {
    // std::cout << "Computing for A = " << A
    //           << "\t rho(r) = " << Density(A,0.,0.,r)
    //           << "\t threshold = " << density_threshold << std::endl;
    r = r + eps;
    if (r > 100) {
      eps = eps * 10;
      std::cerr << "Error:never found R - Still trying - r = " << r
                << "\t density = " << Density(A, 0., 0., r)
                << "\t threshold = " << density_threshold
                << "\t computing for A = " << A
                << std::endl;
    }
  }
  return r;
  /* using the mathematica notebook */
  // if (A == (int) 20.1797)  {return 4.52791;}
  // if (A == (int) 83.7980)  {return 6.48089;}
  // if (A == (int) 131.293)  {return 7.29538;}
}

double Model::GetR(const double A, const double density_threshold)
{
  const double R = FindR(A, density_threshold);
  return R;
}

double Model::GetC(double A)
{
  // return m_c_interpolation[A];
  /* using the mathematica notebook */
  // if (A == (int) 20.1797)  {return 2.77966;}
  // if (A == (int) 83.7980)  {return 4.73264;}
  // if (A == (int) 131.293)  {return 5.54713;}
  return 1.1 * pow(A, 1. / 3.);
}

double Model::Density(const double A, const double xx, const double yy, const double zz)
{
  // Ref. Henk Blok article, Phys Rev. C73, 038201 (2006)
  double rho0 = m_rho0; // 0.170
  double a = m_a;       // 0.5
  double c = GetC(A);
  double r = sqrt(xx * xx + yy * yy + zz * zz);
  double rho = rho0 / (1.0 + exp((r - c) / a));
  return rho;
}

double Model::Fermi(int inucleus)
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

void Model::InteractionPoint(double& x, double& y, double& z, const double R)
{
  while (1) {
    x = m_random3->Uniform(-R, R);
    y = m_random3->Uniform(-R, R);
    z = m_random3->Uniform(-R, R);
    m_xp = x;
    m_yp = y;
    m_zp = z;
    m_rr = R;

    /* spherical coordinates */
    m_rs = sqrt(m_xp * m_xp + m_yp * m_yp);
    m_phi = atan2(y, x);
    m_theta = acos(z / sqrt(m_xp * m_xp + m_yp * m_yp + m_zp * m_zp));

    if (x * x + y * y + z * z < R * R)
      break;
  }
}

void Model::SortProductionLength(double& L)
{
  // double mean = m_lp + m_coeff_1*m_A13 + m_coeff_2*m_A23; // testing idea
  double mean = m_lp;
  // double mean = m_lp; // original idea
  if (m_doFixedLp)
    L = mean;
  else
    L = m_random3->Exp(mean); // exponentially distributed production length
}

void Model::MonitoringStart()
{
  fout = TFile::Open("monitoring.root", "RECREATE");
  tree = new TTree("tree", "tree");
  tree->Branch("production_length", &m_production_length, "production_length/D");
  tree->Branch("parton_length", &m_parton_length, "parton_length/D");
  tree->Branch("hadron_length", &m_hadron_length, "hadron_length/D");
  tree->Branch("nucleus", &m_nucleus, "nucleus/I");
  tree->Branch("zbin", &m_zin_monitoring, "zbin/I");
  tree->Branch("xp", &m_xp, "xp/D");
  tree->Branch("yp", &m_yp, "yp/D");
  tree->Branch("zp", &m_zp, "zp/D");
  tree->Branch("rr", &m_rr, "rr/D");
  tree->Branch("theta", &m_theta, "theta/D");
  tree->Branch("phi", &m_phi, "phi/D");
  tree->Branch("rs", &m_rs, "rs/D");
  tree->Branch("eloss", &m_normalized_energy_loss, "eloss/D");
  tree->Branch("multiplicative_factor", &m_multiplicative_factor, "multiplicative_factor/D");
}

void Model::MonitoringFinish()
{
  tree->Print();
  fout->Write();
  fout->Close();
}

int Model::Compute(const double A)
{
  m_nucleus = (int)A;
  if (m_doMonitoring) {
    std::cout << "Nucleus has A = " << m_nucleus << std::endl;
  }
  // Computation of both quantities dPt2 and Rm
  // We are doing an MC average
  // TF1 *dtd1 = new TF1("dtd1", "[0]*0.170/(1+exp((sqrt([1]*[1]+[2]*[2]+x*x)-[3])/0.5))", 0.,40.); // pT broadening divided by constant.
  TF1* dtd1 = new TF1("dtd1", "0.170/(1+exp((sqrt([0]*[0]+[1]*[1]+x*x)-[2])/0.5))", 0., 40.); // pT broadening divided by constant.
  TF1* dtd2 = new TF1("dtd2", "0.170/(1+exp((sqrt([0]*[0]+[1]*[1]+x*x)-[2])/0.5))", 0., 40.); // multiplicity ratio
  ROOT::Math::GSLIntegrator* igdtd1 = new ROOT::Math::GSLIntegrator(ROOT::Math::IntegrationOneDim::kADAPTIVE);
  ROOT::Math::GSLIntegrator* igdtd2 = new ROOT::Math::GSLIntegrator(ROOT::Math::IntegrationOneDim::kADAPTIVE);
  // m_random3 = new TRandom3(); // this forces all gRandom uses to be TRandom3 instead of TRandom, the default.
  m_random3->SetSeed(2053);
  double R = FindR(A, m_density_threshold); // this has to be done somewhere else since it takes time
  if (irun == -1) {
    std::cout << "Model-Info: R(out)  = " << R << " [fm] \t A = " << A << "\t 1.1*A^(1/3) = " << 1.1 * pow(A, 1 / 3.) << " [fm]" << std::endl;
    std::cout << "Model-Info: c = " << GetC(A) << std::endl;
    irun = 1;
  }
  m_A13 = pow(A, 1 / 3.);
  m_A23 = pow(A, 2 / 3.);
  double max_density = Density(A, 0., 0., 0.);
  double rc = GetC(A);
  double x, y, z;
  double L;
  double weight, ul;
  double temp = 0.0;
  double zrange1 = -1.0, zrange2 = -1.0;
  double accumulator1 = 0.0; // pT2
  double accumulator2 = 0.0; // Rm
  double normalize = 0.0;
  // * Constant to be removed
  double constant = 0.1 * 3. / (4. * 3.141592); // alpha_s * N_c / 4pi, the prefix of the formula for delta pT^2 = 0.02387
  // MC part
  double average_density = 0;
  double average_length = 0;
  double multiplicity_density = 0;
  for (int mcStep = 0; mcStep < m_maxmcSteps; ++mcStep) {
    InteractionPoint(x, y, z, R);
    SortProductionLength(L);
    // First function parameters
    dtd1->SetParameter(0, x);  // starting value of longitudinal coordinate
    dtd1->SetParameter(1, y);  // x
    dtd1->SetParameter(2, rc); // density parameter
    // Second function parameters
    dtd2->SetParameter(0, x);  // x
    dtd2->SetParameter(1, y);  // y
    dtd2->SetParameter(2, rc); // density parameter
    // Wrap functions
    ROOT::Math::WrappedTF1 wdtd1(*dtd1);
    ROOT::Math::WrappedTF1 wdtd2(*dtd2);
    igdtd1->SetFunction(wdtd1);
    igdtd1->SetRelTolerance(0.00001);
    igdtd2->SetFunction(wdtd2);
    igdtd2->SetRelTolerance(0.00001);
    // Physics
    weight = Density(A, x, y, z) / max_density; // this is the weight (probability) of the occurrence of the event
    ul = sqrt(R * R - x * x - y * y);           // We should never integrate beyond this value, which is the surface of the sphere of integration
    /* Monitoring varibles */
    m_production_length = L;
    if (z + L < ul) { // hadron formed inside.
      m_hadron_length = ul - (z + L);
      m_parton_length = L;
    } else {                    // hadron formed outsie
      m_hadron_length = 0;      // hadron path length is zero
      m_parton_length = ul - z; // parton path length goes up to the surface
    }
    /* rest of the code */
    bool isOutside = false;
    // Next, integrate from the starting vertex up to the end of the production length
    if (z + L < ul) {                               // endpoint of quark path is within the sphere of integration
      temp = constant * igdtd1->Integral(z, z + L); // find partonic lengths
      zrange1 = L;
      if (m_DoLogBehavior == true)
        ApplyLogBehavior(zrange1, L);
    }
    if (z + L >= ul) {                           // endpoint of quark path is outside the sphere of integration
      temp = constant * igdtd1->Integral(z, ul); // find partonic lengths
      zrange1 = ul - z;
      if (m_DoLogBehavior == true)
        ApplyLogBehavior(zrange1, L);
    }
    if (z > ul) { // this should not be possible
      std::cout << "Point A: ul = " << ul << " temp, R, x, y, z,  R*R-x*x-y*y " << temp << " " << R << " " << x << " " << y << " " << z << " " << R * R - x * x - y * y << std::endl;
    }
    if (temp < 0) { // this integral should always be positive.
      std::cout << "igdtd1 is negative!! Error!! \n";
      temp = 0.;
      zrange1 = 1.; // dummy value
      m_dPt2 = -99;
      m_Rm = -99;
      return 1;
    }
    if (temp == 0)
      zrange1 = 1.; // dummy value
    if (zrange1 > 0)
      accumulator1 += m_q0 * temp * weight;
    else {
      std::cout << "zrange1 of length zero or negative encountered: " << zrange1 << " \n";
      std::cout << "Point B: ul = " << ul << " temp, R, x, y, z,  R*R-x*x-y*y " << temp << " " << R << " " << x << " " << y << " " << z << " " << R * R - x * x - y * y << std::endl;
    }
    // Next, integrate from the prehadron vertex up to the end of the sphere of integration
    if (z + L < ul) {
      temp = igdtd2->Integral(z + L, ul); // find hadronic lengths
      zrange2 = ul - (z + L);
      isOutside = false;
    }
    if (z + L >= ul) { // pre-hadron forms outside nucleus
      temp = 0.;
      zrange2 = 1.; // dummy value
      isOutside = true;
    }
    if (temp < 0) { // this integral should always be positive.
      std::cout << "igdtd2 is negative!! Error!! \n";
      m_dPt2 = -99;
      m_Rm = -99;
      return 1;
    }

    double multiplicity_ratio = 0;
    if (zrange2 > 0 && (isOutside == false)) {
      if (m_doCascade == true) {
        multiplicity_ratio = (exp(-temp * m_sigma_ph / 10.) + 1 - exp(-temp * m_cascade / 10.)) * weight;
        // accumulator2 += (exp(-temp*m_sigma_ph/10.) + log(m_cascade))*weight;
      } else {
        multiplicity_ratio = exp(-temp * m_sigma_ph / 10.);
      }
    } else if (isOutside == true) {
      multiplicity_ratio = 1;
    }

    /// *** ENERGY LOSS *** //
    if (m_DoEnergyLoss == true) {
      double before = multiplicity_ratio; // before correction;
      // m_normalized_energy_loss = ApplyEnergyLoss(multiplicity_ratio);
      m_normalized_energy_loss = ApplyImprovedEnergyLoss(multiplicity_ratio, m_parton_length);
      double after = multiplicity_ratio; // after correction
      m_multiplicative_factor = after / before;
    }

    accumulator2 += multiplicity_ratio * weight;

    if (zrange2 == 0) {
      std::cout << "Info: zrange2 = 0 encountered; weight, R, z, L= " << weight << " " << R << " " << z << " " << L << " " << std::endl;
    }
    if (zrange2 < 0) {
      std::cout << "Error: negative zrange2 encountered; weight, R, z, L= " << weight << " " << R << " " << z << " " << L << " " << std::endl;
      m_dPt2 = -99;
      m_Rm = -99;
      return 1;
    }
    // normalize+= 1.;
    normalize += weight; // weight initial interaction by density
    if (m_doMonitoring) {
      tree->Fill();
    }
    if (not isOutside) {
      average_density += dtd1->Eval(z + L);
      multiplicity_density += (m_sigma_ph / 10.) * exp(-temp * m_sigma_ph / 10.) * dtd1->Eval(z + L);
      average_length += L;
    } else {
      multiplicity_density += (m_sigma_ph / 10.) * exp(-temp * m_sigma_ph / 10.) * dtd1->Eval(z + ul);
      average_density += dtd1->Eval(z + ul);
      average_length += ul - z;
    }
    // multiplicity_density += (m_sigma_ph/10.)*exp(-temp*m_sigma_ph/10.)*dtd1->Eval(z+ul);
    // average_density += dtd1->Eval(z+ul);
    // average_length += z+ul;
    // if (ul - (z+L) < 0.1) { // choos a a suuuper threshold
    //     multiplicity_density += 1;
    //     multiplicity_density += exp(-temp*m_sigma_ph/10.);
    // }
    // average_density *= weight;
    // multiplicity_density *= weight;
  } // End of big loop     energy loss down here ------------*
  average_density /= m_maxmcSteps;
  multiplicity_density /= m_maxmcSteps;
  average_length /= m_maxmcSteps;
  m_average_density = average_density / average_length;
  m_multip_density = multiplicity_density / average_length;
  m_average_length = average_length;
  // ADD ENERGY LOSS, From Will's original code:
  temp = accumulator2 / normalize;
  // if (m_DoEnergyLoss == true) {
  //     ApplyEnergyLoss(temp);
  //     // ApplyImprovedEnergyLoss(temp);
  // }
  m_dPt2 = accumulator1 / normalize; //  pT broadening
  m_Rm = temp;                       //  Multiplicity
  // if (m_doMonitoring) {
  //   MonitoringFinish();
  // }
  return 0;
}

double Model::ApplyEnergyLoss(double& temp)
{
  const int BIN = m_iz;
  const double b = m_zbinwidth;
  const double ratio = m_binratio;
  double shift = 0.0;
  shift = m_dz;
  //   shift = m_random3->Exp(m_dz);
  if (BIN == kBINS - 1) {
    temp *= 1 + shift / b; // last bin loses events
  } else {
    temp *= 1 + shift / b - shift / b * ratio; // middle bins gain and lose events
  }
  return shift;
}

double Model::ApplyImprovedEnergyLoss(double& temp, const double& L)
{
  const double NU[4] = { 14.37, 13.03, 12.33, 10.70 };
  const int BIN = m_iz;
  const double b = m_zbinwidth;
  const double ratio = m_binratio;
  // Now the z-shift is calculated using model
  // shift = delta E / nu
  // dividing by NU provides m_coeff_2 with units of GeV/fm
  // double a = m_random3->Exp(m_coeff_2);
  // double Lcrit = m_random3->Exp(m_coeff_1);
  double a = m_coeff_2;
  double Lcrit = m_coeff_1;

  double shift = 0.0;
  if (L < Lcrit) {
    shift = a * pow(L, 2);
  } else {
    shift = a * Lcrit * (2 * L - Lcrit);
  }
  
  if (BIN == kBINS - 1) {
    temp *= 1 + shift / b;
  } else {
    temp *= 1 + shift * (1 - ratio) / b; // middle bins gain and lose events
  }

  return shift * NU[BIN];
}

void Model::ApplyLogBehavior(double& zrange, double L)
{
  zrange *= log(pow(L / m_dlog, 2)) * log(pow(L / m_dlog, 2));
}

double Model::Average_density_interpolation(const double& x)
{
  double ans = 0.0857276 + 0.192709 * x - 0.00978284 * pow(x, 2);
  return ans;
}