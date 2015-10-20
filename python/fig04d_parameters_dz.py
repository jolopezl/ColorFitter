#!/usr/bin/python
from numpy import loadtxt
from array import array
import sys, os, ROOT

basepath = "data/fitPIplus/"

folders3P = ["test3P/","test3P-0.0/","test3P-0.5/","test3P-1.0/"]
folders4P = ["test4P/","test4P-0.0/","test4P-0.5/","test4P-1.0/"]
filaname = "testFit.txt"

def retrieveTGraphErrors(i,par,nop):
  if (nop=="3P"):
    filepath = basepath+folders3P[i]+filaname
  elif (nop=="4P"):
    filepath = basepath+folders4P[i]+filaname
  ztemp,qhat,lp,sigma,dlog,dz,err_qhat,err_lp,err_sigma,err_dlog,err_dz,chi2 = loadtxt(filepath,unpack=True,skiprows=1)
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
  yval = array("f",[ytemp[0],ytemp[1],ytemp[2],ytemp[3]])
  xerr = array("f",[0,0,0,0])
  yerr = array("f",[yerrtemp[0],yerrtemp[1],yerrtemp[2],yerrtemp[3]])
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
# ylabel_up = "#hat{q} [GeV/fm^{2}]_{3P} /q_{0}"
# ylabel_down = "#hat{q} [GeV/fm^{2}]_{4P} /q_{0}"
# parameter = "qhat"
# fileout = "fig04a.pdf"
# x0 = 0.15
# y0 = 0.25
# x1 = 0.5
# y1 = 0.5
# ylo = -1.15
# yhi = 1.15

# L_P configuration
# ylabel_up = "l_{p} [fm]_{3P}"
# ylabel_down = "l_{p} [fm]_{4P}"
# parameter = "lp"
# fileout = "fig04b.pdf" #sys.argv[3]
# x0 = 0.5
# y0 = 0.6
# x1 = 0.9
# y1 = 0.85
# ylo = -10
# yhi = 32.5

# Cross section
# ylabel_up = "#sigma_{pre-hadron} [mbarn]_{3P}"
# ylabel_down = "#sigma_{pre-hadron} [mbarn]_{4P}"
# parameter = "sigma"
# fileout = "fig04c.pdf" #sys.argv[3]
# x0 = 0.5
# y0 = 0.6
# x1 = 0.9
# y1 = 0.85
# ylo = -140
# yhi = 490

# dz energy loss
ylabel_up = "#Delta z_{3P}"
ylabel_down = "#Delta z_{4P}"
parameter = "dz"
fileout = "fig04d.pdf" #sys.argv[3]
x0 = 0.5
y0 = 0.6
x1 = 0.9
y1 = 0.85
ylo = -0.125
yhi = 0.175


legends = ["Uncorrected","He subtracted #rho =  0.0","He subtracted #rho = -0.5","He subtracted #rho = -1.0"]
############# code
c = ROOT.TCanvas("canvas","canvas",800,400)
color = [1,2,4,8]
qhat3P = []
qhat4P = []
for i in range(4):
  qhat3P.append(retrieveTGraphErrors(i,parameter,"3P"))
  qhat3P[i].SetMarkerStyle(20+i)
  qhat3P[i].SetMarkerSize(1.5)
  qhat3P[i].SetMarkerColor(color[i]) 
  qhat3P[i].SetLineColor(color[i])
  qhat3P[i].SetLineWidth(2)
  qhat3P[i].GetXaxis().SetTitle(xlabel)
  qhat3P[i].GetYaxis().SetTitle(ylabel_up)
  qhat3P[i].GetYaxis().SetTitleOffset(1.5)
  qhat4P.append(retrieveTGraphErrors(i,parameter,"4P"))
  qhat4P[i].SetMarkerStyle(20+i)
  qhat4P[i].SetMarkerSize(1.5)
  qhat4P[i].SetMarkerColor(color[i]) 
  qhat4P[i].SetLineColor(color[i])
  qhat4P[i].SetLineWidth(2)
  qhat4P[i].GetXaxis().SetTitle(xlabel)
  qhat4P[i].GetYaxis().SetTitle(ylabel_down)
  qhat4P[i].GetYaxis().SetTitleOffset(1.5)
leg = ROOT.TLegend(x0,y0,x1,y1)
leg.SetTextFont(43)
leg.SetTextSize(28)
leg.SetBorderSize(0)
for i in range(4):
  leg.AddEntry(qhat3P[i],legends[i],"ep")
fontAxesSize = 28
fontAxesCode = 43
qhat3P[0].GetXaxis().SetTitleFont(fontAxesCode)
qhat3P[0].GetXaxis().SetTitleSize(fontAxesSize)
qhat3P[0].GetXaxis().SetLabelFont(fontAxesCode)
qhat3P[0].GetXaxis().SetLabelSize(fontAxesSize)
qhat3P[0].GetYaxis().SetTitleFont(fontAxesCode)
qhat3P[0].GetYaxis().SetTitleSize(fontAxesSize)
qhat3P[0].GetYaxis().SetLabelFont(fontAxesCode)
qhat3P[0].GetYaxis().SetLabelSize(fontAxesSize)
qhat4P[0].GetXaxis().SetTitleFont(fontAxesCode)
qhat4P[0].GetXaxis().SetTitleSize(fontAxesSize)
qhat4P[0].GetXaxis().SetLabelFont(fontAxesCode)
qhat4P[0].GetXaxis().SetLabelSize(fontAxesSize)
qhat4P[0].GetYaxis().SetTitleFont(fontAxesCode)
qhat4P[0].GetYaxis().SetTitleSize(fontAxesSize)
qhat4P[0].GetYaxis().SetLabelFont(fontAxesCode)
qhat4P[0].GetYaxis().SetLabelSize(fontAxesSize)
# axes range
qhat3P[0].GetYaxis().SetRangeUser(ylo,yhi)
qhat4P[0].GetYaxis().SetRangeUser(ylo,yhi)
qhat4P[0].GetYaxis().SetTitleOffset(0.75)
# qhat4P[0].GetXaxis().SetTitleOffset(1.5)
#
# c.Divide(1,2,0,0)
# c.cd(1)
# ROOT.gPad.SetBottomMargin(0.001)
# ROOT.gPad.SetTopMargin(0.01)
# ROOT.gPad.SetRightMargin(0.01)
# qhat3P[0].Draw("AP")
# qhat3P[1].Draw("P SAME")
# qhat3P[2].Draw("P SAME")
# qhat3P[3].Draw("P SAME")
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

qhat4P[0].Draw("AP")
line00.Draw("SAME")
qhat4P[1].Draw("P SAME")
qhat4P[2].Draw("P SAME")
qhat4P[3].Draw("P SAME")
leg.Draw()
c.Print(fileout)