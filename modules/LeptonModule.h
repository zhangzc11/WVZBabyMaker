#ifndef LeptonModule_h
#define LeptonModule_h

#include "rooutil.h"
#include "wvzBabyMaker.h"

namespace wvzModule
{
    //__________________________________________________________________
    // Lepton module
    class LeptonModule: public RooUtil::Module
    {
        public:
            wvzBabyMaker* babymaker;
            LeptonModule(wvzBabyMaker* parent) { babymaker = parent; }
            virtual void AddOutput();
            virtual void FillOutput();
    };
}

#endif
