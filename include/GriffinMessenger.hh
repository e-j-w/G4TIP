
#ifndef GriffinMessenger_h
#define GriffinMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAnInteger;
class G4UIcmdWith3Vector;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithABool;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class GriffinMessenger: public G4UImessenger
{
  public:
    GriffinMessenger( DetectorConstruction* ) ;
   ~GriffinMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    DetectorConstruction* Detector;
    
    G4UIdirectory*             detDir;
  
    G4UIcmdWithoutParameter*   UpdateCmd;

    // Detection Systems

    G4UIcmdWithAnInteger*   AddDetectionSystemGriffinForwardCmd;
    G4UIcmdWithAnInteger*   AddDetectionSystemGriffinForwardDetectorCmd;
    G4UIcmdWithAnInteger*   AddDetectionSystemGriffinBackCmd;
    G4UIcmdWithAnInteger*   AddDetectionSystemGriffinBackDetectorCmd;
    //G4UIcmdWith3Vector*     AddDetectionSystemGriffinPositionConfigCmd;
    G4UIcmdWithAnInteger*   AddDetectionSystemSpiceCmd;
    G4UIcmdWithAnInteger*   AddDetectionSystemSpiceV02Cmd;
    G4UIcmdWithAnInteger*   AddDetectionSystemPacesCmd;
    G4UIcmdWithAnInteger*   AddDetectionSystemGriffinHevimetCmd ; 

    G4UIcmdWithAnInteger*       AddDetectionSystemGriffinCustomDetectorCmd ;
    G4UIcmdWithAnInteger*	      AddDetectionSystemGriffinCustomCmd ;
    G4UIcmdWithAnInteger*       AddDetectionSystemGriffinShieldSelectCmd ;
    G4UIcmdWithADoubleAndUnit*  AddDetectionSystemGriffinSetRadialDistanceCmd ; 
    G4UIcmdWithAnInteger*       AddDetectionSystemGriffinSetExtensionSuppLocationCmd ;
    G4UIcmdWith3Vector*         AddDetectionSystemGriffinSetDeadLayerCmd ;
    G4UIcmdWithABool*           UseTIGRESSPositionsCmd;
    G4UIcmdWithABool*           UseTIGRESSSegmentsCmd;
    G4UIcmdWithoutParameter*    UseTIGRESSSegmentsSphCmd;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

