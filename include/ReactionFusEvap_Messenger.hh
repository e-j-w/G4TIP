#ifndef Reaction_Messenger_h
#define Reaction_Messenger_h 1

#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"
#include "ReactionFusEvap.hh"
#include "globals.hh"

class ReactionFusEvap_Messenger : public G4UImessenger {
public:
  ReactionFusEvap_Messenger(ReactionFusEvap *);
  ~ReactionFusEvap_Messenger();

  void SetNewValue(G4UIcommand *, G4String);

private:
  ReactionFusEvap *theReaction;
  G4UIdirectory *theReactionDir;

  G4UIcmdWithAString *ADecCmd;
  G4UIcmdWithAnInteger *NNCmd;
  G4UIcmdWithAnInteger *NPCmd;
  G4UIcmdWithAnInteger *NACmd;

  G4UIcmdWithAnInteger *MACmd;

  G4UIcmdWithADoubleAndUnit *QCmd;

  G4UIcmdWithADoubleAndUnit *Q1Cmd;
  G4UIcmdWithADoubleAndUnit *Q2Cmd;
  G4UIcmdWithADoubleAndUnit *Q3Cmd;
  G4UIcmdWithADoubleAndUnit *Q4Cmd;
  G4UIcmdWithADouble *dExix0Cmd;
  G4UIcmdWithADouble *dExiwCmd;
  G4UIcmdWithADouble *dExitauCmd;
  G4UIcmdWithAString *dExiDistCmd;

  G4UIcmdWithoutParameter *CARCmd;
  G4UIcmdWithADoubleAndUnit *CARMaxCmd;
  G4UIcmdWithADoubleAndUnit *CARMinCmd;

  G4UIcmdWithoutParameter *GDist0Cmd;
  G4UIcmdWithoutParameter *GDist2Cmd;
  G4UIcmdWithoutParameter *GDist4Cmd;
  G4UIcmdWithoutParameter *GDist6Cmd;
};

#endif
