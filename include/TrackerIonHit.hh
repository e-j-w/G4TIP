
#ifndef TrackerIonHit_h
#define TrackerIonHit_h 1


#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include <iomanip>
#include "Flags.hh"

using namespace CLHEP;

class TrackerIonHit : public G4VHit
{
  public:

      TrackerIonHit();
     ~TrackerIonHit();
      TrackerIonHit(const TrackerIonHit&);
      const TrackerIonHit& operator=(const TrackerIonHit&);
      G4int operator==(const TrackerIonHit&) const;

      inline void* operator new(size_t);
      inline void  operator delete(void*);

      void Draw();
      void Print();

  public:
  
      void SetA(G4int a){A=a;};
      void SetZ(G4int z){Z=z;};
      void SetBeta(G4double b){beta=b;};
      void SetKE(G4double k){KE=k;};
      void SetWeight(G4double w){weight=w;};
      void SetPos      (G4ThreeVector xyz){ pos = xyz; };
      void SetMom      (G4ThreeVector xyz){ p = xyz; };
      void SetGunFlag(){flag=GUN_FLAG;}
      void SetVolName(G4String name){volumeName=name;};
      void SetIonName(G4String name){ionName=name;};
      void SetFlagZero(){flag=0;}
      void SetDecayFlag(){pflag=DECAY_FLAG;}
      void SetReactionInFlag(){pflag=REACTION_IN_FLAG;}
      void SetReactionOutFlag(){pflag=REACTION_OUT_FLAG;}
      void SetPlungerTargetInFlag(){flag=PLUNGER_TARGET_IN_FLAG;}
      void SetPlungerTargetOutFlag(){flag=PLUNGER_TARGET_OUT_FLAG;}
      void SetPlungerBackingInFlag(){flag=PLUNGER_BACKING_IN_FLAG;}
      void SetPlungerBackingOutFlag(){flag=PLUNGER_BACKING_OUT_FLAG;}
      void SetPlungerDegraderInFlag(){flag=PLUNGER_DEGRADER_IN_FLAG;}
      void SetPlungerDegraderOutFlag(){flag=PLUNGER_DEGRADER_OUT_FLAG;}
      void SetDSAMTargetInFlag(){flag=DSAM_TARGET_IN_FLAG;}
      void SetDSAMBackingInFlag(){flag=DSAM_BACKING_IN_FLAG;}
      void SetDSAMBackingOutFlag(){flag=DSAM_BACKING_OUT_FLAG;}
      void SetTargetLayerInFlag(G4int layer){flag=TARGET_LAYER_IN_FLAG+layer;};
      void SetTargetLayerOutFlag(G4int layer){flag=TARGET_LAYER_OUT_FLAG+layer;};
      void SetPFlag(G4int i){pflag=i;}
      void SetTime(G4double t){time=t;};
  
      G4int    GetA(){return A;}
      G4int    GetZ(){return Z;}
      G4double GetBeta(){return beta;};
      G4double GetWeight(){return weight;};
      G4double GetKE(){return KE;};
      G4ThreeVector GetPos(){ return pos; };
      G4ThreeVector GetMom(){ return p; };
      G4int    GetFlag(){return flag;}
      G4int    GetPFlag(){return pflag;}
      G4String GetVolName(){return volumeName;};
      G4String GetIonName(){return ionName;};
      G4double GetTime(){return time;};
  private:
      G4int         A;
      G4int         Z;
      G4double      beta;
      G4double      KE;
      G4double      weight;
      G4double      time;
      G4ThreeVector pos;
      G4ThreeVector p;
      G4int         flag;
      G4int         pflag;
      G4String      volumeName;
      G4String      ionName;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<TrackerIonHit> TrackerIonHitsCollection;

extern G4Allocator<TrackerIonHit> TrackerIonHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* TrackerIonHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) TrackerIonHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void TrackerIonHit::operator delete(void *aHit)
{
  TrackerIonHitAllocator.FreeSingle((TrackerIonHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
