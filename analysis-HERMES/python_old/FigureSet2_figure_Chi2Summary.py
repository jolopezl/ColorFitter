#!/usr/bin/python
from numpy import loadtxt
from array import array
import sys, os, ROOT
factor = 1.

from AtlasStyle import SetAtlasStyle
SetAtlasStyle()

val1 = array("f",[2.137191558,1.12430168,0.183660046,0.121672328])  # 4P
val2 = array("f",[1.439136856,0.864235678,0.326817342,0.297840314])  # 3P
val3 = array("f",[1.514137845,0.819098412,0.132133632,0.08829914])   # 3P*
val4 = array("f",[1.168148071,0.648347815,0.308321527,0.254493015]) # 2P

xval = array("f",[0.32,0.53,0.75,0.94])
xerr = array("f",[0,0,0,0])
xval1 = array("f",[0,0,0,0])
xval2 = array("f",[0,0,0,0])
xval3 = array("f",[0,0,0,0])

g1 = ROOT.TGraphErrors(4,xval,val1,xerr,xerr)
g2 = ROOT.TGraphErrors(4,xval,val2,xerr,xerr)
g3 = ROOT.TGraphErrors(4,xval,val3,xerr,xerr)
g4 = ROOT.TGraphErrors(4,xval,val4,xerr,xerr)

# ROOT.gROOT.SetStyle("Plain")
# ROOT.gStyle.SetPadTickX(1)
# ROOT.gStyle.SetPadTickY(1)
# ROOT.gStyle.SetPadTopMargin(0.05)
ROOT.gStyle.SetPadRightMargin(0.05)
ROOT.gStyle.SetPadLeftMargin(0.125)
ROOT.gStyle.SetPadBottomMargin(0.16)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptTitle(0)
ROOT.gStyle.SetEndErrorSize(7.5)

# Configuration
xlabel = "z_{h}"
# L_P configuration
ylabel = "#chi^{2}/^{}DOF"

fileout = "fig05d_chi2_Summary.pdf" #sys.argv[3]

ylo = 0
yhi = 2.2

markerSize = 2.0
lineWidth = 3
############# code
c = ROOT.TCanvas("canvas","canvas",800,600)
color = [1,2,4,8,9]
i = 0
g1.SetMarkerStyle(20+i)
# g1.SetMarkerSize(markerSize)
g1.SetMarkerColor(color[i]) 
g1.SetLineColor(color[i])
# g1.SetLineWidth(lineWidth)
g1.GetXaxis().SetTitle(xlabel)
g1.GetYaxis().SetTitle(ylabel)
g1.GetYaxis().SetTitleOffset(1.75)
i = 1
g2.SetMarkerStyle(20+i)
# g2.SetMarkerSize(markerSize)
g2.SetMarkerColor(color[i]) 
g2.SetLineColor(color[i])
# g2.SetLineWidth(lineWidth)
g2.GetYaxis().SetTitleOffset(1.75)
i = 2
g3.SetMarkerStyle(20+i)
# g3.SetMarkerSize(markerSize)
g3.SetMarkerColor(color[i]) 
g3.SetLineColor(color[i])
# g3.SetLineWidth(lineWidth)
g3.GetYaxis().SetTitleOffset(1.75)
i = 3
g4.SetMarkerStyle(20+i)
# g4.SetMarkerSize(markerSize)
g4.SetMarkerColor(color[i]) 
g4.SetLineColor(color[i])
# g4.SetLineWidth(lineWidth)
g4.GetYaxis().SetTitleOffset(1.75)

g1.GetYaxis().SetNdivisions(5+100*5);
g2.GetYaxis().SetNdivisions(5+100*5);


fontAxesSize = 28
fontAxesCode = 43
# axes range
g1.GetXaxis().SetRangeUser(0.01,0.99)
g1.GetYaxis().SetRangeUser(ylo,yhi)
g1.GetYaxis().SetTitleOffset(1.25)


x0 = 0.425
y0 = 0.6
x1 = x0 + 0.3
y1 = y0 + 0.28
leg = ROOT.TLegend(x0,y0,x1,y1)
leg.SetTextFont(43)
leg.SetTextSize(28)
leg.SetBorderSize(0)
leg.SetFillStyle(0)
leg.SetHeader("He subtracted #rho = 0.0")
# leg.SetNColumns(3);
leg.AddEntry(g1,"4P - free #sigma_{ph}","ep")
leg.AddEntry(g2,"3P  - #sigma_{ph} = 40 [mbarn] - #Deltaz = 0","ep")
leg.AddEntry(g3,"3P* - #sigma_{ph} = 40 [mbarn] free #Deltaz","ep")
leg.AddEntry(g4,"2P  - #sigma_{ph} = 40 [mbarn] - #Deltaz = 0","ep")

text1 = ROOT.TLatex()
text1.SetNDC()
text1.SetTextFont(43)
text1.SetTextSize(fontAxesSize)

g1.Draw("AP")
g2.Draw("P SAME")
g3.Draw("P SAME")
g4.Draw("P SAME")
leg.Draw()
# text1.DrawLatex(0.17,0.85, "He subtracted #rho =  0.0")
# text1.DrawLatex(0.17, 0.8, "Fixed cross section #sigma_{ph} = 40 [mbarn]")
c.Print(fileout)