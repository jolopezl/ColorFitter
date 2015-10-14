#include "graphics.h"

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
    p.DrawLatex(x+1.1*delx,y,text);
    //    p.DrawLatex(x,y,"#sqrt{s}=900GeV");
  }
}

void AddLabel(Double_t x,Double_t y,const char* text) {
  TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize); 
  l.SetNDC();
  l.SetTextFont(42);
  l.DrawLatex(x,y,text);
}

void doDataPlots(myConfig* config, myData* he, myData* ne, myData* kr, myData* xe) {

  // TStyle *gs = new TStyle("gs", "gs1");
  // gs->SetHatchesLineWidth(10);
// 
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

  const float lx0 = 0.1125;
  const float ly0 = 0.1125;
  const float dx0 = 0.4;
  const float dy0 = 0.15;
  TLegend *leg[4];
  leg[0] = new TLegend(lx0,ly0,lx0+dx0,ly0+dy0);//0.1,0.7,0.48,0.9
  leg[1] = new TLegend(lx0,ly0,lx0+dx0,ly0+dy0);//0.1,0.7,0.48,0.9
  leg[2] = new TLegend(lx0,ly0,lx0+dx0,ly0+dy0);//0.1,0.7,0.48,0.9
  leg[3] = new TLegend(lx0,ly0,lx0+dx0,ly0+dy0);//0.1,0.7,0.48,0.9
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

  for (int i=0; i<4; ++i) {
    leg[i]->SetBorderSize(0.0);
    leg[i]->SetFillStyle(0);
  }

  std::vector<std::string> labels = {"HERMES Helium data", "HERMES Neon data", "HERMES Kripton data", "HERMES Xenon data"};
  std::vector<std::string> labels2 = {"HERMES Helium substracted", "HERMES Neon with Helium substracted", "HERMES Kripton with Helium substracted", "HERMES Xenon with Helium substracted"};
  std::vector<std::string> files = {"data_he.pdf","data_ne.pdf","data_kr.pdf","data_xe.pdf"};
  std::vector<std::string> files2 = {"data_he_corr.pdf","data_ne_corr.pdf","data_kr_corr.pdf","data_xe_corr.pdf"};

  TF1 *line00 = new TF1("zero line","00",0.0,1.2);
  line00->SetLineWidth(2);
  line00->SetLineColor(kRed);
  line00->SetLineStyle(2);
  line00->Draw("SAME");

  TCanvas *c = new TCanvas("canvas","canvas title",800,600);
  // c->Divide(2,4);
  std::cout << "Creating Canvas" << std::endl;
  for (int i=0; i<4; ++i) {
    // c->cd(2*i+1);
    mg[0][i]->Draw("a2");
    mg[0][i]->GetXaxis()->SetTitle("z");
    mg[0][i]->GetYaxis()->SetTitle("#Delta#LTp_{t}^{2}#GT [GeV^{2}]");
    mg[0][i]->GetYaxis()->SetTitleOffset(1.25);
    mg[0][i]->GetYaxis()->SetRangeUser(-0.05,0.05);
    mg[1][i]->Draw("p");
    // line00->Draw("SAME");
    leg[i]->Draw();
    UTFSMLabel(0.125,0.85,"Internal, work in progress");
    AddLabel(0.125,0.8,labels[i].c_str());
    // c->SetGrid();
    c->Print(files[i].c_str());
    c->Clear();
    // c->cd(2*i+2);
    mg_corrected[0][i]->Draw("a2");
    mg_corrected[0][i]->GetXaxis()->SetTitle("z");
    mg_corrected[0][i]->GetYaxis()->SetTitle("#Delta#LTp_{t}^{2}#GT [GeV^{2}]");
    mg_corrected[0][i]->GetYaxis()->SetTitleOffset(1.25);
    mg_corrected[0][i]->GetYaxis()->SetRangeUser(-0.05,0.05);
    mg_corrected[1][i]->Draw("p");
    // line00->Draw("SAME");
    leg[i]->Draw();
    UTFSMLabel(0.125,0.85,"Internal, work in progress");
    AddLabel(0.125,0.8,labels2[i].c_str());
    // c->SetGrid();
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

void plotFitOutput(std::string filename) {
  int basecol = 4-4;
  //read the input file
  std::ifstream input;
  input.open(filename);
  std::string binfo;
  std::string line;
  std::vector<std::string> words;
  std::vector<double> zbin;
  std::vector<double> err_zbin = {0.10,0.11,0.11,0.08};
  std::vector<double> qhat,lp,sigma,vlog,dz;
  std::vector<double> err_qhat,err_lp,err_sigma,err_vlog,err_dz;
  std::vector<double> chisq;
  std::getline(input,binfo);
  for (int i=0; i<4; ++i) {
    std::getline(input,line);
    boost::split(words, line, boost::is_any_of("\t"), boost::token_compress_on);
    std::cout << line << std::endl;
    zbin.push_back(std::stod(words[0+basecol]));
    qhat.push_back(std::stod(words[1+basecol]));
    lp.push_back(std::stod(words[2+basecol]));
    sigma.push_back(std::stod(words[3+basecol]));
    vlog.push_back(std::stod(words[4+basecol]));
    dz.push_back(std::stod(words[5+basecol]));
    err_qhat.push_back(std::stod(words[6+basecol]));
    err_lp.push_back(std::stod(words[7+basecol]));
    err_sigma.push_back(std::stod(words[8+basecol]));
    err_vlog.push_back(std::stod(words[9+basecol]));
    err_dz.push_back(std::stod(words[10+basecol]));
    chisq.push_back(std::stod(words[11+basecol]));
  }
  //
  TCanvas *c = new TCanvas("c1","plots",800,600);
  const int markerStyleCode = 21; // circle 20, box 21
  const int markerColorCode = 1; // black 1, red 2, blue 4
  const int markerSizeCode = 1;
  const int markerLineWidthCode = 2;
  // const int fillColorCode = 4;
  // const float fillAlphaCode = 0.3;
  // q-hats
  TGraphErrors *tge_qhat = new TGraphErrors(zbin.size(),&zbin[0],&qhat[0],&err_zbin[0],&err_qhat[0]);
  TLegend *leg_qhat = new TLegend(0.1,0.1,0.5,0.2);//0.1,0.7,0.48,0.9
  leg_qhat->AddEntry(tge_qhat,"Total Uncertainties","lep");
  tge_qhat->SetTitle();
  tge_qhat->SetMarkerColor(markerColorCode);
  tge_qhat->SetLineWidth(markerLineWidthCode);
  tge_qhat->SetMarkerSize(markerSizeCode);
  tge_qhat->SetMarkerStyle(markerStyleCode);
  // tge_qhat->SetFillColorAlpha(fillColorCode,fillAlphaCode);
  // tge_qhat->SetFillStyle(1);
  // tge_qhat->SetFillColor(fillColorCode);
  tge_qhat->GetYaxis()->SetRangeUser(-0.4,1.4);
  tge_qhat->GetXaxis()->SetTitle("z");
  tge_qhat->GetYaxis()->SetTitle("#hat{q} [GeV/fm^{2}]");
  tge_qhat->Draw("ap");
  // leg_qhat->Draw();
  UTFSMLabel(0.125,0.85,"Internal, work in progress");
  c->Print("plotFO_qhat.pdf");
  c->Clear();
  // Formation length
  TGraphErrors *tge_lp = new TGraphErrors(zbin.size(),&zbin[0],&lp[0],&err_zbin[0],&err_lp[0]);
  TLegend *leg_lp = new TLegend(0.1,0.1,0.5,0.2);//0.1,0.7,0.48,0.9
  leg_lp->AddEntry(tge_lp,"Total Uncertainties","lep");
  tge_lp->SetTitle();
  tge_lp->SetMarkerColor(markerColorCode);
  tge_lp->SetLineWidth(markerLineWidthCode);
  tge_lp->SetMarkerSize(markerSizeCode);
  tge_lp->SetMarkerStyle(markerStyleCode);
  tge_lp->GetYaxis()->SetRangeUser(-2,26);
  tge_lp->GetXaxis()->SetTitle("z");
  tge_lp->GetYaxis()->SetTitle("l_{p} [fm]");
  tge_lp->Draw("ap");
  // leg_lp->Draw();
  UTFSMLabel(0.125,0.85,"Internal, work in progress");
  c->Print("plotFO_lp.pdf");
  c->Clear();
  // pre-hadron cross section
  TGraphErrors *tge_sigma = new TGraphErrors(zbin.size(),&zbin[0],&sigma[0],&err_zbin[0],&err_sigma[0]);
  TLegend *leg_sigma = new TLegend(0.1,0.1,0.5,0.2);//0.1,0.7,0.48,0.9
  leg_sigma->AddEntry(tge_sigma,"Pre hadron cross section","lep");
  tge_sigma->SetTitle();
  tge_sigma->SetMarkerColor(markerColorCode);
  tge_sigma->SetLineWidth(markerLineWidthCode);
  tge_sigma->SetMarkerSize(markerSizeCode);
  tge_sigma->SetMarkerStyle(markerStyleCode);
  tge_sigma->GetYaxis()->SetRangeUser(-100,400);
  tge_sigma->GetXaxis()->SetTitle("z");
  tge_sigma->GetYaxis()->SetTitle("#sigma_{pre-hadron} [mbarn]");
  tge_sigma->GetYaxis()->SetTitleOffset(1.5);
  tge_sigma->Draw("ap");
  TF1 *line40 = new TF1("40 mbarns line","40",0.0,1.2);
  line40->SetLineWidth(markerLineWidthCode);
  line40->SetLineColor(kRed);
  line40->SetLineStyle(2);
  line40->Draw("SAME");
  leg_sigma->AddEntry(line40,"Nominal value for fully formed pions","l");
  leg_sigma->Draw();
  UTFSMLabel(0.125,0.85,"Internal, work in progress");
  c->Print("plotFO_sigma.pdf");
  c->Clear();
  // pre-hadron cross section
  TGraphErrors *tge_dz = new TGraphErrors(zbin.size(),&zbin[0],&dz[0],&err_zbin[0],&err_dz[0]);
  TLegend *leg_dz = new TLegend(0.1,0.1,0.5,0.2);//0.1,0.7,0.48,0.9
  leg_dz->AddEntry(tge_dz,"Total Uncertainties","lep");
  tge_dz->SetTitle();
  tge_dz->SetMarkerColor(markerColorCode);
  tge_dz->SetLineWidth(markerLineWidthCode);
  tge_dz->SetMarkerSize(markerSizeCode);
  tge_dz->SetMarkerStyle(markerStyleCode);
  tge_dz->GetYaxis()->SetRangeUser(-0.1,0.5);
  tge_dz->GetXaxis()->SetTitle("z");
  tge_dz->GetYaxis()->SetTitle("#Delta z");
  tge_dz->Draw("ap");
  // leg_dz->Draw();
  UTFSMLabel(0.125,0.85,"Internal, work in progress");
  c->Print("plotFO_dz.pdf");
  c->Clear();
}
