#include "LeptonModule.h"

//==============================================================================================================
//
// Lepton Module
//
//==============================================================================================================

//##############################################################################################################
void wvzModule::LeptonModule::AddOutput()
{

    tx->createBranch<int>("nVlep");
    tx->createBranch<int>("nNlep");
    tx->createBranch<int>("lep_ZCand_idx1");
    tx->createBranch<int>("lep_ZCand_idx2");
    tx->createBranch<int>("lep_Nom_idx1");
    tx->createBranch<int>("lep_Nom_idx2");
    tx->createBranch<int>("lep_Nom_idx3");
    tx->createBranch<int>("lep_2ndZCand_idx1");
    tx->createBranch<int>("lep_2ndZCand_idx2");
    tx->createBranch<int>("lep_WCand_idx1");

    tx->createBranch<vector<LV>>("lep_p4");
    tx->createBranch<vector<float>>("lep_pt");
    tx->createBranch<vector<float>>("lep_eta");
    tx->createBranch<vector<float>>("lep_etaSC");
    tx->createBranch<vector<float>>("lep_phi");
    tx->createBranch<vector<float>>("lep_energy");
    tx->createBranch<vector<float>>("lep_mva");
    tx->createBranch<vector<float>>("lep_mvaIso");
    tx->createBranch<vector<float>>("lep_relIso04DB");
    tx->createBranch<vector<float>>("lep_relIso03EA");
    tx->createBranch<vector<float>>("lep_relIso03EAv4");
    tx->createBranch<vector<float>>("lep_relIso03EAwLep");
    tx->createBranch<vector<float>>("lep_ip3d");
    tx->createBranch<vector<float>>("lep_sip3d");
    tx->createBranch<vector<float>>("lep_dxy");
    tx->createBranch<vector<float>>("lep_dz");
    tx->createBranch<vector<int>>("lep_mc_motherid");
    tx->createBranch<vector<int>>("lep_mc_id");
    tx->createBranch<vector<int>>("lep_motherIdv2");
    tx->createBranch<vector<int>>("lep_idx");
    tx->createBranch<vector<int>>("lep_id");
    tx->createBranch<vector<int>>("lep_isTightPOG");
    tx->createBranch<vector<int>>("lep_isMediumPOG");
    tx->createBranch<vector<int>>("lep_isMVAwp80NoIsoPOG");
    tx->createBranch<vector<int>>("lep_isMVAwp90NoIsoPOG");
    tx->createBranch<vector<int>>("lep_isMVAwpLooseNoIsoPOG");
    tx->createBranch<vector<int>>("lep_isMVAwp80IsoPOG");
    tx->createBranch<vector<int>>("lep_isMVAwp90IsoPOG");
    tx->createBranch<vector<int>>("lep_isMVAwpLooseIsoPOG");
    tx->createBranch<vector<int>>("lep_isMVAwpHZZIsoPOG");
    tx->createBranch<vector<int>>("lep_isCutBasedNoIsoVetoPOG");
    tx->createBranch<vector<int>>("lep_isCutBasedNoIsoLoosePOG");
    tx->createBranch<vector<int>>("lep_isCutBasedNoIsoMediumPOG");
    tx->createBranch<vector<int>>("lep_isCutBasedNoIsoTightPOG");
    tx->createBranch<vector<int>>("lep_isCutBasedIsoVetoPOG");
    tx->createBranch<vector<int>>("lep_isCutBasedIsoLoosePOG");
    tx->createBranch<vector<int>>("lep_isCutBasedIsoMediumPOG");
    tx->createBranch<vector<int>>("lep_isCutBasedIsoTightPOG");

}

