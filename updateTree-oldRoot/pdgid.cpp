#include "pdgid.h"
#include <sstream>
#include <iostream>

std::map<Int_t, PDGId::Part*> PDGId::Part::reg = std::map<Int_t, PDGId::Part*>();
PDGId::Part PDGId::Unknown(0, "unknown", "unknown");
PDGId::Part PDGId::dQuark(1, "d", "d quark");
PDGId::Part PDGId::uQuark(2, "u", "u quark");
PDGId::Part PDGId::sQuark(3, "s", "s quark");
PDGId::Part PDGId::cQuark(4, "c", "c quark");
PDGId::Part PDGId::bQuark(5, "b", "b quark");
PDGId::Part PDGId::tQuark(6, "t", "t quark");
PDGId::Part PDGId::bPrimeQuark(7, "b'", "b' quark");
PDGId::Part PDGId::tPrimeQuark(8, "t'", "t' quark");
PDGId::Part PDGId::gluon({21, 9}, "g", "gluon");
PDGId::Part PDGId::electron        (11, "e", "electron");
PDGId::Part PDGId::electronNeutrino(12, "nu(e)", "electron neutrino");
PDGId::Part PDGId::muon            (13, "mu", "muon");
PDGId::Part PDGId::muonNeutrino    (14, "nu(mu)", "muon neutrino");
PDGId::Part PDGId::tau             (15, "tau", "tau lepton");
PDGId::Part PDGId::tauNeutrino     (16, "nu(tau)", "tau neutrino");


PDGId::Part::Part(Int_t id, const char *name, const char *longName) :
    id(id),
    ids({id}),
    name(name),
    longName(longName)
{
    Register(*this);
}


PDGId::Part::Part(std::initializer_list<Int_t> ids, const char *name, const char *longName) :
    ids(ids),
    id(*this->ids.begin()),
    name(name),
    longName(longName)
{
    Register(*this);
}

void PDGId::Part::Register(Part &p) {
    for (Int_t id : p.ids) {
        if (reg.find(id) != reg.end()) {
            std::stringstream s;
            s << "Trying to add duplicate id to the registry: " << p.longName << " with id=" << id << " (reserved for " << reg.at(id)->longName << ")\n";
            throw std::invalid_argument(s.str());
        }
        reg.insert(std::make_pair(id, &p));
    }
}