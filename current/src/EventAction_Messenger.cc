#include "EventAction_Messenger.hh"


EventAction_Messenger::EventAction_Messenger(EventAction* Chamb)
  :aEventAction(Chamb)
{ 
 
  EventActionDir = new G4UIdirectory("/Trigger/");
  EventActionDir->SetGuidance("Trigger control.");
 
  GSCmd = new G4UIcmdWithoutParameter("/Trigger/GammaSingles",this);
  GSCmd->SetGuidance("Select gamma singles events");  

  PSCmd = new G4UIcmdWithoutParameter("/Trigger/CsISingles",this);
  PSCmd->SetGuidance("Select CsI singles events"); 

  PSRCmd = new G4UIcmdWithoutParameter("/Trigger/CsIRecoilSingles",this);
  PSRCmd->SetGuidance("Select CsI recoil singles events");  

  PSPCmd = new G4UIcmdWithoutParameter("/Trigger/CsIProjectileSingles",this);
  PSPCmd->SetGuidance("Select CsI projectile singles events");  

  GPCCmd = new G4UIcmdWithoutParameter("/Trigger/GammaCsICoincidences",this);
  GPCCmd->SetGuidance("Select gamma-CsI coincident events"); 

  GPRCCmd = new G4UIcmdWithoutParameter("/Trigger/GammaCsIRecoilCoincidences",this);
  GPRCCmd->SetGuidance("Select gamma-CsI recoil coincident events");

  GPPCCmd = new G4UIcmdWithoutParameter("/Trigger/GammaCsIProjectileCoincidences",this);
  GPPCCmd->SetGuidance("Select gamma-CsI projectile coincident events");

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

  // gamma singles
 if( command == GSCmd )
   { aEventAction->SetTriggerGammaSing(); }
 
 // CsI singles (recoil or  projectile)
 if( command == PSCmd )
   { aEventAction->SetTriggerPinSing(); }

 // CsI recoil singles
 if( command == PSRCmd )
   { aEventAction->SetTriggerPinRecoilSing(); }

 // CsI projectile singles
 if( command == PSPCmd )
   { aEventAction->SetTriggerPinProjSing(); }
 
 // gamma-CsI (recoil or  projectile) coinc
 if( command == GPCCmd )
   { aEventAction->SetTriggerGammaPinCoinc(); }

 // gamma-CsI recoil coinc
 if( command == GPRCCmd )
   { aEventAction->SetTriggerGammaPinRecoilCoinc(); }

 // gamma-CsI projectile coinc
 if( command == GPPCCmd )
   { aEventAction->SetTriggerGammaPinProjCoinc(); }
}

