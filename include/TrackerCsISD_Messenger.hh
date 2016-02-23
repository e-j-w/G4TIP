#ifndef TrackerCsISD_Messenger_h
#define TrackerCsISD_Messenger_h 1

#include "TrackerCsISD.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"


class TrackerCsISD_Messenger: public G4UImessenger
{
  public:
    TrackerCsISD_Messenger(TrackerCsISD*);
   ~TrackerCsISD_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    TrackerCsISD* tracker;    
    G4UIdirectory*             PrtDir;
    G4UIcmdWithoutParameter*   PrtSCmd;
    G4UIcmdWithoutParameter*   PrtUCmd;

};


#endif

