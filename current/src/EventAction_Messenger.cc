#include "EventAction_Messenger.hh"


EventAction_Messenger::EventAction_Messenger(EventAction* Chamb)
  :aEventAction(Chamb)
{ 
 
  EventActionDir = new G4UIdirectory("/Trigger/");
  EventActionDir->SetGuidance("Trigger control.");
 
  GSCmd = new G4UIcmdWithoutParameter("/Trigger/GammaSingles",this);
  GSCmd->SetGuidance("Select gamma singles events");  

  TACmd = new G4UIcmdWithAnInteger("/Trigger/A",this);
  TACmd->SetGuidance("Select the mass number for particles to trigger on.");
  //TACmd->SetParameterName("Trigger A",false);
  TACmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TZCmd = new G4UIcmdWithAnInteger("/Trigger/Z",this);
  TZCmd->SetGuidance("Select the atomic number for particles to trigger on.");
  //TZCmd->SetParameterName(Trigger Z",false);
  TZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TAZCmd = new G4UIcmdWithoutParameter("/Trigger/DefinedParticleSingles",this);
  TAZCmd->SetGuidance("Select CsI singles events for the particle defined by /Trigger/A and /Trigger/Z");

  TAZCCmd = new G4UIcmdWithoutParameter("/Trigger/DefinedParticleCoinc",this);
  TAZCCmd->SetGuidance("Select CsI particle-particle coincidence events for the particle defined by /Trigger/A and /Trigger/Z");
  
  TAZCGCmd = new G4UIcmdWithoutParameter("/Trigger/DefinedParticleCoincAndGamma",this);
  TAZCGCmd->SetGuidance("Select CsI particle-particle coincidence AND gamma singles events for the particle defined by /Trigger/A and /Trigger/Z");

  TIDCmd = new G4UIcmdWithAnInteger("/Trigger/CsIDetectorID",this);
  TIDCmd->SetGuidance("Select the CsI detector (1-24) to trigger on.  A value of 0 means all detectors are used.");
  
  TDGCCmd = new G4UIcmdWithAString("/Trigger/DisableGriffinDetCol",this);
  TDGCCmd->SetGuidance("Disable the specified crystal of the specified HPGe.");
  TDGCCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  TDGCmd = new G4UIcmdWithAString("/Trigger/DisableGriffin",this);
  TDGCmd->SetGuidance("Disable all crystals of the specified HPGe.");
  TDGCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


}



EventAction_Messenger::~EventAction_Messenger()
{

  delete EventActionDir;
  delete GSCmd;
  delete TACmd;
  delete TZCmd;
  delete TAZCmd;
  delete TAZCCmd;
  delete TAZCGCmd;
  delete TIDCmd;
  delete TDGCCmd;
  delete TDGCmd;
}


void EventAction_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 

  // gamma singles
 if( command == GSCmd )
   { aEventAction->SetTriggerGammaSing(); }

 // user defined particle singles
 if( command == TAZCmd )
   { aEventAction->SetTriggerParticleSing(); }

 // user defined particle-particle concidences
 if( command == TAZCCmd )
   { aEventAction->SetTriggerParticleCoinc(); }
   
 // user defined particle-particle concidences
 if( command == TAZCGCmd )
   { aEventAction->SetTriggerParticleCoincAndGamma(); }

 //A and Z of user defined particle
 if( command == TACmd )
   { aEventAction->setTriggerA(TACmd->GetNewIntValue(newValue));}
 if( command == TZCmd )
   { aEventAction->setTriggerZ(TZCmd->GetNewIntValue(newValue));}

 if( command == TIDCmd )
   { aEventAction->setTID(TIDCmd->GetNewIntValue(newValue));}
   
  if( command == TDGCCmd )
    {
      int det,col;
      if(sscanf(newValue,"%i %i",&det,&col)==2)
        if(((det-1)>=0)&&(col>=0))
          if((det-1)<16)
            if(col<4)
              {
                aEventAction->DisableGriffinCryst(det-1,col);
                G4cout<<"Disabling Griffin detector "<< det <<", crystal "<< col << "." <<G4endl;
              }
          
    }

  if( command == TDGCmd )
    {
      int det;
      if(sscanf(newValue,"%i",&det)==1)
        if((det-1)>=0)
          if((det-1)<16)
            for(int i=0;i<4;i++)
              {
                aEventAction->DisableGriffinCryst(det-1,i);
                G4cout<<"Disabling Griffin detector "<< det <<", crystal "<< i << "." <<G4endl;
              }
          
    }

}

