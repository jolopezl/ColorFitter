# Interpolate multiplicity data HERMES 2007
import ROOT
ROOT.gROOT.SetStyle("Plain")
from array import array

ptbin = [0.32, 0.53, 0.75, 0.94]
c = ROOT.TCanvas()

# PI+ Rm He/D
xval = array("f", [0.16, 0.25, 0.35, 0.45, 0.55, 0.65, 0.75, 0.85, 0.95])
xerrminus = array("f", [0.06, 0.04999999999999999, 0.04999999999999999, 0.04999999999999999, 0.050000000000000044, 0.050000000000000044, 0.050000000000000044, 0.04999999999999993, 0.04999999999999993])
xerrplus = array("f", [0.04000000000000001, 0.04999999999999999, 0.050000000000000044, 0.04999999999999999, 0.04999999999999993, 0.04999999999999993, 0.050000000000000044, 0.050000000000000044, 0.3500000000000001])
yval = array("f", [0.943, 0.961, 0.95, 0.969, 0.959, 0.992, 0.975, 1.02, 0.917])
yerrminus = array("f", [0.029614185789921695, 0.03157530680769389, 0.029832867780352598, 0.029410882339705485, 0.03008321791298265, 0.03220248437620924, 0.03312099032335839, 0.0442944691807002, 0.04])
yerrplus = array("f", [0.029614185789921695, 0.03157530680769389, 0.029832867780352598, 0.029410882339705485, 0.03008321791298265, 0.03220248437620924, 0.03312099032335839, 0.0442944691807002, 0.04])
ystatminus = array("f", [0.006, 0.006, 0.007, 0.009, 0.011, 0.014, 0.016, 0.021, 0.024])
ystatplus = array("f", [0.006, 0.006, 0.007, 0.009, 0.011, 0.014, 0.016, 0.021, 0.024])
numpoints = 9
p6820_d4x1y1 = ROOT.TGraphAsymmErrors(numpoints, xval, yval, xerrminus, xerrplus, yerrminus, yerrplus)
p6820_d4x1y1.SetName("/HepData/6820/d4x1y1 PI+ He")
p6820_d4x1y1.SetTitle("/HepData/6820/d4x1y1 PI+ He")
p6820_d4x1y1.Draw("AP")


doStat = False # compute the values we need

fit = "pol4"
g0 = ROOT.TGraph(9);
gplus = ROOT.TGraph(9);
gminus = ROOT.TGraph(9);
for i in range(9):
  x = xval[i]
  y = yval[i]
  if (doStat):
    yplus = yval[i]+ystatplus[i]
    yminus = yval[i]-ystatminus[i]
  else: # add whole error bar
    yplus = yval[i]+yerrplus[i]
    yminus = yval[i]-yerrminus[i]
  g0.SetPoint(i,x,y)
  gplus.SetPoint(i,x,yplus)
  gminus.SetPoint(i,x,yminus)
  print xval[i], "\t", yval[i], "\t", 0.0, "\t", yerrplus[i]
g0.Fit(fit)
gplus.Fit(fit)
gminus.Fit(fit)
f0 = g0.GetFunction(fit)
fplus = gplus.GetFunction(fit)
fminus = gminus.GetFunction(fit)
f0.Draw("same")
fplus.Draw("same")
fminus.Draw("same")

new = ROOT.TGraphErrors(4);
for i in range(4):
  z = ptbin[i]
  print "PI+ He", z, f0(z), fplus(z)-fminus(z)
  new.SetPoint(i,z,f0(z))
  new.SetPointError(i,0,(fplus(z)-fminus(z))/2.0)
new.SetMarkerStyle(21)
new.SetMarkerColor(2)
new.SetLineColor(2)
new.Draw("Psame")
c.Print("p6820_d4x1y1.pdf")

