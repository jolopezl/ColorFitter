#!/usr/bin/python
from numpy import loadtxt
from array import array
import sys, os, ROOT
factor = 1.

val1 = array("f",[1.938687537,2.448948249,1.393052958,1.32610177])  # rho = 0.0 3P (BL)
val2 = array("f",[1.960080704,2.382862333,1.131726636,1.076690994]) # rho = 0.0 BLE
val3 = array("f",[2.125454155,2.432882642,1.072942811,1.028574807]) # rho = 0.0 fixed cross section 40 mbarn
val4 = array("f",[2.212336101,2.570475157,1.152221654,1.19471209])  # rho = 0.0 fixed cross section 30 mbarn
val5 = array("f",[2.013385697,2.567153257,1.309393114,1.471376678]) # rho = 0.0 fixed cross section 40 mbarn with energy loss
val6 = array("f",[2.034191371,2.669101521,1.437872973,2.024431129]) # rho = 0.0 fixed cross section 30 mbarn with energy loss

err1 = array("f",[0.386524721,0.706124829,1.718347814,2.694773181])  # rho =  0.0 3P
err2 = array("f",[0.468834974,0.453703411,1.100816193,2.056530162]) # BLE
err3 = array("f",[0.219496572,0.396206752,1.031536588,1.953019171])  # rho = 0.0 fixed cross section 40 mbarn
err4 = array("f",[0.238980688,0.425794534,1.116852869,2.242302313])  # rho = 0.0 fixed cross section 30 mbarn
err5 = array("f",[0.376595945,0.562137198,1.304146158,2.792658242])  # rho = 0.0 fixed cross section 40 mbarn with energy loss
err6 = array("f",[0.393934159,0.629025801,1.461976975,5.921170572])  # rho = 0.0 fixed cross section 30 mbarn with energy loss

xval = array("f",[0.32,0.53,0.75,0.94])
xerr = array("f",[0,0,0,0])
xval1 = array("f",[0,0,0,0])
xval2 = array("f",[0,0,0,0])
xval3 = array("f",[0,0,0,0])
xval4 = array("f",[0,0,0,0])
xval5 = array("f",[0,0,0,0])
xval6 = array("f",[0,0,0,0])

offset = 0.01
offset = offset/2
for i in range(4):   
  xval1[i] = xval[i] - offset
  xval2[i] = xval[i] + offset
  xval3[i] = xval[i] - 2*offset
  xval4[i] = xval[i] + 2*offset
  xval5[i] = xval[i] - 3*offset
  xval6[i] = xval[i] + 3*offset 

g1 = ROOT.TGraphErrors(4,xval1,val1,xerr,err1)
g2 = ROOT.TGraphErrors(4,xval2,val2,xerr,err2)
g3 = ROOT.TGraphErrors(4,xval3,val3,xerr,err3)
g4 = ROOT.TGraphErrors(4,xval4,val4,xerr,err4)
g5 = ROOT.TGraphErrors(4,xval5,val5,xerr,err5)
g6 = ROOT.TGraphErrors(4,xval6,val6,xerr,err6)


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
ylabel = "q_{0} [GeV^{2}fm]"
parameter = "qhat"
fileout = "fig04a2p.pdf" #sys.argv[3]


ylo = -4.0
yhi = 9.15

markerSize = 2.0
lineWidth = 3

legends = ["Uncorrected","He subtracted #rho =  0.0","He subtracted #rho = -0.5","He subtracted #rho = -1.0"]
############# code
c = ROOT.TCanvas("canvas","canvas",800,600)
color = [1,2,4,8,9,12]
marker = []
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
g5.SetMarkerStyle(29)
g5.SetMarkerSize(markerSize+0.75)
g5.SetMarkerColor(color[i]) 
g5.SetLineColor(color[i])
g5.SetLineWidth(lineWidth)
g5.GetXaxis().SetTitle(xlabel)
g5.GetYaxis().SetTitle(ylabel)
g5.GetYaxis().SetTitleOffset(0.75)
i = 5
g6.SetMarkerStyle(33)
g6.SetMarkerSize(markerSize+0.75)
g6.SetMarkerColor(color[i]) 
g6.SetLineColor(color[i])
g6.SetLineWidth(lineWidth)
g6.GetXaxis().SetTitle(xlabel)
g6.GetYaxis().SetTitle(ylabel)
g6.GetYaxis().SetTitleOffset(0.75)

g1.GetYaxis().SetNdivisions(5+100*5);
g2.GetYaxis().SetNdivisions(5+100*5);
g3.GetYaxis().SetNdivisions(5+100*5);


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

x0 = 0.15
y0 = 0.58
x1 = x0 + 0.3
y1 = y0 + 0.315
leg = ROOT.TLegend(x0,y0,x1,y1)
leg.SetTextFont(43)
leg.SetTextSize(28)
leg.SetBorderSize(0)
leg.SetFillStyle(0)
leg.SetHeader("He subtracted #rho = 0.0")
# leg.AddEntry(g1,"3P  - free #sigma_{ph} - #Deltaz = 0","ep")
# leg.AddEntry(g2,"2P  - #sigma_{ph} = 40 [mbarn]","ep")
# leg.AddEntry(g3,"2P  - #sigma_{ph} = 30 [mbarn]","ep")
# leg.AddEntry(g4,"3P* - #sigma_{ph} = 40 [mbarn] free #Deltaz","ep")
# leg.AddEntry(g5,"3P* - #sigma_{ph} = 30 [mbarn] free #Deltaz","ep")
leg.AddEntry(g1,"BL","ep")
leg.AddEntry(g2,"BLE","ep")
leg.AddEntry(g3,"BL#sigma_{40}","ep")
leg.AddEntry(g4,"BL#sigma_{30}","ep")
leg.AddEntry(g5,"BLE#sigma_{40}","ep")
leg.AddEntry(g6,"BLE#sigma_{30}","ep")

g1.Draw("AP")
g2.Draw("P SAME")
g3.Draw("P SAME")
g4.Draw("P SAME")
g5.Draw("P SAME")
g6.Draw("P SAME")
leg.Draw()
c.Print(fileout)