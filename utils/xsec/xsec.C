/*
  Read the cross section from http://pdg.lbl.gov/2019/hadronic-xsections/
*/

using namespace std;

TGraphAsymmErrors *readFromFile(std::string filename = "rpp2018-pipp_total.dat")
{
  std::ifstream infile;
  infile.open(filename);
  // FORMAT(I5,1X,4F11.5,2F8.4,1X,2F6.1,A)
  int POINT_NUMBER;
  double PLAB;
  double PLAB_MIN;
  double PLAB_MAX;
  double SIG;
  double STA_ERR_UP;
  double STA_ERR_LOW;
  double SY_ER_UP_PCT;
  double SY_ER_LOW_PCT;
  std::string REFERENCE;
  std::string FLAG;
  std::string REF1;
  std::string REF2;
  std::string REF3;

  std::string foo;
  for (int i = 0; i < 10; ++i)
  {
    std::getline(infile, foo);
    std::cout << foo << std::endl;
  }
  std::getline(infile, foo);
  std::cout << foo << std::endl;
  const int npoints = std::stoi(foo);
  std::cout << "Reading " << npoints << " points" << std::endl;

  TGraphAsymmErrors *tge = new TGraphAsymmErrors(npoints);
  tge->SetName(filename.c_str());
  for (int i = 0; i < npoints; ++i)
  {
    infile >> POINT_NUMBER >> PLAB >> PLAB_MIN >> PLAB_MAX >> SIG >> STA_ERR_UP >> STA_ERR_LOW >> SY_ER_UP_PCT >> SY_ER_LOW_PCT >> REFERENCE >> FLAG >> REF1 >> REF2 >> REF3;
    // std::cout << "POINT_NUMBER = " << POINT_NUMBER << std::endl;
    // std::cout << "PLAB = " << PLAB << std::endl;
    // std::cout << "PLAB_MIN = " << PLAB_MIN << std::endl;
    // std::cout << "PLAB_MAX = " << PLAB_MAX << std::endl;
    // std::cout << "SIG = " << SIG << std::endl;
    // std::cout << "STA_ERR_UP = " << STA_ERR_UP << std::endl;
    // std::cout << "STA_ERR_LOW = " << STA_ERR_LOW << std::endl;
    // std::cout << "SY_ER_UP_PCT = " << SY_ER_UP_PCT << std::endl;
    // std::cout << "SY_ER_LOW_PCT = " << SY_ER_LOW_PCT << std::endl;
    // std::cout << "REFERENCE = " << REFERENCE << std::endl;
    // std::cout << "FLAG = " << FLAG << std::endl;
    // std::cout << "REF1 = " << REF1 << std::endl;
    // std::cout << "REF2 = " << REF2 << std::endl;
    // std::cout << "REF3 = " << REF3 << std::endl;
    if (POINT_NUMBER != i + 1)
    {
      std::cout << "Something went wrong" << std::endl;
      std::cout << POINT_NUMBER << std::endl;
      std::cout << i << std::endl;
      exit(1);
    }
    tge->SetPoint(i, PLAB, SIG);
    tge->SetPointError(i,
                       0,
                       0,
                       sqrt(pow(STA_ERR_LOW, 2) + pow(SIG * SY_ER_LOW_PCT * 0.01, 2)),
                       sqrt(pow(STA_ERR_UP, 2) + pow(SIG * SY_ER_UP_PCT * 0.01, 2)));
    //  STA_ERR_LOW,
    //  STA_ERR_UP);
  }
  return tge;
}

