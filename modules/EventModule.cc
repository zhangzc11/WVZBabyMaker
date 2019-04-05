#include "EventModule.h"

//==============================================================================================================
//
// Event Module
//
//==============================================================================================================

void wvzModule::EventModule::AddOutput()
{
    tx->createBranch<int>("firstgoodvertex");
    tx->createBranch<int>("nvtx");
    tx->createBranch<int>("nTrueInt");
}

void wvzModule::EventModule::FillOutput()
{
    // First good vertex
    tx->setBranch<int>("firstgoodvertex", firstGoodVertex());

    // Count number of good vertices.
    int nvtx = 0;
    for (unsigned int ivtx = 0; ivtx < cms3.evt_nvtxs(); ivtx++)
    {
        if (!isGoodVertex(ivtx)) { continue; }
        nvtx++;
    }
    tx->setBranch<int>("nvtx", nvtx);

    // N True interaction for pileup reweighting
    if (!cms3.evt_isRealData())
        tx->setBranch<int>("nTrueInt", cms3.puInfo_trueNumInteractions().at(0));
    else
        tx->setBranch<int>("nTrueInt", -999);
}
