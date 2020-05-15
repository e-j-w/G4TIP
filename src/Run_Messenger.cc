#include "Run_Messenger.hh"


Run_Messenger::Run_Messenger(G4RunManager* rm, PhysicsList* physl)
:theRunManager(rm),thePhysicsList(physl)
{ 
 
  thePLDir = new G4UIdirectory("/Physics/");
  thePLDir->SetGuidance("Run physics control.");
  
  theRDir = new G4UIdirectory("/Run/");
  theRDir->SetGuidance("Run control.");
  
  PLSCmd = new G4UIcmdWithADoubleAndUnit("/Physics/Step",this);
  PLSCmd->SetGuidance("Set the step size for ion physics in the simulation.");
  PLSCmd->SetParameterName("Step size",false);
  PLSCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  ICmd = new G4UIcmdWithoutParameter("/Run/Initialize",this);
  ICmd->SetGuidance("Initialize the run.");
  
  CSCmd = new G4UIcmdWithAString("/Physics/StoppingTable",this);
  CSCmd->SetGuidance("Use stopping power tables from the path specified.");
  CSCmd->SetParameterName("File path",false);
  CSCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  NCmd = new G4UIcmdWithoutParameter("/Physics/IgnoreNeutrons",this);
  NCmd->SetGuidance("Ignore neutron interactions when constructing physics (makes things faster).");

  FusEvapCmd = new G4UIcmdWithoutParameter("/Physics/FusionEvaporation",this);
  FusEvapCmd->SetGuidance("Use the fusion-evaporation reaction mechanism (set by default).");

  CoulexCmd = new G4UIcmdWithoutParameter("/Physics/Coulex",this);
  CoulexCmd->SetGuidance("Use the Coulomb excitation reaction mechanism.");

}



Run_Messenger::~Run_Messenger()
{
  delete PLSCmd;
  delete CSCmd;
  delete NCmd;
  delete FusEvapCmd;
  delete CoulexCmd;
}


void Run_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 

  if( command == PLSCmd )
    {
      thePhysicsList->setStepSize(PLSCmd->GetNewDoubleValue(newValue));
    }
  if( command == ICmd )
    {
      G4cout << "---------- INITIALIZING RUN ----------"<< G4endl;
      theRunManager->Initialize();
      G4cout << "---------- DONE RUN INITIALIZATION ----------"<< G4endl;
    }
  if( command == CSCmd )
    {
      thePhysicsList->setcspath(newValue);
      thePhysicsList->setcs();
    }
  if( command == NCmd )
    {
      thePhysicsList->setUseNeutrons(false);
    }
  if( command == FusEvapCmd )
    {
      G4cout << "----> Using the fusion-evaporation reaction mechanism" << G4endl;
      thePhysicsList->setReactionType(0);
    }
  if( command == CoulexCmd )
    {
      G4cout << "----> Using the Coulomb excitation reaction mechanism" << G4endl;
      thePhysicsList->setReactionType(1);
    }

}

