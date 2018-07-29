#include "ROOTVar.h"
#include "dataset.h"

void Dataset::Connect(TTree *tree) {
    if (this->tree)
        throw std::runtime_error("Dataset is already connected");
    if (!tree)
        throw std::invalid_argument("Input tree is null");

    this->tree = tree;

    for (auto pvar : vars)
        pvar->SetBranchAddress(tree);

    for (auto pvar : new_vars)
        pvar->Branch(tree);
}


void Dataset::Fill() {
    for (auto pvar : new_vars) {
        pvar->Fill();
    }
}

void Dataset::GetEntry(Long64_t entry) {
    if (!tree)
        throw std::invalid_argument("Dataset is not connected to the tree");
    tree->GetEntry(entry);
    OnNextEntry(entry);
}

Long64_t Dataset::GetEntries() {
    if (!tree)
        throw std::invalid_argument("Dataset is not connected to the tree");
    return tree->GetEntries();
}

void Dataset::Write(const char *name, Int_t mode) {
    if (!tree)
        throw std::invalid_argument("Dataset is not connected to the tree");
    tree->Write(name, mode);
}