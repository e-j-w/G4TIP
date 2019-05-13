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
    DetectorConstruction_Messenger(DetectorConstruction *);
   ~DetectorConstruction_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    DetectorConstruction* aDetCon;
    
    G4UIdirectory*             DetConDir;
    G4UIcmdWithADoubleAndUnit*  ShiftCmd;
    
    G4UIcmdWithoutParameter*   BallCmd;

};


#endif

