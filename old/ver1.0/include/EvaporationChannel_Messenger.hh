#ifndef EvaporationChannel_Messenger_h
#define EvaporationChannel_Messenger_h 1

#include "EvaporationChannel.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"


class EvaporationChannel_Messenger: public G4UImessenger
{
  public:
    EvaporationChannel_Messenger(EvaporationChannel*);
   ~EvaporationChannel_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    EvaporationChannel* theEvaporationChannel;    
    G4UIdirectory*      theEvaporationChannelDir;
   
    G4UIcmdWithADoubleAndUnit* TauCmd;
    G4UIcmdWithADoubleAndUnit* EneCmd; 
    G4UIcmdWithAnInteger*      NNCmd;
    G4UIcmdWithAnInteger*      NPCmd;
    G4UIcmdWithAnInteger*      NACmd;
};


#endif

