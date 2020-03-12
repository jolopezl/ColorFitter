import ROOT
from matplotlib import pyplot as plt
# plt.rc('font', family='serif', serif='Times')
# plt.rc('text', usetex=True)
# plt.rc('xtick', labelsize=12)
# plt.rc('ytick', labelsize=12)
# plt.rc('axes', labelsize=12)
# plt.rc('text', usetex=True)

from scipy.stats import expon
import numpy as np

import itertools


def main():
    fe = ROOT.TFile.Open("DemoPlots.Sig.root", "READ")

    fig, axs = plt.subplots(
        1, 2, sharex='col', constrained_layout=True, figsize=(4.5, 4.5/2))

    sigmas = [30, 27, 24, 21, 19]
    style = itertools.cycle(["-", "--", "-.", ":", ".", "h", "H"])
    x = np.linspace(0.05, 12.9, 100)
    for sig in sigmas:
        current_style = style.next()
        # pT-broadening
        graph_name = "pT2_lp_"+str(sig)
        axs[0].plot(fe.Get(graph_name).GetX(), fe.Get(graph_name).GetY(),
                    current_style, label='$\sigma = '+str(sig)+'$ (mbar)')
        # Multiplicity ratio
        graph_name = "RM_lp_"+str(sig)
        axs[1].plot(fe.Get(graph_name).GetX(), fe.Get(graph_name).GetY(),
                    current_style, label='$\sigma = '+str(sig)+'$ (mbar)')

    axs[0].set(
        xlabel='$A^{1/3}$', ylabel=r'$\Delta \langle p_\mathrm{T}^2\rangle$ (GeV$^2$)')
    axs[1].set(xlabel='$A^{1/3}$', ylabel='$R_\mathrm{M}$')

    # axs[0,0].set_ylim(0,1)
    # axs[1,0].set_ylim(0,1)
    # axs[0,1].set_ylim(0.001,0.023)
    # axs[1,1].set_ylim(0.001,0.023)
    # axs[0,2].set_ylim(0.1,1.1)
    # axs[1,2].set_ylim(0.1,1.1)

    axs[0].legend(title="For $L_{c}$ = 10 (fm)")
    # fig.tight_layout()
    plt.savefig("demo.pdf")


if __name__ == '__main__':
    main()
