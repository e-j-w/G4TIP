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
  
	ionTable = G4IonTable::GetIonTable();

  ion =  ionTable->GetIon(theProjectile->getZ(),theProjectile->getA(),0.);
  particleGun->SetParticleDefinition(ion);
  
  
  position=theProjectile->getPosition();
  particleGun->SetParticlePosition(position);
      
  direction=theProjectile->getDirection();
  particleGun->SetParticleMomentumDirection(direction);
  
  KE=theProjectile->getKE();
  particleGun->SetParticleEnergy(KE);
 
  //Reactions on the target
  G4double TT=2.*theDetector->GetTarget()->GetTarget()->GetZHalfLength();
  G4double TC=theDetector->GetTarget()->GetTargetPlacement()->GetTranslation().getZ();
  G4double depth=TC+TT*(G4UniformRand()-0.5);
  theDetector->GetTarget()->setTargetReactionDepth(depth);

  // G4cout<<" +++++ Generating an event "<<G4endl;
  particleGun->GeneratePrimaryVertex(anEvent);
  // G4cout<<" +++++ Out Generate Primaries "<<G4endl;
}
