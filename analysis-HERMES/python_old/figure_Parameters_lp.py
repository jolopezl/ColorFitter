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

values[0].append( array("f",[17.17233538,7.642169684,2.773159309,1.898814839]) ) # unsubtracted
values[0].append( array("f",[14.89191345,7.080143499,3.029804261,1.992745574]) ) # rho =  0.0
values[0].append( array("f",[15.47969786,7.384555541,3.116272824,2.007340524]) ) # rho = -0.5
values[0].append( array("f",[16.14852056,7.764888143,3.260488256,2.037622748]) ) # rho = -1.0

errors[0].append( array("f",[11.69654194,5.015228056,5.035150103,2.645185622]) ) # unsubtracted
errors[0].append( array("f",[15.58210515,5.559773446,4.6716252,2.849262832]) ) # rho =  0.0
errors[0].append( array("f",[19.54493751,5.061058273,3.94521402,2.846501778]) ) # rho = -0.5
errors[0].append( array("f",[10.61208113,6.005538867,4.73475397,3.166020322]) ) # rho = -1.0

values[1].append( array("f",[16.24414192,7.960709884,2.195315793,1.555648739]) ) # unsubtracted
values[1].append( array("f",[13.93688552,7.766694217,4.681843459,2.833307188]) ) # rho =  0.0
values[1].append( array("f",[14.52839213,7.859992755,4.754904345,2.91724691]) ) # rho = -0.5
values[1].append( array("f",[15.22968645,7.933951975,4.793478075,0.372188791]) ) # rho = -1.0

errors[1].append( array("f",[9.167021331,3.73830411,5.279407987,3.51940753]) ) # unsubtracted
errors[1].append( array("f",[17.15041095,2.937900015,2.582794139,2.203179308]) ) # rho =  0.0
errors[1].append( array("f",[7.616333411,3.174514155,2.209867522,1.596171989]) ) # rho = -0.5
errors[1].append( array("f",[9.046051099,3.169133794,2.040423639,7.70218304]) ) # rho = -1.0

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
ROOT.gStyle.SetPadRightMargin(0.05)
ROOT.gStyle.SetPadLeftMargin(0.125)
ROOT.gStyle.SetPadBottomMargin(0.16)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptTitle(0)
ROOT.gStyle.SetEndErrorSize(7.5)

# Configuration
xlabel = "z_{h}"
# L_P configuration
ylabel_up = "L_{p} [fm]_{3P}"
ylabel_down = "L_{p} [fm]_{4P}"

ylabel = "L_{p} [fm]"
ylabel_up = ylabel
ylabel_down = ylabel

parameter = "lp"
fileout = "fig04b.pdf" #sys.argv[3]


ylo = -4.999
yhi = 36

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

  plt3P[i].GetYaxis().SetNdivisions(5+100*5);
  plt4P[i].GetYaxis().SetNdivisions(5+100*5);


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
plt4P[0].GetXaxis().SetTitleOffset(1.5)
#

x0 = 0.56
y0 = 0.7
x1 = x0 + 0.3
y1 = y0 + 0.25
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

c.Divide(1,2,0,0)
c.cd(1)
ROOT.gPad.SetBottomMargin(0.001)
ROOT.gPad.SetTopMargin(0.01)
ROOT.gPad.SetRightMargin(0.01)
plt3P[0].Draw("AP")
plt3P[1].Draw("P SAME")
plt3P[2].Draw("P SAME")
plt3P[3].Draw("P SAME")
text1.DrawLatex(0.17,0.91,"3 Parameter Fit")
c.cd(2)
ROOT.gPad.SetTopMargin(0.001)
ROOT.gPad.SetRightMargin(0.01)
plt4P[0].Draw("AP")
plt4P[1].Draw("P SAME")
plt4P[2].Draw("P SAME")
plt4P[3].Draw("P SAME")
text1.DrawLatex(0.17,0.91,"4 Parameter Fit")
leg.Draw()
c.Print(fileout)