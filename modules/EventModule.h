#ifndef EventModule_h
#define EventModule_h

#include "rooutil.h"
#include "wvzBabyMaker.h"

namespace wvzModule
{
    //__________________________________________________________________
    // Event
    class EventModule: public RooUtil::Module
    {
        public:
            wvzBabyMaker* babymaker;
            EventModule(wvzBabyMaker* parent) { babymaker = parent; }
            virtual void AddOutput();
            virtual void FillOutput();
    };
}

#endif
