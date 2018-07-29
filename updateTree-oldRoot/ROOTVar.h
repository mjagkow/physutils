#pragma once
#include <TTree.h>

class ROOTVarBase {
protected:
    TTree *tree;
    TBranch *branch;
public:
    const char *name;
    virtual Int_t SetBranchAddress(TTree *t) = 0;
    virtual TBranch *Branch(TTree *t) = 0;
    void Fill();
};


template<typename T, const int TSize = 0>
class ROOTVar : public ROOTVarBase {
public:
    typedef typename std::conditional<(TSize > 0), T[TSize], T>::type VarType;

private:
    class BranchHelper0 {
    public:
        static Int_t SetBranchAddress(TTree *t, const char *name, VarType &value, TBranch **branch) {
            return t->SetBranchAddress(name, &value, branch);
        }
        static TBranch *Branch(TTree *t, const char *name, VarType &value) {
            return t->Branch(name, &value);
        }
    };

    class BranchHelper {
    public:
        static Int_t SetBranchAddress(TTree *t, const char *name, VarType &value, TBranch **branch) {
            return t->SetBranchAddress(name, value, branch);
        }
        static TBranch *Branch(TTree *t, const char *name, VarType &value) {
            return t->Branch(name, value);
        }
    };

public:
    VarType value;

    ROOTVar(const char *name) {
        this->name = name;
    }

    Int_t SetBranchAddress(TTree *tree) override {
        if (tree == 0)
            std::invalid_argument("Tree to branch from is null");
        if (this->tree != 0)
            std::runtime_error("Trying to overwrite existing bound tree");

        this->tree = tree;

        return std::conditional<(TSize > 0), BranchHelper, BranchHelper0 >::type::
            SetBranchAddress(this->tree, name, value, &branch);
    }

    TBranch *Branch(TTree *tree) override {
        if (tree == 0)
            std::invalid_argument("Tree to branch from is null");
        if (this->tree != 0)
            std::runtime_error("Trying to overwrite existing bound tree");

        this->tree = tree;

        branch = std::conditional<(TSize > 0), BranchHelper, BranchHelper0 >::type::
            Branch(this->tree, name, value);
        return branch;
    }
};