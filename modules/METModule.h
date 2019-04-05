#ifndef METModule_h
#define METModule_h

#include "rooutil.h"
#include "wvzBabyMaker.h"

namespace wvzModule
{
    //__________________________________________________________________
    // MET module
    class METModule: public RooUtil::Module
    {
        public:
            wvzBabyMaker* babymaker;
            METModule(wvzBabyMaker* parent) { babymaker = parent; }
            virtual void AddOutput();
            virtual void FillOutput();
    };
}

#endif
