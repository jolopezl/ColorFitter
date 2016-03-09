// To be used with ROOT Interpreter
// $ root -l load.C
// root[#] ifit()
int load(){
  gROOT->ProcessLine(".L source/model.cc+ ");
  gROOT->ProcessLine(".L source/ifit.cc+");
  return 1;
}
