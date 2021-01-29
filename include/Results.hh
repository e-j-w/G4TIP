#ifndef Results_h
#define Results_h 1

#include "globals.hh"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DetectorConstruction.hh"
#include "Flags.hh"
#include "Materials.hh"
#include "PhysicsList.hh"
#include "Projectile.hh"
#include "Recoil.hh"
#include "TrackerCsIHit.hh"
#include "TrackerIonSD.hh"

//ROOT
#include "TBranch.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH1.h"
#include "TH2.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TTree.h"

#include "ArbitraryTarget.hh" //needed to know max number of layers in target

#define GN 16
#define GS 4
#define TSEG 8 //TIGRESS segments per position
#define NCsI 24
#define PI 3.14159
#define S16K 16384
#define RADIAN 57.29583

#define MAXNUMDECAYS 5

typedef struct {
  Int_t dsfold;
  Double_t calcERes[GN * GS];  // Residual energy (inferred)
  Double_t dsPos[GN * GS];     // doppler shift (array position)
  Double_t dsCore[GN * GS];    // doppler shift (core)
  Double_t thetaPos[GN * GS];  // reconstructed recoil-gamma theta value (gamma from array position)
  Double_t thetaCore[GN * GS]; // reconstructed recoil-gamma theta value (gamma from core)
  Double_t GEABPos[GN * GS];   // reconstructed addback gamma energy (gamma from array position)
  Double_t GEABCore[GN * GS];  // reconstructed addback gamma energy (gamma from core)
} EventStat;

typedef struct {
  Int_t evNb;
  Int_t Ap;
  Int_t Zp;
  Int_t Ar;
  Int_t Zr;
} IonStat;

typedef struct {
  Double_t x;
  Double_t y;
  Double_t z;
  Double_t px;
  Double_t py;
  Double_t pz;
  Double_t E;
  Double_t b;     // beta
  Double_t t;     // time
  Double_t tROffset; //time offset w.r.t. reaction
  Double_t theta; // angle of emission from beam (z) axis
  Double_t phi; // angle between plane of emission and horizontal (x) axis plane
  Double_t w;
  Double_t path;  // path length in material
  Double_t Eloss; // energy loss on path
} IonInf;

typedef struct {
  Double_t x;
  Double_t y;
  Double_t z;
  Double_t px;
  Double_t py;
  Double_t pz;
  Int_t A;
  Int_t Z;
  Double_t E;
  Double_t b;     // beta
  Double_t t;     // time
  Double_t tROffset; //time offset w.r.t. reaction
  Double_t theta; // angle of emission from beam (z) axis
  Double_t phi; // angle between plane of emission and horizontal (x) axis plane
  Double_t w;
  Double_t path;  // path length in material
  Double_t Eloss; // energy loss on path
} DecayInf;

typedef struct {
  Int_t CsIfold;
  Double_t x[NCsI];
  Double_t y[NCsI];
  Double_t z[NCsI];
  Double_t px[NCsI];
  Double_t py[NCsI];
  Double_t pz[NCsI];
  Double_t E[NCsI];
  Double_t b[NCsI];
  Double_t w[NCsI];
  Int_t A[NCsI];
  Int_t Z[NCsI];
  Int_t Id[NCsI];
  Int_t r[NCsI];
  Double_t path[NCsI]; // path length in material
  Double_t dE[NCsI];   // energy deposit for step
  Double_t dEdx[NCsI]; // dE/dx in MeV/um
  Double_t dLdx[NCsI]; // Birks Law dL/dx
  Double_t LY[NCsI];   // Birks Law light yield. LY = sum over dL/dx
                       // Double_t Q;    // Quenching factor LY/E
} CsIInf;

typedef struct {
  Int_t Gfold;
  Int_t GId[GN * GS];
  Int_t GCry[GN * GS];
  Int_t GRing[GN * GS];
  Double_t Gx[GN * GS];
  Double_t Gy[GN * GS];
  Double_t Gz[GN * GS];
  Double_t GE[GN * GS];
  Double_t GW[GN * GS];
  Double_t GT[GN * GS];
  Int_t GfoldAB;
  Int_t GIdAB[GN * GS];
  Int_t GCryAB[GN * GS];
  Int_t GRingAB[GN * GS];
  Double_t GxAB[GN * GS];
  Double_t GyAB[GN * GS];
  Double_t GzAB[GN * GS];
  Double_t GEAB[GN * GS];
} GInf;

