
#include "GriffinMessenger.hh" 

#include "DetectorConstruction.hh" 
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithADouble.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GriffinMessenger::GriffinMessenger(DetectorConstruction* Det)
:Detector(Det)
{ 
  
  detDir = new G4UIdirectory("/Griffin/");
  detDir->SetGuidance("detector control");



  UpdateCmd = new G4UIcmdWithoutParameter("/Griffin/update",this);
  UpdateCmd->SetGuidance("Update geometry.");
  UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  UpdateCmd->SetGuidance("if you changed geometrical value(s).");
  UpdateCmd->AvailableForStates(G4State_Idle);

 
  AddDetectionSystemGriffinForwardCmd = new G4UIcmdWithAnInteger("/Griffin/addGriffinForward",this);
  AddDetectionSystemGriffinForwardCmd->SetGuidance("Add Detection System GriffinForward");
  AddDetectionSystemGriffinForwardCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  AddDetectionSystemGriffinForwardDetectorCmd = new G4UIcmdWithAnInteger("/Griffin/addGriffinForwardDetector",this);
  AddDetectionSystemGriffinForwardDetectorCmd->SetGuidance("Add GriffinForward Detector");
  AddDetectionSystemGriffinForwardDetectorCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  AddDetectionSystemGriffinBackCmd = new G4UIcmdWithAnInteger("/Griffin/addGriffinBack",this);
  AddDetectionSystemGriffinBackCmd->SetGuidance("Add Detection System GriffinBack");
  AddDetectionSystemGriffinBackCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  AddDetectionSystemGriffinBackDetectorCmd = new G4UIcmdWithAnInteger("/Griffin/addGriffinBackDetector",this);
  AddDetectionSystemGriffinBackDetectorCmd->SetGuidance("Add GriffinBack Detector");
  AddDetectionSystemGriffinBackDetectorCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

//  AddDetectionSystemGriffinPositionConfigCmd = new G4UIcmdWith3Vector("/Griffin/addGriffinPositionConfig",this);
//  AddDetectionSystemGriffinPositionConfigCmd->SetGuidance("Add Griffin Detector #, Position #, Config (0=forward, 1=back)");
//  AddDetectionSystemGriffinPositionConfigCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  AddDetectionSystemGriffinCustomDetectorCmd = new G4UIcmdWithAnInteger( "/Griffin/addGriffinCustomDetector", this ) ; 
  AddDetectionSystemGriffinCustomDetectorCmd->SetGuidance( "Adds a detector using the paramaters specified") ; 
  AddDetectionSystemGriffinCustomDetectorCmd->AvailableForStates( G4State_PreInit, G4State_Idle ) ; 

  AddDetectionSystemGriffinCustomCmd = new G4UIcmdWithAnInteger( "/Griffin/addGriffinCustom", this ) ; 
  AddDetectionSystemGriffinCustomCmd->SetGuidance( "Adds a detection system using the paramaters specified" ) ; 
  AddDetectionSystemGriffinCustomCmd->AvailableForStates( G4State_PreInit, G4State_Idle ) ; 
  
//////// Commands that are required for addGriffinCustom
  AddDetectionSystemGriffinShieldSelectCmd = new G4UIcmdWithAnInteger( "/Griffin/SetCustomShieldsPresent", this );
  AddDetectionSystemGriffinShieldSelectCmd->SetGuidance( "Selects whether or not the detector suppressors are included" ) ;
  AddDetectionSystemGriffinShieldSelectCmd->AvailableForStates( G4State_PreInit, G4State_Idle ) ;
 
  AddDetectionSystemGriffinSetRadialDistanceCmd = new G4UIcmdWithADoubleAndUnit( "/Griffin/SetCustomRadialDistance", this ) ; 
  AddDetectionSystemGriffinSetRadialDistanceCmd->SetGuidance( "Selects the radial distance for the detector from the origin") ;
  AddDetectionSystemGriffinSetRadialDistanceCmd->AvailableForStates( G4State_PreInit, G4State_Idle ) ; 
  
  AddDetectionSystemGriffinSetExtensionSuppLocationCmd = new G4UIcmdWithAnInteger( "/Griffin/SetCustomExtensionSuppressorLocation", this ) ; 
  AddDetectionSystemGriffinSetExtensionSuppLocationCmd->SetGuidance( "Selects a position for the extension suppressors. Either forward (0) or back (1)." ) ;
  AddDetectionSystemGriffinSetExtensionSuppLocationCmd->AvailableForStates( G4State_PreInit, G4State_Idle ) ;
  
  AddDetectionSystemGriffinSetDeadLayerCmd = new G4UIcmdWith3Vector( "/Griffin/SetCustomDeadLayer", this ) ; 
  AddDetectionSystemGriffinSetDeadLayerCmd->SetGuidance( "Sets the dead layer and position for the detector placed in the next call to addGriffinCustom." ) ; 
  AddDetectionSystemGriffinSetDeadLayerCmd->AvailableForStates( G4State_PreInit, G4State_Idle ) ; 
////////
  
  AddDetectionSystemGriffinHevimetCmd = new G4UIcmdWithAnInteger( "/Griffin/includeGriffinHevimet", this ) ; 
  AddDetectionSystemGriffinHevimetCmd->SetGuidance( "Includes the Hevimet for a Griffin detector." ) ; 
  AddDetectionSystemGriffinHevimetCmd->AvailableForStates( G4State_PreInit, G4State_Idle ) ; 


  UseTIGRESSPositionsCmd = new G4UIcmdWithABool("/Griffin/UseTIGRESSPositions",this);
  UseTIGRESSPositionsCmd->SetGuidance("Use TIGRESS detector positions rather than GRIFFIN.");
  UseTIGRESSPositionsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  UseTIGRESSSegmentsCmd = new G4UIcmdWithABool("/Griffin/UseTIGRESSSegments",this);
  UseTIGRESSSegmentsCmd->SetGuidance("Construct detector(s) using TIGRESS sgements (geometry may not be accurate).");
  UseTIGRESSSegmentsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GriffinMessenger::~GriffinMessenger()
{
  delete detDir;
 
  delete UpdateCmd;
 
  delete AddDetectionSystemGriffinForwardCmd;
  delete AddDetectionSystemGriffinForwardDetectorCmd;
  delete AddDetectionSystemGriffinBackCmd;
  delete AddDetectionSystemGriffinBackDetectorCmd;
//  delete AddDetectionSystemGriffinPositionConfigCmd;
  delete AddDetectionSystemGriffinCustomDetectorCmd ;
  delete AddDetectionSystemGriffinCustomCmd ; 
  delete AddDetectionSystemGriffinHevimetCmd ; 

  delete AddDetectionSystemGriffinShieldSelectCmd ; 
  delete AddDetectionSystemGriffinSetRadialDistanceCmd ; 
  delete AddDetectionSystemGriffinSetExtensionSuppLocationCmd ; 
  delete AddDetectionSystemGriffinSetDeadLayerCmd ; 

  delete UseTIGRESSPositionsCmd;
  delete UseTIGRESSSegmentsCmd;



}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GriffinMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{			

  if( command == UpdateCmd ) { 
    Detector->UpdateGeometry(); 
  }

  if( command == AddDetectionSystemGriffinForwardCmd ) {
    Detector->AddDetectionSystemGriffinForward(AddDetectionSystemGriffinForwardCmd->GetNewIntValue(newValue));
  }
  if( command == AddDetectionSystemGriffinForwardDetectorCmd ) {
    Detector->AddDetectionSystemGriffinForwardDetector(AddDetectionSystemGriffinForwardDetectorCmd->GetNewIntValue(newValue));
  }
  if( command == AddDetectionSystemGriffinBackCmd ) {
    Detector->AddDetectionSystemGriffinBack(AddDetectionSystemGriffinBackCmd->GetNewIntValue(newValue));
  }
  if( command == AddDetectionSystemGriffinBackDetectorCmd ) {
    Detector->AddDetectionSystemGriffinBackDetector(AddDetectionSystemGriffinBackDetectorCmd->GetNewIntValue(newValue));
  }
//  if( command == AddDetectionSystemGriffinPositionConfigCmd ) {
//    Detector->AddDetectionSystemGriffinPositionConfig(AddDetectionSystemGriffinPositionConfigCmd->GetNew3VectorValue(newValue));
//	}
  if( command == AddDetectionSystemGriffinCustomDetectorCmd ) {
    Detector->AddDetectionSystemGriffinCustomDetector(AddDetectionSystemGriffinCustomDetectorCmd->GetNewIntValue(newValue));
  }
  if( command == AddDetectionSystemGriffinCustomCmd ) {
    Detector->AddDetectionSystemGriffinCustom(AddDetectionSystemGriffinCustomCmd->GetNewIntValue(newValue));
  }  
  if( command == AddDetectionSystemGriffinHevimetCmd ) {
    Detector->AddDetectionSystemGriffinHevimet(AddDetectionSystemGriffinHevimetCmd->GetNewIntValue(newValue));
  }
  if( command == AddDetectionSystemGriffinShieldSelectCmd ) {
    Detector->AddDetectionSystemGriffinShieldSelect(AddDetectionSystemGriffinShieldSelectCmd->GetNewIntValue(newValue)) ; 
  }
  if( command == AddDetectionSystemGriffinSetRadialDistanceCmd ) {
    Detector->AddDetectionSystemGriffinSetRadialDistance(AddDetectionSystemGriffinSetRadialDistanceCmd->GetNewDoubleValue(newValue)) ;
  }
  if( command == AddDetectionSystemGriffinSetExtensionSuppLocationCmd ) {
  	Detector->AddDetectionSystemGriffinSetExtensionSuppLocation(AddDetectionSystemGriffinSetExtensionSuppLocationCmd->GetNewIntValue(newValue)) ;
  }
  if( command == AddDetectionSystemGriffinSetDeadLayerCmd ) {
  	Detector->AddDetectionSystemGriffinSetDeadLayer( AddDetectionSystemGriffinSetDeadLayerCmd->GetNew3VectorValue( newValue ) ) ; 
  }  

  if( command == UseTIGRESSPositionsCmd ) {
    Detector->SetUseTIGRESSPositions(UseTIGRESSPositionsCmd->GetNewBoolValue(newValue));
  }
  if( command == UseTIGRESSSegmentsCmd ) {
    Detector->SetUseTIGRESSSegments(UseTIGRESSSegmentsCmd->GetNewBoolValue(newValue));
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
