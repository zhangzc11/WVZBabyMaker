#ifndef TriggerModule_h
#define TriggerModule_h

#include "rooutil.h"
#include "wvzBabyMaker.h"

namespace wvzModule
{
    //__________________________________________________________________
    // Trigger module
    class TriggerModule: public RooUtil::Module
    {
        public:
            wvzBabyMaker* babymaker;
            TriggerModule(wvzBabyMaker* parent) { babymaker = parent; }
            virtual void AddOutput();
            virtual void FillOutput();
    };
}

#endif
