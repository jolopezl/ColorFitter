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

# matplotlib.rcParams.update({'font.size': 8})
matplotlib.rcParams['mathtext.fontset'] = 'cm'
matplotlib.rcParams['font.family'] = 'cm'
matplotlib.pyplot.title(r'ABC123 vs $\mathrm{ABC123}^{123}$')

SIG1 = np.array([27.075, 25.604, 25.109, 24.946])
z_value = np.array([0.32, 0.54, 0.75, 0.94])
rho = np.array([-0.7, -0.7, -0.7, -0.8])

CORRELATION = [
    {'Q0-KT': -0.710,
     'Q0-LC': -0.473,
     'LC-KT': 0.091},
    {'Q0-KT': 0.751,
     'Q0-LC': 0.250,
     'LC-KT': 0.040},
    {'Q0-KT': -0.766,
     'Q0-LC': -0.041,
     'LC-KT': 0.004},
    {'Q0-KT': -0.793,
     'Q0-LC': -0.027,
     'LC-KT': 0.002},
]


def getChiSq(data, model):
    x = data.GetX()
    y = data.GetY()
    yerr = data.GetEY()
    chisq = 0
    for i in range(3):
        chisq = chisq + ((y[i] - model.Eval(x[i]))**2) / (yerr[i]**2)
    return chisq