# PI+ Rm Ne/D
xval = array("f", [0.16, 0.25, 0.35, 0.45, 0.55, 0.65, 0.75, 0.85, 0.95])
xerrminus = array("f", [0.06, 0.04999999999999999, 0.04999999999999999, 0.04999999999999999, 0.050000000000000044, 0.050000000000000044, 0.050000000000000044, 0.04999999999999993, 0.04999999999999993])
xerrplus = array("f", [0.04000000000000001, 0.04999999999999999, 0.050000000000000044, 0.04999999999999999, 0.04999999999999993, 0.04999999999999993, 0.050000000000000044, 0.050000000000000044, 0.3500000000000001])
yval = array("f", [0.913, 0.902, 0.888, 0.885, 0.894, 0.878, 0.883, 0.856, 0.789])
yerrminus = array("f", [0.03026549190084311, 0.03026549190084311, 0.0282842712474619, 0.02765863337187866, 0.026925824035672518, 0.027202941017470887, 0.028792360097775936, 0.03827531841800927, 0.03264965543462902])
yerrplus = array("f", [0.03026549190084311, 0.03026549190084311, 0.0282842712474619, 0.02765863337187866, 0.026925824035672518, 0.027202941017470887, 0.028792360097775936, 0.03827531841800927, 0.03264965543462902])
ystatminus = array("f", [0.004, 0.004, 0.004, 0.006, 0.007, 0.008, 0.01, 0.013, 0.015])
ystatplus = array("f", [0.004, 0.004, 0.004, 0.006, 0.007, 0.008, 0.01, 0.013, 0.015])
numpoints = 9
p6820_d13x1y1 = ROOT.TGraphAsymmErrors(numpoints, xval, yval, xerrminus, xerrplus, yerrminus, yerrplus)
p6820_d13x1y1.SetName("/HepData/6820/d13x1y1 PI+ Ne")
p6820_d13x1y1.SetTitle("/HepData/6820/d13x1y1 PI+ Ne")
p6820_d13x1y1.Draw("AP")

fit = "pol4"
g0 = ROOT.TGraph(9);
gplus = ROOT.TGraph(9);
gminus = ROOT.TGraph(9);
for i in range(9):
  x = xval[i]
  y = yval[i]
  if (doStat):
    yplus = yval[i]+ystatplus[i]
    yminus = yval[i]-ystatminus[i]
  else: # add whole error bar
    yplus = yval[i]+yerrplus[i]
    yminus = yval[i]-yerrminus[i]
  g0.SetPoint(i,x,y)
  gplus.SetPoint(i,x,yplus)
  gminus.SetPoint(i,x,yminus)
  print xval[i], "\t", yval[i], "\t", 0.0, "\t", yerrplus[i]
g0.Fit(fit)
gplus.Fit(fit)
gminus.Fit(fit)
f0 = g0.GetFunction(fit)
fplus = gplus.GetFunction(fit)
fminus = gminus.GetFunction(fit)
f0.Draw("same")
fplus.Draw("same")
fminus.Draw("same")

new = ROOT.TGraphErrors(4);
for i in range(4):
  z = ptbin[i]
  print "PI+ Ne", z, f0(z), fplus(z)-fminus(z)
  new.SetPoint(i,z,f0(z))
  new.SetPointError(i,0,(fplus(z)-fminus(z))/2.0)
new.SetMarkerStyle(21)
new.SetMarkerColor(2)
new.SetLineColor(2)
new.Draw("Psame")
c.Print("p6820_d13x1y1.pdf")

# PI+ Rm Kr/D
xval = array("f", [0.16, 0.25, 0.34, 0.45, 0.55, 0.65, 0.75, 0.85, 0.95])
xerrminus = array("f", [0.06, 0.04999999999999999, 0.040000000000000036, 0.04999999999999999, 0.050000000000000044, 0.050000000000000044, 0.050000000000000044, 0.04999999999999993, 0.04999999999999993])
xerrplus = array("f", [0.04000000000000001, 0.04999999999999999, 0.06, 0.04999999999999999, 0.04999999999999993, 0.04999999999999993, 0.050000000000000044, 0.050000000000000044, 0.3500000000000001])
yval = array("f", [0.872, 0.814, 0.782, 0.759, 0.739, 0.721, 0.674, 0.625, 0.542])
yerrminus = array("f", [0.03026549190084311, 0.02816025568065745, 0.02630589287593181, 0.024515301344262524, 0.022803508501982758, 0.02308679276123039, 0.023769728648009424, 0.030675723300355937, 0.025059928172283336])
yerrplus = array("f", [0.03026549190084311, 0.02816025568065745, 0.02630589287593181, 0.024515301344262524, 0.022803508501982758, 0.02308679276123039, 0.023769728648009424, 0.030675723300355937, 0.025059928172283336])
ystatminus = array("f",[0.004, 0.003, 0.004, 0.005, 0.006, 0.007, 0.009, 0.01, 0.012]);
ystatplus = array("f",[0.004, 0.003, 0.004, 0.005, 0.006, 0.007, 0.009, 0.01, 0.012]);
numpoints = 9
p6820_d22x1y1 = ROOT.TGraphAsymmErrors(numpoints, xval, yval, xerrminus, xerrplus, yerrminus, yerrplus)
p6820_d22x1y1.SetName("/HepData/6820/d22x1y1 PI+ Kr")
p6820_d22x1y1.SetTitle("/HepData/6820/d22x1y1 PI+ Kr")
p6820_d22x1y1.Draw("AP")

