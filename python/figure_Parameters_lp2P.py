#!/usr/bin/python
from numpy import loadtxt
from array import array
import sys, os, ROOT
factor = 1.

val1 = array("f",[14.89191323, 7.080143977, 3.02980576,  1.992745607])  # rho = 0.0 3P
val2 = array("f",[9.500856728,7.239264002,5.386166164,3.033630863])     # rho = 0.0 fixed cross section 40 mbarn
val3 = array("f",[7.292952595,5.382642303,3.853081538,1.901920671])     # rho = 0.0 fixed cross section 25 mbarn

err1 = array("f",[15.58214421, 5.559833717, 4.670434572, 2.849263584])  # rho =  0.0 3P
err2 = array("f",[1.969936809,1.062397257,0.864394749,0.496174411])     # rho = 0.0 fixed cross section
err3 = array("f",[1.612740326,0.866270272,0.712207577,0.419517937])     # rho = 0.0 fixed cross section 25 mbarn

xval = array("f",[0.32,0.53,0.75,0.94])
xerr = array("f",[0,0,0,0])
xval1 = array("f",[0,0,0,0])
xval2 = array("f",[0,0,0,0])
xval3 = array("f",[0,0,0,0])

offset = 0.0075
offset = offset/2
for i in range(4):   
  xval1[i] = xval[i]
  xval2[i] = xval[i] - offset
  xval3[i] = xval[i] + offset

g1 = ROOT.TGraphErrors(4,xval1,val1,xerr,err1)
g2 = ROOT.TGraphErrors(4,xval2,val2,xerr,err2)
g3 = ROOT.TGraphErrors(4,xval3,val3,xerr,err3)

a = 0.0075
dx = [-3*a/2.,-a/2.,a/2.,3*a/2.]

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
ylabel = "L_{p} [fm]"
parameter = "lp"
fileout = "fig04b2p.pdf" #sys.argv[3]
x0 = 0.5
y0 = 0.6 - 0.1
x1 = 0.9
y1 = 0.85 #+ 0.05
ylo = -4.999
yhi = 36

markerSize = 2.0
lineWidth = 3

legends = ["Uncorrected","He subtracted #rho =  0.0","He subtracted #rho = -0.5","He subtracted #rho = -1.0"]
############# code
c = ROOT.TCanvas("canvas","canvas",800,400)
color = [1,2,4,8]
i = 1
g1.SetMarkerStyle(20+i)
g1.SetMarkerSize(markerSize)
g1.SetMarkerColor(color[i]) 
g1.SetLineColor(color[i])
g1.SetLineWidth(lineWidth)
g1.GetXaxis().SetTitle(xlabel)
g1.GetYaxis().SetTitle(ylabel)
g1.GetYaxis().SetTitleOffset(0.75)
i = 2
g2.SetMarkerStyle(20+i)
g2.SetMarkerSize(markerSize)
g2.SetMarkerColor(color[i]) 
g2.SetLineColor(color[i])
g2.SetLineWidth(lineWidth)
g2.GetXaxis().SetTitle(xlabel)
g2.GetYaxis().SetTitle(ylabel)
g2.GetYaxis().SetTitleOffset(0.75)
i = 3
g3.SetMarkerStyle(20+i)
g3.SetMarkerSize(markerSize)
g3.SetMarkerColor(color[i]) 
g3.SetLineColor(color[i])
g3.SetLineWidth(lineWidth)
g3.GetXaxis().SetTitle(xlabel)
g3.GetYaxis().SetTitle(ylabel)
g3.GetYaxis().SetTitleOffset(0.75)

g1.GetYaxis().SetNdivisions(5+100*5);
g2.GetYaxis().SetNdivisions(5+100*5);

leg = ROOT.TLegend(x0,y0,x1,y1)
leg.SetTextFont(43)
leg.SetTextSize(28)
leg.SetBorderSize(0)
leg.SetHeader("He subtracted #rho = 0.0")
leg.AddEntry(g1,"3P - free #sigma_{ph}","ep")
leg.AddEntry(g2,"2P - #sigma_{ph} = 40 [mbarn]","ep")
leg.AddEntry(g3,"2P - #sigma_{ph} = 25 [mbarn]","ep")
fontAxesSize = 28
fontAxesCode = 43

g1.GetXaxis().SetTitleFont(fontAxesCode)
g1.GetXaxis().SetTitleSize(fontAxesSize)
g1.GetXaxis().SetLabelFont(fontAxesCode)
g1.GetXaxis().SetLabelSize(fontAxesSize)
g1.GetYaxis().SetTitleFont(fontAxesCode)
g1.GetYaxis().SetTitleSize(fontAxesSize)
g1.GetYaxis().SetLabelFont(fontAxesCode)
g1.GetYaxis().SetLabelSize(fontAxesSize)
g2.GetXaxis().SetTitleFont(fontAxesCode)
g2.GetXaxis().SetTitleSize(fontAxesSize)
g2.GetXaxis().SetLabelFont(fontAxesCode)
g2.GetXaxis().SetLabelSize(fontAxesSize)
g2.GetYaxis().SetTitleFont(fontAxesCode)
g2.GetYaxis().SetTitleSize(fontAxesSize)
g2.GetYaxis().SetLabelFont(fontAxesCode)
g2.GetYaxis().SetLabelSize(fontAxesSize)
g3.GetXaxis().SetTitleFont(fontAxesCode)
g3.GetXaxis().SetTitleSize(fontAxesSize)
g3.GetXaxis().SetLabelFont(fontAxesCode)
g3.GetXaxis().SetLabelSize(fontAxesSize)
g3.GetYaxis().SetTitleFont(fontAxesCode)
g3.GetYaxis().SetTitleSize(fontAxesSize)
g3.GetYaxis().SetLabelFont(fontAxesCode)
g3.GetYaxis().SetLabelSize(fontAxesSize)
# axes range
g1.GetXaxis().SetRangeUser(0.01,0.99)
g1.GetYaxis().SetRangeUser(ylo,yhi)
g2.GetYaxis().SetRangeUser(ylo,yhi)
g3.GetYaxis().SetRangeUser(ylo,yhi)
# g1.GetXaxis().SetTitleOffset(1.5)



g1.Draw("AP")
g2.Draw("P SAME")
g3.Draw("P SAME")
leg.Draw()
c.Print(fileout)