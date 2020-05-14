#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4ParticleTypes.hh"
#include "G4ProcessManager.hh"
#include "G4VUserPhysicsList.hh"

// gamma

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

// e-/e+
#include "G4eBremsstrahlung.hh"
#include "G4eIonisation.hh"
#include "G4eMultipleScattering.hh"
#include "G4eplusAnnihilation.hh"
// ions
#include "G4CoulombScattering.hh"
#include "G4IonConstructor.hh"
#include "G4IonCoulombScatteringModel.hh"
#include "G4IonTable.hh"
#include "G4StepLimiter.hh"
#include "G4hIonisation.hh"
#include "G4hMultipleScattering.hh"
#include "G4ionIonisation.hh"
//#include "G4ScreenedNuclearRecoil.hh" //only in newer GEANT4 versions?
#include "G4IonDEDXScalingICRU73.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4IonStoppingData.hh"
#include "G4NuclearStopping.hh"

// neutrons
//#include "G4LElastic.hh"
#include "G4LFission.hh"
#include "G4NeutronHPElastic.hh"
#include "G4NeutronHPElasticData.hh"
#include "G4NeutronHPThermalScattering.hh"
#include "G4NeutronHPThermalScatteringData.hh"
//#include "G4LCapture.hh"
#include "G4NeutronHPCapture.hh"
//#include "G4LENeutronInelastic.hh"
#include "G4HadronCaptureProcess.hh"
#include "G4HadronElasticProcess.hh"
#include "G4HadronFissionProcess.hh"
#include "G4NeutronHPInelastic.hh"
#include "G4NeutronInelasticProcess.hh"

#include "G4BaryonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"

#include "Recoil.hh"
#include "Projectile.hh"
#include "ReactionFusEvap.hh"
#include "ReactionFusEvap_Messenger.hh"
#include "ReactionCoulex.hh"
#include "ReactionCoulex_Messenger.hh"

using namespace CLHEP;

class PhysicsList : public G4VUserPhysicsList {
public:
  PhysicsList(Projectile *, Recoil *, DetectorConstruction *);
  ~PhysicsList();

  int getReactionType() { return reactionType; };
  ReactionFusEvap *getReactionFusEvap() { return theReactionFusEvap; };
  ReactionCoulex *getReactionCoulex() { return theReactionCoulex; };
  void setStepSize(double ss) { stepSize = ss; };
  void setcs() { customStopping = true; };
  void setcspath(const char *csp) { strcpy(cspath, csp); };
  void setUseNeutrons(bool val) { useNeutrons = val; };
  void setReactionType(int val) { reactionType = val; };

protected:
  // Construct particle and physics process
  void ConstructParticle();
  void ConstructProcess();
  void ConstructEM();
  void SetCuts();

private:
  Recoil *theRecoil;
  Projectile *theProjectile;
  DetectorConstruction *theDetector;
  ReactionFusEvap *theReactionFusEvap;
  ReactionFusEvap_Messenger *theReactionFusEvapMessenger;
  ReactionCoulex *theReactionCoulex;
  ReactionCoulex_Messenger *theReactionCoulexMessenger;
  double stepSize;
  bool customStopping;
  bool useNeutrons = true;
  int reactionType; //0=fusion-evaporation, 1=coulex
  char cspath[256];
};

#endif
