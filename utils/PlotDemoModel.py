import subprocess
import ROOT
from matplotlib import pyplot as plt
# plt.style.use('seaborn')
plt.rc('font', family='serif', serif='Times')
plt.rc('text', usetex=True)
plt.rc('xtick', labelsize=10)
plt.rc('ytick', labelsize=10)
plt.rc('axes', labelsize=10)
# plt.rc('text', usetex=True)

from scipy.stats import expon
import numpy as np

import itertools


def main():
    fe = ROOT.TFile.Open("DemoPlots.ExpLp.root", "READ")
    ff = ROOT.TFile.Open("DemoPlots.FixedLp.root", "READ")

    fig, axs = plt.subplots(2, 3, sharex='col',constrained_layout=True)
    width = 7.056870070568701
    height = 2.1806927789016632 * 1.5
    fig.set_size_inches(width, height)
    # fig.subplots_adjust(left=.11, bottom=.15, right=.96, top=.9)
    # fig.subplots_adjust(wspace=0, hspace=0)

    ll = [1, 3, 5, 10]
    style=itertools.cycle(["-","--","-.",":",".","h","H"])
    x = np.linspace(0.05, 12.9, 100)
    for lc in ll:
        current_style = style.next()
        ## Probability distribution
        lambdaL = 1.0 / (1.0*lc)
        axs[0,0].plot(x, lambdaL*np.exp(-lambdaL * x), current_style, label='$L_\mathrm{c} = '+str(lc)+'$ (fm)')
        axs[1,0].plot((lc,lc),(0,1), current_style, label='$L_\mathrm{c} = '+str(lc)+'$ (fm)')
        ## pT-broadening
        graph_name = "pT2_lp_"+str(lc)
        axs[0, 1].plot(fe.Get(graph_name).GetX(), fe.Get(graph_name).GetY(), current_style, label='$L_\mathrm{c} = '+str(lc)+'$ (fm)')
        axs[1, 1].plot(ff.Get(graph_name).GetX(), ff.Get(graph_name).GetY(), current_style, label='$L_\mathrm{c} = '+str(lc)+'$ (fm)')
        ## Multiplicity ratio
        graph_name = "RM_lp_"+str(lc)
        axs[0, 2].plot(fe.Get(graph_name).GetX(), fe.Get(graph_name).GetY(), current_style, label='$L_\mathrm{c} = '+str(lc)+'$ (fm)')
        axs[1, 2].plot(ff.Get(graph_name).GetX(), ff.Get(graph_name).GetY(), current_style, label='$L_\mathrm{c} = '+str(lc)+'$ (fm)')
   
    axs[0,0].set(xlabel='', ylabel=r'$f_\mathrm{p} (L; L_\mathrm{c})$')
    axs[1,0].set(xlabel=r'$L$ (fm)', ylabel=r'$f_\mathrm{p} (L; L_\mathrm{c})$')
    axs[0,1].set(xlabel='', ylabel=r'$\Delta \langle p_\mathrm{T}^2\rangle$ (GeV$^2$)')
    axs[1,1].set(xlabel='$A^{1/3}$', ylabel=r'$\Delta \langle p_\mathrm{T}^2\rangle$ (GeV$^2$)')
    axs[0,2].set(xlabel='', ylabel='$R_\mathrm{M}$')
    axs[1,2].set(xlabel='$A^{1/3}$', ylabel='$R_\mathrm{M}$')

    axs[0,0].set_ylim(0,1)
    axs[1,0].set_ylim(0,1)
    axs[0,1].set_ylim(0.001,0.026)
    axs[1,1].set_ylim(0.001,0.026)
    axs[0,2].set_ylim(0.1,1.1)
    axs[1,2].set_ylim(0.1,1.1)

    axs[0,1].set_xlim(2.5, 5.5)
    axs[0,2].set_xlim(2.5, 5.5)
    axs[1,1].set_xlim(2.5, 5.5)
    axs[1,2].set_xlim(2.5, 5.5)

# if (A == (int) 20.1797)  {return 2.77966;}
# if (A == (int) 83.7980)  {return 4.73264;}
# if (A == (int) 131.293)  {return 5.54713;}


    axs[0,0].annotate('Ne', xy=(1.1 * 20.1797**(1./3.), 0.151),  xycoords='data', xytext=(10,60), textcoords='offset points',
            arrowprops=dict(arrowstyle="->",connectionstyle="angle,angleA=0,angleB=90,rad=10")
            )
    axs[0,0].annotate('Kr', xy=(1.1 * 83.7980**(1./3.), 0.151),  xycoords='data', xytext=(10,40), textcoords='offset points',
            arrowprops=dict(arrowstyle="->",connectionstyle="angle,angleA=0,angleB=90,rad=10")
            )
    axs[0,0].annotate('Xe', xy=(1.1 * 131.293**(1./3.), 0.151),  xycoords='data', xytext=(10,20), textcoords='offset points',
            arrowprops=dict(arrowstyle="->",connectionstyle="angle,angleA=0,angleB=90,rad=10")
            )

    # axs[0,0].set_xscale('log')
    # axs[1,0].set_xscale('log')

    # plt.axis(aspect='equal')
    # plt.xlabel('$A^{1/3}$ (fm)')
    # plt.ylabel('$\Delta p_\mathrm{T}^2$')
    # axs[0,0].legend()
    axs[0,1].legend(frameon=False,
                    loc='upper left', borderaxespad=0.)
    # fig.tight_layout()
    output_file_name = "/Users/lopez/Dropbox/Paper-Color-Lifetime copy/Figures2020/Fig02_Predictions.pdf"
    # output_file_name = "Fig02_Predictions.pdf"
    plt.savefig(output_file_name)
    subprocess.call(["open", output_file_name])    

if __name__ == '__main__':
    main()
