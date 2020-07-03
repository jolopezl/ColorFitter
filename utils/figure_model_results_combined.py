import subprocess
import numpy as np
import ROOT
from matplotlib import pyplot as plt
# plt.style.use('seaborn')
plt.rc('font', family='serif', serif='Times')
plt.rc('text', usetex=True)
plt.rc('xtick', labelsize=10)
plt.rc('ytick', labelsize=10)
plt.rc('axes', labelsize=10)
# plt.rc('text', usetex=True)
plt.rcParams['errorbar.capsize'] = 3


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
    f = ROOT.TFile.Open("OutputROOT.20200630.BL30_2.root", "READ")
    files = [ROOT.TFile.Open("../test_HERMES/OutputROOT.20200629.BL30_deltakT_D_piplus.root", "READ"),
             ROOT.TFile.Open("../test_HERMES/OutputROOT.20200629.BL30_deltakT_D_piminus.root", "READ"),
             ROOT.TFile.Open("../test_HERMES/OutputROOT.20200629.BL30_deltakT_D_Kplus.root", "READ")]

    dof = 8 - 3

    fig, axs = plt.subplots(6, 4, sharey='row', sharex='col',
                            constrained_layout=True)  # , figsize=(9, 4.5))
    # plt.subplots_adjust(
    #     left  = 0.125,  # the left side of the subplots of the figure
    #     right = 0.9 ,   # the right side of the subplots of the figure
    #     bottom = 0.1,  # the bottom of the subplots of the figure
    #     top = 0.9   ,   # the top of the subplots of the figure
    #     wspace = 0,   # the amount of width reserved for blank space between subplots
    #     hspace = 0,   # the amount of height reserved for white space between subplots
    # )
    # width = 7.056870070568701
    # height = 2.1806927789016632 * 3
    width = 7
    height = 8
    fig.set_size_inches(width, height)

    # axs[0, 0].set_ylim(-0.029, 0.039)
    # axs[1, 0].set_ylim(0.41, 1.19)
    p = 0
    idx = 0
    particles = ["pip", "pim", "Kp"]
    for particle in particles:
        for i in range(4):
            if (p==4):
                axs[p, i].set_ylim(-0.085, 0.09)
            else:
                axs[p, i].set_ylim(-0.03, 0.04)
            
            axs[p+1, i].set_ylim(0.4, 1.1)
            # axs[1,i].set_xlim(0.5,5.5)

            graph_name = "tg_data_pT_"+str(i)
            model_result_name = "tg_model_pT_"+str(i)+"_"+str(particle)
            extrapolation_name = "tg_model_pT_extrapolation_" + \
                str(i)+"_"+str(particle)
            extrapolation_up_name = "tg_model_pT_extrapolation_up_" + \
                str(i)+"_"+str(particle)
            extrapolation_down_name = "tg_model_pT_extrapolation_down_" + \
                str(i)+"_"+str(particle)
            axs[p, i].errorbar(files[idx].Get(graph_name).GetX(),
                               files[idx].Get(graph_name).GetY(),
                               files[idx].Get(graph_name).GetEY(),
                               marker="o", linestyle="", markerfacecolor='grey',color='black', zorder=2, label='Data')
            axs[p, i].plot(f.Get(extrapolation_name).GetX(),
                           f.Get(extrapolation_name).GetY(),
                           "b-", zorder=1, label='Model')
            # if (i != 3):
            axs[p, i].fill_between(f.Get(extrapolation_name).GetX(),
                                   f.Get(extrapolation_down_name).GetY(),
                                   f.Get(extrapolation_up_name).GetY(), alpha=0.4, facecolor='blue', zorder=0)

            chisq1 = getChiSq(files[idx].Get(graph_name), f.Get(extrapolation_name))

            graph_name = "tg_data_Rm_"+str(i)
            model_result_name = "tg_model_Rm_"+str(i)+"_"+str(particle)
            extrapolation_name = "tg_model_Rm_extrapolation_" + \
                str(i)+"_"+str(particle)
            extrapolation_up_name = "tg_model_Rm_extrapolation_up_" + \
                str(i)+"_"+str(particle)
            extrapolation_down_name = "tg_model_Rm_extrapolation_down_" + \
                str(i)+"_"+str(particle)
            axs[p + 1, i].errorbar(files[idx].Get(graph_name).GetX(),
                                   files[idx].Get(graph_name).GetY(),
                                   files[idx].Get(graph_name).GetEY(),
                                   marker="o", linestyle="",  markerfacecolor='grey', color='black', zorder=2, label='Data')
            axs[p + 1, i].plot(f.Get(extrapolation_name).GetX(), f.Get(
                extrapolation_name).GetY(), "r-", zorder=1, label='Model')
            axs[p + 1, i].fill_between(f.Get(extrapolation_name).GetX(), f.Get(extrapolation_down_name).GetY(), f.Get(extrapolation_up_name).GetY(),
                                       alpha=0.4, facecolor='red', zorder=0)

            chisq2 = getChiSq(files[idx].Get(graph_name), f.Get(extrapolation_name))
            chisq = chisq1+chisq2
            print("Chi-square = "+str(chisq))
            print("Chi-square/dof = "+str(chisq/dof))
        p = p + 2
        idx = idx +1

    # fig.set_title('Baseline model with fixed cross-section 30 mb results')
    axs[0, 0].annotate(r'$z_\mathrm{h}=0.32$', xy=(
        0.04, 0.85), xycoords='axes fraction')
    axs[0, 1].annotate(r'$z_\mathrm{h}=0.53$', xy=(
        0.04, 0.85), xycoords='axes fraction')
    axs[0, 2].annotate(r'$z_\mathrm{h}=0.75$', xy=(
        0.04, 0.85), xycoords='axes fraction')
    axs[0, 3].annotate(r'$z_\mathrm{h}=0.94$', xy=(
        0.04, 0.85), xycoords='axes fraction')
    # axs[0, 0].set_title(r'$z_\mathrm{h}=0.32$')
    # axs[0, 1].set_title(r'$z_\mathrm{h}=0.53$')
    # axs[0, 2].set_title(r'$z_\mathrm{h}=0.75$')
    # axs[0, 3].set_title(r'$z_\mathrm{h}=0.94$')

    axs[0, 0].annotate("PI+", xy=(
        0.05, 0.05), xycoords='axes fraction')
    axs[2, 0].annotate("PI-", xy=(
        0.05, 0.05), xycoords='axes fraction')
    axs[4, 0].annotate("K+", xy=(
        0.05, 0.05), xycoords='axes fraction')

    axs[0, 0].set(
        xlabel='', ylabel=r'$\Delta \langle p_\perp^2\rangle$ (GeV$^2$)')
    axs[1, 0].set(xlabel='', ylabel='$R_\mathrm{M}$')
    axs[2, 0].set(
        xlabel='', ylabel=r'$\Delta \langle p_\perp^2\rangle$ (GeV$^2$)')
    axs[3, 0].set(xlabel='', ylabel='$R_\mathrm{M}$')
    axs[4, 0].set(
        xlabel='', ylabel=r'$\Delta \langle p_\perp^2\rangle$ (GeV$^2$)')
    axs[5, 0].set(xlabel='$A^{1/3}$', ylabel='$R_\mathrm{M}$')
    axs[5, 1].set(xlabel='$A^{1/3}$', ylabel='')
    axs[5, 2].set(xlabel='$A^{1/3}$', ylabel='')
    axs[5, 3].set(xlabel='$A^{1/3}$', ylabel='')

    # axs[4, 0].legend(frameon=False, loc='lower left')
    # axs[5, 0].legend(frameon=False, loc='lower left')

    fig.align_ylabels(axs[:, 0])

    # output_file_name = "/Users/lopez/Dropbox/Paper-Color-Lifetime copy/Figures2020/Fig03_ModelOutput_BL_FixedSIG_MPL.pdf"
    output_file_name = "Fig03_ModelOutput_BL30_deltakT_D_combined_2.pdf"
    plt.savefig(output_file_name)

    subprocess.call(["open", output_file_name])


if __name__ == "__main__":
    create_plot()
