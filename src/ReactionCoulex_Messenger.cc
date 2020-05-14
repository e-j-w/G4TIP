#include "ReactionCoulex_Messenger.hh"


ReactionCoulex_Messenger::ReactionCoulex_Messenger(ReactionCoulex* React)
  :aReaction(React)
{ 
  ReactionDir = new G4UIdirectory("/Reaction/");
  ReactionDir->SetGuidance("Reaction control.");

  SetDCminCmd = new G4UIcmdWithADouble("/Reaction/SetDCmin",this);
  SetDCminCmd->SetGuidance("Set minimum distance of closest approach in fm.");
  SetDCminCmd->SetParameterName("choice",false);
  SetDCminCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  RepDCminCmd = new G4UIcmdWithoutParameter("/Reaction/ReportDCmin",this);
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

