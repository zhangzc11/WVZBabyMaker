#include "wvzBabyMaker.h"

// #define USE_LEAD_JET_SCHEME

//##############################################################################################################
wvzBabyMaker::wvzBabyMaker() : processor(0)
{
}

wvzBabyMaker::~wvzBabyMaker() {}

//##############################################################################################################
void wvzBabyMaker::ProcessObjectsPrePassSelection()
{
    // Process leptons via CoreUtil
    ProcessLeptons();

    // Process MET (recalculate etc.)
    ProcessMET();

}

//##############################################################################################################
void wvzBabyMaker::ProcessObjectsPostPassSelection()
{

    // Fat jet
    ProcessFatJets();

    // Triggers
    ProcessTriggers();

    // Loop over gen particles
    ProcessGenParticles();

    // Loop over Jets
    ProcessJets();

    // Loop over charged particle candidates
    ProcessTracks();

}

//##############################################################################################################
void wvzBabyMaker::ProcessElectrons()
{
    coreElectron.process(isPt25Electron);
}

//##############################################################################################################
void wvzBabyMaker::ProcessMuons()
{
    coreMuon.process(isPt25Muon);
}

//##############################################################################################################
// Goal is to pass events with at least one fat jet and one lepton
bool wvzBabyMaker::PassSelection()
{
    return true;
}

//##############################################################################################################
void wvzBabyMaker::AddOutput()
{

    // initialize the processor connected to the main output TTreeX=tx.
    processor = new RooUtil::Processor(tx);

    // Add the lepton module which handles what variables to write, and how.
    processor->AddModule(new wvzModule::TriggerModule(this));
    processor->AddModule(new wvzModule::GenPartModule(this));
    processor->AddModule(new wvzModule::EventModule(this));
    processor->AddModule(new wvzModule::LeptonModule(this));
    processor->AddModule(new wvzModule::METModule(this));

    // Now create the outputs to the ttree
    processor->AddOutputs();

}

//##############################################################################################################
void wvzBabyMaker::FillOutput()
{
    processor->FillOutputs();
}

//##############################################################################################################
// Used to overlap remova against tracks
bool wvzBabyMaker::isPt25Electron(int idx)
{
    if (!( cms3.els_p4()[idx].pt() > 25.          )) return false;
    if (!( isPt10Electron(idx)                    )) return false;
    return true;
}

//##############################################################################################################
// Used to overlap remova against tracks
bool wvzBabyMaker::isPt25Muon(int idx)
{
    if (!( cms3.mus_p4()[idx].pt() > 25.        )) return false;
    if (!( isPt10Muon(idx)                      )) return false;
    return true;
}

//##############################################################################################################
// Used to overlap remova against tracks
bool wvzBabyMaker::isPt10Electron(int idx)
{
    if (!( cms3.els_p4()[idx].pt() > 10.          )) return false;
    if (!( isVetoElectronPOGspring16noIso_v1(idx) )) return false;
    if (!( fabs(cms3.els_p4()[idx].eta()) < 2.5   )) return false;
    if (!( elMiniRelIsoCMS3_EA(idx, 2) < 0.2      )) return false;
    if (!( fabs(cms3.els_dzPV()[idx]) < 0.1       )) return false;
    if (!( fabs(cms3.els_dxyPV()[idx]) < 0.05     )) return false;
    return true;
}

//##############################################################################################################
// Used to overlap remova against tracks
bool wvzBabyMaker::isPt10Muon(int idx)
{
    if (!( cms3.mus_p4()[idx].pt() > 10.        )) return false;
    if (!( isLooseMuonPOG(idx)                  )) return false;
    if (!( fabs(cms3.mus_p4()[idx].eta()) < 2.5 )) return false;
    if (!( muMiniRelIsoCMS3_EA(idx, 2) < 0.2    )) return false;
    if (!( fabs(cms3.mus_dzPV()[idx]) < 0.1     )) return false;
    if (!( fabs(cms3.mus_dxyPV()[idx]) < 0.05   )) return false;
    return true;
}

//##############################################################################################################
bool wvzBabyMaker::isLeptonOverlappingWithJet(int ijet)
{
    bool is_overlapping = false;
    int idx = coreJet.index[ijet];
    const LV& jet_p4 = cms3.pfjets_p4()[idx];

    for (unsigned ilep = 0; ilep < cms3.els_p4().size(); ++ilep)
    {
        const LV& p4 = cms3.els_p4()[ilep];
        if (!( isPt10Electron(ilep) )) continue;
        if (!( eleRelIso03EA(ilep, 2) < 0.4 )) continue;
        if (ROOT::Math::VectorUtil::DeltaR(jet_p4, p4) < 0.4)
        {
            is_overlapping = true;
            break;
        }
    }

    for (unsigned ilep = 0; ilep < cms3.mus_p4().size(); ++ilep)
    {
        const LV& p4 = cms3.mus_p4()[ilep];
        if (!( isPt10Muon(ilep) )) continue;
        if (!( muRelIso03EA(ilep, 2) < 0.4 )) continue;
        if (ROOT::Math::VectorUtil::DeltaR(jet_p4, p4) < 0.4)
        {
            is_overlapping = true;
            break;
        }
    }

    if (is_overlapping)
        return true;

    return false;
}