typedef struct {
  Int_t segfold;
  Int_t segPos[GN*GS*TSEG];
  Int_t segCore[GN*GS*TSEG];
  Int_t segId[GN*GS*TSEG];
  Int_t segNumHits[GN*GS*TSEG];
  Double_t segx[GN*GS*TSEG];
  Double_t segy[GN*GS*TSEG];
  Double_t segz[GN*GS*TSEG];
  Double_t segCylr[GN*GS*TSEG];
  Double_t segCylrFrac[GN*GS*TSEG];
  Double_t segCylphi[GN*GS*TSEG];
  Double_t segCylz[GN*GS*TSEG];
  Double_t segE[GN*GS*TSEG];
  Double_t segw[GN*GS*TSEG];
  Int_t maxESegfold;
  Int_t maxESegPos[GN*GS*TSEG];
  Int_t maxESegCore[GN*GS*TSEG];
  Int_t maxESegId[GN*GS*TSEG];
  Int_t maxESegNumHits[GN*GS*TSEG];
  Double_t maxESegCylr[GN*GS*TSEG];
  Double_t maxESegCylrFrac[GN*GS*TSEG];
  Double_t maxESegCylphi[GN*GS*TSEG];
  Double_t maxESegCylz[GN*GS*TSEG];
  Double_t maxESegE[GN*GS*TSEG];
} SegInf;

  

class Results {
public:
  Results(DetectorConstruction *, PhysicsList *);
  ~Results();

public:
  void SetupRunFusEvap(Int_t, Int_t, Int_t);
  void SetupRunCoulex();
  void SetupRun();

  void FillTree(G4int, TrackerIonHitsCollection *, TrackerCsIHitsCollection *,
                G4double[GN][GS], G4double[GN][GS], G4ThreeVector[GN][GS],
                G4double[GN][GS], G4int[GN][GS][TSEG], G4double[GN][GS][TSEG], G4double[GN][GS][TSEG], G4ThreeVector[GN][GS][TSEG], G4ThreeVector[GN][GS][TSEG]);
  void TreeSave(G4String);
  void TreeRead(G4String);
  void TreeAdd(G4String);
  void TreeClear();
  void TreeCreate();
  void TreeReport();
  void TreeSetCsIDetector(G4int index) { CsITrigId = index; };
  void ProjLabScattAngle();
  void RecLabScattAngle();
  void TargetFaceF_CM();
  void SetTargetFaceCrossSection(G4double xs) { TargetFaceCrossSection = xs; };
  G4int RingMap(G4int, G4int);
  void ReportCrystalPositions();
  void ReportCsIWallPositions();
  void GetCsIWallPositions();
  void GetCsIBallPositions();
  void GroupCosDist();
  G4double FWHM_response(G4double);
  G4double CalculatePath(G4ThreeVector, G4ThreeVector);
  G4double CalculateBirksLawStep(G4int, G4double, G4double);

  G4ThreeVector tigressFwdPos[GN][GS];
  G4ThreeVector tigressBackPos[GN][GS];

private:
  // ROOT Tree stuff
  TTree *tree;

  Projectile *theProjectile;
  DetectorConstruction *theDetector;
  PhysicsList *thePhysicsList;

  EventStat eStat;
  IonStat stat;
  IonInf gun;
  IonInf pRIn;
  IonInf pROut;
  IonInf rROut;
  IonInf pTIn_plunger, pTIn_dsam; //projectile target in
  IonInf pTOut_plunger; //projectile target out
  IonInf rTOut_plunger; //recoil target out
  IonInf pBIn_plunger, pBIn_dsam, rBIn_dsam; //backing in
  IonInf pBOut_plunger, rBOut_dsam; //backing out
  IonInf rDIn_plunger; //degrader in
  IonInf rDOut_plunger; //degrader out
  IonInf pTIn_target[NATARGETLAYERS], pTOut_target[NATARGETLAYERS]; //projectile target in and out of each layer
  IonInf rTIn_target[NATARGETLAYERS], rTOut_target[NATARGETLAYERS]; //recoil target in and out of each layer
  DecayInf rDec[MAXNUMDECAYS];
  IonInf partROut;      // ion tracking (projectile, residual)
  CsIInf partHit;     // particle hit
  GInf GHit;          // gamma hit
  SegInf SegHit;      // TIGRESS segment hit
  G4double maxGe[GN]; // maximum single gamma energy deposit in a given detector
                      // (used to get position of hits when using addback)
  G4int Ap, Zp, Ar, Zr, numP, numN, numA;
  G4ThreeVector rDiPos,
      rDPos; // recoil degrader position vectors for calculating distance
  G4double dDensity;   // degrader density for calculating path in mg/cm^2
  G4double CsIDensity; // CsI density for calculating path in mg/cm^2
  G4int CsITrigId;     // ID of CsI detector to save particle data for (0 = all
                    // detectors)

  G4double kB[NCsI];  // Birks constant in um/MeV
  G4double kBm[NCsI]; // Birks constant in (mg/cm^2)/MeV
  G4double S[NCsI];   // scaling factor from LY to channel

  size_t soh, sogh, soi, sos, soes, sod;

  G4int numDec;

  TH1D *h, *g;
  TCanvas *c, *c1;
  TH2D *correlation;
  G4double TargetFaceCrossSection;

  G4ThreeVector CP[GN][GS];
  G4ThreeVector PP[NCsISph];

  G4Material *a;
};

#endif
