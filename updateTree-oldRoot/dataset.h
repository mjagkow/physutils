#pragma once
#include <vector>
#include "ROOTVar.h"

class Dataset {
protected:
    TTree *tree;
    std::vector<ROOTVarBase*> vars;
    std::vector<ROOTVarBase*> new_vars;

    template<typename T, int TSize = 0>
    typename ROOTVar<T, TSize>::VarType &add(const char *name) {
        auto pvar = new ROOTVar<T, TSize>(name);
        vars.push_back(pvar);
        if (tree != 0)
            pvar->SetBranchAddress(tree);
        return pvar->value;
    }

    template<typename T, int TSize = 0>
    typename ROOTVar<T, TSize>::VarType &create(const char *name) {
        auto pvar = new ROOTVar<T, TSize>(name);
        new_vars.push_back(pvar);
        if (tree != 0)
            pvar->Branch(tree);
        return pvar->value;
    }

public:
    virtual void Connect(TTree *tree);
    virtual void OnNextEntry(Long64_t entry) { }
    virtual void Fill();

    Long64_t GetEntries();
    void GetEntry(Long64_t entry);
    void Write(const char *name, Int_t mode);
};