fit = "pol4"
g0 = ROOT.TGraph(9);
gplus = ROOT.TGraph(9);
gminus = ROOT.TGraph(9);
for i in range(9):
  x = xval[i]
  y = yval[i]
  if (doStat):
    yplus = yval[i]+ystatplus[i]
    yminus = yval[i]-ystatminus[i]
  else: # add whole error bar
    yplus = yval[i]+yerrplus[i]
    yminus = yval[i]-yerrminus[i]
  g0.SetPoint(i,x,y)
  gplus.SetPoint(i,x,yplus)
  gminus.SetPoint(i,x,yminus)
  print xval[i], "\t", yval[i], "\t", 0.0, "\t", yerrplus[i]
g0.Fit(fit)
gplus.Fit(fit)
gminus.Fit(fit)
f0 = g0.GetFunction(fit)
fplus = gplus.GetFunction(fit)
fminus = gminus.GetFunction(fit)
f0.Draw("same")
fplus.Draw("same")
fminus.Draw("same")

new = ROOT.TGraphErrors(4);
for i in range(4):
  z = ptbin[i]
  print "PI+ Kr", z, f0(z), fplus(z)-fminus(z)
  new.SetPoint(i,z,f0(z))
  new.SetPointError(i,0,(fplus(z)-fminus(z))/2.0)
new.SetMarkerStyle(21)
new.SetMarkerColor(2)
new.SetLineColor(2)
new.Draw("Psame")
c.Print("p6820_d22x1y1.pdf")

# PI+ Rm Xe/D
xval = array("f", [0.16, 0.25, 0.35, 0.44, 0.55, 0.65, 0.75, 0.84, 0.95])
xerrminus = array("f", [0.06, 0.04999999999999999, 0.04999999999999999, 0.03999999999999998, 0.050000000000000044, 0.050000000000000044, 0.050000000000000044, 0.039999999999999925, 0.04999999999999993])
xerrplus = array("f", [0.04000000000000001, 0.04999999999999999, 0.050000000000000044, 0.06, 0.04999999999999993, 0.04999999999999993, 0.050000000000000044, 0.06000000000000005, 0.3500000000000001])
yval = array("f", [0.838, 0.768, 0.729, 0.701, 0.679, 0.659, 0.616, 0.574, 0.489])
yerrminus = array("f", [0.02942787793912432, 0.0282842712474619, 0.025495097567963927, 0.022803508501982758, 0.02118962010041709, 0.021931712199461308, 0.022360679774997897, 0.030463092423455636, 0.025238858928247926])
yerrplus = array("f", [0.02942787793912432, 0.0282842712474619, 0.025495097567963927, 0.022803508501982758, 0.02118962010041709, 0.021931712199461308, 0.022360679774997897, 0.030463092423455636, 0.025238858928247926])
ystatminus = array("f", [0.005, 0.004, 0.005, 0.006, 0.007, 0.009, 0.01, 0.012, 0.014])
ystatplus = array("f", [0.005, 0.004, 0.005, 0.006, 0.007, 0.009, 0.01, 0.012, 0.014])
numpoints = 9
p6820_d31x1y1 = ROOT.TGraphAsymmErrors(numpoints, xval, yval, xerrminus, xerrplus, yerrminus, yerrplus)
p6820_d31x1y1.SetName("/HepData/6820/d31x1y1 PI+ Xe")
p6820_d31x1y1.SetTitle("/HepData/6820/d31x1y1 PI+ Xe")
p6820_d31x1y1.Draw("AP")

