
#ifndef TrackerPINHit_h
#define TrackerPINHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TrackerPINHit : public G4VHit
{
  public:

      TrackerPINHit();
     ~TrackerPINHit();
      TrackerPINHit(const TrackerPINHit&);
      const TrackerPINHit& operator=(const TrackerPINHit&);
      G4int operator==(const TrackerPINHit&) const;

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
      void SetId        (G4int m)      { id = m; };    
      void SetRingId    (G4int m)      { ring = m; };    
    
      G4int    GetA(){return A;}
      G4int    GetZ(){return Z;}
      G4double GetBeta(){return beta;};
      G4double GetWeight(){return weight;};
      G4double GetKE(){return KE;};
      G4ThreeVector GetPos(){ return pos; };
      G4ThreeVector GetMom(){ return p; };
      G4int    GetId()      { return id; };       
      G4int    GetRingId()  { return ring; };  
  private:
  
      G4int         A;
      G4int         Z;
      G4double      beta;
      G4double      KE;
      G4double      weight;
      G4ThreeVector pos;
      G4ThreeVector p;
      G4int         id;
      G4int         ring;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<TrackerPINHit> TrackerPINHitsCollection;

extern G4Allocator<TrackerPINHit> TrackerPINHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* TrackerPINHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) TrackerPINHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void TrackerPINHit::operator delete(void *aHit)
{
  TrackerPINHitAllocator.FreeSingle((TrackerPINHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
