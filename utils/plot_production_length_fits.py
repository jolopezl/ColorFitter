import subprocess
import numpy as np
import ROOT
from matplotlib import pyplot as plt
from itertools import product
# plt.style.use('seaborn')
# plt.rc('font', family='serif', serif='Times')
# plt.rc('text', usetex=True)
plt.rc('xtick', labelsize=12)
plt.rc('ytick', labelsize=12)
plt.rc('axes', labelsize=12)
# plt.rc('text', usetex=True)
plt.rcParams['errorbar.capsize'] = 3


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
    print "assign"
    for i in range(4):
        xerrors[0, i] = 0
        xerrors[1, i] = xerrors_high[i]
    yerrors = np.ndarray(4, dtype=float, buffer=model.GetEYhigh())

    fig, ax = plt.subplots(figsize=(5, 3.75))
    # plt.errorbar(x, y, yerr=None, xerr=None, fmt='', ecolor=None,
    #              elinewidth=None, capsize=None, barsabove=False, lolims=False,
    #              uplims=False, xlolims=False, xuplims=False, errorevery=1,
    #              capthick=None, *, data=None, **kwargs)
    ax.errorbar(xp, yp, yerr=yerrors, xerr=xerrors, capsize=0,
                marker="o", linestyle="", color='black', zorder=5, label='Fit result')
    ax.plot(grint1.GetX(), grint1.GetY(), 'b-',
            label='Lund String Model\n $\chi^2/\mathrm{dof} = 1.1$, $\kappa = 1.04\pm0.06$ (GeV/fm)')
    ax.plot(grint2.GetX(), grint2.GetY(), 'r-',
            label='Bialas et. al.\n $\chi^2/\mathrm{dof} = 0.35$, $\kappa = 0.86\pm0.05$ (GeV/fm)')

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

    fig.tight_layout()
    ax.legend(title=r'$\langle Q^{2} \rangle = 2.4$ GeV$^{2}$, $\langle \nu \rangle = 12.4$ GeV',
              frameon=False)

    output_file_name = "production_length_fits.pdf"
    fig.savefig(output_file_name)

    subprocess.call(["open", output_file_name])


if __name__ == "__main__":
    create_plot()
