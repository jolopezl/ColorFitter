# Interpolate multiplicity data HERMES 2007
import ROOT
ROOT.gROOT.SetStyle("Plain")
from array import array

ptbin = [0.32, 0.53, 0.75, 0.94]

c = ROOT.TCanvas()
from numpy import log

# PI+ Rm He/D
numpoints = 9
xval = [0.16, 0.25, 0.35, 0.45, 0.55, 0.65, 0.75, 0.85, 0.95]

yval = [[0.943, 0.961, 0.95, 0.969, 0.959, 0.992, 0.975, 1.02, 0.917],
       [0.913, 0.902, 0.888, 0.885, 0.894, 0.878, 0.883, 0.856, 0.789],
       [0.872, 0.814, 0.782, 0.759, 0.739, 0.721, 0.674, 0.625, 0.542],
       [0.838, 0.768, 0.729, 0.701, 0.679, 0.659, 0.616, 0.574, 0.489]]


yerr = [[0.029614185789921695, 0.03157530680769389, 0.029832867780352598, 0.029410882339705485, 0.03008321791298265, 0.03220248437620924, 0.03312099032335839, 0.0442944691807002, 0.04],
       [0.03026549190084311, 0.03026549190084311, 0.0282842712474619, 0.02765863337187866, 0.026925824035672518, 0.027202941017470887, 0.028792360097775936, 0.03827531841800927, 0.03264965543462902],
       [0.03026549190084311, 0.02816025568065745, 0.02630589287593181, 0.024515301344262524, 0.022803508501982758, 0.02308679276123039, 0.023769728648009424, 0.030675723300355937, 0.025059928172283336],
       [0.02942787793912432, 0.0282842712474619, 0.025495097567963927, 0.022803508501982758, 0.02118962010041709, 0.021931712199461308, 0.022360679774997897, 0.030463092423455636, 0.025238858928247926]]

label = ["He","Ne","Ke","Xe"]
A = [4.40026,20.1797,83.7980,131.293]
A13 = []
for i in range(len(A)):
  A13.append(A[i]**(1/3))

ytemp = []
ytemperr = []

f=open("tgraph2d.dat","w")
for j in range(1,4):
  for i in range(9):
    f.write(str(xval[i])+"\t"+str(A[j])+"\t"+str(1-yval[j][i])+"\n")
f.close()

c2 = ROOT.TCanvas()
g2 = ROOT.TGraph2D("tgraph2d.dat")
g2.SetTitle("1-R;z;A")
g2.Draw("colz")
c2.Print("g2.pdf")

fitfunc = ROOT.TF2("fitfunc","([0]+[1]*x+[2]*x**2+[3]*x**3+[4]*x**4)*(1-y**[5])",0,1.1,15,140)
# fitfunc.SetParameter(1,0.0)
# fitfunc.SetParameter(2,0.0)
# fitfunc.SetParameter(3,0.0)
# fitfunc.SetParameter(4,0.0)
# fitfunc.SetParameter(5,0.0)
g2.Fit(fitfunc)

# c = ROOT.TCanvas()
# c.SetLogx()

# for i in range(9):
#   leg = ROOT.TLegend(0,0,0.3,0.1)
#   print "z-bin = ",xval[i]
#   for j in range(4):
#     ytemp.append(1.0-yval[j][i])
#     ytemperr.append(yerr[j][i])
#   print ytemp
#   print ytemperr
#   gr = ROOT.TGraphErrors()
#   for k in range(1,4):
#     print k,A[k],ytemp[k], ytemperr[k]
#     gr.SetPoint(k-1,A[k],ytemp[k])
#     gr.SetPointError(k-1,0,ytemperr[k])
#   gr.SetMarkerStyle(21)
#   gr.Draw("ap")
#   f1 = ROOT.TF1("f1","[0]*pow(x,[1])",10,150)
#   # f1 = ROOT.TF1("f1","0.04*pow(x,[0])",10,150)
#   gr.Fit(f1)
#   f1.SetLineColor(2)
#   f1.SetLineStyle(2)
#   f1.SetLineWidth(2)
#   # f1.Draw("same")
#   leg.AddEntry(gr,"data","lep")
#   leg.AddEntry(f1,"fit","l")
#   c.Print("test-zbin-"+str(xval[i])+".pdf")
#   ytemp = []
#   ytemperr = []

# g0 = ROOT.TGraph(9);
# gplus = ROOT.TGraph(9);
# gminus = ROOT.TGraph(9);
# for i in range(9):
#   x = xval[i]
#   y = yval[i]
#   yplus = yval[i]+yerrplus[i]
#   yminus = yval[i]-yerrminus[i]
#   g0.SetPoint(i,x,y)
#   gplus.SetPoint(i,x,yplus)
#   gminus.SetPoint(i,x,yminus)
# g0.Fit(fit)
# gplus.Fit(fit)
# gminus.Fit(fit)
# f0 = g0.GetFunction(fit)
# fplus = gplus.GetFunction(fit)
# fminus = gminus.GetFunction(fit)
# f0.Draw("same")
# fplus.Draw("same")
# fminus.Draw("same")

# new = ROOT.TGraphErrors(4);
# for i in range(4):
#   z = ptbin[i]
#   print "PI+ Xe", z, f0(z), fplus(z)-fminus(z)
#   new.SetPoint(i,z,f0(z))
#   new.SetPointError(i,0,(fplus(z)-fminus(z))/2.0)
# new.SetMarkerStyle(21)
# new.SetMarkerColor(2)
# new.SetLineColor(2)
# new.Draw("Psame")
# c.Print("p6820_d31x1y1.pdf")
