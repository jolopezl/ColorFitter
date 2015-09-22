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