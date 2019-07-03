#ifndef EventAction_Messenger_h
#define EventAction_Messenger_h 1

#include "EventAction.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"



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
    G4UIcmdWithAnInteger*      TACmd;
    G4UIcmdWithAnInteger*      TZCmd;
    G4UIcmdWithAString*        TARangeCmd;
    G4UIcmdWithAString*        TZRangeCmd;
    G4UIcmdWithoutParameter*   TAZCmd;
    G4UIcmdWithoutParameter*   TAZ1Cmd;
    G4UIcmdWithoutParameter*   TAZCCmd;
    G4UIcmdWithoutParameter*   TAZCGCmd;
    G4UIcmdWithoutParameter*   TAZC2GCmd;
    G4UIcmdWithAnInteger*      TIDCmd;
    G4UIcmdWithAString*        TDGCCmd;
    G4UIcmdWithAString*        TDGCmd;
    G4UIcmdWithAString*        TDCCmd;
    G4UIcmdWithAString*        TDCRCmd;
    G4UIcmdWithAString*        TWCRCmd;
    G4UIcmdWithADoubleAndUnit* CETCmd;
    G4UIcmdWithoutParameter*   RTCmd;

};


#endif

