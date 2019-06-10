int PlotShift()
{
  SetAtlasStyle();

  TF1* fg1 = new TF1("fg1", "fabs(x*((1 + sqrt(1 - pow([0]/(x*[1]),2))) / ([3]/[1] + 1 + TMath::Sqrt(1 + [2]/TMath::Power([1],2)))) - x)",
                     0.01, 1);

  fg1->SetParName(0, "MT");
  fg1->SetParName(1, "NU");
  fg1->SetParName(2, "Q2");
  fg1->SetParName(3, "MP");
  fg1->SetParameter(0, 0.14);
  fg1->SetParameter(1, 12.4);
  fg1->SetParameter(2, 2.4);
  fg1->SetParameter(3, 0.938);

  fg1->Print();

  fg1->SetTitle(";#tilde{z};#deltaz = |z - #tilde{z}|");
  fg1->GetXaxis()->SetLimits(0, 1.0);
  fg1->GetXaxis()->SetRangeUser(0, 1.0);
  fg1->GetXaxis()->SetNdivisions(505);

  TCanvas* c1 = new TCanvas("c1", "shift", 800, 600);
  fg1->Draw();

  return 1;
}
