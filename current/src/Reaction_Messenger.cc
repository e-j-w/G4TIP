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
  EneCmd->SetGuidance("(DEPRECATED, use /Reaction/AddDecay) Gamma ray energy for the simulated transition.");
  EneCmd->SetParameterName("E_gamma",false);
  EneCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
 
  TauCmd = new G4UIcmdWithADoubleAndUnit("/Reaction/Tau",this);
  TauCmd->SetGuidance("(DEPRECATED, use /Reaction/AddDecay) Lifetime for the simulated transition.");
  TauCmd->SetParameterName("Tau",false);
  TauCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ADecCmd = new G4UIcmdWithAString("/Reaction/AddDecay",this);
  ADecCmd->SetGuidance("Adds a transition to the residual nucleus.  Format: '/Reaction/AddDecay ENERGY LIFETIME', with ENERGY in MeV, LIFETIME in ns.");
  ADecCmd->SetParameterName("Tau",false);
  ADecCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

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

  dExiSCmd = new G4UIcmdWithADouble("/ParticleEvaporation/Shift",this);
  dExiSCmd->SetGuidance("Scaling factor of the gamma distribution used to characterize change in compound nucleus excitation energy following particle evaporation.");
  dExiSCmd->SetParameterName("dExiS",false);
  dExiSCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  dExiRhoCmd = new G4UIcmdWithADouble("/ParticleEvaporation/Rho",this);
  dExiRhoCmd->SetGuidance("Rho of the gamma distribution used to characterize change in compound nucleus excitation energy following particle evaporation.");
  dExiRhoCmd->SetParameterName("dExiRho",false);
  dExiRhoCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  dExiLambdaCmd = new G4UIcmdWithADouble("/ParticleEvaporation/Lambda",this);
  dExiLambdaCmd->SetGuidance("Lambda of the gamma distribution used to characterize change in compound nucleus excitation energy following particle evaporation.");
  dExiLambdaCmd->SetParameterName("dExiLambda",false);
  dExiLambdaCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  CARCmd = new G4UIcmdWithoutParameter("/ParticleEvaporation/ConstrainAngularRange",this);
  CARCmd->SetGuidance("Require that at least one evaporated particle be emitted in a specified angular range.");

  CARMaxCmd = new G4UIcmdWithADoubleAndUnit("/ParticleEvaporation/MaxAngle",this);
  CARMaxCmd->SetGuidance("Maximum angle (from the z/beam axis) in which at least one of the evaporated particles must be emitted.");
  CARMaxCmd->SetParameterName("CARMax",false);
  CARMaxCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  CARMinCmd = new G4UIcmdWithADoubleAndUnit("/ParticleEvaporation/MinAngle",this);
  CARMinCmd->SetGuidance("Minimum angle (from the z/beam axis) in which at least one of the evaporated particles must be emitted.");
  CARMinCmd->SetParameterName("CARMin",false);
  CARMinCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}



Reaction_Messenger::~Reaction_Messenger()
{
  delete  theReactionDir;
  delete  EneCmd;
  delete  TauCmd;
  delete  ADecCmd;
  delete  NPCmd;
  delete  NACmd;
  delete  NNCmd;

  delete  theCompoundDir;
  delete  QCmd;
  delete  ExiCmd;

  delete  theEvaporationDir;
  delete  Q1Cmd;
  delete  Q2Cmd;
  delete  dExiSCmd;
  delete  dExiRhoCmd;
  delete  dExiLambdaCmd;

  delete  CARCmd;
  delete  CARMaxCmd;
  delete  CARMinCmd;
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

  if( command == ADecCmd )
    {
      G4double E,T;
      if(sscanf(newValue,"%lf %lf",&E,&T)==2)
        {
          theReaction->AddDecay(E,T);
        }
      else
        {
          G4cerr << "Reaction Messenger: Incorrect parameters for command /Reaction/AddDecay.  Aborting." << G4endl;
          exit(EXIT_FAILURE);
        }
    }

  if( command == QCmd )
    { theReaction->SetRxnQ(QCmd->GetNewDoubleValue(newValue));}

  if( command == ExiCmd )
    { theReaction->SetExi(ExiCmd->GetNewDoubleValue(newValue));}

  if( command == Q1Cmd )
    { theReaction->SetEvapQ1(Q1Cmd->GetNewDoubleValue(newValue));}

  if( command == Q2Cmd )
    { theReaction->SetEvapQ2(Q2Cmd->GetNewDoubleValue(newValue));}

  if( command == dExiSCmd )
    { theReaction->SetShift(dExiSCmd->GetNewDoubleValue(newValue));}

  if( command == dExiRhoCmd )
    { theReaction->SetRho(dExiRhoCmd->GetNewDoubleValue(newValue));}

  if( command == dExiLambdaCmd )
    { theReaction->SetLambda(dExiLambdaCmd->GetNewDoubleValue(newValue));}


  if( command == CARCmd )
    { theReaction->SetConstrainedAngle();}

  if( command == CARMaxCmd )
    { theReaction->SetMaxAngle(CARMaxCmd->GetNewDoubleValue(newValue));}

  if( command == CARMinCmd )
    { theReaction->SetMinAngle(CARMinCmd->GetNewDoubleValue(newValue));}

}

