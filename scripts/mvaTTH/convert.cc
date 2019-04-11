#include "rooutil.h"
#include "cxxopts.h"

int main(int argc, char** argv)
{

    // cxxopts is just a tool to parse argc, and argv easily

    // Grand option setting
    cxxopts::Options options("\n  $ ttreescan",  "\n         **********************\n         *                    *\n         *  TTreeScan Dumper  *\n         *                    *\n         **********************\n");

    // Read the options
    options.add_options()
        ("i,input"       , "Comma separated input file list OR if just a directory is provided it will glob all in the directory BUT must end with '/' for the path", cxxopts::value<std::string>())
        ("o,output"      , "Output file name"                                                                                    , cxxopts::value<std::string>())
        ("h,help"        , "Print help")
        ;

    auto result = options.parse(argc, argv);

    // NOTE: When an option was provided (e.g. -i or --input), then the result.count("<option name>") is more than 0
    // Therefore, the option can be parsed easily by asking the condition if (result.count("<option name>");
    // That's how the several options are parsed below

    //_______________________________________________________________________________
    // --help
    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(1);
    }

    //_______________________________________________________________________________
    // --input
    TString input = "";
    if (result.count("input"))
    {
        input = result["input"].as<std::string>();
    }
    else
    {
        std::cout << options.help() << std::endl;
        std::cout << "ERROR: Input list is not provided! Check your arguments" << std::endl;
        exit(1);
    }

    //_______________________________________________________________________________
    // --output
    TString output = "";
    if (result.count("output"))
    {
        output = result["output"].as<std::string>();
    }
    else
    {
        std::cout << options.help() << std::endl;
        std::cout << "ERROR: Output path is not provided! Check your arguments" << std::endl;
        exit(1);
    }

    ifstream ifile;
    ifile.open( input.Data() );
    std::string line;
    std::map<std::vector<int>, std::vector<float>> varmap;

    while ( std::getline( ifile, line ) )
    {
        TString rawline = line;
        if (rawline.Contains("***"))
            continue;
        if (rawline.Contains("lumi"))
            continue;

        std::vector<TString> items = RooUtil::StringUtil::split(rawline, "*");
        int key1 = items[2].Atoi();
        int key2 = items[3].Atoi();
        int key3 = items[4].Atoi();
        float data1 = items[5].Atof();
        float data2 = items[6].Atof();
        varmap[{key1, key2, key3}].push_back(data1);
        varmap[{key1, key2, key3}].push_back(data2);

    }

    ofstream outfile;
    outfile.open( output.Data() );

    for (auto& pair : varmap)
    {

        std::vector<TString> items;
        for (auto& key : pair.first)
            items.push_back(TString::Format("%d", key));
        for (auto& data : pair.second)
            items.push_back(TString::Format("%f", data));
        outfile << RooUtil::StringUtil::join(items,":").Data() << std::endl;
    }

}
