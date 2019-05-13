
#ifndef TrackerCsIHit_h
#define TrackerCsIHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

using namespace CLHEP;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TrackerCsIHit : public G4VHit
{
  public:

      TrackerCsIHit();
     ~TrackerCsIHit();
      TrackerCsIHit(const TrackerCsIHit&);
      const TrackerCsIHit& operator=(const TrackerCsIHit&);
      G4int operator==(const TrackerCsIHit&) const;

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
      void SetPathLength(G4double l) { path = l; }; 
      void SetDisabled(){disabled=1;};//used to disable CsI hits 
      void SetTime(G4double t){time=t;};
    
      G4int    GetA(){return A;}
      G4int    GetZ(){return Z;}
      G4double GetBeta(){return beta;};
      G4double GetWeight(){return weight;};
      G4double GetKE(){return KE;};
      G4ThreeVector GetPos(){ return pos; };
      G4ThreeVector GetMom(){ return p; };
      G4int    GetId()      { return id; };       
      G4int    GetRingId()  { return ring; };  
      G4double GetPathLength()  { return path; };
      G4int    GetDisabled() {return disabled;};
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
      G4int         id;
      G4int         ring;
      G4double      path;
      G4int         disabled;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<TrackerCsIHit> TrackerCsIHitsCollection;

extern G4Allocator<TrackerCsIHit> TrackerCsIHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* TrackerCsIHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) TrackerCsIHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void TrackerCsIHit::operator delete(void *aHit)
{
  TrackerCsIHitAllocator.FreeSingle((TrackerCsIHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
