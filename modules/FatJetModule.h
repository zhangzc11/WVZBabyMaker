#ifndef FatJetModule_h
#define FatJetModule_h

#include "rooutil.h"
#include "wvzBabyMaker.h"

namespace wvzModule
{
    //__________________________________________________________________
    // FatJet module
    class FatJetModule: public RooUtil::Module
    {
        public:
            wvzBabyMaker* babymaker;
            FatJetModule(wvzBabyMaker* parent) { babymaker = parent; }
            virtual void AddOutput();
            virtual void FillOutput();
            void pushbackFatJet(int ijet);
    };
}

#endif
