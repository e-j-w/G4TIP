#ifndef EvaporationChannel_h
#define EvaporationChannel_h 1

#include "globals.hh"
#include "G4UnitsTable.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4DynamicParticle.hh"
#include "Randomize.hh"
using namespace std;

typedef struct
{
  G4String particle;
  G4double energy;
  G4double fwhm;
} decay;

class EvaporationChannel
{
public:
  EvaporationChannel();
  ~EvaporationChannel();
  
public:

  void Report();
  G4int GetNumberOfProtons(){return nP;};
  G4int GetNumberOfAlphas(){return nA;};
  G4int GetNumberOfNeutrons(){return nN;}; 
  G4double GetEgamma(){return Egamma;};
  G4double GetTau(){return tau;};

  void SetNumberOfProtons(G4int p){nP=p;};
  void SetNumberOfAlphas(G4int a){nA=a;};
  void SetNumberOfNeutrons(G4int n){nN=n;}; 
  void SetEgamma(G4double E){Egamma=E;};
  void SetTau(G4double t){tau=t;};
private:
  
  G4double theEntryRegionEnergy,theEntryRegionWidth;
  G4int    nN,nP,nA;
  G4double Egamma;
  G4double tau;
  vector<decay> *history;
};

#endif


           
