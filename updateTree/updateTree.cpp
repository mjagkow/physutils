#include <TFile.h>
#include <TTree.h>
#include <TLorentzVector.h>

#include <string>
#include <vector>
#include <iostream>
#include <type_traits>
#include <cassert>
#include <cmath>

#include "lhe_dataset.h"
#include "pdgid.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;



class aWtbDataset : public LHEDataset<6> {
protected:
    // Internal and intermediate variables
    // Particle indices in LHE data arrays
    int id_t, id_b, id_mu, id_nu;
public:
    Double_t &Pt_Nu       = Create<Double_t>("Pt_Nu");
    Double_t &Pt_Lep      = Create<Double_t>("Pt_Lep");
    Double_t &Pt_t        = Create<Double_t>("Pt_t");
    Double_t &Pt_b        = Create<Double_t>("Pt_b");
    Double_t &Pt_W        = Create<Double_t>("Pt_W");
    Double_t &Eta_Nu      = Create<Double_t>("Eta_Nu");
    Double_t &Eta_Lep     = Create<Double_t>("Eta_Lep");
    Double_t &Eta_t       = Create<Double_t>("Eta_t");
    Double_t &Eta_b       = Create<Double_t>("Eta_b");
    Double_t &Eta_W       = Create<Double_t>("Eta_W");
    Double_t &M_Inv       = Create<Double_t>("M_Inv");
    Double_t &Cos_Lep_W_W = Create<Double_t>("Cos_Lep_W_W");
    Double_t &Cos_Lep_W_t = Create<Double_t>("Cos_Lep_W_t");
    Double_t &Cos_Nu_W_W  = Create<Double_t>("Cos_Nu_W_W");
    Double_t &Cos_Nu_W_t  = Create<Double_t>("Cos_Nu_W_t");
    Double_t &Cos_Lep_b_W = Create<Double_t>("Cos_Lep_b_W");
    Double_t &Cos_Lep_b_t = Create<Double_t>("Cos_Lep_b_t");
    Double_t &Cos_Nu_b_W  = Create<Double_t>("Cos_Nu_b_W");
    Double_t &Cos_Nu_b_t  = Create<Double_t>("Cos_Nu_b_t");
    
    aWtbDataset(int id_t, int id_b, int id_mu, int id_nu)
     : LHEDataset(), 
       id_t(id_t),
       id_b(id_b),
       id_mu(id_mu),
       id_nu(id_nu)
    { }
    
    TLorentzVector t, b, mu, nu, W, t_reco;

    Double_t make_cos(TLorentzVector a, TLorentzVector b, const TLorentzVector &rf) {
        static TVector3 p3a, p3b, boostVector;
        boostVector = rf.BoostVector();
        a.Boost(-boostVector);
        p3a = a.Vect();
        b.Boost(-boostVector);
        p3b = b.Vect();
        return p3a.Dot(p3b) / (p3a.Mag() * p3b.Mag());
    }

    Double_t make_cos_selfref(TLorentzVector a, const TLorentzVector &b_rf) {
        static TVector3 p3a, boostVector;
        boostVector = b_rf.BoostVector();
        a.Boost(-boostVector);
        p3a = a.Vect();
        return p3a.Dot(-boostVector) / (p3a.Mag() * boostVector.Mag());
    }
    
    void OnNextEntry(Long64_t entry) override {
        assert(abs(kf[id_t])  == PDGId::Part::tQuark.Id);       // Check if particle is top quark
        assert(abs(kf[id_b])  == PDGId::Part::bQuark.Id);       // Check if particle is b quark
        assert(abs(kf[id_mu]) == PDGId::Part::muon.Id);         // Check if particle is muon
        assert(abs(kf[id_nu]) == PDGId::Part::muonNeutrino.Id); // Check if particle is muon neutrino

        // Intermediate variables
        t.SetPxPyPzE(px[id_t], py[id_t], pz[id_t], e[id_t]);
        b.SetPxPyPzE(px[id_b], py[id_b], pz[id_b], e[id_b]);
        mu.SetPxPyPzE(px[id_mu], py[id_mu], pz[id_mu], e[id_mu]);
        nu.SetPxPyPzE(px[id_nu], py[id_nu], pz[id_nu], e[id_nu]);
        W = mu + nu;
        t_reco = W + b;

        // Variables to be written to the tree
        Pt_t = t_reco.Pt();
        Pt_b = b.Pt();
        Pt_Lep = mu.Pt();
        Pt_Nu = nu.Pt();
        Pt_W = W.Pt();
        Eta_t = t_reco.Eta();
        Eta_Nu = nu.Eta();
        Eta_Lep = mu.Eta();
        Eta_W = W.Eta();
        Eta_b = b.Eta();
        M_Inv = t_reco.M();
        
        Cos_Lep_W_t = make_cos(mu, W, t_reco);
        Cos_Lep_W_W = make_cos_selfref(mu, W);
        Cos_Nu_W_t  = make_cos(nu, W, t_reco);
        Cos_Nu_W_W  = make_cos_selfref(nu, W);
        Cos_Lep_b_t = make_cos(mu, b, t_reco);
        Cos_Lep_b_W = make_cos(mu, b, W);
        Cos_Nu_b_t  = make_cos(nu, b, t_reco);
        Cos_Nu_b_W  = make_cos(nu, b, W);
    }
};

int main(int argc, char **argv)
{
    gErrorIgnoreLevel=kError;
    aWtbDataset ds(4, 5, 3, 2);

    string inputFile("vars.root");
    if (argc > 1)
        inputFile = argv[1];

    string treeName("Tchep");

    TFile f(inputFile.c_str(), "update");
    if (f.IsZombie()) {
        cout << "File is marked as Zombie; ignoring\n";
        return 1;
    }
    cout << "Opened '" << inputFile << "' for update" << endl;
    TTree *t = dynamic_cast<TTree *>(f.Get(treeName.c_str()));

    ds.Connect(t);
    Long64_t const nEntries = ds.GetEntries();
    for (Long64_t ev = 0; ev < nEntries; ++ev)
    {
        ds.GetEntry(ev);
        ds.Fill();
        if (ev % 1000 == 0)
            cout << "Processed " << ev << " events\r";
    }
    ds.Write("", TObject::kOverwrite);
    cout << "Successfully updated " << nEntries << " entries\n";
    return 0;
}


