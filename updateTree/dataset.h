#pragma once

#include <exception>
#include <vector>
#include "ROOTVar.h"

using std::vector;

class Dataset {
protected:
    TTree *tree;
    vector<ROOTVarBase*> newVars;
    vector<ROOTVarBase*> vars;
public:
    template<typename T, int TSize = 0>
    typename ROOTVar<T, TSize>::VarType& add(const char *name) {
        ROOTVar<T, TSize> *v = new ROOTVar<T, TSize>(name);
        vars.push_back(v);
        if (tree) {
            v->SetBranchAddress(tree);
        }
        return v->value;
    }
    
    template<typename T, int TSize = 0>
    typename ROOTVar<T, TSize>::VarType& Create(const char *name) {
        ROOTVar<T, TSize> *v = new ROOTVar<T, TSize>(name);
        newVars.push_back(v);
        if (tree) {
            v->Branch(tree);
        }
        return v->value;
    }

    void Connect(TTree *tree) {
        if (tree == 0)
            throw std::invalid_argument("Input tree is null");
        if (this->tree != 0)
            throw std::runtime_error("Local tree is not null");

        this->tree = tree;
        
        for (auto v : vars)
            v->SetBranchAddress(this->tree);

        for (auto v : newVars)
            v->Branch(this->tree);
    }

    virtual void OnNextEntry(Long64_t entry) { }

    void GetEntry(Long64_t entry) {
        if (tree == 0)
            throw std::invalid_argument("The tree is null");
        tree->GetEntry(entry);
        OnNextEntry(entry);
    }

    Long64_t GetEntries() {
        if (tree == 0)
            throw std::invalid_argument("The tree is null");
        return tree->GetEntries();
    }

    void Fill() {
        for (auto v : newVars) {
            v->branch->Fill();
        }
    }

    void Write(const char *name, Int_t mode) {
        if (tree)
            tree->Write(name, mode);
    }
};
