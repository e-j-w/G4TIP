#ifndef Chamber_Messenger_h
#define Chamber_Messenger_h 1

#include "Chamber.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

class Chamber_Messenger: public G4UImessenger
{
  public:
    Chamber_Messenger(Chamber *);
   ~Chamber_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    Chamber* aChamber;
    
    G4UIdirectory*             ChamberDir;
    G4UIcmdWithAString*        MatCmd;  
 //    G4UIcmdWithADoubleAndUnit* RMinCmd;
//     G4UIcmdWithADoubleAndUnit* RMaxCmd;
    G4UIcmdWithoutParameter*   RepCmd;
    G4UIcmdWithoutParameter*   VisOn;
    G4UIcmdWithoutParameter*   VisOff;

};


#endif