fit = "pol4"
g0 = ROOT.TGraph(9);
gplus = ROOT.TGraph(9);
gminus = ROOT.TGraph(9);
for i in range(9):
  x = xval[i]
  y = yval[i]
  if (doStat):
    yplus = yval[i]+ystatplus[i]
    yminus = yval[i]-ystatminus[i]
  else: # add whole error bar
    yplus = yval[i]+yerrplus[i]
    yminus = yval[i]-yerrminus[i]
  g0.SetPoint(i,x,y)
  gplus.SetPoint(i,x,yplus)
  gminus.SetPoint(i,x,yminus)
  print xval[i], "\t", yval[i], "\t", 0.0, "\t", yerrplus[i]
g0.Fit(fit)
gplus.Fit(fit)
gminus.Fit(fit)
f0 = g0.GetFunction(fit)
fplus = gplus.GetFunction(fit)
fminus = gminus.GetFunction(fit)
f0.Draw("same")
fplus.Draw("same")
fminus.Draw("same")

new = ROOT.TGraphErrors(4);
for i in range(4):
  z = ptbin[i]
  print "PI+ Xe", z, f0(z), fplus(z)-fminus(z)
  new.SetPoint(i,z,f0(z))
  new.SetPointError(i,0,(fplus(z)-fminus(z))/2.0)
new.SetMarkerStyle(21)
new.SetMarkerColor(2)
new.SetLineColor(2)
new.Draw("Psame")
c.Print("p6820_d31x1y1.pdf")

# # PI- Rm He/D
# xval = array("f", [0.16, 0.25, 0.34, 0.44, 0.55, 0.64, 0.75, 0.85, 0.96])
# xerrminus = array("f", [0.06, 0.04999999999999999, 0.040000000000000036, 0.03999999999999998, 0.050000000000000044, 0.040000000000000036, 0.050000000000000044, 0.04999999999999993, 0.05999999999999994])
# xerrplus = array("f", [0.04000000000000001, 0.04999999999999999, 0.06, 0.06, 0.04999999999999993, 0.05999999999999994, 0.050000000000000044, 0.050000000000000044, 0.3400000000000001])
# yval = array("f", [0.942, 0.946, 0.955, 0.96, 0.972, 0.961, 0.979, 0.984, 0.899])
# yerrminus = array("f", [0.0356931365951495, 0.036496575181789316, 0.03298484500494128, 0.03162277660168379, 0.03269556544854363, 0.03354101966249685, 0.03982461550347976, 0.05869412236331675, 0.04964876634922564])
# yerrplus = array("f", [0.0356931365951495, 0.036496575181789316, 0.03298484500494128, 0.03162277660168379, 0.03269556544854363, 0.03354101966249685, 0.03982461550347976, 0.05869412236331675, 0.04964876634922564])
# ystatminus = array("f", [0.007, 0.006, 0.008, 0.01, 0.013, 0.015, 0.019, 0.023, 0.028])
# ystatplus = array("f", [0.007, 0.006, 0.008, 0.01, 0.013, 0.015, 0.019, 0.023, 0.028])
# numpoints = 9
# p6820_d40x1y1 = ROOT.TGraphAsymmErrors(numpoints, xval, yval, xerrminus, xerrplus, yerrminus, yerrplus)
# p6820_d40x1y1.SetName("/HepData/6820/d40x1y1 PI- He")
# p6820_d40x1y1.SetTitle("/HepData/6820/d40x1y1 PI- He")
# p6820_d40x1y1.Draw("AP")

# fit = "pol4"
# g0 = ROOT.TGraph(9);
# gplus = ROOT.TGraph(9);
# gminus = ROOT.TGraph(9);
# for i in range(9):
#   x = xval[i]
#   y = yval[i]
#   yplus = yval[i]+ystatplus[i]
#   yminus = yval[i]-ystatminus[i]
#   g0.SetPoint(i,x,y)
#   gplus.SetPoint(i,x,yplus)
#   gminus.SetPoint(i,x,yminus)
#   print xval[i], "\t", yval[i], "\t", 0.0, "\t", yerrplus[i]
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
#   print "PI- He", z, f0(z), fplus(z)-fminus(z)
#   new.SetPoint(i,z,f0(z))
#   new.SetPointError(i,0,(fplus(z)-fminus(z))/2.0)
# new.SetMarkerStyle(21)
# new.SetMarkerColor(2)
# new.SetLineColor(2)
# new.Draw("Psame")
# c.Print("p6820_d40x1y1.pdf")

