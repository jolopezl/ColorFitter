#!/usr/bin/python
from numpy import loadtxt
from array import array
import sys, os, ROOT

from AtlasStyle import SetAtlasStyle, AddLabel
SetAtlasStyle()

factor = 1.

values = []
values.append([]) # position 0 for 3 parameter fits
values.append([]) # position 1 for 4 parameter fits

errors = []
errors.append([])
errors.append([])

values[0].append( array("f",[0,0,0,0]) ) # unsubtracted
values[0].append( array("f",[0,0,0,0]) ) # rho =  0.0
values[0].append( array("f",[0,0,0,0]) ) # rho = -0.5
values[0].append( array("f",[0,0,0,0]) ) # rho = -1.0

errors[0].append( array("f",[0,0,0,0]) ) # unsubtracted
errors[0].append( array("f",[0,0,0,0]) ) # rho =  0.0
errors[0].append( array("f",[0,0,0,0]) ) # rho = -0.5
errors[0].append( array("f",[0,0,0,0]) ) # rho = -1.0

values[1].append( array("f",[0.008497238,-0.086342572,-0.039538395,-0.036207375,]) ) # unsubtracted
values[1].append( array("f",[0.023970141,-0.09027767,-0.096765855,-0.070503146,]) ) # rho =  0.0
values[1].append( array("f",[0.019596812,-0.088084703,-0.108753775,-0.079385432,]) ) # rho = -0.5
values[1].append( array("f",[0.014759475,-0.084527834,-0.1117634,-0.046867095,]) ) # rho = -1.0

errors[1].append( array("f",[0.056258988,0.097967776,0.056029048,0.051966122]) ) # unsubtracted
errors[1].append( array("f",[0.138624751,0.112212584,0.174856466,0.173052092]) ) # rho =  0.0
errors[1].append( array("f",[0.058490901,0.105839395,0.218933457,0.170064816]) ) # rho = -0.5
errors[1].append( array("f",[0.062959199,0.097159853,0.198981891,0.088536499]) ) # rho = -1.0

offset = 0.0075
dx = [-3*offset/2.,-offset/2.,offset/2.,3*offset/2.]

def retrieveTGraphErrors(i,par,nop):
  # dx=0
  xval = array("f",[0.32+dx[i],0.53+dx[i],0.75+dx[i],0.94+dx[i]])
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
xlabel = "z_{h}"

# dz energy loss
ylabel_up = "#Deltaz"
ylabel_down = "#Deltaz"
parameter = "dz"
fileout = "fig04d_dz.pdf" #sys.argv[3]


ylo = -0.35
yhi = 0.35

markerSize = 2.0
lineWidth = 3

legends = ["Uncorrected","He subtracted #rho =  0.0","He subtracted #rho = -0.5","He subtracted #rho = -1.0"]
############# code
c = ROOT.TCanvas("canvas","canvas",800,600)
color = [1,2,4,8]
plt3P = []
plt4P = []
for i in range(4):
  plt3P.append(retrieveTGraphErrors(i,parameter,"3P"))
  plt3P[i].SetMarkerStyle(20+i)
  plt3P[i].SetMarkerColor(color[i]) 
  plt3P[i].SetLineColor(color[i])
  # plt3P[i].SetLineWidth(lineWidth)
  plt3P[i].GetXaxis().SetTitle(xlabel)
  plt3P[i].GetYaxis().SetTitle(ylabel_up)
  plt3P[i].GetYaxis().SetTitleOffset(1.5)
  plt4P.append(retrieveTGraphErrors(i,parameter,"4P"))
  plt4P[i].SetMarkerStyle(20+i)
  plt4P[i].SetMarkerColor(color[i]) 
  plt4P[i].SetLineColor(color[i])
  # plt4P[i].SetLineWidth(lineWidth)
  plt4P[i].GetXaxis().SetTitle(xlabel)
  plt4P[i].GetYaxis().SetTitle(ylabel_down)
  plt4P[i].GetYaxis().SetTitleOffset(1.5)

  plt3P[i].GetYaxis().SetNdivisions(5+100*5);
  plt4P[i].GetYaxis().SetNdivisions(5+100*5);

fontAxesSize = 28
fontAxesCode = 43
# axes range
plt3P[0].GetYaxis().SetRangeUser(ylo,yhi)
plt4P[0].GetYaxis().SetRangeUser(ylo,yhi)
plt4P[0].GetYaxis().SetTitleOffset(0.75)
# plt4P[0].GetXaxis().SetTitleOffset(1.5)
#
# c.Divide(1,2,0,0)
# c.cd(1)
# ROOT.gPad.SetBottomMargin(0.001)
# ROOT.gPad.SetTopMargin(0.01)
# ROOT.gPad.SetRightMargin(0.01)
# plt3P[0].Draw("AP")
# plt3P[1].Draw("P SAME")
# plt3P[2].Draw("P SAME")
# plt3P[3].Draw("P SAME")
# c.cd(2)
# ROOT.gPad.SetTopMargin(0.001)
# ROOT.gPad.SetRightMargin(0.01)

line00 = ROOT.TF1("line00","00",0.0,1.0);
line00.SetLineWidth(2);
line00.SetLineColor(1);
line00.SetLineStyle(2);
line00.GetYaxis().SetRangeUser(ylo,yhi)
line00.GetYaxis().SetRangeUser(ylo,yhi)
line00.GetXaxis().SetTitleOffset(1.5)

x0 = 0.55-0.02
y0 = 0.75
x1 = x0 + 0.3-0.02
y1 = y0 + 0.15
leg = ROOT.TLegend(x0,y0,x1,y1)
leg.SetTextFont(43)
leg.SetTextSize(28)
leg.SetBorderSize(0)
leg.SetFillStyle(0)
for i in range(4):
  leg.AddEntry(plt3P[i],legends[i],"ep")

text1 = ROOT.TLatex()
text1.SetNDC()
text1.SetTextFont(43)
text1.SetTextSize(fontAxesSize)

plt4P[0].Draw("AP")
line00.Draw("SAME")
plt4P[1].Draw("P SAME")
plt4P[2].Draw("P SAME")
plt4P[3].Draw("P SAME")
leg.Draw()
AddLabel(0.2,0.88,"4 Parameter Fit (BLE)")
c.Print(fileout)