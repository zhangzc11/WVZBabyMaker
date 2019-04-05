#include "JetModule.h"

//==============================================================================================================
//
// Jet Module
//
//==============================================================================================================

void wvzModule::JetModule::AddOutput()
{

}

void wvzModule::JetModule::FillOutput()
{

    // Loop over selected jets
    for (unsigned ijet = 0; ijet < babymaker->coreJet.index.size(); ++ijet)
    {
        int idx = babymaker->coreJet.index[ijet];
        float corr = babymaker->coreJet.corrs[ijet];
        // float shift = babymaker->coreJet.shifts[ijet];
        float current_csv_val = cms3.getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", idx);
        LV jet = cms3.pfjets_p4()[idx] * cms3.pfjets_undoJEC()[idx] * corr;

        // Check whether this jet overlaps with any of the leptons
        if (babymaker->isLeptonOverlappingWithJet(ijet))
            continue;

        // Compute dphi to determine which hemisphere the jet is at
        float dphi = RooUtil::Calc::DeltaPhi(jet, LXJ_p4);
        float dphi_SD = RooUtil::Calc::DeltaPhi(jet, LXJ_SD_p4);

        // Compute dR to determine whether the jets are inside the tagged fat-jet
        float dr_J = RooUtil::Calc::DeltaR(jet, J_p4);
        float dr_SD_J = RooUtil::Calc::DeltaR(jet, J_SD_p4);

        // The pt of the jet
        float pt = jet.pt();

        // Require pt minimum requirement of 30 GeV for safety
        if (jet.pt() > 30)
        {

            tx->pushbackToBranch<float>("j_dphis", dphi);
            tx->pushbackToBranch<float>("j_drs", dr_J);
            tx->pushbackToBranch<float>("j_SD_dphis", dphi_SD);
            tx->pushbackToBranch<float>("j_SD_drs", dr_SD_J);
            tx->pushbackToBranch<float>("j_pts", pt);

            // Increase the counter for the number of jets
            nj++;
            ht += pt;

            // Sum the "Recoil" jets
            R_p4 += jet;
            if (fabs(jet.eta()) < 2.5)
                R_cent_p4 += jet;

            if (fabs(dphi) < TMath::Pi()/2. and dr_J < 0.8)
            {
                nj_in++;
                ht_in += pt;
            }
            else if (fabs(dphi) < TMath::Pi()/2. and dr_J < 1.2)
            {
                nj_annuli++;
                ht_annuli += pt;
            }
            else if (fabs(dphi) < TMath::Pi()/2. and dr_J > 1.2)
            {
                nj_same++;
                ht_same += pt;
            }
            else
            {
                nj_away++;
                ht_away += pt;
            }

            if (fabs(dphi_SD) < TMath::Pi()/2. and dr_SD_J < 0.8)
            {
                nj_SD_in++;
                ht_SD_in += pt;
            }
            else if (fabs(dphi_SD) < TMath::Pi()/2. and dr_SD_J < 1.2)
            {
                nj_SD_annuli++;
                ht_SD_annuli += pt;
            }
            else if (fabs(dphi_SD) < TMath::Pi()/2. and dr_SD_J > 1.2)
            {
                nj_SD_same++;
                ht_SD_same += pt;
            }
            else
            {
                nj_SD_away++;
                ht_SD_away += pt;
            }

            babymaker->coreBtagSF.accumulateSF(idx, jet.pt(), jet.eta());

            // if (!isFastSim())
            //     babymaker->coreBtagSF.accumulateSF(idx, jet.pt(), jet.eta());
            // else
            //     babymaker->coreBtagSFFastSim.accumulateSF(idx, jet.pt(), jet.eta());

        }

        const double bjet_CSV_TIGHT = 0.9535;
        const double bjet_CSV_MED = 0.8484;
        const double bjet_CSV_LOOSE = 0.5426;

        // Counting N-btag jets: Require minimum of 20 GeV for increased acceptance
        if (jet.pt() > 20. and fabs(jet.eta()) < 2.4)
        {

            // Increase the counter for the number of b-jets
            if (current_csv_val >= bjet_CSV_LOOSE) nb++;
            if (current_csv_val >= bjet_CSV_MED) nbmed++;
            if (current_csv_val >= bjet_CSV_TIGHT) nbtight++;

            if (fabs(dphi) < TMath::Pi()/2. and dr_J < 0.8)
            {
                if (current_csv_val >= bjet_CSV_LOOSE) nb_in++;
                if (current_csv_val >= bjet_CSV_MED) nbmed_in++;
                if (current_csv_val >= bjet_CSV_TIGHT) nbtight_in++;
            }
            else if (fabs(dphi) < TMath::Pi()/2. and dr_J < 1.2)
            {
                if (current_csv_val >= bjet_CSV_LOOSE) nb_annuli++;
                if (current_csv_val >= bjet_CSV_MED) nbmed_annuli++;
                if (current_csv_val >= bjet_CSV_TIGHT) nbtight_annuli++;
            }
            else if (fabs(dphi) < TMath::Pi()/2. and dr_J > 1.2)
            {
                if (current_csv_val >= bjet_CSV_LOOSE) nb_same++;
                if (current_csv_val >= bjet_CSV_MED) nbmed_same++;
                if (current_csv_val >= bjet_CSV_TIGHT) nbtight_same++;
            }
            else
            {
                if (current_csv_val >= bjet_CSV_LOOSE) nb_away++;
                if (current_csv_val >= bjet_CSV_MED) nbmed_away++;
                if (current_csv_val >= bjet_CSV_TIGHT) nbtight_away++;
            }

            if (fabs(dphi_SD) < TMath::Pi()/2. and dr_SD_J < 0.8)
            {
                if (current_csv_val >= bjet_CSV_LOOSE) nb_SD_in++;
                if (current_csv_val >= bjet_CSV_MED) nbmed_SD_in++;
                if (current_csv_val >= bjet_CSV_TIGHT) nbtight_SD_in++;
            }
            else if (fabs(dphi_SD) < TMath::Pi()/2. and dr_SD_J < 1.2)
            {
                if (current_csv_val >= bjet_CSV_LOOSE) nb_SD_annuli++;
                if (current_csv_val >= bjet_CSV_MED) nbmed_SD_annuli++;
                if (current_csv_val >= bjet_CSV_TIGHT) nbtight_SD_annuli++;
            }
            else if (fabs(dphi_SD) < TMath::Pi()/2. and dr_SD_J > 1.2)
            {
                if (current_csv_val >= bjet_CSV_LOOSE) nb_SD_same++;
                if (current_csv_val >= bjet_CSV_MED) nbmed_SD_same++;
                if (current_csv_val >= bjet_CSV_TIGHT) nbtight_SD_same++;
            }
            else
            {
                if (current_csv_val >= bjet_CSV_LOOSE) nb_SD_away++;
                if (current_csv_val >= bjet_CSV_MED) nbmed_SD_away++;
                if (current_csv_val >= bjet_CSV_TIGHT) nbtight_SD_away++;
            }

        }

        // LV jet_up = jet * (1. + shift);
        // if (jet_up.pt() > 30)
        // {
        //     tx->pushbackToBranch<LV>("jets_up_p4", jet_up);
        //     tx->pushbackToBranch<float>("jets_up_pt", jet_up.pt());
        //     tx->pushbackToBranch<float>("jets_up_eta", jet_up.eta());
        //     tx->pushbackToBranch<float>("jets_up_phi", jet_up.phi());
        //     tx->pushbackToBranch<float>("jets_up_csv", current_csv_val);
        // }

        // LV jet_dn = jet * (1. - shift);
        // if (jet_dn.pt() > 30)
        // {
        //     tx->pushbackToBranch<LV>("jets_dn_p4", jet_dn);
        //     tx->pushbackToBranch<float>("jets_dn_pt", jet_dn.pt());
        //     tx->pushbackToBranch<float>("jets_dn_eta", jet_dn.eta());
        //     tx->pushbackToBranch<float>("jets_dn_phi", jet_dn.phi());
        //     tx->pushbackToBranch<float>("jets_dn_csv", current_csv_val);
        // }

    }

    tx->setBranch<int>("nj", nj);
    tx->setBranch<int>("nj_in", nj_in);
    tx->setBranch<int>("nj_annuli", nj_annuli);
    tx->setBranch<int>("nj_same", nj_same);
    tx->setBranch<int>("nj_away", nj_away);
    tx->setBranch<int>("nj_SD_in", nj_SD_in);
    tx->setBranch<int>("nj_SD_annuli", nj_SD_annuli);
    tx->setBranch<int>("nj_SD_same", nj_SD_same);
    tx->setBranch<int>("nj_SD_away", nj_SD_away);
    tx->setBranch<int>("nb", nb);
    tx->setBranch<int>("nb_in", nb_in);
    tx->setBranch<int>("nb_annuli", nb_annuli);
    tx->setBranch<int>("nb_same", nb_same);
    tx->setBranch<int>("nb_away", nb_away);
    tx->setBranch<int>("nb_SD_in", nb_SD_in);
    tx->setBranch<int>("nb_SD_annuli", nb_SD_annuli);
    tx->setBranch<int>("nb_SD_same", nb_SD_same);
    tx->setBranch<int>("nb_SD_away", nb_SD_away);
    tx->setBranch<int>("nbmed", nbmed);
    tx->setBranch<int>("nbmed_in", nbmed_in);
    tx->setBranch<int>("nbmed_annuli", nbmed_annuli);
    tx->setBranch<int>("nbmed_same", nbmed_same);
    tx->setBranch<int>("nbmed_away", nbmed_away);
    tx->setBranch<int>("nbmed_SD_in", nbmed_SD_in);
    tx->setBranch<int>("nbmed_SD_annuli", nbmed_SD_annuli);
    tx->setBranch<int>("nbmed_SD_same", nbmed_SD_same);
    tx->setBranch<int>("nbmed_SD_away", nbmed_SD_away);
    tx->setBranch<int>("nbtight", nbtight);
    tx->setBranch<int>("nbtight_in", nbtight_in);
    tx->setBranch<int>("nbtight_annuli", nbtight_annuli);
    tx->setBranch<int>("nbtight_same", nbtight_same);
    tx->setBranch<int>("nbtight_away", nbtight_away);
    tx->setBranch<int>("nbtight_SD_in", nbtight_SD_in);
    tx->setBranch<int>("nbtight_SD_annuli", nbtight_SD_annuli);
    tx->setBranch<int>("nbtight_SD_same", nbtight_SD_same);
    tx->setBranch<int>("nbtight_SD_away", nbtight_SD_away);
    tx->setBranch<float>("ht", ht);
    tx->setBranch<float>("ht_in", ht_in);
    tx->setBranch<float>("ht_annuli", ht_annuli);
    tx->setBranch<float>("ht_same", ht_same);
    tx->setBranch<float>("ht_away", ht_away);
    tx->setBranch<float>("ht_SD_in", ht_SD_in);
    tx->setBranch<float>("ht_SD_annuli", ht_SD_annuli);
    tx->setBranch<float>("ht_SD_same", ht_SD_same);
    tx->setBranch<float>("ht_SD_away", ht_SD_away);
    tx->setBranch<LV>("R_p4", R_p4);
    tx->setBranch<float>("R_pt", R_p4.pt());
    tx->setBranch<float>("R_eta", R_p4.eta());
    tx->setBranch<float>("R_phi", R_p4.phi());
    tx->setBranch<float>("R_mass", R_p4.mass());
    tx->setBranch<float>("R_energy", R_p4.energy());
    tx->setBranch<LV>("R_cent_p4", R_cent_p4);
    tx->setBranch<float>("R_cent_pt", R_cent_p4.pt());
    tx->setBranch<float>("R_cent_eta", R_cent_p4.eta());
    tx->setBranch<float>("R_cent_phi", R_cent_p4.phi());
    tx->setBranch<float>("R_cent_mass", R_cent_p4.mass());
    tx->setBranch<float>("R_cent_energy", R_cent_p4.energy());

}
