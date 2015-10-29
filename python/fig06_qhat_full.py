#!/usr/bin/python
from numpy import loadtxt, sqrt
from array import array
import sys, os, ROOT

# Scale to alpha_a*N_c/8*pi = 0.02844
# factor = 0.02844
factor=1.0/42.0;


basepath = "data/fitPIplus/"

folders3P = ["test3P/","test3P-0.0/","test3P-0.5/","test3P-1.0/"]
folders4P = ["test4P/","test4P-0.0/","test4P-0.5/","test4P-1.0/"]
filaname = "testFit.txt"

file_pt_ne = "data/pt_ne.dat"
file_pt_kr = "data/pt_kr.dat"
file_pt_xe = "data/pt_xe.dat"

def retrieveTGraphErrors(i,par,nop,aux):
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
  elif (par == "pT2/lp"):
    ix = 0
    iy = 2
    iyerr = 7
    pT2col = 12 + aux # increases in 0(Ne), 1(Kr), 2(Xe)
  xtemp,ytemp,yerrtemp,pT2 = loadtxt(filepath,unpack=True,skiprows=1,usecols=[ix,iy,iyerr,pT2col])
  # compute new values:
  xval = array("f",[0,0,0,0])
  yval = array("f",[0,0,0,0])
  xerr = array("f",[0,0,0,0])
  yerr = array("f",[0,0,0,0])
  for i in range(4):
    xval[i] = xtemp[i]
    yval[i] = pT2[i]/ytemp[i]
    yerr[i] = abs(yval[i])*sqrt((yerrtemp[i]/abs(ytemp[i]))**2)
    # normalize yval
    yval[i] = yval[i]/factor
    # print xval[i], "\t", yval[i], "\t", yerr[i]
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
ylabel_up = "#hat{q} [GeV^{2}/fm]_{3P}"
ylabel_down = "#hat{q} [GeV^{2}/fm]_{4P}"
parameter = "pT2/lp"
fileout = "fig06_test.pdf" #sys.argv[3]
x0 = 0.15
y0 = 0.25-0.0575
x1 = 0.5
y1 = 0.5-0.0575
ylo = -0.0038/factor
yhi = 0.0075/factor

fontAxesSize = 28
fontAxesCode = 43
def arrayPlot(parameter,A):
  color = [1,2,4,8]
  plt3P = []
  plt4P = []
  offset_title = 1.5
  for i in range(4):
    plt3P.append(retrieveTGraphErrors(i,parameter,"3P",A))
    plt3P[i].SetMarkerStyle(20+i)
    plt3P[i].SetMarkerSize(1.5)
    plt3P[i].SetMarkerColor(color[i]) 
    plt3P[i].SetLineColor(color[i])
    plt3P[i].SetLineWidth(2)
    plt3P[i].GetXaxis().SetTitle(xlabel)
    plt3P[i].GetYaxis().SetTitle(ylabel_up)
    plt3P[i].GetYaxis().SetTitleOffset(offset_title)
    plt4P.append(retrieveTGraphErrors(i,parameter,"4P",A))
    plt4P[i].SetMarkerStyle(20+i)
    plt4P[i].SetMarkerSize(1.5)
    plt4P[i].SetMarkerColor(color[i]) 
    plt4P[i].SetLineColor(color[i])
    plt4P[i].SetLineWidth(2)
    plt4P[i].GetXaxis().SetTitle(xlabel)
    plt4P[i].GetYaxis().SetTitle(ylabel_down)
    plt4P[i].GetYaxis().SetTitleOffset(offset_title)
  leg = ROOT.TLegend(x0,y0,x1,y1)
  leg.SetTextFont(43)
  leg.SetTextSize(28)
  leg.SetBorderSize(0)
  for i in range(4):
    leg.AddEntry(plt3P[i],legends[i],"ep")
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
  return plt3P,plt4P,leg

