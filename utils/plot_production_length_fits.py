import subprocess
import numpy as np
import ROOT
from itertools import product
import matplotlib
from matplotlib import pyplot as plt
# # plt.style.use('seaborn')
# plt.rc('font', family='serif', serif='Times')
plt.rc('text', usetex=True)
plt.rc('xtick', labelsize=10)
plt.rc('ytick', labelsize=10)
plt.rc('axes', labelsize=10)
plt.rcParams['errorbar.capsize'] = 3

# matplotlib.rcParams.update({'font.size': 8})
matplotlib.rcParams['mathtext.fontset'] = 'cm'
matplotlib.rcParams['font.family'] = 'cm'
matplotlib.pyplot.title(r'ABC123 vs $\mathrm{ABC123}^{123}$')


def create_plot():
    print("Production length fit results")
    f = ROOT.TFile.Open("FitOutput_production_length.root", "READ")

    model = f.Get("model")
    grint1 = f.Get("grint1")
    grint2 = f.Get("grint2")

    xp = model.GetX()
    yp = model.GetY()

    xerrors_high = np.ndarray(4, dtype=float, buffer=model.GetEXhigh())
    xerrors_low = np.ndarray(4, dtype=float, buffer=model.GetEXlow())
    xerrors = np.ndarray((2, 4), dtype=float)

    for i in range(4):
        xerrors[0, i] = 0
        xerrors[1, i] = xerrors_high[i]
    yerrors = np.ndarray(4, dtype=float, buffer=model.GetEYhigh())

    fig, ax = plt.subplots(constrained_layout=True)
    width = 3.4039020340390205
    height = width * 0.75
    fig.set_size_inches(width, height)
    
    # plt.errorbar(x, y, yerr=None, xerr=None, fmt='', ecolor=None,
    #              elinewidth=None, capsize=None, barsabove=False, lolims=False,
    #              uplims=False, xlolims=False, xuplims=False, errorevery=1,
    #              capthick=None, *, data=None, **kwargs)
    ax.errorbar(xp, yp, yerr=yerrors, #capsize=0,
                marker="o", linestyle="", markerfacecolor='grey',
                color='black', zorder=5, label='Fit result')
    ax.errorbar(xp, yp, yerr=yerrors, xerr=xerrors, capsize=0,
                marker="o", linestyle="", markerfacecolor='grey',
                color='black')
    ax.plot(grint1.GetX(), grint1.GetY(), 'b-',
            label='LSM, $\chi^2/\mathrm{dof} = 1.32$\n $\kappa = 1.00\pm0.05$ (GeV/fm)')
    ax.plot(grint2.GetX(), grint2.GetY(), 'r-',
            label='Bialas et al., $\chi^2/\mathrm{dof} = 0.68$\n $\kappa = 0.85\pm0.05$ (GeV/fm)')

    ax.annotate(r'$\langle Q^{2} \rangle = 2.4$ GeV$^{2}$, $\langle \nu \rangle = 12.4$ GeV',
                xy=(0.02, 0.03), xycoords='axes fraction')

    Npoints = grint1.GetN()
    xg1 = np.ndarray(Npoints, dtype=float, buffer=grint1.GetX())
    yg1 = np.ndarray(Npoints, dtype=float, buffer=grint1.GetY())
    yeg1 = np.ndarray(Npoints, dtype=float, buffer=grint1.GetEY())
    yg1_up = np.ndarray(Npoints, dtype=float)
    yg1_lo = np.ndarray(Npoints, dtype=float)
    for i in range(Npoints):
        yg1_lo[i] = yg1[i] - yeg1[i]
        yg1_up[i] = yg1[i] + yeg1[i]

    ax.fill_between(xg1, yg1_lo, yg1_up, alpha=0.4, facecolor='blue', zorder=1)

    Npoints = grint2.GetN()
    xg2 = np.ndarray(Npoints, dtype=float, buffer=grint2.GetX())
    yg2 = np.ndarray(Npoints, dtype=float, buffer=grint2.GetY())
    yeg2 = np.ndarray(Npoints, dtype=float, buffer=grint2.GetEY())
    yg2_up = np.ndarray(Npoints, dtype=float)
    yg2_lo = np.ndarray(Npoints, dtype=float)
    for i in range(Npoints):
        yg2_lo[i] = yg2[i] - yeg2[i]
        yg2_up[i] = yg2[i] + yeg2[i]

    ax.fill_between(xg1, yg2_lo, yg2_up, alpha=0.4, facecolor='red', zorder=0)

    ax.locator_params(axis='y', nbins=6)
    ax.set_ylim(0.1, 19.9)
    ax.set_xlim(0, 1)

    ax.set(xlabel='$z$', ylabel='$L_\mathrm{c}$ (fm)')

    # fig.tight_layout()
    ax.legend(frameon=False,loc='upper right', borderaxespad=0.)

    # output_file_name = "/Users/lopez/Dropbox/Paper-Color-Lifetime copy/Figures2020/Fig04_Production_Length_MPL.pdf"
    output_file_name = "Fig04_Production_Length_MPL_fixed.pdf"
    fig.savefig(output_file_name)

    subprocess.call(["open", output_file_name])


if __name__ == "__main__":
    create_plot()
