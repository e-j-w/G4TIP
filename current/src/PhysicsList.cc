#include "PhysicsList.hh"

PhysicsList::PhysicsList(Projectile*Proj):theProjectile(Proj)
{

}


PhysicsList::~PhysicsList()
{;}

void PhysicsList::ConstructParticle()
{
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

void PhysicsList::ConstructProcess()
{
  // Define transportation process

  AddTransportation();
  ConstructEM();
}

void PhysicsList::ConstructEM()
{
  theParticleIterator->reset();


  while( (*theParticleIterator)() ){

    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
 

    //  G4cout<<"++++ Particle name ="<<particleName<<G4endl;
    if (particleName == "gamma") {

   
      pmanager->AddDiscreteProcess(new G4PhotoElectricEffect());
      pmanager->AddDiscreteProcess(new G4ComptonScattering());
      pmanager->AddDiscreteProcess(new G4GammaConversion());
 
    }
    else if (particleName == "e-") {
         pmanager->AddProcess(new G4eMultipleScattering,-1,1,1);
	 pmanager->AddProcess(new G4eIonisation,       -1,2,2);
	 pmanager->AddProcess(new G4eBremsstrahlung,   -1,3,3);     
 
    }
    else if (particleName == "e+") {

         pmanager->AddProcess(new G4eMultipleScattering,-1,1,1);
	 pmanager->AddProcess(new G4eIonisation,       -1,2,2);
	 pmanager->AddProcess(new G4eBremsstrahlung,   -1,3,3);   
         pmanager->AddProcess(new G4eplusAnnihilation,  0,-1,4); 
    }
   else if( particleName == "proton" ) {
         pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
	 pmanager->AddProcess(new G4hIonisation,        -1, 2, 2);
    } 
   else if(particleName=="alpha") {
         pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
	 pmanager->AddProcess(new G4ionIonisation,        -1, 2, 2);
    } 
    else if( particleName == "GenericIon") {
          pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
	  G4ionIonisation* ionIoni = new G4ionIonisation();
	  G4IonParametrisedLossModel* theModel= new G4IonParametrisedLossModel();	 
	  //  G4ExtDEDXTable* table = new G4ExtDEDXTable();
	  // theModel -> AddDEDXTable("MyStoppingPowerTable", table);
	  // table -> RetrievePhysicsTable("MyFile.dat");
	  ionIoni->SetEmModel(theModel);
	  ionIoni->SetStepFunction(0.05, 0.05*um);
	  pmanager->AddProcess(ionIoni,                   -1, 2, 2);
	  //	  getc(stdin);
	  //	  theModel->PrintDEDXTable();
	  // table->StorePhysicsTable("test.dat");
	  // table->DumpMap();
	  //	  getc(stdin);
	  pmanager->AddProcess(new G4NuclearStopping(),   -1, 3,-1);
	  theReaction=new Reaction(theProjectile);
	  theReactionMessenger=new Reaction_Messenger(theReaction);
	  pmanager->AddProcess(theReaction,    -1,-1, 3);

	  pmanager->AddProcess(new G4StepLimiter,        -1,-1, 4);

    } else if (particleName == "neutron") {
         
          // elastic scattering
       G4HadronElasticProcess* theElasticProcess = new G4HadronElasticProcess();
         G4LElastic* theElasticModel = new G4LElastic;
         theElasticProcess->RegisterMe(theElasticModel);
         pmanager->AddDiscreteProcess(theElasticProcess);
          // inelastic scattering
         G4NeutronInelasticProcess* theInelasticProcess = 
                                    new G4NeutronInelasticProcess("inelastic");
         G4LENeutronInelastic* theInelasticModel = new G4LENeutronInelastic;
         theInelasticProcess->RegisterMe(theInelasticModel);
         pmanager->AddDiscreteProcess(theInelasticProcess);
          // fission
         G4HadronFissionProcess* theFissionProcess =
                                    new G4HadronFissionProcess;
         G4LFission* theFissionModel = new G4LFission;
         theFissionProcess->RegisterMe(theFissionModel);
         pmanager->AddDiscreteProcess(theFissionProcess);
         // capture
         G4HadronCaptureProcess* theCaptureProcess =
                                    new G4HadronCaptureProcess;
         G4LCapture* theCaptureModel = new G4LCapture;
         theCaptureProcess->RegisterMe(theCaptureModel);
         pmanager->AddDiscreteProcess(theCaptureProcess);
      } 

  }

}
 

void PhysicsList::SetCuts()
{
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

