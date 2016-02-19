from array import array
from numpy import loadtxt

from ROOT import *

# path = '2p-fixed-crosssection=25mbarn/'
path = '3p-no-energy/'
file = 'testFit.txt'
fitfile = path+file
zbin = 3
########################################################
########################################################
#### data points pT2 is corrected here ####
zcentr           = array("f",[0.32,0.53,0.75,0.94])
pt2_neon         = array("f",[0.0069,0.0063,-0.0015,-0.0037])
pt2_err_neon     = array("f",[0.002747726333,0.005152669211,0.01350888596,0.02077666961])
pt2_kripton      = array("f",[0.021,0.0224,0.0085,0.0115])
pt2_err_kripton  = array("f",[0.002946183973,0.005444263036,0.01360477857,0.02106038936])
pt2_xenon        = array("f",[0.0274,0.0296,0.0144,0.0073])
pt2_err_xenon    = array("f",[0.003243454948,0.005979130372,0.01442289846,0.02177360788])
#### data points multiplicity ratios ####
rm_neon          = array("f",[0.893189114368,0.885454096825,0.880935853275,0.798520384419])
rm_kripton       = array("f",[0.78747612087,0.744660997913,0.679028679486,0.551673817154])
rm_xenon         = array("f",[0.736762500635,0.684223383665,0.619689942725,0.498076090992])
rm_err_neon      = array("f",[0.0594409344724,0.0515307622582,0.0634878265064,0.0682394907588])
rm_err_kripton   = array("f",[0.0542930099596,0.0447182315218,0.05222907333,0.0527700155986])
rm_err_xenon     = array("f",[0.0535218789044,0.0411665583174,0.0503850083386,0.0529182285411])
########################################################
########################################################
fitpars = loadtxt(fitfile,skiprows=1)
zval       = "%.2f" % zcentr[zbin]
qhat       = "%.2f" % fitpars[zbin, 1]
lp         = "%.2f" % fitpars[zbin, 2]
sigma      = "%.2f" % fitpars[zbin, 3]
dlog       = "%.2f" % fitpars[zbin, 4]
dz         = "%.2f" % fitpars[zbin, 5]
cascade    = "%.2f" % fitpars[zbin, 6]
qhat_err   = "%.2f" % fitpars[zbin, 7]
lp_err     = "%.2f" % fitpars[zbin, 8]
sigma_err  = "%.2f" % fitpars[zbin, 9]
dlog_err   = "%.2f" % fitpars[zbin, 10]
dz_err     = "%.2f" % fitpars[zbin, 11]
cascade_err= "%.2f" % fitpars[zbin, 12]
########################################################
########################################################
def getDataPoints(zin):
  i = zbin
  xval = array("f",[1.1*20.1797**(1./3.),1.1*83.7980**(1./3.),1.1*131.293**(1./3.)])
  yval = array("f",[pt2_neon[i],pt2_kripton[i],pt2_xenon[i]])
  xerr = array("f",[0,0,0])
  yerr = array("f",[pt2_err_neon[i],pt2_err_kripton[i],pt2_err_xenon[i]])
  gg_pt = TGraphErrors(3,xval,yval,xerr,yerr)
  yval2 = array("f",[rm_neon[i],rm_kripton[i],rm_xenon[i]])
  yerr2 = array("f",[rm_err_neon[i],rm_err_kripton[i],rm_err_xenon[i]])
  gg_rm = TGraphErrors(3,xval,yval2,xerr,yerr2)
  gg_pt.SetMarkerStyle(20)
  gg_pt.SetMarkerSize(2)
  gg_pt.SetLineWidth(2)
  gg_rm.SetMarkerStyle(20)
  gg_rm.SetMarkerSize(2)
  gg_rm.SetLineWidth(2)
  xlabel = "A^{1/3}"
  ylabel = "#Delta #LT p_{t}^{2} #GT [GeV^{2}]"
  gg_pt.GetXaxis().SetTitle(xlabel)
  gg_pt.GetYaxis().SetTitle(ylabel)
  gg_pt.GetYaxis().SetTitleOffset(1.5)
  ylabel = "R_{m}"
  gg_rm.GetXaxis().SetTitle(xlabel)
  gg_rm.GetYaxis().SetTitle(ylabel)
  gg_rm.GetYaxis().SetTitleOffset(1.5)
  fontAxesSize = 28
  fontAxesCode = 43
  gg_rm.GetXaxis().SetTitleFont(fontAxesCode)
  gg_rm.GetXaxis().SetTitleSize(fontAxesSize)
  gg_rm.GetXaxis().SetLabelFont(fontAxesCode)
  gg_rm.GetXaxis().SetLabelSize(fontAxesSize)
  gg_rm.GetYaxis().SetTitleFont(fontAxesCode)
  gg_rm.GetYaxis().SetTitleSize(fontAxesSize)
  gg_rm.GetYaxis().SetLabelFont(fontAxesCode)
  gg_rm.GetYaxis().SetLabelSize(fontAxesSize)
  gg_pt.GetXaxis().SetTitleFont(fontAxesCode)
  gg_pt.GetXaxis().SetTitleSize(fontAxesSize)
  gg_pt.GetXaxis().SetLabelFont(fontAxesCode)
  gg_pt.GetXaxis().SetLabelSize(fontAxesSize)
  gg_pt.GetYaxis().SetTitleFont(fontAxesCode)
  gg_pt.GetYaxis().SetTitleSize(fontAxesSize)
  gg_pt.GetYaxis().SetLabelFont(fontAxesCode)
  gg_pt.GetYaxis().SetLabelSize(fontAxesSize)
  ylo = -0.028
  yhi = 0.036
  gg_pt.GetYaxis().SetRangeUser(ylo,yhi)
  ylo = 0.4
  yhi = 0.94
  gg_rm.GetYaxis().SetRangeUser(ylo,yhi)
  gg_rm.GetYaxis().SetTitleOffset(1.75)
  gg_pt.GetYaxis().SetTitleOffset(1.75)
  return gg_pt,gg_rm
