#!/usr/bin/python
from numpy import loadtxt
from array import array
import sys, os, ROOT
factor = 1.

from AtlasStyle import SetAtlasStyle
SetAtlasStyle()


labels = ['BL','BLE','BL40','BL30','BLE40','BLE30']

val = []

val.append(array("f",[1.439136856,0.864235678,0.326817342,0.297840314]))  # BL
val.append(array("f",[2.137191558,1.12430168,0.183660046,0.121672328]))  # BLE
val.append(array("f",[1.168148071,0.648347815,0.308321527,0.254493015]))   # BL40
val.append(array("f",[1.234154354,0.656828,0.269769079,0.227156692])) # BL30
val.append(array("f",[1.514137845,0.819098412,0.132133632,0.08829914]))   # BLE40
val.append(array("f",[1.559630861,0.858671771,0.137515303,0.090534845])) # BLE30
xval = array("f",[0.32,0.53,0.75,0.94])

# Prepare plots to be filled
markers = [20,21,22,23,29,33]
# markers = [24,25,26,27,28,32]
colors = [1,2,3,4,6,9]

g = []
for i in range(6):
    g.append(ROOT.TGraph(4,xval,val[i]))
    g[i].SetMarkerStyle(markers[i])
    g[i].SetMarkerColor(colors[i])

# Configuration
xlabel = "z_{h}"
# L_P configuration
ylabel = "#chi^{2}/^{}DOF"

fileout = "fig05d_chi2_Summary.pdf" #sys.argv[3]

ylo = 0
yhi = 2.2

markerSize = 2.0
lineWidth = 3
############# code
c = ROOT.TCanvas("canvas","canvas",800,600)

x0 = 0.6 
y0 = 0.70
x1 = x0 + 0.3
y1 = y0 + 0.15
leg = ROOT.TLegend(x0,y0,x1,y1)
leg.SetNColumns(2)
leg.SetTextFont(43)
leg.SetTextSize(28)
leg.SetBorderSize(0)
leg.SetFillStyle(0)
# leg.SetHeader("He subtracted #rho = 0.0")
# leg.SetNColumns(3);
for i in range(6):
    leg.AddEntry(g[i],labels[i],"ep")

text1 = ROOT.TLatex()
text1.SetNDC()
text1.SetTextFont(43)
text1.SetTextSize(26)


line1 = ROOT.TF1("line1","1",0.0,1.0);
line1.SetLineWidth(2);
line1.SetLineColor(1);
line1.SetLineStyle(2);


g[0].GetYaxis().SetRangeUser(-0.1,2.4)
g[0].GetYaxis().SetTitle(ylabel)
g[0].GetXaxis().SetTitle(xlabel)
g[0].Draw("AP")
line1.Draw("SAME")
for i in range(6):
    if (i==0): continue
    g[i].Draw("P SAME")
leg.Draw()
text1.DrawLatex(0.6,0.88, "He subtracted #rho =  0.0")
# text1.DrawLatex(0.17, 0.8, "Fixed cross section #sigma_{ph} = 40 [mbarn]")
c.Print(fileout)