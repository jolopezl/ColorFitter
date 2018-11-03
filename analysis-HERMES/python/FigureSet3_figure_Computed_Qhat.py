#!/usr/bin/python
from numpy import loadtxt
from array import array
import sys, os, ROOT
factor = 1.

from AtlasStyle import SetAtlasStyle, AddLabel
SetAtlasStyle()

# factor = 1.0
factor = 0.1*3./(4.*3.141592)
print "Factor to be removed ",factor
print "Inverse is ",1/factor

# BLE40
# val1 = array("f",[0.000979387,0.002160808,0.001637914,0.002576695])  
# val2 = array("f",[0.001714001,0.003582285,0.002536743,0.003642609])  
# val3 = array("f",[0.001998672,0.004087083,0.002822044,0.003937508])   
# err1 = array("f",[0.000798121,0.000960257,0.000825269,0.002039819])
# err2 = array("f",[0.001396773,0.001591958,0.001278147,0.002883641])
# err3 = array("f",[0.001628757,0.001816288,0.001421897,0.003117095]) 

# BL30
val1 = array("f",[0.00149515055464036,0.00216943165895517,0.00121563139420037,0.00182171613293309])  
val2 = array("f",[0.00254336705492006,0.00359529131794448,0.00194656579376391,0.00268632623709582])  
val3 = array("f",[0.00293177851834213,0.00410133953717724,0.00219169224687009,0.00294113660645655])   
# err1 = array("f",[0.000322458404009397,0.000334661567553983,0.000210530767651046,0.000349064796067011])
# err2 = array("f",[0.000548526754576147,0.000554617990988482,0.000337118630531875,0.000514735475615264])
# err3 = array("f",[0.000632295268860757,0.000632682164896546,0.000379571186948426,0.000563560497257607]) 
err1 = array("f",[0.000296773,0.000395372,0.001178313,0.003395732])
err2 = array("f",[0.000505189,0.000659603,0.001907591,0.005056599])
err3 = array("f",[0.00058228,0.000751837,0.002144761,0.005530273])


xval  = array("f",[0.32,0.53,0.75,0.94])
xerr  = array("f",[0,0,0,0])
xval1 = array("f",[0,0,0,0])
xval2 = array("f",[0,0,0,0])
xval3 = array("f",[0,0,0,0])

offset = 0.0075
offset = 0.02
offset = offset/2
for i in range(4):   
  xval1[i] = xval[i] - offset
  xval2[i] = xval[i] 
  xval3[i] = xval[i] + offset 

for i in range(4):
    val1[i] = val1[i]/factor;
    val2[i] = val2[i]/factor;
    val3[i] = val3[i]/factor;
    err1[i] = err1[i]/factor;
    err2[i] = err2[i]/factor;
    err3[i] = err3[i]/factor;

g1 = ROOT.TGraphErrors(4,xval1,val1,xerr,err1)
g2 = ROOT.TGraphErrors(4,xval2,val2,xerr,err2)
g3 = ROOT.TGraphErrors(4,xval3,val3,xerr,err3)


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
xlabel = "z"
# L_P configuration
ylabel = "#hat{q} [GeV^{2}/fm] "

fileout = "fig06a_qhat_BL30.pdf" #sys.argv[3]

ylo = 0.0
yhi = 0.01/factor

# 0.000979387
# 0.004087083

markerSize = 2
lineWidth = 2
############# code
color = [1,2,4,8,9]
i = 0
g1.SetMarkerStyle(20+i)
g1.SetMarkerSize(markerSize)
g1.SetMarkerColor(color[i]) 
g1.SetLineColor(color[i])
g1.SetLineWidth(lineWidth)
g1.GetXaxis().SetTitle(xlabel)
g1.GetYaxis().SetTitle(ylabel)
g1.GetYaxis().SetTitleOffset(1.75)
i = 1
g2.SetMarkerStyle(20+i)
g2.SetMarkerSize(markerSize)
g2.SetMarkerColor(color[i]) 
g2.SetLineColor(color[i])
g2.SetLineWidth(lineWidth)
g2.GetXaxis().SetTitle(xlabel)
g2.GetYaxis().SetTitle(ylabel)
g2.GetYaxis().SetTitleOffset(1.75)
i = 2
g3.SetMarkerStyle(20+i)
g3.SetMarkerSize(markerSize)
g3.SetMarkerColor(color[i]) 
g3.SetLineColor(color[i])
g3.SetLineWidth(lineWidth)
g3.GetXaxis().SetTitle(xlabel)
g3.GetYaxis().SetTitle(ylabel)
g3.GetYaxis().SetTitleOffset(1.75)

