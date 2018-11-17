import ROOT
ROOT.gROOT.SetStyle("Plain")
from array import array

c = ROOT.TCanvas("c","canvas",800,600)

xval = array("f", [0.16, 0.25, 0.34, 0.45, 0.55, 0.65, 0.75, 0.85, 0.95])
xerrminus = array("f", [0.06, 0.04999999999999999, 0.040000000000000036, 0.04999999999999999, 0.050000000000000044, 0.050000000000000044, 0.050000000000000044, 0.04999999999999993, 0.04999999999999993])
xerrplus = array("f", [0.04000000000000001, 0.04999999999999999, 0.06, 0.04999999999999999, 0.04999999999999993, 0.04999999999999993, 0.050000000000000044, 0.050000000000000044, 0.3500000000000001])
yval = array("f", [0.872, 0.814, 0.782, 0.759, 0.739, 0.721, 0.674, 0.625, 0.542])
yerrminus = array("f", [0.03026549190084311, 0.02816025568065745, 0.02630589287593181, 0.024515301344262524, 0.022803508501982758, 0.02308679276123039, 0.023769728648009424, 0.030675723300355937, 0.025059928172283336])
yerrplus = array("f", [0.03026549190084311, 0.02816025568065745, 0.02630589287593181, 0.024515301344262524, 0.022803508501982758, 0.02308679276123039, 0.023769728648009424, 0.030675723300355937, 0.025059928172283336])
numpoints = 9
p6820_d22x1y1 = ROOT.TGraphAsymmErrors(numpoints, xval, yval, xerrminus, xerrplus, yerrminus, yerrplus)
p6820_d22x1y1.SetName("/HepData/6820/d22x1y1")
p6820_d22x1y1.SetTitle("/HepData/6820/d22x1y1")
p6820_d22x1y1.Draw("AP")

fit = "pol4"
g0 = ROOT.TGraph(9);
gplus = ROOT.TGraph(9);
gminus = ROOT.TGraph(9);
for i in range(9):
  x = xval[i]
  y = yval[i]
  yplus = yval[i]+yerrplus[i]
  yminus = yval[i]-yerrminus[i]
  g0.SetPoint(i,x,y)
  gplus.SetPoint(i,x,yplus)
  gminus.SetPoint(i,x,yminus)
g0.Fit(fit)
gplus.Fit(fit)
gminus.Fit(fit)
f0 = g0.GetFunction(fit)
fplus = gplus.GetFunction(fit)
fminus = gminus.GetFunction(fit)
f0.Draw("same")
fplus.Draw("same")
fminus.Draw("same")

for i in range(4):
  z = ptbin[i]
  print z, f0(z), fplus(z)-fminus(z)

c.Print("p6820_d22x1y1.pdf")
