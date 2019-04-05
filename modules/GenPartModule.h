#ifndef GenPartModule_h
#define GenPartModule_h

#include "rooutil.h"
#include "wvzBabyMaker.h"

namespace wvzModule
{
    //__________________________________________________________________
    // GenPart
    class GenPartModule: public RooUtil::Module
    {
        public:
            wvzBabyMaker* babymaker;
            GenPartModule(wvzBabyMaker* parent) { babymaker = parent; }
            virtual void AddOutput();
            virtual void FillOutput();
    };
}

#endif
