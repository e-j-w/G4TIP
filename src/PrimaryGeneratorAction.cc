#include "PrimaryGeneratorAction.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction *Det,Projectile* Proj): theProjectile(Proj), theDetector(Det)
{

  n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);
 

}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  
  //particleTable = G4ParticleTable::GetParticleTable(); // v9.4.p04
  ionTable = G4IonTable::GetIonTable();
 
  //ion =  particleTable->GetIon(theProjectile->getZ(),theProjectile->getA(),0.); // v9.4.p04
  ion =  ionTable->GetIon(theProjectile->getZ(),theProjectile->getA(),0.);

  particleGun->SetParticleDefinition(ion);
  
  position=theProjectile->getPosition();
  particleGun->SetParticlePosition(position);
      
  direction=theProjectile->getDirection();
  particleGun->SetParticleMomentumDirection(direction);
  
  KE=theProjectile->getKE();
  particleGun->SetParticleEnergy(KE);
 
  //Reactions on the target
  G4double TT=2.*theDetector->GetPlunger()->GetTarget()->GetZHalfLength();
  G4double TC=theDetector->GetPlunger()->GetTargetPlacement()->GetTranslation().getZ();
  G4double depth=TC+TT*(G4UniformRand()-0.5);
  theDetector->GetPlunger()->SetTargetReactionDepth(depth);
  // printf("tar thickness %f tar center (?) %f --> target reaction depth set to %f\n",TT,TC,depth);
  // getc(stdin);

  // G4cout<<" +++++ Generating an event "<<G4endl;
  particleGun->GeneratePrimaryVertex(anEvent);
  // G4cout<<" +++++ Out Generate Primaries "<<G4endl;
}
