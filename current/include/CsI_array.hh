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
  
  void Construct();
  void Report();
  void MakeSensitive(TrackerCsISD*);
  void setZPos(G4double z){zpos=z;Construct();};
  G4int getRingID(G4int i){return ring[i];};
    private:
 
  vector<CsI_detector*> aCsI_array;
  //materials
  Materials* materials;
  G4int id[NCsI];
  G4int ring[NCsI];
  G4ThreeVector pos[NCsI];
  G4double zpos;
 

};

#endif

