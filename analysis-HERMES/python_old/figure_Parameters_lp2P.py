#!/usr/bin/python
from numpy import loadtxt
from array import array
import sys, os, ROOT
factor = 1.

val1 = array("f",[14.89191345,7.080143499,3.029804261,1.992745574])  # rho = 0.0 3P
val2 = array("f",[9.50174555,7.239484549,5.388096332,3.033429451])      # rho = 0.0 fixed cross section 40 mbarn
val3 = array("f",[8.156268927,6.11454026,4.45823924,2.352734198])     # rho = 0.0 fixed cross section 30 mbarn

val4 = array("f",[12.12615213,6.136720473,3.404236507,1.694836305]) # rho = 0.0 fixed cross section 40 mbarn with energy loss
val5 = array("f",[11.52592869,5.508979276,2.84003639,1.121133062]) # rho = 0.0 fixed cross section 30 mbarn with energy loss

err1 = array("f",[15.58210515,5.559773446,4.6716252,2.849262832])  # rho =  0.0 3P
err2 = array("f",[1.970533965,1.064247156,0.869821482,0.497393965])     # rho = 0.0 fixed cross section 40 mbarn
err3 = array("f",[1.759058613,0.943243185,0.772106194,0.450814849])       # rho = 0.0 fixed cross section 30 mbarn

err4 = array("f",[9.881838808,2.727141719,1.715237301,1.34170283]) # rho = 0.0 fixed cross section 40 mbarn with energy loss
err5 = array("f",[9.417060244,2.603135902,1.625346778,1.488339746]) # rho = 0.0 fixed cross section 30 mbarn with energy loss

xval = array("f",[0.32,0.53,0.75,0.94])
xerr = array("f",[0,0,0,0])
xval1 = array("f",[0,0,0,0])
xval2 = array("f",[0,0,0,0])
xval3 = array("f",[0,0,0,0])
xval4 = array("f",[0,0,0,0])
xval5 = array("f",[0,0,0,0])

offset = 0.0075
offset = 0.01
offset = offset/2
for i in range(4):   
  xval1[i] = xval[i]
  xval2[i] = xval[i] - 3*offset
  xval3[i] = xval[i] + 3*offset
  xval4[i] = xval[i] - offset
  xval5[i] = xval[i] + offset 

g1 = ROOT.TGraphErrors(4,xval1,val1,xerr,err1)
g2 = ROOT.TGraphErrors(4,xval2,val2,xerr,err2)
g3 = ROOT.TGraphErrors(4,xval3,val3,xerr,err3)
g4 = ROOT.TGraphErrors(4,xval4,val4,xerr,err4)
g5 = ROOT.TGraphErrors(4,xval5,val5,xerr,err5)


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

ylo = -2.5
yhi = 32

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
g1.SetLineWidth(lineWidth)
g1.GetXaxis().SetTitle(xlabel)
g1.GetYaxis().SetTitle(ylabel)
g1.GetYaxis().SetTitleOffset(0.75)
i = 1
g2.SetMarkerStyle(20+i)
g2.SetMarkerSize(markerSize)
g2.SetMarkerColor(color[i]) 
g2.SetLineColor(color[i])
g2.SetLineWidth(lineWidth)
g2.GetXaxis().SetTitle(xlabel)
g2.GetYaxis().SetTitle(ylabel)
g2.GetYaxis().SetTitleOffset(0.75)
i = 2
g3.SetMarkerStyle(20+i)
g3.SetMarkerSize(markerSize)
g3.SetMarkerColor(color[i]) 
g3.SetLineColor(color[i])
g3.SetLineWidth(lineWidth)
g3.GetXaxis().SetTitle(xlabel)
g3.GetYaxis().SetTitle(ylabel)
g3.GetYaxis().SetTitleOffset(0.75)
i = 3
g4.SetMarkerStyle(20+i)
g4.SetMarkerSize(markerSize+0.75)
g4.SetMarkerColor(color[i]) 
g4.SetLineColor(color[i])
g4.SetLineWidth(lineWidth)
g4.GetXaxis().SetTitle(xlabel)
g4.GetYaxis().SetTitle(ylabel)
g4.GetYaxis().SetTitleOffset(0.75)
i = 4
g5.SetMarkerStyle(33)
g5.SetMarkerSize(markerSize+0.75)
g5.SetMarkerColor(color[i]) 
g5.SetLineColor(color[i])
g5.SetLineWidth(lineWidth)
g5.GetXaxis().SetTitle(xlabel)
g5.GetYaxis().SetTitle(ylabel)
g5.GetYaxis().SetTitleOffset(0.75)

g1.GetYaxis().SetNdivisions(5+100*5);
g2.GetYaxis().SetNdivisions(5+100*5);


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

x0 = 0.425
y0 = 0.58
x1 = x0 + 0.3
y1 = y0 + 0.3
leg = ROOT.TLegend(x0,y0,x1,y1)
leg.SetTextFont(43)
leg.SetTextSize(28)
leg.SetBorderSize(0)
leg.SetFillStyle(0)
leg.SetHeader("He subtracted #rho = 0.0")
leg.AddEntry(g1,"3P  - free #sigma_{ph} - #Deltaz = 0","ep")
leg.AddEntry(g2,"2P  - #sigma_{ph} = 40 [mbarn]","ep")
leg.AddEntry(g3,"2P  - #sigma_{ph} = 30 [mbarn]","ep")
leg.AddEntry(g4,"3P* - #sigma_{ph} = 40 [mbarn] free #Deltaz","ep")
leg.AddEntry(g5,"3P* - #sigma_{ph} = 30 [mbarn] free #Deltaz","ep")

text1 = ROOT.TLatex()
text1.SetNDC()
text1.SetTextFont(43)
text1.SetTextSize(fontAxesSize)

g1.Draw("AP")
g2.Draw("P SAME")
g3.Draw("P SAME")
g4.Draw("P SAME")
g5.Draw("P SAME")
leg.Draw()
# text1.DrawLatex(0.17,0.85,"He subtracted #rho = 0.0")
c.Print(fileout)