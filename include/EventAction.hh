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
  trigger 10 AND 11                 12 (defined particle-particle coinc)
  trigger 1 AND 12                  13 (defined particle-particle coinc AND gamma singles)
  2 unsupp Griffin cores and 2 CsI  14
 */

class EventAction : public G4UserEventAction
{
  public:
  EventAction(Results*,RunAction*,Projectile*);
   ~EventAction();
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
  void AddGriffinCrystDet(G4double, G4double, G4ThreeVector, G4int, G4int, G4double);
  void SetTriggerGammaSing(){setTrigger=1;};
  void SetTriggerParticleSing(){setTrigger=10;};
  void SetTriggerParticleCoinc(){setTrigger=12;};
  void SetTriggerParticleCoincAndGamma(){setTrigger=13;};
  void SetTriggerParticleCoincAnd2GammaCores(){setTrigger=14;};
  void DisableGriffinCryst(int det,int col){GriffinCrystDisabled[det][col]=1;};


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
  G4int         GriffinCrystDisabled[16][4];
  G4double      GriffinCrystEnergyDet[16][4];
  G4double      GriffinCrystWeightDet[16][4];
  G4ThreeVector GriffinCrystPosDet[16][4];
  G4double      GriffinCrystTimeDet[16][4];
  G4int         GriffinFold;
  size_t        soa,sov,soc,soi;
  unsigned long long int  one,eventTrigger,setTrigger,testTrigger;
  G4double      CsIThreshold;
  G4int         CsIIDTrigger;
  

  // Info for CsI trigger
  Projectile* theProjectile;
  Int_t       At,Zt; //A and Z of particle to trigger on
  G4int numP,numN,numA;//number of each type of recoil particle
};

#endif //EVENTACTION_H

    
