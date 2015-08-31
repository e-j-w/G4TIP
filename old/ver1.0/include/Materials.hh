#ifndef Materials_H
#define Materials_H 1

#include "G4Material.hh"

class Materials 
{
  public:


  Materials();
  ~Materials();
  
  G4Material* FindMaterial(G4String );
    
    private:
  // Elements
 
  G4Element* elementH;
  G4Element* elementC;
  G4Element* elementN;
  G4Element* elementO;
  G4Element* elementMg;
  G4Element* elementAl;
  G4Element* elementSi;
  G4Element* elementTi;
  G4Element* elementV;
  G4Element* elementFe;
  G4Element* elementMo;
  G4Element* elementPt;
  G4Element* elementAu;
  G4Element* elementCs;
  G4Element* elementI;
  G4Element* elementCa;
  G4Element* elementGe;
  G4Element* elementBi;
// Materials

  G4Material* Vacuum;
  G4Material* Air;
  G4Material* Al;
  G4Material* Nb;
  G4Material* C;
  G4Material* Au;
  G4Material* Ir;
  G4Material* Si;
  G4Material* Be;
  G4Material* scintCsI;
  G4Material* Ca;
  G4Material* Ge;
  G4Material* Cu;
  G4Material* BGO;
  G4Material* polyethylene;


};

#endif

