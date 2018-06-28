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
    // Vectors for cosine calculation
    TLorentzVector boostedLepton, boostedW;
    TVector3 p3Lepton, p3W, boostVector;
public:
    Double_t &Pt_Nu      = Create<Double_t>("Pt_Nu");
    Double_t &Pt_Lep     = Create<Double_t>("Pt_Lep");
    Double_t &Pt_t       = Create<Double_t>("Pt_t");
    Double_t &Pt_b       = Create<Double_t>("Pt_b");
    Double_t &Pt_W       = Create<Double_t>("Pt_W");
    Double_t &Pt_Nu_b    = Create<Double_t>("Pt_Nu_b");
    Double_t &Eta_Nu     = Create<Double_t>("Eta_Nu");
    Double_t &Eta_Lep    = Create<Double_t>("Eta_Lep");
    Double_t &M_Inv      = Create<Double_t>("M_Inv");
    Double_t &Cos_LepW_W = Create<Double_t>("Cos_LepW_W");
    Double_t &Cos_LepW_t = Create<Double_t>("Cos_LepW_t");
    
    aWtbDataset(int id_t, int id_b, int id_mu, int id_nu)
     : LHEDataset(), 
       id_t(id_t),
       id_b(id_b),
       id_mu(id_mu),
       id_nu(id_nu)
    { }
    
    TLorentzVector t, b, mu, nu, W, p1, p2, Nu_b, W_b;
    
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
        Nu_b = nu + b;
        W_b = W + b;

        // Variables to be written to the tree
        Pt_t = t.Pt();
        Pt_b = b.Pt();
        Pt_Lep = mu.Pt();
        Pt_Nu = nu.Pt();
        Pt_W = W.Pt();
        Pt_Nu_b = Nu_b.Pt();
        Eta_Nu = nu.Eta();
        Eta_Lep = mu.Eta();
        M_Inv = W_b.M();
        
        boostVector = t.BoostVector();
        boostedLepton = mu;
        boostedLepton.Boost(-boostVector);
        p3Lepton =boostedLepton.Vect();
        boostedW = W;
        boostedW.Boost(-boostVector);
        p3W = boostedW.Vect();
        Cos_LepW_t = p3Lepton.Dot(p3W) / (p3Lepton.Mag() * p3W.Mag());
        
        boostVector = W.BoostVector();
        boostedLepton = mu;
        boostedLepton.Boost(-boostVector);
        p3Lepton = boostedLepton.Vect();
        Cos_LepW_W = p3Lepton.Dot(-boostVector) / (p3Lepton.Mag() * boostVector.Mag());
    }
};

int main()
{
    gErrorIgnoreLevel=kError;
    aWtbDataset ds(4, 5, 3, 2);

    string inputFile = "vars.root";
    string treeName = "Tchep";

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
    }
    ds.Write("", TObject::kOverwrite);
    cout << "Successfully updated " << nEntries << " entries\n";
    return 0;
}


