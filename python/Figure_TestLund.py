import ROOT
from array import array

import ROOT
from AtlasStyle import SetAtlasStyle, AddLabel
SetAtlasStyle()

#### TEST OF FIT TO LUND STRING MODEL ####
xval = array("f",[0.32,0.53,0.75,0.94])
# xerr = array("f",[0.,0.,0.,0.])
xerr = array("f",[0.20/2.0,0.22/2.0,0.22/2.0,0.16/2.0])

print xerr
for i in range(4):
    xerr[i] = xerr[i]/(12.**0.5)
print xerr

yval = array("f",[8.156268927,6.11454026,4.45823924,2.352734198])
yerr = array("f",[1.759058613,0.943243185,0.772106194,0.450814849])
gwr = ROOT.TGraphErrors(4,xval,yval,xerr,yerr)
gwr.SetMarkerStyle(20)
lund = ROOT.TF1("lund","[0]*x*(log(1/(x*x))-1+x*x)/(1-x*x)", -0.01, 1.01)
c2 = ROOT.TCanvas("c2","title",800,600)
gwr.SetMarkerStyle(23)
gwr.SetMarkerColor(4)
gwr.SetLineColor(4)
# gwr.GetYaxis().SetRangeUser(0,12.5)
# gwr.GetXaxis().SetRangeUser(0.0,1.0)
gwr.SetTitle(";z_{h};L_{p} [fm]")

gwr.Fit(lund,"N")
par = lund.GetParameter(0)
print par

lund.GetYaxis().SetRangeUser(0,12.5)
lund.GetXaxis().SetRangeUser(0.0,1.1)
lund.SetLineColor(4)
lund.SetLineWidth(2)
lund.SetLineStyle(2)

gwr.GetYaxis().SetRangeUser(0,12.5)
gwr.GetXaxis().SetRangeUser(0.25,1.0)

gwr.Draw("AP")
lund.Draw("SAME")
# gwr.GetFunction("lund").Draw()


x0 = 0.525
y0 = 0.765
x1 = x0 + 0.3
y1 = y0 + 0.15
leg = ROOT.TLegend(x0,y0,x1,y1)
leg.SetTextFont(43)
leg.SetTextSize(28)
leg.SetBorderSize(0)
leg.SetFillStyle(0)
leg.AddEntry(gwr,"BL30","lep")
leg.AddEntry(lund,"Lund String Model","l")
leg.Draw()

c2.Print("test_lund.pdf")

# val = []
# err = []

# xval = array("f",[0.32,0.53,0.75,0.94])
# yerr = array("f",[9.417060244,2.603135902,1.625346778,1.488339746])
# # VALUES
# val.append(array("f",[14.89191345,7.080143499,3.029804261,1.992745574]))   # BL
# val.append(array("f",[13.93688552,7.766694217,4.681843459,2.833307188]))  # BLE
# val.append(array("f",[9.50174555,7.239484549,5.388096332,3.033429451]))  # BL40
# val.append(array("f",[8.156268927,6.11454026,4.45823924,2.352734198]))   # BL30
# val.append(array("f",[12.12615213,6.136720473,3.404236507,1.694836305]))  # BLE40
# val.append(array("f",[11.52592869,5.508979276,2.84003639,1.121133062]))  # BLE30
# # ERRORS
# err.append(array("f",[15.58210515,5.559773446,4.6716252,2.849262832]))  # BL
# err.append(array("f",[17.15041095,2.937900015,2.582794139,2.203179308]))  # BLE
# err.append(array("f",[1.970533965,1.064247156,0.869821482,0.497393965]))  # BL40
# err.append(array("f",[1.759058613,0.943243185,0.772106194,0.450814849]))  # BL30
# err.append(array("f",[9.881838808,2.727141719,1.715237301,1.34170283]))  # BLE40
# err.append(array("f",[9.417060244,2.603135902,1.625346778,1.488339746]))  # BLE30

# # Prepare plots to be filled
# markers = [20,21,22,23,29,33]
# # markers = [24,25,26,27,28,32]
# colors = [1,2,3,4,6,9]


# labels = ['BL','BLE','BL40','BL30','BLE40','BLE30']

# xlabel = 'z_{h}'
# ylabel = 'L_{p} [fm]'

# g = []
# for i in range(6):
#     g.append(ROOT.TGraphErrors(4,xval,val[i],xerr,err[i]))
#     g[i].SetMarkerStyle(markers[i])
#     g[i].SetMarkerColor(colors[i])
#     g[i].SetLineColor(colors[i])
#     g[i].GetXaxis().SetTitle(xlabel)
#     g[i].GetYaxis().SetTitle(ylabel)

# x0 = 0.625
# y0 = 0.765
# x1 = x0 + 0.3
# y1 = y0 + 0.15
# leg = ROOT.TLegend(x0,y0,x1,y1)
# leg.SetNColumns(2)
# leg.SetTextFont(43)
# leg.SetTextSize(28)
# leg.SetBorderSize(0)
# leg.SetFillStyle(0)
# for i in range(6):
#     leg.AddEntry(g[i],labels[i],"ep")

# for i in range(6):
#     g[i].Fit("lund")
#     g[i].GetFunction("lund").SetLineColor(colors[i])

# # ROOT.gStyle.SetEndErrorSize(7.5)
# c = ROOT.TCanvas("c","title",800,600)
# line00 = ROOT.TF1("line00","00",0.0,1.0);
# line00.SetLineWidth(2);
# line00.SetLineColor(1);
# line00.SetLineStyle(2);
# for i in range(6):
#     if(i == 0):
#         g[i].Draw("AP")
#         # line00.Draw("SAME")
#     else:
#         g[i].Draw("P SAME")
# AddLabel(0.2,0.88,"He subtracted #rho = 0.0")
# leg.Draw()

# # c.SetLogy()

# c.Print("test_lund.pdf")