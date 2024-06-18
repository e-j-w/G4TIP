#include "EventAction_Messenger.hh"


EventAction_Messenger::EventAction_Messenger(EventAction* Chamb):aEventAction(Chamb)
{ 
 
  EventActionDir = new G4UIdirectory("/Trigger/");
  EventActionDir->SetGuidance("Trigger control.");
 
  GSCmd = new G4UIcmdWithoutParameter("/Trigger/GammaSingles",this); //THIS TRIGGER HAS ISSUES WHEN THE BEAM IS THE SAME SPECIES AS THE PARTICLE DEFINED IN /Trigger/A, /Trigger/Z
  GSCmd->SetGuidance("Select gamma singles events");  

  TACmd = new G4UIcmdWithAnInteger("/Trigger/A",this);
  TACmd->SetGuidance("Select the mass number for particles to trigger on.");
  //TACmd->SetParameterName("Trigger A",false);
  TACmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TZCmd = new G4UIcmdWithAnInteger("/Trigger/Z",this);
  TZCmd->SetGuidance("Select the atomic number for particles to trigger on.");
  //TZCmd->SetParameterName(Trigger Z",false);
  TZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TARangeCmd = new G4UIcmdWithAString("/Trigger/ARange",this);
  TARangeCmd->SetGuidance("Select the mass number range for particles to trigger on.");
  TARangeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TZRangeCmd = new G4UIcmdWithAString("/Trigger/ZRange",this);
  TZRangeCmd->SetGuidance("Select the atomic number range for particles to trigger on.");
  TZRangeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TAZCmd = new G4UIcmdWithoutParameter("/Trigger/DefinedParticleSingles",this);
  TAZCmd->SetGuidance("Select CsI singles events for the particle defined by /Trigger/A and /Trigger/Z");

  TAZ1Cmd = new G4UIcmdWithoutParameter("/Trigger/DefinedParticleSingleHit",this);
  TAZ1Cmd->SetGuidance("Select CsI singles events for the particle defined by /Trigger/A and /Trigger/Z, with a single hit restriction.");

  TAZCCmd = new G4UIcmdWithoutParameter("/Trigger/DefinedParticleCoinc",this);
  TAZCCmd->SetGuidance("Select CsI particle-particle coincidence events for the particle defined by /Trigger/A and /Trigger/Z");
  
  TAZGCmd = new G4UIcmdWithoutParameter("/Trigger/DefinedParticleAndGamma",this);
  TAZGCmd->SetGuidance("Select CsI particle AND gamma singles events for the particle defined by /Trigger/A and /Trigger/Z");

  TAZCGCmd = new G4UIcmdWithoutParameter("/Trigger/DefinedParticleCoincAndGamma",this);
  TAZCGCmd->SetGuidance("Select CsI particle-particle coincidence AND gamma singles events for the particle defined by /Trigger/A and /Trigger/Z");
  
  TAZC2GCmd = new G4UIcmdWithoutParameter("/Trigger/DefinedParticleCoincAnd2GammaCores",this);
  TAZC2GCmd->SetGuidance("Select CsI particle-particle coincidence AND gamma events in 2 GRIFFIN cores for the particle defined by /Trigger/A and /Trigger/Z.  Inspired by the Nov 2013 S1232 experiment.");

  TIDCmd = new G4UIcmdWithAnInteger("/Trigger/CsIDetectorID",this);
  TIDCmd->SetGuidance("Select the CsI detector (1-24) to trigger on.  A value of 0 means all detectors are used.");
  
  TDGCCmd = new G4UIcmdWithAString("/Trigger/DisableGriffinDetCol",this);
  TDGCCmd->SetGuidance("Disable the specified crystal of the specified HPGe.");
  TDGCCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  TDGCmd = new G4UIcmdWithAString("/Trigger/DisableGriffin",this);
  TDGCmd->SetGuidance("Disable all crystals of the specified HPGe.");
  TDGCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  TDCCmd = new G4UIcmdWithAString("/Trigger/DisableCsI",this);
  TDCCmd->SetGuidance("Disable the specified CsI detector.");
  TDCCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  TDCRCmd = new G4UIcmdWithAString("/Trigger/DisableCsIRange",this);
  TDCRCmd->SetGuidance("Disable the CsI detectors within the specified range.");
  TDCRCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TWCRCmd = new G4UIcmdWithAString("/Trigger/WeightCsIRange",this);
  TWCRCmd->SetGuidance("Weight the CsI detectors within the specified range.");
  TWCRCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  CETCmd = new G4UIcmdWithADoubleAndUnit("/Trigger/CsIThreshold",this);
  CETCmd->SetGuidance("Set a low energy threshold for the CsI detector(s).");
  CETCmd->SetParameterName("CET",false);
  CETCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  CELTCmd = new G4UIcmdWithAString("/Trigger/CsILinearThreshold",this);
  CELTCmd->SetGuidance("Set a linear low energy threshold for the CsI detector(s), specifying the energy range over which the threshold occurs, in MeV.");
  CELTCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  GETCmd = new G4UIcmdWithADoubleAndUnit("/Trigger/GammaThreshold",this);
  GETCmd->SetGuidance("Set a low energy threshold for gamma rays.");
  GETCmd->SetParameterName("GET",false);
  GETCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  RTCmd = new G4UIcmdWithoutParameter("/Trigger/ReportNumTriggers",this);
  RTCmd->SetGuidance("Report the number of triggered events.");

}

