#ifndef Projectile_h
#define Projectile_h 1

#include "globals.hh"
#include "G4UnitsTable.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4DynamicParticle.hh"
#include "Randomize.hh"
using namespace std;

class Projectile
{
public:
  Projectile();
  ~Projectile();
  
public:

  void Report();
  void setA(G4int);
  void setZ(G4int);
  void setKE(G4double); 
  void setfcX(G4double);
  void setfcDX(G4double);
  void setfcY(G4double);
  void setfcDY(G4double);
  void setfcZ(G4double);
  void setmaxAta(G4double);
  void setmaxBta(G4double);
  void setAta0(G4double a){ata0=a;};
  void setBta0(G4double b){bta0=b;};
  void setthef(G4double t){thef=t;};

  G4int getA()    {return A;}
  G4int getZ()    {return Z;}
  G4double getKE(){return KE;};
  G4double getAta0(){return ata0;}
  G4double getBta0(){return bta0;}
  G4ThreeVector getPosition();
  G4ThreeVector getDirection();
  vector<G4double>* getf(){return f;};
  vector<G4double>* getth(){return th;};
  G4double getthef(){return thef;};

private:
  
  G4int A;
  G4int Z;
  G4double KE;
  G4double fcX;
  G4double fcDX;
  G4double fcY;
  G4double fcDY;
  G4double fcZ;
  G4double maxAta;
  G4double maxBta;
  G4double ata0;
  G4double bta0;
  vector <G4double> *f;
  vector <G4double> *th;
  G4double thef;
};

#endif


           
