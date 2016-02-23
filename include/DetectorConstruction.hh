#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

#include "G4AssemblyVolume.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4SDManager.hh"
#include "Materials.hh"
#include "Experimental_Hall.hh"
#include "Experimental_Hall_Messenger.hh"
#include "Target.hh"
#include "Target_Messenger.hh"
#include "TrackerIonSD.hh"
#include "TrackerIonSD_Messenger.hh"
//#include "PIN_array.hh"
//#include "TrackerPINSD.hh"
#include "CsI_array.hh"
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
 
    Chamber* GetChamber(){return theChamber;};
    Target* GetTarget(){return theTarget;};
    CsI_array* GetCsIArray(){return aCsI_array;};

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
    void UpdateGeometry();
    G4ThreeVector GetDetectorCrystalPosition(G4int det,G4int cry){return DetectorCrystalPosition[det][cry];};
    
    //TIP chamber z-shift
    void setZShift(G4double);
  
  private:
  
  G4LogicalVolume* ExpHall_log;
  G4VPhysicalVolume* ExpHall_phys;
  Target* theTarget;
  CsI_array *aCsI_array;
  //PIN_array *aPIN_array;
  TrackerCsISD* TrackerCsI;
  TrackerCsISD_Messenger* TrackerCsISDMessenger;
  //TrackerPINSD* TrackerPIN;
  Chamber* theChamber;
  G4ThreeVector DetectorCrystalPosition[GN][GS];

  Experimental_Hall_Messenger* ExperimentalHallMessenger;
  Chamber_Messenger* ChamberMessenger;
  Target_Messenger*    TargetMessenger;


  TrackerIonSD* TrackerIon;
  TrackerIonSD_Messenger* TrackerIonSDMessenger;

  DetectionSystemGriffin* myGriffin;

  G4double  griffinFwdBackPosition;
  G4int     detectorShieldSelect ;
  G4double  detectorRadialDistance ;
  G4int     extensionSuppressorLocation ; 
  G4int     customDetectorNumber ; 
  G4int     customDetectorPosition ; 
  G4int     customDetectorVal ; 
  G4int     hevimetSelector ; 
  G4bool    useTigressPositions;

  GriffinMessenger* griffinMessenger;
};

#endif

