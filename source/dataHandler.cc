#include "dataHandler.h"

#define DIM 4 // This should be defined somewhere else

myResult::myResult() {
    m_name = "default result";
    // set dummy values
    float dummy = -99.0;
    m_zbin         = dummy;
    m_qhat         = dummy;
    m_lp           = dummy;
    m_sigma_ph     = dummy;
    m_dz           = dummy;
    m_qhat_err     = dummy;
    m_lp_err       = dummy;
    m_sigma_ph_err = dummy;
    m_dz_err       = dummy;
    m_log          = dummy;
    m_log_err      = dummy;
    m_cascade      = dummy;
    m_cascade_err  = dummy;
    m_chi2         = dummy;
    std::cout << "myResult:: Result created for " << m_name << std::endl;
}

myResult::~myResult() {
    std::cout << "myResult:: Result destructed for " << m_name << std::endl;
}

myData::myData(std::string name) {
    m_name = name;
    m_value.clear();
    m_stat.clear();
    m_syst.clear();
    m_err.clear();
    m_value_corrected.clear();
    m_stat_corrected.clear();
    m_syst_corrected.clear();
    m_err_corrected.clear();
    for (int i=0; i<=DIM; ++i) { // Initialize vectors
        m_value.push_back(0.0);
        m_stat.push_back(0.0);
        m_syst.push_back(0.0);
        m_err.push_back(0.0);
        m_value_corrected.push_back(0.0);
        m_stat_corrected.push_back(0.0);
        m_syst_corrected.push_back(0.0);
        m_err_corrected.push_back(0.0);
    }
    std::cout << "myData:: Data created for " << m_name << std::endl;
}

myData::~myData() {
 std::cout << "myData:: Data destructed for " << m_name << std::endl; 
}

void myData::fill(int i, double val, double stat, double syst) {
    m_value[i] = val;
    m_stat[i] = stat;
    m_syst[i] = syst;
    m_err[i] = stat+syst;
}

/*
    This is the most important part, mixes the errors
    Note that for Z=X-Y, then
    s2 = s_1^2+s_2^2 - 2*rho*s_1*s_2
*/

void myData::applyCorrection(myData* nucl, double rho) { // nucl is the bkg
    for (int i=0; i<=DIM; ++i) {
        m_value_corrected[i] = m_value[i] - nucl->m_value[i];
        // testing January 3, 2018
        // if (m_value_corrected[i] < 0) {
        //     m_value_corrected[i] = 0;
        // }
        m_stat_corrected[i] = sqrt(pow2(m_stat[i]) + pow2(nucl->m_stat[i]));
        m_syst_corrected[i] = sqrt(pow2(m_syst[i]) + pow2(nucl->m_syst[i]) + 2*rho*m_syst[i]*nucl->m_syst[i]);
        m_err_corrected[i] = sqrt(pow2(m_stat_corrected[i]) + pow2(m_syst_corrected[i]));
        // Testing uncertainties in z > 0.5
        // if (i==2|| i==3) {
        //     m_err_corrected[i] *= 0.5;
        // }
    }
}

std::string myData::name() {
    return m_name;
}

