#include "FatJetModule.h"

//==============================================================================================================
//
// Fat Jet Module
//
//==============================================================================================================

void wvzModule::FatJetModule::AddOutput()
{

    tx->createBranch<vector<LV>>("J_p4");
    tx->createBranch<vector<float>>("J_pt");
    tx->createBranch<vector<float>>("J_eta");
    tx->createBranch<vector<float>>("J_phi");
    tx->createBranch<vector<float>>("J_mass");
    tx->createBranch<vector<float>>("J_energy");
    tx->createBranch<vector<float>>("J_SD_mass");
    tx->createBranch<vector<float>>("J_tau31");
    tx->createBranch<vector<float>>("J_tau32");
    tx->createBranch<vector<float>>("J_tau21");
    tx->createBranch<vector<float>>("J_tau1");
    tx->createBranch<vector<float>>("J_tau2");
    tx->createBranch<vector<float>>("J_tau3");
    tx->createBranch<vector<float>>("J_undoJEC");
    tx->createBranch<vector<float>>("J_shift");
    tx->createBranch<vector<float>>("J_deep_rawdisc_h4q");
    tx->createBranch<vector<float>>("J_deep_rawdisc_hbb");
    tx->createBranch<vector<float>>("J_deep_rawdisc_qcd");
    tx->createBranch<vector<float>>("J_deep_rawdisc_top");
    tx->createBranch<vector<float>>("J_deep_rawdisc_w");
    tx->createBranch<vector<float>>("J_deep_rawdisc_z");
    tx->createBranch<vector<float>>("J_deep_rawdisc_zbb");
    tx->createBranch<vector<float>>("J_softdropPuppiSubjet1_pt");
    tx->createBranch<vector<float>>("J_softdropPuppiSubjet1_eta");
    tx->createBranch<vector<float>>("J_softdropPuppiSubjet1_phi");
    tx->createBranch<vector<float>>("J_softdropPuppiSubjet1_mass");
    tx->createBranch<vector<float>>("J_softdropPuppiSubjet1_energy");
    tx->createBranch<vector<float>>("J_softdropPuppiSubjet2_pt");
    tx->createBranch<vector<float>>("J_softdropPuppiSubjet2_eta");
    tx->createBranch<vector<float>>("J_softdropPuppiSubjet2_phi");
    tx->createBranch<vector<float>>("J_softdropPuppiSubjet2_mass");
    tx->createBranch<vector<float>>("J_softdropPuppiSubjet2_energy");

}

void wvzModule::FatJetModule::FillOutput()
{

    // Find the jet for V boson
    // If there are only two ak8jets, one must be the higgs, and the other is the V
    // So use J_p4 vector to anchor the one ak8jet to higgs, and pick the other as V

    // Loop over the jets and find the leading jet on the away side hemisphere
    for (unsigned ijet = 0; ijet < babymaker->coreFatJet.index.size(); ++ijet)
    {
        // int idx = babymaker->coreFatJet.index[ijet];
        // float corr = babymaker->coreFatJet.corrs[ijet];
        // float shift = babymaker->coreFatJet.shifts[ijet];
        // LV fatjet = cms3.ak8jets_p4()[idx] * cms3.ak8jets_undoJEC()[idx] * corr;

        pushbackFatJet(ijet);

    }

}

