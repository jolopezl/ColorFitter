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
yTitle = "L_p [fm]"
zTitle = "#Delta #LT p_{t}^{2} #GT [GeV^{2}]"
xTitleOffSet = 5.0
yTitleOffSet = 5.0
zTitleOffSet = 5.0
tgraph = ROOT.TGraph2D("2d-map.txt")
canvas = ROOT.TCanvas()
tgraph.GetXaxis().SetTitleFont(fontAxesCode)
tgraph.GetXaxis().SetTitleSize(fontAxesSize)
tgraph.GetXaxis().SetLabelFont(fontAxesCode)
tgraph.GetXaxis().SetLabelSize(fontAxesSize)
tgraph.GetYaxis().SetTitleFont(fontAxesCode)
tgraph.GetYaxis().SetTitleSize(fontAxesSize)
tgraph.GetYaxis().SetLabelFont(fontAxesCode)
tgraph.GetYaxis().SetLabelSize(fontAxesSize)

tgraph.SetTitle("#Delta #LT p_{t}^{2} #GT [GeV^{2}];A^{1/3};L_p [fm]")

tgraph.GetYaxis().SetTitleOffset(yTitleOffSet)

tgraph.GetXaxis().SetTitleOffset(xTitleOffSet)

tgraph.GetZaxis().SetTitleOffset(zTitleOffSet)

tgraph.SetLineWidth(2)

tgraph.Draw("surf")
canvas.Print("2d-map.pdf");
