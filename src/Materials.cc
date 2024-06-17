#include "Materials.hh"

 Materials:: Materials()
{
  G4NistManager* man = G4NistManager::Instance();
  man->SetVerbose(1);
 
  // Elemental materials
  Al = man->FindOrBuildMaterial("G4_Al");
  Au = man->FindOrBuildMaterial("G4_Au");
  Be = man->FindOrBuildMaterial("G4_Be"); 
  C = man->FindOrBuildMaterial("G4_C");
  Oxygen18 = new G4Material("O18",8.,17.999*g/mole, 1.141*g/cm3);
  Cu = man->FindOrBuildMaterial("G4_Cu");
  Ca = new G4Material("Ca40", 20., 40.08*g/mole, 1.55*g/cm3);
  G4Ca = man->FindOrBuildMaterial("G4_Ca");
  Ge = man->FindOrBuildMaterial("G4_Ge");
  In = man->FindOrBuildMaterial("G4_In");
  H = man->FindOrBuildMaterial("G4_H");
  He = man->FindOrBuildMaterial("G4_He");
  Hf = man->FindOrBuildMaterial("G4_Hf");
  Li = man->FindOrBuildMaterial("G4_Li");
  Mg = man->FindOrBuildMaterial("G4_Mg");
  Ni = man->FindOrBuildMaterial("G4_Ni");
  S = man->FindOrBuildMaterial("G4_S");
  Ta = man->FindOrBuildMaterial("G4_Ta");
  Ag = man->FindOrBuildMaterial("G4_Ag");
  Pb = man->FindOrBuildMaterial("G4_Pb");
  
  // Compounds
  Vacuum = man->FindOrBuildMaterial("G4_Galactic");
  BGO    = man->FindOrBuildMaterial("G4_BGO");
  CH2    = man->FindOrBuildMaterial("G4_POLYETHYLENE");
  CsI    = man->FindOrBuildMaterial("G4_CESIUM_IODIDE");
  Mylar  = man->FindOrBuildMaterial("G4_MYLAR");
  Air    = man->FindOrBuildMaterial("G4_AIR");
  
  
  //Materials
  UserCarbon  = new G4Material("UserCarbon",   6, 12.011*g/mole,   2.15*g/cm3);
  UserGold  = new G4Material("UserGold",   79, 196.97*g/mole,   19.311*g/cm3);
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
