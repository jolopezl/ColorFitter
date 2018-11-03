#!/usr/bin/python
from numpy import loadtxt
import sys, os, ROOT
"""
This is for plotting two histograms with differing y-ranges and the same x-range.  
"""
# general style (taken from my rootlogon.C)
# ROOT.gROOT.SetStyle("Plain")
# ROOT.gStyle.SetPadTickX(1)
# ROOT.gStyle.SetPadTickY(1)
# ROOT.gStyle.SetPadTopMargin(0.05)
ROOT.gStyle.SetPadRightMargin(0.05)
ROOT.gStyle.SetPadLeftMargin(0.125)
ROOT.gStyle.SetPadBottomMargin(0.16)
# ROOT.gStyle.SetPadBorderMode(0)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptTitle(0)

ROOT.gStyle.SetEndErrorSize(7.5)

file_pt_he = "data/pt_he.dat"
file_pt_ne = "data/pt_ne.dat"
file_pt_kr = "data/pt_kr.dat"
file_pt_xe = "data/pt_xe.dat"
file_rm_ne = "data/rm_ne.dat"
file_rm_kr = "data/rm_kr.dat"
file_rm_xe = "data/rm_xe.dat"

# create a canvas and divide it
c1 = ROOT.TCanvas("paddy","paddy",800,800)#,700,700)
c1.Divide(1,2,0,0)

# pt
g_pt_he = ROOT.TGraphErrors(file_pt_he)
g_pt_ne = ROOT.TGraphErrors(file_pt_ne)
g_pt_kr = ROOT.TGraphErrors(file_pt_kr)
g_pt_xe = ROOT.TGraphErrors(file_pt_xe)

g_pt_ne.SetMarkerStyle(20)
g_pt_kr.SetMarkerStyle(21)
g_pt_xe.SetMarkerStyle(22)
g_pt_ne.SetMarkerColor(1)
g_pt_kr.SetMarkerColor(2)
g_pt_xe.SetMarkerColor(4)
g_pt_ne.SetLineColor(1)
g_pt_kr.SetLineColor(2)
g_pt_xe.SetLineColor(4)
g_pt_ne.SetLineWidth(2)
g_pt_kr.SetLineWidth(2)
g_pt_xe.SetLineWidth(2)

g_pt_xe.GetYaxis().SetTitle("#Delta #LT p_{t}^{2} #GT [GeV^{2}]")#_{A}^{#pi^{+}}")
g_pt_xe.GetYaxis().SetRangeUser(-0.035,0.045)
g_pt_xe.GetXaxis().SetLimits(0.1,1.0)

# Rm
g_rm_ne = ROOT.TGraphErrors(file_rm_ne)
g_rm_kr = ROOT.TGraphErrors(file_rm_kr)
g_rm_xe = ROOT.TGraphErrors(file_rm_xe)

g_rm_ne.SetMarkerStyle(20)
g_rm_kr.SetMarkerStyle(21)
g_rm_xe.SetMarkerStyle(22)
g_rm_ne.SetMarkerColor(1)
g_rm_kr.SetMarkerColor(2)
g_rm_xe.SetMarkerColor(4)
g_rm_ne.SetLineColor(1)
g_rm_kr.SetLineColor(2)
g_rm_xe.SetLineColor(4)
g_rm_ne.SetLineWidth(2)
g_rm_kr.SetLineWidth(2)
g_rm_xe.SetLineWidth(2)

g_rm_xe.GetXaxis().SetTitle("z")
g_rm_xe.GetYaxis().SetTitle("R_{m}")#^{#pi^{+}}")
g_rm_xe.GetYaxis().SetRangeUser(0.35,1.05)
g_rm_xe.GetXaxis().SetLimits(0.1,1.0)

# customize label and title size
fontAxesSize = 28
fontAxesCode = 43
g_pt_xe.GetXaxis().SetLabelFont(fontAxesCode)
g_pt_xe.GetXaxis().SetTitleFont(fontAxesCode)
g_pt_xe.GetYaxis().SetLabelFont(fontAxesCode)
g_pt_xe.GetYaxis().SetTitleFont(fontAxesCode)
g_rm_xe.GetXaxis().SetLabelFont(fontAxesCode)
g_rm_xe.GetXaxis().SetTitleFont(fontAxesCode)
g_rm_xe.GetYaxis().SetLabelFont(fontAxesCode)
g_rm_xe.GetYaxis().SetTitleFont(fontAxesCode)
g_pt_xe.GetXaxis().SetLabelSize(fontAxesSize)
g_pt_xe.GetXaxis().SetTitleSize(fontAxesSize)
g_pt_xe.GetYaxis().SetLabelSize(fontAxesSize)
g_pt_xe.GetYaxis().SetTitleSize(fontAxesSize)
g_rm_xe.GetXaxis().SetLabelSize(fontAxesSize)
g_rm_xe.GetXaxis().SetTitleSize(fontAxesSize)
g_rm_xe.GetYaxis().SetLabelSize(fontAxesSize)
g_rm_xe.GetYaxis().SetTitleSize(fontAxesSize)
# offset
g_pt_xe.GetYaxis().SetTitleOffset(1.85)
g_rm_xe.GetYaxis().SetTitleOffset(1.85)
g_rm_xe.GetXaxis().SetTitleOffset(1.5)

# text
text1 = ROOT.TLatex()
text1.SetNDC()
text1.SetTextFont(53)
text1.SetTextSize(fontAxesSize-4)

