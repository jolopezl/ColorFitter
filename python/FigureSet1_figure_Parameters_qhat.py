#!/usr/bin/python
from numpy import loadtxt
from array import array
import sys, os, ROOT

from AtlasStyle import SetAtlasStyle,AddLabel
SetAtlasStyle()

factor = 0.1*3./(4.*3.141592)

values = []
values.append([]) # position 0 for 3 parameter fits
values.append([]) # position 1 for 4 parameter fits

errors = []
errors.append([])
errors.append([])

values[0].append( array("f",[1.783259079,2.35910074,0.046824663,6.15E-07]) ) # unsubtracted
values[0].append( array("f",[1.938687537,2.448948249,1.393052958,1.32610177]) ) # rho =  0.0
values[0].append( array("f",[1.926978397,2.419270628,1.353904991,1.295141011]) ) # rho = -0.5
values[0].append( array("f",[1.917446575,2.385027347,1.290374082,1.246098182]) ) # rho = -1.0

errors[0].append( array("f",[0.232557913,0.554786187,8.745636603,6.653189239]) ) # unsubtracted
errors[0].append( array("f",[0.386524721,0.706124829,1.718347814,2.694773181]) ) # rho =  0.0
errors[0].append( array("f",[0.433949533,0.605368032,1.426427075,2.456219219]) ) # rho = -0.5
errors[0].append( array("f",[0.250634508,0.614172841,1.278535804,2.168140149]) ) # rho = -1.0

values[1].append( array("f",[1.79824157,2.330934153,0.052069603,4.23E-05]) ) # unsubtracted
values[1].append( array("f",[1.960080704,2.382862333,1.131726636,1.076690994]) ) # rho =  0.0
values[1].append( array("f",[1.948602678,2.375885323,1.106043011,1.034065338]) ) # rho = -0.5
values[1].append( array("f",[1.935007017,2.369727404,1.079419287,5.155405572]) ) # rho = -1.0

errors[1].append( array("f",[0.217728893,0.450412377,8.776851091,6.829139897]) ) # unsubtracted
errors[1].append( array("f",[0.468834974,0.453703411,1.100816193,2.056530162]) ) # rho =  0.0
errors[1].append( array("f",[0.241652716,0.44818071,0.908007271,1.806845322]) ) # rho = -0.5
errors[1].append( array("f",[0.24508155,0.407427979,0.730242733,5.355293349]) ) # rho = -1.0

for k in range(2):
  for j in range(4):
    for i in range(4):
      values[k][j][i] = values[k][j][i]/factor
      errors[k][j][i] = errors[k][j][i]/factor


offset = 0.0075
dx = [-3*offset/2.,-offset/2.,offset/2.,3*offset/2.]

def retrieveTGraphErrors(i,par,nop):
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
# Q-HAT configuration
# ylabel_up = "#hat{q}_{0} [GeV^{2}/fm^{2}]_{3P}"
# ylabel_down = "#hat{q}_{0} [GeV^{2}/fm^{2}]_{4P}"
ylabel_up = "q_{0} [GeV^{2}fm]_{3P}"
ylabel_down = "q_{0} [GeV^{2}fm]_{4P}"

ylabel = "q_{0} [GeV^{2}fm]"
ylabel_up = ylabel
ylabel_down = ylabel

parameter = "qhat"
fileout = "fig04a_q0.pdf"

ylo = -9.15/factor
yhi = 12.15/factor
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
  plt3P[i].SetMarkerColor(color[i]) 
  plt3P[i].SetLineColor(color[i])
  # plt3P[i].SetLineWidth(lineWidth)
  plt3P[i].GetXaxis().SetTitle(xlabel)
  plt3P[i].GetYaxis().SetTitle(ylabel_up)
  plt3P[i].GetYaxis().SetTitleOffset(1.6)
  plt4P.append(retrieveTGraphErrors(i,parameter,"4P"))
  plt4P[i].SetMarkerStyle(20+i)
  plt4P[i].SetMarkerColor(color[i]) 
  plt4P[i].SetLineColor(color[i])
  # plt4P[i].SetLineWidth(lineWidth)
  plt4P[i].GetXaxis().SetTitle(xlabel)
  plt4P[i].GetYaxis().SetTitle(ylabel_down)
  plt4P[i].GetYaxis().SetTitleOffset(1.6)

  # plt3P[i].GetYaxis().CenterTitle()
  # plt4P[i].GetYaxis().CenterTitle()
  plt3P[i].GetYaxis().SetNdivisions(5+100*5);
  plt4P[i].GetYaxis().SetNdivisions(5+100*5);

fontAxesSize = 28
fontAxesCode = 43
# axes range
plt3P[0].GetYaxis().SetRangeUser(ylo,yhi)
plt4P[0].GetYaxis().SetRangeUser(ylo,yhi)
# plt4P[0].GetXaxis().SetTitleOffset(1.5)
#

x0 = 0.2
y0 = 0.2
x1 = 0.5 - 0.025
y1 = 0.5 - 0.05
leg = ROOT.TLegend(x0,y0,x1,y1)
leg.SetTextFont(43)
leg.SetTextSize(28)
leg.SetBorderSize(0)
leg.SetFillStyle(0)
for i in range(4):
  leg.AddEntry(plt3P[i],legends[i],"ep")

c.Divide(1,2,0,0)
c.cd(1)
ROOT.gPad.SetBottomMargin(0.001)
ROOT.gPad.SetTopMargin(0.01)
ROOT.gPad.SetRightMargin(0.01)
plt3P[0].Draw("AP")
plt3P[1].Draw("P SAME")
plt3P[2].Draw("P SAME")
plt3P[3].Draw("P SAME")
AddLabel(0.2,0.88,"3 Parameter Fit (BL)")
c.cd(2)
ROOT.gPad.SetTopMargin(0.001)
ROOT.gPad.SetRightMargin(0.01)
plt4P[0].Draw("AP")
plt4P[1].Draw("P SAME")
plt4P[2].Draw("P SAME")
plt4P[3].Draw("P SAME")
AddLabel(0.2,0.88,"4 Parameter Fit (BLE)")
leg.Draw()
c.Print(fileout)