void TestEstimationsImproved()
{
  SetAtlasStyle();
  TF1* fcn = new TF1("fcn", "([0]+[1]*x+[2]*pow(x,2)) + exp([3]+[4]*x)", 1, 100);
  fcn->SetParameter(0, 1.08904e-01);
  fcn->SetParameter(1, -1.26225e-03);
  fcn->SetParameter(2, 5.35460e-06);
  fcn->SetParameter(3, -1.40235e+00);
  fcn->SetParameter(4, -1.25454e-01);

  std::map<int, double> L0;
  L0[1] = 6.93319 / 9.24;
  L0[2] = 4.95501 / 8.40;
  L0[3] = 2.79043 / 7.94;
  L0[4] = 1.38668 / 7.14;

  TF1* fcnRel = new TF1("fcnRel", "[0]*TMath::Sqrt(x/(2*[1]*[2]) - 1)", 2, 150);
  TF1* fcnRel_up = new TF1("fcnRel_up", "[0]*TMath::Sqrt(x/(2*[1]*[2]) - 1)", 2, 150);
  TF1* fcnRel_down = new TF1("fcnRel_down", "[0]*TMath::Sqrt(x/(2*[1]*[2]) - 1)", 2, 150);
  fcnRel->SetParName(0, "coeff");
  fcnRel->SetParName(1, "Mp");
  fcnRel->SetParName(2, "xBj");
  fcnRel->SetParameter(0, L0[4]);
  fcnRel->SetParameter(1, 0.938); // PDG value in GeV^2

  TGraph* tg = new TGraph(120);
  double xBj = 0.1;
  for (int nu = 1; nu < 121; ++nu) {
    xBj = fcn->Eval(nu);
    fcnRel->SetParameter(2, xBj);
    cout << nu << "\t" << fcnRel->Eval(nu) << endl;
    tg->SetPoint(nu, nu, fcnRel->Eval(nu));
  }
}
