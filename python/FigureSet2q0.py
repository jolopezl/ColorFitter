import ROOT
from AtlasStyle import SetAtlasStyle, AddLabel
SetAtlasStyle()

from array import array

val = []
err = []

labels = ['BL','BLE','BL40','BL30','BLE40','BLE30']

xlabel = 'z'
ylabel = 'q_{0} [GeV^{2}fm]'
filename = 'test_q0'

# VALUES
val.append(array("f",[2.14986,2.6888,1.44892,1.33733]))   # BL
val.append(array("f",[2.13066,2.43684,1.13799,1.03506]))  # BLE
val.append(array("f",[2.21524,2.45588,1.08766,1.04232]))  # BL40
val.append(array("f",[2.3263,2.59993,1.17443,1.19986]))   # BL30
val.append(array("f",[2.25389,2.65101,1.31542,1.34573]))  # BLE40
val.append(array("f",[2.32139,2.78111,1.45245,1.71481]))  # BLE30
# ERRORS
err.append(array("f",[0.344191,0.783364,1.54395,2.62914]))  # BL
err.append(array("f",[0.251622,0.442584,1.15823,1.92342]))  # BLE
err.append(array("f",[0.21074,0.390949,1.04471,1.96152]))  # BL40
err.append(array("f",[0.226337,0.417557,1.13325,2.26414]))  # BL30
err.append(array("f",[0.30239,0.489832,1.29203,2.52295]))  # BLE40
err.append(array("f",[0.334446,0.541974,1.44045,3.1632]))  # BLE30

# Prepare xaxis points
xval = array("f",[0.32,0.53,0.75,0.94])
xerr = array("f",[0,0,0,0])
xvaloff = []
offset = 0.01
offset = offset/2
for i in range(6):
    xvaloff.append(array("f",[0.31,0.54,0.75,0.94]))
for i in range(4):   
    xvaloff[0][i] = xval[i] - offset/2
    xvaloff[1][i] = xval[i] + offset/2
    xvaloff[2][i] = xval[i] - offset/2 - offset
    xvaloff[3][i] = xval[i] + offset/2 + offset
    xvaloff[4][i] = xval[i] - offset/2 - 2*offset
    xvaloff[5][i] = xval[i] + offset/2 + 2*offset

# Prepare plots to be filled
markers = [20,21,22,23,29,33]
# markers = [24,25,26,27,28,32]
colors = [1,2,3,4,6,9]

g = []
for i in range(6):
    g.append(ROOT.TGraphErrors(4,xvaloff[i],val[i],xerr,err[i]))
    g[i].SetMarkerStyle(markers[i])
    g[i].SetMarkerColor(colors[i])
    g[i].SetLineColor(colors[i])
    g[i].GetXaxis().SetTitle(xlabel)
    g[i].GetYaxis().SetTitle(ylabel)

x0 = 0.175
y0 = 0.175
x1 = x0 + 0.3
y1 = y0 + 0.15
leg = ROOT.TLegend(x0,y0,x1,y1)
leg.SetNColumns(2)
leg.SetTextFont(43)
leg.SetTextSize(28)
leg.SetBorderSize(0)
leg.SetFillStyle(0)
for i in range(6):
    leg.AddEntry(g[i],labels[i],"ep")

g[0].GetXaxis().SetLimits(0,1)
g[0].GetXaxis().SetNdivisions(505);
# ROOT.gStyle.SetEndErrorSize(7.5)
c = ROOT.TCanvas("c","title",800,600)
line00 = ROOT.TF1("line00","00",0.0,1.0);
line00.SetLineWidth(2);
line00.SetLineColor(1);
line00.SetLineStyle(2);
for i in range(6):
    if(i == 0):
        g[i].Draw("AP")
        line00.Draw("SAME")
    else:
        g[i].Draw("P SAME")
AddLabel(0.2,0.88,"He subtracted #rho = 0.0")
leg.Draw()

c.Print(filename+".pdf")
c.SetGrayscale()
c.Print(filename+"_gray.pdf")
