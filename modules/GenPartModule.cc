#include "GenPartModule.h"

//==============================================================================================================
//
// GenPart Module
//
//==============================================================================================================

void wvzModule::GenPartModule::AddOutput()
{
    tx->createBranch<float>("gen_ht");
    tx->createBranch<vector<LV>>("gen_V_p4");
    tx->createBranch<vector<float>>("gen_V_pt");
    tx->createBranch<vector<float>>("gen_V_eta");
    tx->createBranch<vector<float>>("gen_V_phi");
    tx->createBranch<vector<float>>("gen_V_mass");
    tx->createBranch<vector<int>>("gen_V_id");
    tx->createBranch<vector<LV>>("gen_lep_p4");
    tx->createBranch<vector<float>>("gen_lep_pt");
    tx->createBranch<vector<float>>("gen_lep_eta");
    tx->createBranch<vector<float>>("gen_lep_phi");
    tx->createBranch<vector<float>>("gen_lep_mass");
    tx->createBranch<vector<int>>("gen_lep_id");
    tx->createBranch<int>("VHchannel");
    tx->createBranch<int>("Higgschannel");
}

void wvzModule::GenPartModule::FillOutput()
{
    tx->setBranch<float>("gen_ht", babymaker->coreGenPart.gen_ht);

    bool isHtoWW = false;
    bool isWnotFromH = false;
    bool isZthere = false;

    const vector<int>& genPart_idx = babymaker->coreGenPart.genPart_idx;
    const vector<int>& genPart_pdgId = babymaker->coreGenPart.genPart_pdgId;
    const vector<int>& genPart_status = babymaker->coreGenPart.genPart_status;
    const vector<int>& genPart_motherId = babymaker->coreGenPart.genPart_motherId;
    const vector<LV>& genPart_p4 = babymaker->coreGenPart.genPart_p4;

    vector<LV> gen_V_p4;
    vector<int> gen_V_id;
    vector<LV> higgs_decay_p4;
    vector<int> higgs_decay_id;

    for (unsigned int i = 0; i < genPart_pdgId.size(); ++i)
    {
        if (
                (abs(genPart_pdgId[i]) == 23 && abs(genPart_motherId[i]) != 25 && genPart_status[i] == 22) or
                (abs(genPart_pdgId[i]) == 24 && abs(genPart_motherId[i]) != 25 && genPart_status[i] == 22)
                // (abs(genPart_motherId[i]) == 25 && (genPart_pdgId[i] == 23 or abs(genPart_pdgId[i]) == 24))
           )
        {
            gen_V_p4.push_back(genPart_p4[i]);
            gen_V_id.push_back(genPart_pdgId[i]);
        }
        if (
                (genPart_motherId[i] == 25 and genPart_pdgId[i] != 25)
           )
        {
            higgs_decay_p4.push_back(genPart_p4[i]);
            higgs_decay_id.push_back(genPart_pdgId[i]);
        }
        // if (abs(genPart_motherId[i]) == 25 && (genPart_pdgId[i] == 23 or abs(genPart_pdgId[i]) == 24))
        //     babymaker->coreGenPart.printParticle(genPart_idx[i]);
        // if (abs(genPart_pdgId[i]) != 24) continue;
        // if (genPart_status[i] != 22) continue;
        // if (abs(genPart_motherId[i]) == 25)  isHtoWW     = true;
        // if (abs(genPart_motherId[i]) != 2)   isWnotFromH = true;
        // if (isHtoWW && isWnotFromH && !isZthere) break;
    }

    if (babymaker->looper.getCurrentFileName().Contains("VHToNonbb"))
    {

        // H->XX
        if (higgs_decay_id.size() == 0)
        {
            std::cout << "Error: expected to find higgs decay but did not find any" << std::endl;
        }
        else if (higgs_decay_id.size() != 2)
        {
            std::cout << "Error: found !=2 higgs_decays" << std::endl;
        }
        else if (abs(higgs_decay_id[0]) == abs(higgs_decay_id[1]))
        {
            tx->setBranch<int>("Higgschannel", abs(higgs_decay_id[0]));
        }
        else if (abs(higgs_decay_id[0]) + abs(higgs_decay_id[1]) == 45) // H->Zgamma
        {
            tx->setBranch<int>("Higgschannel", 22);
        }
        else
        {
            std::cout << "Error: inconsistencies in decay id" << std::endl;
        }

        // Vector boson in VH
        if (gen_V_p4.size() != 1)
        {
            std::cout << "Error: found !=1 associated vector boson" << std::endl;
        }
        else
        {
            tx->setBranch<int>("VHchannel", abs(gen_V_id[0]));
        }
    }

}

