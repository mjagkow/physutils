#pragma once
#include <map>
#include <vector>
#include "Rtypes.h"

class PDGId {
public:
    class Part {
    protected:
        friend class PDGId;
        static std::map<Int_t, Part*> reg;

        Part(Int_t id, const char *name, const char *longName);
        Part(std::initializer_list<Int_t> ids, const char *name, const char *longName);
        static void Register(Part &p);
    
    public:
        const std::vector<Int_t> ids;
        const Int_t id;
        const char *name;
        const char *longName;
        
        static const Part &ById(Int_t id) {
            return *reg.at(id);
        }
    };

    static Part Unknown;
    static Part dQuark;
    static Part uQuark;
    static Part sQuark;
    static Part cQuark;
    static Part bQuark;
    static Part tQuark;
    static Part bPrimeQuark;
    static Part tPrimeQuark;
    static Part gluon;
    static Part electron;
    static Part electronNeutrino;
    static Part muon;
    static Part muonNeutrino;
    static Part tau;
    static Part tauNeutrino;
};
