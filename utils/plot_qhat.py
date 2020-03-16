import subprocess
import numpy as np
import ROOT
from matplotlib import pyplot as plt
from itertools import product
# plt.style.use('seaborn')
plt.rc('font', family='serif')#, serif='Times')
plt.rc('text', usetex=True)
plt.rc('xtick', labelsize=10)
plt.rc('ytick', labelsize=10)
plt.rc('axes', labelsize=10)
# plt.rc('text', usetex=True)
plt.rcParams['errorbar.capsize'] = 3


def create_plot():
    print("Production length fit results")
    f = ROOT.TFile.Open("Qhat_results.root", "READ")

    qhat = f.Get("qhat_means")

    xp = qhat.GetX()
    yp = qhat.GetY()
    yerr = qhat.GetEY()

    fig, ax = plt.subplots(constrained_layout=True)
    width = 3.4039020340390205
    height = width * 0.75
    fig.set_size_inches(width, height)

    ax.errorbar(xp, yp, yerr, capsize=0,
                marker="o", linestyle="", color='black', zorder=5, 
                label='Fit result')

    average_qhat_info = r'$\langle\hat q\rangle = 0.038 \pm 0.026$ GeV$^{2}$/fm'
    ax.annotate(average_qhat_info,
                xy=(0.3, 0.65), xycoords='axes fraction')

    xlim_inf = 2.001
    xlim_sup = 5.4
    shift = 0
    first_point = [xlim_inf + shift, xlim_inf + shift + 0.3]

    theoretical_qhat = 0.075
    theoretical_qhat_lo = theoretical_qhat - 0.005
    theoretical_qhat_up = theoretical_qhat + 0.015
    ax.plot(first_point, [theoretical_qhat, theoretical_qhat],
            'b-', lw=3, label='p+Pb, JHEP03(2013)122')
    ax.fill_between(first_point,
                    [theoretical_qhat_lo, theoretical_qhat_lo],
                    [theoretical_qhat_up, theoretical_qhat_up],
                    alpha=0.4, facecolor='blue', zorder=0)

    ax.plot(first_point, [0.015,0.015],
            'r-', lw=3, label='arXiv:1907.11808')

    ax.plot([xlim_inf, xlim_sup], [theoretical_qhat, theoretical_qhat],
            'b--', lw=1)
    ax.plot([xlim_inf, xlim_sup], [0.015,0.015],
            'r--', lw=1)

    ax.locator_params(axis='y', nbins=6)
    ax.set_ylim(0.001, 0.12)
    ax.set_xlim(xlim_inf, xlim_sup)

    ax.set(xlabel='$A^{1/3}$', ylabel='$\hat{q}$ (GeV$^{2}$/fm)')

#     fig.tight_layout()
    ax.legend(frameon=False,loc='upper right', borderaxespad=0.)

    output_file_name = "/Users/lopez/Dropbox/Paper-Color-Lifetime copy/Figures2020/Fig05_Qhat_MPL.pdf"
    fig.savefig(output_file_name)

    subprocess.call(["open", output_file_name])


if __name__ == "__main__":
    create_plot()
