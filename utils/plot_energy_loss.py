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


def create_plot():
    print("Energy loss fit results")
    f = ROOT.TFile.Open("OutputROOT.20200316.BLE_extended_fixed.root", "READ")

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
            # yp[i][j] = y_input_val[j] * (lp**2) * photon_energy[j] * (1.0 / 25.7)
            # yerr[i][j] = y_input_err[j] * (lp**2) * photon_energy[j] * (1.0 / 25.7)
            Lc = critical_length.GetX()[j]
            yp[i][j] = y_input_val[j] * Lc * (2*lp - Lc) * photon_energy[j] * (1.0 / 25.7)
            yerr[i][j] = y_input_err[j] * Lc * (2*lp - Lc) * photon_energy[j] * (1.0 / 25.7)

    fig, ax = plt.subplots(constrained_layout=True)
    width = 3.4039020340390205
    height = width * 0.75
    fig.set_size_inches(width, height)

    ax.errorbar(xp[0], yp[0], yerr[0], uplims=True,  # capsize=0,
                marker="o", linestyle="", color='red', zorder=5,
                label='Neon')
    ax.errorbar(xp[1], yp[1], yerr[1], uplims=True,  # capsize=0,
                marker="s", linestyle="", color='blue', zorder=5,
                label='Kripton')
    ax.errorbar(xp[2], yp[2], yerr[2], uplims=True,  # capsize=0,
                marker="X", linestyle="", color='green', zorder=5,
                label='Xenon')

    ax.plot([0,1],[0,0],'k--')

    ax.locator_params(axis='y', nbins=6)
    # ax.set_ylim(-2, 0)
    ax.set_xlim(0, 1)

    # ax.set(xlabel='$A^{1/3}$', ylabel='$E_\mathrm{loss}$ (GeV)')
    ax.set(xlabel='$z_\mathrm{h}$', ylabel='$E_\mathrm{loss}$ (GeV)')

#     fig.tight_layout()
    ax.legend(frameon=False, loc='lower right', borderaxespad=0.)

    # output_file_name = "/Users/lopez/Dropbox/Paper-Color-Lifetime copy/Figures2020/Fig05_Qhat_MPL.pdf"
    output_file_name = "Fig_Energy_Loss.pdf"
    fig.savefig(output_file_name)

    subprocess.call(["open", output_file_name])

    fig2, ax2 = plt.subplots(constrained_layout=True)
    width = 3.4039020340390205
    height = width * 0.75
    fig2.set_size_inches(width, height)
    ax2.plot(f.Get('tg_average_parton_length_0').GetX(),
               f.Get('tg_average_parton_length_0').GetY(),
               label = 'bin 1')
    ax2.plot(f.Get('tg_average_parton_length_1').GetX(),
               f.Get('tg_average_parton_length_1').GetY(),
               label = 'bin 2')
    ax2.plot(f.Get('tg_average_parton_length_2').GetX(),
               f.Get('tg_average_parton_length_2').GetY(),
               label = 'bin 3')
    ax2.plot(f.Get('tg_average_parton_length_3').GetX(),
               f.Get('tg_average_parton_length_3').GetY(),
               label = 'bin 4')
    ax2.legend(frameon=False, loc='lower right', borderaxespad=0.)
    ax2.set(xlabel='$A^{1/3}$', ylabel='$L_\mathrm{parton}^\mathrm{in-medium}$ (fm)')
    output_file_name = 'temp.pdf'
    fig2.savefig(output_file_name)
    subprocess.call(["open", output_file_name])

    fig3, ax3 = plt.subplots(constrained_layout=True)
    width = 3.4039020340390205
    height = width * 0.75
    fig3.set_size_inches(width, height)
    ax3.errorbar(f.Get('tg_c1').GetX(),
               f.Get('tg_c1').GetY(),
               f.Get('tg_c1').GetEY())
    # ax2.legend(frameon=False, loc='lower right', borderaxespad=0.)
    ax3.set(xlabel='$z_\mathrm{h}$', ylabel='$L_\mathrm{critical}$ (fm)')
    output_file_name = 'temp2.pdf'
    fig3.savefig(output_file_name)
    subprocess.call(["open", output_file_name])


if __name__ == "__main__":
    create_plot()
