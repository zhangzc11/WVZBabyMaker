#include "GenPartModule.h"

//==============================================================================================================
//
// GenPart Module
//
//==============================================================================================================

void wvzModule::GenPartModule::AddOutput()
{
    tx->createBranch<float>("gen_ht");
    tx->createBranch<vector<LV>>("gen_V_p4");
    tx->createBranch<vector<float>>("gen_V_pt");
    tx->createBranch<vector<float>>("gen_V_eta");
    tx->createBranch<vector<float>>("gen_V_phi");
    tx->createBranch<vector<float>>("gen_V_mass");
    tx->createBranch<vector<int>>("gen_V_id");
    tx->createBranch<vector<LV>>("gen_lep_p4");
    tx->createBranch<vector<float>>("gen_lep_pt");
    tx->createBranch<vector<float>>("gen_lep_eta");
    tx->createBranch<vector<float>>("gen_lep_phi");
    tx->createBranch<vector<float>>("gen_lep_mass");
    tx->createBranch<vector<int>>("gen_lep_id");
    tx->createBranch<int>("VHchannel");
    tx->createBranch<int>("Higgschannel");
    tx->createBranch<int>("nGenTauClean");
    tx->createBranch<int>("nGenTau");
}

void wvzModule::GenPartModule::FillOutput()
{
    tx->setBranch<float>("gen_ht", babymaker->coreGenPart.gen_ht);

    bool isHtoWW = false;
    bool isWnotFromH = false;
    bool isZthere = false;

    const vector<int>& genPart_idx = babymaker->coreGenPart.genPart_idx;
    const vector<int>& genPart_pdgId = babymaker->coreGenPart.genPart_pdgId;
    const vector<int>& genPart_status = babymaker->coreGenPart.genPart_status;
    const vector<int>& genPart_motherId = babymaker->coreGenPart.genPart_motherId;
    const vector<LV>& genPart_p4 = babymaker->coreGenPart.genPart_p4;

    vector<LV> gen_V_p4;
    vector<int> gen_V_id;
    vector<LV> higgs_decay_p4;
    vector<int> higgs_decay_id;

    vector<int> tau_from_z_boson_idxs;
    vector<int> tau_from_w_boson_idxs;
    vector<int> any_tau_from_z;
    vector<int> any_tau_from_w;

    vector<int> lepton_from_boson;

    for (unsigned int i = 0; i < genPart_pdgId.size(); ++i)
    {
        // Is Tau lepton
        if (abs(genPart_pdgId[i]) == 15)
        {
            if (abs(genPart_motherId[i]) == 23 and (abs(genPart_status[i]) == 2 or abs(genPart_status[i]) == 23))
            {
                tau_from_z_boson_idxs.push_back(i);
            }
            if (abs(genPart_motherId[i]) == 23)
            {
                any_tau_from_z.push_back(i);
            }
            if (abs(genPart_motherId[i]) == 24 and (abs(genPart_status[i]) == 2 or abs(genPart_status[i]) == 23))
            {
                tau_from_w_boson_idxs.push_back(i);
            }
            if (abs(genPart_motherId[i]) == 24)
            {
                any_tau_from_w.push_back(i);
            }
        }

        // is Lepton From Boson
        if (babymaker->coreGenPart.isLeptonFromBoson(genPart_idx[i]))
            lepton_from_boson.push_back(i);

    }

    tx->setBranch<int>("nGenTauClean", tau_from_w_boson_idxs.size() + tau_from_z_boson_idxs.size());
    tx->setBranch<int>("nGenTau", any_tau_from_w.size() + any_tau_from_z.size());

    for (auto& i : lepton_from_boson)
    {
        tx->pushbackToBranch<LV>("gen_lep_p4", genPart_p4[i]);
        tx->pushbackToBranch<float>("gen_lep_pt", genPart_p4[i].pt());
        tx->pushbackToBranch<float>("gen_lep_eta", genPart_p4[i].eta());
        tx->pushbackToBranch<float>("gen_lep_phi", genPart_p4[i].phi());
        tx->pushbackToBranch<float>("gen_lep_mass", genPart_p4[i].mass());
        tx->pushbackToBranch<int>("gen_lep_id", genPart_pdgId[i]);
    }

}

