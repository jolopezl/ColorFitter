void plot()
{
  // read the input data
  auto fref = TFile::Open("OutputROOT.20200707.BL30_piplus.root");
  auto tg_lp_ref = (TGraphErrors*)fref->Get("tg_lp");
  auto f = TFile::Open("OutputROOT.20200804.BL30NN_piplus.root");
  auto tg_lp = (TGraphErrors*)f->Get("tg_lp");
  auto tg_c1 = (TGraphErrors*)f->Get("tg_c1");
  auto tg_c2 = (TGraphErrors*)f->Get("tg_c2");
  // setup the plot
  double A[4] = { 4.0026, 20.1797, 83.7980, 131.2930 };
  std::vector<TGraphErrors*> tg;
  for (int i = 0; i < 4; ++i) {
    tg.push_back(new TGraphErrors(4));
    for (int j = 0; j < 4; ++j) {
      double x = 0;
      double yval = 0;
      double yerr = 0;
      x = tg_lp->GetX()[j];
      yval = tg_lp->GetY()[j];
      yval += tg_c1->GetY()[j] * std::pow(A[i], 1. / 3.);
      yval += tg_c2->GetY()[j] * std::pow(A[i], 2. / 3.);
      yerr += std::pow(tg_lp->GetEY()[j], 2);
      yerr += std::pow(tg_c1->GetEY()[j] * std::pow(A[i], 1. / 3.), 2);
      yerr += std::pow(tg_c2->GetEY()[j] * std::pow(A[i], 2. / 3.), 2);
      yerr += 2 * std::pow(A[i], 1./3.) * tg_lp->GetEY()[j] * tg_c1->GetEY()[j] * (-0.950);
      yerr += 2 * std::pow(A[i], 2./3.) * tg_lp->GetEY()[j] * tg_c2->GetEY()[j] * (0.6);
      yerr += 2 * std::pow(A[i], 1./3.) * std::pow(A[i], 2./3.) * tg_c1->GetEY()[j] * tg_c2->GetEY()[j] * (-0.950);
      yerr = std::sqrt(yerr);
      tg[i]->SetPoint(j, x, yval);
      tg[i]->SetPointError(j, 0, yerr);
      std::cout << i << ", point " << j << ", x = " << x << ", y = " << yval << ", yerr = " << yerr <<std::endl;
    }
  }

  // TF1 *f1 = new TF1("f1", "(0.5*[0] + ([1] - [2]) * ((1 - x) + 0.5 * (TMath::Sqrt(1 + [3] / TMath::Power([1] - [2], 2)) - 1))) / [4]", 0, 1);
  TF1 *f1 = new TF1("f1", "(([1]+2*([2]-[3]))/(2*[0]))*x*(log(1/(x*x))-1+x*x)/(1-x*x)", 0, 1);
  f1->SetParName(0, "KAPPA");
  f1->SetParName(1, "MP");
  f1->SetParName(2, "NU");
  f1->SetParName(3, "EPS");
  f1->SetParameter(0, 1.0);
  f1->SetParameter(1, 0.938);
  f1->SetParameter(2, 13.1);
  f1->SetParameter(3, 0.0);
  // f1->FixParameter(0, 1.0);
  f1->FixParameter(1, 0.938);
  f1->FixParameter(2, 13.1);
  // f1->FixParameter(3, 2.4);

  tg_lp_ref->Fit("f1");
  for (int i = 0; i < 4; ++i) {
    tg[i]->Fit("f1");
  }

  
  int colors[4] = {kAzure,kViolet,kPink,kOrange};
  for (int i = 0; i < 4; ++i) {
    tg[i]->SetMarkerStyle(i + 21);
    tg[i]->SetMarkerColor(colors[i]);
    tg[i]->SetLineColor(colors[i]);
    tg[i]->SetLineWidth(2);
  }

  tg_lp_ref->SetTitle(";z_{h};L_{c} (fm)");
  tg_lp_ref->SetLineWidth(2);
  tg_lp_ref->GetYaxis()->SetRangeUser(0,15);
  tg_lp_ref->GetXaxis()->SetLimits(0,1);
  tg_lp_ref->GetXaxis()->SetNdivisions(505);

  TCanvas* cnv_lc = new TCanvas("cnv_lc", "cnv_lc", 800, 600);
  tg_lp_ref->Draw("APEL");
  tg[0]->Draw("PLSAME");
  tg[1]->Draw("PLSAME");
  tg[2]->Draw("PLSAME");
  tg[3]->Draw("PLSAME");

  tg_lp_ref->Draw("PSAME");

  TLegend* leg = new TLegend(0.2, 0.7, 0.35, 0.92);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->AddEntry(tg_lp_ref,"L_{c} - Baseline model","pel");
  leg->AddEntry(tg[0],"L_{c}(He)","pel");
  leg->AddEntry(tg[1],"L_{c}(Ne)","pel");
  leg->AddEntry(tg[2],"L_{c}(Kr)","pel");
  leg->AddEntry(tg[3],"L_{c}(Xe)","pel");
  leg->Draw();

}