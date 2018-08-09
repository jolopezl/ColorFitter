import ROOT

ROOT.gStyle.SetPadTopMargin(0.05);
ROOT.gStyle.SetPadRightMargin(0.05);
ROOT.gStyle.SetPadBottomMargin(0.16);
ROOT.gStyle.SetPadLeftMargin(0.16);
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptTitle(0)
# ROOT.gStyle.SetEndErrorSize(7.5)

fontAxesSize = 0.05
fontAxesCode = 42

xTitle = "A^{1/3}"
yTitle = "#Delta p_{T}^{2} [GeV^{2}]"
yTitleOffSet = 1.5

def tgraph(filename):
    tgraph = ROOT.TGraph(filename)
    tgraph.GetXaxis().SetTitleFont(fontAxesCode)
    tgraph.GetXaxis().SetTitleSize(fontAxesSize)
    tgraph.GetXaxis().SetLabelFont(fontAxesCode)
    tgraph.GetXaxis().SetLabelSize(fontAxesSize)
    tgraph.GetYaxis().SetTitleFont(fontAxesCode)
    tgraph.GetYaxis().SetTitleSize(fontAxesSize)
    tgraph.GetYaxis().SetLabelFont(fontAxesCode)
    tgraph.GetYaxis().SetLabelSize(fontAxesSize)
    tgraph.GetYaxis().SetTitle(yTitle)
    tgraph.GetYaxis().SetTitleOffset(yTitleOffSet)
    tgraph.GetXaxis().SetTitle(xTitle)
    tgraph.SetLineWidth(2)
    return tgraph

############# legend #############
legend = ROOT.TLegend(0.2,0.7,0.7,0.89)
legend.SetTextSize(0.05)
legend.SetTextFont(42)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetNColumns(2);

text1 = ROOT.TLatex()
text1.SetNDC()
text1.SetTextFont(42)
text1.SetTextSize(0.05)

lpList = ['1','2','3','4','5','7','10','20']
graphs = []
index = 0
for lp in lpList:
    filename = "input-exp-fixed-lp=" + lp + ".txt"
    graphs.append( tgraph(filename) )
    graphs[index].SetLineStyle(index+1)
    legend.AddEntry(graphs[index],"L_{p} = " + lp + " [fm]", "l")
    index = index + 1

c1 = ROOT.TCanvas("canvas","canvas",800,600)
# c1.SetLeftMargin(0.2);
# c1.SetBottomMargin(0.2);
graphs[0].GetYaxis().SetRangeUser(0.0,0.02)
graphs[0].GetXaxis().SetRangeUser(2.28943,6.21447)
graphs[0].Draw("AC")
for i in range(1,len(graphs)):
    graphs[i].Draw("SAME")
legend.Draw()
#text1.DrawLatex(0.17,0.51,"Exp(L_{p})")
c1.Print("demoPlotfixed.pdf");
