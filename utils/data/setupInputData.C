/*
Setups the data for fitting
*/

using namespace std;

const char* fit_function_nominal = "pol3";
const char* fit_function_lower = "pol2";

map<string, TGraphErrors*> data;
map<string, TGraphErrors*> dataRM;
map<string, TGraphErrors*> dataRMitp;
array<double, 4> A13{ pow(4.0026, 1. / 3.), pow(20.1797, 1. / 3.), pow(83.7980, 1. / 3.), pow(131.293, 1. / 3.) };
array<double, 4> zbins{ 0.32, 0.54, 0.75, 0.94 };
// arrat<double, 4> zbins{0.31,0.54,0.75,0.94};

void setupPtBroadening();
void setupMultiplicityRatio();
void setupMultiplicityRatioVsA();

void setupInputData()
{
  TFile* fout = TFile::Open("HERMES_InputData.root", "RECREATE");
  setupPtBroadening();
  setupMultiplicityRatio();
  setupMultiplicityRatioVsA();
  for (auto d : data) {
    d.second->Write();
  }
  for (auto d : dataRM) {
    d.second->Write();
  }
  for (auto d : dataRMitp) {
    if (d.second) {
      d.second->Write();
    }
  }
  fout->Write();
  fout->Close();
}

/*
Broadening results as a function of z for pi+:
   D<pt^{2}>_He^pi+(GeV^{2})  Value  Stat. error  Sys. uncertainty 
z-bin# 1  -0.0005  0.0021  0.0009
z-bin# 2  0.0004  0.0037  0.0021
z-bin# 3  -0.0073  0.0076  0.0076
z-bin# 4  -0.0094  0.0123  0.0110
   D<pt^{2}>_Ne^pi+(GeV^{2})  Value  Stat. error  Sys. uncertainty 
z-bin# 1  0.0064  0.0013  0.0008
z-bin# 2  0.0067  0.0022  0.0019
z-bin# 3  -0.0088  0.0044  0.0069
z-bin# 4  -0.0131  0.0073  0.0103
   D<pt^{2}>_Kr^pi+(GeV^{2})  Value  Stat. error  Sys. uncertainty 
z-bin# 1  0.0205  0.0015  0.0011
z-bin# 2  0.0228  0.0025  0.0023
z-bin# 3  0.0012  0.0051  0.0066
z-bin# 4  0.0021  0.0090  0.0095
   D<pt^{2}>_Xe^pi+(GeV^{2})  Value  Stat. error  Sys. uncertainty 
z-bin# 1  0.0269  0.0019  0.0013
z-bin# 2  0.0300  0.0033  0.0026
z-bin# 3  0.0071  0.0067  0.0069
z-bin# 4  -0.0021  0.0116  0.0082

   D<pt^{2}>_He^pi-(GeV^{2})  Value  Stat. error  Sys. uncertainty 
z-bin# 1  0.0017  0.0023  0.0009
z-bin# 2  0.0017  0.0041  0.0030
z-bin# 3  -0.0121  0.0085  0.0063
z-bin# 4  -0.0049  0.0141  0.0083

   D<pt^{2}>_Ne^pi-(GeV^{2})  Value  Stat. error  Sys. uncertainty 
z-bin# 1  0.0080  0.0014  0.0007
z-bin# 2  0.0098  0.0024  0.0028
z-bin# 3  -0.0055  0.0049  0.0057
z-bin# 4  -0.0041  0.0081  0.0074

   D<pt^{2}>_Kr^pi-(GeV^{2})  Value  Stat. error  Sys. uncertainty 
z-bin# 1  0.0183  0.0016  0.0010
z-bin# 2  0.0219  0.0027  0.0031
z-bin# 3  0.0073  0.0056  0.0059
z-bin# 4  -0.0045  0.0092  0.0069

   D<pt^{2}>_Xe^pi-(GeV^{2})  Value  Stat. error  Sys. uncertainty 
z-bin# 1  0.0251  0.0021  0.0012
z-bin# 2  0.0281  0.0035  0.0032
z-bin# 3  0.0104  0.0073  0.0059
z-bin# 4  -0.0053  0.0118  0.0068

  | D<pt^2>_He^K+(GeV^2)  Value | Stat. error | Sys. uncertainty 
z-bin# 1 | 0.0029 | 0.0064 | 0.0025
z-bin# 2 | -0.0048 | 0.0094 | 0.0041
z-bin# 3 | -0.0037 | 0.0190 | 0.0099
z-bin# 4 | -0.0287 | 0.0334 | 0.0394
  | D<pt^2>_Ne^K+(GeV^2)  Value | Stat. error | Sys. uncertainty 
z-bin# 1 | 0.0125 | 0.0037 | 0.0021
z-bin# 2 | 0.0076 | 0.0055 | 0.0031
z-bin# 3 | 0.0069 | 0.0108 | 0.0074
z-bin# 4 | -0.0155 | 0.0199 | 0.0312
  | D<pt^2>_Kr^K+(GeV^2)  Value | Stat. error | Sys. uncertainty 
z-bin# 1 | 0.0289 | 0.0043 | 0.0029
z-bin# 2 | 0.0256 | 0.0062 | 0.0038
z-bin# 3 | 0.0228 | 0.0123 | 0.0084
z-bin# 4 | -0.0273 | 0.0216 | 0.0279
  | D<pt^2>_Xe^K+(GeV^2)  Value | Stat. error | Sys. uncertainty 
z-bin# 1 | 0.0446 | 0.0058 | 0.0037
z-bin# 2 | 0.0369 | 0.0081 | 0.0038
z-bin# 3 | 0.0146 | 0.0157 | 0.0079
z-bin# 4 | 0.0122 | 0.0304 | 0.0440
*/
void setupPtBroadening()
{
  data["tg_pt_piplus_slice_0_zbin_0"] = new TGraphErrors(4);
  data["tg_pt_piplus_slice_0_zbin_1"] = new TGraphErrors(4);
  data["tg_pt_piplus_slice_0_zbin_2"] = new TGraphErrors(4);
  data["tg_pt_piplus_slice_0_zbin_3"] = new TGraphErrors(4);
  data["tg_pt_piminus_slice_0_zbin_0"] = new TGraphErrors(4);
  data["tg_pt_piminus_slice_0_zbin_1"] = new TGraphErrors(4);
  data["tg_pt_piminus_slice_0_zbin_2"] = new TGraphErrors(4);
  data["tg_pt_piminus_slice_0_zbin_3"] = new TGraphErrors(4);
  data["tg_pt_Kplus_slice_0_zbin_0"] = new TGraphErrors(4);
  data["tg_pt_Kplus_slice_0_zbin_1"] = new TGraphErrors(4);
  data["tg_pt_Kplus_slice_0_zbin_2"] = new TGraphErrors(4);
  data["tg_pt_Kplus_slice_0_zbin_3"] = new TGraphErrors(4);
  data["tg_pt_piplus_slice_0_zbin_0"]->SetName("tg_pt_piplus_slice_0_zbin_0");
  data["tg_pt_piplus_slice_0_zbin_1"]->SetName("tg_pt_piplus_slice_0_zbin_1");
  data["tg_pt_piplus_slice_0_zbin_2"]->SetName("tg_pt_piplus_slice_0_zbin_2");
  data["tg_pt_piplus_slice_0_zbin_3"]->SetName("tg_pt_piplus_slice_0_zbin_3");
  data["tg_pt_piminus_slice_0_zbin_0"]->SetName("tg_pt_piminus_slice_0_zbin_0");
  data["tg_pt_piminus_slice_0_zbin_1"]->SetName("tg_pt_piminus_slice_0_zbin_1");
  data["tg_pt_piminus_slice_0_zbin_2"]->SetName("tg_pt_piminus_slice_0_zbin_2");
  data["tg_pt_piminus_slice_0_zbin_3"]->SetName("tg_pt_piminus_slice_0_zbin_3");
  data["tg_pt_Kplus_slice_0_zbin_0"]->SetName("tg_pt_Kplus_slice_0_zbin_0");
  data["tg_pt_Kplus_slice_0_zbin_1"]->SetName("tg_pt_Kplus_slice_0_zbin_1");
  data["tg_pt_Kplus_slice_0_zbin_2"]->SetName("tg_pt_Kplus_slice_0_zbin_2");
  data["tg_pt_Kplus_slice_0_zbin_3"]->SetName("tg_pt_Kplus_slice_0_zbin_3");
  data["tg_pt_piplus_slice_0_zbin_0"]->SetTitle(";A^{1/3};#Delta#LTp_{T}^{2}#GT (GeV^{2})");
  data["tg_pt_piplus_slice_0_zbin_1"]->SetTitle(";A^{1/3};#Delta#LTp_{T}^{2}#GT (GeV^{2})");
  data["tg_pt_piplus_slice_0_zbin_2"]->SetTitle(";A^{1/3};#Delta#LTp_{T}^{2}#GT (GeV^{2})");
  data["tg_pt_piplus_slice_0_zbin_3"]->SetTitle(";A^{1/3};#Delta#LTp_{T}^{2}#GT (GeV^{2})");
  data["tg_pt_piminus_slice_0_zbin_0"]->SetTitle(";A^{1/3};#Delta#LTp_{T}^{2}#GT (GeV^{2})");
  data["tg_pt_piminus_slice_0_zbin_1"]->SetTitle(";A^{1/3};#Delta#LTp_{T}^{2}#GT (GeV^{2})");
  data["tg_pt_piminus_slice_0_zbin_2"]->SetTitle(";A^{1/3};#Delta#LTp_{T}^{2}#GT (GeV^{2})");
  data["tg_pt_piminus_slice_0_zbin_3"]->SetTitle(";A^{1/3};#Delta#LTp_{T}^{2}#GT (GeV^{2})");
  data["tg_pt_Kplus_slice_0_zbin_0"]->SetTitle(";A^{1/3};#Delta#LTp_{T}^{2}#GT (GeV^{2})");
  data["tg_pt_Kplus_slice_0_zbin_1"]->SetTitle(";A^{1/3};#Delta#LTp_{T}^{2}#GT (GeV^{2})");
  data["tg_pt_Kplus_slice_0_zbin_2"]->SetTitle(";A^{1/3};#Delta#LTp_{T}^{2}#GT (GeV^{2})");
  data["tg_pt_Kplus_slice_0_zbin_3"]->SetTitle(";A^{1/3};#Delta#LTp_{T}^{2}#GT (GeV^{2})");
  // pi+
  data["tg_pt_piplus_slice_0_zbin_0"]->SetPoint(0, A13[0], -0.0005);
  data["tg_pt_piplus_slice_0_zbin_1"]->SetPoint(0, A13[0], 0.0064);
  data["tg_pt_piplus_slice_0_zbin_2"]->SetPoint(0, A13[0], -0.0073);
  data["tg_pt_piplus_slice_0_zbin_3"]->SetPoint(0, A13[0], -0.0094);
  data["tg_pt_piplus_slice_0_zbin_0"]->SetPointError(0, 0, sqrt(pow(0.0021, 2) + pow(0.0009, 2)));
  data["tg_pt_piplus_slice_0_zbin_1"]->SetPointError(0, 0, sqrt(pow(0.0037, 2) + pow(0.0021, 2)));
  data["tg_pt_piplus_slice_0_zbin_2"]->SetPointError(0, 0, sqrt(pow(0.0076, 2) + pow(0.0076, 2)));
  data["tg_pt_piplus_slice_0_zbin_3"]->SetPointError(0, 0, sqrt(pow(0.0123, 2) + pow(0.0110, 2)));
  data["tg_pt_piplus_slice_0_zbin_0"]->SetPoint(1, A13[1], 0.0064);
  data["tg_pt_piplus_slice_0_zbin_1"]->SetPoint(1, A13[1], 0.0067);
  data["tg_pt_piplus_slice_0_zbin_2"]->SetPoint(1, A13[1], -0.0088);
  data["tg_pt_piplus_slice_0_zbin_3"]->SetPoint(1, A13[1], -0.0131);
  data["tg_pt_piplus_slice_0_zbin_0"]->SetPointError(1, 0, sqrt(pow(0.0013, 2) + pow(0.0008, 2)));
  data["tg_pt_piplus_slice_0_zbin_1"]->SetPointError(1, 0, sqrt(pow(0.0022, 2) + pow(0.0019, 2)));
  data["tg_pt_piplus_slice_0_zbin_2"]->SetPointError(1, 0, sqrt(pow(0.0044, 2) + pow(0.0069, 2)));
  data["tg_pt_piplus_slice_0_zbin_3"]->SetPointError(1, 0, sqrt(pow(0.0073, 2) + pow(0.0103, 2)));
  data["tg_pt_piplus_slice_0_zbin_0"]->SetPoint(2, A13[2], 0.0205);
  data["tg_pt_piplus_slice_0_zbin_1"]->SetPoint(2, A13[2], 0.0228);
  data["tg_pt_piplus_slice_0_zbin_2"]->SetPoint(2, A13[2], 0.0012);
  data["tg_pt_piplus_slice_0_zbin_3"]->SetPoint(2, A13[2], 0.0021);
  data["tg_pt_piplus_slice_0_zbin_0"]->SetPointError(2, 0, sqrt(pow(0.0015, 2) + pow(0.0011, 2)));
  data["tg_pt_piplus_slice_0_zbin_1"]->SetPointError(2, 0, sqrt(pow(0.0025, 2) + pow(0.0023, 2)));
  data["tg_pt_piplus_slice_0_zbin_2"]->SetPointError(2, 0, sqrt(pow(0.0051, 2) + pow(0.0066, 2)));
  data["tg_pt_piplus_slice_0_zbin_3"]->SetPointError(2, 0, sqrt(pow(0.0090, 2) + pow(0.0095, 2)));
  data["tg_pt_piplus_slice_0_zbin_0"]->SetPoint(3, A13[3], 0.0269);
  data["tg_pt_piplus_slice_0_zbin_1"]->SetPoint(3, A13[3], 0.0300);
  data["tg_pt_piplus_slice_0_zbin_2"]->SetPoint(3, A13[3], 0.0071);
  data["tg_pt_piplus_slice_0_zbin_3"]->SetPoint(3, A13[3], -0.0021);
  data["tg_pt_piplus_slice_0_zbin_0"]->SetPointError(3, 0, sqrt(pow(0.0019, 2) + pow(0.0013, 2)));
  data["tg_pt_piplus_slice_0_zbin_1"]->SetPointError(3, 0, sqrt(pow(0.0033, 2) + pow(0.0026, 2)));
  data["tg_pt_piplus_slice_0_zbin_2"]->SetPointError(3, 0, sqrt(pow(0.0067, 2) + pow(0.0069, 2)));
  data["tg_pt_piplus_slice_0_zbin_3"]->SetPointError(3, 0, sqrt(pow(0.0116, 2) + pow(0.0082, 2)));
  // pi-
  data["tg_pt_piminus_slice_0_zbin_0"]->SetPoint(0, A13[0], 0.0017);
  data["tg_pt_piminus_slice_0_zbin_1"]->SetPoint(0, A13[0], 0.0017);
  data["tg_pt_piminus_slice_0_zbin_2"]->SetPoint(0, A13[0], -0.0121);
  data["tg_pt_piminus_slice_0_zbin_3"]->SetPoint(0, A13[0], -0.0049);
  data["tg_pt_piminus_slice_0_zbin_0"]->SetPointError(0, 0, sqrt(pow(0.0023, 2) + pow(0.0009, 2)));
  data["tg_pt_piminus_slice_0_zbin_1"]->SetPointError(0, 0, sqrt(pow(0.0041, 2) + pow(0.0030, 2)));
  data["tg_pt_piminus_slice_0_zbin_2"]->SetPointError(0, 0, sqrt(pow(0.0085, 2) + pow(0.0063, 2)));
  data["tg_pt_piminus_slice_0_zbin_3"]->SetPointError(0, 0, sqrt(pow(0.0141, 2) + pow(0.0083, 2)));
  data["tg_pt_piminus_slice_0_zbin_0"]->SetPoint(1, A13[1], 0.0080);
  data["tg_pt_piminus_slice_0_zbin_1"]->SetPoint(1, A13[1], 0.0098);
  data["tg_pt_piminus_slice_0_zbin_2"]->SetPoint(1, A13[1], -0.0055);
  data["tg_pt_piminus_slice_0_zbin_3"]->SetPoint(1, A13[1], -0.0041);
  data["tg_pt_piminus_slice_0_zbin_0"]->SetPointError(1, 0, sqrt(pow(0.0014, 2) + pow(0.0007, 2)));
  data["tg_pt_piminus_slice_0_zbin_1"]->SetPointError(1, 0, sqrt(pow(0.0024, 2) + pow(0.0028, 2)));
  data["tg_pt_piminus_slice_0_zbin_2"]->SetPointError(1, 0, sqrt(pow(0.0049, 2) + pow(0.0057, 2)));
  data["tg_pt_piminus_slice_0_zbin_3"]->SetPointError(1, 0, sqrt(pow(0.0081, 2) + pow(0.0074, 2)));
  data["tg_pt_piminus_slice_0_zbin_0"]->SetPoint(2, A13[2], 0.0183);
  data["tg_pt_piminus_slice_0_zbin_1"]->SetPoint(2, A13[2], 0.0219);
  data["tg_pt_piminus_slice_0_zbin_2"]->SetPoint(2, A13[2], 0.0073);
  data["tg_pt_piminus_slice_0_zbin_3"]->SetPoint(2, A13[2], -0.0045);
  data["tg_pt_piminus_slice_0_zbin_0"]->SetPointError(2, 0, sqrt(pow(0.0016, 2) + pow(0.0010, 2)));
  data["tg_pt_piminus_slice_0_zbin_1"]->SetPointError(2, 0, sqrt(pow(0.0027, 2) + pow(0.0031, 2)));
  data["tg_pt_piminus_slice_0_zbin_2"]->SetPointError(2, 0, sqrt(pow(0.0056, 2) + pow(0.0059, 2)));
  data["tg_pt_piminus_slice_0_zbin_3"]->SetPointError(2, 0, sqrt(pow(0.0092, 2) + pow(0.0069, 2)));
  data["tg_pt_piminus_slice_0_zbin_0"]->SetPoint(3, A13[3], 0.0251);
  data["tg_pt_piminus_slice_0_zbin_1"]->SetPoint(3, A13[3], 0.0281);
  data["tg_pt_piminus_slice_0_zbin_2"]->SetPoint(3, A13[3], 0.0104);
  data["tg_pt_piminus_slice_0_zbin_3"]->SetPoint(3, A13[3], -0.0053);
  data["tg_pt_piminus_slice_0_zbin_0"]->SetPointError(3, 0, sqrt(pow(0.0021, 2) + pow(0.0012, 2)));
  data["tg_pt_piminus_slice_0_zbin_1"]->SetPointError(3, 0, sqrt(pow(0.0035, 2) + pow(0.0032, 2)));
  data["tg_pt_piminus_slice_0_zbin_2"]->SetPointError(3, 0, sqrt(pow(0.0073, 2) + pow(0.0059, 2)));
  data["tg_pt_piminus_slice_0_zbin_3"]->SetPointError(3, 0, sqrt(pow(0.0118, 2) + pow(0.0068, 2)));
  // K+
  data["tg_pt_Kplus_slice_0_zbin_0"]->SetPoint(0, A13[0], 0.0029);
  data["tg_pt_Kplus_slice_0_zbin_1"]->SetPoint(0, A13[0], -0.0048);
  data["tg_pt_Kplus_slice_0_zbin_2"]->SetPoint(0, A13[0], -0.0037);
  data["tg_pt_Kplus_slice_0_zbin_3"]->SetPoint(0, A13[0], -0.0287);
  data["tg_pt_Kplus_slice_0_zbin_0"]->SetPointError(0, 0, sqrt(pow(0.0064, 2) + pow(0.0025, 2)));
  data["tg_pt_Kplus_slice_0_zbin_1"]->SetPointError(0, 0, sqrt(pow(0.0094, 2) + pow(0.0041, 2)));
  data["tg_pt_Kplus_slice_0_zbin_2"]->SetPointError(0, 0, sqrt(pow(0.0190, 2) + pow(0.0099, 2)));
  data["tg_pt_Kplus_slice_0_zbin_3"]->SetPointError(0, 0, sqrt(pow(0.0334, 2) + pow(0.0394, 2)));
  data["tg_pt_Kplus_slice_0_zbin_0"]->SetPoint(1, A13[1], 0.0125);
  data["tg_pt_Kplus_slice_0_zbin_1"]->SetPoint(1, A13[1], 0.0076);
  data["tg_pt_Kplus_slice_0_zbin_2"]->SetPoint(1, A13[1], 0.0069);
  data["tg_pt_Kplus_slice_0_zbin_3"]->SetPoint(1, A13[1], -0.0155);
  data["tg_pt_Kplus_slice_0_zbin_0"]->SetPointError(1, 0, sqrt(pow(0.0037, 2) + pow(0.0021, 2)));
  data["tg_pt_Kplus_slice_0_zbin_1"]->SetPointError(1, 0, sqrt(pow(0.0055, 2) + pow(0.0031, 2)));
  data["tg_pt_Kplus_slice_0_zbin_2"]->SetPointError(1, 0, sqrt(pow(0.0108, 2) + pow(0.0074, 2)));
  data["tg_pt_Kplus_slice_0_zbin_3"]->SetPointError(1, 0, sqrt(pow(0.0199, 2) + pow(0.0312, 2)));
  data["tg_pt_Kplus_slice_0_zbin_0"]->SetPoint(2, A13[2], 0.0289);
  data["tg_pt_Kplus_slice_0_zbin_1"]->SetPoint(2, A13[2], 0.0256);
  data["tg_pt_Kplus_slice_0_zbin_2"]->SetPoint(2, A13[2], 0.0228);
  data["tg_pt_Kplus_slice_0_zbin_3"]->SetPoint(2, A13[2], -0.0273);
  data["tg_pt_Kplus_slice_0_zbin_0"]->SetPointError(2, 0, sqrt(pow(0.0043, 2) + pow(0.0029, 2)));
  data["tg_pt_Kplus_slice_0_zbin_1"]->SetPointError(2, 0, sqrt(pow(0.0062, 2) + pow(0.0038, 2)));
  data["tg_pt_Kplus_slice_0_zbin_2"]->SetPointError(2, 0, sqrt(pow(0.0123, 2) + pow(0.0084, 2)));
  data["tg_pt_Kplus_slice_0_zbin_3"]->SetPointError(2, 0, sqrt(pow(0.0216, 2) + pow(0.0279, 2)));
  data["tg_pt_Kplus_slice_0_zbin_0"]->SetPoint(3, A13[3], 0.0446);
  data["tg_pt_Kplus_slice_0_zbin_1"]->SetPoint(3, A13[3], 0.0369);
  data["tg_pt_Kplus_slice_0_zbin_2"]->SetPoint(3, A13[3], 0.0146);
  data["tg_pt_Kplus_slice_0_zbin_3"]->SetPoint(3, A13[3], 0.0122);
  data["tg_pt_Kplus_slice_0_zbin_0"]->SetPointError(3, 0, sqrt(pow(0.0058, 2) + pow(0.0037, 2)));
  data["tg_pt_Kplus_slice_0_zbin_1"]->SetPointError(3, 0, sqrt(pow(0.0081, 2) + pow(0.0038, 2)));
  data["tg_pt_Kplus_slice_0_zbin_2"]->SetPointError(3, 0, sqrt(pow(0.0157, 2) + pow(0.0079, 2)));
  data["tg_pt_Kplus_slice_0_zbin_3"]->SetPointError(3, 0, sqrt(pow(0.0304, 2) + pow(0.0440, 2)));
}

