#ifndef Target_H
#define Target_H 1

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

class Target 
{
  public:

  G4LogicalVolume *expHall_log;

  Target(G4LogicalVolume*,Materials*);
  ~Target();
  
  G4VPhysicalVolume *Construct();
  void setTargetR(G4double);
  void setBackingR(G4double);
  void setTargetZ(G4double);
  void setBackingZ(G4double);
  void setBackingOffset(G4double);
  void setTargetMaterial(G4String);
  void setBackingMaterial(G4String);
  void setBackingCharge(G4int);
  void setBackingMass(G4int);
  void setBackingEx(G4double);
  void setBackingTau(G4double);
  void setTargetCharge(G4int);
  void setTargetMass(G4int);
  void setTargetEx(G4double);
  void setTargetTau(G4double);
  void setNTStep(G4int);
  void setNBStep(G4int);
  void SetTarThickness(G4double);
  void setFracReactionBacking(G4double);
  void setFracReactionTarget(G4double);
  void setFlagReactionBacking(G4bool flag){flagReactionBacking=flag;}
  void Report();
  G4LogicalVolume* GetTargetLog(){return Target_log;}
  G4LogicalVolume* GetBackingLog(){return Backing_log;}
  G4Tubs* GetTarget(){return aTarget;}
  G4Tubs* GetBacking(){return aBacking;}
  G4int getBackingMass(){return BackingA;}
  G4int getBackingCharge(){return BackingZ;}
  G4double getBackingEx(){return BackingEx;}
  G4double getBackingTau(){return BackingTau;}
  G4int getTargetMass(){return TargetA;}
  G4int getTargetCharge(){return TargetZ;}
  G4double getTargetEx(){return TargetEx;}
  G4double getTargetTau(){return TargetTau;}
  G4VPhysicalVolume* GetTargetPlacement(){return Target_phys;} 
  G4VPhysicalVolume* GetBackingPlacement(){return Backing_phys;} 
  void setTargetReactionDepth(G4double);
  void setBackingReactionDepth(G4double);
  G4double GetFracReactionBacking(){return fracReactionBacking;};
  G4bool getFlagReactionBacking(){return flagReactionBacking;}
  G4double GetTargetDensity(){ return Target_log->GetMaterial()->GetDensity()/g*cm3;};
  G4double GetTargetThickness(){return 2.*aTarget->GetZHalfLength()/cm;};
  G4double GetTargetNV(G4int);


    private:
    
  Chamber* chamber;
  
  // dimensions
  G4double Target_radius;
  G4double Target_thickness;
  G4double Backing_radius;
  G4double Backing_thickness;


  //materials
  Materials* materials;
  G4Material* TargetMaterial;
  G4Material* BackingMaterial;
  G4int TargetA,TargetZ;
  G4int BackingA,BackingZ;
  G4double TargetEx,BackingEx;
  G4double TargetTau,BackingTau;
  //default position
  G4RotationMatrix NoRot;
  G4ThreeVector *Pos;

  //the tube
  G4Tubs* aTarget;
  G4Tubs* aBacking;

  //logical volume
  G4LogicalVolume* Target_log;
  G4LogicalVolume* Backing_log;
 
  //physical volume
  G4VPhysicalVolume* Target_phys;
  G4VPhysicalVolume* Backing_phys;

  G4UserLimits *target_limits;
  G4UserLimits *backing_limits;
  //Number of simulation steps
  G4int NTStep;
  G4int NBStep;

  G4double fracReactionBacking;
  G4bool   flagReactionBacking;
};

#endif

