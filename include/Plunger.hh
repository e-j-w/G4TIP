#ifndef Plunger_H
#define Plunger_H 1

#include "G4RunManager.hh"
#include "G4Material.hh"
#include "Materials.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Para.hh"
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

class Plunger
{
  public:

  G4LogicalVolume *expHall_log;

  Plunger(G4LogicalVolume*,Materials*);
  ~Plunger();
  
  void Construct();

  void SetDegR(G4double);
  void SetDegZ(G4double);
  void SetNstepDeg(G4int);
  void SetDegMaterial(G4String);
  void ScaleDegDensity(G4double);

  void     SetTarR(G4double);
  void     SetTarZ(G4double);
  void     SetTarThickness(G4double);
  void     SetNstepTar(G4int);
  void     SetTarMaterial(G4String);
  void     ScaleTarDensity(G4double);
  void     setTargetMass(G4int A){TargetA=A;};
  void     setTargetCharge(G4int Z){TargetZ=Z;};
  G4double GetTargetDensity(){return Target_log->GetMaterial()->GetDensity()/g*cm3;};
  G4int    getTargetMass(){return TargetA;};
  G4int    getTargetCharge(){return TargetZ;};
  G4int    getStopperMass(){return StopperA;};
  G4int    getStopperCharge(){return StopperZ;};  
  void     SetTargetReactionDepth(G4double depth){target_limits->SetUserMinRange(depth);}
  G4Material* GetTargetMaterial(){return Target_log->GetMaterial();};


  void SetBckR(G4double);
  void SetBckZ(G4double);
  void SetNstepBck(G4int);
  void SetBckMaterial(G4String);
  void ScaleBckDensity(G4double);
  void SetPosZ(G4double);
  G4double GetPosZ();
  void SetSeparation(G4double);
  void Report();

  G4LogicalVolume*   GetStopperLog(){return Stopper_log;}
  G4Tubs*            GetStopper(){return theStopper;}
  G4VPhysicalVolume* GetStopperPlacement(){return Stopper_phys;}
  G4double           GetStopperDensity(){return Stopper_log->GetMaterial()->GetDensity()/g*cm3;};

  G4LogicalVolume*   GetTargetLog(){return Target_log;}
  G4Tubs*            GetTarget(){return theTarget;}
  G4VPhysicalVolume* GetTargetPlacement(){return Target_phys;}
  G4double           GetTargetThickness();
  G4double           GetTargetNV(G4int);

  G4LogicalVolume*   GetBackingLog(){return Backing_log;}
  G4Tubs*            GetBacking(){return theBacking;}
  G4VPhysicalVolume* GetBackingPlacement(){return Backing_phys;}

 
    private:
 
  // dimensions
  G4double Stopper_radius;
  G4double Stopper_thickness;
  G4int    NstepDeg;

  G4double Target_radius;
  G4double Target_thickness;
  G4int    NstepTar;
  
  G4double Backing_radius;
  G4double Backing_thickness;
  G4int    NstepBck;

  //materials
  Materials*  materials;
  G4Material* StopperMaterial;
  G4Material* TargetMaterial;
  G4Material* PlungerMaterial;
  G4Material* PostMaterial;
  G4Material* BackingMaterial;
  G4int       TargetA;
  G4int       TargetZ;
  G4int       StopperA;
  G4int       StopperZ;
  
  //default position
  G4RotationMatrix NoRot;
  G4ThreeVector*   Pos;
  
  G4double D;

  //the stuff
  G4Tubs* theStopper;
  G4Tubs* theTarget;
  G4Tubs* theBacking;

  //logical volume
  G4LogicalVolume* Stopper_log;
  G4LogicalVolume* Target_log;
  G4LogicalVolume* Backing_log;
 
  //physical volume
  G4VPhysicalVolume* Stopper_phys;
  G4VPhysicalVolume* Target_phys;
  G4VPhysicalVolume* Backing_phys;
 
  //reaction stuff
  G4UserLimits* degrader_limits;
  G4UserLimits* target_limits;
  G4UserLimits* backing_limits;

  //target and degrader holder
  G4Cons*  DHCone;
  G4Tubs*  DHFRing;
  G4Tubs*  DHRing;
  G4Cons*  THCone;
  G4Tubs*  THRing;
  G4Tubs*  THPost;
  G4Tubs*  DHPost;
  G4double THt;
  G4double DHt;
  G4double DHFRingt;
  G4double DHRingt;
  G4double THRingt;

  // physical volumes for target and degrader
  G4VPhysicalVolume* DHCone_phys;
  G4VPhysicalVolume* DHFRing_phys;
  G4VPhysicalVolume* DHRing_phys;
  G4VPhysicalVolume* DHPost0_phys;
  G4VPhysicalVolume* DHPost1_phys;
  G4VPhysicalVolume* DHPost2_phys;
  G4VPhysicalVolume* THCone_phys;
  G4VPhysicalVolume* THRing_phys;
  G4VPhysicalVolume* THPost0_phys;
  G4VPhysicalVolume* THPost1_phys;
  G4VPhysicalVolume* THPost2_phys;

};


#endif

