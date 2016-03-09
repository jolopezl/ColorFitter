#!/usr/bin/python
from numpy import loadtxt
from array import array
import sys, os, ROOT

values = []
values.append([]) # position 0 for 3 parameter fits
values.append([]) # position 1 for 4 parameter fits

errors = []
errors.append([])
errors.append([])

values[0].append( array("f",[2.287781766, 1.134511264, 0.490208758, 0.419877037]) ) # unsubtracted
values[0].append( array("f",[1.439136856, 0.86423568,  0.32681735,  0.297840314]) ) # rho =  0.0
values[0].append( array("f",[1.583986546, 0.997879765, 0.377075587, 0.321974829]) ) # rho = -0.5
values[0].append( array("f",[1.762573424, 1.186224459, 0.489362825, 0.371093161]) ) # rho = -1.0

errors[0].append( array("f",[0,0,0,0]) ) # unsubtracted
errors[0].append( array("f",[0,0,0,0]) ) # rho =  0.0
errors[0].append( array("f",[0,0,0,0]) ) # rho = -0.5
errors[0].append( array("f",[0,0,0,0]) ) # rho = -1.0

values[1].append( array("f",[3.424659529, 1.645792305, 0.45516461,  0.515535979]) ) # unsubtracted
values[1].append( array("f",[2.158231074, 1.229392776, 0.23027471,  0.336269652]) ) # rho =  0.0
values[1].append( array("f",[2.374500883, 1.441772115, 0.311304842, 0.373639384]) ) # rho = -0.5
values[1].append( array("f",[2.640686749, 1.750390569, 0.490944829, 0.449596266]) ) # rho = -1.0

errors[1].append( array("f",[0,0,0,0]) ) # unsubtracted
errors[1].append( array("f",[0,0,0,0]) ) # rho =  0.0
errors[1].append( array("f",[0,0,0,0]) ) # rho = -0.5
errors[1].append( array("f",[0,0,0,0]) ) # rho = -1.0

def retrieveTGraphErrors(i,par,nop):
  # dx = 0.01*(i-2)
  dx=0
  xval = array("f",[0.32+dx,0.53+dx,0.75+dx,0.94+dx])
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
ROOT.gStyle.SetPadRightMargin(0.05)
ROOT.gStyle.SetPadLeftMargin(0.125)
ROOT.gStyle.SetPadBottomMargin(0.16)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptTitle(0)
ROOT.gStyle.SetEndErrorSize(7.5)

# Configuration
xlabel = "z"
# CHI2 configuration
ylabel_up = "#chi^{2}/^{}DOF _{3P}"
ylabel_down = "#chi^{2}/^{}DOF _{4P}"
parameter = "chi2"
fileout = "fig05.pdf"
x0 = 0.5
y0 = 0.6 + 0.05
x1 = 0.9
y1 = 0.85 + 0.05
ylo = 0.15
yhi = 3.75
# ylo = -0.029
# yhi = 0.029

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
leg = ROOT.TLegend(x0,y0,x1,y1)
leg.SetTextFont(43)
leg.SetTextSize(28)
leg.SetBorderSize(0)
for i in range(4):
  leg.AddEntry(plt3P[i],legends[i],"ep")
fontAxesSize = 28
fontAxesCode = 43
plt3P[0].GetXaxis().SetTitleFont(fontAxesCode)
plt3P[0].GetXaxis().SetTitleSize(fontAxesSize)
plt3P[0].GetXaxis().SetLabelFont(fontAxesCode)
plt3P[0].GetXaxis().SetLabelSize(fontAxesSize)
plt3P[0].GetYaxis().SetTitleFont(fontAxesCode)
plt3P[0].GetYaxis().SetTitleSize(fontAxesSize)
plt3P[0].GetYaxis().SetLabelFont(fontAxesCode)
plt3P[0].GetYaxis().SetLabelSize(fontAxesSize)
plt4P[0].GetXaxis().SetTitleFont(fontAxesCode)
plt4P[0].GetXaxis().SetTitleSize(fontAxesSize)
plt4P[0].GetXaxis().SetLabelFont(fontAxesCode)
plt4P[0].GetXaxis().SetLabelSize(fontAxesSize)
plt4P[0].GetYaxis().SetTitleFont(fontAxesCode)
plt4P[0].GetYaxis().SetTitleSize(fontAxesSize)
plt4P[0].GetYaxis().SetLabelFont(fontAxesCode)
plt4P[0].GetYaxis().SetLabelSize(fontAxesSize)
# axes range
plt3P[0].GetYaxis().SetRangeUser(ylo,yhi)
plt4P[0].GetYaxis().SetRangeUser(ylo,yhi)
plt3P[0].GetYaxis().SetTitleOffset(1.75)
plt4P[0].GetYaxis().SetTitleOffset(1.75)
plt4P[0].GetXaxis().SetTitleOffset(1.5)
#
c.Divide(1,2,0,0)
c.cd(1)
ROOT.gPad.SetBottomMargin(0.001)
ROOT.gPad.SetTopMargin(0.01)
ROOT.gPad.SetRightMargin(0.01)
plt3P[0].Draw("AP")
plt3P[1].Draw("P SAME")
plt3P[2].Draw("P SAME")
plt3P[3].Draw("P SAME")
# for i in range(4):
#   plt3P[i].Fit("pol0","N0")
c.cd(2)
ROOT.gPad.SetTopMargin(0.001)
ROOT.gPad.SetRightMargin(0.01)
plt4P[0].Draw("AP")
plt4P[1].Draw("P SAME")
plt4P[2].Draw("P SAME")
plt4P[3].Draw("P SAME")
# for i in range(4):
#   plt4P[i].Fit("pol0","N0")
leg.Draw()
c.Print(fileout)