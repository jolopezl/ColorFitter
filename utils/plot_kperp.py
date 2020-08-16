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

z_value = np.array([0.32, 0.54, 0.75, 0.94])


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

def create_plot():
    print("k_perp^2 fit results")
    f = ROOT.TFile.Open("OutputROOT.20200707.BL30_piplus.root", "READ")

    kperp = f.Get("tg_c1")

    xp = kperp.GetX()
    yp = kperp.GetY()
    yerr = kperp.GetEY()

    for idx in range(4):
        yp[idx] = yp[idx] * z_value[idx]**2
        yerr[idx] = yerr[idx] * z_value[idx]**2

    fig, ax = plt.subplots(constrained_layout=True)
    width = 3.4039020340390205
    height = width * 0.75
    fig.set_size_inches(width, height)

    pa = ax.errorbar(xp, yp, yerr,  # capsize=0,
                marker="o", linestyle="", markerfacecolor='grey',
                color='black', zorder=5,
                label='Fit result')

    x_lo = 0.28
    x_up = 0.98
    mean, meanError = calculate_mean(yp, yerr)
    pb = ax.plot([x_lo, x_up], [mean, mean],
            'k--', label=r'average $= %.3f \pm %.3f$ GeV$^{2}$' % (mean, meanError))
    pc = ax.fill_between([x_lo, x_up],
                    [mean - meanError, mean - meanError],
                    [mean + meanError, mean + meanError],
                    alpha=0.4, facecolor='g', hatch='/', zorder=0)

    ax.axhline(lw=1,ls='-',c='k')

    print(mean)
    print(meanError)

    # average_qhat_info = r'average $= 0.002 \pm 0.001$ GeV$^{2}$'
    # ax.annotate(average_qhat_info, xy=(0.075, 0.075), xycoords='axes fraction')

    ax.locator_params(axis='x', nbins=4)
    ax.locator_params(axis='y', nbins=6)
    ax.set_ylim(-0.0069, 0.0039)
    ax.set_xlim(0, 1)

    ax.set(xlabel='$z$', ylabel=r'$z^2\Delta\langle k_\perp^2 \rangle$ (GeV$^{2}$)')
    
    ax.legend(frameon=False, loc='upper right', borderaxespad=0.)
    # ax.legend([(pb[0], pc[0]), ], ['Stuff'])

#     output_file_name = "/Users/lopez/Dropbox/Paper-Color-Lifetime copy/Figures2020/Fig05_Qhat_MPL.pdf"
    output_file_name = "Fig06_kperp.pdf"
    fig.savefig(output_file_name)

    subprocess.call(["open", output_file_name])


if __name__ == "__main__":
    create_plot()
