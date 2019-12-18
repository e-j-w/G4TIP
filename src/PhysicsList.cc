#include "PhysicsList.hh"

PhysicsList::PhysicsList(Projectile *Proj, DetectorConstruction *Det)
    : theProjectile(Proj), theDetector(Det) {
  stepSize = 0.05 * um;
}

PhysicsList::~PhysicsList() { ; }

void PhysicsList::ConstructParticle() {
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program.

  G4BosonConstructor bsConstructor;
  bsConstructor.ConstructParticle();
  G4LeptonConstructor lConstructor;
  lConstructor.ConstructParticle();
  G4MesonConstructor mConstructor;
  mConstructor.ConstructParticle();
  G4BaryonConstructor brConstructor;
  brConstructor.ConstructParticle();

  //  ions
  G4IonConstructor iConstructor;
  iConstructor.ConstructParticle();
}

void PhysicsList::ConstructProcess() {
  // Define transportation process

  AddTransportation();
  ConstructEM();
}

void PhysicsList::ConstructEM() {
  G4cout << "Setting up physics..." << G4endl;
  G4cout << "Step size: " << stepSize / um << " um" << G4endl;
  if (customStopping)
    G4cout
        << "Will use custom GenericIon stopping power tables from directory: "
        << cspath << G4endl;
  else
    G4cout << "Will use default GenericIon stopping power tables." << G4endl;

  // theParticleIterator->reset();
  GetParticleIterator()->reset();

  while ((*GetParticleIterator())()) {

    G4ParticleDefinition *particle = GetParticleIterator()->value();
    G4ProcessManager *pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();

    // G4cout<<"++++ Particle name ="<<particleName<<G4endl;
    if (particleName == "gamma") {
      pmanager->AddDiscreteProcess(new G4PhotoElectricEffect());
      pmanager->AddDiscreteProcess(new G4ComptonScattering());
      pmanager->AddDiscreteProcess(new G4GammaConversion());
    } else if (particleName == "e-") {
      pmanager->AddProcess(new G4eMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4eIonisation, -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung, -1, 3, 3);
    } else if (particleName == "e+") {
      pmanager->AddProcess(new G4eMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4eIonisation, -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung, -1, 3, 3);
      pmanager->AddProcess(new G4eplusAnnihilation, 0, -1, 4);
    } else if (particleName == "proton") {
      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation, -1, 2, 2);
    } else if (particleName == "alpha") {
      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      G4ionIonisation *alphaIoni = new G4ionIonisation();
      alphaIoni->SetStepFunction(0.05, 0.05 * um);
      pmanager->AddProcess(alphaIoni, -1, 2, 2);
      // pmanager->AddProcess(new G4NuclearStopping(),   -1, 3,-1); // small for
      // light particles
      pmanager->AddProcess(new G4StepLimiter, -1, -1, 4); // what does this do?
    } else if (particleName == "GenericIon") {
      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);

      /*//Added by JW
      G4ScreenedNuclearRecoil* nucr = new G4ScreenedNuclearRecoil();
      G4double energyLimit = 100.*GeV;
      nucr->SetMaxEnergyForScattering(energyLimit);
      pmanager->AddDiscreteProcess(nucr);*/

      /*//Added by JW
      G4CoulombScattering* cs = new G4CoulombScattering();
      cs->AddEmModel(0, new G4IonCoulombScatteringModel());
      pmanager->AddDiscreteProcess(cs);*/

      G4ionIonisation *ionIoni = new G4ionIonisation();
      G4IonParametrisedLossModel *theModel =
          new G4IonParametrisedLossModel(); // ICRU 73 based model, valid for Z
                                            // = 3 to 26, modified by JW to
                                            // allow for custom stopping powers
      if (customStopping) {
        theModel->RemoveDEDXTable("ICRU73");
        theModel->AddDEDXTable("Custom", new SFUIonStoppingData(cspath),
                               new G4IonDEDXScalingICRU73()); // add stopping
                                                              // power data from
                                                              // data files
      }
      ionIoni->SetStepFunction(
          0.05, stepSize); // small step size needed for short lifetimes?
      ionIoni->SetEmModel(theModel);
      pmanager->AddProcess(ionIoni, -1, 3, 2);
      pmanager->AddProcess(new G4NuclearStopping(), -1, 4, -1);
      theReaction = new ReactionFusEvap(theProjectile, theDetector);
      theReactionMessenger = new Reaction_Messenger(
          theReaction); // this line needed here but not in Aaron's RDM code
      pmanager->AddProcess(theReaction, -1, -1, 3);
      pmanager->AddProcess(new G4StepLimiter, -1, -1, 4);
    } else if (particleName == "neutron") {
      if (useNeutrons) {
        // elastic scattering
        // This scheme copied from geant4 application developer guide sec
        // 5.2.2.4.
        // Old scheme from geant4.9.4 which doesn't compile anymore was
        // commented out.
        G4HadronElasticProcess *theElasticProcess = new G4HadronElasticProcess;
        // Cross Section Data set
        G4NeutronHPElasticData *theHPElasticData = new G4NeutronHPElasticData;
        theElasticProcess->AddDataSet(theHPElasticData);
        G4NeutronHPThermalScatteringData *theHPThermalScatteringData =
            new G4NeutronHPThermalScatteringData;
        theElasticProcess->AddDataSet(theHPThermalScatteringData);
        // Models
        G4NeutronHPElastic *theElasticModel = new G4NeutronHPElastic;
        theElasticModel->SetMinEnergy(4.0 * eV);
        theElasticProcess->RegisterMe(theElasticModel);
        G4NeutronHPThermalScattering *theNeutronThermalElasticModel =
            new G4NeutronHPThermalScattering;
        theNeutronThermalElasticModel->SetMaxEnergy(4.0 * eV);
        theElasticProcess->RegisterMe(theNeutronThermalElasticModel);

        /*G4HadronElasticProcess* theElasticProcess = new
          G4HadronElasticProcess();
          G4LElastic* theElasticModel = new G4LElastic;
          theElasticProcess->RegisterMe(theElasticModel);*/
        pmanager->AddDiscreteProcess(theElasticProcess);
        // inelastic scattering
        G4NeutronInelasticProcess *theInelasticProcess =
            new G4NeutronInelasticProcess("inelastic");
        G4NeutronHPInelastic *theInelasticModel =
            new G4NeutronHPInelastic; // new for geant4.10.1
        // G4LENeutronInelastic* theInelasticModel = new G4LENeutronInelastic;
        // //for geant4.9.4
        theInelasticProcess->RegisterMe(theInelasticModel);
        pmanager->AddDiscreteProcess(theInelasticProcess);
        // fission
        G4HadronFissionProcess *theFissionProcess = new G4HadronFissionProcess;
        G4LFission *theFissionModel = new G4LFission;
        theFissionProcess->RegisterMe(theFissionModel);
        pmanager->AddDiscreteProcess(theFissionProcess);
        // capture
        G4HadronCaptureProcess *theCaptureProcess = new G4HadronCaptureProcess;

        G4NeutronHPCapture *theCaptureModel =
            new G4NeutronHPCapture; // new for geant4.10.1
        // G4LCapture* theCaptureModel = new G4LCapture; //for geant4.9.4
        theCaptureProcess->RegisterMe(theCaptureModel);
        pmanager->AddDiscreteProcess(theCaptureProcess);
      } else {
        G4cout << "Neutron interactions are not used in this simulation."
               << G4endl;
      }
    }
  }
}

void PhysicsList::SetCuts() {
  // suppress error messages even in case e/gamma/proton do not exist

  //  G4int temp = GetVerboseLevel();

  // G4double len=1*mm;
  // SetVerboseLevel(0);
  //  " G4VUserPhysicsList::SetCutsWithDefault" method sets
  //   the default cut value for all particle types

  // SetDefaultCutValue(len);
  SetCutsWithDefault();
  // Retrieve verbose level
  // SetVerboseLevel(temp);
  // getc(stdin);
}
