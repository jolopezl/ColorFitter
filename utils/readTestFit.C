/*

This code must read an plot the following data

iFit Info: Energy Loss: 0 - He subtraction: 1 with correlation = 0
0.32;1.720562806;6.741055814;399.99669;2.5;0;0.2;0.1567536019;0.3972345928;373.6917548;0;0;0;7.129473154;0.01175804512;0.02102023015;0.02407321489;0.9900808808;0.8073921046;0.7153639251
0.53;2.580618792;3.315041826;21.63675098;2.5;0;0.2;1.057150535;1.863832552;22.10093859;0;0;0;4.497416343;0.01490600588;0.02147250905;0.02320580099;0.9213898149;0.7455289381;0.6751609548
0.75;1.122233882;2.854880881;24.12790424;2.5;0;0.2;1.248993816;2.018574014;27.08867989;0;0;0;0.47462916;0.005956435673;0.008321156291;0.008937356377;0.8806441542;0.6853759309;0.6142748512
0.94;0.8642244295;2.68428061;44.37349874;2.5;0;0.2;1.769519503;2.082950861;64.35162835;0;0;0;0.2796043624;0.004411207415;0.006096704539;0.006534339237;0.7962262806;0.561155262;0.4894261845

*/

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

double factor = 0.1 * 3. / (4. * 3.141592); // to recover q0

