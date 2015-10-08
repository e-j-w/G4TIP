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

/*
  Trigger settings notes:
  Gamma singles                      1
  user defined particle singles     10
  CsI particle-particle coinc       11
  trigger 10 AND 11                 12
 */

class EventAction : public G4UserEventAction
{
  public:
  EventAction(Results*,RunAction*,Projectile*);
   ~EventAction();
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
  void AddGriffinCrystDet(G4double, G4double,G4ThreeVector, G4int, G4int);
  void SetTriggerGammaSing(){setTrigger=1;};
  void SetTriggerParticleSing(){setTrigger=10;};
  void SetTriggerParticleCoinc(){setTrigger=12;};


  void setTriggerA(G4int);
  void setTriggerZ(G4int);
  void setTID(G4int TID){CsIIDTrigger=TID;};

  private:
  Results*      results;
  G4int         ionCollectionID;
  G4int         CsICollectionID;
  G4int         CollectionGriffinGe;
  timeval       tc,ts,td;
  double        t,rate;
  RunAction*    run_action;
  G4double      GriffinCrystEnergyDet[16][4];
  G4double      GriffinCrystWeightDet[16][4];
  G4ThreeVector GriffinCrystPosDet[16][4];
  G4int         GriffinFold;
  size_t        soa,sov;
  unsigned long long int  one,eventTrigger,setTrigger,systemTrigger;
  G4double      CsIThreshold;
  G4int         CsIIDTrigger;
  

  // Info for CsI trigger
  Projectile* theProjectile;
  Int_t       At,Zt; //A and Z of particle to trigger on
  G4int numP,numN,numA;//number of each type of recoil particle
};

#endif //EVENTACTION_H

    
