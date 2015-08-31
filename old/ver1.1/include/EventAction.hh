#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "TrackerIonSD.hh"
#include "TrackerPINSD.hh"
#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "globals.hh"
#include "G4UnitsTable.hh"
#include "Results.hh"
#include <sys/time.h>
#include "RunAction.hh"

class EventAction : public G4UserEventAction
{
  public:
  EventAction(Results*,RunAction*);
   ~EventAction();

  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
  void AddGriffinCrystDet(G4double, G4double,G4ThreeVector, G4int, G4int);
  void SetTriggerGammaSing(){setTrigger=1;};
  void SetTriggerPinSing(){setTrigger=2;};
  void SetTriggerGammaPinCoinc(){setTrigger=3;};
  private:
  Results* results;
  G4int ionCollectionID;
  G4int PINCollectionID;
  G4int CollectionGriffinGe;
  timeval tc,ts,td;
  double t,rate;
  RunAction* run_action;
  G4double  GriffinCrystEnergyDet[16][4];
  G4double  GriffinCrystWeightDet[16][4];
  G4ThreeVector  GriffinCrystPosDet[16][4];
  G4int      GriffinFold;
  size_t soa,sov;
  G4int eventTrigger,setTrigger;
};

#endif //EVENTACTION_H

    
