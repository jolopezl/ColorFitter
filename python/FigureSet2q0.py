import ROOT
from AtlasStyle import SetAtlasStyle, AddLabel
SetAtlasStyle()

from array import array

val = []
err = []

labels = ['BL','BLE','BL40','BL30','BLE40','BLE30']

xlabel = 'z_{h}'
ylabel = 'q_{0} [GeV^{2}fm]'
filename = 'test_q0'

# VALUES
val.append(array("f",[1.938687537,2.448948249,1.393052958,1.32610177]))   # BL
val.append(array("f",[1.960080704,2.382862333,1.131726636,1.076690994]))  # BLE
val.append(array("f",[2.125454155,2.432882642,1.072942811,1.028574807]))  # BL40
val.append(array("f",[2.212336101,2.570475157,1.152221654,1.19471209]))   # BL30
val.append(array("f",[2.013385697,2.567153257,1.309393114,1.471376678]))  # BLE40
val.append(array("f",[2.034191371,2.669101521,1.437872973,2.024431129]))  # BLE30
# ERRORS
err.append(array("f",[0.386524721,0.706124829,1.718347814,2.694773181]))  # BL
err.append(array("f",[0.468834974,0.453703411,1.100816193,2.056530162]))  # BLE
err.append(array("f",[0.219496572,0.396206752,1.031536588,1.953019171]))  # BL40
err.append(array("f",[0.238980688,0.425794534,1.116852869,2.242302313]))  # BL30
err.append(array("f",[0.376595945,0.562137198,1.304146158,2.792658242]))  # BLE40
err.append(array("f",[0.393934159,0.629025801,1.461976975,5.921170572]))  # BLE30

# Prepare xaxis points
xval = array("f",[0.32,0.53,0.75,0.94])
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

x0 = 0.2
y0 = 0.2
x1 = x0 + 0.3
y1 = y0 + 0.215
leg = ROOT.TLegend(x0,y0,x1,y1)
leg.SetNColumns(2)
leg.SetTextFont(43)
leg.SetTextSize(28)
leg.SetBorderSize(0)
leg.SetFillStyle(0)
for i in range(6):
    leg.AddEntry(g[i],labels[i],"ep")

# ROOT.gStyle.SetEndErrorSize(7.5)
c = ROOT.TCanvas()
for i in range(6):
    if(i == 0):
        g[i].Draw("AP")
    else:
        g[i].Draw("P SAME")
AddLabel(0.2,0.88,"He subtracted #rho = 0.0")
leg.Draw()

c.Print(filename+".pdf")
c.SetGrayscale()
c.Print(filename+"_gray.pdf")