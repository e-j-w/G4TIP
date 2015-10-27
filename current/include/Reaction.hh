
#ifndef Reaction_h
#define Reaction_h 1
//atomic mass unit in MeV/c^2 
#define xamu 931.494061 

#include "G4ios.hh"
#include "globals.hh"
#include "G4VProcess.hh"
#include "DetectorConstruction.hh"
#include "GammaDecayChannel.hh"
#include "Projectile.hh"
#include "G4VParticleChange.hh"
#include "G4ParticleChange.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4UnitsTable.hh"
#include "G4UserLimits.hh"
#include "G4DecayTable.hh"
#include "G4DynamicParticle.hh"
#include "G4ParticleTable.hh"
#include "G4Proton.hh"
#include "G4Neutron.hh"
#include "G4Alpha.hh"
#include "G4Track.hh"
#include "G4Decay.hh"
#include "G4RandomDirection.hh"
#include <math.h>

#include "CLHEP/Random/RandGamma.h" //for generating random numbers with a gaussian dist.

using namespace std;

#define  eps 0.00001
#define  MAXNUMEVAP 8
#define  MAXNUMDISTS 2

typedef struct
{
  G4String particle;
  G4double energy;
  G4double fwhm;
} evaporation;

class Reaction : public G4VProcess 
{
  public:     
   G4bool reaction_here;

  Reaction(Projectile*, const G4String& processName ="Reaction" );

     virtual ~Reaction();

 
 
    virtual G4double PostStepGetPhysicalInteractionLength(
                             const G4Track& track,
			     G4double   previousStepSize,
			     G4ForceCondition* condition
			    );

     virtual G4VParticleChange* PostStepDoIt(
			     const G4Track& ,
			     const G4Step& 
			    );
			    
     //  no operation in  AtRestGPIL
     virtual G4double AtRestGetPhysicalInteractionLength(
                             const G4Track& ,
			     G4ForceCondition* 
			    ){ return -1.0; };
			    
     //  no operation in  AtRestDoIt      
     virtual G4VParticleChange* AtRestDoIt(
			     const G4Track& ,
			     const G4Step&
			    ){return NULL;};

     //  no operation in  AlongStepGPIL
     virtual G4double AlongStepGetPhysicalInteractionLength(
                             const G4Track&,
			     G4double  ,
			     G4double  ,
			     G4double& ,
                             G4GPILSelection*
			    ){ return -1.0; };

     //  no operation in  AlongStepDoIt
     virtual G4VParticleChange* AlongStepDoIt(
			     const G4Track& ,
			     const G4Step& 
			    ) {return NULL;};

  
  G4bool SetupReactionProducts(const G4Track &,G4DynamicParticle*);
  void TargetFaceCrossSection();
  void SetTargetMassAndCharge(G4double At,G4double Zt){A2=At;Z2=Zt;};
  void SetEvaporationChannel(G4int n, G4int p, G4int a){nN=n;nP=p;nA=a;};
  void SetEgamma(G4double Eg){Egamma=Eg;};
  void SetTau(G4double t){tau=t;};
  void SetNumberOfProtons(G4int p){nP=p;};
  void SetNumberOfAlphas(G4int a){nA=a;};
  void SetNumberOfNeutrons(G4int n){nN=n;};

  //set properties of raction and emitted particles
  void SetRxnQ(G4double x){QRxn=x;};
  void SetExi(G4double x){initExi=x;};
  void SetEvapQ1(G4double x){QEvap[0]=x;};
  void SetEvapQ2(G4double x){QEvap[1]=x;};
  void SetShift(G4double x){dExiShift=x;};
  void SetRho(G4double x){rho=x;};
  void SetLambda(G4double x){lambda=x;};

  //set angular constraints of emitted particles
  void SetConstrainedAngle(){constrainedAngle=true;};
  void UnsetConstrainedAngle(){constrainedAngle=false;};
  void SetMaxAngle(G4double x){maxEvapAngle=x;};
  void SetMinAngle(G4double x){minEvapAngle=x;};

  void AddEvaporation(G4String,G4double,G4double);
  void EvaporateWithMomentumCorrection(G4DynamicParticle*,G4DynamicParticle*,G4DynamicParticle*,G4ParticleDefinition*,G4double,G4double,G4ThreeVector);
  G4ThreeVector GetCMVelocity(const G4Track &);
  G4int GetNumberOfProtons(){return nP;};
  G4int GetNumberOfAlphas(){return nA;};
  G4int GetNumberOfNeutrons(){return nN;}; 
 

  private:
 
  Projectile *theProjectile;

  G4ParticleDefinition* compound; //the nucleus formed directly after beam-target reaction
  G4ParticleDefinition* residual; //the residual nucleus after particles have evaporated from the compund nucleus
  G4ParticleDefinition* proton,*alpha,*neutron;
  G4bool killTrack;
  static G4Decay decay;
  G4ThreeVector posIn;
  G4double A1,Z1,A2,Z2;
  G4int  nP,nN,nA;
  G4int  maxNumEvap;
  G4bool constrainedAngle; //whether to constrain direction of emitted particles
  G4double maxEvapAngle, minEvapAngle; //at least one evaporated particle must be in this angular range with respect to the beam axis
  G4double Egamma,tau;
  G4double QRxn, QEvap[MAXNUMEVAP]; //Q values for the beam-target reaction and evaporation process(es)
  G4double initExi,evapdeltaExi[MAXNUMEVAP],totalEvapdeltaExi,rho,lambda,dExiShift; //excitation energy parameters
  vector<evaporation> *history;
  
  G4int  loopCounter;
};

#endif

