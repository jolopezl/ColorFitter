#!/usr/bin/python
from numpy import loadtxt
from array import array
import sys, os, ROOT
factor = 1.

from AtlasStyle import SetAtlasStyle, AddLabel
SetAtlasStyle()

factor = 0.1*3./(4.*3.141592)
print "Factor to be removed ",factor
print "Inverse is ",1/factor

val1 = array("f",[0.000979387,0.002160808,0.001637914,0.002576695])  
val2 = array("f",[0.001714001,0.003582285,0.002536743,0.003642609])  
val3 = array("f",[0.001998672,0.004087083,0.002822044,0.003937508])   
err1 = array("f",[0.000798121,0.000960257,0.000825269,0.002039819])
err2 = array("f",[0.001396773,0.001591958,0.001278147,0.002883641])
err3 = array("f",[0.001628757,0.001816288,0.001421897,0.003117095]) 

xval  = array("f",[0.32,0.53,0.75,0.94])
xerr  = array("f",[0,0,0,0])
xval1 = array("f",[0,0,0,0])
xval2 = array("f",[0,0,0,0])
xval3 = array("f",[0,0,0,0])

offset = 0.0075
offset = 0.02
offset = offset/2
for i in range(4):   
  xval1[i] = xval[i] - offset
  xval2[i] = xval[i] 
  xval3[i] = xval[i] + offset 

for i in range(4):
    val1[i] = val1[i]/factor;
    val2[i] = val2[i]/factor;
    val3[i] = val3[i]/factor;
    err1[i] = err1[i]/factor;
    err2[i] = err2[i]/factor;
    err3[i] = err3[i]/factor;

for i in range(4):
    val1[i] = val1[i]/xval[i];
    val2[i] = val2[i]/xval[i];
    val3[i] = val3[i]/xval[i];

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
ylabel = "#hat{q} [GeV^{2}/fm] "

fileout = "fig06a_qhat_quark.pdf" #sys.argv[3]

ylo = 0.0
yhi = 0.01/factor

0.000979387
0.004087083

markerSize = 2.0
lineWidth = 3
############# code
c = ROOT.TCanvas("canvas","canvas",800,600)
color = [1,2,4,8,9]
i = 0
g1.SetMarkerStyle(20+i)
g1.SetMarkerSize(markerSize)
g1.SetMarkerColor(color[i]) 
g1.SetLineColor(color[i])
# g1.SetLineWidth(lineWidth)
g1.GetXaxis().SetTitle(xlabel)
g1.GetYaxis().SetTitle(ylabel)
g1.GetYaxis().SetTitleOffset(1.75)
i = 1
g2.SetMarkerStyle(20+i)
g2.SetMarkerSize(markerSize)
g2.SetMarkerColor(color[i]) 
g2.SetLineColor(color[i])
# g2.SetLineWidth(lineWidth)
g2.GetXaxis().SetTitle(xlabel)
g2.GetYaxis().SetTitle(ylabel)
g2.GetYaxis().SetTitleOffset(1.75)
i = 2
g3.SetMarkerStyle(20+i)
g3.SetMarkerSize(markerSize)
g3.SetMarkerColor(color[i]) 
g3.SetLineColor(color[i])
# g3.SetLineWidth(lineWidth)
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
g1.GetYaxis().SetTitleOffset(1.5)

x0 = 0.725
y0 = 0.725
x1 = x0 + 0.325
y1 = y0 + 0.17
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

g1.Draw("AP")
g2.Draw("P SAME")
g3.Draw("P SAME")
leg.Draw()
# AddLabel(0.2,0.26,"#hat{q} = #hat{q}_{h}/z_{h} with a 3 Parameter Fit")
# AddLabel(0.2, 0.2, "Fixed cross section #sigma_{ph} = 40 [mbarn]")
c.Print(fileout)
