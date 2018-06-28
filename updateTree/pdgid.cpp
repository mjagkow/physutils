#include "pdgid.h"

PDGId::Part PDGId::Part::Unknown(0, "unknown", "unknown");
PDGId::Part PDGId::Part::dQuark(1, "d", "d quark");
PDGId::Part PDGId::Part::uQuark(2, "u", "u quark");
PDGId::Part PDGId::Part::sQuark(3, "s", "s quark");
PDGId::Part PDGId::Part::cQuark(4, "c", "c quark");
PDGId::Part PDGId::Part::bQuark(5, "b", "b quark");
PDGId::Part PDGId::Part::tQuark(6, "t", "t quark");
PDGId::Part PDGId::Part::bPrimeQuark(7, "b'", "b' quark");
PDGId::Part PDGId::Part::tPrimeQuark(8, "t'", "t' quark");
PDGId::Part PDGId::Part::gluon({21, 9}, "g", "gluon");
PDGId::Part PDGId::Part::electron        (11, "e", "electron");
PDGId::Part PDGId::Part::electronNeutrino(12, "nu(e)", "electron neutrino");
PDGId::Part PDGId::Part::muon            (13, "mu", "muon");
PDGId::Part PDGId::Part::muonNeutrino    (14, "nu(mu)", "muon neutrino");
PDGId::Part PDGId::Part::tau             (15, "tau", "tau lepton");
PDGId::Part PDGId::Part::tauNeutrino     (16, "nu(tau)", "tau neutrino");
std::map<Int_t, PDGId::Part*> *PDGId::Part::reg = 0;
