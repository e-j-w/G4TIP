#include "DetectorConstruction_Messenger.hh"


DetectorConstruction_Messenger::DetectorConstruction_Messenger(DetectorConstruction* DetCon)
  :aDetCon(DetCon)
{ 
 
  DetConDir = new G4UIdirectory("/Construction/");
  DetConDir->SetGuidance("Dectector construction control.");
  
  ShiftCmd = new G4UIcmdWithADoubleAndUnit("/Construction/TIPChamberZShift",this);
  ShiftCmd->SetGuidance("Shift the TIP chamber (and target, CsI array inside) by the given distance in the z direction.");
  ShiftCmd->SetParameterName("choice",false);
  ShiftCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
	
	BallCmd = new G4UIcmdWithoutParameter("/Construction/UseCsIBall",this);
  BallCmd->SetGuidance("Use the CsI ball array instead of the wall array (which is default).");

}


DetectorConstruction_Messenger::~DetectorConstruction_Messenger()
{
	delete DetConDir;
	delete ShiftCmd;
	delete BallCmd;
}


void DetectorConstruction_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == ShiftCmd )
    { aDetCon->setZShift(ShiftCmd->GetNewDoubleValue(newValue));}

	if( command == BallCmd )
    { aDetCon->UseCsIBall(true);}

}

