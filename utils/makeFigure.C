float zcentr[4]           = {0.32,0.53,0.75,0.94};
float pt2_neon[4]         = {0.0069,0.0063,-0.0015,-0.0037};
float pt2_err_neon[4]     = {0.002747726333,0.005152669211,0.01350888596,0.02077666961};
float pt2_kripton[4]      = {0.021,0.0224,0.0085,0.0115};
float pt2_err_kripton[4]  = {0.002946183973,0.005444263036,0.01360477857,0.02106038936};
float pt2_xenon[4]        = {0.0274,0.0296,0.0144,0.0073};
float pt2_err_xenon[4]    = {0.003243454948,0.005979130372,0.01442289846,0.02177360788};

float rm_neon[4]          = {0.893189114368,0.885454096825,0.880935853275,0.798520384419};
float rm_kripton[4]       = {0.78747612087,0.744660997913,0.679028679486,0.551673817154};
float rm_xenon[4]         = {0.736762500635,0.684223383665,0.619689942725,0.498076090992};
float rm_err_neon[4]      = {0.0594409344724,0.0515307622582,0.0634878265064,0.0682394907588};
float rm_err_kripton[4]   = {0.0542930099596,0.0447182315218,0.05222907333,0.0527700155986};
float rm_err_xenon[4]     = {0.0535218789044,0.0411665583174,0.0503850083386,0.0529182285411};

void makeFigure() {
    gROOT->Reset();
    gROOT->ForceStyle();
    SetAtlasStyle();
    /** model lines **/
    string filename[6][4];
    string basename[6] = {"BL","BLE","BL40","BL30","BLE40","BLE40"};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 6; ++j) {
            filename[j][i] = "testFit"+basename[j]+"_plot_pt_0_"+std::to_string(i)+".txt";
            // filename[j][i] = "testFit"+basename[j]+"_plot_mr_0_"+std::to_string(i)+".txt";
        }
    }
    TGraph* model[6][4];
    for (int i=0; i<4; ++i) {
        for (int j = 0; j < 6; ++j) {
            model[j][i] = new TGraph(filename[j][i].c_str());
        }
    }
    /** data points **/
    TGraphErrors *data[4];
    float xval[3] = {2.9947753767563916, 4.813606330683598, 5.590790378970299};
    float xerr[3] = {0,0,0};
    for (int i = 0; i < 4; ++i) {
        float yval[4] = {pt2_neon[i],pt2_kripton[i],pt2_xenon[i]};
        float yerr[4] = {pt2_err_neon[i],pt2_err_kripton[i],pt2_err_xenon[i]};
        // float yval[4] = {rm_neon[i],rm_kripton[i],rm_xenon[i]};
        // float yerr[4] = {rm_err_neon[i],rm_err_kripton[i],rm_err_xenon[i]};
        data[i] = new TGraphErrors(3,xval,yval,xerr,yerr);
        data[i]->GetYaxis()->SetRangeUser(-0.035,0.035);
        // data[i]->GetYaxis()->SetRangeUser(0.35,1.05);
    }
    /** color and labels **/
    int colors[6] = {1,2,3,4,6,9};
    for (int i=0; i<4; ++i) {
        for (int j = 0; j < 6; ++j) {
            model[j][i]->SetLineColor(colors[j]);
            model[j][i]->SetLineWidth(2);
        }
    }
    /** drawing **/

    data[0]->GetYaxis()->SetTitle("#Delta #LT p_{t}^{2} #GT [GeV^{2}]");
    // data[0]->GetYaxis()->SetTitle("R_{m}");
    data[0]->GetYaxis()->SetTitleOffset(1.75);
    data[3]->GetXaxis()->SetTitle("A^{1/3}");
    data[3]->GetXaxis()->SetTitleOffset(1.25);

    float small = 1e-5;;
    float big = 0.25;
    TCanvas* c1 = new TCanvas("c1","c1 title",800,800);
    c1->Divide(2,2,small,small);
    for (int i=0; i<4; ++i) {
        // pad[i]->cd();
        c1->cd(i+1);
        if (i == 0) {
            gPad->SetBottomMargin(small);
            gPad->SetRightMargin(small);
            gPad->SetLeftMargin(big);
            gPad->SetTopMargin(big);
        }
        else if (i == 1) {
            gPad->SetTopMargin(big);
            gPad->SetBottomMargin(small);
            gPad->SetLeftMargin(small);
            gPad->SetRightMargin(big);
        }
        else if (i == 2) {
            gPad->SetBottomMargin(big);
            gPad->SetTopMargin(small);
            gPad->SetRightMargin(small);
            gPad->SetLeftMargin(big);
        }
        else if (i == 3) {
            gPad->SetBottomMargin(big);
            gPad->SetTopMargin(small);
            gPad->SetLeftMargin(small);
            gPad->SetRightMargin(big);
        }
        // if (i==0) data[i]->Draw();
        data[i]->Draw("AP");
        for (int j = 0; j < 6; ++j) {
            // if (j == 0) model[j][i]->Draw();
            model[j][i]->Draw("SAME");
        }
    }
    
    c1->cd(1);
    myText(0.3,0.65,1,"z-bin #1");
    c1->cd(2);
    myText(0.075,0.65,1,"z-bin #2");
    c1->cd(3);
    myText(0.3,0.9,1,"z-bin #3");
    c1->cd(4);
    myText(0.075,0.9,1,"z-bin #4");

    c1->cd(3);
    float x0 = 0.3;
    float y0 = 0.3;
    float x1 = x0 + 0.55;
    float y1 = y0 + 0.175;
    TLegend* leg = new TLegend(x0,y0,x1,y1);
    leg->SetNColumns(2);
    leg->SetTextFont(43);
    leg->SetTextSize(28);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    for (int i = 0; i < 6; ++i) {
        leg->AddEntry(model[i][0],basename[i].c_str(),"cl");
    }
    leg->Draw();
    c1->Print("testplot.pdf");
}
