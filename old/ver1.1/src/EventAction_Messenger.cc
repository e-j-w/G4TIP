#include "EventAction_Messenger.hh"


EventAction_Messenger::EventAction_Messenger(EventAction* Chamb)
  :aEventAction(Chamb)
{ 
 
  EventActionDir = new G4UIdirectory("/Trigger/");
  EventActionDir->SetGuidance("Trigger control.");
 
  GSCmd = new G4UIcmdWithoutParameter("/Trigger/GammaSingles",this);
  GSCmd->SetGuidance("Select gamma singles events");  

  PSCmd = new G4UIcmdWithoutParameter("/Trigger/PINSingles",this);
  PSCmd->SetGuidance("Select PIN singles events");  

  GPCCmd = new G4UIcmdWithoutParameter("/Trigger/GammaPINCoincidences",this);
  GPCCmd->SetGuidance("Select gamma-PIN coincident events");  

}



EventAction_Messenger::~EventAction_Messenger()
{

  delete EventActionDir;
  delete GSCmd;
  delete PSCmd;
  delete GPCCmd;
}


void EventAction_Messenger::SetNewValue(G4UIcommand* command,G4String)
{ 

 if( command == GSCmd )
   { aEventAction->SetTriggerGammaSing();}
 
 if( command == PSCmd )
   { aEventAction->SetTriggerPinSing();}
 
 if( command == GPCCmd )
   { aEventAction->SetTriggerGammaPinCoinc();}
 

}

