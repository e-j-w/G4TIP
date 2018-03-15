#include "Reaction_Messenger.hh"

Reaction_Messenger::Reaction_Messenger(ReactionFusEvap *EC) : theReaction(EC) {

  theReactionDir = new G4UIdirectory("/Reaction/");
  theReactionDir->SetGuidance("Evaporation channel control.");

  MACmd = new G4UIcmdWithAnInteger("/Reaction/MaxNumAttempts", this);
  MACmd->SetGuidance("Set the maximum number of times to attempt a single "
                     "reaction before giving an error.");
  MACmd->SetParameterName("N_attempts", false);
  MACmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  NACmd = new G4UIcmdWithAnInteger("/Reaction/N_alpha", this);
  NACmd->SetGuidance("Set the number of alphas evaporated.");
  NACmd->SetParameterName("N_proton", false);
  NACmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  NPCmd = new G4UIcmdWithAnInteger("/Reaction/N_protons", this);
  NPCmd->SetGuidance("Set the number of protons evaporated.");
  NPCmd->SetParameterName("N_proton", false);
  NPCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  NNCmd = new G4UIcmdWithAnInteger("/Reaction/N_neutrons", this);
  NNCmd->SetGuidance("Set the number of neutrons evaporated.");
  NNCmd->SetParameterName("N_neutrons", false);
  NNCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  EneCmd = new G4UIcmdWithADoubleAndUnit("/Reaction/E_gamma", this);
  EneCmd->SetGuidance("(DEPRECATED, use /Reaction/AddDecay) Gamma ray energy "
                      "for the simulated transition.");
  EneCmd->SetParameterName("E_gamma", false);
  EneCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  TauCmd = new G4UIcmdWithADoubleAndUnit("/Reaction/Tau", this);
  TauCmd->SetGuidance("(DEPRECATED, use /Reaction/AddDecay) Lifetime for the "
                      "simulated transition.");
  TauCmd->SetParameterName("Tau", false);
  TauCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  ADecCmd = new G4UIcmdWithAString("/Reaction/AddDecay", this);
  ADecCmd->SetGuidance("Adds a transition to the residual nucleus.  Format: "
                       "'/Reaction/AddDecay ENERGY LIFETIME', with ENERGY in "
                       "MeV, LIFETIME in ns.");
  ADecCmd->SetParameterName("Tau", false);
  ADecCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  SetupCmd = new G4UIcmdWithoutParameter("/Reaction/Setup", this);
  SetupCmd->SetGuidance("Set up the reaction with the previously specified "
                        "parameters.  Simulation will fail if this is not "
                        "called.");

  theCompoundDir = new G4UIdirectory("/CompoundFormation/");
  theCompoundDir->SetGuidance("Beam-target reaction parameters.");

  QCmd = new G4UIcmdWithADoubleAndUnit("/CompoundFormation/Q", this);
  QCmd->SetGuidance("Q for the reaction forming the compound.");
  QCmd->SetParameterName("Q", false);
  QCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  ExiCmd =
      new G4UIcmdWithADoubleAndUnit("/CompoundFormation/CompoundExi", this);
  ExiCmd->SetGuidance("Initial excitation energy of the compound.");
  ExiCmd->SetParameterName("Exi", false);
  ExiCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  theEvaporationDir = new G4UIdirectory("/ParticleEvaporation/");
  theEvaporationDir->SetGuidance("Beam-target reaction parameters.");

  Q1Cmd = new G4UIcmdWithADoubleAndUnit("/ParticleEvaporation/Q1", this);
  Q1Cmd->SetGuidance("Q for the first particle evaporation process.");
  Q1Cmd->SetParameterName("Q1", false);
  Q1Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  Q2Cmd = new G4UIcmdWithADoubleAndUnit("/ParticleEvaporation/Q2", this);
  Q2Cmd->SetGuidance(
      "Q for the second particle evaporation process (if necessary).");
  Q2Cmd->SetParameterName("Q2", false);
  Q2Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  Q3Cmd = new G4UIcmdWithADoubleAndUnit("/ParticleEvaporation/Q3", this);
  Q3Cmd->SetGuidance(
      "Q for the third particle evaporation process (if necessary).");
  Q3Cmd->SetParameterName("Q3", false);
  Q3Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  Q4Cmd = new G4UIcmdWithADoubleAndUnit("/ParticleEvaporation/Q4", this);
  Q4Cmd->SetGuidance(
      "Q for the fourth particle evaporation process (if necessary).");
  Q4Cmd->SetParameterName("Q4", false);
  Q4Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  dExix0Cmd = new G4UIcmdWithADouble("/ParticleEvaporation/Centroid", this);
  dExix0Cmd->SetGuidance("Centroid of the Gaussian used to characterize change "
                         "in compound nucleus excitation energy following "
                         "particle evaporation.");
  dExix0Cmd->SetParameterName("dExix0", false);
  dExix0Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  dExiwCmd = new G4UIcmdWithADouble("/ParticleEvaporation/Width", this);
  dExiwCmd->SetGuidance("Width of the Gaussian used to characterize change in "
                        "compound nucleus excitation energy following particle "
                        "evaporation.");
  dExiwCmd->SetParameterName("dExiw", false);
  dExiwCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  dExitauCmd = new G4UIcmdWithADouble("/ParticleEvaporation/Tau", this);
  dExitauCmd->SetGuidance("Tau of the high energy exponential tail used to "
                          "characterize change in compound nucleus excitation "
                          "energy following particle evaporation.");
  dExitauCmd->SetParameterName("dExitau", false);
  dExitauCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  CARCmd = new G4UIcmdWithoutParameter(
      "/ParticleEvaporation/ConstrainAngularRange", this);
  CARCmd->SetGuidance("Require that at least one evaporated particle be "
                      "emitted in a specified angular range.");

  CARMaxCmd =
      new G4UIcmdWithADoubleAndUnit("/ParticleEvaporation/MaxAngle", this);
  CARMaxCmd->SetGuidance("Maximum angle (from the z/beam axis) in which at "
                         "least one of the evaporated particles must be "
                         "emitted.");
  CARMaxCmd->SetParameterName("CARMax", false);
  CARMaxCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  CARMinCmd =
      new G4UIcmdWithADoubleAndUnit("/ParticleEvaporation/MinAngle", this);
  CARMinCmd->SetGuidance("Minimum angle (from the z/beam axis) in which at "
                         "least one of the evaporated particles must be "
                         "emitted.");
  CARMinCmd->SetParameterName("CARMin", false);
  CARMinCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

Reaction_Messenger::~Reaction_Messenger() {
  delete theReactionDir;
  delete EneCmd;
  delete TauCmd;
  delete ADecCmd;
  delete NPCmd;
  delete NACmd;
  delete NNCmd;

  delete MACmd;

  delete SetupCmd;

  delete theCompoundDir;
  delete QCmd;
  delete ExiCmd;

  delete theEvaporationDir;
  delete Q1Cmd;
  delete Q2Cmd;
  delete Q3Cmd;
  delete Q4Cmd;
  delete dExix0Cmd;
  delete dExiwCmd;
  delete dExitauCmd;

  delete CARCmd;
  delete CARMaxCmd;
  delete CARMinCmd;
}

void Reaction_Messenger::SetNewValue(G4UIcommand *command, G4String newValue) {

  if (command == SetupCmd) {
    theReaction->SetupReaction();
  }

  if (command == MACmd) {
    theReaction->SetNumberOfAttempts(NACmd->GetNewIntValue(newValue));
  }

  if (command == NACmd) {
    theReaction->SetNumberOfAlphas(NACmd->GetNewIntValue(newValue));
  }

  if (command == NPCmd) {
    theReaction->SetNumberOfProtons(NPCmd->GetNewIntValue(newValue));
  }

  if (command == NNCmd) {
    theReaction->SetNumberOfNeutrons(NNCmd->GetNewIntValue(newValue));
  }

  if (command == EneCmd) {
    theReaction->SetEgamma(EneCmd->GetNewDoubleValue(newValue));
  }

  if (command == TauCmd) {
    theReaction->SetTau(TauCmd->GetNewDoubleValue(newValue));
  }

  if (command == ADecCmd) {
    G4double E, T;
    if (sscanf(newValue, "%lf %lf", &E, &T) == 2) {
      theReaction->AddDecay(E, T);
    } else {
      G4cerr << "Reaction Messenger: Incorrect parameters for command "
                "/Reaction/AddDecay.  Aborting."
             << G4endl;
      exit(EXIT_FAILURE);
    }
  }

  if (command == QCmd) {
    theReaction->SetRxnQ(QCmd->GetNewDoubleValue(newValue));
  }

  if (command == ExiCmd) {
    theReaction->SetExi(ExiCmd->GetNewDoubleValue(newValue));
  }

  if (command == Q1Cmd) {
    theReaction->SetEvapQ1(Q1Cmd->GetNewDoubleValue(newValue));
  }

  if (command == Q2Cmd) {
    theReaction->SetEvapQ2(Q2Cmd->GetNewDoubleValue(newValue));
  }

  if (command == Q3Cmd) {
    theReaction->SetEvapQ3(Q3Cmd->GetNewDoubleValue(newValue));
  }

  if (command == Q4Cmd) {
    theReaction->SetEvapQ4(Q4Cmd->GetNewDoubleValue(newValue));
  }

  if (command == dExix0Cmd) {
    theReaction->SetExix0(dExix0Cmd->GetNewDoubleValue(newValue));
  }

  if (command == dExiwCmd) {
    theReaction->SetExiw(dExiwCmd->GetNewDoubleValue(newValue));
  }

  if (command == dExitauCmd) {
    theReaction->SetExitau(dExitauCmd->GetNewDoubleValue(newValue));
  }

  if (command == CARCmd) {
    theReaction->SetConstrainedAngle();
  }

  if (command == CARMaxCmd) {
    theReaction->SetMaxAngle(CARMaxCmd->GetNewDoubleValue(newValue));
  }

  if (command == CARMinCmd) {
    theReaction->SetMinAngle(CARMinCmd->GetNewDoubleValue(newValue));
  }
}
