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

    if (gconf.year == 2016)
    {
        tx->setBranch<int>("HLT_DoubleMu" , coreTrigger.HLT_DoubleMu                                );
        tx->setBranch<int>("HLT_DoubleEl" , coreTrigger.HLT_DoubleEl || coreTrigger.HLT_DoubleEl_DZ );
        tx->setBranch<int>("HLT_MuEG"     , coreTrigger.HLT_MuEG                                    );
    }

    else if (gconf.year == 2017)
    {
        tx->setBranch<int>("HLT_DoubleMu" , coreTrigger.HLT_DoubleMu_2017 );
        tx->setBranch<int>("HLT_DoubleEl" , coreTrigger.HLT_DoubleEl_2017 );
        tx->setBranch<int>("HLT_MuEG"     , coreTrigger.HLT_MuEG_2017     );
    }

    else if (gconf.year == 2018)
    {
        tx->setBranch<int>("HLT_DoubleMu" , coreTrigger.HLT_DoubleMu_2018 );
        tx->setBranch<int>("HLT_DoubleEl" , coreTrigger.HLT_DoubleEl_2018 );
        tx->setBranch<int>("HLT_MuEG"     , coreTrigger.HLT_MuEG_2018     );
    }

    bool trig_ee = true;
    bool trig_em = true;
    bool trig_mm = true;

    if (gconf.year == 2016)
    {
        trig_ee = coreTrigger.HLT_DoubleEl || coreTrigger.HLT_DoubleEl_DZ;
        trig_em = coreTrigger.HLT_MuEG;
        trig_mm = coreTrigger.HLT_DoubleMu;
    }
    else if (gconf.year == 2017)
    {
        trig_ee = coreTrigger.HLT_DoubleEl_2017;
        trig_em = coreTrigger.HLT_MuEG_2017;
        trig_mm = coreTrigger.HLT_DoubleMu_2017;
    }
    else if (gconf.year == 2018)
    {
        trig_ee = coreTrigger.HLT_DoubleEl_2018;
        trig_em = coreTrigger.HLT_MuEG_2018;
        trig_mm = coreTrigger.HLT_DoubleMu_2018;
    }

    bool is_pd_ee = (babymaker->looper.getCurrentFileName().Contains("DoubleEG") || babymaker->looper.getCurrentFileName().Contains("EGamma"));
    bool is_pd_em = babymaker->looper.getCurrentFileName().Contains("MuonEG");
    bool is_pd_mm = babymaker->looper.getCurrentFileName().Contains("DoubleMuon");
    bool pass_duplicate_ee_em_mm = false;
    bool pass_duplicate_mm_em_ee = false;

    if (is_pd_ee)
    {
        if (trig_ee)
            pass_duplicate_ee_em_mm = true;
        if (!trig_mm && !trig_em && trig_ee)
            pass_duplicate_mm_em_ee = true;
    }
    else if (is_pd_em)
    {
        if (!trig_ee && trig_em)
            pass_duplicate_ee_em_mm = true;
        if (!trig_mm && trig_em)
            pass_duplicate_mm_em_ee = true;
    }
    else if (is_pd_mm)
    {
        if (!trig_ee && !trig_em && trig_mm)
            pass_duplicate_ee_em_mm = true;
        if (trig_mm)
            pass_duplicate_mm_em_ee = true;
    }
    tx->setBranch<int>("pass_duplicate_ee_em_mm", pass_duplicate_ee_em_mm);
    tx->setBranch<int>("pass_duplicate_mm_em_ee", pass_duplicate_mm_em_ee);

}