EventAction_Messenger::~EventAction_Messenger()
{

  delete EventActionDir;
  delete GSCmd;
  delete TACmd;
  delete TZCmd;
  delete TARangeCmd;
  delete TZRangeCmd;
  delete TAZCmd;
  delete TAZ1Cmd;
  delete TAZCCmd;
  delete TAZGCmd;
  delete TAZCGCmd;
  delete TAZC2GCmd;
  delete TIDCmd;
  delete TDGCCmd;
  delete TDGCmd;
  delete TDCCmd;
  delete TDCRCmd;
  delete TWCRCmd;
  delete CETCmd;
  delete CELTCmd;
  delete RTCmd;
}


void EventAction_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 

  // gamma singles
  if( command == GSCmd ){
    aEventAction->SetTriggerGammaSing();
  }

  // user defined particle singles
  if( command == TAZCmd ){
    aEventAction->SetTriggerParticleSing();
  }
  if( command == TAZ1Cmd ){
    aEventAction->SetTriggerParticleSing1Hit();
  }

  // user defined particle-particle concidences
  if( command == TAZCCmd ){
    aEventAction->SetTriggerParticleCoinc();
  }
   
  // user defined particle-gamma concidences
  if( command == TAZGCmd ){
    aEventAction->SetTriggerParticleAndGamma();
  }
  if( command == TAZCGCmd ){
    aEventAction->SetTriggerParticleCoincAndGamma();
  }
  if( command == TAZC2GCmd ){
    aEventAction->SetTriggerParticleCoincAnd2GammaCores();
  }

  //A and Z of user defined particle
  if( command == TACmd ){
    aEventAction->setTriggerA(TACmd->GetNewIntValue(newValue));
  }
  if( command == TZCmd ){
    aEventAction->setTriggerZ(TZCmd->GetNewIntValue(newValue));
  }

  if( command == TARangeCmd ){
    int min,max;
    if(sscanf(newValue,"%i %i",&min,&max)==2){
      aEventAction->setTriggerARange(min,max);
    }
  }
  if( command == TZRangeCmd ){
    int min,max;
    if(sscanf(newValue,"%i %i",&min,&max)==2){
      aEventAction->setTriggerZRange(min,max);
    }
  }

  if( command == TIDCmd ){
    aEventAction->setTID(TIDCmd->GetNewIntValue(newValue));
  }
   
  if( command == TDGCCmd ){
    int det,col;
    if(sscanf(newValue,"%i %i",&det,&col)==2)
      if(((det-1)>=0)&&(col>=0))
        if((det-1)<16)
          if(col<4){
            aEventAction->DisableGriffinCryst(det-1,col);
            G4cout<<"Disabling Griffin detector "<< det <<", crystal "<< col << "." <<G4endl;
          }
  }

  if( command == TDGCmd ){
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
  
  if( command == TDCCmd ){
    int det;
    if(sscanf(newValue,"%i",&det)==1){
      if(det>0){
        if(det<=NCsISph){
          aEventAction->DisableCsI(det-1);
          G4cout<<"Disabling CsI detector "<< det << "." <<G4endl;
        }
      }
    }
  }
  
  if( command == TDCRCmd ){
    int detLow,detHigh;
    if(sscanf(newValue,"%i %i",&detLow,&detHigh)==2){
      if((detLow>0)&&(detHigh>=detLow)){
        if(detHigh<=NCsISph){
          G4cout<<"Disabling CsI detectors "<< detLow << " to " << detHigh << "." <<G4endl;
          for(int i=detLow;i<=detHigh;i++)
            aEventAction->DisableCsI(i-1);
        }
      }
    }else{
      G4cout<<"ERROR: /Trigger/DisableCsIRange command has an invalid string (" << newValue << ")" << G4endl;
      exit(-1);
    }
  }
  
  if( command == TWCRCmd ){
    int detLow,detHigh;
    double weight=0.0;
    if(sscanf(newValue,"%i %i %lf",&detLow,&detHigh,&weight)==3){
      if((detLow>0)&&(detHigh>=detLow)){
        if(detHigh<=NCsISph){
          G4cout<<"Weighting CsI detectors "<< detLow << " to " << detHigh << " with weight " << weight << "." <<G4endl;
          for(int i=detLow;i<=detHigh;i++)
            aEventAction->WeightCsI(i-1,weight);
        }
      }
    }else{
      G4cout<<"ERROR: /Trigger/WeightCsIRange command has an invalid string (" << newValue << ")" << G4endl;
      exit(-1);
    }
  }

  if( command == CETCmd ){
    aEventAction->SetCsIThreshold(CETCmd->GetNewDoubleValue(newValue));
    G4cout << "Setting CsI low energy threshold to "<< CETCmd->GetNewDoubleValue(newValue) << " MeV." << G4endl;
  }

  if( command == GETCmd ){
    aEventAction->SetGammaThreshold(CETCmd->GetNewDoubleValue(newValue)*1000.);
    G4cout << "Setting gamma-ray low energy threshold to "<< CETCmd->GetNewDoubleValue(newValue) << " MeV." << G4endl;
  }

  if( command == CELTCmd ){
    double tLow,tHigh;
    if(sscanf(newValue,"%lf %lf",&tLow,&tHigh)==2){
      if(tHigh>=tLow){
        G4cout<<"Setting CsI low energy linear threshold between "<< tLow << " and " << tHigh << " MeV." <<G4endl;
        aEventAction->SetCsILinearThreshold(tLow,tHigh);
      }else{
        G4cout<<"ERROR: CsI low energy linear threshold has invalid or negative range (" << tLow << " to " << tHigh << ")." << G4endl;
        exit(-1);
      }
    }else{
      G4cout<<"ERROR: /Trigger/CsILinearThreshold command has an invalid string (" << newValue << ")" << G4endl;
      exit(-1);
    }
  }

  if( command == RTCmd ){
    aEventAction->reportTriggers();
  }

}

