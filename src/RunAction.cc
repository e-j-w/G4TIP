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
    case 1:
      //coulex
      thePhysicsList->getReactionCoulex()->TargetFaceCrossSection();
      recoilZ=thePhysicsList->getReactionCoulex()->getTargetRecoilZ();
      theResults->SetupRunCoulex();
      break;
    case 0:
      //fusion evaporation
      thePhysicsList->getReactionFusEvap()->SetupReaction();
      nP=thePhysicsList->getReactionFusEvap()->GetNumberOfProtons();
      nN=thePhysicsList->getReactionFusEvap()->GetNumberOfNeutrons();
      nA=thePhysicsList->getReactionFusEvap()->GetNumberOfAlphas();
      theResults->SetupRunFusEvap(nP,nN,nA);
      break;
    default:
      G4cout << "ERROR: no reaction mechanism specified.  Specify /Physics/FusionEvaporation or /Physics/Coulex in the macro file and try again." << G4endl;
      exit(-1);
  }
  
  
}


 
void RunAction::EndOfRunAction(const G4Run*)
{
  
  G4cout<<" End of run "<<G4endl;

  switch (thePhysicsList->getReactionType())
  {
    case 1:
      //coulex
      G4double p,ddx,dx,Nv;
      G4cout<<G4endl;
      theResults->SetTargetFaceCrossSection(thePhysicsList->getReactionCoulex()->GetTargetFaceCrossSection());   
    
      G4cout<<setprecision(3);

      G4cout<<" Thin target cross section is calculated assuming all reactions with the energy of the particle gun"<<G4endl;
      G4cout<<" Thick target correction accounts for the projectile energy change while crossing the backing and the target"<<G4endl;
      G4cout<<" Thin Target Cross Section is              : "<<thePhysicsList->getReactionCoulex()->GetTargetFaceCrossSection()<<" [b]"<<G4endl;
      G4cout<<" Thick Target correction is                : "<<thePhysicsList->getReactionCoulex()->GetThickTargetCorrection()<<G4endl;
      G4cout<<" Thick Target Cross Section is             : "<<thePhysicsList->getReactionCoulex()->GetThickTargetCrossSection()<<" [b]"<<G4endl;
      // G4cout<<" Target thickness in um  is                : "<<dx*10000.<<G4endl;
      if(theDetector->GetTargetType()==2){
        //using plunger
        dx=theDetector->GetPlunger()->GetTargetThickness();   // in cm
        ddx=dx*theDetector->GetPlunger()->GetTargetDensity(); // in g/cm^2
        Nv=theDetector->GetPlunger()->GetTargetNV(recoilZ);   // in atoms/cm3
        p=Nv*dx*thePhysicsList->getReactionCoulex()->GetThickTargetCrossSection()*1E-18;
        G4cout<<" Target material density in g/cm3 is       : "<<theDetector->GetPlunger()->GetTargetDensity()<<G4endl;
        G4cout<<" Target thickness in mg/cm2 is             : "<<ddx*1000.<<G4endl;
        // G4cout<<" Number of atoms per unit volume           : "<<Nv<<" atoms/cm3"<<G4endl;
        // G4cout<<" Avogadro's number                         : "<<Avogadro<<" atoms/mol"<<G4endl;
        G4cout<<" Number density of recoils in the target is: "<<Nv/Avogadro*1000.<<" [milli-mole/cm3]"<<G4endl;
        G4cout<<" Number of excitation is                   : "<<p<<" per million beam particles"<<G4endl;
      }
      G4cout<<" Results are based on simulation of : "<<thePhysicsList->getReactionCoulex()->GetNumberOfSimulatedReactions()<<" reactions"<<G4endl;
      G4cout<<" Dropped                            : "<<thePhysicsList->getReactionCoulex()->GetRxnDroppedE()<<" reactions due to energy cutoff"<<G4endl;
      G4cout<<" Dropped                            : "<<thePhysicsList->getReactionCoulex()->GetRxnDroppedKsi()<<" reactions due to adiabaticity xi out of range"<<G4endl;
      G4cout<<" Dropped                            : "<<thePhysicsList->getReactionCoulex()->GetRxnDroppedRand()<<" reactions due to XC RNG"<<G4endl;
      break;
    case 0:
      //fusion evaporation
      break;
    default:
      break;
  }
  
}

