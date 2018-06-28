#pragma once 

#include "dataset.h"

template<int NPart>
class LHEDataset : public Dataset {
public:
    Int_t     & nprt             = add<Int_t>("nprt");
    Int_t     & procid           = add<Int_t>("procid");
    Double_t  & weight           = add<Double_t>("weight");
    Double_t  & scale            = add<Double_t>("scale");
    Double_t  & QEDalpha         = add<Double_t>("QEDalpha");
    Double_t  & QCDalpha         = add<Double_t>("QCDalpha");
    Int_t    (& kf      )[NPart] = add<Int_t, NPart>("kf");
    Int_t    (& status  )[NPart] = add<Int_t, NPart>("status");
    Int_t    (& mother1 )[NPart] = add<Int_t, NPart>("mother1");
    Int_t    (& mother2 )[NPart] = add<Int_t, NPart>("mother2");
    Int_t    (& color1  )[NPart] = add<Int_t, NPart>("color1");
    Int_t    (& color2  )[NPart] = add<Int_t, NPart>("color2");
    Double_t (& px      )[NPart] = add<Double_t, NPart>("px");
    Double_t (& py      )[NPart] = add<Double_t, NPart>("py");
    Double_t (& pz      )[NPart] = add<Double_t, NPart>("pz");
    Double_t (& e       )[NPart] = add<Double_t, NPart>("e");
    Double_t (& m       )[NPart] = add<Double_t, NPart>("m");
    Double_t (& lifetime)[NPart] = add<Double_t, NPart>("lifetime");
    Double_t (& spin    )[NPart] = add<Double_t, NPart>("spin");
    
    LHEDataset() : Dataset()
    { }
};