#top canvas
c1.cd(1)
ROOT.gPad.SetBottomMargin(0.001)
ROOT.gPad.SetTopMargin(0.01)
ROOT.gPad.SetRightMargin(0.01)
g_pt_xe.Draw("AP")
g_pt_kr.Draw("PSAME")
g_pt_ne.Draw("PSAME")
text1.DrawLatex(0.16,0.92,"HERMES Collaboration, Physics Letters B 684 (2010) 114-118")


# bottom canvas
c1.cd(2)
ROOT.gPad.SetTopMargin(0.001)
ROOT.gPad.SetRightMargin(0.01)
g_rm_xe.Draw("AP")
g_rm_kr.Draw("PSAME")
g_rm_ne.Draw("PSAME")
polfit="pol4"
g_rm_xe.Fit(polfit,"Q0")
g_rm_kr.Fit(polfit,"Q0")
g_rm_ne.Fit(polfit,"Q0")
f_rm_xe = g_rm_xe.GetFunction(polfit)
f_rm_kr = g_rm_kr.GetFunction(polfit)
f_rm_ne = g_rm_ne.GetFunction(polfit)
f_rm_ne.SetLineColor(1)
f_rm_kr.SetLineColor(2)
f_rm_xe.SetLineColor(4)
f_rm_ne.SetLineWidth(2)
f_rm_kr.SetLineWidth(2)
f_rm_xe.SetLineWidth(2)
f_rm_ne.SetLineStyle(2)
f_rm_kr.SetLineStyle(2)
f_rm_xe.SetLineStyle(2)
f_rm_xe.Draw("SAME")
f_rm_kr.Draw("SAME")
f_rm_ne.Draw("SAME")
# legend coords
x0 = 0.12+0.06
y0 = 0.0+0.04
dx0 = 0.1
dy0 = 0.075
leg_interp = ROOT.TLegend(x0,y0+0.2,x0+dx0,y0+0.2+4*dy0)
leg_interp.SetTextFont(fontAxesCode) #63
leg_interp.SetTextSize(fontAxesSize-4)
leg_interp.SetBorderSize(0)
# leg_interp.AddEntry(g_pt_he,"He data", "ep")
leg_interp.AddEntry(g_rm_ne,"Ne data", "ep")
leg_interp.AddEntry(g_rm_kr,"Kr data", "ep")
leg_interp.AddEntry(g_rm_xe,"Xe data", "ep")
leg_interp.AddEntry(f_rm_ne,"Ne fit for data interpolation","l")
leg_interp.AddEntry(f_rm_kr,"Kr fit for data interpolation","l")
leg_interp.AddEntry(f_rm_xe,"Xe fit for data interpolation","l")
leg_interp.Draw()
text1.DrawLatex(0.16,0.93,"HERMES Collaboration, Nuclear Physics B 780 (2007) 1-27")

# Extra pad for inset
c1.cd(1)
subpad_x0 = 0.25
subpad_y0 = 0.00
subpad_dx0 = 0.35
subpad_dy0 = 0.45
subpad = ROOT.TPad("subpad","",subpad_x0,subpad_y0,subpad_x0+subpad_dx0,subpad_y0+subpad_dy0);
# ROOT.gPad.SetPadLeftMargin(0.13)
subpad.SetFillStyle(4000)
subpad.Draw();
subpad.cd();
# g_pt_he.GetXaxis().SetTitle("z")
# g_pt_he.GetYaxis().SetTitle("#Delta #LT p_{t}^{2} #GT_{A}^{#pi^{+}}")
# g_pt_he.GetYaxis().SetTitleOffset(4)
# g_pt_he.GetYaxis().SetRangeUser(-0.035,0.045)
# g_pt_he.GetYaxis().SetTextFont(63)
# g_pt_he.GetYaxis().SetTextSize(12)
# g_pt_he.GetXaxis().SetLimits(0.1,1.0)
g_pt_he.SetMarkerStyle(33)
g_pt_he.SetMarkerColor(46)
g_pt_he.SetLineColor(46)
g_pt_he.SetLineWidth(2)
line0 = ROOT.TF1("line0","0",0,1)
# line0.GetXaxis().SetTitle("z")
# line0.GetYaxis().SetTitle("#Delta #LT p_{t}^{2} #GT")#_{A}^{#pi^{+}}")
# line0.GetYaxis().SetTitleOffset(4)
line0.GetYaxis().SetRangeUser(-0.035,0.045)
line0.SetLineColor(1)
line0.SetLineWidth(1)
line0.SetLineStyle(2)
line0.GetXaxis().SetLabelFont(fontAxesCode)
line0.GetXaxis().SetTitleFont(fontAxesCode)
line0.GetYaxis().SetLabelFont(fontAxesCode)
line0.GetYaxis().SetTitleFont(fontAxesCode)
line0.GetXaxis().SetLabelSize(14)
line0.GetXaxis().SetTitleSize(14)
line0.GetYaxis().SetLabelSize(14)
line0.GetYaxis().SetTitleSize(14)
line0.Draw()
g_pt_he.Draw("PSAME")
leg = ROOT.TLegend(0.2,0.7,0.4,0.8)
leg.SetTextFont(fontAxesCode) #63
leg.SetTextSize(12)
leg.SetBorderSize(0)
leg.AddEntry(g_pt_he,"He data","ep")
leg.Draw()

# update the canvas
c1.Update()
c1.Print("fig01_hermes_data.pdf")
# c1.Print("fig01_hermes_data.eps")