#ifndef Chamber_H
#define Chamber_H 1

#include "G4Material.hh"
#include "Materials.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4UnitsTable.hh"
#include "G4SubtractionSolid.hh"

using namespace CLHEP;

class Chamber 
{
  public:

  G4LogicalVolume *expHall_log;

  Chamber(G4LogicalVolume*,Materials*);
  ~Chamber();
  
  G4VPhysicalVolume *Construct();
//   void setRmin(G4double);
//   void setRmax(G4double);
  void setMaterial(G4String);
  void setVisible();
  void setInvisible();
  void Report();
  void SetPosZ(G4double);
  G4double GetPosZ();
  
    private:
  // dimensions
  G4double BTrmin;
  G4double BTrmax;
  G4double BTSPhi;
  G4double BTDPhi; 
  G4double BTSTheta;
  G4double BTDTheta; 
  G4double portOpening;

  //materials
  Materials* materials;
  G4Material* Chamber_Material;

  //default position
  G4RotationMatrix NoRot;
  G4ThreeVector *Pos0;

  //the shell
  G4Sphere* shell;
  G4Tubs*   pipe;

  //logical volume
  G4SubtractionSolid* Chamber_shell;
  G4LogicalVolume* Chamber_log;
 
  //physical volume
  G4VPhysicalVolume* Chamber_phys;
 

};

#endif

