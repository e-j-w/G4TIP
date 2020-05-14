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

  switch (thePhysicsList->getReactionType())
  {
    //case 1:
      //coulex
      //theResults->SetupRun();
    //  break;
    default:
      //fusion evaporation
      thePhysicsList->getReactionFusEvap()->SetupReaction();
      nP=thePhysicsList->getReactionFusEvap()->GetNumberOfProtons();
      nN=thePhysicsList->getReactionFusEvap()->GetNumberOfNeutrons();
      nA=thePhysicsList->getReactionFusEvap()->GetNumberOfAlphas();
      theResults->SetupRunFusEvap(nP,nN,nA);
      break;
  }
  
  
}


 
void RunAction::EndOfRunAction(const G4Run*)
{
  G4cout<<" End of run "<<G4endl;
}

