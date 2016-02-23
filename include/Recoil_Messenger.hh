#ifndef Recoil_Messenger_h
#define Recoil_Messenger_h 1

#include "Recoil.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"
class Recoil_Messenger: public G4UImessenger
{
  public:
    Recoil_Messenger(Recoil*);
   ~Recoil_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    G4UIdirectory*             RecoilDir;
   
    
    G4UIcmdWithAnInteger*      RACmd;
    G4UIcmdWithAnInteger*      RZCmd;
    G4UIcmdWithADoubleAndUnit* RExCmd;
    G4UIcmdWithADoubleAndUnit* RTauCmd;
    G4UIcmdWithoutParameter*   RRepCmd;
  
  Recoil* theRecoil;
};


#endif