void wvzModule::FatJetModule::pushbackFatJet(int ijet)
{

    int idx = babymaker->coreFatJet.index[ijet];
    float corr = babymaker->coreFatJet.corrs[ijet];
    float shift = babymaker->coreFatJet.shifts[ijet];
    LV fatjet = cms3.ak8jets_p4()[idx] * cms3.ak8jets_undoJEC()[idx] * corr;

    tx->pushbackToBranch<LV>("J_p4", fatjet);
    tx->pushbackToBranch<float>("J_pt", fatjet.pt());
    tx->pushbackToBranch<float>("J_eta", fatjet.eta());
    tx->pushbackToBranch<float>("J_phi", fatjet.phi());
    tx->pushbackToBranch<float>("J_mass", fatjet.mass());
    tx->pushbackToBranch<float>("J_energy", fatjet.energy());
    tx->pushbackToBranch<float>("J_SD_mass", cms3.ak8jets_softdropMass()[idx]);
    tx->pushbackToBranch<float>("J_tau31", cms3.ak8jets_nJettinessTau3()[idx] / cms3.ak8jets_nJettinessTau1()[idx]);
    tx->pushbackToBranch<float>("J_tau32", cms3.ak8jets_nJettinessTau3()[idx] / cms3.ak8jets_nJettinessTau2()[idx]);
    tx->pushbackToBranch<float>("J_tau21", cms3.ak8jets_nJettinessTau2()[idx] / cms3.ak8jets_nJettinessTau1()[idx]);
    tx->pushbackToBranch<float>("J_tau1", cms3.ak8jets_nJettinessTau1()[idx]);
    tx->pushbackToBranch<float>("J_tau2", cms3.ak8jets_nJettinessTau2()[idx]);
    tx->pushbackToBranch<float>("J_tau3", cms3.ak8jets_nJettinessTau3()[idx]);
    tx->pushbackToBranch<float>("J_undoJEC", 1. / corr);
    tx->pushbackToBranch<float>("J_shift", shift);
    tx->pushbackToBranch<float>("J_deep_rawdisc_h4q", cms3.ak8jets_deep_rawdisc_h4q()[idx]);
    tx->pushbackToBranch<float>("J_deep_rawdisc_hbb", cms3.ak8jets_deep_rawdisc_hbb()[idx]);
    tx->pushbackToBranch<float>("J_deep_rawdisc_qcd", cms3.ak8jets_deep_rawdisc_qcd()[idx]);
    tx->pushbackToBranch<float>("J_deep_rawdisc_top", cms3.ak8jets_deep_rawdisc_top()[idx]);
    tx->pushbackToBranch<float>("J_deep_rawdisc_w", cms3.ak8jets_deep_rawdisc_w()[idx]);
    tx->pushbackToBranch<float>("J_deep_rawdisc_z", cms3.ak8jets_deep_rawdisc_z()[idx]);
    tx->pushbackToBranch<float>("J_deep_rawdisc_zbb", cms3.ak8jets_deep_rawdisc_zbb()[idx]);
    tx->pushbackToBranch<float>("J_softdropPuppiSubjet1_pt", cms3.ak8jets_softdropPuppiSubjet1()[idx].pt());
    tx->pushbackToBranch<float>("J_softdropPuppiSubjet1_eta", cms3.ak8jets_softdropPuppiSubjet1()[idx].eta());
    tx->pushbackToBranch<float>("J_softdropPuppiSubjet1_phi", cms3.ak8jets_softdropPuppiSubjet1()[idx].phi());
    tx->pushbackToBranch<float>("J_softdropPuppiSubjet1_mass", cms3.ak8jets_softdropPuppiSubjet1()[idx].mass());
    tx->pushbackToBranch<float>("J_softdropPuppiSubjet1_energy", cms3.ak8jets_softdropPuppiSubjet1()[idx].energy());
    tx->pushbackToBranch<float>("J_softdropPuppiSubjet2_pt", cms3.ak8jets_softdropPuppiSubjet2()[idx].pt());
    tx->pushbackToBranch<float>("J_softdropPuppiSubjet2_eta", cms3.ak8jets_softdropPuppiSubjet2()[idx].eta());
    tx->pushbackToBranch<float>("J_softdropPuppiSubjet2_phi", cms3.ak8jets_softdropPuppiSubjet2()[idx].phi());
    tx->pushbackToBranch<float>("J_softdropPuppiSubjet2_mass", cms3.ak8jets_softdropPuppiSubjet2()[idx].mass());
    tx->pushbackToBranch<float>("J_softdropPuppiSubjet2_energy", cms3.ak8jets_softdropPuppiSubjet2()[idx].energy());

}

