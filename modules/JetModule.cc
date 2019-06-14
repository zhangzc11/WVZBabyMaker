#include "JetModule.h"

//==============================================================================================================
//
// Jet Module
//
//==============================================================================================================

void wvzModule::JetModule::AddOutput()
{

    tx->createBranch<vector<LV>>("jets_p4");
    tx->createBranch<vector<float>>("jets_pt");
    tx->createBranch<vector<float>>("jets_eta");
    tx->createBranch<vector<float>>("jets_phi");
    tx->createBranch<vector<float>>("jets_mass");

    tx->createBranch<vector<LV>>("jets_cen_p4");
    tx->createBranch<vector<float>>("jets_cen_pt");
    tx->createBranch<vector<float>>("jets_cen_eta");
    tx->createBranch<vector<float>>("jets_cen_phi");
    tx->createBranch<vector<float>>("jets_cen_mass");

    tx->createBranch<int>("nj");
    tx->createBranch<int>("nb");
    tx->createBranch<int>("nbmed");
    tx->createBranch<float>("ht");
    tx->createBranch<int>("nj_cen");

    tx->createBranch<float>("weight_btagsf");
    tx->createBranch<float>("weight_btagsf_heavy_DN");
    tx->createBranch<float>("weight_btagsf_heavy_UP");
    tx->createBranch<float>("weight_btagsf_light_DN");
    tx->createBranch<float>("weight_btagsf_light_UP");

}

