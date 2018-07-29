#include <string>
#include <iostream>
#include "TFile.h"
#include "aWtbDataset.h"

int main(int argc, char **argv)
{
    gErrorIgnoreLevel=kError;
    std::string fileName("vars.root");
    std::string treeName("Tchep");

    if (argc > 1)
        fileName = argv[1];

    TFile file(fileName.c_str(), "update");
    if (file.IsZombie()) {
        std::cout << "File '" << fileName << "' is marked as Zombie; ignoring\n";
        return 1;
    }
    std::cout << "Opened '" << fileName << "' for update" << std::endl;

    TTree *t = dynamic_cast<TTree *>(file.Get(treeName.c_str()));
    aWtbDataset ds(4, 5, 3, 2);
    ds.Connect(t);

    Long64_t const nEntries = ds.GetEntries();
    for (Long64_t ev = 0; ev < nEntries; ++ev)
    {
        ds.GetEntry(ev);
        ds.Fill();
        if (ev % 1000 == 0)
            std::cout << "Processed " << ev << " events\r" << std::flush;
    }

    ds.Write("", TObject::kOverwrite);
    std::cout << "Successfully updated " << nEntries << " events" << std::endl;

    return 0;
}


