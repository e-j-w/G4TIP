#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "G4RandomDirection.hh"
#include "G4LorentzVector.hh"
#include "G4DynamicParticle.hh"
#include "Projectile.hh"
#include "DetectorConstruction.hh"
#include <vector>


class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction(DetectorConstruction*,Projectile*);
  ~PrimaryGeneratorAction();
  
public:
  void GeneratePrimaries(G4Event* anEvent);


private:


  G4int n_particle;
  G4ParticleGun* particleGun;
  G4ParticleTable* particleTable;
  G4ParticleDefinition* ion;
  G4ThreeVector  direction;
  G4ThreeVector  position;
  G4double       KE;
  

  Projectile *theProjectile;
  DetectorConstruction *theDetector;
 
};


#endif


           