# # PI- Rm Ne/D
# xval = array("f", [0.16, 0.25, 0.34, 0.45, 0.55, 0.65, 0.75, 0.85, 0.95])
# xerrminus = array("f", [0.06, 0.04999999999999999, 0.040000000000000036, 0.04999999999999999, 0.050000000000000044, 0.050000000000000044, 0.050000000000000044, 0.04999999999999993, 0.04999999999999993])
# xerrplus = array("f", [0.04000000000000001, 0.04999999999999999, 0.06, 0.04999999999999999, 0.04999999999999993, 0.04999999999999993, 0.050000000000000044, 0.050000000000000044, 0.3500000000000001])
# yval = array("f", [0.898, 0.889, 0.881, 0.883, 0.879, 0.879, 0.876, 0.877, 0.787])
# yerrminus = array("f", [0.03622154055254966, 0.03622154055254966, 0.03337663853655728, 0.029614185789921695, 0.029120439557122076, 0.030675723300355937, 0.0360555127546399, 0.05797413216254298, 0.044384682042344296])
# yerrplus = array("f", [0.03622154055254966, 0.03622154055254966, 0.03337663853655728, 0.029614185789921695, 0.029120439557122076, 0.030675723300355937, 0.0360555127546399, 0.05797413216254298, 0.044384682042344296])
# ystatminus = array("f", [0.004, 0.004, 0.005, 0.006, 0.008, 0.01, 0.012, 0.015, 0.017])
# ystatplus = array("f", [0.004, 0.004, 0.005, 0.006, 0.008, 0.01, 0.012, 0.015, 0.017])
# numpoints = 9
# p6820_d49x1y1 = ROOT.TGraphAsymmErrors(numpoints, xval, yval, xerrminus, xerrplus, yerrminus, yerrplus)
# p6820_d49x1y1.SetName("/HepData/6820/d49x1y1 PI- Ne")
# p6820_d49x1y1.SetTitle("/HepData/6820/d49x1y1 PI- Ne")
# p6820_d49x1y1.Draw("AP")

# fit = "pol4"
# g0 = ROOT.TGraph(9);
# gplus = ROOT.TGraph(9);
# gminus = ROOT.TGraph(9);
# for i in range(9):
#   x = xval[i]
#   y = yval[i]
#   yplus = yval[i]+ystatplus[i]
#   yminus = yval[i]-ystatminus[i]
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
#   print "PI- Ne", z, f0(z), fplus(z)-fminus(z)
#   new.SetPoint(i,z,f0(z))
#   new.SetPointError(i,0,(fplus(z)-fminus(z))/2.0)
# new.SetMarkerStyle(21)
# new.SetMarkerColor(2)
# new.SetLineColor(2)
# new.Draw("Psame")
# c.Print("p6820_d49x1y1.pdf")

# # PI- Rm Kr/D
# xval = array("f", [0.16, 0.25, 0.34, 0.44, 0.55, 0.65, 0.75, 0.85, 0.95])
# xerrminus = array("f", [0.06, 0.04999999999999999, 0.040000000000000036, 0.03999999999999998, 0.050000000000000044, 0.050000000000000044, 0.050000000000000044, 0.04999999999999993, 0.04999999999999993])
# xerrplus = array("f", [0.04000000000000001, 0.04999999999999999, 0.06, 0.06, 0.04999999999999993, 0.04999999999999993, 0.050000000000000044, 0.050000000000000044, 0.3500000000000001])
# yval = array("f", [0.855, 0.804, 0.774, 0.745, 0.742, 0.726, 0.697, 0.681, 0.576])
# yerrminus = array("f", [0.0382099463490856, 0.03721558813185679, 0.031256999216175564, 0.026683328128252668, 0.025, 0.026570660511172847, 0.030675723300355937, 0.05141984052872977, 0.03676955262170047])
# yerrplus = array("f", [0.0382099463490856, 0.03721558813185679, 0.031256999216175564, 0.026683328128252668, 0.025, 0.026570660511172847, 0.030675723300355937, 0.05141984052872977, 0.03676955262170047])
# ystatminus = array("f", [0.004, 0.004, 0.004, 0.006, 0.007, 0.009, 0.01, 0.012, 0.014])
# ystatplus = array("f", [0.004, 0.004, 0.004, 0.006, 0.007, 0.009, 0.01, 0.012, 0.014])
# numpoints = 9
# p6820_d58x1y1 = ROOT.TGraphAsymmErrors(numpoints, xval, yval, xerrminus, xerrplus, yerrminus, yerrplus)
# p6820_d58x1y1.SetName("/HepData/6820/d58x1y1 PI- Kr")
# p6820_d58x1y1.SetTitle("/HepData/6820/d58x1y1 PI- Kr")
# p6820_d58x1y1.Draw("AP")

