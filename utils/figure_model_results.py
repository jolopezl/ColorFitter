import numpy as np
import ROOT
from matplotlib import pyplot as plt
# plt.style.use('seaborn')
# plt.rc('font', family='serif', serif='Times')
# plt.rc('text', usetex=True)
plt.rc('xtick', labelsize=12)
plt.rc('ytick', labelsize=12)
plt.rc('axes', labelsize=12)
# plt.rc('text', usetex=True)
plt.rcParams['errorbar.capsize'] = 3


def create_plot():
    print("Model results")
    f = ROOT.TFile.Open("OutputROOT.20200306.BL_debug_energy_loss.root", "READ")

    fig, axs = plt.subplots(2, 4, sharey='row', sharex='col',
                            constrained_layout=True, figsize=(9, 4.5))

    axs[0, 0].set_ylim(-0.029, 0.039)
    # axs[1,0].set_ylim(-0.029,0.039)

    for i in range(4):
        axs[0, i].set_xlim(2.5, 5.5)
        axs[1, i].set_xlim(2.5, 5.5)
        # axs[1,i].set_xlim(2.5,5.5)

        graph_name = "tg_data_pT_"+str(i)
        model_result_name = "tg_model_pT_"+str(i)
        extrapolation_name = "tg_model_pT_extrapolation_"+str(i)
        extrapolation_up_name = "tg_model_pT_extrapolation_up_"+str(i)
        extrapolation_down_name = "tg_model_pT_extrapolation_down_"+str(i)
        axs[0, i].errorbar(f.Get(graph_name).GetX(), f.Get(graph_name).GetY(), f.Get(
            graph_name).GetEY(), marker="o", linestyle="", color='black', zorder=2)
        axs[0, i].plot(f.Get(extrapolation_name).GetX(), f.Get(
            extrapolation_name).GetY(), "b-", zorder=1)
        axs[0, i].fill_between(f.Get(extrapolation_name).GetX(), f.Get(extrapolation_down_name).GetY(), f.Get(extrapolation_up_name).GetY(),
                               alpha=0.4, facecolor='blue', zorder=0)

        graph_name = "tg_data_Rm_"+str(i)
        model_result_name = "tg_model_Rm_"+str(i)
        extrapolation_name = "tg_model_Rm_extrapolation_"+str(i)
        extrapolation_up_name = "tg_model_Rm_extrapolation_up_"+str(i)
        extrapolation_down_name = "tg_model_Rm_extrapolation_down_"+str(i)
        axs[1, i].errorbar(f.Get(graph_name).GetX(), f.Get(graph_name).GetY(), f.Get(
            graph_name).GetEY(), marker="o", linestyle="", color='black', zorder=2)
        axs[1, i].plot(f.Get(extrapolation_name).GetX(), f.Get(
            extrapolation_name).GetY(), "r-", zorder=1)
        axs[1, i].fill_between(f.Get(extrapolation_name).GetX(), f.Get(extrapolation_down_name).GetY(), f.Get(extrapolation_up_name).GetY(),
                               alpha=0.4, facecolor='red', zorder=0)

    # f = ROOT.TFile.Open("OutputROOT.20191115.BLE30.root", "READ")
    # for i in range(4):
    #     axs[2,i].set_xlim(2.5,5.5)
    #     axs[3,i].set_xlim(2.5,5.5)
    #     # axs[1,i].set_xlim(2.5,5.5)

    #     graph_name = "tg_data_pT_"+str(i)
    #     model_result_name = "tg_model_pT_"+str(i)
    #     extrapolation_name = "tg_model_pT_extrapolation_"+str(i)
    #     extrapolation_up_name = "tg_model_pT_extrapolation_up_"+str(i)
    #     extrapolation_down_name = "tg_model_pT_extrapolation_down_"+str(i)
    #     axs[2,i].errorbar(f.Get(graph_name).GetX(), f.Get(graph_name).GetY(), f.Get(graph_name).GetEY(), marker="o", linestyle="",color='black')
    #     axs[2,i].plot(f.Get(extrapolation_name).GetX(), f.Get(extrapolation_name).GetY(),"b-")
    #     axs[2,i].fill_between(f.Get(extrapolation_name).GetX(), f.Get(extrapolation_down_name).GetY(), f.Get(extrapolation_up_name).GetY(),
    #                           alpha=0.4, edgecolor='blue', facecolor='blue')

    #     graph_name = "tg_data_Rm_"+str(i)
    #     model_result_name = "tg_model_Rm_"+str(i)
    #     extrapolation_name = "tg_model_Rm_extrapolation_"+str(i)
    #     extrapolation_up_name = "tg_model_Rm_extrapolation_up_"+str(i)
    #     extrapolation_down_name = "tg_model_Rm_extrapolation_down_"+str(i)
    #     axs[3,i].errorbar(f.Get(graph_name).GetX(), f.Get(graph_name).GetY(), f.Get(graph_name).GetEY(), marker="o", linestyle="", color='black')
    #     axs[3,i].plot(f.Get(extrapolation_name).GetX(), f.Get(extrapolation_name).GetY(),"r-")
    #     axs[3,i].fill_between(f.Get(extrapolation_name).GetX(), f.Get(extrapolation_down_name).GetY(), f.Get(extrapolation_up_name).GetY(),
    #                           alpha=0.4, edgecolor='red', facecolor='red', antialiased=True)

    # fig.set_title('Baseline model with fixed cross-section 30 mb results')
    axs[0, 0].set_title(r'$z_\mathrm{h}=0.32$')
    axs[0, 1].set_title(r'$z_\mathrm{h}=0.53$')
    axs[0, 2].set_title(r'$z_\mathrm{h}=0.75$')
    axs[0, 3].set_title(r'$z_\mathrm{h}=0.94$')

    axs[0, 0].set(
        xlabel='', ylabel=r'$\Delta \langle p_\mathrm{T}^2\rangle$ (GeV$^2$)')
    axs[1, 0].set(xlabel='$A^{1/3}$', ylabel='$R_\mathrm{M}$')
    # axs[2,0].set(xlabel='', ylabel=r'$\Delta \langle p_\mathrm{T}^2\rangle$ (GeV$^2$)')
    # axs[3,0].set(xlabel='$A^{1/3}$', ylabel='$R_\mathrm{M}$')
    axs[1, 1].set(xlabel='$A^{1/3}$', ylabel='')
    axs[1, 2].set(xlabel='$A^{1/3}$', ylabel='')
    axs[1, 3].set(xlabel='$A^{1/3}$', ylabel='')

    # axs[1,0].annotate('Ne', xy=(20.1797**(1./3.), 0.85),  xycoords='data', xytext=(0,-40), textcoords='offset points',
    #         arrowprops=dict(arrowstyle="->",connectionstyle="angle,angleA=0,angleB=90,rad=10")
    #         )
    # axs[1,0].annotate('Kr', xy=(83.7980**(1./3.), 0.70),  xycoords='data', xytext=(0,-40), textcoords='offset points',
    #         arrowprops=dict(arrowstyle="->",connectionstyle="angle,angleA=0,angleB=90,rad=10")
    #         )
    # axs[1,0].annotate('Xe', xy=(131.293**(1./3.), 0.65),  xycoords='data', xytext=(0,-40), textcoords='offset points',
    #         arrowprops=dict(arrowstyle="-|>",connectionstyle="angle,angleA=0,angleB=90,rad=10")
    #         )
    xpos = f.Get("tg_data_Rm_0").GetX()
    ypos = f.Get("tg_data_Rm_0").GetY()
    axs[1, 0].text(xpos[0], ypos[0]-0.1, 'Ne')
    axs[1, 0].text(xpos[1], ypos[1]-0.1, 'Kr')
    axs[1, 0].text(xpos[2], ypos[2]-0.1, 'Xe')

    fig.align_ylabels(axs[:, 0])

    plt.savefig("modelplot_result.pdf")


if __name__ == "__main__":
    create_plot()
