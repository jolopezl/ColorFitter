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
        m_stat_corrected[i] = sqrt(pow2(m_stat[i]) + pow2(nucl->m_stat[i]));
        m_syst_corrected[i] = sqrt(pow2(m_syst[i]) + pow2(nucl->m_syst[i]) + 2*rho*m_syst[i]*nucl->m_syst[i]);
        m_err_corrected[i] = sqrt(pow2(m_stat_corrected[i])+pow2(m_syst_corrected[i]));
    }
}

double pow2(double x) {return x*x;} // move this to somewhere else.

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

void conv2double(std::vector<std::string> words, double &val, double &stat, double &syst) {
    val  = std::stod(words.at(2));
    stat = std::stod(words.at(3));
    syst = std::stod(words.at(4));
}

std::vector<myData*> dataHandler(myConfig *config) {
    double correlation = config->m_correlation;
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