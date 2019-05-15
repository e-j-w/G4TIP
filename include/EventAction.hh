#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "TrackerIonSD.hh"
#include "TrackerCsISD.hh"
#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "globals.hh"
#include "G4UnitsTable.hh"
#include "Results.hh"
#include <sys/time.h>
#include "RunAction.hh"
#include "DetectorConstruction.hh"

using namespace CLHEP;

/*
  Trigger settings notes:
  Gamma singles                      1
  user defined particle singles     10
  CsI particle-particle coinc       11
  trigger 10 AND 11                 12 (defined particle-particle coinc)
  trigger 1 AND 12                  13 (defined particle-particle coinc AND gamma singles)
  2 unsupp Griffin cores and 2 CsI  14
  only one defined particle         15 (particle singles with 1 hit restriction)
 */

class EventAction : public G4UserEventAction
{
  public:
  EventAction(Results*,RunAction*,Projectile*,DetectorConstruction*);
   ~EventAction();
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
  void AddGriffinCrystDet(G4double, G4double, G4ThreeVector, G4int, G4int, G4double);
  void SetTriggerGammaSing(){setTrigger=1;};
  void SetTriggerParticleSing(){setTrigger=10;};
  void SetTriggerParticleSing1Hit(){setTrigger=15;};
  void SetTriggerParticleCoinc(){setTrigger=12;};
  void SetTriggerParticleCoincAndGamma(){setTrigger=13;};
  void SetTriggerParticleCoincAnd2GammaCores(){setTrigger=14;};
  void DisableGriffinCryst(int det,int col){GriffinCrystDisabled[det][col]=1;};
  void DisableCsI(int det){CsIDisabled[det]=1;};
  void SetCsIThreshold(G4double x){CsIThreshold=x;};

  void setTriggerA(G4int);
  void setTriggerZ(G4int);
  void setTID(G4int TID){CsIIDTrigger=TID;};

  void reportTriggers();

  private:
  Results*      results;
  G4int         ionCollectionID;
  G4int         CsICollectionID;
  G4int         CollectionGriffinGe;
  timeval       tc,ts,td;
  double        t,rate;
  RunAction*    run_action;
  G4int         GriffinCrystDisabled[16][4];
  G4double      GriffinCrystEnergyDet[16][4];
  G4double      GriffinCrystWeightDet[16][4];
  G4ThreeVector GriffinCrystPosDet[16][4];
  G4double      GriffinCrystTimeDet[16][4];
  G4int         CsIDisabled[NCsISph];
  G4int         GriffinFold;
  size_t        soa,sov,soc,soi;
  unsigned long long int  one,eventTrigger,setTrigger,testTrigger;
  G4double      CsIThreshold;
  G4int         CsIIDTrigger;
  

  // Info for CsI trigger
  Projectile* theProjectile;
  DetectorConstruction* theDetector;
  Int_t       At,Zt; //A and Z of particle to trigger on
  Int_t       triggerAZ; //whether to trigger on a particle with specific A,Z
  G4int numP,numN,numA;//number of each type of recoil particle

  //trigger reporting info
  G4int         numEvents,numTriggeredEvents,numCsIhits,numPCsIHits,numACsIHits,numTriggeredCsIHits;

};

#endif //EVENTACTION_H

    
