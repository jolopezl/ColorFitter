#!/usr/bin/python
from numpy import loadtxt
from array import array
import sys, os, ROOT

from AtlasStyle import SetAtlasStyle, AddLabel
SetAtlasStyle()

values = []
values.append([]) # position 0 for 3 parameter fits
values.append([]) # position 1 for 4 parameter fits

errors = []
errors.append([])
errors.append([])

values[0].append( array("f",[2.287781766,1.134511257,0.490208758,0.419877037]) ) # unsubtracted
values[0].append( array("f",[1.439136856,0.864235678,0.326817342,0.297840314]) ) # rho =  0.0
values[0].append( array("f",[1.583986536,0.997879765,0.377075587,0.321974829]) ) # rho = -0.5
values[0].append( array("f",[1.762573426,1.186224459,0.489362825,0.371093161]) ) # rho = -1.0

errors[0].append( array("f",[0,0,0,0]) ) # unsubtracted
errors[0].append( array("f",[0,0,0,0]) ) # rho =  0.0
errors[0].append( array("f",[0,0,0,0]) ) # rho = -0.5
errors[0].append( array("f",[0,0,0,0]) ) # rho = -1.0

values[1].append( array("f",[3.425385433,1.520533906,0.451327273,0.313829407]) ) # unsubtracted
values[1].append( array("f",[2.137191558,1.12430168,0.183660046,0.121672328]) ) # rho =  0.0
values[1].append( array("f",[2.358594386,1.319393743,0.252515182,0.155919062]) ) # rho = -0.5
values[1].append( array("f",[2.631371177,1.598463538,0.408925707,0.258576782]) ) # rho = -1.0

errors[1].append( array("f",[0,0,0,0]) ) # unsubtracted
errors[1].append( array("f",[0,0,0,0]) ) # rho =  0.0
errors[1].append( array("f",[0,0,0,0]) ) # rho = -0.5
errors[1].append( array("f",[0,0,0,0]) ) # rho = -1.0

def retrieveTGraphErrors(i,par,nop):
  xval = array("f",[0.32,0.53,0.75,0.94])
  xerr = array("f",[0,0,0,0])
  if(nop == "3P"):
    yval = values[0][i]
    yerr = errors[0][i]
  elif(nop == "4P"):
    yval = values[1][i]
    yerr = errors[1][i]
  gg = ROOT.TGraphErrors(4,xval,yval,xerr,yerr)
  return gg

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
xlabel = "z"
# CHI2 configuration
ylabel_up = "#chi^{2}/^{}DOF"
ylabel_down = "#chi^{2}/^{}DOF"
parameter = "chi2"
fileout = "fig04e_chi2.pdf"

ylo = 0.01
yhi = 3.6

markerSize = 2.0
lineWidth = 3

legends = ["Uncorrected","He subtracted #rho =  0.0","He subtracted #rho = -0.5","He subtracted #rho = -1.0"]
############# code
c = ROOT.TCanvas("canvas","canvas",800,800)
color = [1,2,4,8]
plt3P = []
plt4P = []
for i in range(4):
  plt3P.append(retrieveTGraphErrors(i,parameter,"3P"))
  plt3P[i].SetMarkerStyle(20+i)
  plt3P[i].SetMarkerSize(markerSize)
  plt3P[i].SetMarkerColor(color[i]) 
  plt3P[i].SetLineColor(color[i])
  plt3P[i].SetLineWidth(lineWidth)
  plt3P[i].GetXaxis().SetTitle(xlabel)
  plt3P[i].GetYaxis().SetTitle(ylabel_up)
  plt3P[i].GetYaxis().SetTitleOffset(1.5)
  plt4P.append(retrieveTGraphErrors(i,parameter,"4P"))
  plt4P[i].SetMarkerStyle(20+i)
  plt4P[i].SetMarkerSize(markerSize)
  plt4P[i].SetMarkerColor(color[i]) 
  plt4P[i].SetLineColor(color[i])
  plt4P[i].SetLineWidth(lineWidth)
  plt4P[i].GetXaxis().SetTitle(xlabel)
  plt4P[i].GetYaxis().SetTitle(ylabel_down)
  plt4P[i].GetYaxis().SetTitleOffset(1.5)


x0 = 0.56-0.01
y0 = 0.6
x1 = x0 + 0.3-0.01
y1 = y0 + 0.25
leg = ROOT.TLegend(x0,y0,x1,y1)
leg.SetTextFont(43)
leg.SetTextSize(28)
leg.SetBorderSize(0)
leg.SetFillStyle(0)

for i in range(4):
  leg.AddEntry(plt3P[i],legends[i],"ep")
fontAxesSize = 28
fontAxesCode = 43
# axes range
plt3P[0].GetYaxis().SetRangeUser(ylo,yhi)
plt4P[0].GetYaxis().SetRangeUser(ylo,yhi)
plt3P[0].GetYaxis().SetTitleOffset(1.75)
plt4P[0].GetYaxis().SetTitleOffset(1.75)
plt4P[0].GetXaxis().SetTitleOffset(1.5)
#


text1 = ROOT.TLatex()
text1.SetNDC()
text1.SetTextFont(43)
text1.SetTextSize(fontAxesSize)



c.Divide(1,2,0,0)
c.cd(1)
ROOT.gPad.SetBottomMargin(0.001)
ROOT.gPad.SetTopMargin(0.01)
ROOT.gPad.SetRightMargin(0.01)
plt3P[0].Draw("AP")
plt3P[1].Draw("P SAME")
plt3P[2].Draw("P SAME")
plt3P[3].Draw("P SAME")
text1.DrawLatex(0.27,0.88,"3 Parameter Fit (BL)")
# for i in range(4):
#   plt3P[i].Fit("pol0","N0")
c.cd(2)
ROOT.gPad.SetTopMargin(0.001)
ROOT.gPad.SetRightMargin(0.01)
plt4P[0].Draw("AP")
plt4P[1].Draw("P SAME")
plt4P[2].Draw("P SAME")
plt4P[3].Draw("P SAME")
text1.DrawLatex(0.27,0.91,"4 Parameter Fit (BLE)")
# for i in range(4):
#   plt4P[i].Fit("pol0","N0")
leg.Draw()
c.Print(fileout)