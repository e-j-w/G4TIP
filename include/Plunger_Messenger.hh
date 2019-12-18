#ifndef Plunger_Messenger_h
#define Plunger_Messenger_h 1

#include "Plunger.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"

class Plunger_Messenger: public G4UImessenger
{
  public:
    Plunger_Messenger(Plunger*);
   ~Plunger_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    Plunger*                   thePlunger;
    G4UIdirectory*             PlungerDir;
    G4UIdirectory*             StopperDir;
    G4UIdirectory*             TargetDir;
    G4UIdirectory*             BackingDir;
    G4UIcmdWithADoubleAndUnit* SepCmd;
    G4UIcmdWithADoubleAndUnit* PosCmd;

    G4UIcmdWithAString*        MatDegCmd;  
    G4UIcmdWithADoubleAndUnit* RDegCmd;
    G4UIcmdWithADoubleAndUnit* ZDegCmd;
    G4UIcmdWithAnInteger*      NSDegCmd;
    G4UIcmdWithADouble*        ScDDegCmd;

    G4UIcmdWithAString*        MatTarCmd;
    G4UIcmdWithADoubleAndUnit* RTarCmd;  
    G4UIcmdWithADoubleAndUnit* XTarCmd;
    G4UIcmdWithADouble*        TTarCmd;
    G4UIcmdWithAnInteger*      NSTarCmd;
    G4UIcmdWithAnInteger*      ATarCmd;
    G4UIcmdWithAnInteger*      ZTarCmd;  
    G4UIcmdWithADouble*        ScDTarCmd;

    G4UIcmdWithAString*        MatBckCmd;
    G4UIcmdWithADoubleAndUnit* RBckCmd;  
    G4UIcmdWithADoubleAndUnit* ZBckCmd;
    G4UIcmdWithAnInteger*      NSBckCmd;
    G4UIcmdWithADouble*        ScDBckCmd;
 
    G4UIcmdWithoutParameter*   RepCmd;
    
  

};


#endif