g1.GetYaxis().SetNdivisions(5+100*5);
g2.GetYaxis().SetNdivisions(5+100*5);

print "q-hat(Neon)    = ", g1.GetMean(2)
print "q-hat(Krypton) = ", g2.GetMean(2)
print "q-hat(Xenon)   = ", g3.GetMean(2)
print "Global average = ", (g1.GetMean(2)+g2.GetMean(2)+g3.GetMean(2))/3
print "--------------------------------"

ll = ["Neon","Krypton","Xenon"]
il=0
ave = 0
norm = 0
error = 0
for gg in [g1,g2,g3]:
    y1 = gg.GetY()
    ye1 = gg.GetEY()
    ave1 = 0
    norm1 = 0
    for i in range(len(y1)):
        ave1 += y1[i]/ye1[i]
        norm1 += 1/ye1[i]
        ave += ave1
        norm += norm1
    # print "q-hat("+ll[il]+") = "+str(ave1/norm1)+" +/- "+str(1/norm1)
    print ("q-hat("+ll[il]+") = %.3f +/- %.3f" % (ave1/norm1,1/norm1))
    error += (1/norm1)**2
    il+=1
average = ave/norm
# print "Global average = "+str(ave/norm)+" +/- "+str(ROOT.TMath.Sqrt(error)/3) 
print ("Global average = %.3f +/- %.3f" % (average,ROOT.TMath.Sqrt(error)/3))

fontAxesSize = 28
fontAxesCode = 43
# axes range
g1.GetXaxis().SetLimits(0.24,0.99)
g1.GetYaxis().SetRangeUser(ylo,yhi)
g1.GetYaxis().SetRangeUser(-0.0999,0.699)
g1.GetYaxis().SetTitleOffset(1.5)

x0 = 0.625
y0 = 0.725
x1 = x0 + 0.325
y1 = y0 + 0.17
leg = ROOT.TLegend(0.2,0.5,0.4,0.78)
leg.SetTextFont(42)
leg.SetTextSize(0.04)
leg.SetBorderSize(0)
leg.SetFillStyle(0)
# leg.SetHeader("  BLE40")
leg.SetHeader("  BL30")
# leg.SetNColumns(3);
leg.AddEntry(g1,"Neon","ep")
leg.AddEntry(g2,"Krypton","ep")
leg.AddEntry(g3,"Xenon","ep")
# foo = ROOT.TGraph(0);
# foo.SetFillColor()

lxmin=0.24
lxmax=0.99

theoretical_qhat = 0.075
line = ROOT.TLine(lxmin, theoretical_qhat, lxmax, theoretical_qhat)
line.SetLineWidth(2)
line.SetLineStyle(2)
box = ROOT.TBox(lxmin,theoretical_qhat-0.005,lxmax,theoretical_qhat+0.015)
box.SetLineStyle(2)
box.SetLineWidth(2)
box.SetFillColorAlpha(13,0.5)

leg.AddEntry(box,"p+Pb, JHEP03(2013)122","fl")

line3 = ROOT.TLine(lxmin, 0.20, lxmax, 0.20) # BDMPS, http://dx.doi.org/10.1016/j.physletb.2015.07.048
line3.SetLineWidth(2)
line3.SetLineStyle(2)
box3 = ROOT.TBox(lxmin,0.2-0.02,lxmax,0.2+0.02)
box3.SetFillColorAlpha(13,0.5)

line2 = ROOT.TLine(lxmin, average, lxmax, average)
line2.SetLineWidth(2)
line2.SetLineStyle(3)

c = ROOT.TCanvas("canvas","canvas",800,600)
c.cd()
g1.GetXaxis().SetLimits(0,1)
g1.GetXaxis().SetNdivisions(505)
g1.Draw("AP")
box.Draw("SAME")
line.Draw("SAME")
# box3.Draw("SAME")
# line3.Draw("SAME")
g1.Draw("P SAME")
g2.Draw("P SAME")
g3.Draw("P SAME")

leg.Draw()


# AddLabel(0.2,0.88,"#hat{q}_{h} = #Delta#LTp_{T}^{2}#GT/L_{p} with 3 parameter fit")
# AddLabel(0.2, 0.81, "Fixed cross section #sigma_{ph} = 40 [mb]")
AddLabel(0.2,0.88,"#hat{q}_{h} = #Delta#LTp_{T}^{2}#GT/L_{p} with 2 parameter fit",1,22)
AddLabel(0.2, 0.81, "Fixed cross section #sigma_{ph} = 30 [mb]",1,22)
c.Print(fileout)
