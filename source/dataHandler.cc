#include "dataHandler.h"

#include <ctime>

#define DIM 4 // This should be defined somewhere else

myResult::myResult()
{
  m_name = "default result";
  std::cout << "myResult:: Result created for " << m_name << std::endl;
}

myResult::~myResult()
{
  std::cout << "myResult:: Result destructed for " << m_name << std::endl;
}

myData::myData(std::string name)
{
  m_name = name;
  m_value.clear();
  m_stat.clear();
  m_syst.clear();
  m_err.clear();
  m_value_corrected.clear();
  m_stat_corrected.clear();
  m_syst_corrected.clear();
  m_err_corrected.clear();
  for (int i = 0; i <= DIM; ++i) { // Initialize vectors
    m_value.push_back(0.0);
    m_stat.push_back(0.0);
    m_syst.push_back(0.0);
    m_err.push_back(0.0);
    m_value_corrected.push_back(0.0);
    m_stat_corrected.push_back(0.0);
    m_syst_corrected.push_back(0.0);
    m_err_corrected.push_back(0.0);
  }
  std::cout << "myData:: Data created for " << m_name << std::endl;
}

myData::~myData()
{
  std::cout << "myData:: Data destructed for " << m_name << std::endl;
}

void myData::fill(int i, double val, double stat, double syst)
{
  m_value[i] = val;
  m_stat[i] = stat;
  m_syst[i] = syst;
  m_err[i] = stat + syst;
}

/*
    This is the most important part, mixes the errors
    Note that for Z=X-Y, then
    s2 = s_1^2+s_2^2 - 2*rho*s_1*s_2
*/

void myData::applyCorrection(myData* nucl, double rho)
{ // nucl is the bkg
  for (int i = 0; i <= DIM; ++i) {
    m_value_corrected[i] = m_value[i] - nucl->m_value[i];
    // testing January 3, 2018
    // if (m_value_corrected[i] < 0) {
    //     m_value_corrected[i] = 0;
    // }
    m_stat_corrected[i] = sqrt(pow2(m_stat[i]) + pow2(nucl->m_stat[i]));
    m_syst_corrected[i] = sqrt(pow2(m_syst[i]) + pow2(nucl->m_syst[i]) + 2 * rho * m_syst[i] * nucl->m_syst[i]);
    m_err_corrected[i] = sqrt(pow2(m_stat_corrected[i]) + pow2(m_syst_corrected[i]));
    // Testing uncertainties in z > 0.5
    // if (i==2|| i==3) {
    //     m_err_corrected[i] *= 0.5;
    // }
  }
}

std::string myData::name()
{
  return m_name;
}

