#!/usr/bin/python
from numpy import loadtxt
from array import array
import sys, os, ROOT

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

values[1].append( array("f",[-0.011283372, -0.026647436, -0.066144118, -0.018588115]) ) # unsubtracted
values[1].append( array("f",[-0.002802976, -0.030409575, -0.056962346, -0.018320743]) ) # rho =  0.0
values[1].append( array("f",[-0.005235504, -0.018375814, -0.056024581, -0.018320984]) ) # rho = -0.5
values[1].append( array("f",[-0.007088794, -0.036870089, -0.054087861, -0.018069479]) ) # rho = -1.0

errors[1].append( array("f",[0.074671959, 0.094380494, 0.103986215, 0.039909578]) ) # unsubtracted
errors[1].append( array("f",[0.084725235, 0.103987234, 0.121343651, 0.040199065]) ) # rho =  0.0
errors[1].append( array("f",[0.08187597,  0.080513466, 0.12070617,  0.040000753]) ) # rho = -0.5
errors[1].append( array("f",[0.079628074, 0.086322027, 0.115140559, 0.038905246]) ) # rho = -1.0

def retrieveTGraphErrors(i,par,nop):
  dx = 0.0075*(i-1.5)
  # dx=0
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
xlabel = "z_{h}"

# dz energy loss
ylabel_up = "#Delta z_{3P}"
ylabel_down = "#Delta z_{4P}"
parameter = "dz"
fileout = "fig04d.pdf" #sys.argv[3]
x0 = 0.5
y0 = 0.6
x1 = 0.9
y1 = 0.85
ylo = -0.19
yhi = 0.25

markerSize = 2.0
lineWidth = 3

legends = ["Uncorrected","He subtracted #rho =  0.0","He subtracted #rho = -0.5","He subtracted #rho = -1.0"]
############# code
c = ROOT.TCanvas("canvas","canvas",800,400)
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

  plt3P[i].GetYaxis().SetNdivisions(5+100*5);
  plt4P[i].GetYaxis().SetNdivisions(5+100*5);

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
line00.GetXaxis().SetTitleFont(fontAxesCode)
line00.GetXaxis().SetTitleSize(fontAxesSize)
line00.GetXaxis().SetLabelFont(fontAxesCode)
line00.GetXaxis().SetLabelSize(fontAxesSize)
line00.GetYaxis().SetTitleFont(fontAxesCode)
line00.GetYaxis().SetTitleSize(fontAxesSize)
line00.GetYaxis().SetLabelFont(fontAxesCode)
line00.GetYaxis().SetLabelSize(fontAxesSize)
line00.GetYaxis().SetRangeUser(ylo,yhi)
line00.GetYaxis().SetRangeUser(ylo,yhi)
line00.GetXaxis().SetTitleOffset(1.5)

plt4P[0].Draw("AP")
line00.Draw("SAME")
plt4P[1].Draw("P SAME")
plt4P[2].Draw("P SAME")
plt4P[3].Draw("P SAME")
leg.Draw()
c.Print(fileout)