/*
   z      nu(GeV)   Q2(GeV2)   pt2(GeV2)     R        stat       syst
--------------------------------------------------------------------------
// HELIUM pi+
  0.16     18.28      2.50      0.101      0.943      0.006      0.029
  0.25     15.73      2.63      0.154      0.961      0.006      0.031
  0.35     14.53      2.64      0.196      0.950      0.007      0.029
  0.45     14.05      2.63      0.237      0.969      0.009      0.028
  0.55     13.74      2.63      0.266      0.959      0.011      0.028
  0.65     13.37      2.58      0.277      0.992      0.014      0.029
  0.75     12.57      2.43      0.249      0.975      0.016      0.029
  0.85     11.76      2.36      0.205      1.020      0.021      0.039
  0.95     10.46      2.28      0.166      0.917      0.024      0.032
// NEON pi+
  0.16     18.26      2.50      0.101      0.913      0.004      0.030
  0.25     15.77      2.63      0.156      0.902      0.004      0.030
  0.35     14.61      2.66      0.204      0.888      0.004      0.028
  0.45     14.10      2.65      0.241      0.885      0.006      0.027
  0.55     13.81      2.59      0.274      0.894      0.007      0.026
  0.65     13.43      2.55      0.277      0.878      0.008      0.026
  0.75     12.67      2.47      0.251      0.883      0.010      0.027
  0.85     11.75      2.34      0.201      0.856      0.013      0.036
  0.95     10.67      2.30      0.169      0.789      0.015      0.029
// KRYPTON pi+
  0.16     18.32      2.47      0.104      0.872      0.004      0.030
  0.25     15.89      2.65      0.163      0.814      0.003      0.028
  0.34     14.76      2.69      0.217      0.782      0.004      0.026
  0.45     14.31      2.66      0.260      0.759      0.005      0.024
  0.55     13.98      2.62      0.287      0.739      0.006      0.022
  0.65     13.69      2.54      0.296      0.721      0.007      0.022
  0.75     12.83      2.45      0.260      0.674      0.009      0.022
  0.85     11.84      2.31      0.210      0.625      0.010      0.029
  0.95     10.71      2.33      0.170      0.542      0.012      0.022
// XENON pi+
  0.16     18.33      2.48      0.105      0.838      0.005      0.029
  0.25     15.96      2.63      0.167      0.768      0.004      0.028
  0.35     14.83      2.67      0.221      0.729      0.005      0.025
  0.44     14.37      2.67      0.263      0.701      0.006      0.022
  0.55     14.02      2.63      0.294      0.679      0.007      0.020
  0.65     13.69      2.57      0.301      0.659      0.009      0.020
  0.75     12.76      2.46      0.259      0.616      0.010      0.020
  0.84     11.89      2.37      0.215      0.574      0.012      0.028
  0.95     10.88      2.39      0.181      0.489      0.014      0.02
   z      nu(GeV)   Q2(GeV2)   pt2(GeV2)     R        stat       syst
--------------------------------------------------------------------------
// HELIUM pi-
  0.16     18.34      2.44      0.101      0.942      0.007      0.035
  0.25     15.91      2.60      0.159      0.946      0.006      0.036
  0.34     14.64      2.61      0.204      0.955      0.008      0.032
  0.44     14.11      2.57      0.239      0.960      0.010      0.030
  0.55     13.67      2.51      0.257      0.972      0.013      0.030
  0.64     13.20      2.43      0.253      0.961      0.015      0.030
  0.75     12.48      2.29      0.216      0.979      0.019      0.035
  0.85     11.68      2.15      0.165      0.984      0.023      0.054
  0.96     10.58      2.22      0.130      0.899      0.028      0.041
// NEON pi-
  0.16     18.39      2.45      0.102      0.898      0.004      0.036
  0.25     15.97      2.58      0.161      0.889      0.004      0.036
  0.34     14.77      2.61      0.210      0.881      0.005      0.033
  0.45     14.19      2.58      0.247      0.883      0.006      0.029
  0.55     13.78      2.51      0.267      0.879      0.008      0.028
  0.65     13.38      2.43      0.262      0.879      0.010      0.029
  0.75     12.57      2.29      0.218      0.876      0.012      0.034
  0.85     11.78      2.14      0.167      0.877      0.015      0.056
  0.95     10.68      2.16      0.137      0.787      0.017      0.041
// KRYPTON pi-
  0.16     18.40      2.45      0.103      0.855      0.004      0.038
  0.25     16.03      2.59      0.166      0.804      0.004      0.037
  0.34     14.84      2.62      0.221      0.774      0.004      0.031
  0.44     14.33      2.61      0.260      0.745      0.006      0.026
  0.55     13.94      2.54      0.280      0.742      0.007      0.024
  0.65     13.57      2.44      0.273      0.726      0.009      0.025
  0.75     12.82      2.31      0.228      0.697      0.010      0.029
  0.85     11.84      2.18      0.169      0.681      0.012      0.050
  0.95     10.78      2.16      0.137      0.576      0.014      0.034
// XENON pi-
  0.16     18.42      2.45      0.104      0.836      0.005      0.038
  0.25     16.09      2.60      0.169      0.765      0.005      0.037
  0.34     14.89      2.63      0.225      0.726      0.005      0.030
  0.44     14.34      2.58      0.267      0.706      0.007      0.025
  0.55     13.95      2.54      0.277      0.693      0.009      0.024
  0.64     13.53      2.44      0.278      0.672      0.010      0.024
  0.75     12.74      2.32      0.228      0.634      0.012      0.029
  0.85     11.83      2.20      0.175      0.597      0.015      0.048
  0.95     10.79      2.21      0.138      0.536      0.017      0.034
   z      nu(GeV)   Q2(GeV2)   pt2(GeV2)     R        stat       syst
--------------------------------------------------------------------------
// HELIUM K+
  0.16     18.42      2.42      0.117      0.962      0.015      0.028
  0.25     15.24      2.63      0.168      0.953      0.013      0.027
  0.35     14.11      2.67      0.206      0.978      0.015      0.028
  0.45     13.84      2.75      0.247      0.956      0.018      0.027
  0.55     13.77      2.74      0.273      0.945      0.021      0.027
  0.65     13.66      2.69      0.326      0.950      0.026      0.027
  0.75     12.81      2.67      0.304      0.947      0.033      0.027
  0.84     11.92      2.59      0.278      0.984      0.044      0.028
  0.95     11.18      2.54      0.238      0.936      0.064      0.027 
// NEON K+
  0.16     18.48      2.39      0.120      0.970      0.010      0.028
  0.25     15.30      2.64      0.175      0.961      0.009      0.027
  0.35     14.12      2.70      0.217      0.961      0.010      0.027
  0.45     13.81      2.72      0.255      0.923      0.012      0.026
  0.55     13.68      2.69      0.290      0.902      0.014      0.026
  0.64     13.59      2.73      0.330      0.925      0.017      0.026
  0.75     12.78      2.71      0.323      0.886      0.021      0.025
  0.84     12.01      2.61      0.287      0.858      0.027      0.025
  0.94     10.94      2.48      0.243      0.722      0.036      0.021
// KRYPTON K+
  0.16     18.53      2.40      0.123      1.047      0.011      0.033
  0.25     15.46      2.61      0.184      0.985      0.009      0.030
  0.35     14.34      2.69      0.236      0.906      0.010      0.026
  0.45     13.97      2.73      0.276      0.848      0.011      0.024
  0.55     13.81      2.72      0.310      0.822      0.013      0.023
  0.64     13.68      2.77      0.344      0.787      0.015      0.022
  0.75     12.83      2.67      0.332      0.761      0.019      0.022
  0.84     11.96      2.63      0.286      0.687      0.024      0.020
  0.95     11.16      2.51      0.234      0.643      0.034      0.019
// XENON K+
  0.16     18.55      2.44      0.126      1.023      0.014      0.034
  0.25     15.56      2.60      0.191      0.958      0.012      0.029
  0.35     14.45      2.68      0.244      0.874      0.012      0.025
  0.44     14.02      2.71      0.287      0.808      0.014      0.023
  0.55     13.91      2.69      0.319      0.788      0.016      0.022
  0.64     13.62      2.68      0.350      0.770      0.020      0.022
  0.74     12.71      2.69      0.321      0.677      0.023      0.020
  0.84     12.20      2.61      0.314      0.633      0.029      0.018
  0.95     10.93      2.54      0.238      0.599      0.042      0.017
*/
void setupMultiplicityRatio()
{
  dataRM["tg_RM_piplus_Helium"] = new TGraphErrors(9);
  dataRM["tg_RM_piplus_Neon"] = new TGraphErrors(9);
  dataRM["tg_RM_piplus_Krypton"] = new TGraphErrors(9);
  dataRM["tg_RM_piplus_Xenon"] = new TGraphErrors(9);
  dataRM["tg_RM_piminus_Helium"] = new TGraphErrors(9);
  dataRM["tg_RM_piminus_Neon"] = new TGraphErrors(9);
  dataRM["tg_RM_piminus_Krypton"] = new TGraphErrors(9);
  dataRM["tg_RM_piminus_Xenon"] = new TGraphErrors(9);
  dataRM["tg_RM_Kplus_Helium"] = new TGraphErrors(9);
  dataRM["tg_RM_Kplus_Neon"] = new TGraphErrors(9);
  dataRM["tg_RM_Kplus_Krypton"] = new TGraphErrors(9);
  dataRM["tg_RM_Kplus_Xenon"] = new TGraphErrors(9);
  dataRM["tg_RM_piplus_Helium"]->SetName("tg_RM_piplus_Helium");
  dataRM["tg_RM_piplus_Neon"]->SetName("tg_RM_piplus_Neon");
  dataRM["tg_RM_piplus_Krypton"]->SetName("tg_RM_piplus_Krypton");
  dataRM["tg_RM_piplus_Xenon"]->SetName("tg_RM_piplus_Xenon");
  dataRM["tg_RM_piminus_Helium"]->SetName("tg_RM_piminus_Helium");
  dataRM["tg_RM_piminus_Neon"]->SetName("tg_RM_piminus_Neon");
  dataRM["tg_RM_piminus_Krypton"]->SetName("tg_RM_piminus_Krypton");
  dataRM["tg_RM_piminus_Xenon"]->SetName("tg_RM_piminus_Xenon");
  dataRM["tg_RM_Kplus_Helium"]->SetName("tg_RM_Kplus_Helium");
  dataRM["tg_RM_Kplus_Neon"]->SetName("tg_RM_Kplus_Neon");
  dataRM["tg_RM_Kplus_Krypton"]->SetName("tg_RM_Kplus_Krypton");
  dataRM["tg_RM_Kplus_Xenon"]->SetName("tg_RM_Kplus_Xenon");
  dataRM["tg_RM_piplus_Helium"]->SetTitle(";z_{h};R_{M}");
  dataRM["tg_RM_piplus_Neon"]->SetTitle(";z_{h};R_{M}");
  dataRM["tg_RM_piplus_Krypton"]->SetTitle(";z_{h};R_{M}");
  dataRM["tg_RM_piplus_Xenon"]->SetTitle(";z_{h};R_{M}");
  dataRM["tg_RM_piminus_Helium"]->SetTitle(";z_{h};R_{M}");
  dataRM["tg_RM_piminus_Neon"]->SetTitle(";z_{h};R_{M}");
  dataRM["tg_RM_piminus_Krypton"]->SetTitle(";z_{h};R_{M}");
  dataRM["tg_RM_piminus_Xenon"]->SetTitle(";z_{h};R_{M}");
  dataRM["tg_RM_Kplus_Helium"]->SetTitle(";z_{h};R_{M}");
  dataRM["tg_RM_Kplus_Neon"]->SetTitle(";z_{h};R_{M}");
  dataRM["tg_RM_Kplus_Krypton"]->SetTitle(";z_{h};R_{M}");
  dataRM["tg_RM_Kplus_Xenon"]->SetTitle(";z_{h};R_{M}");
  dataRM["tg_RM_piplus_Helium"]->SetPoint(0, 0.16, 0.943);
  dataRM["tg_RM_piplus_Helium"]->SetPoint(1, 0.25, 0.961);
  dataRM["tg_RM_piplus_Helium"]->SetPoint(2, 0.35, 0.950);
  dataRM["tg_RM_piplus_Helium"]->SetPoint(3, 0.45, 0.969);
  dataRM["tg_RM_piplus_Helium"]->SetPoint(4, 0.55, 0.959);
  dataRM["tg_RM_piplus_Helium"]->SetPoint(5, 0.65, 0.992);
  dataRM["tg_RM_piplus_Helium"]->SetPoint(6, 0.75, 0.975);
  dataRM["tg_RM_piplus_Helium"]->SetPoint(7, 0.85, 1.020);
  dataRM["tg_RM_piplus_Helium"]->SetPoint(8, 0.95, 0.917);
  dataRM["tg_RM_piplus_Helium"]->SetPointError(0, 0, sqrt(pow(0.006, 2) + pow(0.029, 2)));
  dataRM["tg_RM_piplus_Helium"]->SetPointError(1, 0, sqrt(pow(0.006, 2) + pow(0.031, 2)));
  dataRM["tg_RM_piplus_Helium"]->SetPointError(2, 0, sqrt(pow(0.007, 2) + pow(0.029, 2)));
  dataRM["tg_RM_piplus_Helium"]->SetPointError(3, 0, sqrt(pow(0.009, 2) + pow(0.028, 2)));
  dataRM["tg_RM_piplus_Helium"]->SetPointError(4, 0, sqrt(pow(0.011, 2) + pow(0.028, 2)));
  dataRM["tg_RM_piplus_Helium"]->SetPointError(5, 0, sqrt(pow(0.014, 2) + pow(0.029, 2)));
  dataRM["tg_RM_piplus_Helium"]->SetPointError(6, 0, sqrt(pow(0.016, 2) + pow(0.029, 2)));
  dataRM["tg_RM_piplus_Helium"]->SetPointError(7, 0, sqrt(pow(0.021, 2) + pow(0.039, 2)));
  dataRM["tg_RM_piplus_Helium"]->SetPointError(8, 0, sqrt(pow(0.024, 2) + pow(0.032, 2)));
  dataRM["tg_RM_piplus_Neon"]->SetPoint(0, 0.16, 0.913);
  dataRM["tg_RM_piplus_Neon"]->SetPoint(1, 0.25, 0.902);
  dataRM["tg_RM_piplus_Neon"]->SetPoint(2, 0.35, 0.888);
  dataRM["tg_RM_piplus_Neon"]->SetPoint(3, 0.45, 0.885);
  dataRM["tg_RM_piplus_Neon"]->SetPoint(4, 0.55, 0.894);
  dataRM["tg_RM_piplus_Neon"]->SetPoint(5, 0.65, 0.878);
  dataRM["tg_RM_piplus_Neon"]->SetPoint(6, 0.75, 0.883);
  dataRM["tg_RM_piplus_Neon"]->SetPoint(7, 0.85, 0.856);
  dataRM["tg_RM_piplus_Neon"]->SetPoint(8, 0.95, 0.789);
  dataRM["tg_RM_piplus_Neon"]->SetPointError(0, 0, sqrt(pow(0.004, 2) + pow(0.030, 2)));
  dataRM["tg_RM_piplus_Neon"]->SetPointError(1, 0, sqrt(pow(0.004, 2) + pow(0.030, 2)));
  dataRM["tg_RM_piplus_Neon"]->SetPointError(2, 0, sqrt(pow(0.004, 2) + pow(0.028, 2)));
  dataRM["tg_RM_piplus_Neon"]->SetPointError(3, 0, sqrt(pow(0.006, 2) + pow(0.027, 2)));
  dataRM["tg_RM_piplus_Neon"]->SetPointError(4, 0, sqrt(pow(0.007, 2) + pow(0.026, 2)));
  dataRM["tg_RM_piplus_Neon"]->SetPointError(5, 0, sqrt(pow(0.008, 2) + pow(0.026, 2)));
  dataRM["tg_RM_piplus_Neon"]->SetPointError(6, 0, sqrt(pow(0.010, 2) + pow(0.027, 2)));
  dataRM["tg_RM_piplus_Neon"]->SetPointError(7, 0, sqrt(pow(0.013, 2) + pow(0.036, 2)));
  dataRM["tg_RM_piplus_Neon"]->SetPointError(8, 0, sqrt(pow(0.015, 2) + pow(0.029, 2)));
  dataRM["tg_RM_piplus_Krypton"]->SetPoint(0, 0.16, 0.855);
  dataRM["tg_RM_piplus_Krypton"]->SetPoint(1, 0.25, 0.804);
  dataRM["tg_RM_piplus_Krypton"]->SetPoint(2, 0.34, 0.774);
  dataRM["tg_RM_piplus_Krypton"]->SetPoint(3, 0.45, 0.745);
  dataRM["tg_RM_piplus_Krypton"]->SetPoint(4, 0.55, 0.742);
  dataRM["tg_RM_piplus_Krypton"]->SetPoint(5, 0.65, 0.726);
  dataRM["tg_RM_piplus_Krypton"]->SetPoint(6, 0.75, 0.697);
  dataRM["tg_RM_piplus_Krypton"]->SetPoint(7, 0.85, 0.681);
  dataRM["tg_RM_piplus_Krypton"]->SetPoint(8, 0.95, 0.576);
  dataRM["tg_RM_piplus_Krypton"]->SetPointError(0, 0, sqrt(pow(0.004, 2) + pow(0.038, 2)));
  dataRM["tg_RM_piplus_Krypton"]->SetPointError(1, 0, sqrt(pow(0.004, 2) + pow(0.037, 2)));
  dataRM["tg_RM_piplus_Krypton"]->SetPointError(2, 0, sqrt(pow(0.004, 2) + pow(0.031, 2)));
  dataRM["tg_RM_piplus_Krypton"]->SetPointError(3, 0, sqrt(pow(0.006, 2) + pow(0.026, 2)));
  dataRM["tg_RM_piplus_Krypton"]->SetPointError(4, 0, sqrt(pow(0.007, 2) + pow(0.024, 2)));
  dataRM["tg_RM_piplus_Krypton"]->SetPointError(5, 0, sqrt(pow(0.009, 2) + pow(0.025, 2)));
  dataRM["tg_RM_piplus_Krypton"]->SetPointError(6, 0, sqrt(pow(0.010, 2) + pow(0.029, 2)));
  dataRM["tg_RM_piplus_Krypton"]->SetPointError(7, 0, sqrt(pow(0.012, 2) + pow(0.050, 2)));
  dataRM["tg_RM_piplus_Krypton"]->SetPointError(8, 0, sqrt(pow(0.014, 2) + pow(0.034, 2)));
  dataRM["tg_RM_piplus_Xenon"]->SetPoint(0, 0.16, 0.838);
  dataRM["tg_RM_piplus_Xenon"]->SetPoint(1, 0.25, 0.768);
  dataRM["tg_RM_piplus_Xenon"]->SetPoint(2, 0.35, 0.729);
  dataRM["tg_RM_piplus_Xenon"]->SetPoint(3, 0.44, 0.701);
  dataRM["tg_RM_piplus_Xenon"]->SetPoint(4, 0.55, 0.679);
  dataRM["tg_RM_piplus_Xenon"]->SetPoint(5, 0.65, 0.659);
  dataRM["tg_RM_piplus_Xenon"]->SetPoint(6, 0.75, 0.616);
  dataRM["tg_RM_piplus_Xenon"]->SetPoint(7, 0.84, 0.574);
  dataRM["tg_RM_piplus_Xenon"]->SetPoint(8, 0.95, 0.489);
  dataRM["tg_RM_piplus_Xenon"]->SetPointError(0, 0, sqrt(pow(0.005, 2) + pow(0.029, 2)));
  dataRM["tg_RM_piplus_Xenon"]->SetPointError(1, 0, sqrt(pow(0.004, 2) + pow(0.028, 2)));
  dataRM["tg_RM_piplus_Xenon"]->SetPointError(2, 0, sqrt(pow(0.005, 2) + pow(0.025, 2)));
  dataRM["tg_RM_piplus_Xenon"]->SetPointError(3, 0, sqrt(pow(0.006, 2) + pow(0.022, 2)));
  dataRM["tg_RM_piplus_Xenon"]->SetPointError(4, 0, sqrt(pow(0.007, 2) + pow(0.020, 2)));
  dataRM["tg_RM_piplus_Xenon"]->SetPointError(5, 0, sqrt(pow(0.009, 2) + pow(0.020, 2)));
  dataRM["tg_RM_piplus_Xenon"]->SetPointError(6, 0, sqrt(pow(0.010, 2) + pow(0.020, 2)));
  dataRM["tg_RM_piplus_Xenon"]->SetPointError(7, 0, sqrt(pow(0.012, 2) + pow(0.028, 2)));
  dataRM["tg_RM_piplus_Xenon"]->SetPointError(8, 0, sqrt(pow(0.014, 2) + pow(0.020, 2)));
  dataRM["tg_RM_piminus_Helium"]->SetPoint(0, 0.16, 0.942);
  dataRM["tg_RM_piminus_Helium"]->SetPoint(1, 0.25, 0.946);
  dataRM["tg_RM_piminus_Helium"]->SetPoint(2, 0.34, 0.955);
  dataRM["tg_RM_piminus_Helium"]->SetPoint(3, 0.44, 0.960);
  dataRM["tg_RM_piminus_Helium"]->SetPoint(4, 0.55, 0.972);
  dataRM["tg_RM_piminus_Helium"]->SetPoint(5, 0.64, 0.961);
  dataRM["tg_RM_piminus_Helium"]->SetPoint(6, 0.75, 0.979);
  dataRM["tg_RM_piminus_Helium"]->SetPoint(7, 0.85, 0.984);
  dataRM["tg_RM_piminus_Helium"]->SetPoint(8, 0.96, 0.899);
  dataRM["tg_RM_piminus_Helium"]->SetPointError(0, 0, sqrt(pow(0.007, 2) + pow(0.035, 2)));
  dataRM["tg_RM_piminus_Helium"]->SetPointError(1, 0, sqrt(pow(0.006, 2) + pow(0.036, 2)));
  dataRM["tg_RM_piminus_Helium"]->SetPointError(2, 0, sqrt(pow(0.008, 2) + pow(0.032, 2)));
  dataRM["tg_RM_piminus_Helium"]->SetPointError(3, 0, sqrt(pow(0.010, 2) + pow(0.030, 2)));
  dataRM["tg_RM_piminus_Helium"]->SetPointError(4, 0, sqrt(pow(0.013, 2) + pow(0.030, 2)));
  dataRM["tg_RM_piminus_Helium"]->SetPointError(5, 0, sqrt(pow(0.015, 2) + pow(0.030, 2)));
  dataRM["tg_RM_piminus_Helium"]->SetPointError(6, 0, sqrt(pow(0.019, 2) + pow(0.035, 2)));
  dataRM["tg_RM_piminus_Helium"]->SetPointError(7, 0, sqrt(pow(0.023, 2) + pow(0.054, 2)));
  dataRM["tg_RM_piminus_Helium"]->SetPointError(8, 0, sqrt(pow(0.028, 2) + pow(0.041, 2)));
  dataRM["tg_RM_piminus_Neon"]->SetPoint(0, 0.16, 0.898);
  dataRM["tg_RM_piminus_Neon"]->SetPoint(1, 0.25, 0.889);
  dataRM["tg_RM_piminus_Neon"]->SetPoint(2, 0.34, 0.881);
  dataRM["tg_RM_piminus_Neon"]->SetPoint(3, 0.45, 0.883);
  dataRM["tg_RM_piminus_Neon"]->SetPoint(4, 0.55, 0.879);
  dataRM["tg_RM_piminus_Neon"]->SetPoint(5, 0.65, 0.879);
  dataRM["tg_RM_piminus_Neon"]->SetPoint(6, 0.75, 0.876);
  dataRM["tg_RM_piminus_Neon"]->SetPoint(7, 0.85, 0.877);
  dataRM["tg_RM_piminus_Neon"]->SetPoint(8, 0.95, 0.787);
  dataRM["tg_RM_piminus_Neon"]->SetPointError(0, 0, sqrt(pow(0.004, 2) + pow(0.036, 2)));
  dataRM["tg_RM_piminus_Neon"]->SetPointError(1, 0, sqrt(pow(0.004, 2) + pow(0.036, 2)));
  dataRM["tg_RM_piminus_Neon"]->SetPointError(2, 0, sqrt(pow(0.005, 2) + pow(0.033, 2)));
  dataRM["tg_RM_piminus_Neon"]->SetPointError(3, 0, sqrt(pow(0.006, 2) + pow(0.029, 2)));
  dataRM["tg_RM_piminus_Neon"]->SetPointError(4, 0, sqrt(pow(0.008, 2) + pow(0.028, 2)));
  dataRM["tg_RM_piminus_Neon"]->SetPointError(5, 0, sqrt(pow(0.010, 2) + pow(0.029, 2)));
  dataRM["tg_RM_piminus_Neon"]->SetPointError(6, 0, sqrt(pow(0.012, 2) + pow(0.034, 2)));
  dataRM["tg_RM_piminus_Neon"]->SetPointError(7, 0, sqrt(pow(0.015, 2) + pow(0.056, 2)));
  dataRM["tg_RM_piminus_Neon"]->SetPointError(8, 0, sqrt(pow(0.017, 2) + pow(0.041, 2)));
  dataRM["tg_RM_piminus_Krypton"]->SetPoint(0, 0.16, 0.855);
  dataRM["tg_RM_piminus_Krypton"]->SetPoint(1, 0.25, 0.804);
  dataRM["tg_RM_piminus_Krypton"]->SetPoint(2, 0.34, 0.774);
  dataRM["tg_RM_piminus_Krypton"]->SetPoint(3, 0.44, 0.745);
  dataRM["tg_RM_piminus_Krypton"]->SetPoint(4, 0.55, 0.742);
  dataRM["tg_RM_piminus_Krypton"]->SetPoint(5, 0.65, 0.726);
  dataRM["tg_RM_piminus_Krypton"]->SetPoint(6, 0.75, 0.697);
  dataRM["tg_RM_piminus_Krypton"]->SetPoint(7, 0.85, 0.681);
  dataRM["tg_RM_piminus_Krypton"]->SetPoint(8, 0.95, 0.576);
  dataRM["tg_RM_piminus_Krypton"]->SetPointError(0, 0, sqrt(pow(0.004, 2) + pow(0.038, 2)));
  dataRM["tg_RM_piminus_Krypton"]->SetPointError(1, 0, sqrt(pow(0.004, 2) + pow(0.037, 2)));
  dataRM["tg_RM_piminus_Krypton"]->SetPointError(2, 0, sqrt(pow(0.004, 2) + pow(0.031, 2)));
  dataRM["tg_RM_piminus_Krypton"]->SetPointError(3, 0, sqrt(pow(0.006, 2) + pow(0.026, 2)));
  dataRM["tg_RM_piminus_Krypton"]->SetPointError(4, 0, sqrt(pow(0.007, 2) + pow(0.024, 2)));
  dataRM["tg_RM_piminus_Krypton"]->SetPointError(5, 0, sqrt(pow(0.009, 2) + pow(0.025, 2)));
  dataRM["tg_RM_piminus_Krypton"]->SetPointError(6, 0, sqrt(pow(0.010, 2) + pow(0.029, 2)));
  dataRM["tg_RM_piminus_Krypton"]->SetPointError(7, 0, sqrt(pow(0.012, 2) + pow(0.050, 2)));
  dataRM["tg_RM_piminus_Krypton"]->SetPointError(8, 0, sqrt(pow(0.014, 2) + pow(0.034, 2)));
  dataRM["tg_RM_piminus_Xenon"]->SetPoint(0, 0.16, 0.836);
  dataRM["tg_RM_piminus_Xenon"]->SetPoint(1, 0.25, 0.765);
  dataRM["tg_RM_piminus_Xenon"]->SetPoint(2, 0.34, 0.726);
  dataRM["tg_RM_piminus_Xenon"]->SetPoint(3, 0.44, 0.706);
  dataRM["tg_RM_piminus_Xenon"]->SetPoint(4, 0.55, 0.693);
  dataRM["tg_RM_piminus_Xenon"]->SetPoint(5, 0.64, 0.672);
  dataRM["tg_RM_piminus_Xenon"]->SetPoint(6, 0.75, 0.634);
  dataRM["tg_RM_piminus_Xenon"]->SetPoint(7, 0.85, 0.597);
  dataRM["tg_RM_piminus_Xenon"]->SetPoint(8, 0.95, 0.536);
  dataRM["tg_RM_piminus_Xenon"]->SetPointError(0, 0, sqrt(pow(0.005, 2) + pow(0.038, 2)));
  dataRM["tg_RM_piminus_Xenon"]->SetPointError(1, 0, sqrt(pow(0.005, 2) + pow(0.037, 2)));
  dataRM["tg_RM_piminus_Xenon"]->SetPointError(2, 0, sqrt(pow(0.005, 2) + pow(0.030, 2)));
  dataRM["tg_RM_piminus_Xenon"]->SetPointError(3, 0, sqrt(pow(0.007, 2) + pow(0.025, 2)));
  dataRM["tg_RM_piminus_Xenon"]->SetPointError(4, 0, sqrt(pow(0.009, 2) + pow(0.024, 2)));
  dataRM["tg_RM_piminus_Xenon"]->SetPointError(5, 0, sqrt(pow(0.010, 2) + pow(0.024, 2)));
  dataRM["tg_RM_piminus_Xenon"]->SetPointError(6, 0, sqrt(pow(0.012, 2) + pow(0.029, 2)));
  dataRM["tg_RM_piminus_Xenon"]->SetPointError(7, 0, sqrt(pow(0.015, 2) + pow(0.048, 2)));
  dataRM["tg_RM_piminus_Xenon"]->SetPointError(8, 0, sqrt(pow(0.017, 2) + pow(0.034, 2)));

  // K+
  dataRM["tg_RM_Kplus_Helium"]->SetPoint(0, 0.16, 0.962);
  dataRM["tg_RM_Kplus_Helium"]->SetPoint(1, 0.25, 0.953);
  dataRM["tg_RM_Kplus_Helium"]->SetPoint(2, 0.35, 0.978);
  dataRM["tg_RM_Kplus_Helium"]->SetPoint(3, 0.45, 0.956);
  dataRM["tg_RM_Kplus_Helium"]->SetPoint(4, 0.55, 0.945);
  dataRM["tg_RM_Kplus_Helium"]->SetPoint(5, 0.65, 0.950);
  dataRM["tg_RM_Kplus_Helium"]->SetPoint(6, 0.75, 0.947);
  dataRM["tg_RM_Kplus_Helium"]->SetPoint(7, 0.84, 0.984);
  dataRM["tg_RM_Kplus_Helium"]->SetPoint(8, 0.95, 0.936);
  dataRM["tg_RM_Kplus_Helium"]->SetPointError(0, 0, sqrt(pow(0.015, 2) + pow(0.028, 2)));
  dataRM["tg_RM_Kplus_Helium"]->SetPointError(1, 0, sqrt(pow(0.013, 2) + pow(0.027, 2)));
  dataRM["tg_RM_Kplus_Helium"]->SetPointError(2, 0, sqrt(pow(0.015, 2) + pow(0.028, 2)));
  dataRM["tg_RM_Kplus_Helium"]->SetPointError(3, 0, sqrt(pow(0.018, 2) + pow(0.027, 2)));
  dataRM["tg_RM_Kplus_Helium"]->SetPointError(4, 0, sqrt(pow(0.021, 2) + pow(0.027, 2)));
  dataRM["tg_RM_Kplus_Helium"]->SetPointError(5, 0, sqrt(pow(0.026, 2) + pow(0.027, 2)));
  dataRM["tg_RM_Kplus_Helium"]->SetPointError(6, 0, sqrt(pow(0.033, 2) + pow(0.027, 2)));
  dataRM["tg_RM_Kplus_Helium"]->SetPointError(7, 0, sqrt(pow(0.044, 2) + pow(0.028, 2)));
  dataRM["tg_RM_Kplus_Helium"]->SetPointError(8, 0, sqrt(pow(0.064, 2) + pow(0.027, 2)));
  dataRM["tg_RM_Kplus_Neon"]->SetPoint(0, 0.16, 0.970);
  dataRM["tg_RM_Kplus_Neon"]->SetPoint(1, 0.25, 0.961);
  dataRM["tg_RM_Kplus_Neon"]->SetPoint(2, 0.35, 0.961);
  dataRM["tg_RM_Kplus_Neon"]->SetPoint(3, 0.45, 0.923);
  dataRM["tg_RM_Kplus_Neon"]->SetPoint(4, 0.55, 0.902);
  dataRM["tg_RM_Kplus_Neon"]->SetPoint(5, 0.64, 0.925);
  dataRM["tg_RM_Kplus_Neon"]->SetPoint(6, 0.75, 0.886);
  dataRM["tg_RM_Kplus_Neon"]->SetPoint(7, 0.84, 0.858);
  dataRM["tg_RM_Kplus_Neon"]->SetPoint(8, 0.94, 0.722);
  dataRM["tg_RM_Kplus_Neon"]->SetPointError(0, 0, sqrt(pow(0.010, 2) + pow(0.028, 2)));
  dataRM["tg_RM_Kplus_Neon"]->SetPointError(1, 0, sqrt(pow(0.009, 2) + pow(0.027, 2)));
  dataRM["tg_RM_Kplus_Neon"]->SetPointError(2, 0, sqrt(pow(0.010, 2) + pow(0.027, 2)));
  dataRM["tg_RM_Kplus_Neon"]->SetPointError(3, 0, sqrt(pow(0.012, 2) + pow(0.026, 2)));
  dataRM["tg_RM_Kplus_Neon"]->SetPointError(4, 0, sqrt(pow(0.014, 2) + pow(0.026, 2)));
  dataRM["tg_RM_Kplus_Neon"]->SetPointError(5, 0, sqrt(pow(0.017, 2) + pow(0.026, 2)));
  dataRM["tg_RM_Kplus_Neon"]->SetPointError(6, 0, sqrt(pow(0.021, 2) + pow(0.025, 2)));
  dataRM["tg_RM_Kplus_Neon"]->SetPointError(7, 0, sqrt(pow(0.027, 2) + pow(0.025, 2)));
  dataRM["tg_RM_Kplus_Neon"]->SetPointError(8, 0, sqrt(pow(0.036, 2) + pow(0.021, 2)));
  dataRM["tg_RM_Kplus_Krypton"]->SetPoint(0, 0.16, 1.047);
  dataRM["tg_RM_Kplus_Krypton"]->SetPoint(1, 0.25, 0.985);
  dataRM["tg_RM_Kplus_Krypton"]->SetPoint(2, 0.35, 0.906);
  dataRM["tg_RM_Kplus_Krypton"]->SetPoint(3, 0.45, 0.848);
  dataRM["tg_RM_Kplus_Krypton"]->SetPoint(4, 0.55, 0.822);
  dataRM["tg_RM_Kplus_Krypton"]->SetPoint(5, 0.64, 0.787);
  dataRM["tg_RM_Kplus_Krypton"]->SetPoint(6, 0.75, 0.761);
  dataRM["tg_RM_Kplus_Krypton"]->SetPoint(7, 0.84, 0.687);
  dataRM["tg_RM_Kplus_Krypton"]->SetPoint(8, 0.95, 0.643);
  dataRM["tg_RM_Kplus_Krypton"]->SetPointError(0, 0, sqrt(pow(0.011, 2) + pow(0.033, 2)));
  dataRM["tg_RM_Kplus_Krypton"]->SetPointError(1, 0, sqrt(pow(0.009, 2) + pow(0.030, 2)));
  dataRM["tg_RM_Kplus_Krypton"]->SetPointError(2, 0, sqrt(pow(0.010, 2) + pow(0.026, 2)));
  dataRM["tg_RM_Kplus_Krypton"]->SetPointError(3, 0, sqrt(pow(0.011, 2) + pow(0.024, 2)));
  dataRM["tg_RM_Kplus_Krypton"]->SetPointError(4, 0, sqrt(pow(0.013, 2) + pow(0.023, 2)));
  dataRM["tg_RM_Kplus_Krypton"]->SetPointError(5, 0, sqrt(pow(0.015, 2) + pow(0.022, 2)));
  dataRM["tg_RM_Kplus_Krypton"]->SetPointError(6, 0, sqrt(pow(0.019, 2) + pow(0.022, 2)));
  dataRM["tg_RM_Kplus_Krypton"]->SetPointError(7, 0, sqrt(pow(0.024, 2) + pow(0.020, 2)));
  dataRM["tg_RM_Kplus_Krypton"]->SetPointError(8, 0, sqrt(pow(0.034, 2) + pow(0.019, 2)));
  dataRM["tg_RM_Kplus_Xenon"]->SetPoint(0, 0.16, 1.023);
  dataRM["tg_RM_Kplus_Xenon"]->SetPoint(1, 0.25, 0.958);
  dataRM["tg_RM_Kplus_Xenon"]->SetPoint(2, 0.35, 0.874);
  dataRM["tg_RM_Kplus_Xenon"]->SetPoint(3, 0.44, 0.808);
  dataRM["tg_RM_Kplus_Xenon"]->SetPoint(4, 0.55, 0.788);
  dataRM["tg_RM_Kplus_Xenon"]->SetPoint(5, 0.64, 0.770);
  dataRM["tg_RM_Kplus_Xenon"]->SetPoint(6, 0.74, 0.677);
  dataRM["tg_RM_Kplus_Xenon"]->SetPoint(7, 0.84, 0.633);
  dataRM["tg_RM_Kplus_Xenon"]->SetPoint(8, 0.95, 0.599);
  dataRM["tg_RM_Kplus_Xenon"]->SetPointError(0, 0, sqrt(pow(0.014, 2) + pow(0.034, 2)));
  dataRM["tg_RM_Kplus_Xenon"]->SetPointError(1, 0, sqrt(pow(0.012, 2) + pow(0.029, 2)));
  dataRM["tg_RM_Kplus_Xenon"]->SetPointError(2, 0, sqrt(pow(0.012, 2) + pow(0.025, 2)));
  dataRM["tg_RM_Kplus_Xenon"]->SetPointError(3, 0, sqrt(pow(0.014, 2) + pow(0.023, 2)));
  dataRM["tg_RM_Kplus_Xenon"]->SetPointError(4, 0, sqrt(pow(0.016, 2) + pow(0.022, 2)));
  dataRM["tg_RM_Kplus_Xenon"]->SetPointError(5, 0, sqrt(pow(0.020, 2) + pow(0.022, 2)));
  dataRM["tg_RM_Kplus_Xenon"]->SetPointError(6, 0, sqrt(pow(0.023, 2) + pow(0.020, 2)));
  dataRM["tg_RM_Kplus_Xenon"]->SetPointError(7, 0, sqrt(pow(0.029, 2) + pow(0.018, 2)));
  dataRM["tg_RM_Kplus_Xenon"]->SetPointError(8, 0, sqrt(pow(0.042, 2) + pow(0.017, 2)));
}

