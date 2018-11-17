#!/usr/bin/python
from numpy import loadtxt
from array import array
import sys, os, ROOT

# Scale to alpha_a*N_c/8*pi = 0.02844
# factor = 0.02844
factor=1


basepath = "data/fitPIplus/"

folders3P = ["test3P/","test3P-0.0/","test3P-0.5/","test3P-1.0/"]
folders4P = ["test4P/","test4P-0.0/","test4P-0.5/","test4P-1.0/"]
filaname = "testFit.txt"

def retrieveTGraphErrors(i,par,nop):
  if (nop=="3P"):
    filepath = basepath+folders3P[i]+filaname
  elif (nop=="4P"):
    filepath = basepath+folders4P[i]+filaname
  # ztemp,qhat,lp,sigma,dlog,dz,err_qhat,err_lp,err_sigma,err_dlog,err_dz,chi2 = loadtxt(filepath,unpack=True,skiprows=1)
  if (par == "qhat"):
    ix = 0
    iy = 1
    iyerr = 6
    ichi2 = 11
  elif (par == "lp"):
    ix = 0
    iy = 2
    iyerr = 7
    ichi2 =  11
  elif (par == "sigma"):
    ix = 0
    iy = 3
    iyerr = 8
    ichi2 =  11
  elif (par == "dz"):
    ix = 0
    iy = 5
    iyerr = 10
    ichi2 =  11
  xtemp,ytemp,yerrtemp,chi2temp = loadtxt(filepath,unpack=True,skiprows=1,usecols=[ix,iy,iyerr,ichi2])
  xval = array("f",[xtemp[0],xtemp[1],xtemp[2],xtemp[3]])
  if (nop=="3P"):
    factor=1/(6.0-3.0)
    yval = array("f",[chi2temp[0]*factor,chi2temp[1]*factor,chi2temp[2]*factor,chi2temp[3]*factor])
  elif (nop=="4P"):
    factor=1/(6.0-2.0)
    yval = array("f",[chi2temp[0]*factor,chi2temp[1]*factor,chi2temp[2]*factor,chi2temp[3]*factor])
  gg = ROOT.TGraphErrors(4,xval,yval)
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
ylabel_up = "#chi^{2}/^{}NDF _{3P}"
ylabel_down = "#chi^{2}/^{}NDF _{4P}"
parameter = "qhat"
fileout = "fig05.pdf"
x0 = 0.5
y0 = 0.6
x1 = 0.9
y1 = 0.85
ylo = -0.15
yhi = 2.65
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
for i in range(4):
  plt3P[i].Fit("pol0","N0")
c.cd(2)
ROOT.gPad.SetTopMargin(0.001)
ROOT.gPad.SetRightMargin(0.01)
plt4P[0].Draw("AP")
plt4P[1].Draw("P SAME")
plt4P[2].Draw("P SAME")
plt4P[3].Draw("P SAME")
for i in range(4):
  plt4P[i].Fit("pol0","N0")
leg.Draw()
c.Print(fileout)