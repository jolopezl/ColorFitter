import subprocess
import numpy as np
import ROOT
import matplotlib
from matplotlib import pyplot as plt
from itertools import product

plt.rc('text', usetex=True)
plt.rc('xtick', labelsize=10)
plt.rc('ytick', labelsize=10)
plt.rc('axes', labelsize=10)
plt.rcParams['errorbar.capsize'] = 3

# matplotlib.rcParams.update({'font.size': 8})
matplotlib.rcParams['mathtext.fontset'] = 'cm'
matplotlib.rcParams['font.family'] = 'cm'
matplotlib.pyplot.title(r'ABC123 vs $\mathrm{ABC123}^{123}$')

plt.rcParams['errorbar.capsize'] = 3

from plot_kperp import calculate_mean, z_value

def qhatfunc(x):
    """
    Qhat as prescribed in 
    https://arxiv.org/abs/1907.11808v1
    """
    alpha_s = 0.3
    qhat  = 0.02 * alpha_s * x**(-0.17) * (1-x)**(-2.79) * np.log(2.4)**(0.25)
    return qhat

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

    fig, ax = plt.subplots(2, 2, constrained_layout=True)
    width = 7.056870070568701 * 0.8
    height = width * 0.75
    fig.set_size_inches(width, height)

    ax[0][0].errorbar(xp, yp, yerr=yerrors, #capsize=0,
                marker="o", linestyle="", markerfacecolor='grey',
                color='black', zorder=5, label='Fit result')
    ax[0][0].errorbar(xp, yp, yerr=yerrors, xerr=xerrors, capsize=0,
                marker="o", linestyle="", markerfacecolor='grey',
                color='black')
    ax[0][0].plot(grint1.GetX(), grint1.GetY(), 'b-',
            label='LSM, $\chi^2/\mathrm{dof} = 1.32$\n $\kappa = 1.00\pm0.05$ (GeV/fm)')
    ax[0][0].plot(grint2.GetX(), grint2.GetY(), 'r-',
            label='Bialas et. al, $\chi^2/\mathrm{dof} = 0.68$\n $\kappa = 0.85\pm0.05$ (GeV/fm)')

    # ax[0][0].annotate(r'$\langle Q^{2} \rangle = 2.4$ GeV$^{2}$, $\langle \nu \rangle = 12.4$ GeV', xy=(0.02, 0.03), xycoords='axes fraction')

    Npoints = grint1.GetN()
    xg1 = np.ndarray(Npoints, dtype=float, buffer=grint1.GetX())
    yg1 = np.ndarray(Npoints, dtype=float, buffer=grint1.GetY())
    yeg1 = np.ndarray(Npoints, dtype=float, buffer=grint1.GetEY())
    yg1_up = np.ndarray(Npoints, dtype=float)
    yg1_lo = np.ndarray(Npoints, dtype=float)
    for i in range(Npoints):
        yg1_lo[i] = yg1[i] - yeg1[i]
        yg1_up[i] = yg1[i] + yeg1[i]

    ax[0][0].fill_between(xg1, yg1_lo, yg1_up, alpha=0.4, facecolor='blue', zorder=1)

    Npoints = grint2.GetN()
    xg2 = np.ndarray(Npoints, dtype=float, buffer=grint2.GetX())
    yg2 = np.ndarray(Npoints, dtype=float, buffer=grint2.GetY())
    yeg2 = np.ndarray(Npoints, dtype=float, buffer=grint2.GetEY())
    yg2_up = np.ndarray(Npoints, dtype=float)
    yg2_lo = np.ndarray(Npoints, dtype=float)
    for i in range(Npoints):
        yg2_lo[i] = yg2[i] - yeg2[i]
        yg2_up[i] = yg2[i] + yeg2[i]

    ax[0][0].fill_between(xg1, yg2_lo, yg2_up, alpha=0.4, facecolor='red', zorder=0)

    ax[0][0].locator_params(axis='y', nbins=6)
    ax[0][0].set_ylim(0.1, 24.9)
    ax[0][0].set_xlim(0, 1)

    ax[0][0].set(xlabel='$z$', ylabel='$L_\mathrm{c}$ (fm)')

    # fig.tight_layout()
    handles, labels = ax[0][0].get_legend_handles_labels()
    # sort both labels and handles by labels
    # labels, handles = zip(*sorted(zip(labels, handles), key=lambda t: t[0]))
    # ax[0][0].legend([handles[1],handles[2],handles[0]],
    #              [labels[1],labels[2],labels[0]],
    #              frameon=False, loc='upper right', borderaxespad=0., fontsize=8)
    ax[0][0].legend(frameon=False, loc='upper right', borderaxespad=0., fontsize=8)
    

    ##### QHAT
    fqhat = ROOT.TFile.Open("Qhat_results.root", "READ")
    qhat = fqhat.Get("qhat_means")
    xp = qhat.GetX()
    yp = qhat.GetY()
    yerr = qhat.GetEY()
    color_factor = 9.0/4.0

    ax[0][1].errorbar(xp, yp, yerr, #capsize=0,
                marker="o", linestyle="", markerfacecolor='grey',
                color='black', zorder=5,
                label='Fit result')
    # average_qhat_info = r'$\langle\hat q\rangle = 0.038 \pm 0.026$ GeV$^{2}$/fm'
    # ax[0][1].annotate(average_qhat_info, xy=(0.1, 0.6), xycoords='axes fraction')
    xlim_inf = 2.5
    xlim_sup = 5.5

    x_lo = 1
    x_up = 6
    mean, meanError = calculate_mean(yp, yerr)
    pb = ax[0][1].plot([x_lo, x_up], [mean, mean],
            'k--', label=r'average $= %.3f \pm %.3f$ GeV$^{2}$' % (mean, meanError))
    pc = ax[0][1].fill_between([x_lo, x_up],
                    [mean - meanError, mean - meanError],
                    [mean + meanError, mean + meanError],
                    alpha=0.4, facecolor='g', hatch='/', zorder=0)
    # ax[0][1].plot([xlim_inf, xlim_sup], [qhatfunc(0.11), qhatfunc(0.11)],
    #         'r-', label='arXiv:1907.11808')
    ax[0][1].locator_params(axis='y', nbins=6)
    ax[0][1].locator_params(axis='x', nbins=4)
    ax[0][1].set_ylim(0.001, 0.12)
    ax[0][1].set_xlim(xlim_inf, xlim_sup)
    ax[0][1].set(xlabel='$A^{1/3}$', ylabel='$\hat{q}$ (GeV$^{2}$/fm)')
    ax[0][1].legend(frameon=False, loc='upper right', borderaxespad=0., fontsize=8)

    ### K_PERP
    ff = ROOT.TFile.Open("OutputROOT.20200707.BL30_piplus.root", "READ")
    kperp = ff.Get("tg_c1")
    xp = kperp.GetX()
    yp = kperp.GetY()
    yerr = kperp.GetEY()
    for idx in range(4):
        yp[idx] = yp[idx] * z_value[idx]**2
        yerr[idx] = yerr[idx] * z_value[idx]**2
    pa = ax[1][0].errorbar(xp, yp, yerr,  # capsize=0,
                marker="o", linestyle="", markerfacecolor='grey',
                color='black', zorder=5,
                label='Fit parameter')
    x_lo = 0.28
    x_up = 0.98
    mean, meanError = calculate_mean(yp, yerr)
    pb = ax[1][0].plot([x_lo, x_up], [mean, mean],
            'k--', label=r'average $= %.3f \pm %.3f$ GeV$^{2}$' % (mean, meanError))
    pc = ax[1][0].fill_between([x_lo, x_up],
                    [mean - meanError, mean - meanError],
                    [mean + meanError, mean + meanError],
                    alpha=0.4, facecolor='g', hatch='/', zorder=0)
    ax[1][0].axhline(lw=1,ls='-',c='k')
    # ax[1][0].locator_params(axis='x', nbins=4)
    ax[1][0].locator_params(axis='y', nbins=6)
    ax[1][0].set_ylim(-0.0069, 0.0039)
    ax[1][0].set_xlim(0, 1)
    ax[1][0].set(xlabel='$z$', ylabel=r'$z^2\Delta\langle k_\perp^2 \rangle$ (GeV$^{2}$)')
    ax[1][0].legend(frameon=False, loc='upper right', borderaxespad=0., fontsize=8)

    ax[-1, -1].axis('off')
    # output_file_name = "/Users/lopez/Dropbox/Paper-Color-Lifetime copy/Figures2020/Fig04_Production_Length_MPL.pdf"
    output_file_name = "Fig04x.pdf"
    fig.savefig(output_file_name)

    subprocess.call(["open", output_file_name])


if __name__ == "__main__":
    create_plot()
