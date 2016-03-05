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

values[0].append( array("f",[321.912272,44.12992721,18.08344504,24.98647915]) ) # unsubtracted
values[0].append( array("f",[155.7160234,38.0841994,19.37761822,25.90003306]) ) # rho =  0.0
values[0].append( array("f",[184.058854,41.41878193,20.0098872,26.0476387]) ) # rho = -0.5
values[0].append( array("f",[226.7602114,45.54354196,20.90492348,26.3484768]) ) # rho = -1.0

errors[0].append( array("f",[359.2263148,55.70172103,26.7360517,25.86462152]) ) # unsubtracted
errors[0].append( array("f",[119.2619578,48.6419476,23.72866069,27.7583819]) ) # rho =  0.0
errors[0].append( array("f",[274.22988,52.41039975,23.25715415,28.19598746]) ) # rho = -0.5
errors[0].append( array("f",[238.2504663,61.09008854,24.2752466,28.16864487]) ) # rho = -1.0

values[1].append( array("f",[166.7678294,78.43110625,35.7742569,35.16900859]) ) # unsubtracted
values[1].append( array("f",[139.9974142,75.06270127,41.18379195,35.78160847]) ) # rho =  0.0
values[1].append( array("f",[143.488942,59.46720623,41.90878049,35.98944953]) ) # rho = -0.5
values[1].append( array("f",[156.6794948,151.7202217,43.66457825,36.15996987]) ) # rho = -1.0

errors[1].append( array("f",[308.4540732,321.8839333,51.43014498,46.21377645]) ) # unsubtracted
errors[1].append( array("f",[290.738684,325.788957,86.6042786,47.98297351]) ) # rho =  0.0
errors[1].append( array("f",[293.3263346,119.2359533,90.69377101,48.07656261]) ) # rho = -0.5
errors[1].append( array("f",[303.6203887,270.8649815,87.93950452,46.17254951]) ) # rho = -1.0

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
# Cross section
ylabel_up = "#sigma_{pre-hadron} [mbarn]_{3P}"
ylabel_down = "#sigma_{pre-hadron} [mbarn]_{4P}"
parameter = "sigma"
fileout = "fig04c.pdf" #sys.argv[3]
x0 = 0.5
y0 = 0.6
x1 = 0.9
y1 = 0.85
ylo = -300
yhi = 750

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
line40 = ROOT.TF1("line40","40",0.0,1.0);
line40.SetLineWidth(2);
line40.SetLineColor(1);
line40.SetLineStyle(2);

line40.GetXaxis().SetTitleFont(fontAxesCode)
line40.GetXaxis().SetTitleSize(fontAxesSize)
line40.GetXaxis().SetLabelFont(fontAxesCode)
line40.GetXaxis().SetLabelSize(fontAxesSize)
line40.GetYaxis().SetTitleFont(fontAxesCode)
line40.GetYaxis().SetTitleSize(fontAxesSize)
line40.GetYaxis().SetLabelFont(fontAxesCode)
line40.GetYaxis().SetLabelSize(fontAxesSize)
line40.GetYaxis().SetRangeUser(ylo,yhi)
line40.GetYaxis().SetRangeUser(ylo,yhi)
line40.GetXaxis().SetTitleOffset(1.5)

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
c.cd(2)
ROOT.gPad.SetTopMargin(0.001)
ROOT.gPad.SetRightMargin(0.01)
plt4P[0].Draw("AP")
line40.Draw("SAME");
plt4P[1].Draw("P SAME")
plt4P[2].Draw("P SAME")
plt4P[3].Draw("P SAME")
leg.Draw()
c.Print(fileout)