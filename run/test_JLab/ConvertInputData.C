/*

Jorge Lopez
Oct. 24, 2017

Read pT-broadennig and multiplicity ratios and produce TGraphErrors

*/
#include <fstream>
#include <sstream>
#include <string>

void ConvertInputData()
{
  SetAtlasStyle();
  TFile* fout = new TFile("InputData-JLab.root", "RECREATE");

  double zmin, zmax;
  double val[3];
  double err[3];
  double xp[3];
  xp[0] = pow(12.0107, 1. / 3.); // C
  xp[1] = pow(55.845, 1. / 3.);  // Fe
  xp[2] = pow(207.2, 1. / 3.);   // Pb

  double xerr[3] = { 0, 0, 0 };

  TGraphErrors tge1[16][10];
  TGraphErrors tge2[16][10];

  TNamed slice_name[16];

  std::ifstream infile1("pt_broadening.txt");
  std::string line;
  std::getline(infile1, line);
  std::getline(infile1, line);
  for (int islice = 0; islice < 16; ++islice) {
    std::getline(infile1, line);
    slice_name[islice] = TNamed(Form("slice_%d", islice + 1), line.c_str());
    slice_name[islice].Write();
    for (int iz = 0; iz < 10; ++iz) {
      std::cout << "Reading slice #" << islice + 1 << ", z-bin #" << iz + 1 << std::endl;
      std::getline(infile1, line);
      // std::cout << line << std::endl;
      std::istringstream iss(line);
      if (!(iss >> zmin >> zmax >> val[0] >> err[0] >> val[1] >> err[1] >> val[2] >> err[2])) {
        break;
      } // error
      // std::cout << "\t" << zmin << "\t" << zmax << "\t" << val[0] << "\t" << err[0] << "\t" << val[1] << "\t" << err[1] << "\t" << val[2] << "\t" << err[2] << std::endl;
      tge1[islice][iz] = TGraphErrors(3, xp, val, xerr, err);
      tge1[islice][iz].SetName(Form("tge_PT2_slice_%d_zbin_%d", islice + 1, iz + 1));
      tge1[islice][iz].SetTitle("p_{T}^{2} vs A^{1/3};A^{1/3};p_{T}^{2} [GeV^{2}]");
      tge1[islice][iz].Write();
    }
    std::getline(infile1, line);
  }

  std::ifstream infile2("multiplicity_ratio.txt");
  std::getline(infile2, line);
  std::getline(infile2, line);
  for (int islice = 0; islice < 16; ++islice) {
    std::getline(infile2, line);
    for (int iz = 0; iz < 10; ++iz) {
      std::cout << "Reading slice #" << islice + 1 << ", z-bin #" << iz + 1 << std::endl;
      std::getline(infile2, line);
      // std::cout << line << std::endl;
      std::istringstream iss(line);
      if (!(iss >> zmin >> zmax >> val[0] >> err[0] >> val[1] >> err[1] >> val[2] >> err[2])) {
        break;
      } // error
      // std::cout << "\t" << zmin << "\t" << zmax << "\t" << val[0] << "\t" << err[0] << "\t" << val[1] << "\t" << err[1] << "\t" << val[2] << "\t" << err[2] << std::endl;
      tge2[islice][iz] = TGraphErrors(3, xp, val, xerr, err);
      tge2[islice][iz].SetName(Form("tge_RM_slice_%d_zbin_%d", islice + 1, iz + 1));
      tge2[islice][iz].SetTitle("R_{M} vs A^{1/3};A^{1/3};R_{M}");
      tge2[islice][iz].Write();
    }
    std::getline(infile2, line);
  }

  gStyle->SetLegendBorderSize(1);
  gStyle->SetLegendFont(42);
  gStyle->SetLegendTextSize(0.05);

  TCanvas* c1 = new TCanvas("c1", "title", 1600, 1600);
  c1->DivideSquare(16, 0, 0);
  for (int islice = 0; islice < 16; ++islice) {
    c1->cd(islice + 1);
    for (int iz = 0; iz < 10; ++iz) {
      tge1[islice][iz].SetMarkerStyle(20 + iz);
      tge1[islice][iz].SetMarkerColor(iz + 51);
      tge1[islice][iz].GetYaxis()->SetTitleOffset(6);
      tge1[islice][iz].GetXaxis()->SetTitleOffset(4);
      if (iz == 0) {
        tge1[islice][iz].GetYaxis()->SetRangeUser(-0.044, 0.11);
        tge1[islice][iz].Draw("APEX");
      } else
        tge1[islice][iz].Draw("PSAMEX");
    }
    myText(0.2, 0.9, kBlack, slice_name[islice].GetTitle(), 22);
  }
  c1->cd(12);
  TLegend* ll = new TLegend(0, 0, 1, 0.2);
  ll->SetNColumns(5);
  for (int ii = 0; ii < 10; ++ii) {
    ll->AddEntry(&tge1[15][ii], Form("z-bin #%d", ii + 1), "P");
  }
  ll->Draw();
  c1->Print("plot_pt-broadening.pdf");

  TCanvas* c2 = new TCanvas("c1", "title", 1600, 1600);
  c2->DivideSquare(16, 0, 0);
  for (int islice = 0; islice < 16; ++islice) {
    c2->cd(islice + 1);
    for (int iz = 0; iz < 10; ++iz) {
      tge2[islice][iz].SetMarkerStyle(20 + iz);
      tge2[islice][iz].SetMarkerColor(iz + 51);
      tge2[islice][iz].GetYaxis()->SetTitleOffset(6);
      tge2[islice][iz].GetXaxis()->SetTitleOffset(4);
      if (iz == 0) {
        tge2[islice][iz].GetYaxis()->SetRangeUser(-0.1, 1.89);
        tge2[islice][iz].Draw("APEX");
      } else
        tge2[islice][iz].Draw("PSAMEX");
    }
    myText(0.2, 0.9, kBlack, slice_name[islice].GetTitle(), 22);
  }
  c2->cd(12);
  ll->Draw();
  c2->Print("plot_multiplicity_ratio.pdf");
}
