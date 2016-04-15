import ROOT
from AtlasStyle import SetAtlasStyle, AddLabel
SetAtlasStyle()

from array import array

val = []
err = []

labels = ['BL','BLE','BL40','BL30','BLE40','BLE30']

xlabel = 'z_{h}'
ylabel = 'L_{p} [fm]'
filename = 'test_Lp'

# VALUES
val.append(array("f",[14.89191345,7.080143499,3.029804261,1.992745574]))   # BL
val.append(array("f",[13.93688552,7.766694217,4.681843459,2.833307188]))  # BLE
val.append(array("f",[9.50174555,7.239484549,5.388096332,3.033429451]))  # BL40
val.append(array("f",[8.156268927,6.11454026,4.45823924,2.352734198]))   # BL30
val.append(array("f",[12.12615213,6.136720473,3.404236507,1.694836305]))  # BLE40
val.append(array("f",[11.52592869,5.508979276,2.84003639,1.121133062]))  # BLE30
# ERRORS
err.append(array("f",[15.58210515,5.559773446,4.6716252,2.849262832]))  # BL
err.append(array("f",[17.15041095,2.937900015,2.582794139,2.203179308]))  # BLE
err.append(array("f",[1.970533965,1.064247156,0.869821482,0.497393965]))  # BL40
err.append(array("f",[1.759058613,0.943243185,0.772106194,0.450814849]))  # BL30
err.append(array("f",[9.881838808,2.727141719,1.715237301,1.34170283]))  # BLE40
err.append(array("f",[9.417060244,2.603135902,1.625346778,1.488339746]))  # BLE30

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

x0 = 0.625
y0 = 0.7
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