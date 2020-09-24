double SIG1[4] = { 27.075, 25.604, 25.109, 24.946 }; // interpolated cross-section for pi+
double ZBINS[4] = { 0.31, 0.54, 0.75, 0.94 };        // pi+
double BINRATIO[4] = { 0.22, 0.43, 0.44, 0.18 };     // PI+ with HERMES cuts
double NU[4] = { 14.37, 13.03, 12.33, 10.70 };

void xsec()
{
  gStyle->SetEndErrorSize(5);
  auto f = TFile::Open("OutputROOT.20200718.BL_SIG_piplus.root");
  auto tg_lp = (TGraphErrors*)f->Get("tg_lp");
  auto tg_xsec_fit = (TGraphErrors*)f->Get("tg_sigma");
  TGraph* tg_xsec_pdg = new TGraph(4, ZBINS, SIG1);
  tg_xsec_pdg->SetLineColor(kRed);
  tg_xsec_pdg->SetLineWidth(2);

  tg_xsec_fit->GetYaxis()->SetRangeUser(0, 120);
  tg_xsec_fit->GetXaxis()->SetLimits(0, 1);
  tg_xsec_fit->GetXaxis()->SetNdivisions(505);
  TCanvas* cnv_lc = new TCanvas("cnv_lc", "cnv_lc", 800, 600);
  tg_xsec_fit->Draw("APE");
  tg_xsec_pdg->Draw("LSAME");

  TLegend* leg = new TLegend(0.2, 0.7, 0.35, 0.92);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->AddEntry(tg_xsec_pdg, "PDG xsec", "l");
  leg->AddEntry(tg_xsec_fit, "Fit xsec", "pel");
  leg->Draw();

  double xxx[4];
  xxx[0] = std::cbrt(4.0026);  // Helium
  xxx[1] = std::cbrt(20.1797); // Neon
  xxx[2] = std::cbrt(83.7980); // Krypton
  xxx[3] = std::cbrt(131.293); // Xenon
  string names[4] = { "He", "Ne", "Kr", "Xe" };
  // Calculate energy loss per bin
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      double RA = 1.1 * xxx[j];
      double lifetime = ((TGraphErrors*)f->Get(Form("tg_average_length_%d",i)))->Eval(RA);
      printf("RA = %.4f, Lc = %.4f \t",RA,lifetime);
      double delta_xsec = tg_xsec_pdg->GetY()[i] - tg_xsec_fit->GetY()[i];
      double SHIFT = NU[i] * (ZBINS[i] * (1 - BINRATIO[i]));
      SHIFT /= (1 - TMath::Exp(delta_xsec * (RA - lifetime)) + ZBINS[i] * (1 - BINRATIO[i]));
      printf("NU = %.4f, SHIFT = %.4f \t", NU[i], SHIFT);
      double energy_loss = NU[i] - SHIFT;
      energy_loss = NU[i] - energy_loss;
      if (delta_xsec < 0 || (RA - lifetime) < 0) {
        energy_loss = -99;
        printf("BIN %d, delta_xsec = %.4f, E_LOSS(%s)=%.4f (GeV)\n", i, delta_xsec, names[j].c_str(), energy_loss);
      } else {
        printf("BIN %d, delta_xsec = %.4f, E_LOSS(%s)=%.4f (GeV)\n", i, delta_xsec, names[j].c_str(), energy_loss);
      }
    }
  }
}
