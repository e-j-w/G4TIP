#ifndef DetectorConstruction_Messenger_h
#define DetectorConstruction_Messenger_h 1

#include "DetectorConstruction.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

class DetectorConstruction_Messenger: public G4UImessenger
{
  public:
    DetectorConstruction_Messenger(DetectorConstruction*);
   ~DetectorConstruction_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
  DetectorConstruction* theDetector;

  G4UIdirectory* DetectorDir;

  G4UIcmdWithoutParameter*   RepCmd;
  G4UIcmdWithADoubleAndUnit* STCmd;  
  G4UIcmdWithADoubleAndUnit* SPCmd;
  G4UIcmdWithoutParameter*   BallCmd;
};

#endif

