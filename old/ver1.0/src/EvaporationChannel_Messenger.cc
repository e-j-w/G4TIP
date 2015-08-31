#include "EvaporationChannel_Messenger.hh"


EvaporationChannel_Messenger::EvaporationChannel_Messenger(EvaporationChannel* EC):theEvaporationChannel(EC)
{ 
 
  theEvaporationChannelDir = new G4UIdirectory("/EvaporationChannel/");
  theEvaporationChannelDir->SetGuidance("Evaporation channel control.");

  NACmd = new G4UIcmdWithAnInteger("/EvaporationChannel/N_alpha",this);
  NACmd->SetGuidance("Set the number of alphas evaporated.");
  NACmd->SetParameterName("N_proton",false);
  NACmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  NPCmd = new G4UIcmdWithAnInteger("/EvaporationChannel/N_protons",this);
  NPCmd->SetGuidance("Set the number of protons evaporated.");
  NPCmd->SetParameterName("N_proton",false);
  NPCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  NNCmd = new G4UIcmdWithAnInteger("/EvaporationChannel/N_neutrons",this);
  NNCmd->SetGuidance("Set the number of neutrons evaporated.");
  NNCmd->SetParameterName("N_neutrons",false);
  NNCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  EneCmd = new G4UIcmdWithADoubleAndUnit("/EvaporationChannel/E_gamma",this);
  EneCmd->SetGuidance("Gamma ray energy for the simulated transition.");
  EneCmd->SetParameterName("E_gamma",false);
  EneCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
 
  TauCmd = new G4UIcmdWithADoubleAndUnit("/EvaporationChannel/Tau",this);
  TauCmd->SetGuidance("Lifetime for the simulated transition.");
  TauCmd->SetParameterName("Tau",false);
  TauCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
 
  
}



EvaporationChannel_Messenger::~EvaporationChannel_Messenger()
{
  delete  theEvaporationChannelDir;
  delete  EneCmd;
  delete  TauCmd;
  delete  NPCmd;
  delete  NACmd;
  delete  NNCmd;
}


void EvaporationChannel_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 

  if( command == NACmd )
    { theEvaporationChannel->SetNumberOfAlphas(NACmd->GetNewIntValue(newValue));}

  if( command == NPCmd )
    { theEvaporationChannel->SetNumberOfProtons(NPCmd->GetNewIntValue(newValue));}
 
  if( command == NNCmd )
    { theEvaporationChannel->SetNumberOfNeutrons(NNCmd->GetNewIntValue(newValue));}

  if( command == EneCmd )
    { theEvaporationChannel->SetEgamma(EneCmd->GetNewDoubleValue(newValue));}

  if( command == TauCmd )
    { theEvaporationChannel->SetTau(TauCmd->GetNewDoubleValue(newValue));}

}

