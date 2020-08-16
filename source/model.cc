#include "../include/model.h"

Model::Model() : m_ModelName("Default"),
                 m_dPt2(0.0),
                 m_Rm(0.0),
                 m_q0(1.5),
                 m_lp(3.5),
                 m_sigma_ph(40.0), // prehadron cross section
                 m_dlog(0.0),      // log description?
                 m_dz(0.0),        // energy loss parameter
                 m_cascade(0.0),
                 m_kt2(0.0),
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
                                 m_kt2(0.0),
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

ModelOutput Model::GetResultStruct()
{
  ModelOutput output;
  output.pt_broadening = m_dPt2;
  output.multiplicity_ratio = m_Rm;
  output.average_density = m_average_density;
  output.average_multiplicity_density = m_multip_density;
  output.average_production_length = m_average_length;
  output.average_parton_length = m_average_parton_length;
  return output;
}

std::vector<double> Model::GetResultVector()
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

void Model::SetTestParameter(double aa, double c1, double c2)
{
  m_kt2 = aa;
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
  m_c_interpolation = { 0, 0.41403570800376926, 0.8415285494389906, 1.1143344140766305, 1.3209538023584304, 1.489923624990808, 1.6342860261930716, 1.7611634352821233,
                        1.8749002836749948, 1.9783555883566586, 2.0735183130905295, 2.16183217939171, 2.2443808983509697, 2.3220003686496806, 2.395350008388296,
                        2.464959946343503, 2.5312632996991273, 2.5946188849507283, 2.655327591430356, 2.713644438607743, 2.7697876216581534,
                        2.8239454102311825, 2.876281487715273, 2.9269391383028083, 2.976044569737189, 3.0237095787191235, 3.0700337101009225, 3.115106021782662,
                        3.159006539257331, 3.201807463521847, 3.2435741812441865, 3.2843661150791648, 3.324237443776035, 3.3632377154692557, 3.401412372759739,
                        3.438803204500331, 3.4754487363232944, 3.511384569690755, 3.546643677464943, 3.5812566625747175, 3.6152519852168097, 3.6486561631125842,
                        3.681493948597048, 3.7137884857099257, 3.7455614499611407, 3.776833173033261, 3.807622754344103, 3.837948161110587, 3.8678263183194135,
                        3.897273189812414, 3.926303851528216, 3.954932557801319, 3.983172801500345, 4.011037368686, 4.03853838838248, 4.065687377981986,
                        4.092495284738293, 4.118972523750319, 4.14512901278924, 4.170974204281651, 4.196517114725404, 4.221766351783787, 4.246730139276529,
                        4.271416340262266, 4.295832478386443, 4.319985757650006, 4.343883080738554, 4.36753106603691, 4.390936063441769, 4.414104169073853,
                        4.437041238981015, 4.459752901915091, 4.4822445712572225, 4.504521456159591, 4.5265885719650445, 4.54845074996069, 4.570112646516284,
                        4.591578751653905, 4.612853397091243, 4.6339407637972245, 4.654844889095322, 4.675569673347038, 4.696118886245219, 4.716496172744494,
                        4.736705058653937, 4.756748955914962, 4.776631167585677, 4.796354892551319, 4.815923229978738, 4.83533918353167, 4.854605665362139,
                        4.873725499892323, 4.892701427399977, 4.911536107419744, 4.930232121971666, 4.948791978627371, 4.96721811342383, 4.9855128936337145,
                        5.003678620400801, 5.0217175312483935, 5.0396318024680555, 5.057423551395487, 5.075094838580018, 5.0926476698536245, 5.110083998305115,
                        5.127405726164627, 5.144614706603415, 5.161712745453475, 5.17870160285124, 5.1955829948094685, 5.212358594721038, 5.229030034798176,
                        5.245598907450512, 5.262066766605056, 5.278435128970995, 5.294705475252166, 5.310879251309767, 5.326957869277718, 5.342942708633085,
                        5.3588351172236734, 5.374636412254856, 5.390347881237621, 5.405970782899652, 5.421506348061137, 5.436955780477027, 5.452320257647214,
                        5.467600931596161, 5.482798929623307, 5.497915355025627, 5.5129512877935625, 5.52790778528148, 5.542785882853822, 5.557586594508012,
                        5.572310913475052, 5.586959812798863, 5.601534245895242, 5.616035147091247, 5.630463432145921, 5.644819998753094,
                        5.659105727026962, 5.673321479971237, 5.68746810393249, 5.7015464290383076, 5.715557269620924, 5.729501424626898,
                        5.743379678013336, 5.757192799131274, 5.770941543096657, 5.784626651149445, 5.798248851001242, 5.811808857171967,
                        5.82530737131594, 5.838745082537758, 5.852122667698412, 5.865440791711964, 5.878700107833135, 5.891901257936155, 5.905044872785204,
                        5.918131572296703, 5.931161965793811, 5.944136652253375, 5.957056220545592, 5.969921249666669, 5.982732308964726, 5.995489958359142,
                        6.0081947485536205, 6.0208472212431765, 6.033447909315222, 6.045997337045002, 6.058496020285556, 6.070944466652351, 6.083343175702834,
                        6.095692639111015, 6.107993340837295, 6.120245757293631, 6.132450357504261, 6.144607603262107, 6.156717949280958, 6.168781843343639,
                        6.180799726446238, 6.19277203293857, 6.204699190660904, 6.2165816210772, 6.2284197394048615, 6.240213954741155, 6.251964670186402,
                        6.263672282964017, 6.275337184537552, 6.286959760724717, 6.2985403918086265, 6.310079452646211, 6.321577312773991, 6.333034336511202,
                        6.344450883060435, 6.355827306605767, 6.367163956408564, 6.378461176900934, 6.389719307776956, 6.400938684081719, 6.412119636298261,
                        6.423262490432409, 6.434367568095676, 6.445435186586182, 6.4564656589677005, 6.467459294146872, 6.478416396948628, 6.489337268189914,
                        6.500222204751668, 6.511071499649226, 6.521885442101099, 6.532664317596208, 6.543408407959611, 6.55411799141679, 6.564793342656454,
                        6.575434732892007, 6.586042429921646, 6.596616698187141, 6.607157798831332, 6.6176659897544035, 6.628141525668897, 6.638584658153589,
                        6.648995635706194, 6.659374703794944, 6.66972210490908, 6.6800380786082965, 6.690322861571097, 6.700576687642195, 6.710799787878891,
                        6.7209923905965105, 6.731154721412888, 6.741287003291941, 6.751389456586377, 6.761462299079479, 6.771505746026095, 6.781520010192772,
                        6.791505301897097, 6.80146182904623, 6.81138979717471, 6.821289409481454, 6.831160866866072, 6.841004367964444, 6.8508201091836085,
                        6.860608284735964, 6.870369086672824, 6.880102704917282, 6.889809327296487, 6.899489139573279, 6.909142325477218, 6.918769066735028,
                        6.928369543100458, 6.937943932383601, 6.947492410479616, 6.957015151396957, 6.966512327285054, 6.975984108461481 };

  std::vector<double> x_range;
  for (int i = 0; i < m_c_interpolation.size(); ++i) {
    x_range.push_back(i);
  }
  g_c_interp = TGraph(m_c_interpolation.size(), &x_range[0], &m_c_interpolation[0]);

  m_random3 = new TRandom3(); // this forces all gRandom uses to be TRandom3 instead of TRandom, the default.

  std::cout << "Model parameters initialized" << std::endl;
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
}

