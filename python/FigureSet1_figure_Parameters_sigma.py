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

values[0].append( array("f",[321.912272,  44.12992721, 18.08344504, 24.98647915]) ) # unsubtracted
values[0].append( array("f",[155.928215,  38.41367971, 19.51217989, 25.90466669]) ) # rho =  0.0
values[0].append( array("f",[184.058854,  41.41878193, 20.0098872,  26.0476387]) ) # rho = -0.5
values[0].append( array("f",[228.1761888, 45.61409581, 20.90185032, 26.38412097]) ) # rho = -1.0

errors[0].append( array("f",[359.2265356,55.67064829,26.7360229,25.86490465]) ) # unsubtracted
errors[0].append( array("f",[288.8089248,52.57768348,26.70406836,28.13699807]) ) # rho =  0.0
errors[0].append( array("f",[274.0898039,52.41050185,23.26176394,28.1959846]) ) # rho = -0.5
errors[0].append( array("f",[257.8719775,67.79902084,28.89728351,32.59142606]) ) # rho = -1.0

values[1].append( array("f",[399.5513201,397.9858632,23.45143611,37.21908878]) ) # unsubtracted
values[1].append( array("f",[396.3541695,385.4976906,171.6206303,150.1345343]) ) # rho =  0.0
values[1].append( array("f",[399.6938622,387.3063491,227.2951723,193.7940624]) ) # rho = -0.5
values[1].append( array("f",[398.886293,366.5469273,249.0802896,23.8339861]) ) # rho = -1.0

errors[1].append( array("f",[361.6060231,364.4155968,44.23396039,67.22150109,]) ) # unsubtracted
errors[1].append( array("f",[200.6929694,255.942428,281.0169835,290.8718307,]) ) # rho =  0.0
errors[1].append( array("f",[200.3977299,349.0317648,278.1828202,279.9607114,]) ) # rho = -0.5
errors[1].append( array("f",[321.082018,279.0394081,275.1074907,21.28889001,]) ) # rho = -1.0

a = 0.0075
dx = [-3*a/2.,-a/2.,a/2.,3*a/2.]

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
# Cross section
ylabel_up = "#sigma_{ph} [mbarn]_{3P}"
ylabel_down = "#sigma_{ph} [mbarn]_{4P}"

ylabel = "#sigma_{ph} [mbarn]"
ylabel_up = ylabel
ylabel_down = ylabel

parameter = "sigma"
fileout = "fig04c_sigma.pdf" #sys.argv[3]
x0 = 0.5
y0 = 0.6 + 0.05
x1 = 0.9
y1 = 0.85 + 0.05
ylo = -150
yhi = 900

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
  plt3P[i].GetXaxis().SetTitle(xlabel)
  plt3P[i].GetYaxis().SetTitle(ylabel_up)
  plt3P[i].GetYaxis().SetTitleOffset(1.5)
  plt4P.append(retrieveTGraphErrors(i,parameter,"4P"))
  plt4P[i].SetMarkerStyle(20+i)
  plt4P[i].SetMarkerColor(color[i]) 
  plt4P[i].SetLineColor(color[i])
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
# axes range
plt3P[0].GetYaxis().SetRangeUser(ylo,yhi)
plt4P[0].GetYaxis().SetRangeUser(ylo,yhi)
plt4P[0].GetXaxis().SetTitleOffset(1.5)
#
line40 = ROOT.TF1("line40","40",0.0,1.0);
line40.SetLineWidth(2);
line40.SetLineColor(1);
line40.SetLineStyle(2);

line40.GetYaxis().SetRangeUser(ylo,yhi)
line40.GetYaxis().SetRangeUser(ylo,yhi)
line40.GetXaxis().SetTitleOffset(1.5)

x0 = 0.56-0.01
y0 = 0.7
x1 = x0 + 0.3-0.01
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
line40.Draw("SAME");
plt3P[1].Draw("P SAME")
plt3P[2].Draw("P SAME")
plt3P[3].Draw("P SAME")
text1.DrawLatex(0.2,0.88,"3 Parameter Fit")
leg.Draw()
c.cd(2)
ROOT.gPad.SetTopMargin(0.001)
ROOT.gPad.SetRightMargin(0.01)
plt4P[0].Draw("AP")
line40.Draw("SAME");
plt4P[1].Draw("P SAME")
plt4P[2].Draw("P SAME")
plt4P[3].Draw("P SAME")
AddLabel(0.2,0.88,"4 Parameter Fit")

c.Print(fileout)