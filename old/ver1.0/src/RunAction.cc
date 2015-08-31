#include "RunAction.hh"

 
RunAction::RunAction(PhysicsList* PL,Results* Res,DetectorConstruction* Det, EvaporationChannel* Evp): thePhysicsList(PL), theResults(Res), theDetector(Det), theEvaporationChannel(Evp)
{
  
}


RunAction::~RunAction()
{

}

void RunAction::BeginOfRunAction(const G4Run*)
{
  G4double At,Zt;
  G4int nP,nN,nA;
  G4double Egamma,tau;
  G4int DA,DZ;
  G4cout<<" Beginin of run "<<G4endl;
  gettimeofday(&ts,NULL);
 
  At=theDetector->GetTarget()->getTargetMass();
  Zt=theDetector->GetTarget()->getTargetCharge();
  nN=theEvaporationChannel->GetNumberOfNeutrons();
  nP=theEvaporationChannel->GetNumberOfProtons();
  nA=theEvaporationChannel->GetNumberOfAlphas();
  Egamma=theEvaporationChannel->GetEgamma();
  tau=theEvaporationChannel->GetTau();

  thePhysicsList->getReaction()->SetEvaporationChannel(nN,nP,nA);
  thePhysicsList->getReaction()->SetEgamma(Egamma);
  thePhysicsList->getReaction()->SetTau(tau);
  thePhysicsList->getReaction()->SetTargetMassAndCharge(At,Zt);
  thePhysicsList->getReaction()->TargetFaceCrossSection();
  
  DA=At-nN-nP-4*nA;
  DZ=Zt-nP-2*nA;
  theResults->SetupRun(DA,DZ);
}


 
void RunAction::EndOfRunAction(const G4Run*)
{
 
}

