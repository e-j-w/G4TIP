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
  trigger 10 AND 1                  16 (particle-gamma coinc, only 1 of each needed)
 */

#define GAMMA_SINGLES_TRIGGER                          1
#define DEFINEDPARTICLE_SINGLES_TRIGGER                10
#define PARTICLE_COINC_TRIGGER                         11
#define DEFINEDPARTICLE_COINC_TRIGGER                  12
#define DEFINEDPARTICLE_COINC_AND_GAMMA_TRIGGER        13
#define DEFINEDPARTICLE_COINC_AND_GAMMA_COINC_TRIGGER  14
#define DEFINEDPARTICLE_ONEPARTICLE_TRIGGER            15
#define DEFINEDPARTICLE_AND_GAMMA_TRIGGER              16

class EventAction : public G4UserEventAction
{
  public:
  EventAction(Results*,RunAction*,Projectile*,DetectorConstruction*);
   ~EventAction();
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
  void AddGriffinCrystDet(G4double, G4double, G4ThreeVector, G4int, G4int, G4double);
  G4bool passesCsIThresold(G4double);
  void SetTriggerGammaSing(){setTrigger=1;};
  void SetTriggerParticleSing(){setTrigger=10;};
  void SetTriggerParticleSing1Hit(){setTrigger=15;};
  void SetTriggerParticleCoinc(){setTrigger=12;};
  void SetTriggerParticleAndGamma(){setTrigger=16;};
  void SetTriggerParticleCoincAndGamma(){setTrigger=13;};
  void SetTriggerParticleCoincAnd2GammaCores(){setTrigger=14;};
  void DisableGriffinCryst(int det,int col){GriffinCrystDisabled[det][col]=1;};
  void DisableCsI(int det){CsIDisabled[det]=1;};
  void WeightCsI(int det, double weight){CsIWeight[det]=weight;};
  void SetCsIThreshold(G4double x){CsIThreshold[0]=x; CsIThreshold[1]=x;};
  void SetCsILinearThreshold(G4double low, G4double high){CsIThreshold[0]=low; CsIThreshold[1]=high;};

  void setTriggerA(G4int);
  void setTriggerZ(G4int);
  void setTriggerARange(G4int,G4int);
  void setTriggerZRange(G4int,G4int);
  void setTID(G4int TID){CsIIDTrigger=TID;};

  void reportTriggers();

  private:
  Results*      results;
  G4int         ionCollectionID;
  G4int         CsICollectionID;
  G4int         CollectionGriffinGe;
  timeval       tc,ts,td;
  double        tt,rate;
  RunAction*    run_action;
  size_t        soa,sov,sois,soas,sovs,soc,soi;
  unsigned long long int  eventTrigger,setTrigger,testTrigger;
  G4double      CsIThreshold[2];
  G4int         CsIIDTrigger;

  //GRIFFIN/TIGRESS interaction information
  G4int         GriffinCrystDisabled[16][4];
  G4double      GriffinCrystEnergyDet[16][4];
  G4double      GriffinCrystWeightDet[16][4];
  G4ThreeVector GriffinCrystPosDet[16][4];
  G4double      GriffinCrystTimeDet[16][4];
  G4int         GriffinFold;
  //TIGRESS segment interaction information
  G4int         TigressSegHitsDet[16][4][8]; //number of hits in each segment
  G4double      TigressSegWeightDet[16][4][8];
  G4double      TigressSegEnergyDet[16][4][8];
  G4ThreeVector TigressSegPosDet[16][4][8]; //x,y,z position of hit
  G4ThreeVector TigressSegPosCylDet[16][4][8]; //r,phi,z (cylindrical coordinates) position of hit w.r.t the core where the hit occurs
  //CsI array interaction information
  G4int         CsIDisabled[NCsISph];
  G4double      CsIWeight[NCsISph];
  

  // Info for CsI trigger
  Projectile* theProjectile;
  DetectorConstruction* theDetector;
  Int_t       At,Zt; //A and Z of particle to trigger on
  Int_t       triggerAZ; //whether to trigger on a particle with specific A,Z
  Int_t       Atmin,Atmax,Ztmin,Ztmax;
  G4int numP,numN,numA;//number of each type of recoil particle

  //trigger reporting info
  G4double         numEvents,numTriggeredEvents,numCsIhits,numPCsIHits,numACsIHits,numTriggeredCsIHits;

};

#endif //EVENTACTION_H

    
