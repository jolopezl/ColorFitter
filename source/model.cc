#include "model.h"

Model::Model(): 
  m_ModelName("Default"),
  m_dPt2(0.0), 
  m_Rm(0.0),
  m_DoEnergyLoss(false),
  m_DoLogBehavior(false),
  m_DoFermiMotion(false) {
  std::cout << "Model created: " << m_ModelName << std::endl;
}

Model::Model(std::string name): 
  m_ModelName(name), 
  m_dPt2(0.0), 
  m_Rm(0.0), 
  m_DoEnergyLoss(false), 
  m_DoLogBehavior(false), 
  m_DoFermiMotion(false) {
  std::cout << "Model created: " << m_ModelName << std::endl;
}

Model::~Model() {
  std::cout << "Model destructed: " << m_ModelName << std::endl;
}

std::vector<double> Model::GetResult() {
  std::vector<double> output = {m_dPt2, m_Rm};
  return output;
}

double Model::Get1(){
  return m_dPt2;
}

double Model::Get2(){
  return m_Rm; 
}

double Model::GetC(int A) {
  return m_c_interpolation[A];
}

void Model::SetParameters(std::vector<double> parms) {
  m_qhat     = parms.at(0);
  m_lp       = parms.at(1);
  m_sigma_ph = parms.at(2);
  m_dlog     = parms.at(3);
  m_dz       = parms.at(4);
}

void Model::SetParameters(std::string parameter, double value) {
  if      (parameter == "qhat")              m_qhat = value;
  else if (parameter == "lp")                m_lp = value;
  else if (parameter == "sigma_ph")          m_sigma_ph = value;
  else if (parameter == "dlog")              m_dlog = value;
  else if (parameter == "dz")                m_dz = value;
  else if (parameter == "density threshold") m_density_threshold = value;
  else std::cout << "Not a valid parameter name" << std::endl;
}

void Model::SetBinRatio(int diz, double dbinw, double dbinratio){
  m_iz = diz;
  m_zbinwidth = dbinw;
  m_binratio = dbinratio;
}

void Model::SetFermiValues(double xb, double z) {
  m_xB = xb;
  m_zbinvalue = z;
}

void Model::DoEnergyLoss(bool foo) {
  m_DoEnergyLoss = foo;
}

void Model::DoLogBehavior(bool foo) {
  m_DoLogBehavior = foo;
}

void Model::DoFermiMotion(bool foo) {
  m_DoFermiMotion = foo;
}

void Model::Initialization() {
  // This will do the interpolation in the future
  m_c_interpolation = {0, 0, 0, 0, 1.321, 1.46802, 1.61163, 1.74843, 1.875, 1.98877, 2.09042, 2.18148, 2.26346, 2.33789, 2.40628, \
    2.47014, 2.531, 2.59013, 2.64781, 2.70407, 2.75897, 2.81252, 2.86478, 2.91577, 2.96554, 3.01412, 3.06154, 3.10785, 3.15309, 3.19728, \
    3.24048, 3.2827, 3.324, 3.3644, 3.40394, 3.44263, 3.48049, 3.51755, 3.55382, 3.58934, 3.62412, 3.65819, 3.69156, 3.72426, 3.75632, \
    3.78774, 3.81856, 3.8488, 3.87848, 3.90762, 3.93624, 3.96436, 3.99202, 4.01922, 4.04599, 4.07236, 4.09834, 4.12396, 4.14924, 4.1742, \
    4.19887, 4.22326, 4.24739, 4.2713, 4.295, 4.31851, 4.34183, 4.36497, 4.38793, 4.41071, 4.43331, 4.45574, 4.47799, 4.50007, 4.52198, \
    4.54371, 4.56528, 4.58669, 4.60793, 4.629, 4.64992, 4.67068, 4.69128, 4.71172, 4.73201, 4.75214, 4.77213, 4.79197, 4.81166, 4.8312, \
    4.8506, 4.86986, 4.88897, 4.90795, 4.92679, 4.94549, 4.96406, 4.9825, 5.00081, 5.01899, 5.03704, 5.05497, 5.07277, 5.09045, 5.10801, \
    5.12546, 5.14278, 5.15999, 5.17709, 5.19407, 5.21095, 5.22771, 5.24437, 5.26093, 5.27738, 5.29373, 5.30998, 5.32613, 5.34218, 5.35814, \
    5.37401, 5.38978, 5.40547, 5.42106, 5.43657, 5.452, 5.46734, 5.4826, 5.49778, 5.51288, 5.5279, 5.54283, 5.55769, 5.57247, 5.58717, \
    5.6018, 5.61634, 5.63082, 5.64521, 5.65953, 5.67378, 5.68796, 5.70206, 5.71609, 5.73005, 5.74393, 5.75775, 5.7715, 5.78518, 5.79879, \
    5.81233, 5.82581, 5.83922, 5.85256, 5.86584, 5.87905, 5.89221, 5.90529, 5.91832, 5.93128, 5.94419, 5.95703, 5.96981, 5.98253, 5.9952, \
    6.00781, 6.02035, 6.03285, 6.04528, 6.05767, 6.06999, 6.08226, 6.09448, 6.10665, 6.11876, 6.13083, 6.14284, 6.1548, 6.16671, 6.17858, \
    6.19039, 6.20216, 6.21388, 6.22555, 6.23718, 6.24877, 6.2603, 6.2718, 6.28325, 6.29466, 6.30603, 6.31736, 6.32864, 6.33989, 6.35109, \
    6.36226, 6.37339, 6.38449, 6.39554, 6.40656, 6.41755, 6.4285, 6.43941, 6.4503, 6.46114, 6.47196, 6.48275, 6.4935, 6.50423, 6.51492, \
    6.52559, 6.53623, 6.54684, 6.55742, 6.56798, 6.57851, 6.58901, 6.5995, 6.60995, 6.62039, 6.6308, 6.64119, 6.65156, 6.66191, 6.67224, \
    6.68254, 6.69284, 6.70311, 6.71336, 6.7236, 6.73382, 6.74403, 6.75422, 6.7644, 6.77456, 6.78471, 6.79485, 6.80498, 6.8151, 6.8252, \
    6.8353, 6.84539, 6.85547, 6.86554, 6.8756, 6.88566, 6.89571, 6.90576, 6.9158, 6.92584, 6.93588, 6.94591, 6.95594, 6.96597, 6.976};
}

