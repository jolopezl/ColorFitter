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

color_factor = 9.0/4.0

def calculate_mean(values, errors):
    mean = 0
    error = 0
    sumw = 0
    for idx in range(len(values)):
        mean += values[idx] / errors[idx]
        error += errors[idx]**2
        sumw += 1 / errors[idx]
    mean = mean/sumw
    error = np.sqrt(error) / 4
    return mean, error

def qhatfunc(x, Q2 = 2.4):
    """
    Qhat as prescribed in 
    https://arxiv.org/abs/1907.11808v1
    """
    alpha_s = 0.3
    q0 = 0.015
    qhat = q0 * alpha_s * x**(-0.17) * (1-x)**(-2.79) * np.log(Q2)**(0.25)
    return qhat


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

    ax.errorbar(xp, yp, yerr,  # capsize=0,
                marker="o", linestyle="", markerfacecolor='grey',
                color='black', zorder=5,
                label='Fit result')

    # average_qhat_info = r'$\langle\hat q\rangle = 0.038 \pm 0.026$ GeV$^{2}$/fm'
    # ax.annotate(average_qhat_info,
    #             xy=(0.1, 0.6), xycoords='axes fraction')

    xlim_inf = 1.0
    xlim_sup = 5.5
    shift = 0
    first_point = [xlim_inf + shift, xlim_inf + shift + 0.3]

    # theoretical_qhat = 0.075 / color_factor
    # theoretical_qhat_lo = theoretical_qhat - 0.005 / color_factor
    # theoretical_qhat_up = theoretical_qhat + 0.015 / color_factor
    # ax.plot([xlim_inf, xlim_sup], [theoretical_qhat, theoretical_qhat],
    #         'b-', label=r'p+Pb, JHEP03(2013)122 ($\times 4/9$)')
    # ax.fill_between([xlim_inf, xlim_sup],
    #                 [theoretical_qhat_lo, theoretical_qhat_lo],
    #                 [theoretical_qhat_up, theoretical_qhat_up],
    #                 alpha=0.4, facecolor='blue', zorder=0)
    x_lo = 1
    x_up = 6
    mean, meanError = calculate_mean(yp, yerr)
    pb = ax.plot([x_lo, x_up], [mean, mean],
            'k--', label=r'average $= %.3f \pm %.3f$ GeV$^{2}$/fm' % (mean, meanError))
    pc = ax.fill_between([x_lo, x_up],
                    [mean - meanError, mean - meanError],
                    [mean + meanError, mean + meanError],
                    alpha=0.4, facecolor='g', hatch='/', zorder=0)

    # ax.plot([xlim_inf, xlim_sup], [0.015, 0.015],
    #         'r-', label='arXiv:1907.11808')
    # print("The value of q-hat(0.11) is " +
    #       str(qhatfunc(0.11))+" as in Ref. arXiv:1907.11808")
    # ax.plot([xlim_inf, xlim_sup], [qhatfunc(0.11), qhatfunc(0.11)],
    #         'r-', label='arXiv:1907.11808')

    # ax.fill_between([xlim_inf, xlim_sup],
    #                 [qhatfunc(0.09), qhatfunc(0.09)],
    #                 [qhatfunc(0.14), qhatfunc(0.14)],
    #                 alpha=0.4, facecolor='red', label='arXiv:1907.11808')

    ax.locator_params(axis='x', nbins=4)
    ax.locator_params(axis='y', nbins=6)
    ax.set_ylim(0.001, 0.12)
    # ax.set_xlim(2.5, 5.5)
    # ax.set_xlim(xlim_inf, xlim_sup)

    ax.set(xlabel='$A^{1/3}$', ylabel='$\hat{q}$ (GeV$^{2}$/fm)')

    # ax.text(xp[0]+0.1, yp[0]-0.01, 'Ne')
    # ax.text(xp[1]+0.1, yp[1]-0.01, 'Kr')
    # ax.text(xp[2]+0.1, yp[2]-0.01, 'Xe')

#     fig.tight_layout()
    ax.legend(frameon=False, loc='upper right', borderaxespad=0.)

#     output_file_name = "/Users/lopez/Dropbox/Paper-Color-Lifetime copy/Figures2020/Fig05_Qhat_MPL.pdf"
    output_file_name = "Fig05_Qhat_MPL.pdf"
    fig.savefig(output_file_name)

    subprocess.call(["open", output_file_name])


if __name__ == "__main__":
    create_plot()