legends = ["Uncorrected","He subtracted #rho =  0.0","He subtracted #rho = -0.5","He subtracted #rho = -1.0"]
############# code
c = ROOT.TCanvas("canvas","canvas",800,2400)
# text
text1 = ROOT.TLatex()
text1.SetNDC()
text1.SetTextFont(43)
text1.SetTextSize(fontAxesSize+5)
#
c.Divide(3,2)
nuclei_name = "Neon"
plt3P,plt4P,leg=arrayPlot("pT2/lp",0)
c.cd(1)
# ROOT.gPad.SetBottomMargin(0.001)
# ROOT.gPad.SetTopMargin(0.01)
# ROOT.gPad.SetRightMargin(0.01)
plt3P[0].Draw("AP")
plt3P[1].Draw("P SAME")
plt3P[2].Draw("P SAME")
plt3P[3].Draw("P SAME")
line0 = ROOT.TF1("line0","0",0,1)
line0.SetLineColor(1)
line0.SetLineWidth(1)
line0.SetLineStyle(2)
line0.Draw("SAME")
text1.DrawLatex(0.2,0.75,"#hat{q} = #Delta#LTp_{t}^{2}#GT/l_{p}")
text1.DrawLatex(0.2,0.9,nuclei_name)
# for i in range(4):
#   plt3P[i].Fit("pol0","N0")
c.cd(2)
# ROOT.gPad.SetTopMargin(0.001)
# ROOT.gPad.SetRightMargin(0.01)
plt4P[0].Draw("AP")
plt4P[1].Draw("P SAME")
plt4P[2].Draw("P SAME")
plt4P[3].Draw("P SAME")
line0.Draw("SAME")
# for i in range(4):
#   plt4P[i].Fit("pol0","N0")
leg.SetFillStyle(0)
leg.Draw()
###################################
nuclei_name = "Krypton"
plt3P,plt4P,leg=arrayPlot("pT2/lp",1)
c.cd(3)
# ROOT.gPad.SetBottomMargin(0.001)
# ROOT.gPad.SetTopMargin(0.01)
# ROOT.gPad.SetRightMargin(0.01)
# ROOT.gPad.SetLeftMargin(0.01)
plt3P[0].Draw("AP")
plt3P[1].Draw("P SAME")
plt3P[2].Draw("P SAME")
plt3P[3].Draw("P SAME")
line0 = ROOT.TF1("line0","0",0,1)
line0.SetLineColor(1)
line0.SetLineWidth(1)
line0.SetLineStyle(2)
line0.Draw("SAME")
text1.DrawLatex(0.2,0.75,"#hat{q} = #Delta#LTp_{t}^{2}#GT/l_{p}")
text1.DrawLatex(0.2,0.9,nuclei_name)
# for i in range(4):
#   plt3P[i].Fit("pol0","N0")
c.cd(4)
# ROOT.gPad.SetTopMargin(0.001)
# ROOT.gPad.SetRightMargin(0.01)
plt4P[0].Draw("AP")
plt4P[1].Draw("P SAME")
plt4P[2].Draw("P SAME")
plt4P[3].Draw("P SAME")
line0.Draw("SAME")
# for i in range(4):
#   plt4P[i].Fit("pol0","N0")
leg.SetFillStyle(0)
leg.Draw()
###################################
nuclei_name = "Xenon"
plt3P,plt4P,leg=arrayPlot("pT2/lp",2)
c.cd(5)
# ROOT.gPad.SetBottomMargin(0.001)
# ROOT.gPad.SetTopMargin(0.01)
# ROOT.gPad.SetRightMargin(0.01)
plt3P[0].Draw("AP")
plt3P[1].Draw("P SAME")
plt3P[2].Draw("P SAME")
plt3P[3].Draw("P SAME")
line0 = ROOT.TF1("line0","0",0,1)
line0.SetLineColor(1)
line0.SetLineWidth(1)
line0.SetLineStyle(2)
line0.Draw("SAME")
text1.DrawLatex(0.2,0.75,"#hat{q} = #Delta#LTp_{t}^{2}#GT/l_{p}")
text1.DrawLatex(0.2,0.9,nuclei_name)
# for i in range(4):
#   plt3P[i].Fit("pol0","N0")
c.cd(6)
# ROOT.gPad.SetTopMargin(0.001)
# ROOT.gPad.SetRightMargin(0.01)
plt4P[0].Draw("AP")
plt4P[1].Draw("P SAME")
plt4P[2].Draw("P SAME")
plt4P[3].Draw("P SAME")
line0.Draw("SAME")
# for i in range(4):
#   plt4P[i].Fit("pol0","N0")
leg.SetFillStyle(0)
leg.Draw()
###################################
c.Print(fileout)