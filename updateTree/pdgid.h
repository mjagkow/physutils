#pragma once

#include "Rtypes.h"
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <sstream>

class PDGId {
public:
    class Part {
    protected:
        static std::map<Int_t, Part*> *reg;

        Part(Int_t Id, const char *name, const char *longName) {
            this->Id = Id;
            this->Ids.push_back(Id);
            this->name = name;
            this->longName = longName;
            if (Id)
                Register(*this);
        }
        
        
        Part(std::initializer_list<Int_t> Ids, const char *name, const char *longName) {
            this->Id = *Ids.begin();
            this->Ids = std::vector<Int_t>(Ids);
            this->name = name;
            this->longName = longName;
            if (this->Id)
                Register(*this);
        }

        static void Register(Part &p) {
            if (!reg)
                reg = new std::map<Int_t, Part*>;
            for (Int_t id : p.Ids) {
                if (reg->find(id) != reg->end()) {
                    std::stringstream s;
                    s << "Trying to add duplicate id to the registry: " << p.longName << " with id=" << id << " (reserved for " << reg->at(id)->longName << ")\n";
                    throw std::invalid_argument(s.str());
                }
                reg->insert(std::make_pair(id, &p));
            }
        }

    
    public:
        std::vector<Int_t> Ids;
        Int_t Id;
        const char *name;
        const char *longName;
        
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
        
        
        static const Part &ParticleByID(Int_t id) {
            return *reg->at(id);
        }
    };

};
