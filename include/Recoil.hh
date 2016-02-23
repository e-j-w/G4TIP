#ifndef Recoil_h
#define Recoil_h 1

#include <cmath>
#include <vector>
using namespace std;

#include "globals.hh"
#include "G4UnitsTable.hh"
#include "G4ThreeVector.hh"
#include "G4Track.hh"
#include "G4DynamicParticle.hh"
#include "G4ParticleTable.hh"
#include "G4RandomDirection.hh"
#include "G4Decay.hh"
#include "Randomize.hh"



// this is?
//#define  eps 0.00001

class Recoil
{
public:
  Recoil();
  ~Recoil();

  void SetRecoilA(G4int A){RecoilA=A;     G4cout<<"----> Recoil A set to              "<<RecoilA<< G4endl;};
  void SetRecoilZ(G4int Z){RecoilZ=Z;     G4cout<<"----> Recoil Z set to              "<<RecoilZ<< G4endl;};
  void SetRecoilEx(G4int Ex){RecoilEx=Ex;   G4cout<<"----> Recoil Ex set to             "<<RecoilEx/MeV<<" MeV"<< G4endl;};
  void SetRecoilTau(G4int Tau){RecoilTau=Tau;G4cout<<"----> Recoil decay lifetime set to "<<RecoilTau/ns*1000.<<" ps "<< G4endl;};
  G4int getA(){return RecoilA;};
  G4int getZ(){return RecoilZ;};
  G4int getEx(){return RecoilEx;};
  G4int getTau(){return RecoilTau;};
  void Report();

private:

  G4int RecoilA;
  G4int RecoilZ;
  G4int RecoilEx;
  G4int RecoilTau;

};

#endif


           
