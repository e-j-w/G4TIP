#include "ArbitraryTarget_Messenger.hh"


ArbitraryTarget_Messenger::ArbitraryTarget_Messenger(ArbitraryTarget* Tar)
:aArbitraryTarget(Tar)
{ 
 
  TargetDir = new G4UIdirectory("/Target/");
  TargetDir->SetGuidance("Target control.");

  char str[256], guideStr[256];
  for(int i=0;i<NATARGETLAYERS;i++){

    snprintf(str,256,"/Target/Layer%i/",i+1);
    snprintf(guideStr,256,"Target layer %i control.",i+1);
    TargetLayerDir[i] = new G4UIdirectory(str);
    TargetLayerDir[i]->SetGuidance(guideStr);

    snprintf(str,256,"/Target/Layer%i/Material",i+1);
    snprintf(guideStr,256,"Select material for target layer %i.",i+1);
    TMatCmd[i] = new G4UIcmdWithAString(str,this);
    TMatCmd[i]->SetGuidance(guideStr);
    TMatCmd[i]->SetParameterName("choice",false);
    TMatCmd[i]->AvailableForStates(G4State_PreInit,G4State_Idle);

    snprintf(str,256,"/Target/Layer%i/A",i+1);
    snprintf(guideStr,256,"Set the mass number A for target layer %i.",i+1);
    TMCmd[i] = new G4UIcmdWithAnInteger(str,this);
    TMCmd[i]->SetGuidance(guideStr);
    TMCmd[i]->SetParameterName("choice",false);
    TMCmd[i]->AvailableForStates(G4State_PreInit,G4State_Idle);

    snprintf(str,256,"/Target/Layer%i/Z",i+1);
    snprintf(guideStr,256,"Set the atomic number Z for target layer %i.",i+1);
    TQCmd[i] = new G4UIcmdWithAnInteger(str,this);
    TQCmd[i]->SetGuidance(guideStr);
    TQCmd[i]->SetParameterName("choice",false);
    TQCmd[i]->AvailableForStates(G4State_PreInit,G4State_Idle);

    snprintf(str,256,"/Target/Layer%i/Thickness",i+1);
    snprintf(guideStr,256,"Set the thickness for target layer %i.",i+1);
    TZCmd[i] = new G4UIcmdWithADoubleAndUnit(str,this);
    TZCmd[i]->SetGuidance(guideStr);
    TZCmd[i]->SetParameterName("choice",false);
    TZCmd[i]->AvailableForStates(G4State_PreInit,G4State_Idle);

    snprintf(str,256,"/Target/Layer%i/ThicknessMgCm2",i+1);
    snprintf(guideStr,256,"Set the thickness for target layer %i in mg/cm^2.",i+1);
    TTarCmd[i] = new G4UIcmdWithADouble(str,this);
    TTarCmd[i]->SetGuidance(guideStr);
    TTarCmd[i]->SetParameterName("choice",false);
    TTarCmd[i]->AvailableForStates(G4State_PreInit,G4State_Idle);

    snprintf(str,256,"/Target/Layer%i/Position",i+1);
    snprintf(guideStr,256,"Set the position for target layer %i.",i+1);
    TPCmd[i] = new G4UIcmdWithADoubleAndUnit(str,this);
    TPCmd[i]->SetGuidance(guideStr);
    TPCmd[i]->SetParameterName("choice",false);
    TPCmd[i]->AvailableForStates(G4State_PreInit,G4State_Idle);

    snprintf(str,256,"/Target/Layer%i/AttachToLayer",i+1);
    snprintf(guideStr,256,"Attach target layer %i to another layer.",i+1);
    TACmd[i] = new G4UIcmdWithAString(str,this);
    TACmd[i]->SetGuidance(guideStr);
    TACmd[i]->SetParameterName("choice",false);
    TACmd[i]->AvailableForStates(G4State_PreInit,G4State_Idle);

  }
  
  TRLCmd = new G4UIcmdWithAnInteger("/Target/ReactionLayer",this);
  TRLCmd->SetGuidance("Select the layer of the target which participates in the reaction.");
  TRLCmd->SetParameterName("choice",false);
  TRLCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
 
  TExCmd = new G4UIcmdWithADoubleAndUnit("/Target/Excitation",this);
  TExCmd->SetGuidance("Set energy for target recoil excitation");
  TExCmd->SetParameterName("choice",false);
  TExCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  TTauCmd = new G4UIcmdWithADoubleAndUnit("/Target/Lifetime",this);
  TTauCmd->SetGuidance("Set lifetime for target recoil excitation");
  TTauCmd->SetParameterName("choice",false);
  TTauCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TRCmd = new G4UIcmdWithADoubleAndUnit("/Target/Radius",this);
  TRCmd->SetGuidance("Select radius of the target");
  TRCmd->SetParameterName("choice",false);
  TRCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  NTSCmd = new G4UIcmdWithAnInteger("/Target/NStep",this);
  NTSCmd->SetGuidance("Select the number of steps in the target");
  NTSCmd->SetParameterName("choice",false);
  NTSCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TRepCmd = new G4UIcmdWithoutParameter("/Target/Report",this);
  TRepCmd->SetGuidance("Report target and backing parameters");  
 
}


