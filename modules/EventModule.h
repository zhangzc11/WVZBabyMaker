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

float getTruePUw2016(int nvtx);
float getTruePUwUp2016(int nvtx);
float getTruePUwDn2016(int nvtx);
float getTruePUw2017(int nvtx);
float getTruePUwUp2017(int nvtx);
float getTruePUwDn2017(int nvtx);
float getTruePUw2018(int nvtx);
float getTruePUwUp2018(int nvtx);
float getTruePUwDn2018(int nvtx);

#endif
