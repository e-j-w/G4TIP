#include "Chamber_Messenger.hh"


Chamber_Messenger::Chamber_Messenger(Chamber* Chamb)
  :aChamber(Chamb)
{ 
 
  ChamberDir = new G4UIdirectory("/Chamber/");
  ChamberDir->SetGuidance("Chamber control.");
  
  MatCmd = new G4UIcmdWithAString("/Chamber/Material",this);
  MatCmd->SetGuidance("Select material for the chamber shell.");
  MatCmd->SetParameterName("choice",false);
  MatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
//   RMinCmd = new G4UIcmdWithADoubleAndUnit("/Chamber/Rmin",this);
//   RMinCmd->SetGuidance("Set inner radius for the chamber");
//   RMinCmd->SetParameterName("choice",false);
//   RMinCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

//   RMaxCmd = new G4UIcmdWithADoubleAndUnit("/Chamber/Rmax",this);
//   RMaxCmd->SetGuidance("Set outer radius for the chamber");
//   RMaxCmd->SetParameterName("choice",false);
//   RMaxCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  VisOn = new G4UIcmdWithoutParameter("/Chamber/Visible",this);
  VisOn->SetGuidance("Make exp. hall visible");  

  VisOff = new G4UIcmdWithoutParameter("/Chamber/Invisible",this);
  VisOff->SetGuidance("Make exp. hall invisible");  

  RepCmd = new G4UIcmdWithoutParameter("/Chamber/Report",this);
  RepCmd->SetGuidance("Report exp. hall parameters");  

}



Chamber_Messenger::~Chamber_Messenger()
{
//   delete RMinCmd;
//   delete RMaxCmd;
  delete MatCmd;
  delete ChamberDir;
  delete RepCmd;
  delete VisOn;
  delete VisOff;
}


void Chamber_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == MatCmd )
   { aChamber->setMaterial(newValue);} 
//   if( command == RMinCmd )
//    { aChamber->setRmin(RMinCmd->GetNewDoubleValue(newValue));}
//   if( command == RMaxCmd )
//    { aChamber->setRmax(RMaxCmd->GetNewDoubleValue(newValue));}
 if( command == VisOff )
   { aChamber->setInvisible();}
 if( command == VisOn )
   { aChamber->setVisible();}
  if( command == RepCmd )
   { aChamber->Report();}

}

