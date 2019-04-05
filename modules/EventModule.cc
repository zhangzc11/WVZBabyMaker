#include "EventModule.h"

//==============================================================================================================
//
// Event Module
//
//==============================================================================================================

void wvzModule::EventModule::AddOutput()
{
    tx->createBranch<float>("nvtx");
}

void wvzModule::EventModule::FillOutput()
{
    // Count number of good vertices.
    int nvtx = 0;
    for (unsigned int ivtx = 0; ivtx < cms3.evt_nvtxs(); ivtx++)
    {
        if (!isGoodVertex(ivtx)) { continue; }
        nvtx++;
    }
    tx->setBranch<float>("nvtx", nvtx);
}
