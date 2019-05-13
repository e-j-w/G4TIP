#include "RunAction.hh"

 
RunAction::RunAction(PhysicsList* PL,Results* Res,DetectorConstruction* Det): thePhysicsList(PL), theResults(Res), theDetector(Det)
{
  
}


RunAction::~RunAction()
{

}

void RunAction::BeginOfRunAction(const G4Run*)
{
  G4cout<<"---> Beginning the run!"<<G4endl;
  gettimeofday(&ts,NULL);
  
  thePhysicsList->getReaction()->SetupReaction();
  nP=thePhysicsList->getReaction()->GetNumberOfProtons();
  nN=thePhysicsList->getReaction()->GetNumberOfNeutrons();
  nA=thePhysicsList->getReaction()->GetNumberOfAlphas();
  theResults->SetupRun(nP,nN,nA);
}


 
void RunAction::EndOfRunAction(const G4Run*)
{
  G4cout<<" End of run "<<G4endl;
}

