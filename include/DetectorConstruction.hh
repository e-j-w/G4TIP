#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

#include "G4AssemblyVolume.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4SDManager.hh"
#include "Materials.hh"
#include "Experimental_Hall.hh"
#include "Experimental_Hall_Messenger.hh"
#include "Plunger.hh"
#include "Plunger_Messenger.hh"
#include "Target.hh"
#include "Target_Messenger.hh"
#include "ArbitraryTarget.hh"
#include "ArbitraryTarget_Messenger.hh"
#include "TrackerIonSD.hh"
#include "TrackerIonSD_Messenger.hh"
#include "CsI_array.hh"
#include "CsI_array_spherical.hh"
#include "TrackerCsISD.hh"
#include "TrackerCsISD_Messenger.hh"
#include "DetectionSystemGriffin.hh"
#include "GriffinMessenger.hh"
#include "G4NistManager.hh"
#include "Chamber.hh"
#include "Chamber_Messenger.hh"

#define GN     16 // detectors                                                                                                                                                                                                          
#define GS     4  // crystals 

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  
  DetectorConstruction();
  ~DetectorConstruction();
  
  G4VPhysicalVolume* Construct();
  
  Plunger*             GetPlunger(){return thePlunger;};
  Target*              GetTarget(){return theTarget;};
  ArbitraryTarget*     GetArbitraryTarget(){return theArbitraryTarget;};
  CsI_array*           GetCsIWall(){return aCsI_wall;};
  CsI_array_spherical* GetCsIBall(){return aCsI_ball;};
  Chamber*             GetChamber(){return theChamber;};
  int                  GetTargetType() {return targetType;};
  G4int                GetAncArrayType(){return ancArrayType;};
  
  G4int griffinDetectorsMapIndex;
  G4int griffinDetectorsMap[16];
  
  void AddDetectionSystemGriffinForward(G4int ndet);
  void AddDetectionSystemGriffinForwardDetector(G4int ndet);
  void AddDetectionSystemGriffinBack(G4int ndet);
  void AddDetectionSystemGriffinBackDetector(G4int ndet);
  //void AddDetectionSystemGriffinPositionConfig(G4ThreeVector input);
  void AddDetectionSystemGriffinHevimet( G4int input ) ; 
  void AddDetectionSystemGriffinCustom( G4int ndet ) ;
  void AddDetectionSystemGriffinCustomDetector( G4int ndet ) ; 
  void AddDetectionSystemGriffinShieldSelect( G4int ShieldSelect ) ;
  void AddDetectionSystemGriffinSetRadialDistance( G4double detectorDist ) ;
  void AddDetectionSystemGriffinSetExtensionSuppLocation( G4int detectorPos ) ;
  void AddDetectionSystemGriffinSetDeadLayer( G4ThreeVector params ) ; 
  void UseTIGRESSPositions( G4bool input ) {useTigressPositions = input;};
  void SetUseCsIWall() {ancArrayType = 0;};
  void SetUseCsIBall() {ancArrayType = 1;};
  void SetUseNoAncArray() {ancArrayType = 2;};
  void SetUseArbitraryTarget() {targetType = 0;};
  void SetUseDSAMTarget() {targetType = 1;};
  void SetUsePlunger() {targetType = 2;};
  void UpdateGeometry();
  G4ThreeVector GetDetectorCrystalPosition(G4int det,G4int cry){return DetectorCrystalPosition[det][cry];};
  void ShiftChamber(G4double);
  void ShiftPlunger(G4double);
  void Report();

  
private:
  
  G4LogicalVolume*        ExpHall_log;
  G4VPhysicalVolume*      ExpHall_phys;
  Plunger*                thePlunger;
  Target*                 theTarget;
  ArbitraryTarget*        theArbitraryTarget;
  CsI_array*              aCsI_wall; 
  CsI_array_spherical*    aCsI_ball;
  TrackerCsISD*           TrackerCsI;
  TrackerCsISD_Messenger* TrackerCsISDMessenger;
  Chamber*                theChamber;

  G4ThreeVector DetectorCrystalPosition[GN][GS];

  Experimental_Hall_Messenger* ExperimentalHallMessenger;
  Chamber_Messenger*           ChamberMessenger;
  Plunger_Messenger*           PlungerMessenger;
  Target_Messenger*            TargetMessenger;
  ArbitraryTarget_Messenger*   ArbitraryTargetMessenger;

  TrackerIonSD*           TrackerIon;
  TrackerIonSD_Messenger* TrackerIonSDMessenger;

  G4double  griffinFwdBackPosition;
  G4int     detectorShieldSelect ;
  G4double  detectorRadialDistance ;
  G4int     extensionSuppressorLocation ; 
  G4int     customDetectorNumber ; 
  G4int     customDetectorPosition ; 
  G4int     customDetectorVal ; 
  G4int     hevimetSelector ; 
  G4bool    useTigressPositions;
  G4int     ancArrayType; //0=CsI wall, 1=CsI ball, 2=no array
  G4int     targetType; //0=arbitrary target, 1=DSAM target, 2=plunger

  GriffinMessenger* griffinMessenger;

  void DefineSuppressedParameters();
  void DefineMaterials();
};

#endif

