void PlotCorrelationParameters()
{
  SetAtlasStyle();
  TFile *f1 = TFile::Open("OutputROOT.20200218.BL30.root", "READ");
  TGraphErrors *tg_q0 = (TGraphErrors *)f1->Get("tg_q0");
  TGraphErrors *tg_lp = (TGraphErrors *)f1->Get("tg_lp");
  TFile *f2 = TFile::Open("correlation_test.root", "READ");
  TGraph *contours[5];
  for (int i = 0; i < 5; ++i)
  {
    contours[i] = (TGraph *)f2->Get(Form("contour_%d", i));
  }

  auto density = (TGraphErrors *)f1->Get("tg_average_density_2");
  for (int i = 0; i < 5; ++i)
  {
    for (int j = 0; j <= 50; ++j)
    {
      double xp, yp;
      contours[i]->GetPoint(j, xp, yp);
      xp = xp * density->Eval(pow(83.7980, 1 / 3.));
      contours[i]->SetPoint(j, xp, yp);
      contours[i]->SetLineStyle(kDashed);
      contours[i]->SetLineWidth(2);
    }
  }

  TGraphErrors *point = new TGraphErrors(1);
  point->SetPoint(1,
                  tg_q0->GetY()[1] * density->Eval(pow(83.7980, 1 / 3.)),
                  tg_lp->GetY()[1]);
  point->SetPointError(1,
                  tg_q0->GetEY()[1] * density->Eval(pow(83.7980, 1 / 3.)),
                  tg_lp->GetEY()[1]);

  TCanvas *c = new TCanvas("c", "correlation plots", 600, 600);
  contours[4]->GetXaxis()->SetTitle("#hat{q} (GeV^{2}/fm)");
  contours[4]->GetYaxis()->SetTitle("L_{c} (fm)");
  contours[4]->GetXaxis()->CenterTitle();
  contours[4]->GetYaxis()->CenterTitle();

  contours[4]->Draw("AL");
  contours[3]->Draw("SAMEL");
  contours[2]->Draw("SAMEL");
  contours[1]->Draw("SAMEL");
  contours[0]->Draw("SAMEL");
  point->Draw("PSAME");

  c->Print("unnamed.pdf");
}