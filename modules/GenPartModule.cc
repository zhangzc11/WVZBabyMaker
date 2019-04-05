#include "GenPartModule.h"

//==============================================================================================================
//
// GenPart Module
//
//==============================================================================================================

void wvzModule::GenPartModule::AddOutput()
{
    tx->createBranch<float>("gen_ht");
}

void wvzModule::GenPartModule::FillOutput()
{
    tx->setBranch<float>("gen_ht", babymaker->coreGenPart.gen_ht);
}

