#include "BDTModule.h"
#include "xgboost/wwz_vs_ttz_OffZ.h"
#include "xgboost/wwz_vs_ttz_bVeto.h"
#include "xgboost/wwz_vs_ttz_emu.h"
#include "xgboost/wwz_vs_ttz_nbAll.h"
#include "xgboost/wwz_vs_ttzzz_OffZ.h"
#include "xgboost/wwz_vs_ttzzz_bVeto.h"
#include "xgboost/wwz_vs_ttzzz_emu.h"
#include "xgboost/wwz_vs_zz_OffZ.h"
#include "xgboost/wwz_vs_zz_OffZHighTTZBDT.h"
#include "xgboost/wwz_vs_zz_emu.h"
#include "xgboost/wwz_vs_zz_emuHighTTZBDT.h"

//==============================================================================================================
//
// BDT Module
//
//==============================================================================================================

//##############################################################################################################
void wvzModule::BDTModule::AddOutput()
{

    tx->createBranch<float>("wwz_vs_ttz_bVeto");
    tx->createBranch<float>("wwz_vs_ttz_emu");
    tx->createBranch<float>("wwz_vs_ttz_nbAll");
    tx->createBranch<float>("wwz_vs_ttz_OffZ");
    tx->createBranch<float>("wwz_vs_ttzzz_bVeto");
    tx->createBranch<float>("wwz_vs_ttzzz_emu");
    tx->createBranch<float>("wwz_vs_ttzzz_OffZ");
    tx->createBranch<float>("wwz_vs_zz_emu");
    tx->createBranch<float>("wwz_vs_zz_emuHighTTZBDT");
    tx->createBranch<float>("wwz_vs_zz_OffZ");
    tx->createBranch<float>("wwz_vs_zz_OffZHighTTZBDT");

}

