import ROOT

ROOT.gStyle.SetPadRightMargin(0.05)
ROOT.gStyle.SetPadLeftMargin(0.15)
ROOT.gStyle.SetPadBottomMargin(0.16)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptTitle(0)
# ROOT.gStyle.SetEndErrorSize(7.5)

fontAxesSize = 28
fontAxesCode = 43

xTitle = "A^{1/3}"
yTitle = "#Delta #LT p_{t}^{2} #GT [GeV^{2}]"
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

g3 = tgraph("input-lp=1.0.txt")
g4 = tgraph("input-lp=5.0.txt")
g5 = tgraph("input-lp=10.0.txt")
g6 = tgraph("input-lp=20.0.txt")
# g7 = tgraph("input-lp=100.0.txt")

g3.GetYaxis().SetRangeUser(0.0,0.03)
g3.GetXaxis().SetRangeUser(2.28943,6.21447)

g3.SetLineStyle(1)
g4.SetLineStyle(2)
g5.SetLineStyle(3)
g6.SetLineStyle(4)
# g7.SetLineStyle(5)

############# legend #############
legend = ROOT.TLegend(0.15+0.025,0.70,0.48,0.89)
legend.SetTextSize(fontAxesSize)
legend.SetTextFont(fontAxesCode)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.AddEntry(g3,"L_{p} = 1 fm", "l")
legend.AddEntry(g4,"L_{p} = 5 fm", "l")
legend.AddEntry(g5,"L_{p} = 10 fm", "l")
legend.AddEntry(g6,"L_{p} = 20 fm", "l")
# legend.AddEntry(g7,"L_{p} = 100 fm", "l")

c1 = ROOT.TCanvas("canvas","canvas",800,600)

g3.Draw("AC");
g4.Draw("SAME");
g5.Draw("SAME");
g6.Draw("SAME");
# g7.Draw("SAME");
legend.Draw()

c1.Print("demoPlot.pdf");
