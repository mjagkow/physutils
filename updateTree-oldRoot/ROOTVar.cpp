#include "ROOTVar.h"

void ROOTVarBase::Fill() {
    if (!branch)
        throw std::runtime_error("Corresponding branch doesn't exist");
    branch->Fill();
}