#ifndef METModule_h
#define METModule_h

#include "rooutil.h"
#include "wvzBabyMaker.h"
#include "METCorrectionHandler.h"

namespace wvzModule
{
    //__________________________________________________________________
    // MET module
    class METModule: public RooUtil::Module
    {
        public:
            wvzBabyMaker* babymaker;
            METCorrectionHandler metcorrector;
            METObject metobj;
            METObject metobj_corrected;
            METModule(wvzBabyMaker* parent) { babymaker = parent; metcorrector.setup(gconf.year, TString::Format("%d", gconf.year), "StopAnalysis/StopCORE/METCorr/METSFs/"); }
            virtual void AddOutput();
            virtual void FillOutput();
            virtual void correctMET();
    };
}

#endif
