#pragma once

#include <exception>
#include <TTree.h>

class ROOTVarBase {
protected:
    TTree *tree = 0;
public:
    const char *name;
    TBranch *branch;
    virtual Int_t SetBranchAddress(TTree *t) = 0;
    virtual void Branch(TTree *t) = 0;
};

template<typename T, const int TSize = 0>
class ROOTVar : public ROOTVarBase {
    template<typename X>
    class BranchHelper0 {
    public:
        static Int_t SetBranchAddress(TTree *t, const char *name, X &value, TBranch **branch) {
            return t->SetBranchAddress(name, &value, branch);
        }
        static TBranch *Branch(TTree *t, const char *name, X &value) {
            return t->Branch(name, &value);
        }
    };

    template<typename X>
    class BranchHelper {
    public:
        static Int_t SetBranchAddress(TTree *t, const char *name, X &value, TBranch **branch) {
            return t->SetBranchAddress(name, value, branch);
        }
        static TBranch *Branch(TTree *t, const char *name, X &value) {
            return t->Branch(name, value);
        }
    };

public:
    typedef typename std::conditional<(TSize > 0), T[TSize], T>::type VarType;
    VarType value;

    ROOTVar(const char *name)
    {
        this->name = name;
    }



    Int_t SetBranchAddress(TTree *tree) {
        if (tree == 0)
            std::invalid_argument("Tree to branch from is null");
        if (this->tree != 0)
            std::runtime_error("Trying to overwrite existing bound tree");

        this->tree = tree;

        Int_t val = std::conditional<(TSize > 0), BranchHelper<VarType>, BranchHelper0<VarType> >::type::
            SetBranchAddress(this->tree, name, value, &branch);
        return val;
    }

    void Branch(TTree *tree) {
        if (tree == 0)
            std::invalid_argument("Tree to branch from is null");
        if (this->tree != 0)
            std::runtime_error("Trying to overwrite existing bound tree");

        this->tree = tree;

        branch = std::conditional<(TSize > 0), BranchHelper<VarType>, BranchHelper0<VarType> >::type::
            Branch(this->tree, name, value);
    }
};

