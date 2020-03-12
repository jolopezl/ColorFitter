const double factor = 0.1 * 3. / (4. * 3.141592); // to be removed!!

void PlotQhatPerA()
{
  SetAtlasStyle(43, 22);
  TFile* fin = TFile::Open("OutputROOT.20200310.BL30.root", "READ");

  TGraphErrors* tg_q0;
  std::vector<TGraphErrors*> tg_average_density;
  std::vector<TGraphErrors*> tg_qhat; // this will host 3 qhat

  tg_q0 = (TGraphErrors*)fin->Get("tg_q0");
  for (int i = 0; i < 4; ++i) {
    auto temp = (TGraphErrors*)fin->Get(Form("tg_average_density_%d", i));
    tg_average_density.push_back(temp);
  }

  std::vector<float> nucleus_list = { 20.1797, 83.7980, 131.293 };
  std::vector<float> A13list;
  for (const auto& A : nucleus_list) {
    auto A13 = TMath::Power(A, 1. / 3.);
    A13list.push_back(A13);
    cout << "A^(1/3) = " << A13 << endl;
    auto temp = new TGraphErrors(4);
    for (int iz = 0; iz < 4; ++iz) {
      temp->GetX()[iz] = tg_q0->GetX()[iz];
      temp->GetEX()[iz] = 0;
      auto average_density_at_z = tg_average_density[iz]->Eval(A13);
      cout << "Average densitizy at z-bin " << iz + 1 << " is " << average_density_at_z << endl;
      temp->GetY()[iz] = tg_q0->GetY()[iz] * average_density_at_z;
      temp->GetEY()[iz] = tg_q0->GetEY()[iz] * average_density_at_z;
    }
    tg_qhat.push_back(temp);
  }

  // Set drawing attributes
  for (const auto& model : tg_qhat) {
    model->SetTitle(";#it{z};#it{#hat{q}} (GeV^{2}/fm)");
    model->GetXaxis()->CenterTitle();
    model->GetYaxis()->CenterTitle();
    model->GetXaxis()->SetLimits(0.001, 0.999);
    model->GetXaxis()->SetNdivisions(505);
    model->GetYaxis()->SetRangeUser(-0.015, 0.11);
    model->GetYaxis()->SetNdivisions(505);
    model->GetYaxis()->SetTitleOffset(2.8);
  }

  TCanvas* c1 = new TCanvas("c1", "title", 1200, 500);
  c1->SetLeftMargin(0.22);
  c1->SetBottomMargin(0.17);
  c1->Divide(4, 1, 0, 0);

  for (int i = 0; i < 3; ++i) {
    c1->cd(i + 1);
    tg_qhat.at(i)->Draw("APE");
  }

  TGraphErrors* means = new TGraphErrors(3);
  means->SetTitle(";A^{1/3};#it{#hat{q}} (GeV^{2}/fm)");
  means->GetXaxis()->CenterTitle();
  means->GetYaxis()->CenterTitle();
  means->GetXaxis()->SetLimits(1.50001, 5.4);
  means->GetXaxis()->SetNdivisions(505);
  means->GetYaxis()->SetRangeUser(-0.015, 0.11);
  means->GetYaxis()->SetNdivisions(505);
  // means->GetYaxis()->SetTitleOffset(2.8);

  for (int i = 0; i < 3; ++i) {
    means->GetX()[i] = A13list.at(i);
    double average_qhat = 0, average_qhat_err = 0, weight = 0;
    auto model = tg_qhat.at(i);
    for (int i = 0; i < 4; ++i) {
      average_qhat += model->GetY()[i] / model->GetEY()[i];
      weight += 1 / model->GetEY()[i];
      average_qhat_err += TMath::Power(model->GetEY()[i], 2);
    }
    average_qhat /= weight;
    average_qhat_err = TMath::Sqrt(average_qhat_err) / 4;

    means->GetY()[i] = average_qhat;
    means->GetEY()[i] = average_qhat_err;

    cout << "Average q-hat = " << average_qhat << " +/- " << average_qhat_err << endl;
  }

  double average_qhat = 0, average_qhat_err = 0, weight = 0;
  for (int i = 0; i < 3; ++i) {
    average_qhat += means->GetY()[i] / means->GetEY()[i];
    weight += 1 / means->GetEY()[i];
    average_qhat_err += TMath::Power(means->GetEY()[i], 2);
  }
  average_qhat /= weight;
  average_qhat_err = TMath::Sqrt(average_qhat_err) / 4;
  cout << "Global average q-hat = " << average_qhat << " +/- " << average_qhat_err << endl;

  c1->cd(4);
  means->Draw("APE");

  c1->Print("figure_qhat.pdf");

  auto fout = TFile::Open("Qhat_results.root", "RECREATE");
  fout->cd();
  int d = 0;
  for (int i = 0; i < 3; ++i) {
      tg_qhat[i]->SetName(Form("qhat_%d",d));
      tg_qhat[i]->Write();
      d++;
  }
  means->SetName("qhat_means");
  means->Write();
  fout->Write();
  fout->Close();
}
