#ifndef ArbitraryTarget_Messenger_h
#define ArbitraryTarget_Messenger_h 1

#include "ArbitraryTarget.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"

class ArbitraryTarget_Messenger: public G4UImessenger
{
  public:
    ArbitraryTarget_Messenger(ArbitraryTarget*);
   ~ArbitraryTarget_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    ArbitraryTarget* aArbitraryTarget;
    
    G4UIdirectory*             TargetDir;
    G4UIdirectory*             TargetLayerDir[NATARGETLAYERS];
    G4UIcmdWithAString*        TMatCmd[NATARGETLAYERS];  
    G4UIcmdWithAnInteger*      TMCmd[NATARGETLAYERS];
    G4UIcmdWithAnInteger*      TQCmd[NATARGETLAYERS];
    G4UIcmdWithAnInteger*      TRLCmd;
    G4UIcmdWithADoubleAndUnit* TExCmd;
    G4UIcmdWithADoubleAndUnit* TTauCmd;
    G4UIcmdWithADouble*        TTarCmd[NATARGETLAYERS];
    G4UIcmdWithADoubleAndUnit* TRCmd;
    G4UIcmdWithADoubleAndUnit* TZCmd[NATARGETLAYERS];
    G4UIcmdWithoutParameter*   TRepCmd;
    G4UIcmdWithAnInteger*      NTSCmd;

};


#endif

