#ifndef Projectile_Messenger_h
#define Projectile_Messenger_h 1

#include "Projectile.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"


class Projectile_Messenger: public G4UImessenger
{
  public:
    Projectile_Messenger(Projectile*);
   ~Projectile_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    Projectile* theProjectile;    
    G4UIdirectory*             theProjectileDir;
    G4UIdirectory*             fcDir;
    G4UIcmdWithAnInteger*      ACmd;
    G4UIcmdWithAnInteger*      ZCmd;
    G4UIcmdWithADoubleAndUnit* KECmd;
    G4UIcmdWithADoubleAndUnit* fcXCmd;
    G4UIcmdWithADoubleAndUnit* fcDXCmd;
    G4UIcmdWithADoubleAndUnit* fcYCmd;
    G4UIcmdWithADoubleAndUnit* fcDYCmd;
    G4UIcmdWithADoubleAndUnit* fcZCmd;
    G4UIcmdWithADoubleAndUnit* maxACmd;
    G4UIcmdWithADoubleAndUnit* maxBCmd;
    G4UIcmdWithADoubleAndUnit* Ata0Cmd;
    G4UIcmdWithADoubleAndUnit* Bta0Cmd;
    G4UIcmdWithoutParameter*   RepCmd;
  

};


#endif

