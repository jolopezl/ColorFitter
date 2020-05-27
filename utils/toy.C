#define kappa 1.0
#define MP 0.938

#include "multiplicities.C"
#include "../source/model.cc"

TFile* fin = TFile::Open("../run/test_HERMES/FitOutput_production_length.root", "READ");

TFile* taya = TFile::Open("/Users/lopez/temp/taya/multiplicities/multiplicities.root", "READ");

double Lc(double nu, double Q2, double zh)
{
  return 0.5 * kappa * (MP + nu + std::sqrt(pow(nu, 2) + pow(Q2, 2)) - 2 * nu * zh);
}

double LcBialas(double nu, double Q2, double zh)
{
  const char* LundLogFull = "(([1]+2*[2])/(2*[0]))*x*(log(1/(x*x))-1+x*x)/(1-x*x)"; // Bialas paper
  TF1* fg2 = new TF1("fg2", LundLogFull, 0, 1);
  fg2->SetParName(0, "KAPPA");
  fg2->SetParName(1, "MP");
  fg2->SetParName(2, "NU");
  fg2->SetParameter(0, kappa);
  fg2->FixParameter(1, MP);
  fg2->FixParameter(2, nu);
  return fg2->Eval(zh);
}

double LcFit(double zh)
{
  TGraphAsymmErrors* lc = (TGraphAsymmErrors*)fin->Get("model");
  TGraphErrors* lch = new TGraphErrors(4);
  double x, y, xerr, yerr;
  for (int i = 0; i < 4; ++i) {
    lc->GetPoint(i, x, y);
    xerr = lc->GetErrorXhigh(i);
    yerr = lc->GetErrorYhigh(i);
    lch->SetPoint(i, x + xerr, y);
    lch->SetPointError(i, 0, yerr);
  }
  return lch->Eval(zh);
}

void toy()
{
  // gROOT->LoadMacro("../source/model.cc");
  Model m;
  m.Initialization();
  m.SetParameters("q0", 1.8);
  // m.SetParameters("sigma", 35);

  vector<double> zh;

  double z = 0.3;
  while (z <= 0.99) {
    // cout << z << endl;
    zh.push_back(z);
    z += 0.1;
  }

  vector<double> vecA = { 12, 56, 131 };

  map<double, double> sigmaA;
  sigmaA[vecA[0]] = 15;
  sigmaA[vecA[1]] = 25;
  sigmaA[vecA[2]] = 35;
  map<int, vector<double>> broadening;
  map<int, vector<double>> multiplicity;

  const double NU = 3.465;
  const double Q2 = 1.545;

  for (int i = 0; i < zh.size(); ++i) {
    m.SetParameters("lp", Lc(NU, Q2, zh[i]));
    // m.SetParameters("lp", LcBialas(NU, Q2, zh[i]));
    // m.SetParameters("lp", LcFit(zh[i]));
    // m.DoEnergyLoss(true, zh.size());
    // m.SetParameters("dz", 0.1);
    // m.SetBinRatio(i, 0.01, 0.5);
    for (const auto& A : vecA) {
      m.SetParameters("sigma", sigmaA[A]);
      m.Compute(A);
      vector<double> res = m.GetResultVector();
      broadening[A].push_back(res[0]);
      multiplicity[A].push_back(res[1]);
    }
  }

  map<int, TGraph*> tg_broadening;
  map<int, TGraph*> tg_multiplicity;

  for (const auto& A : vecA) {
    tg_broadening[A] = new TGraph(zh.size(), &zh[0], &(broadening[A])[0]);
    tg_multiplicity[A] = new TGraph(zh.size(), &zh[0], &(multiplicity[A])[0]);
  }

  vector<int> colorVec = { kAzure, kViolet, kPink };
  // auto data = multiplicities();
  vector<TGraphErrors*> data;
  data.push_back((TGraphErrors*)taya->Get("multiplicity_vs_zh_target_0_Q2_1_Nu_1.txt"));
  data.push_back((TGraphErrors*)taya->Get("multiplicity_vs_zh_target_1_Q2_1_Nu_1.txt"));
  data.push_back((TGraphErrors*)taya->Get("multiplicity_vs_zh_target_2_Q2_1_Nu_1.txt"));
  for (int i = 0; i < 3; ++i) {
    data[i]->SetMarkerColor(colorVec[i]);
    data[i]->SetLineColor(colorVec[i]);
    tg_multiplicity[vecA[i]]->SetLineColor(colorVec[i]);
    tg_multiplicity[vecA[i]]->SetLineWidth(4);
  }

  data[0]->GetXaxis()->SetNdivisions(505);
  data[0]->GetYaxis()->SetRangeUser(0, 1);
  data[0]->GetXaxis()->SetLimits(0, 1);
  data[0]->GetYaxis()->SetTitle("#it{R}_{M}");
  data[0]->GetYaxis()->SetTitleOffset(1.6);
  data[0]->GetXaxis()->SetTitle("#it{z}_{h}");

  TCanvas c("c", "title", 800, 600);
  data[0]->Draw("APE");
  data[1]->Draw("PSAME");
  data[2]->Draw("PSAME");
  for (const auto& A : vecA) {
    tg_multiplicity[A]->Draw("SAME");
  }

  TLegend* ll = new TLegend(0.2, 0.2, 0.35, 0.55);
  ll->SetBorderSize(0); // no border
  ll->SetFillStyle(0);
  ll->SetFillColor(0); // Legend background should be white
  ll->SetTextFont(42);
  ll->SetTextSize(0.03); // Increase entry font size!
  // ll->SetNColumns(2);
  ll->SetHeader("1.33<Q^{2}<1.76 (GeV^{2}), and 3.2<#nu<3.73 (GeV)");
  ll->AddEntry(data[0], "C data", "pe");
  ll->AddEntry(data[1], "Fe data", "pe");
  ll->AddEntry(data[2], "Pb data", "pe");
  ll->AddEntry(tg_multiplicity[vecA[0]], "C model", "l");
  ll->AddEntry(tg_multiplicity[vecA[1]], "Fe model", "l");
  ll->AddEntry(tg_multiplicity[vecA[2]], "Pb model", "l");
  ll->Draw();

  c.SaveAs("test.pdf");
}