void myData::doTGraphErrors()
{
  const int markerStyleCode = 20; // circle 20, box 21
  const int markerColorCode = 1;  // black 1, red 2, blue 4
  const int markerSizeCode = 1;
  const int makerLineWidthCode = 2;
  const int markerColorCodeStat = 2; // red
  const int markerColorCodeSyst = 4; // blue
  const float markerAlphaCode = 1.0;
  const int fillColorCode = 4;
  const int fillStyleCode = 3144;
  m_tge.clear();
  m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value[0], &m_wbin[0], &m_stat[0]));
  m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value[0], &m_wbin[0], &m_syst[0]));
  m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value[0], &m_wbin[0], &m_err[0]));
  m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value_corrected[0], &m_wbin[0], &m_stat_corrected[0]));
  m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value_corrected[0], &m_wbin[0], &m_syst_corrected[0]));
  m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value_corrected[0], &m_wbin[0], &m_err_corrected[0]));
  m_tge[0]->SetName("gg1");
  m_tge[0]->SetTitle("Statistical Errors");
  m_tge[0]->SetFillColorAlpha(markerColorCodeStat, markerAlphaCode);
  m_tge[1]->SetName("gg2");
  m_tge[1]->SetTitle("Systematic Errors");
  m_tge[1]->SetFillColorAlpha(markerColorCodeSyst, 0.1 * markerAlphaCode);
  m_tge[1]->SetFillColor(fillColorCode);
  m_tge[1]->SetFillStyle(fillStyleCode);
  m_tge[2]->SetName("gg3");
  m_tge[2]->SetTitle("Total Uncertainties");
  m_tge[2]->SetMarkerColor(markerColorCode);
  m_tge[2]->SetLineWidth(makerLineWidthCode);
  m_tge[2]->SetMarkerSize(markerSizeCode);
  m_tge[2]->SetMarkerStyle(markerStyleCode);
  m_tge[3]->SetName("gg1_corrected");
  m_tge[3]->SetTitle("Statistical Errors");
  m_tge[3]->SetFillColorAlpha(markerColorCodeStat, markerAlphaCode);
  m_tge[4]->SetName("gg2_corrected");
  m_tge[4]->SetTitle("Systematic Errors");
  m_tge[4]->SetFillColorAlpha(markerColorCodeSyst, 0.1 * markerAlphaCode);
  m_tge[4]->SetFillColor(fillColorCode);
  m_tge[4]->SetFillStyle(fillStyleCode);
  m_tge[5]->SetName("gg3_corrected");
  m_tge[5]->SetTitle("Total Uncertainties");
  m_tge[5]->SetMarkerColor(markerColorCode);
  m_tge[5]->SetLineWidth(makerLineWidthCode);
  m_tge[5]->SetMarkerSize(markerSizeCode);
  m_tge[5]->SetMarkerStyle(markerStyleCode);
}

std::vector<myData*> dataHandler(myConfig* config)
{
  double correlation = config->m_correlation;

  /* 
    This is a function and not a method of myData becuase it reads 
    from an input file that is not well designed now, so all three nuclei are read at once.
    Of course, this should only old for HERMES analysis. For Jlab analysis all data
    should be read from TGraphErrors of pT and RM vs A^1/3 for each kinematic bin
    */

  myData* he = new myData("Helium");
  myData* ne = new myData("Neon");
  myData* kr = new myData("Kripton");
  myData* xe = new myData("Xenon");
  std::ifstream input;
  input.open(config->m_input_pt);
  if (!input.is_open()) {
    std::cout << "Check your input data file is here" << std::endl;
    std::vector<myData*> output = {};
    return output;
  }
  std::string foo, line;
  std::vector<std::string> words = {};
  double val, stat, syst;
  // Read data and fill objects
  std::getline(input, foo);
  std::getline(input, foo);
  for (int i = 0; i < DIM; ++i) {
    std::getline(input, line); // read line of data
    boost::split(words, line, boost::is_any_of(" "), boost::token_compress_on);
    conv2double(words, val, stat, syst);
    he->fill(i, val, stat, syst);
  }
  std::getline(input, foo); // dummy line to ignore
  for (int i = 0; i < DIM; ++i) {
    std::getline(input, line); // read line of data
    boost::split(words, line, boost::is_any_of(" "), boost::token_compress_on);
    conv2double(words, val, stat, syst);
    ne->fill(i, val, stat, syst);
  }
  std::getline(input, foo); // dummy line to ignore
  for (int i = 0; i < DIM; ++i) {
    std::getline(input, line); // read line of data
    boost::split(words, line, boost::is_any_of(" "), boost::token_compress_on);
    conv2double(words, val, stat, syst);
    kr->fill(i, val, stat, syst);
  }
  std::getline(input, foo); // dummy line to ignore
  for (int i = 0; i < DIM; ++i) {
    std::getline(input, line); // read line of data
    boost::split(words, line, boost::is_any_of(" "), boost::token_compress_on);
    conv2double(words, val, stat, syst);
    xe->fill(i, val, stat, syst);
  }
  input.close();
  // Apply Helium substraction
  he->applyCorrection(he, correlation);
  ne->applyCorrection(he, correlation);
  kr->applyCorrection(he, correlation);
  xe->applyCorrection(he, correlation);
  // Create TGraphErros contained in each object
  he->doTGraphErrors();
  ne->doTGraphErrors();
  kr->doTGraphErrors();
  xe->doTGraphErrors();
  // Do plots of data
  if (config->correctionPlots) {
    doDataPlots(config, he, ne, kr, xe);
  }
  // Prepare output and finish
  std::vector<myData*> output;
  // output.push_back(he); // we don't need to return He.
  output.push_back(ne);
  output.push_back(kr);
  output.push_back(xe);
  // output.push_back(he);
  // **** Print values to file **** //
  if (config->writeCorrectedValues) {
    std::ofstream filevalues;
    filevalues.open("data_correct_pT2.txt", std::ios::out);
    if (filevalues.is_open()) {
      filevalues.precision(10);
      for (const auto& nucl : output) {
        filevalues << nucl->name() << "\n";
        for (int i = 0; i < 4; ++i) {
          filevalues << nucl->m_zbin[i] << "\t" << nucl->m_value_corrected[i] << "\t" << nucl->m_err_corrected[i] << "\n";
        }
      }
      filevalues.close();
    } else {
      std::cerr << "ERROR from dataHandler, A problem ocurred when opening a file" << std::endl;
    }
  }
  std::cout << "dataHandler finished" << std::endl;
  return output;
}