void readTestFit(std::string filename)
{
  SetAtlasStyle();

  std::string foutname = filename;
  if (foutname.size() > 0) {
    foutname.resize(foutname.size() - 4);
  }
  foutname = foutname + ".root";
  TFile* fout = TFile::Open(foutname.c_str(), "RECREATE");

  double zbin[4];
  double zbinw[4] = { 0.20 / 2, 0.22 / 2, 0.22 / 2, 0.16 / 2 }; // Approx.
  double q0[4], q0_err[4];
  double lp[4], lp_err[4];
  double cs[4], cs_err[4];
  double dlog[4], dlog_err[4];
  double dz[4], dz_err[4];
  double casc[4], casc_err[4];
  double chisq[4];
  std::cout << "Processing " << filename << std::endl;
  std::ifstream file(filename);
  std::string foo, line;
  std::vector<std::string> words = {};
  int i = 0;
  std::getline(file, line); // skip first line
  while (std::getline(file, line)) {
    boost::split(words, line, boost::is_any_of(";"), boost::token_compress_on);
    std::cout << "Size of words is " << words.size() << std::endl;

    zbin[i] = std::stod(words.at(0));
    q0[i] = std::stod(words.at(1));
    q0_err[i] = std::stod(words.at(1 + 6));
    q0[i] = q0[i] / factor;
    q0_err[i] = q0_err[i] / factor;
    lp[i] = std::stod(words.at(2));
    lp_err[i] = std::stod(words.at(2 + 6));
    cs[i] = std::stod(words.at(3));
    cs_err[i] = std::stod(words.at(3 + 6));
    dlog[i] = std::stod(words.at(4));
    dlog_err[i] = std::stod(words.at(4 + 6));
    dz[i] = std::stod(words.at(5));
    dz_err[i] = std::stod(words.at(5 + 6));
    casc[i] = std::stod(words.at(6));
    casc_err[i] = std::stod(words.at(6 + 6));
    chisq[i] = std::stod(words.at(13));

    std::cout << "********************************" << std::endl;
    std::cout << "zbin = " << zbin[i] << std::endl;
    std::cout << "q0 = " << q0[i] << " +/- " << q0_err[i] << std::endl;
    std::cout << "lp = " << lp[i] << " +/- " << lp_err[i] << std::endl;
    std::cout << "cs = " << cs[i] << " +/- " << cs_err[i] << std::endl;
    std::cout << "dlog = " << dlog[i] << " +/- " << dlog_err[i] << std::endl;
    std::cout << "dz = " << dz[i] << " +/- " << dz_err[i] << std::endl;
    std::cout << "casc = " << casc[i] << " +/- " << casc_err[i] << std::endl;
    std::cout << "chisq = " << chisq[i] << std::endl;
    ++i;
  }

  TGraphErrors* gr[7];
  gr[0] = new TGraphErrors(4, zbin, q0, zbinw, q0_err);
  gr[1] = new TGraphErrors(4, zbin, lp, zbinw, lp_err);
  gr[2] = new TGraphErrors(4, zbin, cs, zbinw, cs_err);
  gr[3] = new TGraphErrors(4, zbin, dlog, zbinw, dlog_err);
  gr[4] = new TGraphErrors(4, zbin, dz, zbinw, dz_err);
  gr[5] = new TGraphErrors(4, zbin, casc, zbinw, casc_err);

  double zero_errors[4] = { 0, 0, 0, 0 };
  int DOF = -99;
  if (filename == "testFitBL.csv")
    DOF = 6 - 3;
  if (filename == "testFitBL.fixedLp.csv")
    DOF = 6 - 3;
  if (filename == "testFitBL30.csv")
    DOF = 6 - 2;
  if (filename == "testFitBL30.fixedLp.csv")
    DOF = 6 - 2;
  if (filename == "testFitBL40.csv")
    DOF = 6 - 2;
  if (filename == "testFitBL40.fixedLp.csv")
    DOF = 6 - 2;
  if (filename == "testFitBLE.csv")
    DOF = 6 - 3;
  if (filename == "testFitBLE.fixedLp.csv")
    DOF = 6 - 3;
  if (filename == "testFitBLE30.csv")
    DOF = 6 - 4;
  if (filename == "testFitBLE30.fixedLp.csv")
    DOF = 6 - 4;
  if (filename == "testFitBLE40.csv")
    DOF = 6 - 4;
  if (filename == "testFitBLE40.fixedLp.csv")
    DOF = 6 - 4;
  for (int i = 0; i < 4; ++i) {
    chisq[i] = chisq[i] / DOF;
  }
  gr[6] = new TGraphErrors(4, zbin, chisq, zero_errors, zero_errors);

  gr[0]->SetName("tg_q0");
  gr[0]->SetTitle("tg_q0;z_{h};q_{0} [GeV^{2}fm^{2}]");
  gr[1]->SetName("tg_lp");
  gr[1]->SetTitle("tg_lp;z_{h};L_{p} [fm]");
  gr[2]->SetName("tg_cs");
  gr[2]->SetTitle("tg_cs;z_{h};#sigma [mbarn]");
  gr[3]->SetName("tg_dlog");
  gr[3]->SetTitle("tg_dlog;z_{h};dlog behav");
  gr[4]->SetName("tg_dz");
  gr[4]->SetTitle("tg_dz;z_{h};#Deltaz");
  gr[5]->SetName("tg_casc");
  gr[5]->SetTitle("tg_casc;z_{h};Hadron Cascade Parameter");
  gr[6]->SetName("tg_chisq");
  gr[6]->SetTitle("tg_chisq;z_{h};#chi^{2}/ndf");

  for (int i = 0; i < 7; ++i) {
    gr[i]->Write();
  }
  fout->Close();
}

void readTestFitAll()
{
  readTestFit("testFitBL.csv");
  readTestFit("testFitBL.fixedLp.csv");
  readTestFit("testFitBL30.csv");
  readTestFit("testFitBL30.fixedLp.csv");
  readTestFit("testFitBL40.csv");
  readTestFit("testFitBL40.fixedLp.csv");
  readTestFit("testFitBLE.csv");
  readTestFit("testFitBLE.fixedLp.csv");
  readTestFit("testFitBLE30.csv");
  readTestFit("testFitBLE30.fixedLp.csv");
  readTestFit("testFitBLE40.csv");
  readTestFit("testFitBLE40.fixedLp.csv");
}