void xsec()
{
  TGraphAsymmErrors *tge1 = readFromFile("rpp2018-pipp_total.dat");
  tge1->SetName("rpp2018-pipp_total.dat");
  tge1->SetTitle(";P_{lab} (GeV);#sigma (mb)");
  TGraphAsymmErrors *tge1elastic = readFromFile("rpp2018-pipp_elastic.dat");
  tge1elastic->SetName("rpp2018-pipp_elastic.dat");
  tge1elastic->SetTitle(";P_{lab} (GeV);#sigma (mb)");

  TGraphAsymmErrors *tge2 = readFromFile("rpp2018-pimp_total.dat");
  tge2->SetName("rpp2018-pimp_total.dat");
  tge2->SetTitle(";P_{lab} (GeV);#sigma (mb)");
  TGraphAsymmErrors *tge2elastic = readFromFile("rpp2018-pimp_elastic.dat");
  tge2elastic->SetName("rpp2018-pimp_elastic.dat");
  tge2elastic->SetTitle(";P_{lab} (GeV);#sigma (mb)");
  // cout << "SIG(4.6 GeV) = " << tge2->Eval(4.6) << " (MB)" << endl;
  // cout << "SIG(6.9 GeV) = " << tge2->Eval(6.9) << " (MB)" << endl;
  // cout << "SIG(9.2 GeV) = " << tge2->Eval(9.2) << " (MB)" << endl;
  // cout << "SIG(10.1 GeV) = " << tge2->Eval(10.1) << " (MB)" << endl;

  TGraphAsymmErrors *tge3 = readFromFile("rpp2018-kpp_total.dat");
  tge3->SetName("rpp2018-kpp_total.dat");
  tge3->SetTitle(";P_{lab} (GeV);#sigma (mb)");
  TGraphAsymmErrors *tge3elastic = readFromFile("rpp2018-kpp_elastic.dat");
  tge3elastic->SetName("rpp2018-kpp_elastic.dat");
  tge3elastic->SetTitle(";P_{lab} (GeV);#sigma (mb)");
  // cout << "SIG(4.6 GeV) = " << tge3->Eval(4.6) << " (MB)" << endl;
  // cout << "SIG(6.9 GeV) = " << tge3->Eval(6.9) << " (MB)" << endl;
  // cout << "SIG(9.2 GeV) = " << tge3->Eval(9.2) << " (MB)" << endl;
  // cout << "SIG(10.1 GeV) = " << tge3->Eval(10.1) << " (MB)" << endl;

  TCanvas *c1 = new TCanvas("c1", "c1 title", 800, 600);
  c1->SetLogx();
  // c1->SetLogy();
  tge1->Draw("APE");

  tge1->Fit("pol6", "QEMR", "", 4.0, 25.0);
  auto f1 = tge1->GetFunction("pol6");
  f1->SetLineColor(kRed);

  cout << "SIG(4.6 GeV) = " << f1->Eval(4.6) << " (MB)" << endl;
  cout << "SIG(6.9 GeV) = " << f1->Eval(6.9) << " (MB)" << endl;
  cout << "SIG(9.2 GeV) = " << f1->Eval(9.2) << " (MB)" << endl;
  cout << "SIG(10.1 GeV) = " << f1->Eval(10.1) << " (MB)" << endl;
  TGraph *tg1 = new TGraph(4);
  tg1->SetMarkerColor(kRed);
  tg1->SetPoint(0, 4.6, f1->Eval(4.6));
  tg1->SetPoint(1, 6.9, f1->Eval(6.9));
  tg1->SetPoint(2, 9.2, f1->Eval(9.2));
  tg1->SetPoint(3, 10.1, f1->Eval(10.1));

  tge1elastic->SetMarkerStyle(kOpenCircle);
  tge1elastic->Draw("PSAME");
  tg1->Draw("PSAME");
  TLegend *legend1 = new TLegend(0.5, 0.7, 0.88, 0.88);
  legend1->SetBorderSize(0); // no border
  legend1->SetFillStyle(0);
  legend1->SetFillColor(0); // legend background should be white
  legend1->SetTextFont(43);
  legend1->SetTextSize(22); // Increase entry font size!
  legend1->AddEntry(tge1, "Total collision cross-section", "p");
  legend1->AddEntry(tge1elastic, "Total elastic cross-section", "p");
  legend1->Draw();

  TCanvas *c2 = new TCanvas("c2", "c2 title", 800, 600);
  c2->SetLogx();
  // c2->SetLogy();
  tge2->Draw("APE");

  tge2->Fit("pol6", "QEMR", "", 4.0, 25.0);
  auto f2 = tge2->GetFunction("pol6");
  f2->SetLineColor(kRed);

  cout << "SIG(4.6 GeV) = " << f2->Eval(4.6) << " (MB)" << endl;
  cout << "SIG(6.9 GeV) = " << f2->Eval(6.9) << " (MB)" << endl;
  cout << "SIG(9.2 GeV) = " << f2->Eval(9.2) << " (MB)" << endl;
  cout << "SIG(10.1 GeV) = " << f2->Eval(10.1) << " (MB)" << endl;
  TGraph *tg2 = new TGraph(4);
  tg2->SetMarkerColor(kRed);
  tg2->SetPoint(0, 4.6, f2->Eval(4.6));
  tg2->SetPoint(1, 6.9, f2->Eval(6.9));
  tg2->SetPoint(2, 9.2, f2->Eval(9.2));
  tg2->SetPoint(3, 10.1, f2->Eval(10.1));

  tge2elastic->SetMarkerStyle(kOpenCircle);
  tge2elastic->Draw("PSAME");
  tg2->Draw("PSAME");
  TLegend *legend2 = new TLegend(0.5, 0.7, 0.88, 0.88);
  legend2->SetBorderSize(0); // no border
  legend2->SetFillStyle(0);
  legend2->SetFillColor(0); // legend background should be white
  legend2->SetTextFont(43);
  legend2->SetTextSize(22); // Increase entry font size!
  legend2->AddEntry(tge2, "Total collision cross-section", "p");
  legend2->AddEntry(tge2elastic, "Total elastic cross-section", "p");
  legend2->Draw();

  TCanvas *c3 = new TCanvas("c3", "c3 title", 800, 600);
  c3->SetLogx();
  // c3->SetLogy();
  tge3->Draw("APE");

  tge3->Fit("pol2", "QEMR", "", 4.0, 25.0);
  auto f3 = tge3->GetFunction("pol2");
  f3->SetLineColor(kRed);

  cout << "SIG(4.6 GeV) = " << f3->Eval(4.6) << " (MB)" << endl;
  cout << "SIG(6.9 GeV) = " << f3->Eval(6.9) << " (MB)" << endl;
  cout << "SIG(9.2 GeV) = " << f3->Eval(9.2) << " (MB)" << endl;
  cout << "SIG(10.1 GeV) = " << f3->Eval(10.1) << " (MB)" << endl;
  TGraph *tg3 = new TGraph(4);
  tg3->SetMarkerColor(kRed);
  tg3->SetPoint(0, 4.6, f3->Eval(4.6));
  tg3->SetPoint(1, 6.9, f3->Eval(6.9));
  tg3->SetPoint(2, 9.2, f3->Eval(9.2));
  tg3->SetPoint(3, 10.1, f3->Eval(10.1));

  tge3elastic->SetMarkerStyle(kOpenCircle);
  tge3elastic->Draw("PSAME");
  tg3->Draw("PSAME");
  TLegend *legend3 = new TLegend(0.5, 0.7, 0.88, 0.88);
  legend3->SetBorderSize(0); // no border
  legend3->SetFillStyle(0);
  legend3->SetFillColor(0); // legend background should be white
  legend3->SetTextFont(43);
  legend3->SetTextSize(22); // Increase entry font size!
  legend3->AddEntry(tge3, "Total collision cross-section", "p");
  legend3->AddEntry(tge3elastic, "Total elastic cross-section", "p");
  legend3->Draw();

  return 0;
}