#include "dataHandler.h"

#define DIM 4 // This should be defined somewhere else

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
  for (int i=0; i<=DIM; ++i) { // Initialize vectors
    m_value.push_back(0.0);
    m_stat.push_back(0.0);
    m_syst.push_back(0.0);
    m_err.push_back(0.0);
    m_value_corrected.push_back(0.0);
    m_stat_corrected.push_back(0.0);
    m_syst_corrected.push_back(0.0);
    m_err_corrected.push_back(0.0);
  }
  std::cout << "Data created for " << m_name << std::endl;
}
myData::~myData() {
 std::cout << "Data destructed for " << m_name << std::endl; 
}

void myData::fill(int i, double val, double stat, double syst) {
  m_value[i] = val;
  m_stat[i] = stat;
  m_syst[i] = syst;
  m_err[i] = stat+syst;
}

/*
  This is the most important part, mixes the errors
  Note that for Z=X-Y, then
  s2 = s_1^2+s_2^2 - 2*rho*s_1*s_2
*/

const double rho = 0.0; 

void myData::applyCorrection(myData* nucl) { // nucl is the bkg
  for (int i=0; i<=DIM; ++i) {
    m_value_corrected[i] = m_value[i] - nucl->m_value[i];
    m_stat_corrected[i] = sqrt(pow2(m_stat[i]) + pow2(nucl->m_stat[i]));
    m_syst_corrected[i] = sqrt(pow2(m_syst[i]) + pow2(nucl->m_syst[i]) + 2*rho*m_syst[i]*nucl->m_syst[i]);
    m_err_corrected[i] = sqrt(pow2(m_stat_corrected[i])+pow2(m_syst_corrected[i]));
  }
}

double pow2(double x) {return x*x;} // move this to somewhere else.

void myData::doTGraphErrors() {

  const int markerStyleCode = 20; // circle 20, box 21
  const int markerColorCode = 1; // black 1, red 2, blue 4
  const int markerSizeCode = 1;
  const int makerLineWidthCode = 2;

  m_tge.clear();
  m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value[0], &m_wbin[0], &m_stat[0]));
  m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value[0], &m_wbin[0], &m_syst[0]));
  m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value[0], &m_wbin[0], &m_err[0]));
  m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value_corrected[0], &m_wbin[0], &m_stat_corrected[0]));
  m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value_corrected[0], &m_wbin[0], &m_syst_corrected[0]));
  m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value_corrected[0], &m_wbin[0], &m_err_corrected[0]));
  m_tge[0]->SetName("gg1");
  m_tge[0]->SetTitle("Statistical Errors");
  m_tge[0]->SetFillColorAlpha(2,0.35);
  m_tge[1]->SetName("gg2");
  m_tge[1]->SetTitle("Systematic Errors");
  m_tge[1]->SetFillColorAlpha(3,0.35); 
  m_tge[2]->SetName("gg3");
  m_tge[2]->SetTitle("Total Uncertainties");
  m_tge[2]->SetMarkerColor(markerColorCode);
  m_tge[2]->SetLineWidth(makerLineWidthCode);
  m_tge[2]->SetMarkerSize(markerSizeCode);
  m_tge[2]->SetMarkerStyle(markerStyleCode);
  m_tge[3]->SetName("gg1_corrected");
  m_tge[3]->SetTitle("Statistical Errors");
  m_tge[3]->SetFillColorAlpha(2,0.35);
  m_tge[4]->SetName("gg2_corrected");
  m_tge[4]->SetTitle("Systematic Errors");
  m_tge[4]->SetFillColorAlpha(3,0.35); 
  m_tge[5]->SetName("gg3_corrected");
  m_tge[5]->SetTitle("Total Uncertainties");
  m_tge[5]->SetMarkerColor(markerColorCode);
  m_tge[5]->SetLineWidth(makerLineWidthCode);
  m_tge[5]->SetMarkerSize(markerSizeCode);
  m_tge[5]->SetMarkerStyle(markerStyleCode);
}

void conv2double(std::vector<std::string> words, double &val, double &stat, double &syst) {
  val  = std::stod(words.at(2));
  stat = std::stod(words.at(3));
  syst = std::stod(words.at(4));
}

