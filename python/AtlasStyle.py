from ROOT import gROOT, TStyle

def SetAtlasStyle ():
  print "\nApplying ATLAS style settings..."
  atlasStyle = AtlasStyle()
  gROOT.SetStyle("ATLAS")
  gROOT.ForceStyle()

def AtlasStyle():
  atlasStyle = TStyle("ATLAS","Atlas style")
  # use plain black on white colors
  icol=0 # WHITE
  atlasStyle.SetFrameBorderMode(icol)
  atlasStyle.SetFrameFillColor(icol)
  atlasStyle.SetCanvasBorderMode(icol)
  atlasStyle.SetCanvasColor(icol)
  atlasStyle.SetPadBorderMode(icol)
  atlasStyle.SetPadColor(icol)
  atlasStyle.SetStatColor(icol)
  #atlasStyle.SetFillColor(icol) # don't use: white fill color for *all* objects
  # set the paper & margin sizes
  # atlasStyle.SetPaperSize(20,26)

  # set margin sizes
  atlasStyle.SetPadTopMargin(0.05)
  atlasStyle.SetPadRightMargin(0.05)
  atlasStyle.SetPadBottomMargin(0.16)
  atlasStyle.SetPadLeftMargin(0.16)

  # set title offsets (for axis label)
  atlasStyle.SetTitleXOffset(1.0)
  atlasStyle.SetTitleYOffset(1.0)

  # use large fonts
  #Int_t font=72 # Helvetica italics
  font=43 # Helvetica
  tsize=28 #0.05
  atlasStyle.SetTextFont(font)

  atlasStyle.SetTextSize(tsize)
  atlasStyle.SetLabelFont(font,"x")
  atlasStyle.SetTitleFont(font,"x")
  atlasStyle.SetLabelFont(font,"y")
  atlasStyle.SetTitleFont(font,"y")
  atlasStyle.SetLabelFont(font,"z")
  atlasStyle.SetTitleFont(font,"z")
  
  atlasStyle.SetLabelSize(tsize,"x")
  atlasStyle.SetTitleSize(tsize,"x")
  atlasStyle.SetLabelSize(tsize,"y")
  atlasStyle.SetTitleSize(tsize,"y")
  atlasStyle.SetLabelSize(tsize,"z")
  atlasStyle.SetTitleSize(tsize,"z")

  # use bold lines and markers
  atlasStyle.SetMarkerStyle(20)
  # atlasStyle.SetMarkerSize(1.2)
  atlasStyle.SetMarkerSize(2)
  atlasStyle.SetHistLineWidth(2)
  atlasStyle.SetLineStyleString(2,"[12 12]") # postscript dashes

  # get rid of X error bars 
  #atlasStyle.SetErrorX(0.001)
  # get rid of error bar caps
  atlasStyle.SetEndErrorSize(0.)
  # atlasStyle.SetEndErrorSize(7.5)

  # do not display any of the standard histogram decorations
  atlasStyle.SetOptTitle(0)
  #atlasStyle.SetOptStat(1111)
  atlasStyle.SetOptStat(0)
  #atlasStyle.SetOptFit(1111)
  atlasStyle.SetOptFit(0)

  # put tick marks on top and RHS of plots
  atlasStyle.SetPadTickX(1)
  atlasStyle.SetPadTickY(1)
  return atlasStyle

from ROOT import TLatex, gPad

def ATLASLabel(x,y,text="Internal",color=1):
  l=TLatex()
  # l.SetTextAlign(12);
  # l.SetTextSize(tsize); 
  l.SetNDC()
  l.SetTextFont(72)
  l.SetTextColor(color)
  delx = 0.115*696*gPad.GetWh()/(472*gPad.GetWw())
  l.DrawLatex(x,y,"ATLAS");
  if (text):
    p=TLatex()
    p.SetNDC()
    p.SetTextFont(42)
    p.SetTextColor(color)
    p.DrawLatex(x+delx,y,text)
    #    p.DrawLatex(x,y,"#sqrt{s}=900GeV");

def AddLabel(x,y,text="Text here",color=1):
  if (text):
    p=TLatex()
    p.SetNDC()
    p.SetTextFont(43)
    p.SetTextSize(28)
    p.SetTextColor(color)
    p.DrawLatex(x,y,text)
    #    p.DrawLatex(x,y,"#sqrt{s}=900GeV");  
