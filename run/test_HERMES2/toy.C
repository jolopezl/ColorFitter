double nu[4] = { 14.37, 13.03, 12.33, 10.70 };
double lc[4] = { 7.0959, 5.4743, 4.08972, 1.97673 };
double qhat = 0.041; // +/- 0.011
double alpha_s = 0.3;
double Nc = 3;

void toy()
{
  auto h = Form("Bin\tLc\tLc2\tEloss\tLcrit");
  std::cout << h << std::endl;
  for (int i = 0; i < 4; ++i) {
    int bin = i + 1;
    double lc1 = lc[i];
    double lc2 = 2 * std::pow(lc[i], 2);
    double eloss = alpha_s * Nc * 0.25 * qhat * lc2 / 0.2;
    double lcrit = std::sqrt(nu[i] / qhat * 0.2);
    auto s = Form("%d\t%.3f\t%.3f\t%.3f\t%.3f", bin, lc1, lc2, eloss, lcrit);
    std::cout << s << std::endl;
  }
}