#ifndef ReactionCoulex_h
#define ReactionCoulex_h 1

#include "G4ios.hh"
#include "globals.hh"
#include "G4VProcess.hh"
#include "DetectorConstruction.hh"
#include "GammaDecayChannel.hh"
#include "Recoil.hh"
#include "Projectile.hh"
#include "G4VParticleChange.hh" // standard particle change 
//#include "ParticleChange.hh"      // custom particle change
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4UnitsTable.hh"
#include "G4UserLimits.hh"
#include "G4DecayTable.hh"
#include "G4DynamicParticle.hh"
#include "G4ParticleTable.hh"
#include "G4Track.hh"
#include "G4Decay.hh" // standard decay
//#include "Decay.hh" // custom decay
#include "Common.hh"
#include <math.h>

using namespace std;

#define  EPSILON 0.00001

class ReactionCoulex : public G4VProcess 
{
public:     
  G4bool reaction_here;
  
  ReactionCoulex(Projectile*,Recoil*, const G4String& processName ="ReactionCoulex" );

  virtual ~ReactionCoulex();

 
 
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

  void     TargetFaceCrossSection();
  G4int    getTargetRecoilA(){return A2;};
  G4int    getTargetRecoilZ(){return Z2;};
  G4double GetTargetFaceCrossSection(){return sigmaFace;};// in barns
  G4double GetThickTargetCorrection(){return sumWeights/(sumProj+dropRand);};
  G4double GetThickTargetCrossSection(){return sumWeights/(sumProj+dropRand)*sigmaFace;};// in barns
  G4int    GetNumberOfSimulatedReactions(){return sumProj;};
  G4int    GetRxnDroppedE(){return dropE;};
  G4int    GetRxnDroppedKsi(){return dropKsi;};
  G4int    GetRxnDroppedRand(){return dropRand;};
  G4bool   GetProjEx(){return ProjEx;};
  void     ReportDCmin(){printf("Minimum istnace of closest approach = %.2f fm\n",dcmin);};
  void     SetDCmin(G4double d){dcmin = d;};

  Projectile* getProjectile() { return theProjectile; };
  Recoil*     getRecoil() { return theRecoil; };
  
private:
  
  // hide assignment operator as private 
  ReactionCoulex& operator=(const ReactionCoulex&){return *this;};

  Recoil     *theRecoil;
  Projectile *theProjectile;
 
  G4int    Calcfthksi(double,vector<G4double>*);
  void     SetupLookupGenerator(G4double fksi);
  G4double GetTheta();
  G4double FineThetaFunction(G4double,G4double,G4double,G4double,G4double,G4double,G4double);
  G4bool   SetupReactionProducts(const G4Track &,G4DynamicParticle*,G4DynamicParticle*);
  G4double GetKsi(G4double);
  G4double GetfKsi(G4double);
  G4double dfdOmega(G4double,G4double);
  G4double dfofTheta(G4double,vector<G4double>*);
 
  G4ThreeVector posIn;
  G4int ReactionFlag;

  vector<G4double> ksiArray;
  vector<G4double> fksiArray;
  vector<G4double> thetaArray;
  vector<G4double> th000;
  vector<G4double> th010;
  vector<G4double> th020;
  vector<G4double> th030;
  vector<G4double> th040;
  vector<G4double> th050;
  vector<G4double> th060;
  vector<G4double> th070;
  vector<G4double> th080;
  vector<G4double> th090;
  vector<G4double> th100;
  vector<G4double> th110;
  vector<G4double> th120;
  vector<G4double> th130;
  vector<G4double> th140;
  vector<G4double> th150;
  vector<G4double> th160;
  vector<G4double> th170;
  vector<G4double> th180;
  vector<vector<G4double> > fthksi;
  vector<G4double> thefth;
  vector<G4double> thbin;
  vector<G4double> fbin;
  vector<G4int> thlookup;
  G4double thef;
  G4double sigmaFace;
  G4double sumWeights;
  G4int    sumProj;
  G4int    dropRand,dropE,dropKsi;
  G4double ksiFace;
  G4double EprimeFace;
  G4double A1,Z1,A2,Z2;
  G4bool   ProjEx; //true if the projectile is excited (and decays), false if the recoil is excited
  G4double Ex1,Ex2;
  G4double BE2;
  G4double DE,DEp;

  G4Decay *decay; // standard decy
  //static Decay decay; // custom decay

  G4double dcmin; // minimum allowed distance of closest approach in fm

  G4ParticleDefinition* proj;
  G4ParticleDefinition* rec;

  G4double theWeight;
};

#endif

