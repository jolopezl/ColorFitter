import subprocess
import numpy as np
import ROOT
from matplotlib import pyplot as plt
from itertools import product
# plt.style.use('seaborn')
plt.rc('font', family='serif')  # , serif='Times')
plt.rc('text', usetex=True)
plt.rc('xtick', labelsize=10)
plt.rc('ytick', labelsize=10)
plt.rc('axes', labelsize=10)

plt.rcParams['errorbar.capsize'] = 3


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

    fig, ax = plt.subplots(1, 2, constrained_layout=True)
    width = 7.056870070568701
    height = 0.5 * width * (600./800.)
    fig.set_size_inches(width, height)

    ax[0].errorbar(xp, yp, yerr=yerrors, #capsize=0,
                marker="o", linestyle="", markerfacecolor='grey',
                color='black', zorder=5, label='Fit result')
    ax[0].errorbar(xp, yp, yerr=yerrors, xerr=xerrors, capsize=0,
                marker="o", linestyle="", markerfacecolor='grey',
                color='black')
    ax[0].plot(grint1.GetX(), grint1.GetY(), 'b-',
            label='LSM, $\chi^2/\mathrm{dof} = 1.32$\n $\kappa = 1.00\pm0.05$ (GeV/fm)')
    ax[0].plot(grint2.GetX(), grint2.GetY(), 'r-',
            label='Bialas et. al, $\chi^2/\mathrm{dof} = 0.68$\n $\kappa = 0.85\pm0.05$ (GeV/fm)')

    ax[0].annotate(r'$\langle Q^{2} \rangle = 2.4$ GeV$^{2}$, $\langle \nu \rangle = 12.4$ GeV',
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

    ax[0].fill_between(xg1, yg1_lo, yg1_up, alpha=0.4, facecolor='blue', zorder=1)

    Npoints = grint2.GetN()
    xg2 = np.ndarray(Npoints, dtype=float, buffer=grint2.GetX())
    yg2 = np.ndarray(Npoints, dtype=float, buffer=grint2.GetY())
    yeg2 = np.ndarray(Npoints, dtype=float, buffer=grint2.GetEY())
    yg2_up = np.ndarray(Npoints, dtype=float)
    yg2_lo = np.ndarray(Npoints, dtype=float)
    for i in range(Npoints):
        yg2_lo[i] = yg2[i] - yeg2[i]
        yg2_up[i] = yg2[i] + yeg2[i]

    ax[0].fill_between(xg1, yg2_lo, yg2_up, alpha=0.4, facecolor='red', zorder=0)

    ax[0].locator_params(axis='y', nbins=6)
    ax[0].set_ylim(0.1, 19.9)
    ax[0].set_xlim(0, 1)

    ax[0].set(xlabel='$z$', ylabel='$L_\mathrm{c}$ (fm)')

    # fig.tight_layout()
    ax[0].legend(frameon=False, loc='upper right', borderaxespad=0.)

    ##### QHAT
    fqhat = ROOT.TFile.Open("Qhat_results.root", "READ")
    qhat = fqhat.Get("qhat_means")
    xp = qhat.GetX()
    yp = qhat.GetY()
    yerr = qhat.GetEY()
    color_factor = 9.0/4.0

    ax[1].errorbar(xp, yp, yerr, #capsize=0,
                marker="o", linestyle="", markerfacecolor='grey',
                color='black', zorder=5,
                label='Fit result')
    average_qhat_info = r'$\langle\hat q\rangle = 0.038 \pm 0.026$ GeV$^{2}$/fm'
    ax[1].annotate(average_qhat_info,
                xy=(0.1, 0.6), xycoords='axes fraction')
    xlim_inf = 2.5
    xlim_sup = 5.5
    shift = 0
    first_point = [xlim_inf + shift, xlim_inf + shift + 0.3]
    theoretical_qhat = 0.075 / color_factor
    theoretical_qhat_lo = theoretical_qhat - 0.005 / color_factor
    theoretical_qhat_up = theoretical_qhat + 0.015 / color_factor
    ax[1].plot([xlim_inf, xlim_sup], [theoretical_qhat, theoretical_qhat],
            'b-', label=r'p+Pb, JHEP03(2013)122 ($\times 4/9$)')
    ax[1].fill_between([xlim_inf, xlim_sup],
                    [theoretical_qhat_lo, theoretical_qhat_lo],
                    [theoretical_qhat_up, theoretical_qhat_up],
                    alpha=0.4, facecolor='blue', zorder=0)
    # ax[1].plot([xlim_inf, xlim_sup], [qhatfunc(0.11), qhatfunc(0.11)],
    #         'r-', label='arXiv:1907.11808')
    ax[1].locator_params(axis='y', nbins=6)
    ax[1].locator_params(axis='x', nbins=4)
    ax[1].set_ylim(0.001, 0.12)
    ax[1].set_xlim(xlim_inf, xlim_sup)
    ax[1].set(xlabel='$A^{1/3}$', ylabel='$\hat{q}$ (GeV$^{2}$/fm)')
    ax[1].legend(frameon=False, loc='upper right', borderaxespad=0.)

    # output_file_name = "/Users/lopez/Dropbox/Paper-Color-Lifetime copy/Figures2020/Fig04_Production_Length_MPL.pdf"
    output_file_name = "Fig04x.pdf"
    fig.savefig(output_file_name)

    subprocess.call(["open", output_file_name])


if __name__ == "__main__":
    create_plot()
