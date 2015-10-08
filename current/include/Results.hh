#ifndef Results_h
#define Results_h 1

#include "globals.hh"
#include "TROOT.h"
#include "TTree.h"
#include "TBranch.h"
#include "TStyle.h"
#include "TFile.h"
#include "TCanvas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TrackerIonSD.hh"
#include "TrackerCsIHit.hh"
#include "Projectile.hh"
#include "Recoil.hh"
#include "Flags.hh"
#include "DetectorConstruction.hh"
#include "Materials.hh"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"

#define GN     16
#define GS     4
#define NCsI   24
#define PI     3.14159
#define S16K   16384
#define RADIAN 57.29583

typedef struct{
  Int_t evNb;
  Int_t Ap;
  Int_t Zp;
  Int_t Ar;
  Int_t Zr;
 } IonStat;

typedef struct{
    Double_t x;
    Double_t y;
    Double_t z;
    Double_t px;
    Double_t py;
    Double_t pz;
    Double_t E;
    Double_t b;
    Double_t w;
    Double_t path;  // path length in material
    Double_t Eloss; // energy loss on path
 } IonInf;

typedef struct{
    Double_t x;
    Double_t y;
    Double_t z;
    Double_t px;
    Double_t py;
    Double_t pz;
    Double_t E;
    Double_t b;
    Double_t w;
    Double_t Id;
    Double_t r;
    Double_t path; // path length in material
    Double_t dE;   // energy deposit for step
    Double_t dEdx; // dE/dx in MeV/um
    Double_t dLdx; // Birks Law dL/dx
    Double_t LY;   // Birks Law light yield. LY = sum over dL/dx
    Double_t Q;    // Quenching factor LY/E
 } CsIInf;

typedef struct{
    Int_t    Gfold;
    Int_t    GId[GN*GS];
    Int_t    GSeg[GN*GS];
    Double_t Gx[GN*GS];
    Double_t Gy[GN*GS];
    Double_t Gz[GN*GS];
    Double_t GE[GN*GS];
    Double_t GW[GN*GS];
 } GInf;
class Results
{
public:
  //Results(Projectile*,Recoil*,DetectorConstruction*);
  Results(Projectile*,DetectorConstruction*);
  ~Results();

public:
  
  void SetupRun(Int_t, Int_t, Int_t);

  void FillTree(G4int,TrackerIonHitsCollection*,TrackerCsIHitsCollection*,G4double[16][4], G4double[16][4],G4ThreeVector[16][4]);
  void TreeView();
  void TreeSave(G4String);
  void TreeRead(G4String);
  void TreeAdd(G4String);
  void TreeClear();
  void TreeCreate();
  void TreeReport();
  void TreeSetCsIDetector(G4int index){CsITrigId=index;};
  void ProjLabScattAngle();
  void RecLabScattAngle();
  void CrossSectionZProfile();
  void TargetFaceF_CM();
  void SetTargetFaceCrossSection(G4double xs){TargetFaceCrossSection=xs;};
  void GammaRingSpectrum(G4int);
  void CsIRingSpectrum(G4int);
  void DetCryCsIGammaSpectrum(G4int,G4int,G4int);
  void DetRingCsIRingGammaSpectrum(G4int,G4int,G4double);
  G4int RingMap(G4int,G4int);
  void ReportCrystalPositions();
  void ReportCsIPositions();
  void CalculateCrystalPositions();
  void CalculateCsIPositions();
  void GroupCosDist();
  G4double FWHM_response(G4double);
  G4double CalculatePath(G4ThreeVector,G4ThreeVector);
  G4double CalculateBirksLawStep(G4int,G4double,G4double);
private:
  
 // ROOT Tree stuff
  TTree* tree;
  G4int  IonFill;

  Projectile*           theProjectile;
  Recoil*               theRecoil;
  DetectorConstruction* theDetector;

  IonStat       stat;
  IonInf        gun,pTIn,pRIn,rROut,rBIn,rBOut,rDec; //ion tracking (projectile, residual)
  CsIInf        partHit; //particle hit
  GInf          GHit; //gamma hit
  G4int         Ap,Zp,Ar,Zr;
  G4ThreeVector rDiPos,rDPos; // recoil degrader position vectors for calculating distance
  G4double      dDensity; // degrader density for calculating path in mg/cm^2
  G4double      CsIDensity;   // CsI density for calculating path in mg/cm^2
  G4int         CsITrigId; //ID of CsI detector to save particle data for (0 = all detectors)

  G4double kB[NCsI];  // Birks constant in um/MeV
  G4double kBm[NCsI]; // Birks constant in (mg/cm^2)/MeV
  G4double S[NCsI]; // scaling factor from LY to channel


  size_t soh,sogh,soi,sos;

  //CsI parameters outside of structure
  Double_t PE;
  Double_t PLY;   // Birks Law light yield. LY = sum over dL/dx

  TH1D     *h,*g;
  TCanvas  *c,*c1;
  TH2D     *correlation;
  G4double TargetFaceCrossSection;
 
  G4ThreeVector CP[GN][GS];
  G4ThreeVector PP[NCsI];

  G4double A,B,C,F,G,H;

  G4Material* a;
};

#endif


           
