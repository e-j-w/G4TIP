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
#include "TrackerPINHit.hh"
#include "Projectile.hh"
#include "Flags.hh"
#include "TH1.h"
#include "TGraph.h"

#define GN  16
#define GS   4
#define NPIN 44
#define PI  3.14159
#define S16K 16384
#define RADIAN 57.29583

typedef struct{
  Int_t evNb;
  Int_t Ap;
  Int_t Zp;
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
 } PINInf;
class Results
{
public:
  Results(Projectile*);
  ~Results();

public:
  
  void SetupRun(G4int,G4int);

  void FillTree(G4int,TrackerIonHitsCollection*,TrackerPINHitsCollection*,G4double[16][4], G4double[16][4],G4ThreeVector[16][4]);
  void TreeView();
  void TreeSave(G4String);
  void TreeRead(G4String);
  void TreeAdd(G4String);
  void TreeClear();
  void TreeCreate();
  void TreeReport();

  void GammaRingSpectrum(G4int);
  G4int RingMap(G4int,G4int);
  void ReportCrystalPositions();
  void CalculateCrystalPositions();
  G4double FWHM_response(G4double);
private:
  
 // ROOT Tree stuff
 
  TTree*  tree;
  G4int  IonFill;

  Projectile *theProjectile;
  IonStat stat;
  IonInf gun,pTIn,pRIn,rROut,rBIn,rBOut,rDec;
  G4int  Ap,Zp,Ar,Zr;

  size_t soh,soi,sos;

  Int_t    Gfold;
  Int_t    GId[GN*GS];
  Int_t    GSeg[GN*GS];
  Double_t Gx[GN*GS];
  Double_t Gy[GN*GS];
  Double_t Gz[GN*GS];
  Double_t GE[GN*GS];
  Double_t GW[GN*GS];

  TH1D* h,*g;
  TCanvas *c;

  G4double TargetFaceCrossSection;
 
  G4ThreeVector CP[GN][GS];
  G4ThreeVector PP[NPIN];


  //FWHM
  G4double F;
  G4double G;
  G4double H;
 
  //conversion from energy to channels
  G4double A;
  G4double B;
  G4double C;

};

#endif


           
