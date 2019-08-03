#ifndef BDTModule_h
#define BDTModule_h

#include "wvzBabyMaker.h"

namespace wvzModule
{
    //__________________________________________________________________
    // BDT module
    class BDTModule: public RooUtil::Module
    {
        public:
            wvzBabyMaker* babymaker;
            BDTModule(wvzBabyMaker* parent) { babymaker = parent; }
            virtual void AddOutput();
            virtual void FillOutput();
    };
}

#endif
