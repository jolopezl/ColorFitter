#!/usr/bin/python
from numpy import loadtxt
from array import array
import sys, os, ROOT
factor = 1.

from AtlasStyle import SetAtlasStyle, AddLabel
SetAtlasStyle()

val1 = array("f",[0.023970141,-0.09027767,-0.096765855,-0.070503146])  # rho = 0.0 3P
val2 = array("f",[-0.018364875,-0.017736651,-0.045972771,-0.036238201])    # rho = 0.0 fixed cross section 40 mbarn
val3 = array("f",[-0.024345224,-0.010381708,-0.040340539,-0.036086849])     # rho = 0.0 fixed cross section 30 mbarn

err1 = array("f",[0.138624751,0.112212584,0.174856466,0.173052092])  # rho =  0.0 3P
err2 = array("f",[0.05202612,0.048785183,0.055557061,0.051039642]) # rho = 0.0 fixed cross section 40 mbarn
err3 = array("f",[0.046843264,0.046405784,0.05402113,0.060139015]) # rho = 0.0 fixed cross section 30 mbarn

xval = array("f",[0.32,0.53,0.75,0.94])
xerr = array("f",[0,0,0,0])
xval1 = array("f",[0,0,0,0])
xval2 = array("f",[0,0,0,0])
xval3 = array("f",[0,0,0,0])

offset = 0.0075
offset = 0.01
offset = offset/2
for i in range(4):   
  xval1[i] = xval[i] - offset
  xval2[i] = xval[i] 
  xval3[i] = xval[i] + offset 

g1 = ROOT.TGraphErrors(4,xval1,val1,xerr,err1)
g2 = ROOT.TGraphErrors(4,xval2,val2,xerr,err2)
g3 = ROOT.TGraphErrors(4,xval3,val3,xerr,err3)


# ROOT.gROOT.SetStyle("Plain")
# ROOT.gStyle.SetPadTickX(1)
# ROOT.gStyle.SetPadTickY(1)
# ROOT.gStyle.SetPadTopMargin(0.05)
# ROOT.gStyle.SetPadRightMargin(0.05)
# ROOT.gStyle.SetPadLeftMargin(0.125)
# ROOT.gStyle.SetPadBottomMargin(0.16)
# ROOT.gStyle.SetOptStat(0)
# ROOT.gStyle.SetOptTitle(0)
# ROOT.gStyle.SetEndErrorSize(7.5)

# Configuration
xlabel = "z_{h}"
# L_P configuration
ylabel = "#Deltaz"

fileout = "fig05c_dz.pdf" #sys.argv[3]

ylo = -0.35
yhi = 0.35

markerSize = 2.0
lineWidth = 3
############# code
c = ROOT.TCanvas("canvas","canvas",800,600)
color = [1,2,4,8,9]

markers = [20,21,22,23,29,33]
# markers = [24,25,26,27,28,32]
colors = [1,2,3,4,6,9]

i = 1
g1.SetMarkerStyle(markers[i])
g1.SetMarkerColor(colors[i]) 
g1.SetLineColor(colors[i])
g1.GetXaxis().SetTitle(xlabel)
g1.GetYaxis().SetTitle(ylabel)
g1.GetYaxis().SetTitleOffset(0.75)
i = 4
g2.SetMarkerStyle(markers[i])
g2.SetMarkerColor(colors[i]) 
g2.SetLineColor(colors[i])
g2.GetXaxis().SetTitle(xlabel)
g2.GetYaxis().SetTitle(ylabel)
g2.GetYaxis().SetTitleOffset(0.75)
i = 5
g3.SetMarkerStyle(markers[i])
g3.SetMarkerColor(colors[i]) 
g3.SetLineColor(colors[i])
g3.GetXaxis().SetTitle(xlabel)
g3.GetYaxis().SetTitle(ylabel)
g3.GetYaxis().SetTitleOffset(0.75)

g1.GetYaxis().SetNdivisions(5+100*5);
g2.GetYaxis().SetNdivisions(5+100*5);


fontAxesSize = 28
# axes range
g1.GetXaxis().SetRangeUser(0.01,0.99)
g1.GetYaxis().SetRangeUser(ylo,yhi)
g2.GetYaxis().SetRangeUser(ylo,yhi)
g3.GetYaxis().SetRangeUser(ylo,yhi)
g1.GetYaxis().SetTitleOffset(1.0)

x0 = 0.55-0.02
y0 = 0.625+0.06
x1 = x0 + 0.3-0.02
y1 = y0 + 0.25
leg = ROOT.TLegend(x0,y0,x1,y1)
leg.SetTextFont(43)
leg.SetTextSize(28)
leg.SetBorderSize(0)
leg.SetFillStyle(0)
leg.SetHeader("He subtracted #rho = 0.0")
leg.AddEntry(g1,"BLE","ep")
# leg.AddEntry(g2,"2P  - #sigma_{ph} = 40 [mbarn]","ep")
# leg.AddEntry(g3,"2P  - #sigma_{ph} = 30 [mbarn]","ep")
leg.AddEntry(g2,"BLE40","ep")
leg.AddEntry(g3,"BLE30","ep")

text1 = ROOT.TLatex()
text1.SetNDC()
text1.SetTextFont(43)
text1.SetTextSize(fontAxesSize)

g1.Draw("AP")
g2.Draw("P SAME")
g3.Draw("P SAME")
leg.Draw()
# text1.DrawLatex(0.17,0.85,"He subtracted #rho = 0.0")
c.Print(fileout)