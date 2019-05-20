#include "TChain.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TString.h"

#include "wvzBabyMaker.h"

#include "hadoopmap.h"

#include <iostream>

int main(int argc, char **argv)
{
    //
    // Parse options
    //
    if (argc < 2)
    {
        std::cout << "USAGE: processBaby <filename> [<max_num_events>] [index] [babymode] [type anything to make it verbose]" << std::endl;
        return 1;
    }

    TString infile(argv[1]);
    int max_events = -1;
    int index = 1;
    int babymode = 1;
    bool verbose = false;

    if (argc >= 3)
        max_events = atoi(argv[2]);

    if (argc >= 4)
        index = atoi(argv[3]);

    if (argc >= 5)
        babymode = atoi(argv[4]);

    if (argc >= 6)
        verbose = true;

    std::cout << "set max number of events to: " << max_events << std::endl;
    std::cout << "running on files: " << infile.Data() << std::endl;

    //
    // Run
    //
    wvzBabyMaker *looper = new wvzBabyMaker();
    switch (babymode)
    {
        case 1: looper->SetBabyMode(wvzBabyMaker::kWVZ); break;
        case 2: looper->SetBabyMode(wvzBabyMaker::kDilep); break;
    }
    looper->PrintBabyMode();
    looper->ProcessCMS4(infile, max_events, index, verbose);
    delete looper;
    return 0;
}
