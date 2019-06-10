void PlotCrossSection()
{
  SetAtlasStyle();

  // TFile *fin = TFile::Open("OutputROOT.20180806.BLE30.root", "READ");
  TFile* fin = new TFile("OutputROOT.20181107.BL.root", "READ");

  TGraphErrors* tg = (TGraphErrors*)fin->Get("tg_sigma");

  auto model = tg; // Choose BLE30 as nominal;
  model->SetMarkerSize(1.5);
  model->SetMarkerStyle(20);
  model->GetXaxis()->SetLimits(0.0, 1.0);
  model->GetXaxis()->SetNdivisions(505);
  model->GetYaxis()->SetRangeUser(-25, 180);
  // model->GetYaxis()->SetRangeUser(0.1,70);
  model->GetYaxis()->SetNdivisions(505);
  model->SetTitle(";#it{z};#it{L}_{p} (fm)");
  model->SetTitle(";#it{z};#it{#sigma} (mbarn)");
  model->GetXaxis()->CenterTitle();
  model->GetYaxis()->CenterTitle();

  TLine* line = new TLine(0, 40, 1, 40);
  // line->SetLineWidth(4);
  line->SetLineStyle(kDashed);

  TCanvas* c2 = new TCanvas("c2", "c2 title", 800, 600);

  model->Draw("APE");
  line->Draw("SAME");

  // model_corrected->Draw("PSAME");

  // TLegend* leg = new TLegend(0.2,0.2,0.35,0.35);
  TLegend* leg = new TLegend(0.2, 0.75, 0.35, 0.92);
  // leg->SetNColumns(2);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  // leg->AddEntry(model,"BLE30","pe");
  // leg->AddEntry(grint2,Form("Bialas #it{et. al.}, #chi^{2}/dof = %.3f",fg2->GetChisquare()/fg2->GetNDF()),"fl");
  // leg->AddEntry(grint1,Form("Linear Form, #chi^{2}/dof = %.3f, #kappa = %.3f #pm %.3f GeV/fm",fg1->GetChisquare()/fg1->GetNDF(),fg1->GetParameter(2),fg1->GetParError(2)),"fl");
  // leg->AddEntry(grint1,Form("Linear Form, #chi^{2}/dof = %.2f, #kappa = %.1f #pm %.1f GeV/fm",fg1->GetChisquare()/fg1->GetNDF(),fg1->GetParameter(2),fg1->GetParError(2)),"fl");
  // leg->AddEntry(grint1,Form("Lund String Model (struck quark), #chi^{2}/dof = %.2f, #kappa = %.2f #pm %.2f GeV/fm",fg1->GetChisquare()/fg1->GetNDF(),fg1->GetParameter(0),fg1->GetParError(0)),"fl");
  // leg->AddEntry(grint2,Form("Bialas #it{et. al.}, #chi^{2}/dof = %.2f, #kappa = %.2f #pm %.2f GeV/fm",fg2->GetChisquare()/fg2->GetNDF(),fg2->GetParameter(0),fg2->GetParError(0)),"fl");
  // leg->AddEntry(grint1, "Lund String Model (struck quark)","fl");//   Form("Linear Form, #chi^{2}/dof = %.2f, #kappa = %.1f #pm %.1f GeV/fm",fg1->GetChisquare()/fg1->GetNDF(),fg1->GetParameter(0),fg1->GetParError(0)),"fl");
  // leg->AddEntry(grint2, "Bialas #it{et. al.}","fl");//Form("Bialas #it{et. al.}, #chi^{2}/dof = %.2f, #kappa = %.1f #pm %.1f GeV/fm",fg2->GetChisquare()/fg2->GetNDF(),fg2->GetParameter(1),fg2->GetParError(1)),"fl");
  leg->AddEntry(model, "BL", "pe");
  leg->AddEntry(line, "40 mbarn", "l");
  leg->Draw();
  c2->Print("figure_cross_section.pdf");
}
