#!/usr/bin/python
from numpy import loadtxt
from array import array
import sys, os, ROOT
factor = 1.

from AtlasStyle import SetAtlasStyle, AddLabel
SetAtlasStyle()

val0 = array("f",[-0.018364875,-0.017736651,-0.045972771,-0.036238201])
err0 = array("f",[0.05202612,0.048785183,0.055557061,0.051039642])

val1 = array("f",[-0.01159284,-0.011196274,-0.029020345,-0.022875391])  
val2 = array("f",[-0.019900569,-0.019219813,-0.049817072,-0.039268486])  
val3 = array("f",[-0.023601214,-0.022793867,-0.059080895,-0.046570727])   
err1 = array("f",[0.032841526,0.030795683,0.035070435,0.032218811]) 
err2 = array("f",[0.05637661,0.052864662,0.060202813,0.055307641])
err3 = array("f",[0.066860223,0.062695205,0.071397934,0.065592473]) 

xval = array("f",[0.32,0.53,0.75,0.94])
xerr = array("f",[0,0,0,0])
xval1 = array("f",[0,0,0,0])
xval2 = array("f",[0,0,0,0])
xval3 = array("f",[0,0,0,0])

average_nu = array("f",[13.7, 13.9, 14.0])

offset = 0.0075
offset = 0.02
offset = offset/2
for i in range(4):   
  xval1[i] = xval[i] - offset
  xval2[i] = xval[i] 
  xval3[i] = xval[i] + offset 

for i in range(4):
  val0[i] = val0[i]*13.87
  err0[i] = err0[i]*13.87
  val1[i] = val1[i]*average_nu[0]
  val2[i] = val2[i]*average_nu[1]
  val3[i] = val3[i]*average_nu[2]
  err1[i] = err1[i]*average_nu[0]
  err2[i] = err2[i]*average_nu[1]
  err3[i] = err3[i]*average_nu[2]

g0 = ROOT.TGraphErrors(4,xval,val0,xerr,err0)
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
ylabel = "E_{loss} [GeV] "

fileout = "fig06b_dz.pdf" #sys.argv[3]

ylo = -0.13*14
yhi = 0.09*14

markerSize = 2.0
lineWidth = 3
############# code
c = ROOT.TCanvas("canvas","canvas",800,600)
color = [1,2,4,8,9]
i = 0
g1.SetMarkerStyle(20+i)
g1.SetMarkerColor(color[i]) 
g1.SetLineColor(color[i])
g1.GetXaxis().SetTitle(xlabel)
g1.GetYaxis().SetTitle(ylabel)
g1.GetYaxis().SetTitleOffset(1.75)
i = 1
g2.SetMarkerStyle(20+i)
g2.SetMarkerColor(color[i]) 
g2.SetLineColor(color[i])
g2.GetXaxis().SetTitle(xlabel)
g2.GetYaxis().SetTitle(ylabel)
g2.GetYaxis().SetTitleOffset(1.75)
i = 2
g3.SetMarkerStyle(20+i)
g3.SetMarkerColor(color[i]) 
g3.SetLineColor(color[i])
g3.GetXaxis().SetTitle(xlabel)
g3.GetYaxis().SetTitle(ylabel)
g3.GetYaxis().SetTitleOffset(1.75)

g1.GetYaxis().SetNdivisions(5+100*5);
g2.GetYaxis().SetNdivisions(5+100*5);


fontAxesSize = 28
fontAxesCode = 43
# axes range
g1.GetXaxis().SetRangeUser(0.01,0.99)
g1.GetYaxis().SetRangeUser(ylo,yhi)
g1.GetYaxis().SetTitleOffset(1.25)

g0.SetMarkerStyle(25)

x0 = 0.725
y0 = 0.7
x1 = x0 + 0.325
y1 = y0 + 0.17#/3.*4.
leg = ROOT.TLegend(x0,y0,x1,y1)
leg.SetTextFont(43)
leg.SetTextSize(28)
leg.SetBorderSize(0)
leg.SetFillStyle(0)
leg.SetHeader("  BLE40")
# leg.SetNColumns(3);
leg.AddEntry(g1,"Neon","ep")
leg.AddEntry(g2,"Krypton","ep")
leg.AddEntry(g3,"Xenon","ep")
# leg.AddEntry(g0,"#nu#Deltaz","ep")

line00 = ROOT.TF1("line00","00",0.0,1.0);
line00.SetLineWidth(2);
line00.SetLineColor(1);
line00.SetLineStyle(2);

g1.Draw("AP")
line00.Draw("SAME")
g2.Draw("P SAME")
g3.Draw("P SAME")
# g0.Draw("P SAME")
leg.Draw()
AddLabel(0.2,0.88,"Energy Loss with a 3 Parameter Fit")
AddLabel(0.2, 0.82, "Fixed cross section #sigma_{ph} = 40 [mbarn]")
c.Print(fileout)