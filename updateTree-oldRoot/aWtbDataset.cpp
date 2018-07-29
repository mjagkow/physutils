#include <string>
#include "aWtbDataset.h"
#include "pdgid.h"

Double_t aWtbDataset::make_cos(TLorentzVector a, TLorentzVector b, const TLorentzVector &rf) {
    static TVector3 p3a, p3b, boostVector;
    boostVector = rf.BoostVector();
    a.Boost(-boostVector);
    p3a = a.Vect();
    b.Boost(-boostVector);
    p3b = b.Vect();
    return p3a.Dot(p3b) / (p3a.Mag() * p3b.Mag());
}

Double_t aWtbDataset::make_cos_selfref(TLorentzVector a, const TLorentzVector &b_rf) {
    static TVector3 p3a, boostVector;
    boostVector = b_rf.BoostVector();
    a.Boost(-boostVector);
    p3a = a.Vect();
    return p3a.Dot(-boostVector) / (p3a.Mag() * boostVector.Mag());
}

void aWtbDataset::OnNextEntry(Long64_t entry) {
    if (abs(kf[id_t])  != PDGId::tQuark.id ||
        abs(kf[id_b])  != PDGId::bQuark.id ||
        abs(kf[id_mu]) != PDGId::muon.id   ||     
        abs(kf[id_nu]) != PDGId::muonNeutrino.id)
        throw std::runtime_error(std::string("Particle id mismatch in event ") + std::to_string(entry));

    // Intermediate variables
    t.SetPxPyPzE(px[id_t], py[id_t], pz[id_t], e[id_t]);
    b.SetPxPyPzE(px[id_b], py[id_b], pz[id_b], e[id_b]);
    mu.SetPxPyPzE(px[id_mu], py[id_mu], pz[id_mu], e[id_mu]);
    nu.SetPxPyPzE(px[id_nu], py[id_nu], pz[id_nu], e[id_nu]);
    W = mu + nu;
    t_reco = W + b;

    // Variables to be written to the tree
    Pt_t    = t_reco.Pt();
    Pt_b    = b.Pt();
    Pt_Lep  = mu.Pt();
    Pt_Nu   = nu.Pt();
    Pt_W    = W.Pt();
    Eta_t   = t_reco.Eta();
    Eta_Nu  = nu.Eta();
    Eta_Lep = mu.Eta();
    Eta_W   = W.Eta();
    Eta_b   = b.Eta();
    M_Inv   = t_reco.M();
    
    Cos_Lep_W_t = make_cos(mu, W, t_reco);
    Cos_Lep_W_W = make_cos_selfref(mu, W);
    Cos_Nu_W_t  = make_cos(nu, W, t_reco);
    Cos_Nu_W_W  = make_cos_selfref(nu, W);
    Cos_Lep_b_t = make_cos(mu, b, t_reco);
    Cos_Lep_b_W = make_cos(mu, b, W);
    Cos_Nu_b_t  = make_cos(nu, b, t_reco);
    Cos_Nu_b_W  = make_cos(nu, b, W);
}