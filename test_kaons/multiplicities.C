using namespace std;

void ComputeFit(double* xval, double* xerrminus, double* xerrplus, double* yval, double* yerrminus, double* yerrplus) {
  // make 3 graphs
  // - g0, g_upper, g_lower
  // fit each one to a "pol4"
  TGraph* g_val = new TGraph(9);
  TGraph* g_plus = new TGraph(9);
  TGraph* g_minus = new TGraph(9);
  for (int i = 0; i < 9; ++i) {
    double x = xval[i];
    double y = yval[i];
    double y_plus = yval[i] + yerrplus[i];
    double y_minus = yval[i] - yerrminus[i];
    g_val->SetPoint(i,x,y);
    g_plus->SetPoint(i,x,y_plus);
    g_minus->SetPoint(i,x,y_minus);
  }
  g_val->Fit("pol4","Q");
  g_plus->Fit("pol4","Q");
  g_minus->Fit("pol4","Q");

  auto f_val = g_val->GetFunction("pol4");
  auto f_plus = g_plus->GetFunction("pol4");
  auto f_minus = g_minus->GetFunction("pol4");

  double zbin[4] = {0.32, 0.53, 0.75, 0.94};
  for (int i = 0; i < 4; ++i) {
    float z = zbin[i];
    cout << z << " " << f_val->Eval(z) << " " << f_plus->Eval(z)-f_minus->Eval(z) << endl;
  }

  return;

  TCanvas c("c");
  g_val->GetYaxis()->SetRangeUser(0.,1.1);
  g_val->SetMarkerStyle(20);
  g_val->Draw("APE");
  c.Print("test.pdf");

/**
// this has to dump
    Rm Value Stat. Error  Syst. Uncert.
  z-bin#1 
  z-bin#2 
  z-bin#3 
  z-bin#4 
// or
  Value Total Error Stat Error
**/
}