########################################################
########################################################
def getModelPlots(zin):
  model_pt_file = path+"testFit_plot_pt_0_"+str(zbin)+".txt"
  model_rm_file = path+"testFit_plot_mr_0_"+str(zbin)+".txt"
  model_pt = TGraph(model_pt_file)
  model_rm = TGraph(model_rm_file)
  model_pt.SetLineWidth(2)
  model_rm.SetLineWidth(2)
  return model_pt,model_rm
########################################################
########################################################
gStyle.SetPadRightMargin(0.05)
gStyle.SetPadLeftMargin(0.125)
gStyle.SetPadBottomMargin(0.16)
gStyle.SetOptStat(0)
gStyle.SetOptTitle(0)
gStyle.SetEndErrorSize(7.5)

c1 = TCanvas("paddy","paddy",800,1600)#,700,700)
c1.Divide(1,2)
# zbin = 0
# updateParameters(zbin)
gg_pt,gg_rm=getDataPoints(zbin)
model_pt,model_rm=getModelPlots(zbin)  
c1.cd(1)
gPad.SetBottomMargin(0.001)
gPad.SetTopMargin(0.01)
gPad.SetRightMargin(0.01)
gg_pt.Draw("AP")
model_pt.Draw("SAME")
##
c1.cd(2)
gPad.SetTopMargin(0.001)
gPad.SetRightMargin(0.01)
gg_rm.Draw("AP")
model_rm.Draw("SAME")

c1.cd(1)
# text
text1 = TLatex()
text1.SetNDC()
text1.SetTextFont(83)
text1.SetTextSize(28-4)
text1.DrawLatex(0.16,0.82,
"#splitline{#splitline{z = "+zval+"}{q_{0} = "+str(qhat)+" #pm "+str(qhat_err)+"}}{#splitline{l_{p} = "+str(lp)+" #pm "+str(lp_err)+"}{#sigma_{ph} = "+str(sigma)+" #pm "+str(sigma_err)+"}}")

c1.Print("test_result.pdf")

