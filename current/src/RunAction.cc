#include "RunAction.hh"

 
RunAction::RunAction(PhysicsList* PL,Results* Res,DetectorConstruction* Det): thePhysicsList(PL), theResults(Res), theDetector(Det)
{
  
}


RunAction::~RunAction()
{

}

void RunAction::BeginOfRunAction(const G4Run*)
{
  G4double At,Zt;
  G4cout<<" Beginning of run "<<G4endl;
  gettimeofday(&ts,NULL);
 
  At=theDetector->GetTarget()->getTargetMass();
  Zt=theDetector->GetTarget()->getTargetCharge();
  thePhysicsList->getReaction()->SetTargetMassAndCharge(At,Zt);
  thePhysicsList->getReaction()->TargetFaceCrossSection();
  nP=thePhysicsList->getReaction()->GetNumberOfProtons();
  nN=thePhysicsList->getReaction()->GetNumberOfNeutrons();
  nA=thePhysicsList->getReaction()->GetNumberOfAlphas();
  theResults->SetupRun(nP,nN,nA);
}


 
void RunAction::EndOfRunAction(const G4Run*)
{
  G4cout<<" End of run "<<G4endl;
}

