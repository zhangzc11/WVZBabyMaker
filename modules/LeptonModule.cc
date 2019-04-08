#include "LeptonModule.h"

//==============================================================================================================
//
// Lepton Module
//
//==============================================================================================================

//##############################################################################################################
void wvzModule::LeptonModule::AddOutput()
{

    tx->createBranch<vector<LV>>("lep_p4");
    tx->createBranch<vector<float>>("lep_pt");
    tx->createBranch<vector<float>>("lep_eta");
    tx->createBranch<vector<float>>("lep_phi");
    tx->createBranch<vector<float>>("lep_energy");
    tx->createBranch<vector<float>>("lep_mva");
    tx->createBranch<vector<float>>("lep_relIso03EA");
    tx->createBranch<vector<float>>("lep_relIso03EAwLep");
    tx->createBranch<vector<float>>("lep_ip3d");
    tx->createBranch<vector<float>>("lep_sip3d");
    tx->createBranch<vector<float>>("lep_dxy");
    tx->createBranch<vector<float>>("lep_dz");
    tx->createBranch<vector<int>>("lep_mc_id");
    tx->createBranch<vector<int>>("lep_motherIdv2");
    tx->createBranch<vector<int>>("lep_idx");
    tx->createBranch<vector<int>>("lep_id");
    tx->createBranch<vector<int>>("lep_isTightPOG");
    tx->createBranch<vector<int>>("lep_isMediumPOG");

}

//##############################################################################################################
void wvzModule::LeptonModule::FillOutput()
{

    // I expect either one electron or one muon so it's ok to loop over
    for (auto& idx : babymaker->coreElectron.index)
    {
        tx->pushbackToBranch<LV>("lep_p4", cms3.els_p4()[idx]);
        tx->pushbackToBranch<float>("lep_pt", cms3.els_p4()[idx].pt());
        tx->pushbackToBranch<float>("lep_eta", cms3.els_p4()[idx].eta());
        tx->pushbackToBranch<float>("lep_phi", cms3.els_p4()[idx].phi());
        tx->pushbackToBranch<float>("lep_energy", cms3.els_p4()[idx].energy());
        if (gconf.year == 2016)
            tx->pushbackToBranch<float>("lep_mva", getMVAoutput(idx));
        if (gconf.year == 2017 or gconf.year == 2018)
            tx->pushbackToBranch<float>("lep_mva", getMVAoutput(idx, true));
        tx->pushbackToBranch<float>("lep_relIso03EA", eleRelIso03EA(idx, gconf.ea_version, false));
        tx->pushbackToBranch<float>("lep_relIso03EAwLep", eleRelIso03EA(idx, gconf.ea_version, true));
        tx->pushbackToBranch<float>("lep_ip3d", cms3.els_ip3d()[idx]);
        tx->pushbackToBranch<float>("lep_sip3d", cms3.els_ip3d()[idx] / cms3.els_ip3derr()[idx]);
        tx->pushbackToBranch<float>("lep_dxy", cms3.els_dxyPV()[idx]);
        tx->pushbackToBranch<float>("lep_dz", cms3.els_dzPV()[idx]);
        if (!cms3.evt_isRealData())
        {
            pair<int, int> motherId_genIdx = lepMotherID_v2(Lep(cms3.els_charge()[idx] * (-11), idx)); //don't forget the sign
            int mc_id = 0;
            if (isFromW        (11, idx)) mc_id =  1;
            if (isFromZ        (11, idx)) mc_id =  2;
            if (isFromB        (11, idx)) mc_id = -1;
            if (isFromC        (11, idx)) mc_id = -2;
            if (isFromLight    (11, idx)) mc_id = -3;
            if (isFromLightFake(11, idx)) mc_id = -4;
            tx->pushbackToBranch<int>("lep_motherIdv2" , motherId_genIdx.first);
            tx->pushbackToBranch<int>("lep_mc_id"      , mc_id);
        }
        else
        {
            tx->pushbackToBranch<int>("lep_motherIdv2" , 99);
            tx->pushbackToBranch<int>("lep_mc_id"      , 99);
        }
        tx->pushbackToBranch<int>("lep_idx", idx);
        tx->pushbackToBranch<int>("lep_id", cms3.els_charge()[idx]*(-11));
        tx->pushbackToBranch<int>("lep_isTightPOG", isMVAwp80NoIsofall17(idx, true));
        tx->pushbackToBranch<int>("lep_isMediumPOG", isMVAwp90NoIsofall17(idx, true));
    }

    // I expect either one electron or one muon so it's ok to loop over
    for (auto& idx : babymaker->coreMuon.index)
    {
        tx->pushbackToBranch<LV>("lep_p4", cms3.mus_p4()[idx]);
        tx->pushbackToBranch<float>("lep_pt", cms3.mus_p4()[idx].pt());
        tx->pushbackToBranch<float>("lep_eta", cms3.mus_p4()[idx].eta());
        tx->pushbackToBranch<float>("lep_phi", cms3.mus_p4()[idx].phi());
        tx->pushbackToBranch<float>("lep_energy", cms3.mus_p4()[idx].energy());
        tx->pushbackToBranch<float>("lep_mva", 999);
        tx->pushbackToBranch<float>("lep_relIso03EA", muRelIso03EA(idx, gconf.ea_version, false));
        tx->pushbackToBranch<float>("lep_relIso03EAwLep", muRelIso03EA(idx, gconf.ea_version, true));
        tx->pushbackToBranch<float>("lep_ip3d", cms3.mus_ip3d()[idx]);
        tx->pushbackToBranch<float>("lep_sip3d", cms3.mus_ip3d()[idx] / cms3.mus_ip3derr()[idx]);
        tx->pushbackToBranch<float>("lep_dxy", cms3.mus_dxyPV()[idx]);
        tx->pushbackToBranch<float>("lep_dz", cms3.mus_dzPV()[idx]);
        if (!cms3.evt_isRealData())
        {
            pair<int, int> motherId_genIdx = lepMotherID_v2(Lep(cms3.mus_charge()[idx] * (-13), idx)); //don't forget the sign
            int mc_id = 0;
            if (isFromW        (13, idx)) mc_id =  1;
            if (isFromZ        (13, idx)) mc_id =  2;
            if (isFromB        (13, idx)) mc_id = -1;
            if (isFromC        (13, idx)) mc_id = -2;
            if (isFromLight    (13, idx)) mc_id = -3;
            if (isFromLightFake(13, idx)) mc_id = -4;
            tx->pushbackToBranch<int>("lep_motherIdv2" , motherId_genIdx.first);
            tx->pushbackToBranch<int>("lep_mc_id"      , mc_id);
        }
        else
        {
            tx->pushbackToBranch<int>("lep_motherIdv2" , 99);
            tx->pushbackToBranch<int>("lep_mc_id"      , 99);
        }
        tx->pushbackToBranch<int>("lep_idx", idx);
        tx->pushbackToBranch<int>("lep_id", cms3.mus_charge()[idx]*(-13));
        tx->pushbackToBranch<int>("lep_isTightPOG", isTightMuonPOG(idx));
        tx->pushbackToBranch<int>("lep_isMediumPOG", isMediumMuonPOG(idx));
    }

}