void setupMultiplicityRatioVsA()
{
  data["tg_RM_piplus_slice_0_zbin_0"] = new TGraphErrors(4);
  data["tg_RM_piplus_slice_0_zbin_1"] = new TGraphErrors(4);
  data["tg_RM_piplus_slice_0_zbin_2"] = new TGraphErrors(4);
  data["tg_RM_piplus_slice_0_zbin_3"] = new TGraphErrors(4);
  data["tg_RM_piminus_slice_0_zbin_0"] = new TGraphErrors(4);
  data["tg_RM_piminus_slice_0_zbin_1"] = new TGraphErrors(4);
  data["tg_RM_piminus_slice_0_zbin_2"] = new TGraphErrors(4);
  data["tg_RM_piminus_slice_0_zbin_3"] = new TGraphErrors(4);
  data["tg_RM_Kplus_slice_0_zbin_0"] = new TGraphErrors(4);
  data["tg_RM_Kplus_slice_0_zbin_1"] = new TGraphErrors(4);
  data["tg_RM_Kplus_slice_0_zbin_2"] = new TGraphErrors(4);
  data["tg_RM_Kplus_slice_0_zbin_3"] = new TGraphErrors(4);
  data["tg_RM_piplus_slice_0_zbin_0"]->SetName("tg_RM_piplus_slice_0_zbin_0");
  data["tg_RM_piplus_slice_0_zbin_1"]->SetName("tg_RM_piplus_slice_0_zbin_1");
  data["tg_RM_piplus_slice_0_zbin_2"]->SetName("tg_RM_piplus_slice_0_zbin_2");
  data["tg_RM_piplus_slice_0_zbin_3"]->SetName("tg_RM_piplus_slice_0_zbin_3");
  data["tg_RM_piminus_slice_0_zbin_0"]->SetName("tg_RM_piminus_slice_0_zbin_0");
  data["tg_RM_piminus_slice_0_zbin_1"]->SetName("tg_RM_piminus_slice_0_zbin_1");
  data["tg_RM_piminus_slice_0_zbin_2"]->SetName("tg_RM_piminus_slice_0_zbin_2");
  data["tg_RM_piminus_slice_0_zbin_3"]->SetName("tg_RM_piminus_slice_0_zbin_3");
  data["tg_RM_Kplus_slice_0_zbin_0"]->SetName("tg_RM_Kplus_slice_0_zbin_0");
  data["tg_RM_Kplus_slice_0_zbin_1"]->SetName("tg_RM_Kplus_slice_0_zbin_1");
  data["tg_RM_Kplus_slice_0_zbin_2"]->SetName("tg_RM_Kplus_slice_0_zbin_2");
  data["tg_RM_Kplus_slice_0_zbin_3"]->SetName("tg_RM_Kplus_slice_0_zbin_3");
  data["tg_RM_piplus_slice_0_zbin_0"]->SetTitle(";A^{1/3};R_{M}");
  data["tg_RM_piplus_slice_0_zbin_1"]->SetTitle(";A^{1/3};R_{M}");
  data["tg_RM_piplus_slice_0_zbin_2"]->SetTitle(";A^{1/3};R_{M}");
  data["tg_RM_piplus_slice_0_zbin_3"]->SetTitle(";A^{1/3};R_{M}");
  data["tg_RM_piminus_slice_0_zbin_0"]->SetTitle(";A^{1/3};R_{M}");
  data["tg_RM_piminus_slice_0_zbin_1"]->SetTitle(";A^{1/3};R_{M}");
  data["tg_RM_piminus_slice_0_zbin_2"]->SetTitle(";A^{1/3};R_{M}");
  data["tg_RM_piminus_slice_0_zbin_3"]->SetTitle(";A^{1/3};R_{M}");
  data["tg_RM_Kplus_slice_0_zbin_0"]->SetTitle(";A^{1/3};R_{M}");
  data["tg_RM_Kplus_slice_0_zbin_1"]->SetTitle(";A^{1/3};R_{M}");
  data["tg_RM_Kplus_slice_0_zbin_2"]->SetTitle(";A^{1/3};R_{M}");
  data["tg_RM_Kplus_slice_0_zbin_3"]->SetTitle(";A^{1/3};R_{M}");

  unordered_map<string, array<string, 4>> dict;
  dict["tg_RM_piplus_slice_0_zbin_0"] = { "tg_RM_piplus_Helium", "tg_RM_piplus_Neon",
                                          "tg_RM_piplus_Krypton", "tg_RM_piplus_Xenon" };
  dict["tg_RM_piplus_slice_0_zbin_1"] = { "tg_RM_piplus_Helium", "tg_RM_piplus_Neon",
                                          "tg_RM_piplus_Krypton", "tg_RM_piplus_Xenon" };
  dict["tg_RM_piplus_slice_0_zbin_2"] = { "tg_RM_piplus_Helium", "tg_RM_piplus_Neon",
                                          "tg_RM_piplus_Krypton", "tg_RM_piplus_Xenon" };
  dict["tg_RM_piplus_slice_0_zbin_3"] = { "tg_RM_piplus_Helium", "tg_RM_piplus_Neon",
                                          "tg_RM_piplus_Krypton", "tg_RM_piplus_Xenon" };

  dict["tg_RM_piminus_slice_0_zbin_0"] = { "tg_RM_piminus_Helium", "tg_RM_piminus_Neon",
                                           "tg_RM_piminus_Krypton", "tg_RM_piminus_Xenon" };
  dict["tg_RM_piminus_slice_0_zbin_1"] = { "tg_RM_piminus_Helium", "tg_RM_piminus_Neon",
                                           "tg_RM_piminus_Krypton", "tg_RM_piminus_Xenon" };
  dict["tg_RM_piminus_slice_0_zbin_2"] = { "tg_RM_piminus_Helium", "tg_RM_piminus_Neon",
                                           "tg_RM_piminus_Krypton", "tg_RM_piminus_Xenon" };
  dict["tg_RM_piminus_slice_0_zbin_3"] = { "tg_RM_piminus_Helium", "tg_RM_piminus_Neon",
                                           "tg_RM_piminus_Krypton", "tg_RM_piminus_Xenon" };
  dict["tg_RM_Kplus_slice_0_zbin_0"] = { "tg_RM_Kplus_Helium", "tg_RM_Kplus_Neon",
                                         "tg_RM_Kplus_Krypton", "tg_RM_Kplus_Xenon" };
  dict["tg_RM_Kplus_slice_0_zbin_1"] = { "tg_RM_Kplus_Helium", "tg_RM_Kplus_Neon",
                                         "tg_RM_Kplus_Krypton", "tg_RM_Kplus_Xenon" };
  dict["tg_RM_Kplus_slice_0_zbin_2"] = { "tg_RM_Kplus_Helium", "tg_RM_Kplus_Neon",
                                         "tg_RM_Kplus_Krypton", "tg_RM_Kplus_Xenon" };
  dict["tg_RM_Kplus_slice_0_zbin_3"] = { "tg_RM_Kplus_Helium", "tg_RM_Kplus_Neon",
                                         "tg_RM_Kplus_Krypton", "tg_RM_Kplus_Xenon" };

  for (auto d : dataRM) {
    if (d.first.find("Helium") != string::npos) {
      d.second->Fit(fit_function_lower);
    } else {
      d.second->Fit(fit_function_nominal);
    }
  }

  vector<string> names = { "tg_RM_piplus_Helium", "tg_RM_piplus_Neon",
                           "tg_RM_piplus_Krypton", "tg_RM_piplus_Xenon",
                           "tg_RM_piminus_Helium", "tg_RM_piminus_Neon",
                           "tg_RM_piminus_Krypton", "tg_RM_piminus_Xenon",
                           "tg_RM_Kplus_Helium", "tg_RM_Kplus_Neon",
                           "tg_RM_Kplus_Krypton", "tg_RM_Kplus_Xenon" };
  for (string n : names) {
    string x = n + "_itp";
    // cout << "Defining " << x << endl;
    dataRMitp[x] = new TGraphErrors(4);
    dataRMitp[x]->SetName(x.c_str());
    dataRMitp[x]->SetTitle(";z_{h}; Interpolated R_{M}");
  }

  for (auto d : dict) {
    auto key = d.first;
    cout << "Accessing key: " << key << endl;
    auto sources = d.second;

    for (int i = 0; i < 4; ++i) {
      auto key2 = sources[i];
      TGraphErrors* input_data = dataRM[key2];
      int z_index = atoi(&key.back());
      double z = zbins[z_index];
      cout << "Filling point from " << key2 << ", z = " << z << endl;
      double R = -1;
      double Rerr = -1;

      TF1* func = nullptr;

      if (key2.find("Helium") != string::npos) {
        func = input_data->GetFunction(fit_function_lower);
      } else {
        func = input_data->GetFunction(fit_function_nominal);
      }
      if (!func) {
        cout << "Something went wrong" << endl;
      }
      R = func->Eval(z);
      data[key]->SetPoint(i, A13[i], R);

      // Compute the uncertainty
      TGraphErrors* upper = (TGraphErrors*)input_data->Clone("upper");
      TGraphErrors* lower = (TGraphErrors*)input_data->Clone("lower");
      for (int i = 0; i < input_data->GetN(); ++i) {
        upper->GetY()[i] = upper->GetY()[i] + 0.5 * upper->GetEY()[i];
        lower->GetY()[i] = lower->GetY()[i] - 0.5 * lower->GetEY()[i];
      }
      if (key2.find("Helium") != string::npos) {
        upper->Fit(fit_function_lower, "Q");
        lower->Fit(fit_function_lower, "Q");
        Rerr = upper->GetFunction(fit_function_lower)->Eval(z) - lower->GetFunction(fit_function_lower)->Eval(z);
      } else {
        upper->Fit(fit_function_nominal, "Q");
        lower->Fit(fit_function_nominal, "Q");
        Rerr = upper->GetFunction(fit_function_nominal)->Eval(z) - lower->GetFunction(fit_function_nominal)->Eval(z);
      }
      // Rerr = upper->GetFunction(fit_function_nominal)->Eval(z) - lower->GetFunction(fit_function_nominal)->Eval(z);
      data[key]->SetPointError(i, 0, Rerr);

      string x = key2 + "_itp";
      dataRMitp[x]->SetPoint(z_index, z, R);
      dataRMitp[x]->SetPointError(z_index, 0, Rerr);
      // }
    }
  }
}