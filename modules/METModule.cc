#include "METModule.h"

//==============================================================================================================
//
// MET Module
//
//==============================================================================================================

void wvzModule::METModule::AddOutput()
{

    tx->createBranch<LV>("met_p4");
    tx->createBranch<float>("met_pt");
    tx->createBranch<float>("met_phi");
    tx->createBranch<float>("met_up_pt");
    tx->createBranch<float>("met_up_phi");
    tx->createBranch<float>("met_dn_pt");
    tx->createBranch<float>("met_dn_phi");
    tx->createBranch<float>("met_gen_pt");
    tx->createBranch<float>("met_gen_phi");

}

void wvzModule::METModule::FillOutput()
{

    tx->setBranch<LV>("met_p4", RooUtil::Calc::getLV(babymaker->coreMET.met_pt, 0, babymaker->coreMET.met_phi, 0));
    tx->setBranch<float>("met_pt", babymaker->coreMET.met_pt);
    tx->setBranch<float>("met_phi", babymaker->coreMET.met_phi);
    tx->setBranch<float>("met_up_pt", babymaker->coreMET.met_up_pt);
    tx->setBranch<float>("met_up_phi", babymaker->coreMET.met_up_phi);
    tx->setBranch<float>("met_dn_pt", babymaker->coreMET.met_dn_pt);
    tx->setBranch<float>("met_dn_phi", babymaker->coreMET.met_dn_phi);
    tx->setBranch<float>("met_gen_pt", cms3.gen_met());
    tx->setBranch<float>("met_gen_phi", cms3.gen_metPhi());

}
