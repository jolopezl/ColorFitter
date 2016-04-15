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

############# legend #############
legend = ROOT.TLegend(0.15+0.025,0.7,0.6,0.89)
legend.SetTextSize(fontAxesSize-2)
legend.SetTextFont(fontAxesCode)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetNColumns(2);

text1 = ROOT.TLatex()
text1.SetNDC()
text1.SetTextFont(43)
text1.SetTextSize(fontAxesSize)

lpList = ['1','2','3','4','5','7','10','20']
graphs = []
index = 0
for lp in lpList:
    filename = "input-exp-lp=" + lp + ".txt"
    graphs.append( tgraph(filename) )
    graphs[index].SetLineStyle(index+1)
    legend.AddEntry(graphs[index],"L_{p} = " + lp + " [fm]", "l")
    index = index + 1

c1 = ROOT.TCanvas("canvas","canvas",800,600)
graphs[0].GetYaxis().SetRangeUser(0.0,0.02)
graphs[0].GetXaxis().SetRangeUser(2.28943,6.21447)
graphs[0].Draw("AC")
for i in range(1,len(graphs)):
    graphs[i].Draw("SAME")
legend.Draw()
#text1.DrawLatex(0.17,0.51,"Exp(L_{p})")
c1.Print("demoPlot.pdf");
