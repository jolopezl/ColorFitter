import subprocess
import numpy as np
import ROOT
import matplotlib
from matplotlib import pyplot as plt
# # plt.style.use('seaborn')
# plt.rc('font', family='serif', serif='Times')
plt.rc('text', usetex=True)
plt.rc('xtick', labelsize=10)
plt.rc('ytick', labelsize=10)
plt.rc('axes', labelsize=10)
plt.rcParams['errorbar.capsize'] = 3

matplotlib.rcParams['mathtext.fontset'] = 'cm'
matplotlib.rcParams['font.family'] = 'cm'
matplotlib.pyplot.title(r'ABC123 vs $\mathrm{ABC123}^{123}$')


def create_plot():
    print("Prehadron cross section fit results")
    f = ROOT.TFile.Open("OutputROOT.20200718.BL_SIG_piplus.root", "READ")

    qhat = f.Get("tg_sigma")

    xp = qhat.GetX()
    yp = qhat.GetY()
    yerr = qhat.GetEY()

    fig, ax = plt.subplots(constrained_layout=True)
    width = 3.4039020340390205
    height = width * 0.75
    fig.set_size_inches(width, height)

    ax.errorbar(xp, yp, yerr,
                marker="o", linestyle="", markerfacecolor='grey',
                color='black', zorder=5, label='Fit result')
    pdg = [27.075, 25.604, 25.109, 24.946]
    ax.plot(xp, pdg, 'r-', lw=2, label='M. Tanabashi et al. (PDG)\n PRD 98, 030001 (2018)')
    ax.locator_params(axis='y', nbins=6)
#     ax.set_ylim(0.001, 0.12)
#     ax.set_xlim(xlim_inf, xlim_sup)

    ax.set(xlabel='$z_\mathrm{h}$', ylabel='$\sigma$ (mbarn)')

    ax.set_xlim(0, 1)
    ax.set_ylim(0, 159)

    fig.tight_layout()
    ax.legend(frameon=False, loc='upper right', borderaxespad=0.,fontsize=8)

    output_file_name = "sigma.pdf"
    fig.savefig(output_file_name)

    subprocess.call(["open", output_file_name])


if __name__ == "__main__":
    create_plot()