# fit = "pol4"
# g0 = ROOT.TGraph(9);
# gplus = ROOT.TGraph(9);
# gminus = ROOT.TGraph(9);
# for i in range(9):
#   x = xval[i]
#   y = yval[i]
#   yplus = yval[i]+ystatplus[i]
#   yminus = yval[i]-ystatminus[i]
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
#   print "PI- Kr", z, f0(z), fplus(z)-fminus(z)
#   new.SetPoint(i,z,f0(z))
#   new.SetPointError(i,0,(fplus(z)-fminus(z))/2.0)
# new.SetMarkerStyle(21)
# new.SetMarkerColor(2)
# new.SetLineColor(2)
# new.Draw("Psame")
# c.Print("p6820_d58x1y1.pdf")

# # PI- Rm Xe/D
# xval = array("f", [0.16, 0.25, 0.34, 0.44, 0.55, 0.64, 0.75, 0.85, 0.95])
# xerrminus = array("f", [0.06, 0.04999999999999999, 0.040000000000000036, 0.03999999999999998, 0.050000000000000044, 0.040000000000000036, 0.050000000000000044, 0.04999999999999993, 0.04999999999999993])
# xerrplus = array("f", [0.04000000000000001, 0.04999999999999999, 0.06, 0.06, 0.04999999999999993, 0.05999999999999994, 0.050000000000000044, 0.050000000000000044, 0.3500000000000001])
# yval = array("f", [0.836, 0.765, 0.726, 0.706, 0.693, 0.672, 0.634, 0.597, 0.536])
# yerrminus = array("f", [0.0383275357934736, 0.037336309405188936, 0.0304138126514911, 0.02596150997149434, 0.025632011235952594, 0.026000000000000002, 0.031384709652950434, 0.05028916384272063, 0.03801315561749643])
# yerrplus = array("f", [0.0383275357934736, 0.037336309405188936, 0.0304138126514911, 0.02596150997149434, 0.025632011235952594, 0.026000000000000002, 0.031384709652950434, 0.05028916384272063, 0.03801315561749643])
# ystatminus = array("f", [0.005, 0.005, 0.005, 0.007, 0.009, 0.01, 0.012, 0.015, 0.017])
# ystatplus = array("f", [0.005, 0.005, 0.005, 0.007, 0.009, 0.01, 0.012, 0.015, 0.017])
# numpoints = 9
# p6820_d67x1y1 = ROOT.TGraphAsymmErrors(numpoints, xval, yval, xerrminus, xerrplus, yerrminus, yerrplus)
# p6820_d67x1y1.SetName("/HepData/6820/d67x1y1 PI- Xe")
# p6820_d67x1y1.SetTitle("/HepData/6820/d67x1y1 PI- Xe")
# p6820_d67x1y1.Draw("AP")

# fit = "pol4"
# g0 = ROOT.TGraph(9);
# gplus = ROOT.TGraph(9);
# gminus = ROOT.TGraph(9);
# for i in range(9):
#   x = xval[i]
#   y = yval[i]
#   yplus = yval[i]+ystatplus[i]
#   yminus = yval[i]-ystatminus[i]
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
#   print "PI- Xe", z, f0(z), fplus(z)-fminus(z)
#   new.SetPoint(i,z,f0(z))
#   new.SetPointError(i,0,(fplus(z)-fminus(z))/2.0)
# new.SetMarkerStyle(21)
# new.SetMarkerColor(2)
# new.SetLineColor(2)
# new.Draw("Psame")
# c.Print("p6820_d67x1y1.pdf")
