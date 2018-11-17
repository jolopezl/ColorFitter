import ROOT
from AtlasStyle import SetAtlasStyle, AddLabel
SetAtlasStyle()

from array import array

val = []
err = []

labels = ['BL','BLE','BL40','BL30','BLE40','BLE30']

xlabel = 'z'
ylabel = 'L_{p} [fm]'
filename = 'test_Lp'

# VALUES
val.append(array("f",[9.08462,5.39494,2.80624,1.96209]))   # BL
val.append(array("f",[9.39309,7.21143,4.54394,3.12418]))  # BLE
val.append(array("f",[8.11446,7.02926,5.20119,3.00113]))  # BL40
val.append(array("f",[6.8853,5.91803,4.29427,2.31287]))   # BL30
val.append(array("f",[7.63051,5.60696,3.35716,1.95077]))  # BLE40
val.append(array("f",[6.93319,4.95501,2.79043,1.38668]))  # BLE30
# ERRORS
err.append(array("f",[4.723,3.51195,2.35571,2.23841]))  # BL
err.append(array("f",[2.88202,1.66983,1.63229,1.22972]))  # BLE
err.append(array("f",[0.90411,0.646415,0.531775,0.351992]))  # BL40
err.append(array("f",[0.801357,0.571775,0.473234,0.318382]))  # BL30
err.append(array("f",[2.59589,1.48544,1.08585,0.94542]))  # BLE40
err.append(array("f",[2.47533,1.42262,1.0399,1.02507]))  # BLE30

# Prepare xaxis points
xval = array("f",[0.31,0.54,0.75,0.94])
xerr = array("f",[0,0,0,0])
xvaloff = []
offset = 0.01
offset = offset/2
for i in range(6):
    xvaloff.append(array("f",[0.32,0.53,0.75,0.94]))
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

x0 = 0.625
y0 = 0.765
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
g[0].GetYaxis().SetRangeUser(0.0001,14)
g[0].GetXaxis().SetNdivisions(505);
# ROOT.gStyle.SetEndErrorSize(5)
c = ROOT.TCanvas("c","title",800,600)
line00 = ROOT.TF1("line00","00",0.0,1.0);
line00.SetLineWidth(2);
line00.SetLineColor(1);
line00.SetLineStyle(2);
for i in range(6):
    if(i == 0):
        g[i].Draw("AP")
        # line00.Draw("SAME")
    else:
        g[i].Draw("P SAME")
AddLabel(0.2,0.2,"He subtracted #rho = 0.0")
leg.Draw()

c.Print(filename+".pdf")
# c.SetGrayscale()
# c.Print(filename+"_gray.pdf")