//##############################################################################################################
void wvzModule::LeptonModule::FillOutput()
{

    // Counting number of veto leptons
    int nVlep = 0;

    // I expect either one electron or one muon so it's ok to loop over
    for (auto& idx : babymaker->coreElectron.index)
    {
        tx->pushbackToBranch<LV>("lep_p4", cms3.els_p4()[idx]);
        tx->pushbackToBranch<float>("lep_pt", cms3.els_p4()[idx].pt());
        tx->pushbackToBranch<float>("lep_eta", cms3.els_p4()[idx].eta());
        tx->pushbackToBranch<float>("lep_etaSC", cms3.els_etaSC()[idx]);
        tx->pushbackToBranch<float>("lep_phi", cms3.els_p4()[idx].phi());
        tx->pushbackToBranch<float>("lep_energy", cms3.els_p4()[idx].energy());
        tx->pushbackToBranch<float>("lep_mva", cms3.els_VIDFall17V2NoIsoMvaValue().at(idx));
        tx->pushbackToBranch<float>("lep_mvaIso", cms3.els_VIDFall17V2IsoMvaValue().at(idx));
        tx->pushbackToBranch<float>("lep_relIso04DB", -999);
        tx->pushbackToBranch<float>("lep_relIso03EA", eleRelIso03EA(idx, gconf.ea_version, false));
        tx->pushbackToBranch<float>("lep_relIso03EAv4", eleRelIso03EA(idx, 4, false));
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
            if (isFromTau      (11, idx)) mc_id =  3;
            if (isFromB        (11, idx)) mc_id = -1;
            if (isFromC        (11, idx)) mc_id = -2;
            if (isFromLight    (11, idx)) mc_id = -3;
            if (isFromLightFake(11, idx)) mc_id = -4;
            tx->pushbackToBranch<int>("lep_motherIdv2" , motherId_genIdx.first);
            tx->pushbackToBranch<int>("lep_mc_id"      , mc_id);
            tx->pushbackToBranch<int>("lep_mc_motherid", cms3.els_mc_motherid()[idx]);
        }
        else
        {
            tx->pushbackToBranch<int>("lep_motherIdv2" , 99);
            tx->pushbackToBranch<int>("lep_mc_id"      , 99);
            tx->pushbackToBranch<int>("lep_mc_motherid", 99);
        }
        tx->pushbackToBranch<int>("lep_idx", idx);
        tx->pushbackToBranch<int>("lep_id", cms3.els_charge()[idx]*(-11));
        tx->pushbackToBranch<int>("lep_isTightPOG", isMVAwp80NoIsofall17V2(idx, true));
        tx->pushbackToBranch<int>("lep_isMediumPOG", isMVAwp90NoIsofall17V2(idx, true));
        tx->pushbackToBranch<int>("lep_isMVAwp80NoIsoPOG"    , isMVAwp80NoIsofall17V2(idx));
        tx->pushbackToBranch<int>("lep_isMVAwp90NoIsoPOG"    , isMVAwp90NoIsofall17V2(idx));
        tx->pushbackToBranch<int>("lep_isMVAwpLooseNoIsoPOG" , isMVAwpLooseNoIsofall17V2(idx));
        tx->pushbackToBranch<int>("lep_isMVAwp80IsoPOG"      , isMVAwp80Isofall17V2(idx));
        tx->pushbackToBranch<int>("lep_isMVAwp90IsoPOG"      , isMVAwp90Isofall17V2(idx));
        tx->pushbackToBranch<int>("lep_isMVAwpLooseIsoPOG"   , isMVAwpLooseIsofall17V2(idx));
        tx->pushbackToBranch<int>("lep_isMVAwpHZZIsoPOG"     , isMVAHZZIsofall17V2(idx));
        tx->pushbackToBranch<int>("lep_isCutBasedNoIsoVetoPOG"  , isVetoElectronPOGfall17noIso_v2(idx) );
        tx->pushbackToBranch<int>("lep_isCutBasedNoIsoLoosePOG" , isLooseElectronPOGfall17noIso_v2(idx) );
        tx->pushbackToBranch<int>("lep_isCutBasedNoIsoMediumPOG", isMediumElectronPOGfall17noIso_v2(idx) );
        tx->pushbackToBranch<int>("lep_isCutBasedNoIsoTightPOG" , isTightElectronPOGfall17noIso_v2(idx) );
        tx->pushbackToBranch<int>("lep_isCutBasedIsoVetoPOG"    , isVetoElectronPOGfall17_v2(idx) );
        tx->pushbackToBranch<int>("lep_isCutBasedIsoLoosePOG"   , isLooseElectronPOGfall17_v2(idx) );
        tx->pushbackToBranch<int>("lep_isCutBasedIsoMediumPOG"  , isMediumElectronPOGfall17_v2(idx) );
        tx->pushbackToBranch<int>("lep_isCutBasedIsoTightPOG"   , isTightElectronPOGfall17_v2(idx) );

        if (babymaker->isPt10AnalysisVetoElectron(idx))
            nVlep++;

    }

    // I expect either one electron or one muon so it's ok to loop over
    for (auto& idx : babymaker->coreMuon.index)
    {
        tx->pushbackToBranch<LV>("lep_p4", cms3.mus_p4()[idx]);
        tx->pushbackToBranch<float>("lep_pt", cms3.mus_p4()[idx].pt());
        tx->pushbackToBranch<float>("lep_eta", cms3.mus_p4()[idx].eta());
        tx->pushbackToBranch<float>("lep_etaSC", -999);
        tx->pushbackToBranch<float>("lep_phi", cms3.mus_p4()[idx].phi());
        tx->pushbackToBranch<float>("lep_energy", cms3.mus_p4()[idx].energy());
        tx->pushbackToBranch<float>("lep_mva", 999);
        tx->pushbackToBranch<float>("lep_mvaIso", 999);
        tx->pushbackToBranch<float>("lep_relIso04DB", muRelIso04DB(idx));
        tx->pushbackToBranch<float>("lep_relIso03EA", muRelIso03EA(idx, gconf.ea_version, false));
        tx->pushbackToBranch<float>("lep_relIso03EAv4", muRelIso03EA(idx, 4, false));
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
            if (isFromTau      (13, idx)) mc_id =  3;
            if (isFromB        (13, idx)) mc_id = -1;
            if (isFromC        (13, idx)) mc_id = -2;
            if (isFromLight    (13, idx)) mc_id = -3;
            if (isFromLightFake(13, idx)) mc_id = -4;
            tx->pushbackToBranch<int>("lep_motherIdv2" , motherId_genIdx.first);
            tx->pushbackToBranch<int>("lep_mc_id"      , mc_id);
            tx->pushbackToBranch<int>("lep_mc_motherid", cms3.mus_mc_motherid()[idx]);
        }
        else
        {
            tx->pushbackToBranch<int>("lep_motherIdv2" , 99);
            tx->pushbackToBranch<int>("lep_mc_id"      , 99);
            tx->pushbackToBranch<int>("lep_mc_motherid", 99);
        }
        tx->pushbackToBranch<int>("lep_idx", idx);
        tx->pushbackToBranch<int>("lep_id", cms3.mus_charge()[idx]*(-13));
        tx->pushbackToBranch<int>("lep_isTightPOG", isTightMuonPOG(idx));
        tx->pushbackToBranch<int>("lep_isMediumPOG", isMediumMuonPOG(idx));
        tx->pushbackToBranch<int>("lep_isMVAwp80NoIsoPOG"       , true);
        tx->pushbackToBranch<int>("lep_isMVAwp90NoIsoPOG"       , true);
        tx->pushbackToBranch<int>("lep_isMVAwpLooseNoIsoPOG"    , true);
        tx->pushbackToBranch<int>("lep_isMVAwp80IsoPOG"         , true);
        tx->pushbackToBranch<int>("lep_isMVAwp90IsoPOG"         , true);
        tx->pushbackToBranch<int>("lep_isMVAwpLooseIsoPOG"      , true);
        tx->pushbackToBranch<int>("lep_isMVAwpHZZIsoPOG"        , true);
        tx->pushbackToBranch<int>("lep_isCutBasedNoIsoVetoPOG"  , true);
        tx->pushbackToBranch<int>("lep_isCutBasedNoIsoLoosePOG" , true);
        tx->pushbackToBranch<int>("lep_isCutBasedNoIsoMediumPOG", true);
        tx->pushbackToBranch<int>("lep_isCutBasedNoIsoTightPOG" , true);
        tx->pushbackToBranch<int>("lep_isCutBasedIsoVetoPOG"    , true);
        tx->pushbackToBranch<int>("lep_isCutBasedIsoLoosePOG"   , true);
        tx->pushbackToBranch<int>("lep_isCutBasedIsoMediumPOG"  , true);
        tx->pushbackToBranch<int>("lep_isCutBasedIsoTightPOG"   , true);

        if (babymaker->isPt10AnalysisVetoMuon(idx))
            nVlep++;

    }

    tx->sortVecBranchesByPt("lep_p4",
            {
            "lep_pt",
            "lep_eta",
            "lep_etaSC",
            "lep_phi",
            "lep_energy",
            "lep_mva",
            "lep_mvaIso",
            "lep_relIso04DB",
            "lep_relIso03EA",
            "lep_relIso03EAv4",
            "lep_relIso03EAwLep",
            "lep_ip3d",
            "lep_sip3d",
            "lep_dxy",
            "lep_dz",
            },
            {
            "lep_mc_motherid",
            "lep_mc_id",
            "lep_motherIdv2",
            "lep_idx",
            "lep_id",
            "lep_isTightPOG",
            "lep_isMediumPOG",
            "lep_isMVAwp80NoIsoPOG",
            "lep_isMVAwp90NoIsoPOG",
            "lep_isMVAwpLooseNoIsoPOG",
            "lep_isMVAwp80IsoPOG",
            "lep_isMVAwp90IsoPOG",
            "lep_isMVAwpLooseIsoPOG",
            "lep_isMVAwpHZZIsoPOG",
            "lep_isCutBasedNoIsoVetoPOG",
            "lep_isCutBasedNoIsoLoosePOG",
            "lep_isCutBasedNoIsoMediumPOG",
            "lep_isCutBasedNoIsoTightPOG",
            "lep_isCutBasedIsoVetoPOG",
            "lep_isCutBasedIsoLoosePOG",
            "lep_isCutBasedIsoMediumPOG",
            "lep_isCutBasedIsoTightPOG"
            },
            {});

    tx->setBranch<int>("nVlep", nVlep);

    if (nVlep >= 3)
    {

        //===========================================================
        // Finding Z candidates
        //===========================================================

        int lep_ZCand_idx1 = -999;
        int lep_ZCand_idx2 = -999;
        const vector<LV>& lep_p4 = tx->getBranch<vector<LV>>("lep_p4");
        const vector<float>& lep_pt = tx->getBranch<vector<float>>("lep_pt");
        const vector<int>& lep_id = tx->getBranch<vector<int>>("lep_id");
        const vector<int>& lep_idx = tx->getBranch<vector<int>>("lep_idx");

        double compare = 10; // Min value of |Mll - MZ|

        // Loop over the leptons and find the Z boson pair
        for (unsigned int jj = 0; jj < (lep_p4.size() - 1); jj++)
        {

            int id1 = lep_id.at(jj);
            if (abs(id1) == 11)
            {
                if (not babymaker->isPt10AnalysisVetoElectron(lep_idx.at(jj)))
                    continue;
            }
            else if (abs(id1) == 13)
            {
                if (not babymaker->isPt10AnalysisVetoMuon(lep_idx.at(jj)))
                    continue;
            }
            else
            {
                continue;
            }

            for (unsigned int kk = jj + 1; kk < lep_p4.size(); kk++)
            {

                int id2 = lep_id.at(kk);
                if (abs(id2) == 11)
                {
                    if (not babymaker->isPt10AnalysisVetoElectron(lep_idx.at(kk)))
                        continue;
                }
                else if (abs(id2) == 13)
                {
                    if (not babymaker->isPt10AnalysisVetoMuon(lep_idx.at(kk)))
                        continue;
                }
                else
                {
                    continue;
                }

                LV dilepZCand = lep_p4.at(jj) + lep_p4.at(kk);
                bool ifpass = true;
                if (fabs(dilepZCand.M() - 91.1875) > 10)  ifpass = false; // within Z mass window
                if (abs(id1) != abs(id2)) ifpass = false; // same-flavor
                if (id1 == id2)  ifpass = false; // opposite-sign
                if (ifpass && fabs(dilepZCand.M() - 91.1875) > compare) ifpass = false; // if bigger than previous
                if (ifpass)
                {
                    compare = fabs(dilepZCand.M() - 91.1876);
                    lep_ZCand_idx1 = jj;
                    lep_ZCand_idx2 = kk;
                }
            }
        }

        tx->setBranch<int>("lep_ZCand_idx1", lep_ZCand_idx1);
        tx->setBranch<int>("lep_ZCand_idx2", lep_ZCand_idx2);

        //===========================================================
        // Finding "Nominal leptons" (if lep_ZCand_idx1 is found)
        //===========================================================

        if (lep_ZCand_idx1 >= 0 and lep_ZCand_idx2 >= 0)
        {

            // The nominal leptons are the leptons that are not tagged as Z

            // reset
            int nNlep = -999;
            int lep_Nom_idx1 = -999;
            int lep_Nom_idx2 = -999;
            int lep_Nom_idx3 = -999;
            vector<int> lep_nom_idxs;

            // Loop over the leptons
            for (unsigned int jj = 0 ; jj < lep_pt.size(); jj++)
            {

                if (jj == (unsigned int) lep_ZCand_idx1)
                    continue;

                if (jj == (unsigned int) lep_ZCand_idx2)
                    continue;

                int id = lep_id.at(jj);

                if (abs(id) == 11)
                {
                    if (not babymaker->isPt10AnalysisNominalElectron(lep_idx.at(jj)))
                        continue;
                }
                else if (abs(id) == 13)
                {
                    if (not babymaker->isPt10AnalysisNominalMuon(lep_idx.at(jj)))
                        continue;
                }
                else
                {
                    continue;
                }

                lep_nom_idxs.push_back(jj);

            }

            nNlep = lep_nom_idxs.size(); // # of good nominal leptons
            if (nNlep > 0) lep_Nom_idx1 = lep_nom_idxs.at(0);
            if (nNlep > 1) lep_Nom_idx2 = lep_nom_idxs.at(1);
            if (nNlep > 2) lep_Nom_idx3 = lep_nom_idxs.at(2);

            tx->setBranch<int>("nNlep", nNlep);
            tx->setBranch<int>("lep_Nom_idx1", lep_Nom_idx1);
            tx->setBranch<int>("lep_Nom_idx2", lep_Nom_idx2);
            tx->setBranch<int>("lep_Nom_idx3", lep_Nom_idx3);

            //===========================================================
            // Finding "2nd Z candidate"
            //===========================================================

            // These are the variables to set
            int lep_2ndZCand_idx1 = -999;
            int lep_2ndZCand_idx2 = -999;
            int lep_WCand_idx1 = -999;

            std::vector<int> good_veto_idx; // index of good nominal leptons

            // Loop over the leptons
            for (unsigned int jj = 0 ; jj < lep_pt.size(); jj++)
            {

                if (jj == (unsigned int) lep_ZCand_idx1)
                    continue;

                if (jj == (unsigned int) lep_ZCand_idx2)
                    continue;

                int id = lep_id.at(jj);
                if (abs(id) == 11)
                {
                    if (not babymaker->isPt10AnalysisVetoElectron(lep_idx.at(jj)))
                        continue;
                }
                else if (abs(id) == 13)
                {
                    if (not babymaker->isPt10AnalysisVetoMuon(lep_idx.at(jj)))
                        continue;
                }
                else
                {
                    continue;
                }

                good_veto_idx.push_back(jj);

            }

            // At this point we must only find 5 total
            if (good_veto_idx.size() == 3)
            {

                int lep_veto_idx1 = good_veto_idx.at(0);
                int lep_veto_idx2 = good_veto_idx.at(1);
                int lep_veto_idx3 = good_veto_idx.at(2);

                // Assumes lep_Nom_idx1,2,3 are set
                double dM12 = fabs((lep_p4.at(lep_veto_idx1) + lep_p4.at(lep_veto_idx2)).M() - 91.1876);
                double dM13 = fabs((lep_p4.at(lep_veto_idx1) + lep_p4.at(lep_veto_idx3)).M() - 91.1876);
                double dM23 = fabs((lep_p4.at(lep_veto_idx2) + lep_p4.at(lep_veto_idx3)).M() - 91.1876);
                double mindM = std::min(dM12, std::min(dM13, dM23));
                if (mindM == dM12)
                {
                    lep_2ndZCand_idx1 = lep_pt.at(lep_veto_idx1) > lep_pt.at(lep_veto_idx2) ? lep_veto_idx1 : lep_veto_idx2;
                    lep_2ndZCand_idx2 = lep_pt.at(lep_veto_idx1) > lep_pt.at(lep_veto_idx2) ? lep_veto_idx2 : lep_veto_idx1;
                    lep_WCand_idx1 = lep_veto_idx3;
                }
                else if (mindM == dM13)
                {
                    lep_2ndZCand_idx1 = lep_pt.at(lep_veto_idx1) > lep_pt.at(lep_veto_idx3) ? lep_veto_idx1 : lep_veto_idx3;
                    lep_2ndZCand_idx2 = lep_pt.at(lep_veto_idx1) > lep_pt.at(lep_veto_idx3) ? lep_veto_idx3 : lep_veto_idx1;
                    lep_WCand_idx1 = lep_veto_idx2;
                }
                else if (mindM == dM23)
                {
                    lep_2ndZCand_idx1 = lep_pt.at(lep_veto_idx2) > lep_pt.at(lep_veto_idx3) ? lep_veto_idx2 : lep_veto_idx3;
                    lep_2ndZCand_idx2 = lep_pt.at(lep_veto_idx2) > lep_pt.at(lep_veto_idx3) ? lep_veto_idx3 : lep_veto_idx2;
                    lep_WCand_idx1 = lep_veto_idx1;
                }
                else
                {
                    RooUtil::error("I should not be here!", "select2ndZCandAndWCandLeptons");
                }

                tx->setBranch<int>("lep_2ndZCand_idx1", lep_2ndZCand_idx1);
                tx->setBranch<int>("lep_2ndZCand_idx2", lep_2ndZCand_idx2);
                tx->setBranch<int>("lep_WCand_idx1", lep_WCand_idx1);

            }

        }

    }

}

