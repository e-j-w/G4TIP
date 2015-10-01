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


  theCompoundDir = new G4UIdirectory("/CompoundFormation/");
  theCompoundDir->SetGuidance("Beam-target reaction parameters.");

  QCmd = new G4UIcmdWithADoubleAndUnit("/CompoundFormation/Q",this);
  QCmd->SetGuidance("Q for the reaction forming the compound.");
  QCmd->SetParameterName("Q",false);
  QCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
 
  ExiCmd = new G4UIcmdWithADoubleAndUnit("/CompoundFormation/CompoundExi",this);
  ExiCmd->SetGuidance("Initial excitation energy of the compound.");
  ExiCmd->SetParameterName("Exi",false);
  ExiCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  theEvaporationDir = new G4UIdirectory("/ParticleEvaporation/");
  theEvaporationDir->SetGuidance("Beam-target reaction parameters.");

  Q1Cmd = new G4UIcmdWithADoubleAndUnit("/ParticleEvaporation/Q1",this);
  Q1Cmd->SetGuidance("Q for the first particle evaporation process.");
  Q1Cmd->SetParameterName("Q1",false);
  Q1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  Q2Cmd = new G4UIcmdWithADoubleAndUnit("/ParticleEvaporation/Q2",this);
  Q2Cmd->SetGuidance("Q for the second particle evaporation process (if necessary).");
  Q2Cmd->SetParameterName("Q2",false);
  Q2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  dExi0mCmd = new G4UIcmdWithADoubleAndUnit("/ParticleEvaporation/FirstParticleDeltaExiMean",this);
  dExi0mCmd->SetGuidance("Mean change in compound nucleus excitation energy following evaporation of the first particle.");
  dExi0mCmd->SetParameterName("dExi0m",false);
  dExi0mCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  dExi0sCmd = new G4UIcmdWithADoubleAndUnit("/ParticleEvaporation/FirstParticleDeltaExiWidth",this);
  dExi0sCmd->SetGuidance("Width of change in compound nucleus excitation energy distrubution, for evaporation of the first particle.");
  dExi0sCmd->SetParameterName("dExi0s",false);
  dExi0sCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  dExi1mCmd = new G4UIcmdWithADoubleAndUnit("/ParticleEvaporation/TotalDeltaExiMean",this);
  dExi1mCmd->SetGuidance("Mean change in compound nucleus excitation energy following evaporation of all particles.");
  dExi1mCmd->SetParameterName("dExi1m",false);
  dExi1mCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  dExi1sCmd = new G4UIcmdWithADoubleAndUnit("/ParticleEvaporation/TotalDeltaExiWidth",this);
  dExi1sCmd->SetGuidance("Width of change in compound nucleus excitation energy distrubution, for evaporation of the all particles.");
  dExi1sCmd->SetParameterName("dExi1s",false);
  dExi1sCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}



Reaction_Messenger::~Reaction_Messenger()
{
  delete  theReactionDir;
  delete  EneCmd;
  delete  TauCmd;
  delete  NPCmd;
  delete  NACmd;
  delete  NNCmd;

  delete  theCompoundDir;
  delete  QCmd;
  delete  ExiCmd;

  delete  theEvaporationDir;
  delete  Q1Cmd;
  delete  Q2Cmd;
  delete  dExi0mCmd;
  delete  dExi0sCmd;
  delete  dExi1mCmd;
  delete  dExi1sCmd;
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


  if( command == QCmd )
    { theReaction->SetRxnQ(QCmd->GetNewDoubleValue(newValue));}

  if( command == ExiCmd )
    { theReaction->SetExi(ExiCmd->GetNewDoubleValue(newValue));}

  if( command == Q1Cmd )
    { theReaction->SetEvapQ1(Q1Cmd->GetNewDoubleValue(newValue));}

  if( command == Q2Cmd )
    { theReaction->SetEvapQ2(Q2Cmd->GetNewDoubleValue(newValue));}

  if( command == dExi0mCmd )
    { theReaction->SetdExi0m(dExi0mCmd->GetNewDoubleValue(newValue));}

  if( command == dExi0sCmd )
    { theReaction->SetdExi0s(dExi0sCmd->GetNewDoubleValue(newValue));}

  if( command == dExi1mCmd )
    { theReaction->SetdExi1m(dExi1mCmd->GetNewDoubleValue(newValue));}

  if( command == dExi1sCmd )
    { theReaction->SetdExi1s(dExi1sCmd->GetNewDoubleValue(newValue));}

}

