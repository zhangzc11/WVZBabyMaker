#include "TriggerModule.h"

//==============================================================================================================
//
// Trigger Module
//
//==============================================================================================================

void wvzModule::TriggerModule::AddOutput()
{
    // Triggers
    tx->createBranch<int>("HLT_DoubleMu");
    tx->createBranch<int>("HLT_DoubleEl");
    tx->createBranch<int>("HLT_MuEG");

    // duplicate removal bits
    tx->createBranch<int>("pass_duplicate_ee_em_mm");
    tx->createBranch<int>("pass_duplicate_mm_em_ee");
}

void wvzModule::TriggerModule::FillOutput()
{
    // Triggers
    tx->createBranch<int>("HLT_DoubleMu");
    tx->createBranch<int>("HLT_DoubleEl");
    tx->createBranch<int>("HLT_MuEG");

        if (gconf.year == 2016)
        {
            tx->setBranch<int>("HLT_DoubleMu"                  , coreTrigger.HLT_DoubleMu                  );
            tx->setBranch<int>("HLT_DoubleEl_DZ_2"             , coreTrigger.HLT_DoubleEl_DZ_2             );
            tx->setBranch<int>("HLT_MuEG"                      , coreTrigger.HLT_MuEG                      );
        }

        else if (gconf.year == 2017)
        {
            tx->setBranch<int>("HLT_DoubleMu"                  , coreTrigger.HLT_DoubleMu_2017             );
            tx->setBranch<int>("HLT_DoubleEl"                  , coreTrigger.HLT_DoubleEl_2017             );
            tx->setBranch<int>("HLT_DoubleEl_DZ"               , coreTrigger.HLT_DoubleEl_DZ               );
            tx->setBranch<int>("HLT_DoubleEl_DZ_2"             , coreTrigger.HLT_DoubleEl_DZ_2             );
            tx->setBranch<int>("HLT_MuEG"                      , coreTrigger.HLT_MuEG_2017                 );
            tx->setBranch<int>("HLT_MuEG_2016"                 , coreTrigger.HLT_MuEG                      );
            tx->setBranch<int>("HLT_SingleEl8"                 , coreTrigger.HLT_SingleEl8_2017            );
            tx->setBranch<int>("HLT_SingleEl17"                , coreTrigger.HLT_SingleEl17_2017           );
            tx->setBranch<int>("HLT_SingleIsoEl8"              , coreTrigger.HLT_SingleIsoEl8_2017         );
            tx->setBranch<int>("HLT_SingleIsoEl17"             , coreTrigger.HLT_SingleIsoEl17             );
            tx->setBranch<int>("HLT_SingleIsoEl23"             , coreTrigger.HLT_SingleIsoEl23_2017        );
            tx->setBranch<int>("HLT_SingleIsoMu8"              , coreTrigger.HLT_SingleIsoMu8_2017         );
            tx->setBranch<int>("HLT_SingleIsoMu17"             , coreTrigger.HLT_SingleIsoMu17_2017        );
            tx->setBranch<int>("HLT_PFMET140_PFMHT140_IDTight" , coreTrigger.HLT_PFMET140_PFMHT140_IDTight );
        }

        else if (gconf.year == 2018)
        {
            tx->setBranch<int>("HLT_DoubleMu"                  , coreTrigger.HLT_DoubleMu_2018             );
            tx->setBranch<int>("HLT_DoubleEl"                  , coreTrigger.HLT_DoubleEl_2018             );
            tx->setBranch<int>("HLT_DoubleEl_DZ"               , coreTrigger.HLT_DoubleEl_DZ               );
            tx->setBranch<int>("HLT_DoubleEl_DZ_2"             , coreTrigger.HLT_DoubleEl_DZ_2             );
            tx->setBranch<int>("HLT_MuEG"                      , coreTrigger.HLT_MuEG_2018                 );
            tx->setBranch<int>("HLT_MuEG_2016"                 , coreTrigger.HLT_MuEG                      );
            tx->setBranch<int>("HLT_SingleEl8"                 , coreTrigger.HLT_SingleEl8_2018            );
            tx->setBranch<int>("HLT_SingleEl17"                , coreTrigger.HLT_SingleEl17_2018           );
            tx->setBranch<int>("HLT_SingleIsoEl8"              , coreTrigger.HLT_SingleIsoEl8_2018         );
            tx->setBranch<int>("HLT_SingleIsoEl17"             , coreTrigger.HLT_SingleIsoEl17             );
            tx->setBranch<int>("HLT_SingleIsoEl23"             , coreTrigger.HLT_SingleIsoEl23_2018        );
            tx->setBranch<int>("HLT_SingleIsoMu8"              , coreTrigger.HLT_SingleIsoMu8_2018         );
            tx->setBranch<int>("HLT_SingleIsoMu17"             , coreTrigger.HLT_SingleIsoMu17_2018        );
            tx->setBranch<int>("HLT_PFMET140_PFMHT140_IDTight" , coreTrigger.HLT_PFMET140_PFMHT140_IDTight );
        }


    int pass_duplicate_se_sm = 0;
    int pass_duplicate_sm_se = 0;
    tx->setBranch<int>("pass_duplicate_se_sm", pass_duplicate_se_sm);
    tx->setBranch<int>("pass_duplicate_sm_se", pass_duplicate_sm_se);
}
