#include "ReactionFusEvap_Messenger.hh"

ReactionFusEvap_Messenger::ReactionFusEvap_Messenger(ReactionFusEvap *EC) : theReaction(EC) {

  theReactionDir = new G4UIdirectory("/FusionEvaporation/");
  theReactionDir->SetGuidance("Fusion-evaporation reaction control.");

  MACmd = new G4UIcmdWithAnInteger("/FusionEvaporation/MaxNumAttempts", this);
  MACmd->SetGuidance("Set the maximum number of times to attempt a single "
                     "reaction before giving an error.");
  MACmd->SetParameterName("N_attempts", false);
  MACmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  NACmd = new G4UIcmdWithAnInteger("/FusionEvaporation/N_alpha", this);
  NACmd->SetGuidance("Set the number of alphas evaporated.");
  NACmd->SetParameterName("N_proton", false);
  NACmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  NPCmd = new G4UIcmdWithAnInteger("/FusionEvaporation/N_protons", this);
  NPCmd->SetGuidance("Set the number of protons evaporated.");
  NPCmd->SetParameterName("N_proton", false);
  NPCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  NNCmd = new G4UIcmdWithAnInteger("/FusionEvaporation/N_neutrons", this);
  NNCmd->SetGuidance("Set the number of neutrons evaporated.");
  NNCmd->SetParameterName("N_neutrons", false);
  NNCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  ADecCmd = new G4UIcmdWithAString("/FusionEvaporation/AddDecay", this);
  ADecCmd->SetGuidance("Adds a transition to the residual nucleus.  Format: "
                       "'/Reaction/AddDecay ENERGY LIFETIME', with ENERGY in "
                       "MeV, LIFETIME in ns.");
  ADecCmd->SetParameterName("Tau", false);
  ADecCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  QCmd = new G4UIcmdWithADoubleAndUnit("/FusionEvaporation/CompoundFormationQ", this);
  QCmd->SetGuidance("Q for the reaction forming the compound.");
  QCmd->SetParameterName("Q", false);
  QCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  Q1Cmd = new G4UIcmdWithADoubleAndUnit("/FusionEvaporation/Q1", this);
  Q1Cmd->SetGuidance("Q for the first particle evaporation process.");
  Q1Cmd->SetParameterName("Q1", false);
  Q1Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  Q2Cmd = new G4UIcmdWithADoubleAndUnit("/FusionEvaporation/Q2", this);
  Q2Cmd->SetGuidance(
      "Q for the second particle evaporation process (if necessary).");
  Q2Cmd->SetParameterName("Q2", false);
  Q2Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  Q3Cmd = new G4UIcmdWithADoubleAndUnit("/FusionEvaporation/Q3", this);
  Q3Cmd->SetGuidance(
      "Q for the third particle evaporation process (if necessary).");
  Q3Cmd->SetParameterName("Q3", false);
  Q3Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  Q4Cmd = new G4UIcmdWithADoubleAndUnit("/FusionEvaporation/Q4", this);
  Q4Cmd->SetGuidance(
      "Q for the fourth particle evaporation process (if necessary).");
  Q4Cmd->SetParameterName("Q4", false);
  Q4Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  dExiVCmd = new G4UIcmdWithADouble("/FusionEvaporation/CoulombBarrier", this);
  dExiVCmd->SetGuidance("Coulomb barrier used to characterize particle evaporation.");
  dExiVCmd->SetParameterName("dExiV", false);
  dExiVCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  dExikTCmd = new G4UIcmdWithADouble("/FusionEvaporation/Temperature", this);
  dExikTCmd->SetGuidance("Temperature used to characterize particle evaporation.");
  dExikTCmd->SetParameterName("dExikT", false);
  dExikTCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  // dExix0Cmd = new G4UIcmdWithADouble("/FusionEvaporation/Centroid", this);
  // dExix0Cmd->SetGuidance("Centroid of the Gaussian used to characterize change "
  //                        "in compound nucleus excitation energy following "
  //                        "particle evaporation.");
  // dExix0Cmd->SetParameterName("dExix0", false);
  // dExix0Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  // dExiwCmd = new G4UIcmdWithADouble("/FusionEvaporation/Width", this);
  // dExiwCmd->SetGuidance("Width of the Gaussian used to characterize change in "
  //                       "compound nucleus excitation energy following particle "
  //                       "evaporation.");
  // dExiwCmd->SetParameterName("dExiw", false);
  // dExiwCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  // dExitauCmd = new G4UIcmdWithADouble("/FusionEvaporation/Tau", this);
  // dExitauCmd->SetGuidance("Tau of the high energy exponential tail used to "
  //                         "characterize change in compound nucleus excitation "
  //                         "energy following particle evaporation.");
  // dExitauCmd->SetParameterName("dExitau", false);
  // dExitauCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  dExiDistCmd = new G4UIcmdWithAString("/FusionEvaporation/DistFile", this);
  dExiDistCmd->SetGuidance("Specifies a tabulated distribution of dExi values for evaporated particles (containing 2 columns, start-of-bin energy in MeV and counts).");
  dExiDistCmd->SetParameterName("Tau", false);
  dExiDistCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  CARCmd = new G4UIcmdWithoutParameter(
      "/FusionEvaporation/ConstrainParticleAngularRange", this);
  CARCmd->SetGuidance("Require that at least one evaporated particle be "
                      "emitted in a specified angular range.");

  CARMaxCmd =
      new G4UIcmdWithADoubleAndUnit("/FusionEvaporation/MaxParticleAngle", this);
  CARMaxCmd->SetGuidance("Maximum angle (from the z/beam axis) in which at "
                         "least one of the evaporated particles must be "
                         "emitted.");
  CARMaxCmd->SetParameterName("CARMax", false);
  CARMaxCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  CARMinCmd =
      new G4UIcmdWithADoubleAndUnit("/FusionEvaporation/MinParticleAngle", this);
  CARMinCmd->SetGuidance("Minimum angle (from the z/beam axis) in which at "
                         "least one of the evaporated particles must be "
                         "emitted.");
  CARMinCmd->SetParameterName("CARMin", false);
  CARMinCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  GDist0Cmd = new G4UIcmdWithoutParameter("/FusionEvaporation/P0", this);
  GDist0Cmd->SetGuidance("Sets the angular distribution of emitted gamma rays to be isotropic.");

  GDist2Cmd = new G4UIcmdWithoutParameter("/FusionEvaporation/P2", this);
  GDist2Cmd->SetGuidance("Sets the angular distribution of emitted gamma rays to a 2nd order legendre polynomial in cos(theta).");

  GDist4Cmd = new G4UIcmdWithoutParameter("/FusionEvaporation/P4", this);
  GDist4Cmd->SetGuidance("Sets the angular distribution of emitted gamma rays to a 4th order legendre polynomial in cos(theta).");

  GDist6Cmd = new G4UIcmdWithoutParameter("/FusionEvaporation/P6", this);
  GDist6Cmd->SetGuidance("Sets the angular distribution of emitted gamma rays to a 6th order legendre polynomial in cos(theta).");

}

