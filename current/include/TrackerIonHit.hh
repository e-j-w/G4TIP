
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
      void SetFlagZero(){flag=0;}
      void SetDecayFlag(){pflag=DECAY_FLAG;}
      void SetReactionInFlag(){pflag=REACTION_IN_FLAG;}
      void SetReactionOutFlag(){pflag=REACTION_OUT_FLAG;}
      void SetTargetInFlag(){flag=TARGET_IN_FLAG;}
      void SetBackingInFlag(){flag=BACKING_IN_FLAG;}
      void SetBackingOutFlag(){flag=BACKING_OUT_FLAG;}
  
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
  private:
      G4int         A;
      G4int         Z;
      G4double      beta;
      G4double      KE;
      G4double      weight;
      G4ThreeVector pos;
      G4ThreeVector p;
      G4int         flag;
      G4int         pflag;
      G4String      volumeName;
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
