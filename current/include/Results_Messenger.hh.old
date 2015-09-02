#ifndef Results_Messenger_h
#define Results_Messenger_h 1

#include "Results.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWith3Vector.hh"


class Results_Messenger: public G4UImessenger
{
  public:
    Results_Messenger(Results*);
   ~Results_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    Results* results;    
    G4UIdirectory*             ResDir;
    G4UIdirectory*             TreDir;
    G4UIdirectory*             ProjDir;
    G4UIdirectory*             GDir;
    G4UIdirectory*             PDir;
    G4UIdirectory*             GRDir;

  // tree
    G4UIcmdWithoutParameter*   TRepCmd;
    G4UIcmdWithoutParameter*   TVCmd;
    G4UIcmdWithoutParameter*   TCCmd;
    G4UIcmdWithAString*        TSCmd;
    G4UIcmdWithAString*        TRCmd;
    G4UIcmdWithAString*        TACmd;

  //projectile
    G4UIcmdWithoutParameter*   PLSACmd;
 
  //gamma
    G4UIcmdWithAnInteger*      GRSCmd;
 
  //groups
    G4UIcmdWithoutParameter*   RCSPCmd;
    G4UIcmdWithoutParameter*   RRSPCmd;

};


#endif