void wvzModule::JetModule::FillOutput()
{

    // Variables to compute and fill to the ttree output
    int nj = 0;
    int nj_cen = 0;
    int nb = 0;
    int nbmed = 0;
    float ht = 0;

    // Clear SF
    babymaker->coreBtagSF.clearSF();

    // Loop over selected jets
    // coreJet.index contains index to the jets in cms3.pfjets_p4() vector
    for (unsigned ijet = 0; ijet < babymaker->coreJet.index.size(); ++ijet)
    {
        // Get the index
        int idx = babymaker->coreJet.index[ijet];

        // Get the JEC correction
        float corr = babymaker->coreJet.corrs[ijet];

        if (gconf.year == 2016)
        {
            if (!isLoosePFJet_Summer16_v1(idx)) { continue; }
        }
        else if (gconf.year == 2017)
        {
            if (!isTightPFJet_2017_v1(idx)) { continue; }
        }
        else if (gconf.year == 2018)
        {
            if (!isTightPFJet_2018_v1(idx)) { continue; }
        }

        // Get the JEC shift
        // float shift = babymaker->coreJet.shifts[ijet];

        static TString deepCSV_prefix = "NULL";
        if (deepCSV_prefix == "NULL")
        {
            for (TString discName : cms3.pfjets_bDiscriminatorNames())
            {
                if (discName.Contains("pfDeepCSV"))    // 2017 convention
                {
                    deepCSV_prefix = "pfDeepCSV";
                    break;
                }
                else if (discName.Contains("deepFlavour"))    // 2016 convention
                {
                    deepCSV_prefix = "deepFlavour";
                    break;
                }
            } // end loop over b discriminator names
            if (deepCSV_prefix == "NULL")
            {
                cout << "Error:" << __FUNCTION__ << "Can't find DeepCSV discriminator names!" << endl;
                exit(1);
            }
        }

        // Get the b-tagging value
        float current_btag_score_val = -2;
        if (gconf.year == 2016)
            current_btag_score_val = cms3.getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", idx);
        else if (gconf.year == 2017 || gconf.year == 2018)
            current_btag_score_val = cms3.getbtagvalue(deepCSV_prefix + "JetTags:probb", ijet) + cms3.getbtagvalue(deepCSV_prefix + "JetTags:probbb", ijet);

        LV jet = cms3.pfjets_p4()[idx] * cms3.pfjets_undoJEC()[idx] * corr;

        // Check whether this jet overlaps with any of the leptons
        switch (babymaker->babyMode)
        {
            case wvzBabyMaker::kWVZ:
                if (babymaker->isPOGLeptonOverlappingWithJet(ijet)) continue;
                break;
            case wvzBabyMaker::kDilep:
                if (babymaker->isPOGLeptonOverlappingWithJet(ijet)) continue;
                break;
            case wvzBabyMaker::kTrilep:
                if (babymaker->isPOGLeptonOverlappingWithJet(ijet)) continue;
                break;
            case wvzBabyMaker::kWVZMVA:
                if (babymaker->isMVAPOGLeptonOverlappingWithJet(ijet)) continue;
                break;
        }

        // The pt of the jet
        float pt = jet.pt();

        // Require pt minimum requirement of 30 GeV for safety
        if (jet.pt() > 30)
        {

            // Increase the counter for the number of jets
            nj++;
            ht += pt;

            if (fabs(jet.eta()) < 2.4)
                nj_cen++;

        }

        float btag_loose_threshold = -999;
        if (gconf.year == 2016)
            btag_loose_threshold = gconf.WP_CSVv2_LOOSE;
        else if (gconf.year == 2017 or gconf.year == 2018)
            btag_loose_threshold = gconf.WP_DEEPCSV_LOOSE;

        float btag_medium_threshold = -999;
        if (gconf.year == 2016)
            btag_medium_threshold = gconf.WP_CSVv2_MEDIUM;
        else if (gconf.year == 2017 or gconf.year == 2018)
            btag_medium_threshold = gconf.WP_DEEPCSV_MEDIUM;

        // Counting N-btag jets: Require minimum of 20 GeV for increased acceptance
        if (jet.pt() > 20. and fabs(jet.eta()) < 2.4)
        {

            // Increase the counter for the number of b-jets
            if (current_btag_score_val >= btag_loose_threshold) nb++;
            if (current_btag_score_val >= btag_medium_threshold) nbmed++;

            babymaker->coreBtagSF.accumulateSF(idx, jet.pt(), jet.eta());

        }

        // Adding jets to the container
        if (jet.pt() > 20.)
        {
            tx->pushbackToBranch<LV>("jets_p4", jet);
            tx->pushbackToBranch<float>("jets_pt", jet.pt());
            tx->pushbackToBranch<float>("jets_eta", jet.eta());
            tx->pushbackToBranch<float>("jets_phi", jet.phi());
            tx->pushbackToBranch<float>("jets_mass", jet.mass());
        }

        // Adding jets to the container
        if (jet.pt() > 20.)
        {
            tx->pushbackToBranch<LV>("jets_cen_p4", jet);
            tx->pushbackToBranch<float>("jets_cen_pt", jet.pt());
            tx->pushbackToBranch<float>("jets_cen_eta", jet.eta());
            tx->pushbackToBranch<float>("jets_cen_phi", jet.phi());
            tx->pushbackToBranch<float>("jets_cen_mass", jet.mass());
        }


    } // End looping over jets

    tx->setBranch<int>("nj", nj);
    tx->setBranch<int>("nb", nb);
    tx->setBranch<int>("nbmed", nbmed);
    tx->setBranch<float>("ht", ht);
    tx->setBranch<int>("nj_cen", nj_cen);

    tx->setBranch<float>("weight_btagsf"         , babymaker->coreBtagSF.btagprob_data     / babymaker->coreBtagSF.btagprob_mc);
    tx->setBranch<float>("weight_btagsf_heavy_DN", babymaker->coreBtagSF.btagprob_heavy_DN / babymaker->coreBtagSF.btagprob_mc);
    tx->setBranch<float>("weight_btagsf_heavy_UP", babymaker->coreBtagSF.btagprob_heavy_UP / babymaker->coreBtagSF.btagprob_mc);
    tx->setBranch<float>("weight_btagsf_light_DN", babymaker->coreBtagSF.btagprob_light_DN / babymaker->coreBtagSF.btagprob_mc);
    tx->setBranch<float>("weight_btagsf_light_UP", babymaker->coreBtagSF.btagprob_light_UP / babymaker->coreBtagSF.btagprob_mc);

    tx->sortVecBranchesByPt("jets_p4",
            {
            "jets_pt",
            "jets_eta",
            "jets_phi",
            "jets_mass"
            },{},{});

    tx->sortVecBranchesByPt("jets_cen_p4",
            {
            "jets_cen_pt",
            "jets_cen_eta",
            "jets_cen_phi",
            "jets_cen_mass"
            },{},{});

}
