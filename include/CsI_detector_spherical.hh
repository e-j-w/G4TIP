#ifndef CsI_detector_spherical_H
#define CsI_detector_spherical_H 1


#include "G4Material.hh"
#include "Materials.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Trap.hh"
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
#include "G4IntersectionSolid.hh"

using namespace CLHEP;

class CsI_detector_spherical
{
  public:

  G4LogicalVolume *expHall_log;

  CsI_detector_spherical(G4LogicalVolume*,Materials*);
  ~CsI_detector_spherical();
  
  G4VPhysicalVolume* Construct(G4ThreeVector,G4ThreeVector);
  void setId(G4int i){Id=i;};
  void setRingId(G4int i){RingId=i;};
  void setName();
  void Report();
  void Place(G4ThreeVector);
  G4LogicalVolume* GetLog(){return CsI_detector_log;};
  void setAbsorberThickness(G4double i){CsI_absorber_thickness=i;};
 
    private:
  // dimensions
  G4double CsI_absorber_thickness;

  //materials
  Materials* materials;
  G4Material* CsI_Material;
  G4Material* CsI_absorber_Material;

  //default position
  G4RotationMatrix NoRot;
  G4ThreeVector *Pos;
  G4ThreeVector *Pos_abs;
  
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

