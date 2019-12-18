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
  
  Plunger*   GetPlunger(){return thePlunger;};
  CsI_array* GetCsIWall(){return aCsI_wall;};
  CsI_array_spherical* GetCsIBall(){return aCsI_ball;};
  Chamber*   GetChamber(){return theChamber;};
  G4bool usingCsIBall(){return useCsIball;};
  
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
  void UseCsIBall( G4bool input ) {useCsIball = input;};
  void UpdateGeometry();
  G4ThreeVector GetDetectorCrystalPosition(G4int det,G4int cry){return DetectorCrystalPosition[det][cry];};
  void SetPosZ_TIP(G4double);
  void ShiftPlunger(G4double);
  void Report();

  
private:
  
  G4LogicalVolume*        ExpHall_log;
  G4VPhysicalVolume*      ExpHall_phys;
  Plunger*                thePlunger;
  CsI_array*              aCsI_wall; 
  CsI_array_spherical*    aCsI_ball;
  TrackerCsISD*           TrackerCsI;
  TrackerCsISD_Messenger* TrackerCsISDMessenger;
  Chamber*                theChamber;
  G4ThreeVector DetectorCrystalPosition[GN][GS];


  Experimental_Hall_Messenger* ExperimentalHallMessenger;
  Chamber_Messenger*           ChamberMessenger;
  Plunger_Messenger*           PlungerMessenger;

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
  G4bool    useCsIball;

  GriffinMessenger* griffinMessenger;

  void DefineSuppressedParameters();
  void DefineMaterials();
};

#endif

