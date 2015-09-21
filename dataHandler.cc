#include "dataHandler.h"

#define DIM 4

myData::myData(std::string name) {
  m_name = name;
  m_value.clear();
  m_stat.clear();
  m_syst.clear();
  m_err.clear();
  m_value_corrected.clear();
  m_stat_corrected.clear();
  m_syst_corrected.clear();
  m_err_corrected.clear();
  std::cout << "Data created for " << m_name << std::endl;
}
myData::~myData() {
 std::cout << "Data destructed for " << m_name << std::endl; 
}

void myData::fill(double val, double stat, double syst) {
  m_value.push_back(val);
  m_stat.push_back(stat);
  m_syst.push_back(syst);
  m_err.push_back(stat+syst);
}

void myData::applyCorrection(myData* nucl) { // nucl is the bkg
  m_value_corrected.reserve(m_value.size());
  m_stat_corrected.reserve(m_stat.size());
  m_syst_corrected.reserve(m_syst.size());
  m_err_corrected.reserve(m_err.size());
  for (int i=0; i<=DIM; ++i) {
    m_value_corrected[i] = m_value[i] - nucl->m_value[i];
    m_stat_corrected[i] = m_stat[i] + nucl->m_stat[i];
    m_syst_corrected[i] = m_syst[i] + nucl->m_syst[i];
    m_err_corrected[i] = m_stat_corrected[i]+m_syst_corrected[i];
  }
}

void myData::doTGraphErrors() {
  // m_tge[0] = new TGraphErrors(DIM, &m_zbin[0], &m_value[0], &m_wbin[0], &m_stat[0]);
  // m_tge[1] = new TGraphErrors(DIM, &m_zbin[0], &m_value[0], &m_wbin[0], &m_syst[0]);
  // m_tge[2] = new TGraphErrors(DIM, &m_zbin[0], &m_value[0], &m_wbin[0], &m_err[0]);
  // m_tge[3] = new TGraphErrors(DIM, &m_zbin[0], &m_value_corrected[0], &m_wbin[0], &m_stat_corrected[0]);
  // m_tge[4] = new TGraphErrors(DIM, &m_zbin[0], &m_value_corrected[0], &m_wbin[0], &m_syst_corrected[0]);
  // m_tge[5] = new TGraphErrors(DIM, &m_zbin[0], &m_value_corrected[0], &m_wbin[0], &m_err_corrected[0]);
  m_tge.clear();
  m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value[0], &m_wbin[0], &m_stat[0]));
  m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value[0], &m_wbin[0], &m_syst[0]));
  m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value[0], &m_wbin[0], &m_err[0]));
  m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value_corrected[0], &m_wbin[0], &m_stat_corrected[0]));
  m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value_corrected[0], &m_wbin[0], &m_syst_corrected[0]));
  m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value_corrected[0], &m_wbin[0], &m_err_corrected[0]));
  m_tge[0]->SetName("gg1");
  m_tge[0]->SetTitle("Statistical Errors");
  m_tge[0]->SetMarkerColor(2);
  m_tge[0]->SetMarkerSize(0.5);
  m_tge[0]->SetMarkerStyle(20);
  m_tge[0]->SetFillColorAlpha(2,0.35);
  m_tge[1]->SetName("gg2");
  m_tge[1]->SetTitle("Systematic Errors");
  m_tge[1]->SetMarkerColor(2);
  m_tge[1]->SetMarkerSize(0.5);
  m_tge[1]->SetMarkerStyle(20);
  m_tge[1]->SetFillColorAlpha(3,0.35); 
  m_tge[2]->SetName("gg3");
  m_tge[2]->SetTitle("Total Uncertainties");
  m_tge[2]->SetMarkerColor(5);
  m_tge[2]->SetLineWidth(2);
  m_tge[2]->SetMarkerSize(0.5);
  m_tge[2]->SetMarkerStyle(24);
  m_tge[3]->SetName("gg1_corrected");
  m_tge[3]->SetTitle("Statistical Errors");
  m_tge[3]->SetMarkerColor(2);
  m_tge[3]->SetMarkerSize(0.5);
  m_tge[3]->SetMarkerStyle(20);
  m_tge[3]->SetFillColorAlpha(2,0.35);
  m_tge[4]->SetName("gg2_corrected");
  m_tge[4]->SetTitle("Systematic Errors");
  m_tge[4]->SetMarkerColor(2);
  m_tge[4]->SetMarkerSize(0.5);
  m_tge[4]->SetMarkerStyle(20);
  m_tge[4]->SetFillColorAlpha(3,0.35); 
  m_tge[5]->SetName("gg3_corrected");
  m_tge[5]->SetTitle("Total Uncertainties");
  m_tge[5]->SetMarkerColor(5);
  m_tge[5]->SetLineWidth(2);
  m_tge[5]->SetMarkerSize(0.5);
  m_tge[5]->SetMarkerStyle(24);
}

void conv2double(std::vector<std::string> words, double &val, double &stat, double &syst) {
  val  = std::stod(words.at(2));
  stat = std::stod(words.at(3));
  syst = std::stod(words.at(4));
}

