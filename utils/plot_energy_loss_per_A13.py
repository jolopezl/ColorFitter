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

    N = average_parton_length.GetN()
    xp = np.ndarray(shape=N, dtype=float, buffer=average_parton_length.GetX())
    yp = [np.ndarray(shape=N, dtype=float),np.ndarray(shape=N, dtype=float),np.ndarray(shape=N, dtype=float)]

    energy_uncertainty = np.ndarray(4,float,shape_parameter.GetEY())

    A13 = np.array([20.1797**(1./3.), 83.7980**(1./3.), 131.293**(1./3.)])
    A = ["Neon", "Kripton", "Xenon"]
    photon_energy = [14.37, 13.03, 12.33, 10.70]
    photon_energy_average = (13.03+12.33+10.70)/3.0
    for j in range(N):
        lp = average_parton_length[i].GetX()[j]
        ## critical len average error
        band = (energy_uncertainty[1]+energy_uncertainty[2]+energy_uncertainty[3]) / 3.0
        yp[i][j] = -band * Lc * (2*lp - Lc) * photon_energy[j] * (1.0 / 25.7)

    fig, ax = plt.subplots(constrained_layout=True)
    width = 3.4039020340390205
    height = width * 0.75
    fig.set_size_inches(width, height)



    ax.locator_params(axis='y', nbins=6)
    # ax.set_ylim(-2, 0)
    ax.set_xlim(0, 1)

    # ax.set(xlabel='$A^{1/3}$', ylabel='$E_\mathrm{loss}$ (GeV)')
    ax.set(xlabel='$A^{1/3}$', ylabel='$E_\mathrm{loss}$ (GeV)')

#     fig.tight_layout()
    ax.legend(frameon=False, loc='lower right', borderaxespad=0.)

    # output_file_name = "/Users/lopez/Dropbox/Paper-Color-Lifetime copy/Figures2020/Fig05_Qhat_MPL.pdf"
    output_file_name = "Fig_Energy_Loss_Per_A.pdf"
    fig.savefig(output_file_name)


if __name__ == "__main__":
    create_plot()
