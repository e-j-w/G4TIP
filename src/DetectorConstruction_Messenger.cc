#include "DetectorConstruction_Messenger.hh"

DetectorConstruction_Messenger::DetectorConstruction_Messenger(DetectorConstruction* Det)
  :theDetector(Det)
{ 
  // directories 
  DetectorDir = new G4UIdirectory("/Construction/");
  DetectorDir->SetGuidance("Detector construction control.");

  // commands
  RepCmd = new G4UIcmdWithoutParameter("/Construction/Report",this);
  RepCmd->SetGuidance("Report TIP construction parameters");

  STCmd = new G4UIcmdWithADoubleAndUnit("/Construction/ShiftChamber",this);
  STCmd->SetGuidance("Set the position of the TIP chamber along the z (beam) axis");
  STCmd->SetParameterName("choice",false);
  STCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SPCmd = new G4UIcmdWithADoubleAndUnit("/Construction/ShiftPlunger",this);
  SPCmd->SetGuidance("Shift the plunger along the z (beam) axis wrt chamber center");
  SPCmd->SetParameterName("choice",false);
  SPCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  BallCmd = new G4UIcmdWithoutParameter("/Construction/UseCsIBall",this);
  BallCmd->SetGuidance("Use the CsI ball array instead of the wall array (which is default).");

  PlungerCmd = new G4UIcmdWithoutParameter("/Construction/UsePlunger",this);
  PlungerCmd->SetGuidance("Use the TIP plunger as the reaction target (DSAM target is default).");

  DSAMCmd = new G4UIcmdWithoutParameter("/Construction/UseDSAMTarget",this);
  DSAMCmd->SetGuidance("Use the DSAM reaction target.");

  TargetCmd = new G4UIcmdWithoutParameter("/Construction/UseTarget",this);
  TargetCmd->SetGuidance("Use the user-definable reaction target (this is the default).");


}


DetectorConstruction_Messenger::~DetectorConstruction_Messenger()
{
  // directories
  delete DetectorDir;

  // commands
  delete RepCmd;
  delete STCmd;
  delete SPCmd;
  delete BallCmd;
  delete PlungerCmd;
  delete DSAMCmd;
  delete TargetCmd;
}


void DetectorConstruction_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == RepCmd )
    { theDetector->Report(); }

  if( command == STCmd )
    { theDetector->ShiftChamber(STCmd->GetNewDoubleValue(newValue)); }

  if( command == SPCmd )
    { theDetector->ShiftPlunger(SPCmd->GetNewDoubleValue(newValue)); }

  if( command == BallCmd )
    { theDetector->UseCsIBall(true);}

  if( command == PlungerCmd )
    { 
      G4cout << "----> Using the TIP plunger as the reaction target" << G4endl;
      theDetector->SetUsePlunger();
    }

  if( command == DSAMCmd )
    { 
      G4cout << "----> Using the TIP DSAM reaction target" << G4endl;
      theDetector->SetUseDSAMTarget();
    }

  if( command == TargetCmd )
    { 
      G4cout << "----> Using the user-definable reaction target" << G4endl;
      theDetector->SetUseArbitraryTarget();
    }
  
}