void myData::doTGraphErrors() {
    const int markerStyleCode = 20; // circle 20, box 21
    const int markerColorCode = 1; // black 1, red 2, blue 4
    const int markerSizeCode = 1;
    const int makerLineWidthCode = 2;
    const int markerColorCodeStat = 2; // red
    const int markerColorCodeSyst = 4; // blue
    const float markerAlphaCode = 1.0;
    const int fillColorCode = 4;
    const int fillStyleCode = 3144;
    m_tge.clear();
    m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value[0], &m_wbin[0], &m_stat[0]));
    m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value[0], &m_wbin[0], &m_syst[0]));
    m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value[0], &m_wbin[0], &m_err[0]));
    m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value_corrected[0], &m_wbin[0], &m_stat_corrected[0]));
    m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value_corrected[0], &m_wbin[0], &m_syst_corrected[0]));
    m_tge.push_back(new TGraphErrors(DIM, &m_zbin[0], &m_value_corrected[0], &m_wbin[0], &m_err_corrected[0]));
    m_tge[0]->SetName("gg1");
    m_tge[0]->SetTitle("Statistical Errors");
    m_tge[0]->SetFillColorAlpha(markerColorCodeStat,markerAlphaCode);
    m_tge[1]->SetName("gg2");
    m_tge[1]->SetTitle("Systematic Errors");
    m_tge[1]->SetFillColorAlpha(markerColorCodeSyst,0.1*markerAlphaCode);
    m_tge[1]->SetFillColor(fillColorCode);
    m_tge[1]->SetFillStyle(fillStyleCode);
    m_tge[2]->SetName("gg3");
    m_tge[2]->SetTitle("Total Uncertainties");
    m_tge[2]->SetMarkerColor(markerColorCode);
    m_tge[2]->SetLineWidth(makerLineWidthCode);
    m_tge[2]->SetMarkerSize(markerSizeCode);
    m_tge[2]->SetMarkerStyle(markerStyleCode);
    m_tge[3]->SetName("gg1_corrected");
    m_tge[3]->SetTitle("Statistical Errors");
    m_tge[3]->SetFillColorAlpha(markerColorCodeStat,markerAlphaCode);
    m_tge[4]->SetName("gg2_corrected");
    m_tge[4]->SetTitle("Systematic Errors");
    m_tge[4]->SetFillColorAlpha(markerColorCodeSyst,0.1*markerAlphaCode); 
    m_tge[4]->SetFillColor(fillColorCode);
    m_tge[4]->SetFillStyle(fillStyleCode);
    m_tge[5]->SetName("gg3_corrected");
    m_tge[5]->SetTitle("Total Uncertainties");
    m_tge[5]->SetMarkerColor(markerColorCode);
    m_tge[5]->SetLineWidth(makerLineWidthCode);
    m_tge[5]->SetMarkerSize(markerSizeCode);
    m_tge[5]->SetMarkerStyle(markerStyleCode);
}

std::vector<myData*> dataHandler(myConfig *config) {
    double correlation = config->m_correlation;

    /* 
    This is a function and not a method of myData becuase it reads 
    from an input file that is not well designed now, so all three nuclei are read at once.
    Of course, this should only old for HERMES analysis. For Jlab analysis all data
    should be read from TGraphErrors of pT and RM vs A^1/3 for each kinematic bin
    */

    myData *he = new myData("Helium");
    myData *ne = new myData("Neon");
    myData *kr = new myData("Kripton");
    myData *xe = new myData("Xenon");
    std::ifstream input;
    input.open(config->m_input_pt);
    if (!input.is_open()) {
        std::cout << "Check your input data file is here" << std::endl;
        std::vector<myData*> output = {};
        return output;
    }
    std::string foo, line;
    std::vector<std::string> words = {};
    double val,stat,syst;
    // Read data and fill objects
    std::getline(input,foo);
    std::getline(input,foo);
    for (int i=0; i<DIM;++i) {
        std::getline(input,line); // read line of data
        boost::split(words, line, boost::is_any_of(" "), boost::token_compress_on);
        conv2double(words,val,stat,syst);
        he->fill(i,val,stat,syst);
    }
    std::getline(input,foo); // dummy line to ignore
    for (int i=0; i<DIM;++i) {
        std::getline(input,line); // read line of data
        boost::split(words, line, boost::is_any_of(" "), boost::token_compress_on);
        conv2double(words,val,stat,syst);
        ne->fill(i,val,stat,syst);
    }
    std::getline(input,foo); // dummy line to ignore
    for (int i=0; i<DIM;++i) {
        std::getline(input,line); // read line of data
        boost::split(words, line, boost::is_any_of(" "), boost::token_compress_on);
        conv2double(words,val,stat,syst);
        kr->fill(i,val,stat,syst);
    }
    std::getline(input,foo); // dummy line to ignore
    for (int i=0; i<DIM;++i) {
        std::getline(input,line); // read line of data
        boost::split(words, line, boost::is_any_of(" "), boost::token_compress_on);
        conv2double(words,val,stat,syst);
        xe->fill(i,val,stat,syst);
    }
    input.close();
    // Apply Helium substraction
    he->applyCorrection(he,correlation);
    ne->applyCorrection(he,correlation);
    kr->applyCorrection(he,correlation);
    xe->applyCorrection(he,correlation);
    // Create TGraphErros contained in each object
    he->doTGraphErrors();
    ne->doTGraphErrors();
    kr->doTGraphErrors();
    xe->doTGraphErrors();
    // Do plots of data
    if (config->correctionPlots){
        doDataPlots(config,he,ne,kr,xe);
    }
    // Prepare output and finish
    std::vector<myData*> output;
    // output.push_back(he); // we don't need to return He.
    output.push_back(ne);
    output.push_back(kr);
    output.push_back(xe);
    // output.push_back(he);
        // **** Print values to file **** //
    if (config->writeCorrectedValues) {
        std::ofstream filevalues;
        filevalues.open("data_correct_pT2.txt", std::ios::out);
        if (filevalues.is_open()) {
            filevalues.precision(10);
            for (const auto &nucl : output) {
                filevalues << nucl->name() << "\n";
                for (int i=0; i<4; ++i) {
                    filevalues << nucl->m_zbin[i] << "\t" << nucl->m_value_corrected[i] << "\t" << nucl->m_err_corrected[i] << "\n";
                }
            }
            filevalues.close();
        }
        else {
            std::cerr << "ERROR from dataHandler, A problem ocurred when opening a file" << std::endl;
        }
    }
    std::cout << "dataHandler finished" << std::endl;
    return output;
}