def create_plot():
    print("Model results")
    # f = ROOT.TFile.Open("OutputROOT.20200707.BL30_piplus.root", "READ")
    f = ROOT.TFile.Open("OutputROOT.20200804.BL30NN_piplus.root", "READ")

    dof = 8 - 4

    fig, axs = plt.subplots(2, 4, sharey='row', sharex='col',
                            constrained_layout=True)  # , figsize=(9, 4.5))
    width = 7.056870070568701
    height = 2.1806927789016632 * 1.5
    fig.set_size_inches(width, height)

    # axs[0, 0].set_ylim(-0.029, 0.039)
    # axs[1, 0].set_ylim(0.41, 1.19)

    for i in range(4):
        # axs[0, i].set_xlim(1, 6)
        # axs[1, i].set_xlim(1, 6)
        # axs[1,i].set_xlim(0.5,5.5)

        graph_name = "tg_data_pT_"+str(i)
        model_result_name = "tg_model_pT_"+str(i)
        extrapolation_name = "tg_model_pT_extrapolation_"+str(i)
        extrapolation_up_name = "tg_model_pT_extrapolation_up_"+str(i)
        extrapolation_down_name = "tg_model_pT_extrapolation_down_"+str(i)
        axs[0, i].errorbar(f.Get(graph_name).GetX(), f.Get(graph_name).GetY(), f.Get(
            graph_name).GetEY(), marker="o", linestyle="", markerfacecolor='grey',
            color='black', zorder=2, label='Data')
        axs[0, i].plot(f.Get(extrapolation_name).GetX(), f.Get(
            extrapolation_name).GetY(), "b-", zorder=1, label='Model')

        # Calculate de uncertainties on the fly
        npoints = f.Get(extrapolation_name).GetN()
        xp = np.ndarray(npoints, dtype=float,
                        buffer=f.Get(extrapolation_name).GetX())
        yp = np.ndarray(npoints, dtype=float,
                        buffer=f.Get(extrapolation_name).GetY())
        yp_hi = np.zeros(npoints)
        yp_lo = np.zeros(npoints)
        pt2 = np.ndarray(npoints, dtype=float,
                         buffer=f.Get(extrapolation_name).GetY())
        Lc = f.Get("tg_lp").GetY()[i]
        LcErr = f.Get("tg_lp").GetEY()[i]
        q0 = f.Get("tg_q0").GetY()[i]
        q0Err = f.Get("tg_q0").GetEY()[i]
        kperp2 = f.Get("tg_c1").GetY()[i]
        kperp2Err = f.Get("tg_c1").GetEY()[i]
        z = z_value[i]
        # average_density = np.ndarray(npoints, dtype=float, buffer=f.Get("tg_average_density_"+str(i)).GetY())
        average_density = f.Get("tg_average_density_"+str(i))

        idx = 0
        for yp_val in yp:
            uncert = 0.0
            uncert += (pt2[i]/q0 - z**2 * kperp2)**2 * q0Err**2
            average_density_point = average_density.Eval(xp[idx])
            uncert += q0**2 * average_density_point**2 * LcErr**2
            uncert += z**4 * kperp2Err**2
            # add correlation terms
            uncert += 2 * (pt2[i]/q0 - z**2 * kperp2) * z**2 * \
                CORRELATION[i]['Q0-KT'] * q0Err * kperp2Err
            uncert += 2 * (pt2[i]/q0 - z**2 * kperp2) * q0 * \
                average_density_point * CORRELATION[i]['Q0-LC'] * q0Err * LcErr
            uncert += 2 * z**2 * q0 * average_density_point * \
                CORRELATION[i]['LC-KT'] * LcErr * kperp2Err
            uncert = np.sqrt(uncert)
            yp_hi[idx] = yp_val + 0.25 * uncert
            yp_lo[idx] = yp_val - 0.25 * uncert
            idx = idx + 1

        # axs[0, i].fill_between(xp, yp_lo, yp_hi, alpha=0.4,
        #                        facecolor='blue', zorder=0)

        chisq1 = getChiSq(f.Get(graph_name), f.Get(extrapolation_name))

        graph_name = "tg_data_Rm_"+str(i)
        model_result_name = "tg_model_Rm_"+str(i)
        extrapolation_name = "tg_model_Rm_extrapolation_"+str(i)
        extrapolation_up_name = "tg_model_Rm_extrapolation_up_"+str(i)
        extrapolation_down_name = "tg_model_Rm_extrapolation_down_"+str(i)
        axs[1, i].errorbar(f.Get(graph_name).GetX(), f.Get(graph_name).GetY(), f.Get(
            graph_name).GetEY(), marker="o", linestyle="",  markerfacecolor='grey',
            color='black', zorder=2, label='Data')
        axs[1, i].plot(f.Get(extrapolation_name).GetX(), f.Get(
            extrapolation_name).GetY(), "r-", zorder=1, label='Model')
        # axs[1, i].fill_between(f.Get(extrapolation_name).GetX(), f.Get(extrapolation_down_name).GetY(), f.Get(extrapolation_up_name).GetY(),
        #                        alpha=0.4, facecolor='red', zorder=0)

        # Calculate de uncertainties on the fly
        npoints = f.Get(extrapolation_name).GetN()
        xp2 = np.ndarray(npoints, dtype=float,
                         buffer=f.Get(extrapolation_name).GetX())
        yp2 = np.ndarray(npoints, dtype=float,
                         buffer=f.Get(extrapolation_name).GetY())
        yp_hi2 = np.zeros(npoints)
        yp_lo2 = np.zeros(npoints)
        LcErr = f.Get("tg_lp").GetEY()[i]
        # multiplicity_density = f.Get("tg_multiplicity_density_"+str(i))
        multiplicity_density = f.Get("tg_average_density_"+str(i))

        idx = 0
        for yp_val in yp2:
            uncert = 0.0
            multiplicity_density_point = multiplicity_density.Eval(xp[idx])
            uncert += (SIG1[i] * 0.1)**2 * \
                multiplicity_density_point**2 * yp_val**2 * LcErr**2
            uncert = np.sqrt(uncert)
            yp_hi2[idx] = yp_val + uncert
            yp_lo2[idx] = yp_val - uncert
            idx = idx + 1

        # axs[1, i].fill_between(xp2, yp_lo2, yp_hi2,
        #                        alpha=0.4, facecolor='red', zorder=0)

        chisq2 = getChiSq(f.Get(graph_name), f.Get(extrapolation_name))
        chisq = chisq1+chisq2
        print("Chi-square = "+str(chisq))
        print("Chi-square/dof = "+str(chisq/dof))

        axs[0,i].annotate(r'$\chi^2/$dof = %.2f' % (chisq/dof), xy=(0.04, 0.88), xycoords='axes fraction', fontsize=8)

    # fig.set_title('Baseline model with fixed cross-section 30 mb results')
    axs[0, 0].annotate(r'$z_\mathrm{h}=0.32$', xy=(0.04, 0.76), xycoords='axes fraction', fontsize=8)
    axs[0, 1].annotate(r'$z_\mathrm{h}=0.53$', xy=(0.04, 0.76), xycoords='axes fraction', fontsize=8)
    axs[0, 2].annotate(r'$z_\mathrm{h}=0.75$', xy=(0.04, 0.76), xycoords='axes fraction', fontsize=8)
    axs[0, 3].annotate(r'$z_\mathrm{h}=0.94$', xy=(0.04, 0.76), xycoords='axes fraction', fontsize=8)

    axs[0, 0].set(xlabel='', ylabel=r'$\Delta \langle p_\mathrm{T}^2\rangle$ (GeV$^2$)')
    axs[1, 0].set(xlabel='$A^{1/3}$', ylabel='$R_\mathrm{M}$')
    # axs[2,0].set(xlabel='', ylabel=r'$\Delta \langle p_\mathrm{T}^2\rangle$ (GeV$^2$)')
    # axs[3,0].set(xlabel='$A^{1/3}$', ylabel='$R_\mathrm{M}$')
    axs[1, 1].set(xlabel='$A^{1/3}$', ylabel='')
    axs[1, 2].set(xlabel='$A^{1/3}$', ylabel='')
    axs[1, 3].set(xlabel='$A^{1/3}$', ylabel='')

    xpos = f.Get("tg_data_Rm_0").GetX()
    ypos = f.Get("tg_data_Rm_0").GetY()
    # axs[1, 0].text(xpos[0], ypos[0]-0.1, 'Ne')
    # axs[1, 0].text(xpos[1], ypos[1]-0.1, 'Kr')
    # axs[1, 0].text(xpos[2], ypos[2]-0.1, 'Xe')

    axs[0, 0].legend(frameon=False, loc='lower left',fontsize=8)
    axs[1, 0].legend(frameon=False, loc='lower left',fontsize=8)

    fig.align_ylabels(axs[:, 0])

    # output_file_name = "/Users/lopez/Dropbox/Paper-Color-Lifetime copy/Figures2020/Fig03_ModelOutput_BL_FixedSIG_MPL.pdf"
    output_file_name = "Fig03_ModelOutput_BL_SIG_deltakT_D_piplus.pdf"
    plt.savefig(output_file_name)

    subprocess.call(["open", output_file_name])


if __name__ == "__main__":
    create_plot()
