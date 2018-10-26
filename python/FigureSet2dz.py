import ROOT
from AtlasStyle import SetAtlasStyle, AddLabel
SetAtlasStyle()

from array import array

val = []
err = []

labels = ['BLE','BLE40','BLE30']

xlabel = 'z'
ylabel = '#delta z'
filename = 'test_dz'

# VALUES
val.append(array("f",[0.0670631,-0.089505,-0.087014,-0.0578115]))  # BLE
val.append(array("f",[0.00575979,-0.0251509,-0.0443178,-0.0249268]))  # BLE40
val.append(array("f",[-0.000616009,-0.0182998,-0.038861,-0.0239079]))  # BLE30
# ERRORS
err.append(array("f",[0.0588113,0.0935059,0.120255,0.0797446]))  # BLE
err.append(array("f",[0.031416,0.030734,0.0357612,0.0288715]))  # BLE40
err.append(array("f",[0.0297718,0.0297642,0.0351889,0.0332699]))  # BLE30

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
markers = [21,29,33]
# markers = [24,25,26,27,28,32]
colors = [2,6,9]

g = []
for i in range(3):
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
# leg.SetNColumns(2)
leg.SetTextFont(43)
leg.SetTextSize(28)
leg.SetBorderSize(0)
leg.SetFillStyle(0)
for i in range(3):
    leg.AddEntry(g[i],labels[i],"ep")

g[0].GetXaxis().SetLimits(0,1)
g[0].GetYaxis().SetRangeUser(-0.29,0.29)
g[0].GetXaxis().SetNdivisions(505);
# ROOT.gStyle.SetEndErrorSize(7.5)
c = ROOT.TCanvas("c","title",800,600)
line00 = ROOT.TF1("line00","00",0.0,1.0);
line00.SetLineWidth(2);
line00.SetLineColor(1);
line00.SetLineStyle(2);
for i in range(3):
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
