#include "ReactionCoulex_Messenger.hh"


ReactionCoulex_Messenger::ReactionCoulex_Messenger(ReactionCoulex* React)
  :aReaction(React)
{ 
  ReactionDir = new G4UIdirectory("/Coulex/");
  ReactionDir->SetGuidance("Coulomb excitaiton reaction control.");

  SetDCminCmd = new G4UIcmdWithADoubleAndUnit("/Coulex/SetDCmin",this);
  SetDCminCmd->SetGuidance("Set minimum distance of closest approach in fm.");
  SetDCminCmd->SetParameterName("choice",false);
  SetDCminCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  RepDCminCmd = new G4UIcmdWithoutParameter("/Coulex/ReportDCmin",this);
  RepDCminCmd->SetGuidance("Report minimum distance of closest approach in fm");  
}



ReactionCoulex_Messenger::~ReactionCoulex_Messenger()
{
  delete SetDCminCmd;
  delete RepDCminCmd;
}


void ReactionCoulex_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
 if( command == SetDCminCmd )
   { aReaction->SetDCmin(SetDCminCmd->GetNewDoubleValue(newValue));} 

  if( command == RepDCminCmd )
   { aReaction->ReportDCmin();}
}

