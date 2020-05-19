// Simulation program for TIP
// Fusion-evaporation or coulex
// Plunger or DSAM target
// Implements CsI wall and ball arrays

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "DetectorConstruction.hh"
#include "DetectorConstruction_Messenger.hh"
#include "EventAction.hh"
#include "EventAction_Messenger.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "Projectile.hh"
#include "Projectile_Messenger.hh"
#include "Recoil.hh"
#include "Recoil_Messenger.hh"
#include "Results.hh"
#include "Results_Messenger.hh"
#include "RunAction.hh"
#include "Run_Messenger.hh"
#include "SteppingAction.hh"

int main(int argc, char **argv) {

  // Detect interactive mode (if using '-u' argument) and define UI session
  G4UIExecutive* ui = 0;
  if (( argc == 2 )&&(strcmp(argv[1],"-u")==0)) {
    ui = new G4UIExecutive(1, argv);
  }

  // Seed the random number generator manually
  G4long myseed = time(NULL);
  // myseed=1388637269;
  CLHEP::HepRandom::setTheSeed(myseed);
  G4cout << " Seed set to  " << myseed << G4endl;

  // Construct the default run manager
  #ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
  #else
    G4RunManager* runManager = new G4RunManager;
  #endif

  // set mandatory initialization classes
  DetectorConstruction *theDetector = new DetectorConstruction();
  runManager->SetUserInitialization(theDetector);
  DetectorConstruction_Messenger *detectorMessenger;
  detectorMessenger = new DetectorConstruction_Messenger(theDetector);

  // Construct the incoming beam
  Projectile *theProjectile = new Projectile();
  Projectile_Messenger *ProjectileMessenger;
  ProjectileMessenger = new Projectile_Messenger(theProjectile);
  //theProjectile->Report();

  // Construct the outgoing beam (for Coulex)
  Recoil* theRecoil=new Recoil();
  Recoil_Messenger* RecoilMessenger;
  RecoilMessenger = new Recoil_Messenger(theRecoil);
  //theRecoil->Report();

  // Setup physics list
  // Also sets up the reaction
  PhysicsList *thePhysicsList = new PhysicsList(theProjectile, theRecoil, theDetector);
  runManager->SetUserInitialization(thePhysicsList);

  Run_Messenger *runMessenger;
  runMessenger = new Run_Messenger(runManager, thePhysicsList);

  PrimaryGeneratorAction *generatorAction = new PrimaryGeneratorAction(theDetector, theProjectile);
  runManager->SetUserAction(generatorAction);

  Results *results = new Results(theDetector, thePhysicsList);
  Results_Messenger *resultsMessenger;
  resultsMessenger = new Results_Messenger(results);

  RunAction *theRunAction = new RunAction(thePhysicsList, results, theDetector);
  runManager->SetUserAction(theRunAction);

  EventAction *eventAction = new EventAction(results, theRunAction, theProjectile, theDetector);
  runManager->SetUserAction(eventAction);
  EventAction_Messenger *eventActionMessenger;
  eventActionMessenger = new EventAction_Messenger(eventAction);

  SteppingAction *stepAction = new SteppingAction(theDetector, eventAction);
  runManager->SetUserAction(stepAction);

  

  // get the pointer to the UI manager and set verbosities
  G4UImanager *UI = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  if( ! ui ){ 
    // batch mode
    if (argc == 1)
      {  
        G4cout << "G4TIP macro_file" << G4endl;
        G4cout << "----------------" << G4endl;
        G4cout << "Please specify a macro file (.mac) to run as an argument."
              << G4endl;
        exit(-1);
      } else {
        // check whether the macro file exists
        FILE *file;
        file = fopen(argv[1], "r");
        if (file) {
          fclose(file);
        } else {
          G4cout << "ERROR: macro file " << argv[1] << " cannot be opened."
                << G4endl;
          G4cout << "Please check whether the file exists." << G4endl;
          exit(-1);
        }
      }
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UI->ApplyCommand(command + fileName);
  }else{
    // interactive mode
    // Initialize visualization
    G4VisManager* visManager = new G4VisExecutive("quiet");
    visManager->Initialize();
    //UI->ApplyCommand("/control/execute macros/init_vis.mac");
    ui->SessionStart();
    //getc(stdin);
    delete ui;
    delete visManager;
  }

  // job termination
  delete detectorMessenger;
  delete ProjectileMessenger;
  delete RecoilMessenger;
  delete resultsMessenger;
  delete runMessenger;
  delete eventActionMessenger;
  delete runManager;
  
  
  return 0;
}