//##############################################################################################################
void wvzModule::BDTModule::FillOutput()
{

    //index:
    //0 - wwz_vs_ttz_bVeto
    //1 - wwz_vs_ttz_emu
    //2 - wwz_vs_ttz_nbAll
    //3 - wwz_vs_ttz_OffZ
    //4 - wwz_vs_ttzzz_bVeto
    //5 - wwz_vs_ttzzz_emu
    //6 - wwz_vs_ttzzz_OffZ
    //7 - wwz_vs_zz_emu
    //8 - wwz_vs_zz_emuHighTTZBDT
    //9 - wwz_vs_zz_OffZ
    //10 - wwz_vs_zz_OffZHighTTZBDT

    // BDT input variables are calculated only when event passes nVlep == 4
    const int& nVlep = tx->getBranch<int>("nVlep");
    const int& nNlep = tx->getBranch<int>("nNlep", false);
    if (nVlep >= 4 and nNlep >= 2)
    {

        const float& evt_MllN = tx->getBranch<float>("MllN");
        const float& evt_MllZ = tx->getBranch<float>("MllZ");
        const float& evt_ZPt = tx->getBranch<float>("ZPt");
        const float& evt_met_pt = tx->getBranch<float>("met_pt");
        const float& evt_nj = tx->getBranch<float>("nj");
        const float& evt_nb = tx->getBranch<float>("nb");
        const float& evt_lep1Pt = tx->getBranch<float>("lep1Pt");
        const float& evt_lep2Pt = tx->getBranch<float>("lep2Pt");
        const float& evt_lep3Pt = tx->getBranch<float>("lep3Pt");
        const float& evt_lep4Pt = tx->getBranch<float>("lep4Pt");
        const float& evt_lep3Id = tx->getBranch<float>("lep3Id");
        const float& evt_lep4Id = tx->getBranch<float>("lep4Id");
        const float& evt_lep3MT = tx->getBranch<float>("lep3MT");
        const float& evt_lep4MT = tx->getBranch<float>("lep4MT");
        const float& evt_lep34MT = tx->getBranch<float>("lep34MT");
        const float& evt_lep1dZ = tx->getBranch<float>("lep1dZ");
        const float& evt_lep2dZ = tx->getBranch<float>("lep2dZ");
        const float& evt_lep3dZ = tx->getBranch<float>("lep3dZ");
        const float& evt_lep4dZ = tx->getBranch<float>("lep4dZ");
        const float& evt_pt_zeta = tx->getBranch<float>("pt_zeta");
        const float& evt_pt_zeta_vis = tx->getBranch<float>("pt_zeta_vis");
        const float& evt_phi0 = tx->getBranch<float>("phi0");
        const float& evt_phi = tx->getBranch<float>("phi");
        const float& evt_phiH = tx->getBranch<float>("phiH");
        const float& evt_theta0 = tx->getBranch<float>("theta0");
        const float& evt_theta1 = tx->getBranch<float>("theta1");
        const float& evt_theta2 = tx->getBranch<float>("theta2");
        const float& evt_minDRJetToLep3 = tx->getBranch<float>("minDRJetToLep3");
        const float& evt_minDRJetToLep4 = tx->getBranch<float>("minDRJetToLep4");
        const float& evt_jet1Pt = tx->getBranch<float>("jet1Pt");
        const float& evt_jet2Pt = tx->getBranch<float>("jet2Pt");
        const float& evt_jet3Pt = tx->getBranch<float>("jet3Pt");
        const float& evt_jet4Pt = tx->getBranch<float>("jet4Pt");
        const float& evt_jet1BtagScore = tx->getBranch<float>("jet1BtagScore");
        const float& evt_jet2BtagScore = tx->getBranch<float>("jet2BtagScore");
        const float& evt_jet3BtagScore = tx->getBranch<float>("jet3BtagScore");
        const float& evt_jet4BtagScore = tx->getBranch<float>("jet4BtagScore");


        std::vector<float> test_sample_ttz_bVeto{evt_nj, evt_minDRJetToLep3, evt_minDRJetToLep4, evt_jet1Pt, evt_jet2Pt, evt_jet3Pt, evt_jet4Pt, evt_jet1BtagScore, evt_jet2BtagScore, evt_jet3BtagScore, evt_jet4BtagScore, evt_MllN, evt_lep3MT, evt_lep4MT, evt_lep34MT, evt_ZPt};
        std::vector<float> test_sample_ttz_emu{evt_nj, evt_minDRJetToLep3, evt_minDRJetToLep4, evt_jet1Pt, evt_jet2Pt, evt_jet3Pt, evt_jet4Pt, evt_jet1BtagScore, evt_jet2BtagScore, evt_jet3BtagScore, evt_jet4BtagScore, evt_MllN, evt_lep3MT, evt_lep4MT, evt_lep34MT, evt_ZPt};
        std::vector<float> test_sample_ttz_nbAll{evt_nb, evt_nj, evt_minDRJetToLep3, evt_minDRJetToLep4, evt_jet1Pt, evt_jet2Pt, evt_jet3Pt, evt_jet4Pt, evt_jet1BtagScore, evt_jet2BtagScore, evt_jet3BtagScore, evt_jet4BtagScore, evt_MllN, evt_lep3MT, evt_lep4MT, evt_lep34MT, evt_ZPt};
        std::vector<float> test_sample_ttz_OffZ{evt_nj, evt_minDRJetToLep3, evt_minDRJetToLep4, evt_jet1Pt, evt_jet2Pt, evt_jet3Pt, evt_jet4Pt, evt_jet1BtagScore, evt_jet2BtagScore, evt_jet3BtagScore, evt_jet4BtagScore, evt_MllN, evt_lep3MT, evt_lep4MT, evt_lep34MT, evt_ZPt};
        std::vector<float> test_sample_ttzzz_bVeto{evt_met_pt, evt_lep3Id, evt_lep4Id, evt_lep3Pt, evt_lep4Pt, evt_ZPt, evt_lep3dZ, evt_lep4dZ, evt_lep3MT, evt_lep4MT, evt_lep34MT, evt_phi0, evt_theta0, evt_phi, evt_theta1, evt_theta2, evt_MllN, evt_pt_zeta, evt_pt_zeta_vis, evt_nj, evt_minDRJetToLep3, evt_minDRJetToLep4, evt_jet1Pt, evt_jet2Pt, evt_jet3Pt, evt_jet4Pt, evt_jet1BtagScore, evt_jet2BtagScore, evt_jet3BtagScore, evt_jet4BtagScore};
        std::vector<float> test_sample_ttzzz_emu{evt_met_pt, evt_lep3Pt, evt_lep4Pt, evt_ZPt, evt_lep3dZ, evt_lep4dZ, evt_lep3MT, evt_lep4MT, evt_lep34MT, evt_phi0, evt_theta0, evt_phi, evt_theta1, evt_theta2, evt_MllN, evt_pt_zeta, evt_pt_zeta_vis, evt_nj, evt_minDRJetToLep3, evt_minDRJetToLep4, evt_jet1Pt, evt_jet2Pt, evt_jet3Pt, evt_jet4Pt, evt_jet1BtagScore, evt_jet2BtagScore, evt_jet3BtagScore, evt_jet4BtagScore};
        std::vector<float> test_sample_ttzzz_OffZ{evt_met_pt, evt_lep3Pt, evt_lep4Pt, evt_ZPt, evt_lep3dZ, evt_lep4dZ, evt_lep3MT, evt_lep4MT, evt_lep34MT, evt_phi0, evt_theta0, evt_phi, evt_theta1, evt_theta2, evt_MllN, evt_pt_zeta, evt_pt_zeta_vis, evt_nj, evt_minDRJetToLep3, evt_minDRJetToLep4, evt_jet1Pt, evt_jet2Pt, evt_jet3Pt, evt_jet4Pt, evt_jet1BtagScore, evt_jet2BtagScore, evt_jet3BtagScore, evt_jet4BtagScore};
        std::vector<float> test_sample_zz_emu{evt_met_pt, evt_lep3Pt, evt_lep4Pt, evt_ZPt, evt_lep3dZ, evt_lep4dZ, evt_lep3MT, evt_lep4MT, evt_lep34MT, evt_phi0, evt_theta0, evt_phi, evt_theta1, evt_theta2, evt_MllN, evt_pt_zeta, evt_pt_zeta_vis};
        std::vector<float> test_sample_zz_emuHighTTZBDT{evt_met_pt, evt_lep3Pt, evt_lep4Pt, evt_ZPt, evt_lep3dZ, evt_lep4dZ, evt_lep3MT, evt_lep4MT, evt_lep34MT, evt_phi0, evt_theta0, evt_phi, evt_theta1, evt_theta2, evt_MllN, evt_pt_zeta, evt_pt_zeta_vis};
        std::vector<float> test_sample_zz_OffZ{evt_met_pt, evt_lep3Pt, evt_lep4Pt, evt_ZPt, evt_lep3dZ, evt_lep4dZ, evt_lep3MT, evt_lep4MT, evt_lep34MT, evt_phi0, evt_theta0, evt_phi, evt_theta1, evt_theta2, evt_MllN, evt_pt_zeta, evt_pt_zeta_vis};
        std::vector<float> test_sample_zz_OffZHighTTZBDT{evt_met_pt, evt_lep3Pt, evt_lep4Pt, evt_ZPt, evt_lep3dZ, evt_lep4dZ, evt_lep3MT, evt_lep4MT, evt_lep34MT, evt_phi0, evt_theta0, evt_phi, evt_theta1, evt_theta2, evt_MllN, evt_pt_zeta, evt_pt_zeta_vis};

        tx->setBranch<float>("wwz_vs_ttz_bVeto", wwz_vs_ttz_bVeto(test_sample_ttz_bVeto, true)[0]);
        tx->setBranch<float>("wwz_vs_ttz_emu", wwz_vs_ttz_emu(test_sample_ttz_emu, true)[0]);
        tx->setBranch<float>("wwz_vs_ttz_nbAll", wwz_vs_ttz_nbAll(test_sample_ttz_nbAll, true)[0]);
        tx->setBranch<float>("wwz_vs_ttz_OffZ", wwz_vs_ttz_OffZ(test_sample_ttz_OffZ, true)[0]);
        tx->setBranch<float>("wwz_vs_ttzzz_bVeto", wwz_vs_ttzzz_bVeto(test_sample_ttzzz_bVeto, true)[0]);
        tx->setBranch<float>("wwz_vs_ttzzz_emu", wwz_vs_ttzzz_emu(test_sample_ttzzz_emu, true)[0]);
        tx->setBranch<float>("wwz_vs_ttzzz_OffZ", wwz_vs_ttzzz_OffZ(test_sample_ttzzz_OffZ, true)[0]);
        tx->setBranch<float>("wwz_vs_zz_emu", wwz_vs_zz_emu(test_sample_zz_emu, true)[0]);
        tx->setBranch<float>("wwz_vs_zz_emuHighTTZBDT", wwz_vs_zz_emuHighTTZBDT(test_sample_zz_emuHighTTZBDT, true)[0]);
        tx->setBranch<float>("wwz_vs_zz_OffZ", wwz_vs_zz_OffZ(test_sample_zz_OffZ, true)[0]);
        tx->setBranch<float>("wwz_vs_zz_OffZHighTTZBDT", wwz_vs_zz_OffZHighTTZBDT(test_sample_zz_OffZHighTTZBDT, true)[0]);
    }

}
