#pragma once 
#include "dataset.h"

template<int NPart>
class LHEDataset : public Dataset {
    template<typename Type>
    struct A { typedef Type (&T)[NPart]; };
public:
    Int_t    &nprt     = add<Int_t   >("nprt");
    Int_t    &procid   = add<Int_t   >("procid");
    Double_t &weight   = add<Double_t>("weight");
    Double_t &scale    = add<Double_t>("scale");
    Double_t &QEDalpha = add<Double_t>("QEDalpha");
    Double_t &QCDalpha = add<Double_t>("QCDalpha");
    typename A<Int_t   >::T  kf, status, mother1, mother2, color1, color2;
    typename A<Double_t>::T  px, py, pz, e, m, lifetime, spin;

    LHEDataset() :
      Dataset(),
      kf      (add<Int_t   , NPart>("kf")),
      status  (add<Int_t   , NPart>("status")),
      mother1 (add<Int_t   , NPart>("mother1")),
      mother2 (add<Int_t   , NPart>("mother2")),
      color1  (add<Int_t   , NPart>("color1")),
      color2  (add<Int_t   , NPart>("color2")),
      px      (add<Double_t, NPart>("px")),
      py      (add<Double_t, NPart>("py")),
      pz      (add<Double_t, NPart>("pz")),
      e       (add<Double_t, NPart>("e")),
      m       (add<Double_t, NPart>("m")),
      lifetime(add<Double_t, NPart>("lifetime")),
      spin    (add<Double_t, NPart>("spin"))
    { }
};
