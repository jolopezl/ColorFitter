void plot_ratio() {
    // Generate a new canvas and divide it
    TCanvas *cnvrp = new TCanvas("cnvrp","example",600,600);
    cnvrp->SetFillColor(0);
    cnvrp->SetFrameFillStyle(0);
    TPad *pad1 = new TPad("pad1","pad1",0,0.4,1,1);
    pad1->SetBottomMargin(0);
    pad1->Draw();
    pad1->cd();
    // Draw plots here

    ATLASLabel(0.2,0.85,"Internal");
    myMarkerText(0.3,0.3,g_two_subevent_resolution->GetMarkerColor(),g_two_subevent_resolution->GetMarkerStyle(),"2-subevent method",1.25,22);
    myMarkerText(0.3,0.24,g_three_subevent_resolution_AP->GetMarkerColor(),g_three_subevent_resolution_AP->GetMarkerStyle(),"3-subevent method for FCal in side A",1.25,22);
    myMarkerText(0.3,0.18,g_three_subevent_resolution_AN->GetMarkerColor(),g_three_subevent_resolution_AN->GetMarkerStyle(),"3-subevent method for FCal in side C",1.25,22);
    
    c1->cd();
    TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.4);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.35);
    pad2->Draw();
    pad2->cd();
    // Draw ratio
    
    cnvrp->Print("plot_ratios.pdf");
}
