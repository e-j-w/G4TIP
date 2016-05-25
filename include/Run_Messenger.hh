#ifndef Run_Messenger_h
#define Run_Messenger_h 1

#include "G4RunManager.hh"
#include "PhysicsList.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
//#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
//#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
//#include "G4UIcmdWithAnInteger.hh"


class Run_Messenger: public G4UImessenger
{
  public:
    Run_Messenger(G4RunManager*,PhysicsList*);
   ~Run_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    G4RunManager* theRunManager;
    PhysicsList* thePhysicsList;
    G4UIdirectory             *thePLDir,*theRDir;
    G4UIcmdWithADoubleAndUnit* PLSCmd;
    G4UIcmdWithoutParameter* ICmd;
};


#endif

