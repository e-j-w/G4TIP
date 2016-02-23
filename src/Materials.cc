#include "Materials.hh"

 Materials:: Materials()
{
  G4NistManager* man = G4NistManager::Instance();
  man->SetVerbose(1);
 
  // Elemental materials
  Al = man->FindOrBuildMaterial("G4_Al");
  Ge = man->FindOrBuildMaterial("G4_Ge"); 
  Cu = man->FindOrBuildMaterial("G4_Cu");
  C = man->FindOrBuildMaterial("G4_C");
  Au = man->FindOrBuildMaterial("G4_Au");
  
  // Compounds
  Vacuum = man->FindOrBuildMaterial("G4_Galactic");
  BGO    = man->FindOrBuildMaterial("G4_BGO");
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
