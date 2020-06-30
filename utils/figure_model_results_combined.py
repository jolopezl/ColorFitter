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
    files = [ROOT.TFile.Open("OutputROOT.20200629.BL30_deltakT_D_piplus.root", "READ"),
         ROOT.TFile.Open("OutputROOT.20200629.BL30_deltakT_D_piminus.root", "READ"),
         ROOT.TFile.Open("OutputROOT.20200629.BL30_deltakT_D_Kplus.root", "READ")]
    
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
    for f in files:
        for i in range(4):
            # axs[p, i].set_ylim(0, 5.5)
            # axs[p+1, i].set_ylim(0.5, 1.1)
            # axs[1,i].set_xlim(0.5,5.5)

            graph_name = "tg_data_pT_"+str(i)
            model_result_name = "tg_model_pT_"+str(i)
            extrapolation_name = "tg_model_pT_extrapolation_"+str(i)
            axs[p, i].errorbar(f.Get(graph_name).GetX(), f.Get(graph_name).GetY(), f.Get(
                graph_name).GetEY(), marker="o", linestyle="", markerfacecolor='grey',
                color='black', zorder=2, label='Data')
            axs[p, i].plot(f.Get(extrapolation_name).GetX(), f.Get(
                extrapolation_name).GetY(), "b-", zorder=1, label='Model')

            chisq1 = getChiSq(f.Get(graph_name), f.Get(extrapolation_name))

            graph_name = "tg_data_Rm_"+str(i)
            model_result_name = "tg_model_Rm_"+str(i)
            extrapolation_name = "tg_model_Rm_extrapolation_"+str(i)
            extrapolation_up_name = "tg_model_Rm_extrapolation_up_"+str(i)
            extrapolation_down_name = "tg_model_Rm_extrapolation_down_"+str(i)
            axs[p + 1, i].errorbar(f.Get(graph_name).GetX(), f.Get(graph_name).GetY(), f.Get(
                graph_name).GetEY(), marker="o", linestyle="",  markerfacecolor='grey',
                color='black', zorder=2, label='Data')
            axs[p + 1, i].plot(f.Get(extrapolation_name).GetX(), f.Get(
                extrapolation_name).GetY(), "r-", zorder=1, label='Model')

            chisq2 = getChiSq(f.Get(graph_name), f.Get(extrapolation_name))
            chisq = chisq1+chisq2
            print("Chi-square = "+str(chisq))
            print("Chi-square/dof = "+str(chisq/dof))
        p = p + 2

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

    axs[0, 0].set(xlabel='', ylabel=r'$\Delta \langle p_\perp^2\rangle$ (GeV$^2$)')
    axs[1, 0].set(xlabel='', ylabel='$R_\mathrm{M}$')
    axs[2, 0].set(xlabel='', ylabel=r'$\Delta \langle p_\perp^2\rangle$ (GeV$^2$)')
    axs[3, 0].set(xlabel='', ylabel='$R_\mathrm{M}$')
    axs[4, 0].set(xlabel='', ylabel=r'$\Delta \langle p_\perp^2\rangle$ (GeV$^2$)')
    axs[5, 0].set(xlabel='$A^{1/3}$', ylabel='$R_\mathrm{M}$')
    axs[5, 1].set(xlabel='$A^{1/3}$', ylabel='')
    axs[5, 2].set(xlabel='$A^{1/3}$', ylabel='')
    axs[5, 3].set(xlabel='$A^{1/3}$', ylabel='')

    # axs[4, 0].legend(frameon=False, loc='lower left')
    # axs[5, 0].legend(frameon=False, loc='lower left')

    fig.align_ylabels(axs[:, 0])

    # output_file_name = "/Users/lopez/Dropbox/Paper-Color-Lifetime copy/Figures2020/Fig03_ModelOutput_BL_FixedSIG_MPL.pdf"
    output_file_name = "Fig03_ModelOutput_BL30_deltakT_D_combined.pdf"
    plt.savefig(output_file_name)

    subprocess.call(["open", output_file_name])


if __name__ == "__main__":
    create_plot()
