#ifndef CsI_detector_H
#define CsI_detector_H 1


#include "G4Material.hh"
#include "Materials.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4UnitsTable.hh"
#include "G4RunManager.hh"
#include "G4SubtractionSolid.hh"
class CsI_detector 
{
  public:

  G4LogicalVolume *expHall_log;

  CsI_detector(G4LogicalVolume*,Materials*);
  ~CsI_detector();
  
  G4VPhysicalVolume *Construct();
  void setId(G4int i){Id=i;};
  void setRingId(G4int i){RingId=i;};
  void setName();
  void Report();
  void Place(G4ThreeVector);
  G4LogicalVolume* GetLog(){return CsI_detector_log;};
 
    private:
  // dimensions
  G4double CsI_detector_side_x;
  G4double CsI_detector_side_y;
  G4double CsI_detector_thickness;
  G4double CsI_absorber_thickness;


  //materials
  Materials* materials;
  G4Material* CsI_Material;
  G4Material* CsI_absorber_Material;

  //default position
  G4RotationMatrix NoRot;
  G4ThreeVector *Pos;
  G4ThreeVector *Pos_abs;

  G4Box* aCsI_detector;
  G4Box* aCsI_absorber;
  G4SubtractionSolid* aCsI_side_absorber;
  //logical volume
  G4LogicalVolume* CsI_detector_log;
  G4LogicalVolume* CsI_absorber_log;
  G4LogicalVolume* CsI_side_absorber_log;

  //physical volume
  G4VPhysicalVolume* CsI_detector_phys;
  G4VPhysicalVolume* CsI_absorber_phys;
  G4VPhysicalVolume* CsI_side_absorber_phys;
  G4int Id,RingId;
};

#endif

