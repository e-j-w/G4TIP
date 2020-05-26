#ifndef ArbitraryTarget_H
#define ArbitraryTarget_H 1

#include "G4RunManager.hh"
#include "G4Material.hh"
#include "Chamber.hh"
#include "Materials.hh"
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
#include "G4UserLimits.hh"

using namespace CLHEP;

#define NATARGETLAYERS 10 //the maximum number of layers in the target

class ArbitraryTarget 
{
  public:

  G4LogicalVolume *expHall_log;

  ArbitraryTarget(G4LogicalVolume*,Materials*);
  ~ArbitraryTarget();
  
  G4VPhysicalVolume *AddLayer();
  void setTargetR(G4double);
  void setTargetZ(G4int, G4double);
  void setTargetMaterial(G4int, G4String);
  void setTargetCharge(G4int, G4int);
  void setTargetMass(G4int, G4int);
  void setTargetEx(G4double);
  void setTargetExLayer(G4int);
  void setTargetTau(G4double);
  void setNTStep(G4int);
  void SetTarThickness(G4int, G4double);
  void SetReactionLayer(G4int layer);
  void setTargetPosition(G4int, G4double);
  void Report();
  G4LogicalVolume* GetTargetLog(unsigned int layer){return Target_log[layer];}
  G4Tubs* GetTarget(unsigned int layer){return aTargetLayer[layer];}
  G4int getTargetMass(unsigned int layer){return TargetA[layer];}
  G4int getTargetCharge(unsigned int layer){return TargetZ[layer];}
  G4double getTargetEx(){return TargetEx;}
  G4double getTargetTau(){return TargetTau;}
  G4VPhysicalVolume* GetTargetPlacement(unsigned int layer){return Target_phys[layer];} 
  void setTargetReactionDepth(G4int, G4double);
  G4double GetTargetDensity(unsigned int layer){ return Target_log[layer]->GetMaterial()->GetDensity()/g*cm3;};
  G4double GetTargetThickness(G4int layer){return 2.*aTargetLayer[layer]->GetZHalfLength()/cm;};
  G4double GetTargetNV(G4int, G4int);
  G4int getNumberOfLayers(){return numTargetLayers;};
  G4int getTargetExLayer(){return TargetExLayer;};

  bool CheckAndAddLayers(int);

  


  private:

  void setTargetExAndLayer(G4int, G4double);
    
  Chamber* chamber;

  G4int numTargetLayers;
  
  // dimensions
  G4double Target_radius;
  G4double Target_thickness[NATARGETLAYERS];

  //materials
  Materials* materials;
  G4Material* TargetMaterial[NATARGETLAYERS];

  G4int TargetA[NATARGETLAYERS],TargetZ[NATARGETLAYERS];
  G4double TargetLayerPosition[NATARGETLAYERS]; //positions of target layers (0=chamber center)
  G4double TargetEx;
  G4double TargetTau;
  G4int TargetExLayer; //layer of the target which is excited (or where reaction occurs)
  //default position
  G4RotationMatrix NoRot;
  G4ThreeVector *Pos; //overall position of target (used to shift entire target, 0 = centered in chamber)

  //the tube
  G4Tubs* aTargetLayer[NATARGETLAYERS];

  //logical volume
  G4LogicalVolume* Target_log[NATARGETLAYERS];
  G4LogicalVolume* Backing_log;
 
  //physical volume
  G4VPhysicalVolume* Target_phys[NATARGETLAYERS];

  G4UserLimits *target_limits[NATARGETLAYERS];

  //Number of simulation steps
  G4int NTStep;
  G4int NBStep;

};

#endif