void multiplicities() {
  gROOT->SetStyle("Plain");
  // K+ multiplicty ratio (Helium/Deuterium) as a function of Z.
  // Plot: p6820_d5x1y1
  double p6820_d5x1y1_xval[] = { 0.16, 0.25, 0.35, 0.45, 0.55, 0.65, 0.75, 0.84, 0.95 };
  double p6820_d5x1y1_xerrminus[] = { 0.06, 0.04999999999999999, 0.04999999999999999, 0.04999999999999999, 0.050000000000000044, 0.050000000000000044, 0.050000000000000044, 0.039999999999999925, 0.04999999999999993 };
  double p6820_d5x1y1_xerrplus[] = { 0.04000000000000001, 0.04999999999999999, 0.050000000000000044, 0.04999999999999999, 0.04999999999999993, 0.04999999999999993, 0.050000000000000044, 0.06000000000000005, 0.3500000000000001 };
  double p6820_d5x1y1_yval[] = { 0.962, 0.953, 0.978, 0.956, 0.945, 0.95, 0.947, 0.984, 0.936 };
  double p6820_d5x1y1_yerrminus[] = { 0.03176476034853718, 0.02996664812754339, 0.03176476034853718, 0.0324499614791759, 0.03420526275297414, 0.03748332962798263, 0.04263801121065569, 0.05215361924162119, 0.06946221994724902 };
  double p6820_d5x1y1_yerrplus[] = { 0.03176476034853718, 0.02996664812754339, 0.03176476034853718, 0.0324499614791759, 0.03420526275297414, 0.03748332962798263, 0.04263801121065569, 0.05215361924162119, 0.06946221994724902 };
  double p6820_d5x1y1_ystatminus[] = { 0.015, 0.013, 0.015, 0.018, 0.021, 0.026, 0.033, 0.044, 0.064 };
  double p6820_d5x1y1_ystatplus[] = { 0.015, 0.013, 0.015, 0.018, 0.021, 0.026, 0.033, 0.044, 0.064 };
  int p6820_d5x1y1_numpoints = 9;
  TGraphAsymmErrors p6820_d5x1y1(p6820_d5x1y1_numpoints, p6820_d5x1y1_xval, p6820_d5x1y1_yval, p6820_d5x1y1_xerrminus, p6820_d5x1y1_xerrplus, p6820_d5x1y1_yerrminus, p6820_d5x1y1_yerrplus);
  p6820_d5x1y1.SetName("/HepData/6820/d5x1y1");
  p6820_d5x1y1.SetTitle("/HepData/6820/d5x1y1");
  p6820_d5x1y1.SetLineColor(2);
  p6820_d5x1y1.SetMarkerColor(2);
  p6820_d5x1y1.Draw("AP");

  cout << "K+ multiplicty ratio (Helium/Deuterium) as a function of Z." << endl;
  ComputeFit(p6820_d5x1y1_xval,
             p6820_d5x1y1_xerrminus,
             p6820_d5x1y1_xerrplus,
             p6820_d5x1y1_yval,
             p6820_d5x1y1_yerrminus,
             p6820_d5x1y1_yerrplus
             );

  // K+ multiplicty ratio (Neon/Deuterium) as a function of Z.
  // Plot: p6820_d14x1y1
  double p6820_d14x1y1_xval[] = { 0.16, 0.25, 0.35, 0.45, 0.55, 0.64, 0.75, 0.84, 0.94 };
  double p6820_d14x1y1_xerrminus[] = { 0.06, 0.04999999999999999, 0.04999999999999999, 0.04999999999999999, 0.050000000000000044, 0.040000000000000036, 0.050000000000000044, 0.039999999999999925, 0.039999999999999925 };
  double p6820_d14x1y1_xerrplus[] = { 0.04000000000000001, 0.04999999999999999, 0.050000000000000044, 0.04999999999999999, 0.04999999999999993, 0.05999999999999994, 0.050000000000000044, 0.06000000000000005, 0.3600000000000001 };
  double p6820_d14x1y1_yval[] = { 0.97, 0.961, 0.961, 0.923, 0.902, 0.925, 0.886, 0.858, 0.722 };
  double p6820_d14x1y1_yerrminus[] = { 0.029732137494637014, 0.02846049894151541, 0.028792360097775936, 0.028635642126552705, 0.0295296461204668, 0.031064449134018134, 0.03264965543462902, 0.0367967389859482, 0.04167733196834941 };
  double p6820_d14x1y1_yerrplus[] = { 0.029732137494637014, 0.02846049894151541, 0.028792360097775936, 0.028635642126552705, 0.0295296461204668, 0.031064449134018134, 0.03264965543462902, 0.0367967389859482, 0.04167733196834941 };
  double p6820_d14x1y1_ystatminus[] = { 0.01, 0.009, 0.01, 0.012, 0.014, 0.017, 0.021, 0.027, 0.036 };
  double p6820_d14x1y1_ystatplus[] = { 0.01, 0.009, 0.01, 0.012, 0.014, 0.017, 0.021, 0.027, 0.036 };
  int p6820_d14x1y1_numpoints = 9;
  TGraphAsymmErrors p6820_d14x1y1(p6820_d14x1y1_numpoints, p6820_d14x1y1_xval, p6820_d14x1y1_yval, p6820_d14x1y1_xerrminus, p6820_d14x1y1_xerrplus, p6820_d14x1y1_yerrminus, p6820_d14x1y1_yerrplus);
  p6820_d14x1y1.SetName("/HepData/6820/d14x1y1");
  p6820_d14x1y1.SetTitle("/HepData/6820/d14x1y1");
  p6820_d14x1y1.SetLineColor(3);
  p6820_d14x1y1.SetMarkerColor(3);
  p6820_d14x1y1.Draw("AP SAME");

  cout << "K+ multiplicty ratio (Neon/Deuterium) as a function of Z." << endl;
  ComputeFit(p6820_d14x1y1_xval,
             p6820_d14x1y1_xerrminus,
             p6820_d14x1y1_xerrplus,
             p6820_d14x1y1_yval,
             p6820_d14x1y1_yerrminus,
             p6820_d14x1y1_yerrplus
             );

  // K+ multiplicty ratio (Krypton/Deuterium) as a function of Z.
  // Plot: p6820_d23x1y1
  double p6820_d23x1y1_xval[] = { 0.16, 0.25, 0.35, 0.45, 0.55, 0.64, 0.75, 0.84, 0.95 };
  double p6820_d23x1y1_xerrminus[] = { 0.06, 0.04999999999999999, 0.04999999999999999, 0.04999999999999999, 0.050000000000000044, 0.040000000000000036, 0.050000000000000044, 0.039999999999999925, 0.04999999999999993 };
  double p6820_d23x1y1_xerrplus[] = { 0.04000000000000001, 0.04999999999999999, 0.050000000000000044, 0.04999999999999999, 0.04999999999999993, 0.05999999999999994, 0.050000000000000044, 0.06000000000000005, 0.3500000000000001 };
  double p6820_d23x1y1_yval[] = { 1.047, 0.985, 0.906, 0.848, 0.822, 0.787, 0.761, 0.687, 0.643 };
  double p6820_d23x1y1_yerrminus[] = { 0.034785054261852175, 0.03132091952673165, 0.02785677655436824, 0.02640075756488817, 0.02641968962724581, 0.026627053911388695, 0.029068883707497266, 0.031240998703626618, 0.03894868418830089 };
  double p6820_d23x1y1_yerrplus[] = { 0.034785054261852175, 0.03132091952673165, 0.02785677655436824, 0.02640075756488817, 0.02641968962724581, 0.026627053911388695, 0.029068883707497266, 0.031240998703626618, 0.03894868418830089 };
  double p6820_d23x1y1_ystatminus[] = { 0.011, 0.009, 0.01, 0.011, 0.013, 0.015, 0.019, 0.024, 0.034 };
  double p6820_d23x1y1_ystatplus[] = { 0.011, 0.009, 0.01, 0.011, 0.013, 0.015, 0.019, 0.024, 0.034 };
  int p6820_d23x1y1_numpoints = 9;
  TGraphAsymmErrors p6820_d23x1y1(p6820_d23x1y1_numpoints, p6820_d23x1y1_xval, p6820_d23x1y1_yval, p6820_d23x1y1_xerrminus, p6820_d23x1y1_xerrplus, p6820_d23x1y1_yerrminus, p6820_d23x1y1_yerrplus);
  p6820_d23x1y1.SetName("/HepData/6820/d23x1y1");
  p6820_d23x1y1.SetTitle("/HepData/6820/d23x1y1");
  p6820_d23x1y1.SetLineColor(3);
  p6820_d23x1y1.SetMarkerColor(3);
  p6820_d23x1y1.Draw("AP SAME");

  cout << "K+ multiplicty ratio (Krypton/Deuterium) as a function of Z." << endl;
  ComputeFit(p6820_d23x1y1_xval,
             p6820_d23x1y1_xerrminus,
             p6820_d23x1y1_xerrplus,
             p6820_d23x1y1_yval,
             p6820_d23x1y1_yerrminus,
             p6820_d23x1y1_yerrplus
             );

  // K+ multiplicty ratio (Xenon/Deuterium) as a function of Z.
  // Plot: p6820_d32x1y1
  double p6820_d32x1y1_xval[] = { 0.16, 0.25, 0.35, 0.44, 0.55, 0.64, 0.74, 0.84, 0.95 };
  double p6820_d32x1y1_xerrminus[] = { 0.06, 0.04999999999999999, 0.04999999999999999, 0.03999999999999998, 0.050000000000000044, 0.040000000000000036, 0.040000000000000036, 0.039999999999999925, 0.04999999999999993 };
  double p6820_d32x1y1_xerrplus[] = { 0.04000000000000001, 0.04999999999999999, 0.050000000000000044, 0.06, 0.04999999999999993, 0.05999999999999994, 0.06000000000000005, 0.06000000000000005, 0.3500000000000001 };
  double p6820_d32x1y1_yval[] = { 1.023, 0.958, 0.874, 0.808, 0.788, 0.77, 0.677, 0.633, 0.599 };
  double p6820_d32x1y1_yerrminus[] = { 0.03676955262170047, 0.031384709652950434, 0.027730849247724097, 0.026925824035672518, 0.027202941017470887, 0.02973213749463701, 0.03047950130825634, 0.03413209633175202, 0.04531004303683677 };
  double p6820_d32x1y1_yerrplus[] = { 0.03676955262170047, 0.031384709652950434, 0.027730849247724097, 0.026925824035672518, 0.027202941017470887, 0.02973213749463701, 0.03047950130825634, 0.03413209633175202, 0.04531004303683677 };
  double p6820_d32x1y1_ystatminus[] = { 0.014, 0.012, 0.012, 0.014, 0.016, 0.02, 0.023, 0.029, 0.042 };
  double p6820_d32x1y1_ystatplus[] = { 0.014, 0.012, 0.012, 0.014, 0.016, 0.02, 0.023, 0.029, 0.042 };
  int p6820_d32x1y1_numpoints = 9;
  TGraphAsymmErrors p6820_d32x1y1(p6820_d32x1y1_numpoints, p6820_d32x1y1_xval, p6820_d32x1y1_yval, p6820_d32x1y1_xerrminus, p6820_d32x1y1_xerrplus, p6820_d32x1y1_yerrminus, p6820_d32x1y1_yerrplus);
  p6820_d32x1y1.SetName("/HepData/6820/d32x1y1");
  p6820_d32x1y1.SetTitle("/HepData/6820/d32x1y1");
  p6820_d32x1y1.SetLineColor(4);
  p6820_d32x1y1.SetMarkerColor(4);
  p6820_d32x1y1.Draw("AP SAME");

  cout << "K+ multiplicty ratio (Xenon/Deuterium) as a function of Z." << endl;
  ComputeFit(p6820_d32x1y1_xval,
             p6820_d32x1y1_xerrminus,
             p6820_d32x1y1_xerrplus,
             p6820_d32x1y1_yval,
             p6820_d32x1y1_yerrminus,
             p6820_d32x1y1_yerrplus
             );
  return;
}