std::vector<myData*> dataHandler() {
  myData *he = new myData("Helium");
  myData *ne = new myData("Neon");
  myData *kr = new myData("Kripton");
  myData *xe = new myData("Xeon");
  std::ifstream input;
  input.open("hermesData.txt");
  std::string foo, line;
  std::vector<std::string> words = {};
  double val,stat,syst;
  // Read data and fill objects
  std::getline(input,foo);
  std::getline(input,foo);
  for (int i=0; i<DIM;++i) {
    std::getline(input,line); // read line of data
    boost::split(words, line, boost::is_any_of(" "), boost::token_compress_on);
    conv2double(words,val,stat,syst);
    he->fill(i,val,stat,syst);
  }
  std::getline(input,foo);
  for (int i=0; i<DIM;++i) {
    std::getline(input,line); // read line of data
    boost::split(words, line, boost::is_any_of(" "), boost::token_compress_on);
    conv2double(words,val,stat,syst);
    ne->fill(i,val,stat,syst);
  }
  std::getline(input,foo);
  for (int i=0; i<DIM;++i) {
    std::getline(input,line); // read line of data
    boost::split(words, line, boost::is_any_of(" "), boost::token_compress_on);
    conv2double(words,val,stat,syst);
    kr->fill(i,val,stat,syst);
  }
  std::getline(input,foo);
  for (int i=0; i<DIM;++i) {
    std::getline(input,line); // read line of data
    boost::split(words, line, boost::is_any_of(" "), boost::token_compress_on);
    conv2double(words,val,stat,syst);
    xe->fill(i,val,stat,syst);
  }
  input.close();
  // Apply Helium substraction
  he->applyCorrection(he);
  ne->applyCorrection(he);
  kr->applyCorrection(he);
  xe->applyCorrection(he);
  // Create TGraphErros contained in each object
  he->doTGraphErrors();
  ne->doTGraphErrors();
  kr->doTGraphErrors();
  xe->doTGraphErrors();
  // Do plots of data
  doDataPlots(he,ne,kr,xe);
  // Prepare output and finish
  std::vector<myData*> output;
  // output.push_back(he); // we don't need to return He.
  output.push_back(ne);
  output.push_back(kr);
  output.push_back(xe);
  std::cout << "dataHandler finished" << std::endl;
  return output;
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

  TLegend *leg[4];
  leg[0] = new TLegend(0.1,0.1,0.5,0.25);//0.1,0.7,0.48,0.9
  leg[1] = new TLegend(0.1,0.1,0.5,0.25);//0.1,0.7,0.48,0.9
  leg[2] = new TLegend(0.1,0.1,0.5,0.25);//0.1,0.7,0.48,0.9
  leg[3] = new TLegend(0.1,0.1,0.5,0.25);//0.1,0.7,0.48,0.9
  leg[0]->AddEntry(he->m_tge[0],"Statistical Uncertainties","f");
  leg[0]->AddEntry(he->m_tge[1],"Systematic Uncertainties","f");
  leg[0]->AddEntry(he->m_tge[2],"Total Uncertainties","lep");
  leg[1]->AddEntry(ne->m_tge[0],"Statistical Uncertainties","f");
  leg[1]->AddEntry(ne->m_tge[1],"Systematic Uncertainties","f");
  leg[1]->AddEntry(ne->m_tge[2],"Total Uncertainties","lep");
  leg[2]->AddEntry(kr->m_tge[0],"Statistical Uncertainties","f");
  leg[2]->AddEntry(kr->m_tge[1],"Systematic Uncertainties","f");
  leg[2]->AddEntry(kr->m_tge[2],"Total Uncertainties","lep");
  leg[3]->AddEntry(xe->m_tge[0],"Statistical Uncertainties","f");
  leg[3]->AddEntry(xe->m_tge[1],"Systematic Uncertainties","f");
  leg[3]->AddEntry(xe->m_tge[2],"Total Uncertainties","lep");

  std::vector<std::string> labels = {"HERMES Helium data", "HERMES Neon data", "HERMES Kripton data", "HERMES Xeon data"};
  std::vector<std::string> labels2 = {"HERMES Helium substracted", "HERMES Neon with Helium substracted", "HERMES Kripton with Helium substracted", "HERMES Xeon with Helium substracted"};
  std::vector<std::string> files = {"data_he.pdf","data_ne.pdf","data_kr.pdf","data_xe.pdf"};
  std::vector<std::string> files2 = {"data_he_corr.pdf","data_ne_corr.pdf","data_kr_corr.pdf","data_xe_corr.pdf"};

  TCanvas *c = new TCanvas("canvas","canvas title",800,600);
  // c->Divide(2,4);
  std::cout << "Creating Canvas" << std::endl;
  for (int i=0; i<4; ++i) {
    // c->cd(2*i+1);
    mg[0][i]->Draw("a2");
    mg[0][i]->GetXaxis()->SetTitle("z_{h}");
    mg[0][i]->GetYaxis()->SetTitle("<#DeltaP_{T}^{2}> [GeV^{2}]");
    mg[0][i]->GetYaxis()->SetTitleOffset(1.5);
    mg[0][i]->GetYaxis()->SetRangeUser(-0.02,0.05);
    mg[1][i]->Draw("p");
    leg[i]->Draw();
    UTFSMLabel(0.125,0.85,"Internal, work on progress");
    AddLabel(0.125,0.8,labels[i].c_str());
    c->Print(files[i].c_str());
    c->Clear();
    // c->cd(2*i+2);
    mg_corrected[0][i]->Draw("a2");
    mg_corrected[0][i]->GetXaxis()->SetTitle("z_{h}");
    mg_corrected[0][i]->GetYaxis()->SetTitle("<#DeltaP_{T}^{2}> [GeV^{2}]");
    mg_corrected[0][i]->GetYaxis()->SetTitleOffset(1.5);
    mg_corrected[0][i]->GetYaxis()->SetRangeUser(-0.02,0.05);
    mg_corrected[1][i]->Draw("p");
    leg[i]->Draw();
    UTFSMLabel(0.125,0.85,"Internal, work on progress");
    AddLabel(0.125,0.8,labels2[i].c_str());
    c->Print(files2[i].c_str());
  }
  // c->Print("plot_HermesData.pdf");
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

void UTFSMLabel(Double_t x,Double_t y,const char* text) {
  TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize); 
  l.SetNDC();
  l.SetTextFont(72);
  double delx = 0.115*696*gPad->GetWh()/(472*gPad->GetWw());
  l.DrawLatex(x,y,"UTFSM");
  if (text) {
    TLatex p; 
    p.SetNDC();
    p.SetTextFont(42);
    // p.SetTextColor(color);
    p.DrawLatex(x+delx,y,text);
    //    p.DrawLatex(x,y,"#sqrt{s}=900GeV");
  }
}

void AddLabel(Double_t x,Double_t y,const char* text) {
  TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize); 
  l.SetNDC();
  l.SetTextFont(42);
  l.DrawLatex(x,y,text);
}