#include "Materials.hh"

 Materials:: Materials()
{

  

 // Elements
 
  elementH  = new G4Element("Hydrogen",  "H",  1.,  1.0079*g/mole);
  elementC  = new G4Element("Carbon",    "C",  6.,  12.011*g/mole);
  elementN  = new G4Element("Nitrogen",  "N",  7.,  14.007*g/mole);
  elementO  = new G4Element("Oxygen",    "O",  8., 15.9994*g/mole);
  elementMg = new G4Element("Magnesium", "Mg",12., 24.3050*g/mole);
  elementAl = new G4Element("Aluminium", "Al",13., 26.9815*g/mole);
  elementSi = new G4Element("Silicon",   "Si",14., 28.0855*g/mole);
  elementTi = new G4Element("Titanium",  "Ti",22.,   47.90*g/mole);
  elementV  = new G4Element("Vanadium",  "V", 23., 50.9415*g/mole);
  elementFe = new G4Element("Iron",      "Fe",26.,  55.845*g/mole);
  elementMo = new G4Element("Molybdenum","Mo",42.,   95.94*g/mole);
  elementPt = new G4Element("Platinum",  "Pt",78.,  195.08*g/mole);
  elementAu = new G4Element("Gold",      "Au",79.,  196.97*g/mole);
  elementCs = new G4Element("Cesium",    "Cs",55.,  132.91*g/mole);
  elementI =  new G4Element("Iodine",    "I", 53.,  126.90*g/mole);
  elementCa = new G4Element("Calcium",   "Ca",20.,   40.08*g/mole);
  elementGe = new G4Element("Germanium", "Ge", 32., 72.64*g/mole);
  elementBi = new G4Element("Bismuth",  "Bi", 83., 208.98*g/mole);
 
// Materials

  Vacuum = new G4Material("Vacuum", 1, 1.00794*g/mole, 
     1.0E-25*g/cm3, kStateGas, 0.1*kelvin, 1.0E-19*pascal);

  Al = new G4Material("Aluminum", 13, 26.98153*g/mole, 2.70*g/cm3);
  Nb = new G4Material("Niobium", 41, 92.90638*g/mole, 8.57*g/cm3);
  C  = new G4Material("Carbon",   6, 12.011*g/mole,   2.15*g/cm3);
  Au = new G4Material("Gold", 79., 196.9*g/mole, 19.32*g/cm3);
  Be = new G4Material("Berylium", 4, 9.012182*g/mole, 1.84*g/cm3);
  Si = new G4Material("Silicon", 14., 28.0855*g/mole, 2.33*g/cm3);
  Ir = new G4Material("Irridium", 77., 192.217*g/mole, 22.65*g/cm3);
  Ca = new G4Material("Calcium", 20., 40.08*g/mole, 1.55*g/cm3);
  Ge = new G4Material("Germanium",32.,72.64*g/mole,5.323 *g/cm3);
  Cu = new G4Material("Copper", 29., 63.546*g/mole, 8.960*g/cm3);

  BGO = new G4Material("BGO",7.3*g/cm3, 3);
  BGO->AddElement(elementBi, 4);    
  BGO->AddElement(elementGe, 3);    
  BGO->AddElement(elementO, 12);

  scintCsI = new G4Material("CesiumIodide", 4.53*g/cm3,2);
  scintCsI->AddElement(elementCs,1);
  scintCsI->AddElement(elementI,1);

  polyethylene = new G4Material("polyethylene",0.935*g/cm3,2);
  polyethylene->AddElement(elementC,1);
  polyethylene->AddElement(elementH,2);

  Air = new G4Material("Air", 1.29*mg/cm3, 2);
  Air->AddElement(elementN, .7);
  Air->AddElement(elementO, .3);


}

 Materials::~ Materials()
{;}
//-----------------------------------------------------------------------------
G4Material*  Materials::FindMaterial(G4String materialName)
{


   // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  

  return pttoMaterial;
  
}
