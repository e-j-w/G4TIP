#ifndef ReactionCoulex_Messenger_h
#define ReactionCoulex_Messenger_h 1

#include "ReactionCoulex.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"

class ReactionCoulex_Messenger: public G4UImessenger
{
public:
  ReactionCoulex_Messenger(ReactionCoulex *);
  ~ReactionCoulex_Messenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  ReactionCoulex* aReaction;  
  G4UIdirectory             *ReactionDir;
  G4UIcmdWithADouble        *SetDCminCmd;
  G4UIcmdWithoutParameter   *RepDCminCmd;
};

#endif