ReactionFusEvap_Messenger::~ReactionFusEvap_Messenger() {
  delete theReactionDir;
  delete ADecCmd;
  delete NPCmd;
  delete NACmd;
  delete NNCmd;

  delete MACmd;

  delete QCmd;

  delete Q1Cmd;
  delete Q2Cmd;
  delete Q3Cmd;
  delete Q4Cmd;
  delete dExiVCmd;
  delete dExikTCmd;
  // delete dExix0Cmd;
  // delete dExiwCmd;
  // delete dExitauCmd;
  delete dExiDistCmd;

  delete CARCmd;
  delete CARMaxCmd;
  delete CARMinCmd;

  delete GDist0Cmd;
  delete GDist2Cmd;
  delete GDist4Cmd;
  delete GDist6Cmd;
}

void ReactionFusEvap_Messenger::SetNewValue(G4UIcommand *command, G4String newValue) {

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

  if (command == dExiVCmd) {
    theReaction->SetTabulatedExi(false);
    theReaction->SetExiV(dExiVCmd->GetNewDoubleValue(newValue));
  }

  if (command == dExikTCmd) {
    theReaction->SetTabulatedExi(false);
    theReaction->SetExikT(dExikTCmd->GetNewDoubleValue(newValue));
  }

  // if (command == dExix0Cmd) {
  //   theReaction->SetTabulatedExi(false);
  //   theReaction->SetExix0(dExix0Cmd->GetNewDoubleValue(newValue));
  // }

  // if (command == dExiwCmd) {
  //   theReaction->SetTabulatedExi(false);
  //   theReaction->SetExiw(dExiwCmd->GetNewDoubleValue(newValue));
  // }

  // if (command == dExitauCmd) {
  //   theReaction->SetTabulatedExi(false);
  //   theReaction->SetExitau(dExitauCmd->GetNewDoubleValue(newValue));
  // }

  if (command == dExiDistCmd) {
    theReaction->SetTabulatedExi(true);
    theReaction->ReadTabulatedExi(newValue);
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

  if (command == GDist0Cmd) {
    G4cout << "----> Setting angular distribution of emitted gamma ray(s) to be isotropic." << G4endl;
    theReaction->SetGDist0();
  }

  if (command == GDist2Cmd) {
    G4cout << "----> Setting angular distribution of emitted gamma ray(s) to a 2nd order legendre polynomial in cos(theta)." << G4endl;
    theReaction->SetGDist2();
  }

  if (command == GDist4Cmd) {
    G4cout << "----> Setting angular distribution of emitted gamma ray(s) to a 4th order legendre polynomial in cos(theta)." << G4endl;
    theReaction->SetGDist4();
  }

  if (command == GDist6Cmd) {
    G4cout << "----> Setting angular distribution of emitted gamma ray(s) to a 6th order legendre polynomial in cos(theta)." << G4endl;
    theReaction->SetGDist6();
  }
}
