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

values[0].append( array("f",[17.17233478,7.642162395,2.773159332,1.898814839]) ) # unsubtracted
values[0].append( array("f",[14.90299282,7.04932036,3.007188085,1.99198312]) ) # rho =  0.0
values[0].append( array("f",[15.47969688,7.384555532,3.116273594,2.007340508]) ) # rho = -0.5
values[0].append( array("f",[16.13567581,7.75952233,3.264025024,2.033672257]) ) # rho = -1.0

errors[0].append( array("f",[11.69656677,5.018397119,5.035155052,2.645156007]) ) # unsubtracted
errors[0].append( array("f",[9.797059021,5.303053065,4.121854244,2.808611336]) ) # rho =  0.0
errors[0].append( array("f",[19.53834759,5.061047353,3.944393404,2.846501988]) ) # rho = -0.5
errors[0].append( array("f",[9.589701073,5.247577008,3.869236946,2.679820728]) ) # rho = -1.0

values[1].append( array("f",[17.98658239,7.053854886,1.459275736,1.36880465]) ) # unsubtracted
values[1].append( array("f",[15.12749648,6.643573121,2.078651119,1.419206332]) ) # rho =  0.0
values[1].append( array("f",[15.79198295,6.943995315,2.150188325,1.430497641]) ) # rho = -0.5
values[1].append( array("f",[16.5955688,7.714527203,2.313099633,1.455922586]) ) # rho = -1.0

errors[1].append( array("f",[12.68161521,4.298022361,5.123075743,2.618483253]) ) # unsubtracted
errors[1].append( array("f",[11.85766816,4.251289192,3.947859605,2.718563503]) ) # rho =  0.0
errors[1].append( array("f",[12.59845864,4.604401637,4.536823313,2.65831863]) ) # rho = -0.5
errors[1].append( array("f",[12.65018279,4.490785816,4.041930567,2.274777654]) ) # rho = -1.0

def retrieveTGraphErrors(i,par,nop):
  dx = 0.0075*(i-1.5)
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
# L_P configuration
ylabel_up = "l_{p} [fm]_{3P}"
ylabel_down = "l_{p} [fm]_{4P}"
parameter = "lp"
fileout = "fig04b.pdf" #sys.argv[3]
x0 = 0.5
y0 = 0.6
x1 = 0.9
y1 = 0.85
ylo = -9
yhi = 36

legends = ["Uncorrected","He subtracted #rho =  0.0","He subtracted #rho = -0.5","He subtracted #rho = -1.0"]
############# code
c = ROOT.TCanvas("canvas","canvas",800,800)
color = [1,2,4,8]
plt3P = []
plt4P = []
for i in range(4):
  plt3P.append(retrieveTGraphErrors(i,parameter,"3P"))
  plt3P[i].SetMarkerStyle(20+i)
  plt3P[i].SetMarkerSize(1.5)
  plt3P[i].SetMarkerColor(color[i]) 
  plt3P[i].SetLineColor(color[i])
  plt3P[i].SetLineWidth(2)
  plt3P[i].GetXaxis().SetTitle(xlabel)
  plt3P[i].GetYaxis().SetTitle(ylabel_up)
  plt3P[i].GetYaxis().SetTitleOffset(1.5)
  plt4P.append(retrieveTGraphErrors(i,parameter,"4P"))
  plt4P[i].SetMarkerStyle(20+i)
  plt4P[i].SetMarkerSize(1.5)
  plt4P[i].SetMarkerColor(color[i]) 
  plt4P[i].SetLineColor(color[i])
  plt4P[i].SetLineWidth(2)
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
c.cd(2)
ROOT.gPad.SetTopMargin(0.001)
ROOT.gPad.SetRightMargin(0.01)
plt4P[0].Draw("AP")
plt4P[1].Draw("P SAME")
plt4P[2].Draw("P SAME")
plt4P[3].Draw("P SAME")
# lundModel = ROOT.TF1("lund","x*(log(1/(x*x))-1+x*x)/(1-x*x)",0,1)
# lundModel.Draw("SAME")
leg.Draw()
c.Print(fileout)