bool OutputResultsToFile(const std::string model, std::vector<myResult> resultCont)
{
  /*
    This function is created to simplify the main function regarding the output handling.
    It still needs some tweakign for instance reading from somewhere else the number of z-bins.
    */
  const int fNzbins = 4; // 10 for JLab and 4 for HERMES !
  double z[fNzbins];
  double z_err[fNzbins];
  double q0[fNzbins];
  double lp1[fNzbins], lp2[fNzbins], lp3[fNzbins];
  double sig1[fNzbins], sig2[fNzbins], sig3[fNzbins];
  double dz[fNzbins];
  double kt2[fNzbins];
  double q0_err[fNzbins];
  double lp1_err[fNzbins], lp2_err[fNzbins], lp3_err[fNzbins];
  double sig1_err[fNzbins], sig2_err[fNzbins], sig3_err[fNzbins];
  double dz_err[fNzbins];
  double kt2_err[fNzbins];

  double chisquared[fNzbins];
  if (resultCont.size() != fNzbins) {
    std::cout << "I cannot produce a ROOT output file, please check the produced CSV file" << std::endl;
    return false;
  }
  std::cout << "I will produce a ROOT out file..." << std::endl;
  for (int i = 0; i < fNzbins; ++i) {
    std::cout << "Fetching result container for element " << i << std::endl;
    std::cout << "z = " << z[i] << std::endl;
    z[i] = resultCont.at(i).m_zbin;
    z_err[i] = 0;
    q0[i] = resultCont.at(i).m_q0;
    q0_err[i] = resultCont.at(i).m_q0_err;
    lp1[i] = resultCont.at(i).m_lp1;
    lp2[i] = resultCont.at(i).m_lp2;
    lp3[i] = resultCont.at(i).m_lp3;
    lp1_err[i] = resultCont.at(i).m_lp1_err;
    lp2_err[i] = resultCont.at(i).m_lp2_err;
    lp3_err[i] = resultCont.at(i).m_lp3_err;
    sig1[i] = resultCont.at(i).m_sig1;
    sig2[i] = resultCont.at(i).m_sig2;
    sig3[i] = resultCont.at(i).m_sig3;
    sig1_err[i] = resultCont.at(i).m_sig1_err;
    sig2_err[i] = resultCont.at(i).m_sig2_err;
    sig3_err[i] = resultCont.at(i).m_sig3_err;
    dz[i] = resultCont.at(i).m_dz;
    dz_err[i] = resultCont.at(i).m_dz_err;
    kt2[i] = resultCont.at(i).m_dkt2;
    kt2_err[i] = resultCont.at(i).m_dkt2_err;
    chisquared[i] = resultCont.at(i).m_chi2;
  }

  time_t t = time(NULL);
  auto my_time = localtime(&t);
  std::string dd = "";
  dd += std::to_string(my_time->tm_year + 1900);
  if ((my_time->tm_mon + 1) < 10) {
    dd += "0" + std::to_string(my_time->tm_mon + 1);
  } else {
    dd += std::to_string(my_time->tm_mon + 1);
  }
  if (my_time->tm_mday < 10) {
    dd += "0" + std::to_string(my_time->tm_mday);
  } else {
    dd += std::to_string(my_time->tm_mday);
  }

  std::string ffout = "OutputROOT." + dd + "." + model + ".root";
  TFile* OutputROOT = new TFile(ffout.c_str(), "RECREATE");
  std::cout << "Output file created" << std::endl;
  OutputROOT->cd();
  std::cout << "Making plots of everything" << std::endl;
  TGraphErrors* tg_q0 = new TGraphErrors(fNzbins, z, q0, z_err, q0_err);
  tg_q0->SetName("tg_q0");
  tg_q0->SetTitle(";#it{z};#it{q}_{0} (GeV^{2}fm^{2})");
  TGraphErrors* tg_lp1 = new TGraphErrors(fNzbins, z, lp1, z_err, lp1_err);
  TGraphErrors* tg_lp2 = new TGraphErrors(fNzbins, z, lp2, z_err, lp2_err);
  TGraphErrors* tg_lp3 = new TGraphErrors(fNzbins, z, lp3, z_err, lp3_err);
  tg_lp1->SetName("tg_lp1");
  tg_lp2->SetName("tg_lp2");
  tg_lp3->SetName("tg_lp3");
  tg_lp1->SetTitle(";#it{z};#pi^{+} #it{L}_{p} (fm)");
  tg_lp2->SetTitle(";#it{z};#pi^{-} #it{L}_{p} (fm)");
  tg_lp3->SetTitle(";#it{z};K^{+} #it{L}_{p} (fm)");
  TGraphErrors* tg_sig1 = new TGraphErrors(fNzbins, z, sig1, z_err, sig1_err);
  TGraphErrors* tg_sig2 = new TGraphErrors(fNzbins, z, sig2, z_err, sig2_err);
  TGraphErrors* tg_sig3 = new TGraphErrors(fNzbins, z, sig3, z_err, sig3_err);
  tg_sig1->SetName("tg_sig1");
  tg_sig2->SetName("tg_sig2");
  tg_sig3->SetName("tg_sig3");
  tg_sig1->SetTitle(";#it{z};#pi^{+} #it{#sigma} (mbarn)");
  tg_sig2->SetTitle(";#it{z};#pi^{-} #it{#sigma} (mbarn)");
  tg_sig3->SetTitle(";#it{z};K^{+} #it{#sigma} (mbarn)");
  TGraphErrors* tg_dz = new TGraphErrors(fNzbins, z, dz, z_err, dz_err);
  tg_dz->SetName("tg_dz");
  tg_dz->SetTitle(";#it{z};#delta#it{z} (GeV)");
  TGraphErrors* tg_deltakT = new TGraphErrors(fNzbins, z, kt2, z_err, kt2_err);
  tg_deltakT->SetName("tg_deltakT2");
  tg_deltakT->SetTitle(";#it{z};#Delta#it{k}_{#perp} (Gev^{2})");
  TGraph* tg_chisquared = new TGraph(fNzbins, z, chisquared);
  tg_chisquared->SetName("tg_chisquared");
  tg_chisquared->SetTitle(";#it{z};#chi^{2}");
  std::cout << "Writing first set of plots" << std::endl;
  tg_q0->Write();
  tg_lp1->Write();
  tg_lp2->Write();
  tg_lp3->Write();
  tg_sig1->Write();
  tg_sig2->Write();
  tg_sig3->Write();
  tg_dz->Write();
  tg_deltakT->Write();
  tg_chisquared->Write();
  std::cout << "Creating model plots" << std::endl;
  TGraphErrors* tg_data_pT[fNzbins][3];
  TGraphErrors* tg_data_Rm[fNzbins][3];
  TGraphErrors* tg_model_pT[fNzbins][3];
  TGraphErrors* tg_model_Rm[fNzbins][3];
  TGraphErrors* tg_model_pT_extrapolation[fNzbins][3];
  TGraphErrors* tg_model_pT_extrapolation_up[fNzbins][3];
  TGraphErrors* tg_model_pT_extrapolation_down[fNzbins][3];
  TGraphErrors* tg_model_Rm_extrapolation[fNzbins][3];
  TGraphErrors* tg_model_Rm_extrapolation_up[fNzbins][3];
  TGraphErrors* tg_model_Rm_extrapolation_down[fNzbins][3];
  TGraph* tg_average_density[fNzbins][3];
  TGraph* tg_multiplicity_density[fNzbins][3];
  TGraph* tg_average_length[fNzbins][3];
  TGraph* tg_average_parton_length[fNzbins][3];

  std::string title;
  std::array<std::string, 3> particle_names = { "pip", "pim", "Kp" };
  for (int j = 0; j < 3; ++j) {
    for (int i = 0; i < fNzbins; ++i) {
      std::cout << "Creating model plots for element " << i << std::endl;
      title = ";A^{1/3};#Delta#LTp_{T}^{2}#GT";
      tg_data_pT[i][j] = &(resultCont.at(i).m_tg_data_pT[j]);
      tg_data_pT[i][j]->SetName(Form("tg_data_pT_%d_%s", i, particle_names[j].c_str()));
      tg_data_pT[i][j]->SetTitle(title.c_str());
      tg_model_pT[i][j] = &(resultCont.at(i).m_tg_pT[j]);
      tg_model_pT[i][j]->SetName(Form("tg_model_pT_%d_%s", i, particle_names[j].c_str()));
      tg_model_pT[i][j]->SetTitle(title.c_str());
      tg_model_pT_extrapolation[i][j] = &(resultCont.at(i).m_tg_pT_extrapolation[j]);
      tg_model_pT_extrapolation[i][j]->SetName(Form("tg_model_pT_extrapolation_%d_%s", i, particle_names[j].c_str()));
      tg_model_pT_extrapolation[i][j]->SetTitle(title.c_str());
      tg_model_pT_extrapolation_up[i][j] = &(resultCont.at(i).m_tg_pT_extrapolation_up[j]);
      tg_model_pT_extrapolation_up[i][j]->SetName(Form("tg_model_pT_extrapolation_up_%d_%s", i, particle_names[j].c_str()));
      tg_model_pT_extrapolation_up[i][j]->SetTitle(title.c_str());
      tg_model_pT_extrapolation_down[i][j] = &(resultCont.at(i).m_tg_pT_extrapolation_down[j]);
      tg_model_pT_extrapolation_down[i][j]->SetName(Form("tg_model_pT_extrapolation_down_%d_%s", i, particle_names[j].c_str()));
      tg_model_pT_extrapolation_down[i][j]->SetTitle(title.c_str());
      title = ";A^{1/3};R_{M}";
      tg_data_Rm[i][j] = &(resultCont.at(i).m_tg_data_Rm[j]);
      tg_data_Rm[i][j]->SetName(Form("tg_data_Rm_%d_%s", i, particle_names[j].c_str()));
      tg_data_Rm[i][j]->SetTitle(title.c_str());
      tg_model_Rm[i][j] = &(resultCont.at(i).m_tg_Rm[j]);
      tg_model_Rm[i][j]->SetName(Form("tg_model_Rm_%d_%s", i, particle_names[j].c_str()));
      tg_model_Rm[i][j]->SetTitle(title.c_str());
      tg_model_Rm_extrapolation[i][j] = &(resultCont.at(i).m_tg_Rm_extrapolation[j]);
      tg_model_Rm_extrapolation[i][j]->SetName(Form("tg_model_Rm_extrapolation_%d_%s", i, particle_names[j].c_str()));
      tg_model_Rm_extrapolation[i][j]->SetTitle(title.c_str());
      tg_model_Rm_extrapolation_up[i][j] = &(resultCont.at(i).m_tg_Rm_extrapolation_up[j]);
      tg_model_Rm_extrapolation_up[i][j]->SetName(Form("tg_model_Rm_extrapolation_up_%d_%s", i, particle_names[j].c_str()));
      tg_model_Rm_extrapolation_up[i][j]->SetTitle(title.c_str());
      tg_model_Rm_extrapolation_down[i][j] = &(resultCont.at(i).m_tg_Rm_extrapolation_down[j]);
      tg_model_Rm_extrapolation_down[i][j]->SetName(Form("tg_model_Rm_extrapolation_down_%d_%s", i, particle_names[j].c_str()));
      tg_model_Rm_extrapolation_down[i][j]->SetTitle(title.c_str());
      title = ";A^{1/3};#LT #rho #GT";
      tg_average_density[i][j] = &(resultCont.at(i).m_tg_average_density[j]);
      tg_average_density[i][j]->SetName(Form("tg_average_density_%d_%s", i, particle_names[j].c_str()));
      tg_average_density[i][j]->SetTitle(title.c_str());
      title = ";A^{1/3};#LT #sigma exp(-#sigma#int#rhodz) #rho(z_{0}+l) #GT";
      tg_multiplicity_density[i][j] = &(resultCont.at(i).m_tg_multiplicity_density[j]);
      tg_multiplicity_density[i][j]->SetName(Form("tg_multiplicity_density_%d_%s", i, particle_names[j].c_str()));
      tg_multiplicity_density[i][j]->SetTitle(title.c_str());
      title = ";A^{1/3};#LT l #GT (fm)";
      tg_average_length[i][j] = &(resultCont.at(i).m_tg_average_length[j]);
      tg_average_length[i][j]->SetName(Form("tg_average_length_%d_%s", i, particle_names[j].c_str()));
      tg_average_length[i][j]->SetTitle(title.c_str());
      title = ";A^{1/3};#LT l_parton #GT (fm)";
      tg_average_parton_length[i][j] = &(resultCont.at(i).m_tg_average_parton_length[j]);
      tg_average_parton_length[i][j]->SetName(Form("tg_average_parton_length_%d_%s", i, particle_names[j].c_str()));
      tg_average_parton_length[i][j]->SetTitle(title.c_str());
      tg_data_pT[i][j]->Write();
      tg_data_Rm[i][j]->Write();
      tg_model_pT[i][j]->Write();
      tg_model_Rm[i][j]->Write();
      tg_model_pT_extrapolation[i][j]->Write();
      tg_model_pT_extrapolation_up[i][j]->Write();
      tg_model_pT_extrapolation_down[i][j]->Write();
      tg_model_Rm_extrapolation[i][j]->Write();
      tg_model_Rm_extrapolation_up[i][j]->Write();
      tg_model_Rm_extrapolation_down[i][j]->Write();
      tg_average_density[i][j]->Write();
      tg_multiplicity_density[i][j]->Write();
      tg_average_length[i][j]->Write();
      tg_average_parton_length[i][j]->Write();
    }
  }
  std::cout << "Done." << std::endl;
  OutputROOT->Close();
  std::cout << "Results saved to a ROOT file file: " << ffout << std::endl;
  return true;
}
