#!/usr/bin/python
from numpy import loadtxt, sqrt
from array import array
import sys, os, ROOT

# Scale to alpha_a*N_c/8*pi = 0.02844
# factor = 0.02844
factor=1.0;

basepath = "../../test/"
folders3P = ["Ifit__3p-uncorrected/","Ifit__3p/","Ifit__3p-rho=-0.5/","Ifit__3p-rho=-1.0/"]
folders4P = ["Ifit__4p-new-uncorrected/","Ifit__4p-new/","Ifit__4p-new-rho=-0.5/","Ifit__4p-new-rho=-1.0/"]
filaname = "testFit.csv"

a = 0.0075
dx = [-3*a/2.,-a/2.,a/2.,3*a/2.]

def retrieveTGraphErrors(i,par,nop,aux):
  if (nop=="3P"):
    filepath = basepath+folders3P[i]+filaname
  elif (nop=="4P"):
    filepath = basepath+folders4P[i]+filaname
  print filepath
  ix = 0
  iy = 2
  iyerr = 9
  pT2col = 14 + aux # increases in 0(Ne), 1(Kr), 2(Xe)
  xtemp,ytemp,yerrtemp,pT2 = loadtxt(filepath,delimiter=";",unpack=True,skiprows=1,usecols=[ix,iy,iyerr,pT2col])
  # compute new values:
  xval = array("f",[0.32+dx[i],0.53+dx[i],0.75+dx[i],0.94+dx[i]])
  yval = array("f",[0,0,0,0])
  xerr = array("f",[0,0,0,0])
  yerr = array("f",[0,0,0,0])
  for i in range(4):
    yval[i] = pT2[i]/ytemp[i]
    # yerr[i] = abs(yval[i])*sqrt((yerrtemp[i]/abs(ytemp[i]))**2)
    yerr[i] = abs(yval[i])*(yerrtemp[i]/abs(ytemp[i]))
    # normalize yval
    yval[i] = yval[i]
    # print xval[i], "\t", yval[i], "\t", yerr[i]
    yval[i] = yval[i]
    # yerr[i] = 0.
  print xval
  print yval
  print xerr
  print yerr
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
ylabel_up = "#hat{q} [GeV^{2}/fm]_{3P}"
ylabel_down = "#hat{q} [GeV^{2}/fm]_{4P}"
parameter = "pT2/lp"
fileout = "fig06.pdf" #sys.argv[3]
x0 = 0.15
y0 = 0.25-0.0575
x1 = 0.5
y1 = 0.5-0.0575

ylo = -0.0015
yhi = 0.0055

markerSize = 2.0
lineWidth = 3

def job(fileref,fout,nuclei_name):
  legends = ["Uncorrected","He subtracted #rho =  0.0","He subtracted #rho = -0.5","He subtracted #rho = -1.0"]
  ############# code
  c = ROOT.TCanvas("canvas","canvas",800,800)
  color = [1,2,4,8]
  plt3P = []
  plt4P = []
  offset_title = 1.5
  for i in range(4):
    plt3P.append(retrieveTGraphErrors(i,parameter,"3P",fileref))
    plt3P[i].SetMarkerStyle(20+i)
    plt3P[i].SetMarkerSize(markerSize)
    plt3P[i].SetMarkerColor(color[i]) 
    plt3P[i].SetLineColor(color[i])
    plt3P[i].SetLineWidth(lineWidth)
    plt3P[i].GetXaxis().SetTitle(xlabel)
    plt3P[i].GetYaxis().SetTitle(ylabel_up)
    plt3P[i].GetYaxis().SetTitleOffset(offset_title)
    plt4P.append(retrieveTGraphErrors(i,parameter,"4P",fileref))
    plt4P[i].SetMarkerStyle(20+i)
    plt4P[i].SetMarkerSize(markerSize)
    plt4P[i].SetMarkerColor(color[i]) 
    plt4P[i].SetLineColor(color[i])
    plt4P[i].SetLineWidth(lineWidth)
    plt4P[i].GetXaxis().SetTitle(xlabel)
    plt4P[i].GetYaxis().SetTitle(ylabel_down)
    plt4P[i].GetYaxis().SetTitleOffset(offset_title)
    
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
  # plt3P[0].GetYaxis().SetRangeUser(ylo,yhi)
  # plt4P[0].GetYaxis().SetRangeUser(ylo,yhi)
  plt3P[0].GetYaxis().SetTitleOffset(1.75)
  plt4P[0].GetYaxis().SetTitleOffset(1.75)
  plt4P[0].GetXaxis().SetTitleOffset(1.5)
  # text
  text1 = ROOT.TLatex()
  text1.SetNDC()
  text1.SetTextFont(43)
  text1.SetTextSize(fontAxesSize+5)
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
  line0 = ROOT.TF1("line0","0",0,1)
  line0.SetLineColor(1)
  line0.SetLineWidth(1)
  line0.SetLineStyle(2)
  line0.Draw("SAME")
  text1.DrawLatex(0.2,0.75,"#hat{q} = #Delta#LTp_{t}^{2}#GT/L_{p}")
  text1.DrawLatex(0.2,0.9,nuclei_name)
  # for i in range(4):
  #   plt3P[i].Fit("pol0","N0")
  c.cd(2)
  ROOT.gPad.SetTopMargin(0.001)
  ROOT.gPad.SetRightMargin(0.01)
  plt4P[0].Draw("AP")
  plt4P[1].Draw("P SAME")
  plt4P[2].Draw("P SAME")
  plt4P[3].Draw("P SAME")
  line0.Draw("SAME")
  # for i in range(4):
  #   plt4P[i].Fit("pol0","N0")
  leg.SetFillStyle(0)
  leg.Draw()
  c.Print(fout)

print "#######     Neon"
job(0,"fig06_neon.pdf","Neon")
print "#######     Krypton"
job(1,"fig06_krypton.pdf","Krypton")
print "#######     Xenon"
job(2,"fig06_xenon.pdf","Xenon")