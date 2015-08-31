#include "Reaction_Messenger.hh"


Reaction_Messenger::Reaction_Messenger(Reaction* EC):theReaction(EC)
{ 
 
  theReactionDir = new G4UIdirectory("/Reaction/");
  theReactionDir->SetGuidance("Evaporation channel control.");

  NACmd = new G4UIcmdWithAnInteger("/Reaction/N_alpha",this);
  NACmd->SetGuidance("Set the number of alphas evaporated.");
  NACmd->SetParameterName("N_proton",false);
  NACmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  NPCmd = new G4UIcmdWithAnInteger("/Reaction/N_protons",this);
  NPCmd->SetGuidance("Set the number of protons evaporated.");
  NPCmd->SetParameterName("N_proton",false);
  NPCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  NNCmd = new G4UIcmdWithAnInteger("/Reaction/N_neutrons",this);
  NNCmd->SetGuidance("Set the number of neutrons evaporated.");
  NNCmd->SetParameterName("N_neutrons",false);
  NNCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  EneCmd = new G4UIcmdWithADoubleAndUnit("/Reaction/E_gamma",this);
  EneCmd->SetGuidance("Gamma ray energy for the simulated transition.");
  EneCmd->SetParameterName("E_gamma",false);
  EneCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
 
  TauCmd = new G4UIcmdWithADoubleAndUnit("/Reaction/Tau",this);
  TauCmd->SetGuidance("Lifetime for the simulated transition.");
  TauCmd->SetParameterName("Tau",false);
  TauCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
 
  
}



Reaction_Messenger::~Reaction_Messenger()
{
  delete  theReactionDir;
  delete  EneCmd;
  delete  TauCmd;
  delete  NPCmd;
  delete  NACmd;
  delete  NNCmd;
}


void Reaction_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 

  if( command == NACmd )
    { theReaction->SetNumberOfAlphas(NACmd->GetNewIntValue(newValue));}

  if( command == NPCmd )
    { theReaction->SetNumberOfProtons(NPCmd->GetNewIntValue(newValue));}
 
  if( command == NNCmd )
    { theReaction->SetNumberOfNeutrons(NNCmd->GetNewIntValue(newValue));}

  if( command == EneCmd )
    { theReaction->SetEgamma(EneCmd->GetNewDoubleValue(newValue));}

  if( command == TauCmd )
    { theReaction->SetTau(TauCmd->GetNewDoubleValue(newValue));}

}

