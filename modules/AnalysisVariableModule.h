#ifndef AnalysisVariableModule_h
#define AnalysisVariableModule_h

#include "rooutil.h"
#include "wvzBabyMaker.h"

namespace wvzModule
{
    //__________________________________________________________________
    // AnalysisVariable module
    class AnalysisVariableModule: public RooUtil::Module
    {
        public:
            wvzBabyMaker* babymaker;
            AnalysisVariableModule(wvzBabyMaker* parent) { babymaker = parent; }
            virtual void AddOutput();
            virtual void FillOutput();
    };
}

#endif
