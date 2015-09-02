#ifndef EventAction_Messenger_h
#define EventAction_Messenger_h 1

#include "EventAction.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"



class EventAction_Messenger: public G4UImessenger
{
  public:
    EventAction_Messenger(EventAction*);
   ~EventAction_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    EventAction* aEventAction;
    
    G4UIdirectory*             EventActionDir;
    G4UIcmdWithoutParameter*   GSCmd;
    G4UIcmdWithoutParameter*   PSCmd;
    G4UIcmdWithoutParameter*   GPCCmd;
  
};


#endif

