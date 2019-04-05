#ifndef JetModule_h
#define JetModule_h

#include "rooutil.h"
#include "wvzBabyMaker.h"

namespace wvzModule
{
    //__________________________________________________________________
    // Jet module
    class JetModule: public RooUtil::Module
    {
        public:
            wvzBabyMaker* babymaker;
            JetModule(wvzBabyMaker* parent) { babymaker = parent; }
            virtual void AddOutput();
            virtual void FillOutput();
    };
}

#endif
