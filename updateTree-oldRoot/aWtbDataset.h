#pragma once
#include <TLorentzVector.h>
#include "lhe_dataset.h"


class aWtbDataset : public LHEDataset<6> {
protected:
    // Particle indices in LHE data arrays
    int id_t, id_b, id_mu, id_nu;
public:
    TLorentzVector t, b, mu, nu, W, t_reco;

    Double_t &Pt_Nu       = create<Double_t>("Pt_Nu");
    Double_t &Pt_Lep      = create<Double_t>("Pt_Lep");
    Double_t &Pt_t        = create<Double_t>("Pt_t");
    Double_t &Pt_b        = create<Double_t>("Pt_b");
    Double_t &Pt_W        = create<Double_t>("Pt_W");
    Double_t &Eta_Nu      = create<Double_t>("Eta_Nu");
    Double_t &Eta_Lep     = create<Double_t>("Eta_Lep");
    Double_t &Eta_t       = create<Double_t>("Eta_t");
    Double_t &Eta_b       = create<Double_t>("Eta_b");
    Double_t &Eta_W       = create<Double_t>("Eta_W");
    Double_t &M_Inv       = create<Double_t>("M_Inv");
    Double_t &Cos_Lep_W_W = create<Double_t>("Cos_Lep_W_W");
    Double_t &Cos_Lep_W_t = create<Double_t>("Cos_Lep_W_t");
    Double_t &Cos_Nu_W_W  = create<Double_t>("Cos_Nu_W_W");
    Double_t &Cos_Nu_W_t  = create<Double_t>("Cos_Nu_W_t");
    Double_t &Cos_Lep_b_W = create<Double_t>("Cos_Lep_b_W");
    Double_t &Cos_Lep_b_t = create<Double_t>("Cos_Lep_b_t");
    Double_t &Cos_Nu_b_W  = create<Double_t>("Cos_Nu_b_W");
    Double_t &Cos_Nu_b_t  = create<Double_t>("Cos_Nu_b_t");
    
    aWtbDataset(int id_t, int id_b, int id_mu, int id_nu)
     : LHEDataset(), 
       id_t(id_t),
       id_b(id_b),
       id_mu(id_mu),
       id_nu(id_nu)
    { }


    static Double_t make_cos(TLorentzVector a, TLorentzVector b, const TLorentzVector &rf);
    static Double_t make_cos_selfref(TLorentzVector a, const TLorentzVector &b_rf);
    
    void OnNextEntry(Long64_t entry) override;
};