void dataHandler() {
  myData *he = new myData("Helium");
  myData *ne = new myData("Neon");
  myData *kr = new myData("Kripton");
  myData *xe = new myData("Xeon");
  std::ifstream input;
  input.open("hermesData.txt");
  std::string foo, line;
  std::vector<std::string> words = {};
  std::getline(input,foo);
  std::getline(input,foo);
  double val,stat,syst;
  for (int i=0; i<DIM;++i) {
    std::getline(input,line); // read line of data
    boost::split(words, line, boost::is_any_of(" "), boost::token_compress_on);
    conv2double(words,val,stat,syst);
    he->fill(val,stat,syst);
  }
  std::getline(input,foo);
  for (int i=0; i<DIM;++i) {
    std::getline(input,line); // read line of data
    boost::split(words, line, boost::is_any_of(" "), boost::token_compress_on);
    conv2double(words,val,stat,syst);
    ne->fill(val,stat,syst);
  }
  std::getline(input,foo);
  for (int i=0; i<DIM;++i) {
    std::getline(input,line); // read line of data
    boost::split(words, line, boost::is_any_of(" "), boost::token_compress_on);
    conv2double(words,val,stat,syst);
    kr->fill(val,stat,syst);
  }
  std::getline(input,foo);
  for (int i=0; i<DIM;++i) {
    std::getline(input,line); // read line of data
    boost::split(words, line, boost::is_any_of(" "), boost::token_compress_on);
    conv2double(words,val,stat,syst);
    xe->fill(val,stat,syst);
  }
  input.close();
  he->applyCorrection(he);
  ne->applyCorrection(he);
  kr->applyCorrection(he);
  xe->applyCorrection(he);
  he->doTGraphErrors();
  ne->doTGraphErrors();
  kr->doTGraphErrors();
  xe->doTGraphErrors();
  doDataPlots(he,ne,kr,xe);
  std::cout << "dataHandler finished" << std::endl;
}

void doDataPlots(myData* he, myData* ne, myData* kr, myData* xe) {
  std::cout << "Creating plots" << std::endl;
  TMultiGraph *mg[2][4];
  TMultiGraph *mg_corrected[2][4];
  for (int i=0;i<4;++i) {
    mg[0][i] = new TMultiGraph();
    mg[1][i] = new TMultiGraph();
    mg_corrected[0][i] = new TMultiGraph();
    mg_corrected[1][i] = new TMultiGraph();
  }
  std::cout << "Adding Multigraphs" << std::endl;
  mg[0][0]->Add(he->m_tge[0]); mg_corrected[0][0]->Add(he->m_tge[3]);
  mg[0][0]->Add(he->m_tge[1]); mg_corrected[0][0]->Add(he->m_tge[4]);
  mg[1][0]->Add(he->m_tge[2]); mg_corrected[1][0]->Add(he->m_tge[5]);
  mg[0][1]->Add(ne->m_tge[0]); mg_corrected[0][1]->Add(ne->m_tge[3]);
  mg[0][1]->Add(ne->m_tge[1]); mg_corrected[0][1]->Add(ne->m_tge[4]);
  mg[1][1]->Add(ne->m_tge[2]); mg_corrected[1][1]->Add(ne->m_tge[5]);
  mg[0][2]->Add(kr->m_tge[0]); mg_corrected[0][2]->Add(kr->m_tge[3]);
  mg[0][2]->Add(kr->m_tge[1]); mg_corrected[0][2]->Add(kr->m_tge[4]);
  mg[1][2]->Add(kr->m_tge[2]); mg_corrected[1][2]->Add(kr->m_tge[5]);
  mg[0][3]->Add(xe->m_tge[0]); mg_corrected[0][3]->Add(xe->m_tge[3]);
  mg[0][3]->Add(xe->m_tge[1]); mg_corrected[0][3]->Add(xe->m_tge[4]);
  mg[1][3]->Add(xe->m_tge[2]); mg_corrected[1][3]->Add(xe->m_tge[5]);

  TCanvas *c = new TCanvas("canvas","canvas title",800*2,600*4);
  c->Divide(2,4);
  std::cout << "Creating Canvas" << std::endl;
  for (int i=0; i<4; ++i) {
    c->cd(2*i+1);
    mg[0][i]->Draw("a2");
    mg[0][i]->GetXaxis()->SetTitle("z_h");
    mg[0][i]->GetYaxis()->SetTitle("#DeltaP_{T}");
    // mg[0][i]->GetYaxis()->SetRangeUser(-0.025,0.025);
    mg[1][i]->Draw("p");
    c->cd(2*i+2);
    mg_corrected[0][i]->Draw("a2");
    mg_corrected[0][i]->GetXaxis()->SetTitle("z_{h}");
    mg_corrected[0][i]->GetYaxis()->SetTitle("#DeltaP_{T}^{2}");
    // mg_corrected[0][i]->GetYaxis()->SetRangeUser(-0.025,0.025);
    mg_corrected[1][i]->Draw("p");
  }
  c->Print("test.pdf");
  std::cout << "Plots ok" << std::endl;
  for (int i=0;i<4;++i) {
    delete(mg[0][i]);
    delete(mg[1][i]);
    delete(mg_corrected[0][i]);
    delete(mg_corrected[1][i]);
  }
  delete(c);
  std::cout << "Plots objects deleted" << std::endl;
}