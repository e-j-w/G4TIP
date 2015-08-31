//DSAM PROGRAM for TIP/PIN wall fusion-evaporation 

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#ifdef G4UI_USE_ROOT
#include "G4UIRoot.hh"
#else
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#endif

#ifdef G4UI_USE_XM
#include "G4UIXm.hh"
#endif


#ifdef G4VIS_USE
#include "VisManager.hh"
#endif


#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "EventAction.hh"
#include "EventAction_Messenger.hh"
#include "Results.hh"
#include "Results_Messenger.hh"
#include "Projectile.hh"
#include "Projectile_Messenger.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"

int main(int argc,char** argv) 
{

 // Seed the random number generator manually
  G4long myseed = time(NULL);
  myseed=1388637269;
  CLHEP::HepRandom::setTheSeed(myseed);
  G4cout<<" Seed set to  "<<myseed<<G4endl;


  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager;
 
  // set mandatory initialization classes
  DetectorConstruction* theDetector=new DetectorConstruction();
  runManager->SetUserInitialization(theDetector);
 
  // Construct the incoming  beam
  Projectile* theProjectile=new Projectile();
  Projectile_Messenger* ProjectileMessenger;
  ProjectileMessenger=new Projectile_Messenger(theProjectile);
  theProjectile->Report();

 
 // set mandatory user action clas
  PhysicsList *thePhysicsList = new PhysicsList(theProjectile);
  runManager->SetUserInitialization(thePhysicsList);
 
 
  PrimaryGeneratorAction* generatorAction= new PrimaryGeneratorAction(theDetector,theProjectile);
  runManager->SetUserAction(generatorAction);

  Results* results = new Results(theProjectile);
  Results_Messenger* resultsMessenger;
  resultsMessenger = new Results_Messenger(results);

  RunAction* theRunAction=new RunAction(thePhysicsList,results,theDetector);
  runManager->SetUserAction(theRunAction);
 
  EventAction* eventAction = new EventAction(results,theRunAction);
  runManager->SetUserAction(eventAction);
  EventAction_Messenger* eventActionMessenger;
  eventActionMessenger = new EventAction_Messenger(eventAction);

  SteppingAction* stepAction = new SteppingAction(theDetector,eventAction);
  runManager->SetUserAction(stepAction);

 

 G4UIsession* session=0;

#ifdef G4VIS_USE  
 G4VisManager* visManager = new VisManager; 
#endif  

  if (argc==1)   // Define UI session for interactive mode.
    {

#ifdef G4VIS_USE
  // visualization manager
  visManager->Initialize();
#endif

      // G4UIterminal is a (dumb) terminal.
#ifdef G4UI_USE_ROOT
  // G4URoot is a ROOT based GUI.
  session = new G4UIRoot(argc,argv);
#else
#ifdef G4UI_USE_XM
      session = new G4UIXm(argc,argv);
#else           
#ifdef G4UI_USE_TCSH
      session = new G4UIterminal(new G4UItcsh);      
#else
      session = new G4UIterminal();
#endif
#endif
#endif
    
  

    }

  // Initialize G4 kernel
  runManager->Initialize();

  // get the pointer to the UI manager and set verbosities
  G4UImanager* UI = G4UImanager::GetUIpointer();

  if (session)   // Define UI session for interactive mode.
    {
      // G4UIterminal is a (dumb) terminal.
      
      #ifdef G4UI_USE_XM
      //   Customize the G4UIXm menubar with a macro file :
           UI->ApplyCommand("/control/execute gui/gui.mac");
      #endif
      session->SessionStart();
      delete session;
    }
  else           // Batch mode
    { 
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UI->ApplyCommand(command+fileName);
    }





  // job termination
  if(argc==1){
#ifdef G4VIS_USE
  delete visManager;
#endif
  }

  
  delete runManager;

  return 0;
}