double Model::FindR(double A, const double density_threshold){
  double r = 0.0;
  double eps = 1.0e-3;
  while (Density(A,0.,0.,r)>=density_threshold) {
    // std::cout << "Computing for A = " << A
    //           << "\t rho(r) = " << Density(A,0.,0.,r) 
    //           << "\t threshold = " << density_threshold << std::endl;
    r = r+eps;
    if (r > 10) {
      eps = eps*10;
      std::cerr << "Error:never found R - Still trying - r = " << r
                << "\t density = " << Density(A,0.,0.,r)
                << "\t threshold = " << density_threshold
                << "\t computing for A = " << A
                << std::endl;
    }
  }
  return r;
}

double Model::Density(const double A, const double xx, const double yy, const double zz){
  // Ref. Henk Blok article, Phys Rev. C73, 038201 (2006)
  double rho0 = m_rho0;
  double a = m_a;
  double c = m_c_interpolation[(int) A]; // Change to m_c?
  double r = sqrt(xx*xx+yy*yy+zz*zz);
  double rho = rho0/(1.0+exp((r-c)/a));
  return rho;
}


double Model::Fermi(int inucleus){
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

void Model::Compute(const double A){
  // Computation of both quantities dPt2 and Rm
  // We are doing an MC average
  TF1 *dtd1 = new TF1("dtd1", "[0]*0.170/(1+exp((sqrt([1]*[1]+[2]*[2]+x*x)-[3])/0.5))", 0.,40.); // pT broadening divided by constant.
  // TF1 *dtd1 = new TF1("dtd1", "0.170/(1+exp((sqrt([0]*[0]+[1]*[1]+x*x)-[2])/0.5))", 0.,40.); // pT broadening divided by constant.
  TF1 *dtd2 = new TF1("dtd2", "0.170/(1+exp((sqrt([0]*[0]+[1]*[1]+x*x)-[2])/0.5))", 0.,40.); // multiplicity ratio
  ROOT::Math::GSLIntegrator *igdtd1 = new ROOT::Math::GSLIntegrator(ROOT::Math::IntegrationOneDim::kADAPTIVE);
  ROOT::Math::GSLIntegrator *igdtd2 = new ROOT::Math::GSLIntegrator(ROOT::Math::IntegrationOneDim::kADAPTIVE);
  TRandom3 *gRandom = new TRandom3(); // this forces all gRandom uses to be TRandom3 instead of TRandom, the default.
  gRandom->SetSeed(2053);
  double R=FindR(A,m_density_threshold); // this has to be done somewhere else since it takes time
  // std::cout << "Model-Info: R = " << R << " [fm] \t A = " << A << std::endl;
  double max_density=Density(A,0.,0.,0.);
  double x,y,z;
  double L;
  double weight, ul;
  double temp, accumulator1=0.0, accumulator2=0.0, zrange1, zrange2;
  double constant = 0.1*3./(4.*3.141592); // alpha_s * N_c / 4pi, the prefix of the formula for delta pT^2 = 0.02387
  double normalize = 0.0;
  for (int mcStep=0; mcStep<m_maxmcSteps; ++mcStep){
    while(1){// only consider points inside the integration sphere
      x = gRandom->Uniform(-R,R);
      y = gRandom->Uniform(-R,R);
      z = gRandom->Uniform(-R,R);
      if(x*x+y*y+z*z<R*R) break;
    }
    L = gRandom->Exp(m_lp); // exponentially distributed production length
    dtd1->SetParameter(0,m_qhat); // qhat parameter  
    dtd1->SetParameter(1,x); // starting value of longitudinal coordinate  
    dtd1->SetParameter(2,y); // x
    dtd1->SetParameter(3,m_c_interpolation[(int)A]); // density parameter
    // dtd1->SetParameter(0,x); // starting value of longitudinal coordinate  
    // dtd1->SetParameter(1,y); // x
    // dtd1->SetParameter(2,m_c_interpolation[(int)A]); // density parameter
    dtd2->SetParameter(0,x); // x
    dtd2->SetParameter(1,y); // y
    dtd2->SetParameter(2,m_c_interpolation[(int)A]); // density parameter
    ROOT::Math::WrappedTF1 wdtd1(*dtd1);
    ROOT::Math::WrappedTF1 wdtd2(*dtd2);
    igdtd1->SetFunction(wdtd1);
    igdtd1->SetRelTolerance(0.00001);
    igdtd2->SetFunction(wdtd2);
    igdtd2->SetRelTolerance(0.00001);
    weight=Density(A,x,y,z)/max_density; // this is the weight (probability) of the occurrence of the event 
    ul = sqrt(R*R-x*x-y*y); // We should never integrate beyond this value, which is the surface of the sphere of integration
    // Next, integrate from the starting vertex up to the end of the production length
    if(z+L<ul){// endpoint of quark path is within the sphere of integration
      temp=constant*igdtd1->Integral(z,z+L) ; // find partonic lengths
      zrange1=L;
      if(m_DoLogBehavior == true) {
        zrange1*= log(pow(L/m_dlog,2))*log(pow(L/m_dlog,2)); // log squared term
      }
    }
    if(z+L>=ul){ // endpoint of quark path is outside the sphere of integration
      temp=constant*igdtd1->Integral(z,ul) ; // find partonic lengths
      zrange1=ul-z;
      if(m_DoLogBehavior == true) {
        zrange1*= log(pow(L/m_dlog,2))*log(pow(L/m_dlog,2)); // log squared term
      }
    }
    if(z>ul){// this should not be possible
      std::cout << "Point A: ul = " << ul << " temp, R, x, y, z,  R*R-x*x-y*y " << temp << " " << R << " " << x << " " << y << " " << z << " " << R*R-x*x-y*y << std::endl;
    }
    if(temp<0){ // this integral should always be positive.
      std::cout << "igdtd1 is negative!! Error!! \n";
      temp=0.;
      zrange1=1.; // dummy value
    }
    if(temp==0){ 
      zrange1=1.; // dummy value
    }
    if(zrange1>0){
      // accumulator1+=zrange1*temp*weight;
      accumulator1+=temp*weight;
      // accumulator1+=m_qhat*zrange1*temp*weight; 
    }
    else{
      std::cout << "zrange1 of length zero or negative encountered: " << zrange1 << " \n";
      std::cout << "Point B: ul = " << ul << " temp, R, x, y, z,  R*R-x*x-y*y " << temp <<" "<< R <<" "<< x <<" "<< y <<" "<< z << " " << R*R-x*x-y*y << std::endl;
    }
    // Next, integrate from the prehadron vertex up to the end of the sphere of integration
    if (z+L<ul){
      temp=igdtd2->Integral(z+L,ul) ; // find hadronic lengths
      zrange2=ul-(z+L);
    }
    if (z+L>=ul){ // pre-hadron forms outside nucleus
      temp=0.;
      zrange2=1.; // dummy value
    }
    if(temp<0){ // this integral should always be positive.
      std::cout << "igdtd2 is negative!! Error!! \n";
    }
    if(zrange2>0){
      accumulator2+= exp(-temp*m_sigma_ph/10.)*weight;
    }
    if(zrange2==0){
      std::cout<<"Info: zrange2 = 0 encountered; weight, R, z, L= " << weight << " " << R << " " << z << " " << L << " " << "\n";
    }
    if(zrange2<0){
      std::cout<<"Error: negative zrange2 encountered; weight, R, z, L= " << weight << " " << R << " " << z << " " << L << " " << "\n";  
    }
    //      normalize+= 1.;
    normalize+=weight; // weight initial interaction by density  
  } // End of big loop     energy loss down here ------------*
  // ADD ENERGY LOSS, From Will's original code:
  temp = accumulator2/normalize;
  if (m_DoEnergyLoss == true) {
    if (m_iz > 0) {
      temp*=(1.-(1.-m_binratio)*m_dz/m_zbinwidth); // add effect of energy loss; par[4] is the average z shift due to energy loss
    }
    else {
      temp*=(1.+(m_binratio*m_dz)/m_zbinwidth); // events increase in the lowest z bin.
    }
  }
  m_dPt2=accumulator1/normalize; //  pT broadening
  m_Rm=temp; //  Multiplicity
}