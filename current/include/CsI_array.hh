#ifndef CsI_array_H
#define CsI_array_H 1

#define NCsI 24
#include "G4Material.hh"
#include "Materials.hh"
#include "G4ThreeVector.hh"
#include "CsI_detector.hh"
#include "globals.hh"
#include "TrackerCsISD.hh"
#include "TrackerIonSD.hh"
#include <iostream>
#include <vector>
using namespace std;


class CsI_array 
{
  public:

  G4LogicalVolume *expHall_log;
  
  CsI_array(G4LogicalVolume*,Materials*);
  ~CsI_array();

  CsI_detector* GetCsIDetector(){return aCsI_detector=new CsI_detector(expHall_log,materials);};
  
  void Construct();
  void Report();
  void MakeSensitive(TrackerCsISD*);
  void setZPos(G4double z){zpos=z;Construct();};
  G4int getRingID(G4int id){return ring[id-1];};               // read ring by position = id-1
  void     SetBirksConstant(G4int id,G4double k){kB[id-1]=k;}; // set kB by position = id-1
  G4double GetBirksConstant(G4int id){return kB[id];};         // read kB by index id
  G4double GetLYScaling(G4int id){return S[id];};         // read S by index id
  G4double GetCsIDensity(){return materials->FindMaterial("G4_CESIUM_IODIDE")->GetDensity()/g*cm3;};

  private:

  vector<CsI_detector*> aCsI_array;
  CsI_detector* aCsI_detector;
  Materials* materials;
  G4int id[NCsI];
  G4int ring[NCsI];
  G4ThreeVector pos[NCsI];
  G4double zpos;
  G4double kB[NCsI]; // Birks constant in um/MeV
  G4double S[NCsI]; // scaling factor to convert LY to channel

};

#endif