ArbitraryTarget_Messenger::~ArbitraryTarget_Messenger()
{
  delete TRCmd;  
  delete TRLCmd;
  delete TExCmd;
  delete TTauCmd;
  delete TargetDir;
  delete TRepCmd;
  delete NTSCmd;

  for(int i=0;i<NATARGETLAYERS;i++)
    {
      delete TMatCmd[i];
      delete TZCmd[i];
      delete TMCmd[i];
      delete TQCmd[i];
      delete TPCmd[i];
      delete TTarCmd[i];
      delete TACmd[i];
      delete TargetLayerDir[i];
    }
}

void ArbitraryTarget_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 

  for(int i=0;i<NATARGETLAYERS;i++){
    if( command == TMatCmd[i] ){
      if(aArbitraryTarget->CheckAndAddLayers(i))
        aArbitraryTarget->setTargetMaterial(i, newValue);
      break;
    } 
    if( command == TMCmd[i] ){ 
      if(aArbitraryTarget->CheckAndAddLayers(i))
        aArbitraryTarget->setTargetMass(i, TMCmd[i]->GetNewIntValue(newValue));
      break;
    }
    if( command == TQCmd[i] ){
      if(aArbitraryTarget->CheckAndAddLayers(i)) 
        aArbitraryTarget->setTargetCharge(i, TQCmd[i]->GetNewIntValue(newValue));
      break;
    }
    if( command == TZCmd[i] ){
      if(aArbitraryTarget->CheckAndAddLayers(i)) 
        aArbitraryTarget->setTargetZ(i, TZCmd[i]->GetNewDoubleValue(newValue));
      break;
    }
    if( command == TTarCmd[i] ){
      if(aArbitraryTarget->CheckAndAddLayers(i))
        aArbitraryTarget->SetTarThickness(i,TTarCmd[i]->GetNewDoubleValue(newValue));
      break;
    }
    if( command == TPCmd[i] ){
      if(aArbitraryTarget->CheckAndAddLayers(i)) 
        aArbitraryTarget->setTargetPosition(i, TPCmd[i]->GetNewDoubleValue(newValue));
      break;
    }
    if( command == TACmd[i] ){
      G4int layer1;
      char str[64];
      if(sscanf(newValue, "%i %s", &layer1, str) == 2) {
        if(strcmp(str,"downstream")==0){
          aArbitraryTarget->attachLayers(layer1-1, i, true);
        }else if(strcmp(str,"upstream")==0){
          aArbitraryTarget->attachLayers(layer1-1, i, false);
        }else{
          G4cerr << "ERROR: /Target/Layer" << i << "/AttachToLayer command has invalid upstream/downstream specifier." << G4endl;
          G4cerr << "Valid format for this command is: /Target/Layer"  << i << "/AttachToLayer layer_index us/ds," << G4endl;
          G4cerr << "where 'us/ds' is 'upstream' or 'downstream'." << G4endl;
          exit(EXIT_FAILURE);
        }
      }else{
        G4cerr << "ERROR: /Target/Layer" << i << "/AttachToLayer command is improperly formatted." << G4endl;
        G4cerr << "Valid format for this command is: /Target/Layer"  << i << "/AttachToLayer layer_index us/ds," << G4endl;
        G4cerr << "where 'us/ds' is 'upstream' or 'downstream'." << G4endl;
        exit(EXIT_FAILURE);
      }
      break;
    } 
  }
  
  if( command == TRLCmd ){
    aArbitraryTarget->setTargetExLayer(TRLCmd->GetNewIntValue(newValue)-1);
  }
  if( command == TExCmd ){
    aArbitraryTarget->setTargetEx(TExCmd->GetNewDoubleValue(newValue));
  }
  if( command == TTauCmd ){
    aArbitraryTarget->setTargetTau(TTauCmd->GetNewDoubleValue(newValue));
  }
  if( command == TRCmd ){
    aArbitraryTarget->setTargetR(TRCmd->GetNewDoubleValue(newValue));
  }
  if( command == NTSCmd ){
    aArbitraryTarget->setNTStep(NTSCmd->GetNewIntValue(newValue));
  }
  if( command == TRepCmd ){
    aArbitraryTarget->Report();
  }


}

