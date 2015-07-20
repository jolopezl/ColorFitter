//
int load(){
  gROOT->ProcessLine(".L model.cc+ ");
  gROOT->ProcessLine(".L ifit.cc+");
  return 1;
}