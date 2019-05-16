#ifndef wvzBabyMaker_h
#define wvzBabyMaker_h

#include "babyMaker.h"

class wvzBabyMaker: public babyMaker
{
    public:
        wvzBabyMaker();
        ~wvzBabyMaker();

        enum BabyMode
        {
            kWVZ = 1,
            kDilep = 2,
        };

        RooUtil::Processor* processor;
        RooUtil::VarMap additional_elec_vars;
        RooUtil::VarMap additional_muon_vars;

        BabyMode babyMode;
        void SetBabyMode(BabyMode bm);

        virtual void SetLeptonID();

        virtual void ProcessObjectsPrePassSelection();
        virtual void ProcessObjectsPostPassSelection();
        virtual void ProcessElectrons();
        virtual void ProcessMuons();
        virtual bool PassSelection();

        virtual void AddOutput();
        virtual void FillOutput();

        static bool isPt10Electron(int idx);
        static bool isPt10Muon(int idx);
        bool isLeptonOverlappingWithJet(int ijet);

};

#include "TriggerModule.h"
#include "GenPartModule.h"
#include "EventModule.h"
#include "LeptonModule.h"
#include "METModule.h"
#include "JetModule.h"


#endif