double Model::GetR(const double A, const double density_threshold)
{
  const double R = FindR(A, density_threshold);
  return R;
}

double Model::GetC(double A)
{
  return g_c_interp.Eval(A);
  // return m_c_interpolation[A];
  /* using the mathematica notebook */
  //  if (A == (int) 4.0026)   {return 1.321;}
  //  if (A == (int) 20.1797)  {return 2.77966;}
  //  if (A == (int) 83.7980)  {return 4.73264;}
  //  if (A == (int) 131.293)  {return 5.54713;}
  //return 1.1 * pow(A, 1. / 3.);
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
  double mean = m_lp + m_coeff_1*m_A13 + m_coeff_2*m_A23; // testing idea
  // const double NU[4] = { 14.37, 13.03, 12.33, 10.70 };
  // const double ZH[4] = { 0.31, 0.54, 0.75, 0.94 };
  // const int BIN = m_iz;
  // double z = ZH[BIN];
  // double mean = 0.5 * (1 + 2 * NU[BIN]) * z * (TMath::Log(1 / (z * z)) - 1 + z * z) / (1 - z * z); // testing idea
  // double mean = m_lp;
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
  double average_parton_length = 0;
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
    average_parton_length += m_parton_length;
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
      accumulator1 += m_q0 * temp * weight + pow(m_zbinvalue, 2) * m_kt2;
    // accumulator1 += m_q0 * temp * weight + m_coeff_1;
    // accumulator1 += m_zbinvalue * m_zbinvalue * m_q0 * temp * weight;
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
      m_normalized_energy_loss = ApplyEnergyLoss(multiplicity_ratio);
      // m_normalized_energy_loss = ApplyImprovedEnergyLoss(multiplicity_ratio, m_parton_length);
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
  m_average_parton_length = average_parton_length / m_maxmcSteps;
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
  const double NU[4] = { 14.37, 13.03, 12.33, 10.70 };
  const double ZH[4] = { 0.31, 0.54, 0.75, 0.94 };
  const int BIN = m_iz;
  const double b = m_zbinwidth;
  const double ratio = m_binratio;
  double shift = ZH[BIN] * (NU[BIN] / (NU[BIN] - m_dz) - 1);
  // shift = ZH[BIN] * NU[BIN] / (NU[BIN] - m_dz);
  if (BIN == kBINS - 1) {
    temp *= 1 - shift; // last bin loses events
  } else {
    temp *= 1 - shift * (1 - ratio); // middle bins gain and lose events
  }
  return shift;
}

double Model::ApplyImprovedEnergyLoss(double& temp, const double& L)
{
  const double NU[4] = { 14.37, 13.03, 12.33, 10.70 };
  const double ZH[4] = { 0.31, 0.54, 0.75, 0.94 };
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

  double eloss = 0;
  if (L < Lcrit) {
    eloss = a * pow(L, 2);
  } else {
    eloss = a * Lcrit * (2 * L - Lcrit);
  }

  double shift = ZH[BIN] * (NU[BIN] / (NU[BIN] - eloss) - 1);

  if (BIN == kBINS - 1) {
    temp *= 1 - shift;
  } else {
    temp *= 1 - shift * (1 - ratio); // middle bins gain and lose events
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
