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
    print("Prehadron cross section fit results")
    f = ROOT.TFile.Open("OutputROOT.20200310.BL.root", "READ")

    qhat = f.Get("tg_sigma")

    xp = qhat.GetX()
    yp = qhat.GetY()
    yerr = qhat.GetEY()

    fig, ax = plt.subplots(figsize=(5, 3.75))
    ax.errorbar(xp, yp, yerr, capsize=0,
                marker="o", linestyle="", color='black', zorder=5, 
                label='Fit result,\n Average for $z_\mathrm{h}>0.5$\n $\sigma = 22.1 \pm 29.1$ mbarn')
    pdg = [27.0363,25.4381,25.098,24.9184]
    ax.plot(xp, pdg, 'r-', lw=3, label='M. Tanabashi et al. (PDG)\n PRD 98, 030001 (2018)')
    ax.locator_params(axis='y', nbins=6)
#     ax.set_ylim(0.001, 0.12)
#     ax.set_xlim(xlim_inf, xlim_sup)

    ax.set(xlabel='$z_\mathrm{h}$', ylabel='$\sigma$ (mbarn)')

    ax.set_xlim(0, 1)
    ax.set_ylim(0, 79)

    fig.tight_layout()
    ax.legend(frameon=False)

    output_file_name = "sigma.pdf"
    fig.savefig(output_file_name)

    subprocess.call(["open", output_file_name])


if __name__ == "__main__":
    create_plot()
