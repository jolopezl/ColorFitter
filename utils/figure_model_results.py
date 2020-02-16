import ROOT
from matplotlib import pyplot as plt
# plt.rc('font', family='serif', serif='Times')
# plt.rc('text', usetex=True)
# plt.rc('xtick', labelsize=12)
# plt.rc('ytick', labelsize=12)
# plt.rc('axes', labelsize=12)
# plt.rc('text', usetex=True)

import numpy as np

def main():
    print("Model results")
    f = ROOT.TFile.Open("OutputROOT.20191115.BL30.root", "READ")

    fig, axs = plt.subplots(4, 4, sharey='row', sharex='col',constrained_layout=True,figsize=(9,6))

    axs[0,0].set_ylim(-0.029,0.039)
    # axs[1,0].set_ylim(-0.029,0.039)

    for i in range(4):
        axs[0,i].set_xlim(2.5,5.5)
        axs[1,i].set_xlim(2.5,5.5)
        # axs[1,i].set_xlim(2.5,5.5)

        graph_name = "tg_data_pT_"+str(i)
        model_result_name = "tg_model_pT_"+str(i)
        extrapolation_name = "tg_model_pT_extrapolation_"+str(i)
        extrapolation_up_name = "tg_model_pT_extrapolation_up_"+str(i)
        extrapolation_down_name = "tg_model_pT_extrapolation_down_"+str(i)
        axs[0,i].errorbar(f.Get(graph_name).GetX(), f.Get(graph_name).GetY(), f.Get(graph_name).GetEY(), marker="o", linestyle="",color='black')
        axs[0,i].plot(f.Get(extrapolation_name).GetX(), f.Get(extrapolation_name).GetY(), "b-")
        axs[0,i].fill_between(f.Get(extrapolation_name).GetX(), f.Get(extrapolation_down_name).GetY(), f.Get(extrapolation_up_name).GetY(),
                              alpha=0.4, edgecolor='blue', facecolor='blue')
        
        graph_name = "tg_data_Rm_"+str(i)
        model_result_name = "tg_model_Rm_"+str(i)
        extrapolation_name = "tg_model_Rm_extrapolation_"+str(i)
        extrapolation_up_name = "tg_model_Rm_extrapolation_up_"+str(i)
        extrapolation_down_name = "tg_model_Rm_extrapolation_down_"+str(i)
        axs[1,i].errorbar(f.Get(graph_name).GetX(), f.Get(graph_name).GetY(), f.Get(graph_name).GetEY(), marker="o", linestyle="", color='black')
        axs[1,i].plot(f.Get(extrapolation_name).GetX(), f.Get(extrapolation_name).GetY(), "r-")
        axs[1,i].fill_between(f.Get(extrapolation_name).GetX(), f.Get(extrapolation_down_name).GetY(), f.Get(extrapolation_up_name).GetY(),
                              alpha=0.4, edgecolor='red', facecolor='red')

    f = ROOT.TFile.Open("OutputROOT.20191115.BLE30.root", "READ")
    for i in range(4):
        axs[2,i].set_xlim(2.5,5.5)
        axs[3,i].set_xlim(2.5,5.5)
        # axs[1,i].set_xlim(2.5,5.5)

        graph_name = "tg_data_pT_"+str(i)
        model_result_name = "tg_model_pT_"+str(i)
        extrapolation_name = "tg_model_pT_extrapolation_"+str(i)
        extrapolation_up_name = "tg_model_pT_extrapolation_up_"+str(i)
        extrapolation_down_name = "tg_model_pT_extrapolation_down_"+str(i)
        axs[2,i].errorbar(f.Get(graph_name).GetX(), f.Get(graph_name).GetY(), f.Get(graph_name).GetEY(), marker="o", linestyle="",color='black')
        axs[2,i].plot(f.Get(extrapolation_name).GetX(), f.Get(extrapolation_name).GetY(),"b-")
        axs[2,i].fill_between(f.Get(extrapolation_name).GetX(), f.Get(extrapolation_down_name).GetY(), f.Get(extrapolation_up_name).GetY(),
                              alpha=0.4, edgecolor='blue', facecolor='blue')
        
        graph_name = "tg_data_Rm_"+str(i)
        model_result_name = "tg_model_Rm_"+str(i)
        extrapolation_name = "tg_model_Rm_extrapolation_"+str(i)
        extrapolation_up_name = "tg_model_Rm_extrapolation_up_"+str(i)
        extrapolation_down_name = "tg_model_Rm_extrapolation_down_"+str(i)
        axs[3,i].errorbar(f.Get(graph_name).GetX(), f.Get(graph_name).GetY(), f.Get(graph_name).GetEY(), marker="o", linestyle="", color='black')
        axs[3,i].plot(f.Get(extrapolation_name).GetX(), f.Get(extrapolation_name).GetY(),"r-")
        axs[3,i].fill_between(f.Get(extrapolation_name).GetX(), f.Get(extrapolation_down_name).GetY(), f.Get(extrapolation_up_name).GetY(),
                              alpha=0.4, edgecolor='red', facecolor='red')


    axs[3,0].text(2.7, 0.45, r'$z_\mathrm{h}=0.32$')
    axs[3,1].text(2.7, 0.45, r'$z_\mathrm{h}=0.53$')
    axs[3,2].text(2.7, 0.45, r'$z_\mathrm{h}=0.75$')
    axs[3,3].text(2.7, 0.45, r'$z_\mathrm{h}=0.94$')

    axs[0,0].set(xlabel='', ylabel=r'$\Delta \langle p_\mathrm{T}^2\rangle$ (GeV$^2$)')
    axs[1,0].set(xlabel='', ylabel='$R_\mathrm{M}$')
    axs[2,0].set(xlabel='', ylabel=r'$\Delta \langle p_\mathrm{T}^2\rangle$ (GeV$^2$)')
    axs[3,0].set(xlabel='$A^{1/3}$', ylabel='$R_\mathrm{M}$')
    axs[3,1].set(xlabel='$A^{1/3}$', ylabel='')
    axs[3,2].set(xlabel='$A^{1/3}$', ylabel='')
    axs[3,3].set(xlabel='$A^{1/3}$', ylabel='')


    fig.align_ylabels(axs[:,0])

    plt.savefig("modelplot_result.pdf")

if __name__ == "__main__":
    main()