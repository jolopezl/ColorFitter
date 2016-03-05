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

values[0].append( array("f",[1.783259081,2.359101836,0.046824664,6.15E-07]) ) # unsubtracted
values[0].append( array("f",[1.937605378,2.451870533,1.390701946,1.325518864]) ) # rho =  0.0
values[0].append( array("f",[1.926978412,2.419270628,1.353903941,1.295141276]) ) # rho = -0.5
values[0].append( array("f",[1.916631914,2.385707681,1.292526878,1.249361285]) ) # rho = -1.0

errors[0].append( array("f",[0.232558318,0.555006047,8.745636509,6.653189238]) ) # unsubtracted
errors[0].append( array("f",[0.284763384,0.697034046,1.667032683,2.685889045]) ) # rho =  0.0
errors[0].append( array("f",[0.433821661,0.605366834,1.426322873,2.456219795]) ) # rho = -0.5
errors[0].append( array("f",[0.241510758,0.564889424,1.177186258,2.107379463]) ) # rho = -1.0

values[1].append( array("f",[1.771398551,2.412180865,0.005217184,2.01E-06]) ) # unsubtracted
values[1].append( array("f",[1.93317907,2.501781292,1.732744031,1.694833994]) ) # rho =  0.0
values[1].append( array("f",[1.920935166,2.464056612,1.677625074,1.652262325]) ) # rho = -0.5
values[1].append( array("f",[1.908828444,2.389102269,1.562426638,1.571110585]) ) # rho = -1.0

errors[1].append( array("f",[0.230071148,0.563087591,6.996401851,6.989005551]) ) # unsubtracted
errors[1].append( array("f",[0.307281346,0.649868425,2.524074135,5.733476976]) ) # rho =  0.0
errors[1].append( array("f",[0.296045067,0.622413772,2.464351098,5.773890896]) ) # rho = -0.5
errors[1].append( array("f",[0.271160745,0.514046442,1.902753054,2.76858071]) ) # rho = -1.0

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
xlabel = "z"
# Q-HAT configuration
# ylabel_up = "#hat{q}_{0} [GeV^{2}/fm^{2}]_{3P}"
# ylabel_down = "#hat{q}_{0} [GeV^{2}/fm^{2}]_{4P}"
ylabel_up = "#hat{q}_{0} [GeV^{2}fm]_{3P}"
ylabel_down = "#hat{q}_{0} [GeV^{2}fm]_{4P}"
parameter = "qhat"
fileout = "fig04a.pdf"
x0 = 0.15
y0 = 0.25
x1 = 0.5
y1 = 0.5
ylo = -9.15*factor
yhi = 9.15*factor
# ylo = -0.029
# yhi = 0.029

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