
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
# plt.rc('text', usetex=True)
plt.rcParams['errorbar.capsize'] = 3


def create_plot(input_file = "OutputROOT.20200325.BLEI_single_par.root", critical_length_value = 100):
    print("Energy loss fit results")
    f = ROOT.TFile.Open(input_file, "READ")

    text = "$L_\mathrm{crit} = "+str(critical_length_value)+"$ (fm)"

    critical_length = f.Get("tg_c1")
    shape_parameter = f.Get("tg_c2")
    average_parton_length = [f.Get("tg_average_parton_length_0"),
                             f.Get("tg_average_parton_length_1"),
                             f.Get("tg_average_parton_length_2"),
                             f.Get("tg_average_parton_length_3")]

    xp = [np.ndarray(shape=4, dtype=float, buffer=shape_parameter.GetX()) - 0.025,
          np.ndarray(shape=4, dtype=float, buffer=shape_parameter.GetX()),
          np.ndarray(shape=4, dtype=float, buffer=shape_parameter.GetX()) + 0.025]

    y_input_val = np.ndarray(shape=4, dtype=float,
                             buffer=shape_parameter.GetY())
    y_input_err = np.ndarray(shape=4, dtype=float,
                             buffer=shape_parameter.GetEY())

    yp = [np.ndarray(shape=4, dtype=float),
          np.ndarray(shape=4, dtype=float),
          np.ndarray(shape=4, dtype=float)]

    yerr = [np.ndarray(shape=4, dtype=float),
            np.ndarray(shape=4, dtype=float),
            np.ndarray(shape=4, dtype=float)]

    A13 = np.array([20.1797**(1./3.), 83.7980**(1./3.), 131.293**(1./3.)])
    A = ["Neon", "Kripton", "Xenon"]
    photon_energy = [14.37, 13.03, 12.33, 10.70]

    print yp
    print A13
    print photon_energy

    for i in range(3):
        for j in range(4):
            lp = average_parton_length[j].Eval(A13[i])
            Lc = critical_length_value
            if (lp < Lc):
                yp[i][j] = y_input_val[j] * (lp**2) * photon_energy[j]
                yerr[i][j] = y_input_err[j] * (lp**2) * photon_energy[j]
            else:
                yp[i][j] = y_input_val[j] * Lc * (2*lp - Lc) * photon_energy[j]
                yerr[i][j] = y_input_err[j] * Lc * \
                    (2*lp - Lc) * photon_energy[j]

    fig, ax = plt.subplots(constrained_layout=True)
    width = 3.4039020340390205
    height = width * 0.75
    fig.set_size_inches(width, height)

    ax.errorbar(xp[0], yp[0], yerr[0],  # uplims=True,  # capsize=0,
                marker="o", linestyle="", color='red', zorder=5,
                label='Neon')
    ax.errorbar(xp[1], yp[1], yerr[1],  # uplims=True,  # capsize=0,
                marker="s", linestyle="", color='blue', zorder=5,
                label='Kripton')
    ax.errorbar(xp[2], yp[2], yerr[2],  # uplims=True,  # capsize=0,
                marker="X", linestyle="", color='green', zorder=5,
                label='Xenon')

    ax.plot([0, 1], [0, 0], 'k--')

    ax.locator_params(axis='y', nbins=6)
    # ax.set_ylim(-0.25, 0.75)
    ax.set_xlim(0, 1)

    # ax.set(xlabel='$A^{1/3}$', ylabel='$E_\mathrm{loss}$ (GeV)')
    ax.set(xlabel='$z_\mathrm{h}$', ylabel='$E_\mathrm{loss}$ (GeV)')

#     fig.tight_layout()
    ax.legend(frameon=False, loc='upper left', borderaxespad=0.)

    ax.annotate(text,
                xy=(0.02, 0.03), xycoords='axes fraction')

    # output_file_name = "/Users/lopez/Dropbox/Paper-Color-Lifetime copy/Figures2020/Fig05_Qhat_MPL.pdf"
    output_file_name = "Fig_Energy_Loss__Lc="+str(critical_length_value)+".pdf"
    fig.savefig(output_file_name)

    subprocess.call(["open", output_file_name])

    return ax


if __name__ == "__main__":
    create_plot("OutputROOT.20200325.BLEI_single_par.root", 100)
    create_plot("OutputROOT.20200325.BLEI_single_par_Lcrit3.root", 3)
    create_plot("OutputROOT.20200325.BLEI_single_par_Lcrit_one_and_a_half_fm.root", 1.5)
    create_plot("OutputROOT.20200325.BLEI_single_par_Lcrit_half_fm.root", 0.5)