bool OutputResultsToFile(const std::string model, std::vector<myResult> resultCont) {
    /*
    This function is created to simplify the main function regarding the output handling.
    It still needs some tweakign for instance reading from somewhere else the number of z-bins.
    */
    const int fNzbins = 4; // 10 for JLab and 4 for HERMES !
    double z[fNzbins], q0[fNzbins], lp[fNzbins], sigma[fNzbins], dz[fNzbins], c1[fNzbins], c2[fNzbins], cascade[fNzbins];
    double zErr[fNzbins], q0Err[fNzbins], lpErr[fNzbins], sigmaErr[fNzbins], dzErr[fNzbins], c1Err[fNzbins], c2Err[fNzbins], cascade_err[fNzbins];
    double chisquared[fNzbins];
    if (resultCont.size() != fNzbins) {
        std::cout << "I cannot produce a ROOT output file, please check the produced CSV file" << std::endl;
        return false;
    }
    std::cout << "I will produce a ROOT out file..." << std::endl;
    for (int i=0; i<fNzbins; ++i) {
        std::cout << "Fetching result container for element " << i << std::endl;
        z[i] = resultCont.at(i).m_zbin;         zErr[i] = 0;
        q0[i] = resultCont.at(i).m_qhat;        q0Err[i] = resultCont.at(i).m_qhat_err;
        lp[i] = resultCont.at(i).m_lp;          lpErr[i] = resultCont.at(i).m_lp_err;
        sigma[i] = resultCont.at(i).m_sigma_ph; sigmaErr[i] = resultCont.at(i).m_sigma_ph_err;
        dz[i] = resultCont.at(i).m_dz;          dzErr[i] = resultCont.at(i).m_dz_err;
        c1[i] = resultCont.at(i).m_c1;          c1Err[i] = resultCont.at(i).m_c1_err;
        c2[i] = resultCont.at(i).m_c2;          c2Err[i] = resultCont.at(i).m_c2_err;
        cascade[i] = resultCont.at(i).m_cascade;          cascade_err[i] = resultCont.at(i).m_cascade;
        chisquared[i] = resultCont.at(i).m_chi2;
        std::cout << "z = " << z[i] << std::endl;
    }
    std::string ffout = "OutputROOT.20191115."+model+".root";
    TFile *OutputROOT = new TFile(ffout.c_str(), "RECREATE");
    std::cout << "Output file created" << std::endl;
    OutputROOT->cd();
    std::cout << "Making plots of everything" << std::endl;
    TGraphErrors *tg_q0 = new TGraphErrors(fNzbins, z, q0, zErr, q0Err); tg_q0->SetName("tg_q0"); tg_q0->SetTitle(";#it{z};#it{q}_{0} (GeV^{2}fm^{2})");
    TGraphErrors *tg_lp = new TGraphErrors(fNzbins, z, lp, zErr, lpErr); tg_lp->SetName("tg_lp"); tg_lp->SetTitle(";#it{z};#it{L}_{p} (fm)");
    TGraphErrors *tg_sigma = new TGraphErrors(fNzbins, z, sigma, zErr, sigmaErr); tg_sigma->SetName("tg_sigma"); tg_sigma->SetTitle(";#it{z};#it{#sigma} (mbarn)");
    TGraphErrors *tg_dz = new TGraphErrors(fNzbins, z, dz, zErr, dzErr); tg_dz->SetName("tg_dz");
    TGraphErrors *tg_c1 = new TGraphErrors(fNzbins, z, c1, zErr, c1Err); tg_c1->SetName("tg_c1");
    TGraphErrors *tg_c2 = new TGraphErrors(fNzbins, z, c2, zErr, c2Err); tg_c2->SetName("tg_c2");
    TGraphErrors *tg_cascade = new TGraphErrors(fNzbins, z, cascade, zErr, cascade_err); tg_cascade->SetName("tg_cascade");
    TGraph *tg_chisquared = new TGraph(fNzbins, z, chisquared); tg_chisquared->SetName("tg_chisquared");
    std::cout << "Writing first set of plots" << std::endl;
    tg_q0->Write();
    tg_lp->Write();
    tg_sigma->Write();
    tg_dz->Write();
    tg_c1->Write();
    tg_c2->Write();
    tg_cascade->Write();
    tg_chisquared->Write();
    std::cout << "Creating model plots" << std::endl;
    TGraphErrors *tg_data_pT[fNzbins];
    TGraphErrors *tg_data_Rm[fNzbins];
    TGraphErrors *tg_model_pT[fNzbins];
    TGraphErrors *tg_model_Rm[fNzbins];
    TGraphErrors *tg_model_pT_extrapolation[fNzbins];
    TGraphErrors *tg_model_pT_extrapolation_up[fNzbins];
    TGraphErrors *tg_model_pT_extrapolation_down[fNzbins];
    TGraphErrors *tg_model_Rm_extrapolation[fNzbins];
    TGraphErrors *tg_model_Rm_extrapolation_up[fNzbins];
    TGraphErrors *tg_model_Rm_extrapolation_down[fNzbins];
    TGraph *tg_average_density[fNzbins];
    TGraph *tg_multiplicity_density[fNzbins];
    TGraph *tg_average_length[fNzbins];
    
    std::string title = ";A^{1/3};#Delta#LTp_{t}^{2}#GT";
    for (int i=0; i<fNzbins; ++i) {
        std::cout << "Creating model plots for element " << i << std::endl;
        title = ";A^{1/3};#Delta p_{t}^{2}";
        tg_data_pT[i] = &(resultCont.at(i).m_tg_data_pT); tg_data_pT[i]->SetName(Form("tg_data_pT_%d",i)); tg_data_pT[i]->SetTitle(title.c_str());
        tg_model_pT[i] = &(resultCont.at(i).m_tg_pT); tg_model_pT[i]->SetName(Form("tg_model_pT_%d",i)); tg_model_pT[i]->SetTitle(title.c_str());
        tg_model_pT_extrapolation[i] = &(resultCont.at(i).m_tg_pT_extrapolation); tg_model_pT_extrapolation[i]->SetName(Form("tg_model_pT_extrapolation_%d",i)); tg_model_pT_extrapolation[i]->SetTitle(title.c_str());
        tg_model_pT_extrapolation_up[i] = &(resultCont.at(i).m_tg_pT_extrapolation_up); tg_model_pT_extrapolation_up[i]->SetName(Form("tg_model_pT_extrapolation_up_%d",i)); tg_model_pT_extrapolation_up[i]->SetTitle(title.c_str());
        tg_model_pT_extrapolation_down[i] = &(resultCont.at(i).m_tg_pT_extrapolation_down); tg_model_pT_extrapolation_down[i]->SetName(Form("tg_model_pT_extrapolation_down_%d",i)); tg_model_pT_extrapolation_down[i]->SetTitle(title.c_str());
                    title = ";A^{1/3};R_{M}";
        tg_data_Rm[i] = &(resultCont.at(i).m_tg_data_Rm); tg_data_Rm[i]->SetName(Form("tg_data_Rm_%d",i)); tg_data_Rm[i]->SetTitle(title.c_str());
        tg_model_Rm[i] = &(resultCont.at(i).m_tg_Rm); tg_model_Rm[i]->SetName(Form("tg_model_Rm_%d",i)); tg_model_Rm[i]->SetTitle(title.c_str());
        tg_model_Rm_extrapolation[i] = &(resultCont.at(i).m_tg_Rm_extrapolation); tg_model_Rm_extrapolation[i]->SetName(Form("tg_model_Rm_extrapolation_%d",i)); tg_model_Rm_extrapolation[i]->SetTitle(title.c_str());
        tg_model_Rm_extrapolation_up[i] = &(resultCont.at(i).m_tg_Rm_extrapolation_up); tg_model_Rm_extrapolation_up[i]->SetName(Form("tg_model_Rm_extrapolation_up_%d",i)); tg_model_Rm_extrapolation_up[i]->SetTitle(title.c_str());
        tg_model_Rm_extrapolation_down[i] = &(resultCont.at(i).m_tg_Rm_extrapolation_down); tg_model_Rm_extrapolation_down[i]->SetName(Form("tg_model_Rm_extrapolation_down_%d",i)); tg_model_Rm_extrapolation_down[i]->SetTitle(title.c_str());
        title = ";A^{1/3};#LT #rho #GT";
        tg_average_density[i] = &(resultCont.at(i).m_tg_average_density); tg_average_density[i]->SetName(Form("tg_average_density_%d",i)); tg_average_density[i]->SetTitle(title.c_str());
        title = ";A^{1/3};#LT #sigma exp(-#sigma#int#rhodz) #rho(z_{0}+l) #GT";
        tg_multiplicity_density[i] = &(resultCont.at(i).m_tg_multiplicity_density); tg_multiplicity_density[i]->SetName(Form("tg_multiplicity_density_%d",i)); tg_multiplicity_density[i]->SetTitle(title.c_str());
        title = ";A^{1/3};#LT l #GT (fm)";
        tg_average_length[i] = &(resultCont.at(i).m_tg_average_length); tg_average_length[i]->SetName(Form("tg_average_length_%d",i)); tg_average_length[i]->SetTitle(title.c_str());
        tg_data_pT[i]->Write();
        tg_data_Rm[i]->Write();
        tg_model_pT[i]->Write();
        tg_model_Rm[i]->Write();
        tg_model_pT_extrapolation[i]->Write();
        tg_model_pT_extrapolation_up[i]->Write();
        tg_model_pT_extrapolation_down[i]->Write();
        tg_model_Rm_extrapolation[i]->Write();
        tg_model_Rm_extrapolation_up[i]->Write();
        tg_model_Rm_extrapolation_down[i]->Write();
        tg_average_density[i]->Write();
        tg_multiplicity_density[i]->Write();
        tg_average_length[i]->Write();
    }
    std::cout << "Done." << std::endl;
    OutputROOT->Close();
    std::cout << "Results saved to a ROOT file file: " << ffout << std::endl;
    return true;
}
