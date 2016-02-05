void fit2d() {
  TCanvas *c = new TCanvas();
  TGraph2D *gg = new TGraph2D("tgraph2d.dat");
  gg->SetTitle("1-R;z;A");
  gg->SetMarkerStyle(20);
  gg->Draw("AP");
  gg->Draw("surf same");
  c->Print("g2.pdf");
  TF2 *func = new TF2("func","([0]+[1]*x+[2]*x**2+[3]*x**3+[4]*x**4)*(1-y**[5])");
  gg->Fit(func);
}