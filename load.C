// To be used with ROOT Interpreter
// $ root -l load.C
// root[#] ifit()
int load(){
  gROOT->ProcessLine(".L model.cc+ ");
  gROOT->ProcessLine(".L ifit.cc+");
  gROOT->ProcessLine(".L main.cc+");
  return 1;
}
