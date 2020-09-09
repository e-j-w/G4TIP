#include "Results.hh"

Results::Results(DetectorConstruction *det, PhysicsList *physl) : theDetector(det), thePhysicsList(physl) 
{
  soh = sizeof(partHit);
  sogh = sizeof(GHit);
  soi = sizeof(gun);
  sos = sizeof(stat);
  soes = sizeof(eStat);
  sod = sizeof(rDec[0]);
  memset(CP, 0, sizeof(CP));
}

Results::~Results() { tree->Delete(); }
//---------------------------------------------------------
void Results::SetupRunFusEvap(Int_t nP, Int_t nN, Int_t nA) {
  // Get A, Z of the projectile and recoiling nucleus (needed for particle
  // identification when saving data to tree)
  numP = nP;
  numN = nN;
  numA = nA;
  Ap = thePhysicsList->getReactionFusEvap()->getProjectile()->getA();
  Zp = thePhysicsList->getReactionFusEvap()->getProjectile()->getZ();
  switch(theDetector->GetTargetType())
  {
    case 2:
      //plunger
      Ar = thePhysicsList->getReactionFusEvap()->getProjectile()->getA() + theDetector->GetPlunger()->getTargetMass() - numP - numN - numA * 4;
      Zr = thePhysicsList->getReactionFusEvap()->getProjectile()->getZ() + theDetector->GetPlunger()->getTargetCharge() - numP - numA * 2;
      //   G4cout << "Results: target A: " << theDetector->GetPlunger()->getTargetMass() << ", target Z: " <<theDetector->GetPlunger()->getTargetCharge() << G4endl;
      break;
    case 1:
      //dsam target
      Ar = thePhysicsList->getReactionFusEvap()->getProjectile()->getA() + theDetector->GetTarget()->getTargetMass() - numP - numN - numA * 4;
      Zr = thePhysicsList->getReactionFusEvap()->getProjectile()->getZ() + theDetector->GetTarget()->getTargetCharge() - numP - numA * 2;
      // G4cout << "Results: target A: " << theDetector->GetTarget()->getTargetMass() << ", target Z: " << theDetector->GetTarget()->getTargetCharge() << G4endl;
      break;
    default:
      //arbitrary target
      Ar = thePhysicsList->getReactionFusEvap()->getProjectile()->getA() + theDetector->GetArbitraryTarget()->getTargetMass(theDetector->GetArbitraryTarget()->getTargetExLayer()) - numP - numN - numA * 4;
      Zr = thePhysicsList->getReactionFusEvap()->getProjectile()->getZ() + theDetector->GetArbitraryTarget()->getTargetCharge(theDetector->GetArbitraryTarget()->getTargetExLayer()) - numP - numA * 2;
      break;
  }

  //G4cout << "Results: projectile A: " << Ap << ", projectile Z: " << Zp << ",recoil A: " << Ar << ", recoil Z: " << Zr << G4endl;

  numDec = thePhysicsList->getReactionFusEvap()->GetNumDecays();
  G4cout << "Results - number of decays: " << numDec << G4endl;

  SetupRun();
}
//---------------------------------------------------------
void Results::SetupRunCoulex() {

  Ap = thePhysicsList->getReactionCoulex()->getProjectile()->getA();
  Zp = thePhysicsList->getReactionCoulex()->getProjectile()->getZ();
  Ar = thePhysicsList->getReactionCoulex()->getRecoil()->getA();
  Zr = thePhysicsList->getReactionCoulex()->getRecoil()->getZ();
  numDec = 1;

  SetupRun();
}
//---------------------------------------------------------
void Results::SetupRun(){

  // get CsI crystal positions
  switch (theDetector->GetAncArrayType())
  {
    case 2:
      // no ancillary array
      break;
    case 1:
      //CsI ball
      GetCsIBallPositions();
      break;
    default:
      //CsI wall
      GetCsIWallPositions();
      break;
  }

  /* // get HPGe crystal positions
  for(int i=0; i<GN; i++)
    for(int j=0; j<GS; j++)
      {
              CP[i][j]=theDetector->GetDetectorCrystalPosition(i,j);
              printf("HPGe position %d crystal %d x %f y %f z
    %f\n",i+1,j,CP[i][j].getX(),CP[i][j].getY(),CP[i][j].getZ());
      }*/

  G4cout << "Results - creating tree... ";
  TreeCreate();
  G4cout << "created!" << G4endl;
  // getc(stdin);
}
//---------------------------------------------------------
void Results::TreeCreate() {

  char branchName[256];

  if (tree == NULL) {
    tree = new TTree("tree", "tree");
    tree->Branch("GammaFold", &GHit.Gfold, "Gfold/I");
    tree->Branch("TigressID", GHit.GId, "GId[Gfold]/I");
    tree->Branch("TigressCrystal", GHit.GCry, "GCry[Gfold]/I");
    tree->Branch("TigressRing", GHit.GRing, "GRing[Gfold]/I");
    tree->Branch("Gx", GHit.Gx, "Gx[Gfold]/D");
    tree->Branch("Gy", GHit.Gy, "Gy[Gfold]/D");
    tree->Branch("Gz", GHit.Gz, "Gz[Gfold]/D");
    tree->Branch("GammaEnergy", GHit.GE, "GE[Gfold]/D");
    tree->Branch("GW", GHit.GW, "GW[Gfold]/D");
    tree->Branch("GT", GHit.GT, "GT[Gfold]/D");
    tree->Branch("GammaFoldAddBack", &GHit.GfoldAB, "GfoldAB/I");
    tree->Branch("TigressIDAddBack", GHit.GIdAB, "GIdAB[GfoldAB]/I");
    tree->Branch("TigressCrystalAddBack", GHit.GCryAB, "GCryAB[GfoldAB]/I");
    tree->Branch("TigressRingAddBack", GHit.GRingAB, "GRingAB[GfoldAB]/I");
    tree->Branch("GxAddBack", GHit.GxAB, "GxAB[GfoldAB]/D");
    tree->Branch("GyAddBack", GHit.GyAB, "GyAB[GfoldAB]/D");
    tree->Branch("GzAddBack", GHit.GzAB, "GzAB[GfoldAB]/D");
    tree->Branch("GammaEnergyAddBack", GHit.GEAB, "GEAB[GfoldAB]/D");
    if(theDetector->GetUseTIGRESSSegments()){
      tree->Branch("TigressSegmentFold", &SegHit.segfold, "segfold/I");
      tree->Branch("TigressSegmentId", SegHit.segId, "segId[segfold]/I");
      tree->Branch("TigressSegmentNumHits", SegHit.segNumHits, "segNumHits[segfold]/I");
      tree->Branch("TigressSegmentx", SegHit.segx, "segx[segfold]/D");
      tree->Branch("TigressSegmenty", SegHit.segy, "segy[segfold]/D");
      tree->Branch("TigressSegmentz", SegHit.segz, "segz[segfold]/D");
      if(theDetector->GetUseTIGRESSSegmentsSph()){
        tree->Branch("TigressSegmentCylSphr", SegHit.segCylr, "segCylr[segfold]/D");
        tree->Branch("TigressSegmentCylSphphi", SegHit.segCylphi, "segCylphi[segfold]/D");
        tree->Branch("TigressSegmentCylSphz", SegHit.segCylz, "segCylz[segfold]/D");
      }else{
        tree->Branch("TigressSegmentCylr", SegHit.segCylr, "segCylr[segfold]/D");
        tree->Branch("TigressSegmentCylrFrac", SegHit.segCylrFrac, "segCylrFrac[segfold]/D");
        tree->Branch("TigressSegmentCylphi", SegHit.segCylphi, "segCylphi[segfold]/D");
        tree->Branch("TigressSegmentCylz", SegHit.segCylz, "segCylz[segfold]/D");
      }
      tree->Branch("TigressSegmentE", SegHit.segE, "segE[segfold]/D");
      tree->Branch("TigressSegmentW", SegHit.segw, "segw[segfold]/D");
      tree->Branch("TigressSegmentMaxEFold", &SegHit.maxESegfold, "maxESegfold/I");
      tree->Branch("TigressSegmentMaxEId", SegHit.maxESegId, "maxESegId[maxESegfold]/I");
      tree->Branch("TigressSegmentMaxENumHits", SegHit.maxESegNumHits, "maxESegNumHits[maxESegfold]/I");
      if(theDetector->GetUseTIGRESSSegmentsSph()){
        tree->Branch("TigressSegmentMaxECylSphr", SegHit.maxESegCylr, "maxESegCylr[maxESegfold]/D");
        tree->Branch("TigressSegmentMaxECylSphphi", SegHit.maxESegCylphi, "maxESegCylphi[maxESegfold]/D");
        tree->Branch("TigressSegmentMaxECylSphz", SegHit.maxESegCylz, "maxESegCylz[maxESegfold]/D");
      }else{
        tree->Branch("TigressSegmentMaxECylr", SegHit.maxESegCylr, "maxESegCylr[maxESegfold]/D");
        tree->Branch("TigressSegmentMaxECylrFrac", SegHit.maxESegCylrFrac, "maxESegCylrFrac[maxESegfold]/D");
        tree->Branch("TigressSegmentMaxECylphi", SegHit.maxESegCylphi, "maxESegCylphi[maxESegfold]/D");
        tree->Branch("TigressSegmentMaxECylz", SegHit.maxESegCylz, "maxESegCylz[maxESegfold]/D");
      }
      tree->Branch("TigressSegmentMaxESegE", SegHit.maxESegE, "maxESegE[maxESegfold]/D");
    }
    tree->Branch("DopplerShiftFactorFold", &eStat.dsfold, "dsfold/I");
    tree->Branch("DopplerShiftFactor", &eStat.ds, "ds[dsfold]/D");
    tree->Branch("calcERecoil", &eStat.calcERes, "calcERes[dsfold]/D");
    tree->Branch("CsIFold", &partHit.CsIfold, "CsIfold/I");
    tree->Branch("CsIx", partHit.x, "x[CsIfold]/D");
    tree->Branch("CsIy", partHit.y, "y[CsIfold]/D");
    tree->Branch("CsIz", partHit.z, "z[CsIfold]/D");
    tree->Branch("CsIpx", partHit.px, "px[CsIfold]/D");
    tree->Branch("CsIpy", partHit.py, "py[CsIfold]/D");
    tree->Branch("CsIpz", partHit.pz, "pz[CsIfold]/D");
    tree->Branch("CsIEnergy", partHit.E, "E[CsIfold]/D");
    tree->Branch("CsIb", partHit.b, "b[CsIfold]/D");
    tree->Branch("CsIw", partHit.w, "w[CsIfold]/D");
    tree->Branch("CsIA", partHit.A, "A[CsIfold]/I");
    tree->Branch("CsIZ", partHit.Z, "Z[CsIfold]/I");
    tree->Branch("CsIID", partHit.Id, "Id[CsIfold]/I");
    tree->Branch("CsIr", partHit.r, "r[CsIfold]/I");
    tree->Branch("CsIpath", partHit.path, "path[CsIfold]/D");
    tree->Branch("CsIdE", partHit.Id, "dE[CsIfold]/D");
    tree->Branch("CsIdEdx", partHit.dEdx, "dEdx[CsIfold]/D");
    tree->Branch("CsIdLdx", partHit.dLdx, "dLdx[CsIfold]/D");
    tree->Branch("CsILY", partHit.LY, "LY[CsIfold]/D");
    tree->Branch("ProjectileStart", &gun,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:t/D:tROffset/D:theta/""D:phi/D:w/D"); // projectile when shot from the particle gun
    tree->Branch("ProjectileReactionIn", &pRIn,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:t/D:tROffset/D:theta/""D:phi/D:w/D"); // projectile at the reaction point
    tree->Branch("ProjectileReactionOut",&pROut,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:t/D:tROffset/D:theta/""D:phi/D:w/D");
    tree->Branch("RecoilReactionOut", &rROut,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:t/D:tROffset/D:theta/""D:phi/D:w/D"); // recoil at the reaction point
    //setup branches that are relevant to the chosen target
    switch(theDetector->GetTargetType())
    {
      case 2:
        //plunger
        tree->Branch("ProjectileBackingIn", &pBIn_plunger,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:t/D:tROffset/D:theta/""D:phi/D:w/D"); // projectile upon entering the target  
        tree->Branch("ProjectileTargetIn", &pTIn_plunger,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:t/D:tROffset/D:theta/""D:phi/D:w/D"); // projectile upon entering the target 
        tree->Branch("ProjectileTargetOut",&pTOut_plunger,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:t/D:tROffset/D:theta/""D:phi/D:w/D");
        tree->Branch("RecoilTargetOut", &rTOut_plunger,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:t/D:tROffset/D:theta/D:phi/D:w/D"); // recoil upon leaving the target
        tree->Branch("RecoilDegraderIn", &rDIn_plunger,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:t/D:tROffset/D:theta/D:phi/D:w/D"); // recoil upon entering the degrader  
        tree->Branch("RecoilDegraderOut", &rDOut_plunger,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:t/D:tROffset/D:theta/D:phi/D:w/D"); // recoil upon leaving the degrader
        break;
      case 1:
        //dsam target
        tree->Branch("ProjectileTargetIn", &pTIn_dsam,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:t/D:tROffset/D:theta/""D:phi/D:w/D"); // projectile upon entering the target
        tree->Branch("ProjectileBackingIn",&pBIn_dsam,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:t/D:tROffset/D:theta/""D:phi/D:w/D");
        tree->Branch("RecoilBackingIn", &rBIn_dsam,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:t/D:tROffset/D:theta/D:phi/D:w/D"); // recoil upon leaving the target/entering the backing
        tree->Branch("RecoilBackingOut", &rBOut_dsam,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:t/D:tROffset/D:theta/D:phi/D:w/D"); // recoil upon leaving the backing (if it makes it that far)
        break;
      default:
        //arbitrary target
        for(int i=0; i<theDetector->GetArbitraryTarget()->getNumberOfLayers(); i++){ //make branches for each layer
          sprintf(branchName, "ProjectileTargetLayer%iIn", i + 1);
          tree->Branch(branchName,&pTIn_target[i],"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:t/D:tROffset/D:theta/""D:phi/D:w/D");
        }
        for(int i=0; i<theDetector->GetArbitraryTarget()->getNumberOfLayers(); i++){ //make branches for each layer
          sprintf(branchName, "ProjectileTargetLayer%iOut", i + 1);
          tree->Branch(branchName,&pTOut_target[i],"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:t/D:tROffset/D:theta/""D:phi/D:w/D");
        }
        for(int i=0; i<theDetector->GetArbitraryTarget()->getNumberOfLayers(); i++){ //make branches for each layer
          sprintf(branchName, "RecoilTargetLayer%iIn", i + 1);
          tree->Branch(branchName,&rTIn_target[i],"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:t/D:tROffset/D:theta/""D:phi/D:w/D");
        }
        for(int i=0; i<theDetector->GetArbitraryTarget()->getNumberOfLayers(); i++){ //make branches for each layer
          sprintf(branchName, "RecoilTargetLayer%iOut", i + 1);
          tree->Branch(branchName,&rTOut_target[i],"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:t/D:tROffset/D:theta/""D:phi/D:w/D");
        }
        break;
    } 

    //setup branches that are relevant to the chosen reaction
    switch(thePhysicsList->getReactionType()==0)
    {
      case 1:
        //coulex
        break;
      default:
        //fusion-evaporation
        tree->Branch("ParticleReactionOut", &partROut,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:t/D:theta/D:phi/D:w/D"); // evaporated particle at the reaction point
        break;
    }

    //setup decays
    for (int i = 0; i < numDec; i++) // make branch for each decay
      if (i < MAXNUMDECAYS) {
        sprintf(branchName, "Decay%i", i + 1);
        tree->Branch(branchName, &rDec[i],"x/D:y/D:z/D:px/D:py/D:pz/D:A/I:Z/I:E/D:b/D:t/D:tROffset/D:theta/D:phi/D:w/D"); // recoil upon decaying via gamma emission
      }
 } else {
    G4cout << "WARNING: Tree exists, could not create new tree!" << G4endl;
    //getc(stdin);
  }
}
//---------------------------------------------------------
void Results::TreeClear() {
  tree->Delete("all");
  tree = NULL;
  TreeCreate();
}
//---------------------------------------------------------
void Results::TreeReport() { tree->Print(); }
//---------------------------------------------------------
void Results::TreeSave(G4String name) {
  TDirectory *dir = new TDirectory();
  dir = gDirectory;
  TFile f(name, "recreate");
  f.cd();
  // tree->AutoSave();
  // tree->SetDirectory(dir);
  tree->Write();
  f.Close();
  dir->cd();
  G4cout << "Trees of simulated parameters saved in file " << name << G4endl;
}
//---------------------------------------------------------
void Results::FillTree(G4int evtNb, TrackerIonHitsCollection *IonCollection,
                       TrackerCsIHitsCollection *CsICollection,
                       G4double gw[GN][GS], G4double ge[GN][GS],
                       G4ThreeVector gp[GN][GS], G4double gt[GN][GS], 
                       G4int tsh[GN][GS][TSEG], G4double tsw[GN][GS][TSEG], G4double tse[GN][GS][TSEG], G4ThreeVector tsp[GN][GS][TSEG], 
                       G4ThreeVector tscp[GN][GS][TSEG]) {

  G4int Nt = IonCollection->entries();

  memset(&eStat, 0, soes);
  memset(&stat, 0, sos);
  memset(&gun, 0, soi);
  memset(&pBIn_plunger, 0, soi);
  memset(&pTIn_plunger, 0, soi);
  memset(&pTOut_plunger, 0, soi);
  memset(&rTOut_plunger,0,soi);
  memset(&rDIn_plunger,0,soi);
  memset(&rDOut_plunger,0,soi);
  memset(&pTIn_dsam,0,soi);
  memset(&pBIn_dsam,0,soi);
  memset(&rBIn_dsam,0,soi);
  memset(&rBOut_dsam,0,soi);
  memset(&pRIn, 0, soi);
  memset(&pROut, 0, soi);
  memset(&rROut, 0, soi);
  if(theDetector->GetTargetType()==0){
    for(int i=0; i<theDetector->GetArbitraryTarget()->getNumberOfLayers(); i++){
      memset(&pTIn_target[i], 0, soi);
      memset(&pTOut_target[i], 0, soi);
      memset(&rTIn_target[i], 0, soi);
      memset(&rTOut_target[i], 0, soi);
    }
  }
 
  for (int i = 0; i < numDec; i++)
    if (i < MAXNUMDECAYS)
      memset(&rDec[i], 0, sod);

  memset(&partROut, 0, soi);
  memset(&partHit, 0, soh);
  // memset(&GHit,0,sogh);

  // evaporated particle tracking
  G4int Np = CsICollection->entries();
  if (Np > 0) {
    if (((numA > 0) && ((*CsICollection)[0]->GetA() == 4) &&
          ((*CsICollection)[0]->GetZ() == 2)) ||
        ((numP > 0) && ((*CsICollection)[0]->GetA() == 1) &&
          ((*CsICollection)[0]->GetZ() == 1)) ||
        ((numN > 0) && ((*CsICollection)[0]->GetA() == 1) &&
          ((*CsICollection)[0]->GetZ() == 0))) {
            
      partROut.x = (*CsICollection)[0]->GetPos().getX() / mm;
      partROut.y = (*CsICollection)[0]->GetPos().getY() / mm;
      partROut.z = (*CsICollection)[0]->GetPos().getZ() / mm;
      partROut.px = (*CsICollection)[0]->GetMom().getX() / MeV;
      partROut.py = (*CsICollection)[0]->GetMom().getY() / MeV;
      partROut.pz = (*CsICollection)[0]->GetMom().getZ() / MeV;
      partROut.b = (*CsICollection)[0]->GetBeta();
      partROut.E = (*CsICollection)[0]->GetKE() / MeV;
      partROut.t = (*CsICollection)[0]->GetTime() / ns;
      partROut.tROffset = 0.;
      partROut.theta = acos(((*CsICollection)[0]->GetMom().getZ()) /
                            ((*CsICollection)[0]->GetMom().mag())) /
                        degree; // angle between (0,0,1) and momentum vector
      partROut.phi =
          acos((*CsICollection)[0]->GetMom().getX() /
                sqrt((*CsICollection)[0]->GetMom().getX() *
                        (*CsICollection)[0]->GetMom().getX() +
                    (*CsICollection)[0]->GetMom().getY() *
                        (*CsICollection)[0]->GetMom().getY())) /
          degree; // angle between (1,0,0) and momentum vector in x and y
      partROut.w = (*CsICollection)[0]->GetWeight();
    }
  }


  if (Nt > 0) {
    //G4cout << "Saving ion collection data..." << G4endl;
    stat.evNb = evtNb;
    stat.Ap = Ap;
    stat.Zp = Zp;

    for (Int_t i = 0; i < Nt; i++) {
      
      //      if((*IonCollection)[i]->GetFlag()!=0)
      //	printf("Flag %d\n",(*IonCollection)[i]->GetFlag());

      if ((*IonCollection)[i]->GetFlag() == GUN_FLAG) {
        if ((*IonCollection)[i]->GetA() == Ap)
          if ((*IonCollection)[i]->GetZ() == Zp) {
            gun.x = (*IonCollection)[i]->GetPos().getX() / mm;
            gun.y = (*IonCollection)[i]->GetPos().getY() / mm;
            gun.z = (*IonCollection)[i]->GetPos().getZ() / mm;
            gun.px = (*IonCollection)[i]->GetMom().getX() / MeV;
            gun.py = (*IonCollection)[i]->GetMom().getY() / MeV;
            gun.pz = (*IonCollection)[i]->GetMom().getZ() / MeV;
            gun.b = (*IonCollection)[i]->GetBeta();
            gun.E = (*IonCollection)[i]->GetKE() / MeV;
            gun.t = (*IonCollection)[i]->GetTime() / ns;
            gun.tROffset = 0.;
            gun.theta = acos(((*IonCollection)[i]->GetMom().getZ()) /
                             ((*IonCollection)[i]->GetMom().mag())) /
                        degree; // angle between (0,0,1) and momentum vector
            gun.phi =
                acos((*IonCollection)[i]->GetMom().getX() /
                     sqrt((*IonCollection)[i]->GetMom().getX() *
                              (*IonCollection)[i]->GetMom().getX() +
                          (*IonCollection)[i]->GetMom().getY() *
                              (*IonCollection)[i]->GetMom().getY())) /
                degree; // angle between (1,0,0) and momentum vector in x and y
            gun.w = (*IonCollection)[i]->GetWeight();
          }
      } else if ((*IonCollection)[i]->GetFlag() == PLUNGER_BACKING_IN_FLAG) {
        if ((*IonCollection)[i]->GetA() == Ap)
          if ((*IonCollection)[i]->GetZ() == Zp) {
            pBIn_plunger.x = (*IonCollection)[i]->GetPos().getX() / mm;
            pBIn_plunger.y = (*IonCollection)[i]->GetPos().getY() / mm;
            pBIn_plunger.z = (*IonCollection)[i]->GetPos().getZ() / mm;
            pBIn_plunger.px = (*IonCollection)[i]->GetMom().getX() / MeV;
            pBIn_plunger.py = (*IonCollection)[i]->GetMom().getY() / MeV;
            pBIn_plunger.pz = (*IonCollection)[i]->GetMom().getZ() / MeV;
            pBIn_plunger.b = (*IonCollection)[i]->GetBeta();
            pBIn_plunger.E = (*IonCollection)[i]->GetKE() / MeV;
            pBIn_plunger.t = (*IonCollection)[i]->GetTime() / ns;
            pBIn_plunger.tROffset = 0.;
            pBIn_plunger.theta = acos(((*IonCollection)[i]->GetMom().getZ()) /
                              ((*IonCollection)[i]->GetMom().mag())) /
                         degree; // angle between (0,0,1) and momentum vector                                                                                                       
            pBIn_plunger.phi =
                acos((*IonCollection)[i]->GetMom().getX() /
                     sqrt((*IonCollection)[i]->GetMom().getX() *
                              (*IonCollection)[i]->GetMom().getX() +
                          (*IonCollection)[i]->GetMom().getY() *
                              (*IonCollection)[i]->GetMom().getY())) /
                degree; // angle between (1,0,0) and momentum vector in x and y                                                                                                     
            pBIn_plunger.w = (*IonCollection)[i]->GetWeight();
          }
      } else if ((*IonCollection)[i]->GetFlag() == PLUNGER_TARGET_IN_FLAG) {
        if ((*IonCollection)[i]->GetA() == Ap)
          if ((*IonCollection)[i]->GetZ() == Zp) {
            pTIn_plunger.x = (*IonCollection)[i]->GetPos().getX() / mm;
            pTIn_plunger.y = (*IonCollection)[i]->GetPos().getY() / mm;
            pTIn_plunger.z = (*IonCollection)[i]->GetPos().getZ() / mm;
            pTIn_plunger.px = (*IonCollection)[i]->GetMom().getX() / MeV;
            pTIn_plunger.py = (*IonCollection)[i]->GetMom().getY() / MeV;
            pTIn_plunger.pz = (*IonCollection)[i]->GetMom().getZ() / MeV;
            pTIn_plunger.b = (*IonCollection)[i]->GetBeta();
            pTIn_plunger.E = (*IonCollection)[i]->GetKE() / MeV;
            pTIn_plunger.t = (*IonCollection)[i]->GetTime() / ns;
            pTIn_plunger.tROffset = 0.;
            pTIn_plunger.theta = acos(((*IonCollection)[i]->GetMom().getZ()) /
                              ((*IonCollection)[i]->GetMom().mag())) /
                         degree; // angle between (0,0,1) and momentum vector
            pTIn_plunger.phi =
                acos((*IonCollection)[i]->GetMom().getX() /
                     sqrt((*IonCollection)[i]->GetMom().getX() *
                              (*IonCollection)[i]->GetMom().getX() +
                          (*IonCollection)[i]->GetMom().getY() *
                              (*IonCollection)[i]->GetMom().getY())) /
                degree; // angle between (1,0,0) and momentum vector in x and y
            pTIn_plunger.w = (*IonCollection)[i]->GetWeight();
          }
      }
      else if ((*IonCollection)[i]->GetFlag() == PLUNGER_TARGET_OUT_FLAG) {
        if ((*IonCollection)[i]->GetA() == Ap)
          if ((*IonCollection)[i]->GetZ() == Zp) {
            pTOut_plunger.x = (*IonCollection)[i]->GetPos().getX() / mm;
            pTOut_plunger.y = (*IonCollection)[i]->GetPos().getY() / mm;
            pTOut_plunger.z = (*IonCollection)[i]->GetPos().getZ() / mm;
            pTOut_plunger.px = (*IonCollection)[i]->GetMom().getX() / MeV;
            pTOut_plunger.py = (*IonCollection)[i]->GetMom().getY() / MeV;
            pTOut_plunger.pz = (*IonCollection)[i]->GetMom().getZ() / MeV;
            pTOut_plunger.b = (*IonCollection)[i]->GetBeta();
            pTOut_plunger.E = (*IonCollection)[i]->GetKE() / MeV;
            pTOut_plunger.t = (*IonCollection)[i]->GetTime() / ns;
            pTOut_plunger.tROffset = 0.;
            pTOut_plunger.theta = acos(((*IonCollection)[i]->GetMom().getZ()) /
                              ((*IonCollection)[i]->GetMom().mag())) /
                         degree; // angle between (0,0,1) and momentum vector
            pTOut_plunger.phi =
                acos((*IonCollection)[i]->GetMom().getX() /
                     sqrt((*IonCollection)[i]->GetMom().getX() *
                              (*IonCollection)[i]->GetMom().getX() +
                          (*IonCollection)[i]->GetMom().getY() *
                              (*IonCollection)[i]->GetMom().getY())) /
                degree; // angle between (1,0,0) and momentum vector in x and y
            pTOut_plunger.w = (*IonCollection)[i]->GetWeight();
          }
        if ((*IonCollection)[i]->GetA() == Ar)
          if ((*IonCollection)[i]->GetZ() == Zr) {
            rTOut_plunger.x = (*IonCollection)[i]->GetPos().getX() / mm;
            rTOut_plunger.y = (*IonCollection)[i]->GetPos().getY() / mm;
            rTOut_plunger.z = (*IonCollection)[i]->GetPos().getZ() / mm;
            rTOut_plunger.px = (*IonCollection)[i]->GetMom().getX() / MeV;
            rTOut_plunger.py = (*IonCollection)[i]->GetMom().getY() / MeV;
            rTOut_plunger.pz = (*IonCollection)[i]->GetMom().getZ() / MeV;
            rTOut_plunger.b = (*IonCollection)[i]->GetBeta();
            rTOut_plunger.E = (*IonCollection)[i]->GetKE() / MeV;
            rTOut_plunger.t = (*IonCollection)[i]->GetTime() / ns;
            rTOut_plunger.tROffset = 0.;
            rTOut_plunger.theta = acos(((*IonCollection)[i]->GetMom().getZ()) /
                              ((*IonCollection)[i]->GetMom().mag())) /
                         degree; // angle between (0,0,1) and momentum vector
            rTOut_plunger.phi =
                acos((*IonCollection)[i]->GetMom().getX() /
                     sqrt((*IonCollection)[i]->GetMom().getX() *
                              (*IonCollection)[i]->GetMom().getX() +
                          (*IonCollection)[i]->GetMom().getY() *
                              (*IonCollection)[i]->GetMom().getY())) /
                degree; // angle between (1,0,0) and momentum vector in x and y
            rTOut_plunger.w = (*IonCollection)[i]->GetWeight();
          }
      }
      else if ((*IonCollection)[i]->GetFlag() == PLUNGER_DEGRADER_IN_FLAG) {
        if ((*IonCollection)[i]->GetA() == Ar)
          if ((*IonCollection)[i]->GetZ() == Zr) {
            rDIn_plunger.x = (*IonCollection)[i]->GetPos().getX() / mm;
            rDIn_plunger.y = (*IonCollection)[i]->GetPos().getY() / mm;
            rDIn_plunger.z = (*IonCollection)[i]->GetPos().getZ() / mm;
            rDIn_plunger.px = (*IonCollection)[i]->GetMom().getX() / MeV;
            rDIn_plunger.py = (*IonCollection)[i]->GetMom().getY() / MeV;
            rDIn_plunger.pz = (*IonCollection)[i]->GetMom().getZ() / MeV;
            rDIn_plunger.b = (*IonCollection)[i]->GetBeta();
            rDIn_plunger.E = (*IonCollection)[i]->GetKE() / MeV;
            rDIn_plunger.t = (*IonCollection)[i]->GetTime() / ns;
            rDIn_plunger.tROffset = 0.;
            rDIn_plunger.theta = acos(((*IonCollection)[i]->GetMom().getZ()) /
                               ((*IonCollection)[i]->GetMom().mag())) /
                          degree; // angle between (0,0,1) and momentum vector
            rDIn_plunger.phi =
                acos((*IonCollection)[i]->GetMom().getX() /
                     sqrt((*IonCollection)[i]->GetMom().getX() *
                              (*IonCollection)[i]->GetMom().getX() +
                          (*IonCollection)[i]->GetMom().getY() *
                              (*IonCollection)[i]->GetMom().getY())) /
                degree; // angle between (1,0,0) and momentum vector in x and y
            rDIn_plunger.w = (*IonCollection)[i]->GetWeight();
	    }
        }
      else if ((*IonCollection)[i]->GetFlag() == PLUNGER_DEGRADER_OUT_FLAG) {
	if ((*IonCollection)[i]->GetA() == Ar)
          if ((*IonCollection)[i]->GetZ() == Zr) {
            rDOut_plunger.x = (*IonCollection)[i]->GetPos().getX() / mm;
            rDOut_plunger.y = (*IonCollection)[i]->GetPos().getY() / mm;
            rDOut_plunger.z = (*IonCollection)[i]->GetPos().getZ() / mm;
            rDOut_plunger.px = (*IonCollection)[i]->GetMom().getX() / MeV;
            rDOut_plunger.py = (*IonCollection)[i]->GetMom().getY() / MeV;
            rDOut_plunger.pz = (*IonCollection)[i]->GetMom().getZ() / MeV;
            rDOut_plunger.b = (*IonCollection)[i]->GetBeta();
            rDOut_plunger.E = (*IonCollection)[i]->GetKE() / MeV;
            rDOut_plunger.t = (*IonCollection)[i]->GetTime() / ns;
            rDOut_plunger.tROffset = 0.;
            rDOut_plunger.theta = acos(((*IonCollection)[i]->GetMom().getZ()) /
                               ((*IonCollection)[i]->GetMom().mag())) /
                          degree; // angle between (0,0,1) and momentum vector                                                                                                             
            rDOut_plunger.phi =
                acos((*IonCollection)[i]->GetMom().getX() /
                     sqrt((*IonCollection)[i]->GetMom().getX() *
                              (*IonCollection)[i]->GetMom().getX() +
                          (*IonCollection)[i]->GetMom().getY() *
                              (*IonCollection)[i]->GetMom().getY())) /
                degree; // angle between (1,0,0) and momentum vector in x and y                                                                                                            
            rDOut_plunger.w = (*IonCollection)[i]->GetWeight();
            }
        } else if ((*IonCollection)[i]->GetFlag() == DSAM_TARGET_IN_FLAG) {
          if ((*IonCollection)[i]->GetA() == Ap)
            if ((*IonCollection)[i]->GetZ() == Zp) {
              pTIn_dsam.x = (*IonCollection)[i]->GetPos().getX() / mm;
              pTIn_dsam.y = (*IonCollection)[i]->GetPos().getY() / mm;
              pTIn_dsam.z = (*IonCollection)[i]->GetPos().getZ() / mm;
              pTIn_dsam.px = (*IonCollection)[i]->GetMom().getX() / MeV;
              pTIn_dsam.py = (*IonCollection)[i]->GetMom().getY() / MeV;
              pTIn_dsam.pz = (*IonCollection)[i]->GetMom().getZ() / MeV;
              pTIn_dsam.b = (*IonCollection)[i]->GetBeta();
              pTIn_dsam.E = (*IonCollection)[i]->GetKE() / MeV;
              pTIn_dsam.t = (*IonCollection)[i]->GetTime() / ns;
              pTIn_dsam.tROffset = 0.;
              pTIn_dsam.theta = acos(((*IonCollection)[i]->GetMom().getZ()) /
                                ((*IonCollection)[i]->GetMom().mag())) /
                          degree; // angle between (0,0,1) and momentum vector
              pTIn_dsam.phi =
                  acos((*IonCollection)[i]->GetMom().getX() /
                      sqrt((*IonCollection)[i]->GetMom().getX() *
                                (*IonCollection)[i]->GetMom().getX() +
                            (*IonCollection)[i]->GetMom().getY() *
                                (*IonCollection)[i]->GetMom().getY())) /
                  degree; // angle between (1,0,0) and momentum vector in x and y
              pTIn_dsam.w = (*IonCollection)[i]->GetWeight();
            }
        } else if ((*IonCollection)[i]->GetFlag() == DSAM_BACKING_IN_FLAG) {
          if ((*IonCollection)[i]->GetA() == Ap)
            if ((*IonCollection)[i]->GetZ() == Zp) {
              pBIn_dsam.x = (*IonCollection)[i]->GetPos().getX() / mm;
              pBIn_dsam.y = (*IonCollection)[i]->GetPos().getY() / mm;
              pBIn_dsam.z = (*IonCollection)[i]->GetPos().getZ() / mm;
              pBIn_dsam.px = (*IonCollection)[i]->GetMom().getX() / MeV;
              pBIn_dsam.py = (*IonCollection)[i]->GetMom().getY() / MeV;
              pBIn_dsam.pz = (*IonCollection)[i]->GetMom().getZ() / MeV;
              pBIn_dsam.b = (*IonCollection)[i]->GetBeta();
              pBIn_dsam.E = (*IonCollection)[i]->GetKE() / MeV;
              pBIn_dsam.t = (*IonCollection)[i]->GetTime() / ns;
              pBIn_dsam.tROffset = 0.;
              pBIn_dsam.theta = acos(((*IonCollection)[i]->GetMom().getZ()) /
                                ((*IonCollection)[i]->GetMom().mag())) /
                          degree; // angle between (0,0,1) and momentum vector
              pBIn_dsam.phi =
                  acos((*IonCollection)[i]->GetMom().getX() /
                      sqrt((*IonCollection)[i]->GetMom().getX() *
                                (*IonCollection)[i]->GetMom().getX() +
                            (*IonCollection)[i]->GetMom().getY() *
                                (*IonCollection)[i]->GetMom().getY())) /
                  degree; // angle between (1,0,0) and momentum vector in x and y
              pBIn_dsam.w = (*IonCollection)[i]->GetWeight();
            }
          if ((*IonCollection)[i]->GetA() == Ar)
            if ((*IonCollection)[i]->GetZ() == Zr) {
              rBIn_dsam.x = (*IonCollection)[i]->GetPos().getX() / mm;
              rBIn_dsam.y = (*IonCollection)[i]->GetPos().getY() / mm;
              rBIn_dsam.z = (*IonCollection)[i]->GetPos().getZ() / mm;
              rBIn_dsam.px = (*IonCollection)[i]->GetMom().getX() / MeV;
              rBIn_dsam.py = (*IonCollection)[i]->GetMom().getY() / MeV;
              rBIn_dsam.pz = (*IonCollection)[i]->GetMom().getZ() / MeV;
              rBIn_dsam.b = (*IonCollection)[i]->GetBeta();
              rBIn_dsam.E = (*IonCollection)[i]->GetKE() / MeV;
              rBIn_dsam.t = (*IonCollection)[i]->GetTime() / ns;
              rBIn_dsam.tROffset = 0.;
              rBIn_dsam.theta = acos(((*IonCollection)[i]->GetMom().getZ()) /
                                ((*IonCollection)[i]->GetMom().mag())) /
                          degree; // angle between (0,0,1) and momentum vector
              rBIn_dsam.phi =
                  acos((*IonCollection)[i]->GetMom().getX() /
                      sqrt((*IonCollection)[i]->GetMom().getX() *
                                (*IonCollection)[i]->GetMom().getX() +
                            (*IonCollection)[i]->GetMom().getY() *
                                (*IonCollection)[i]->GetMom().getY())) /
                  degree; // angle between (1,0,0) and momentum vector in x and y
              rBIn_dsam.w = (*IonCollection)[i]->GetWeight();
            }
        } else if ((*IonCollection)[i]->GetFlag() == DSAM_BACKING_OUT_FLAG) {
          if ((*IonCollection)[i]->GetA() == Ar)
            if ((*IonCollection)[i]->GetZ() == Zr) {
              rBOut_dsam.x = (*IonCollection)[i]->GetPos().getX() / mm;
              rBOut_dsam.y = (*IonCollection)[i]->GetPos().getY() / mm;
              rBOut_dsam.z = (*IonCollection)[i]->GetPos().getZ() / mm;
              rBOut_dsam.px = (*IonCollection)[i]->GetMom().getX() / MeV;
              rBOut_dsam.py = (*IonCollection)[i]->GetMom().getY() / MeV;
              rBOut_dsam.pz = (*IonCollection)[i]->GetMom().getZ() / MeV;
              rBOut_dsam.b = (*IonCollection)[i]->GetBeta();
              rBOut_dsam.E = (*IonCollection)[i]->GetKE() / MeV;
              rBOut_dsam.t = (*IonCollection)[i]->GetTime() / ns;
              rBOut_dsam.tROffset = 0.;
              rBOut_dsam.theta = acos(((*IonCollection)[i]->GetMom().getZ()) /
                                ((*IonCollection)[i]->GetMom().mag())) /
                            degree; // angle between (0,0,1) and momentum vector
              rBOut_dsam.phi =
                  acos((*IonCollection)[i]->GetMom().getX() /
                      sqrt((*IonCollection)[i]->GetMom().getX() *
                                (*IonCollection)[i]->GetMom().getX() +
                            (*IonCollection)[i]->GetMom().getY() *
                                (*IonCollection)[i]->GetMom().getY())) /
                  degree; // angle between (1,0,0) and momentum vector in x and y
              rBOut_dsam.w = (*IonCollection)[i]->GetWeight();
            }
        }      
    }
      
    for (Int_t i = 0; i < Nt; i++) {
      if ((*IonCollection)[i]->GetPFlag() == REACTION_IN_FLAG) {
        if ((*IonCollection)[i]->GetA() == Ap)
          if ((*IonCollection)[i]->GetZ() == Zp) {
            pRIn.x = (*IonCollection)[i]->GetPos().getX() / mm;
            pRIn.y = (*IonCollection)[i]->GetPos().getY() / mm;
            pRIn.z = (*IonCollection)[i]->GetPos().getZ() / mm;
            pRIn.px = (*IonCollection)[i]->GetMom().getX() / MeV;
            pRIn.py = (*IonCollection)[i]->GetMom().getY() / MeV;
            pRIn.pz = (*IonCollection)[i]->GetMom().getZ() / MeV;
            pRIn.b = (*IonCollection)[i]->GetBeta();
            pRIn.E = (*IonCollection)[i]->GetKE() / MeV;
            pRIn.t = (*IonCollection)[i]->GetTime() / ns;
            pRIn.tROffset = 0.;
            pRIn.theta = acos(((*IonCollection)[i]->GetMom().getZ()) /
                              ((*IonCollection)[i]->GetMom().mag())) /
                         degree; // angle between (0,0,1) and momentum vector
            pRIn.phi =
                acos((*IonCollection)[i]->GetMom().getX() /
                     sqrt((*IonCollection)[i]->GetMom().getX() *
                              (*IonCollection)[i]->GetMom().getX() +
                          (*IonCollection)[i]->GetMom().getY() *
                              (*IonCollection)[i]->GetMom().getY())) /
                degree; // angle between (1,0,0) and momentum vector in x and y
            pRIn.w = (*IonCollection)[i]->GetWeight();
          }
      } else if ((*IonCollection)[i]->GetPFlag() == REACTION_OUT_FLAG) {
        if ((*IonCollection)[i]->GetA() == Ap)
          if ((*IonCollection)[i]->GetZ() == Zp) {
            pROut.x = (*IonCollection)[i]->GetPos().getX() / mm;
            pROut.y = (*IonCollection)[i]->GetPos().getY() / mm;
            pROut.z = (*IonCollection)[i]->GetPos().getZ() / mm;
            pROut.px = (*IonCollection)[i]->GetMom().getX() / MeV;
            pROut.py = (*IonCollection)[i]->GetMom().getY() / MeV;
            pROut.pz = (*IonCollection)[i]->GetMom().getZ() / MeV;
            pROut.b = (*IonCollection)[i]->GetBeta();
            pROut.E = (*IonCollection)[i]->GetKE() / MeV;
            pROut.t = (*IonCollection)[i]->GetTime() / ns;
            pROut.tROffset = 0.;
            pROut.theta = acos(((*IonCollection)[i]->GetMom().getZ()) /
                               ((*IonCollection)[i]->GetMom().mag())) /
                          degree; // angle between (0,0,1) and momentum vector
            pROut.phi =
                acos((*IonCollection)[i]->GetMom().getX() /
                     sqrt((*IonCollection)[i]->GetMom().getX() *
                              (*IonCollection)[i]->GetMom().getX() +
                          (*IonCollection)[i]->GetMom().getY() *
                              (*IonCollection)[i]->GetMom().getY())) /
                degree; // angle between (1,0,0) and momentum vector in x and y
            pROut.w = (*IonCollection)[i]->GetWeight();
          }
        // recoil nucleus tracking
        if ((*IonCollection)[i]->GetA() == Ar)
          if ((*IonCollection)[i]->GetZ() == Zr) {
            rROut.x = (*IonCollection)[i]->GetPos().getX() / mm;
            rROut.y = (*IonCollection)[i]->GetPos().getY() / mm;
            rROut.z = (*IonCollection)[i]->GetPos().getZ() / mm;
            rROut.px = (*IonCollection)[i]->GetMom().getX() / MeV;
            rROut.py = (*IonCollection)[i]->GetMom().getY() / MeV;
            rROut.pz = (*IonCollection)[i]->GetMom().getZ() / MeV;
            rROut.b = (*IonCollection)[i]->GetBeta();
            rROut.E = (*IonCollection)[i]->GetKE() / MeV;
            rROut.t = (*IonCollection)[i]->GetTime() / ns;
            rROut.tROffset = 0.;
            rROut.theta = acos(((*IonCollection)[i]->GetMom().getZ()) /
                               ((*IonCollection)[i]->GetMom().mag())) /
                          degree; // angle between (0,0,1) and momentum vector
            rROut.phi =
                acos((*IonCollection)[i]->GetMom().getX() /
                     sqrt((*IonCollection)[i]->GetMom().getX() *
                              (*IonCollection)[i]->GetMom().getX() +
                          (*IonCollection)[i]->GetMom().getY() *
                              (*IonCollection)[i]->GetMom().getY())) /
                degree; // angle between (1,0,0) and momentum vector in x and y
            rROut.w = (*IonCollection)[i]->GetWeight();
          }
      } else if (((*IonCollection)[i]->GetPFlag() >= DECAY_FLAG) && ((*IonCollection)[i]->GetPFlag() < TARGET_LAYER_IN_FLAG)) {
        G4int flag = (*IonCollection)[i]->GetPFlag();
        if (((*IonCollection)[i]->GetA() == Ar) || ((*IonCollection)[i]->GetA() == Ap))
          if (((*IonCollection)[i]->GetZ() == Zr) || ((*IonCollection)[i]->GetZ() == Zp)) {
            rDec[flag - DECAY_FLAG].x =
                (*IonCollection)[i]->GetPos().getX() / mm;
            rDec[flag - DECAY_FLAG].y =
                (*IonCollection)[i]->GetPos().getY() / mm;
            rDec[flag - DECAY_FLAG].z =
                (*IonCollection)[i]->GetPos().getZ() / mm;
            rDec[flag - DECAY_FLAG].px =
                (*IonCollection)[i]->GetMom().getX() / MeV;
            rDec[flag - DECAY_FLAG].py =
                (*IonCollection)[i]->GetMom().getY() / MeV;
            rDec[flag - DECAY_FLAG].pz =
                (*IonCollection)[i]->GetMom().getZ() / MeV;
            rDec[flag - DECAY_FLAG].b = (*IonCollection)[i]->GetBeta();
            rDec[flag - DECAY_FLAG].A = (*IonCollection)[i]->GetA();
            rDec[flag - DECAY_FLAG].Z = (*IonCollection)[i]->GetZ();
            rDec[flag - DECAY_FLAG].E = (*IonCollection)[i]->GetKE() / MeV;
            rDec[flag - DECAY_FLAG].t = (*IonCollection)[i]->GetTime() / ns;
            rDec[flag - DECAY_FLAG].tROffset =
                rDec[flag - DECAY_FLAG].t - pRIn.t;
            rDec[flag - DECAY_FLAG].theta =
                acos(((*IonCollection)[i]->GetMom().getZ()) /
                     ((*IonCollection)[i]->GetMom().mag())) /
                degree; // angle between (0,0,1) and momentum vector
            rDec[flag - DECAY_FLAG].phi =
                acos((*IonCollection)[i]->GetMom().getX() /
                     sqrt((*IonCollection)[i]->GetMom().getX() *
                              (*IonCollection)[i]->GetMom().getX() +
                          (*IonCollection)[i]->GetMom().getY() *
                              (*IonCollection)[i]->GetMom().getY())) /
                degree; // angle between (1,0,0) and momentum vector in x and y
            rDec[flag - DECAY_FLAG].w = (*IonCollection)[i]->GetWeight();
          }
      } else if (((*IonCollection)[i]->GetFlag() >= TARGET_LAYER_IN_FLAG) && ((*IonCollection)[i]->GetFlag() < TARGET_LAYER_OUT_FLAG)) {
        G4int flag = (*IonCollection)[i]->GetFlag();
        if (((*IonCollection)[i]->GetZ() == Zp) && ((*IonCollection)[i]->GetA() == Ap)) {
          pTIn_target[flag - TARGET_LAYER_IN_FLAG].x =
              (*IonCollection)[i]->GetPos().getX() / mm;
          pTIn_target[flag - TARGET_LAYER_IN_FLAG].y =
              (*IonCollection)[i]->GetPos().getY() / mm;
          pTIn_target[flag - TARGET_LAYER_IN_FLAG].z =
              (*IonCollection)[i]->GetPos().getZ() / mm;
          pTIn_target[flag - TARGET_LAYER_IN_FLAG].px =
              (*IonCollection)[i]->GetMom().getX() / MeV;
          pTIn_target[flag - TARGET_LAYER_IN_FLAG].py =
              (*IonCollection)[i]->GetMom().getY() / MeV;
          pTIn_target[flag - TARGET_LAYER_IN_FLAG].pz =
              (*IonCollection)[i]->GetMom().getZ() / MeV;
          pTIn_target[flag - TARGET_LAYER_IN_FLAG].b = (*IonCollection)[i]->GetBeta();
          pTIn_target[flag - TARGET_LAYER_IN_FLAG].E = (*IonCollection)[i]->GetKE() / MeV;
          pTIn_target[flag - TARGET_LAYER_IN_FLAG].t = (*IonCollection)[i]->GetTime() / ns;
          pTIn_target[flag - TARGET_LAYER_IN_FLAG].tROffset =
              pTIn_target[flag - TARGET_LAYER_IN_FLAG].t - pRIn.t;
          pTIn_target[flag - TARGET_LAYER_IN_FLAG].theta =
              acos(((*IonCollection)[i]->GetMom().getZ()) /
                    ((*IonCollection)[i]->GetMom().mag())) /
              degree; // angle between (0,0,1) and momentum vector
          pTIn_target[flag - TARGET_LAYER_IN_FLAG].phi =
              acos((*IonCollection)[i]->GetMom().getX() /
                    sqrt((*IonCollection)[i]->GetMom().getX() *
                            (*IonCollection)[i]->GetMom().getX() +
                        (*IonCollection)[i]->GetMom().getY() *
                            (*IonCollection)[i]->GetMom().getY())) /
              degree; // angle between (1,0,0) and momentum vector in x and y
          pTIn_target[flag - TARGET_LAYER_IN_FLAG].w = (*IonCollection)[i]->GetWeight();
        } else if (((*IonCollection)[i]->GetZ() == Zr) && ((*IonCollection)[i]->GetA() == Ar)) {
          rTIn_target[flag - TARGET_LAYER_IN_FLAG].x =
              (*IonCollection)[i]->GetPos().getX() / mm;
          rTIn_target[flag - TARGET_LAYER_IN_FLAG].y =
              (*IonCollection)[i]->GetPos().getY() / mm;
          rTIn_target[flag - TARGET_LAYER_IN_FLAG].z =
              (*IonCollection)[i]->GetPos().getZ() / mm;
          rTIn_target[flag - TARGET_LAYER_IN_FLAG].px =
              (*IonCollection)[i]->GetMom().getX() / MeV;
          rTIn_target[flag - TARGET_LAYER_IN_FLAG].py =
              (*IonCollection)[i]->GetMom().getY() / MeV;
          rTIn_target[flag - TARGET_LAYER_IN_FLAG].pz =
              (*IonCollection)[i]->GetMom().getZ() / MeV;
          rTIn_target[flag - TARGET_LAYER_IN_FLAG].b = (*IonCollection)[i]->GetBeta();
          rTIn_target[flag - TARGET_LAYER_IN_FLAG].E = (*IonCollection)[i]->GetKE() / MeV;
          rTIn_target[flag - TARGET_LAYER_IN_FLAG].t = (*IonCollection)[i]->GetTime() / ns;
          rTIn_target[flag - TARGET_LAYER_IN_FLAG].tROffset =
              rTIn_target[flag - TARGET_LAYER_IN_FLAG].t - pRIn.t;
          rTIn_target[flag - TARGET_LAYER_IN_FLAG].theta =
              acos(((*IonCollection)[i]->GetMom().getZ()) /
                    ((*IonCollection)[i]->GetMom().mag())) /
              degree; // angle between (0,0,1) and momentum vector
          rTIn_target[flag - TARGET_LAYER_IN_FLAG].phi =
              acos((*IonCollection)[i]->GetMom().getX() /
                    sqrt((*IonCollection)[i]->GetMom().getX() *
                            (*IonCollection)[i]->GetMom().getX() +
                        (*IonCollection)[i]->GetMom().getY() *
                            (*IonCollection)[i]->GetMom().getY())) /
              degree; // angle between (1,0,0) and momentum vector in x and y
          rTIn_target[flag - TARGET_LAYER_IN_FLAG].w = (*IonCollection)[i]->GetWeight();
        }
      } else if ((*IonCollection)[i]->GetFlag() >= TARGET_LAYER_OUT_FLAG) {
        G4int flag = (*IonCollection)[i]->GetFlag();
        if (((*IonCollection)[i]->GetZ() == Zp) && ((*IonCollection)[i]->GetA() == Ap)) {
          pTOut_target[flag - TARGET_LAYER_OUT_FLAG].x =
              (*IonCollection)[i]->GetPos().getX() / mm;
          pTOut_target[flag - TARGET_LAYER_OUT_FLAG].y =
              (*IonCollection)[i]->GetPos().getY() / mm;
          pTOut_target[flag - TARGET_LAYER_OUT_FLAG].z =
              (*IonCollection)[i]->GetPos().getZ() / mm;
          pTOut_target[flag - TARGET_LAYER_OUT_FLAG].px =
              (*IonCollection)[i]->GetMom().getX() / MeV;
          pTOut_target[flag - TARGET_LAYER_OUT_FLAG].py =
              (*IonCollection)[i]->GetMom().getY() / MeV;
          pTOut_target[flag - TARGET_LAYER_OUT_FLAG].pz =
              (*IonCollection)[i]->GetMom().getZ() / MeV;
          pTOut_target[flag - TARGET_LAYER_OUT_FLAG].b = (*IonCollection)[i]->GetBeta();
          pTOut_target[flag - TARGET_LAYER_OUT_FLAG].E = (*IonCollection)[i]->GetKE() / MeV;
          pTOut_target[flag - TARGET_LAYER_OUT_FLAG].t = (*IonCollection)[i]->GetTime() / ns;
          pTOut_target[flag - TARGET_LAYER_OUT_FLAG].tROffset =
              pTOut_target[flag - TARGET_LAYER_OUT_FLAG].t - pRIn.t;
          pTOut_target[flag - TARGET_LAYER_OUT_FLAG].theta =
              acos(((*IonCollection)[i]->GetMom().getZ()) /
                    ((*IonCollection)[i]->GetMom().mag())) /
              degree; // angle between (0,0,1) and momentum vector
          pTOut_target[flag - TARGET_LAYER_OUT_FLAG].phi =
              acos((*IonCollection)[i]->GetMom().getX() /
                    sqrt((*IonCollection)[i]->GetMom().getX() *
                            (*IonCollection)[i]->GetMom().getX() +
                        (*IonCollection)[i]->GetMom().getY() *
                            (*IonCollection)[i]->GetMom().getY())) /
              degree; // angle between (1,0,0) and momentum vector in x and y
          pTOut_target[flag - TARGET_LAYER_OUT_FLAG].w = (*IonCollection)[i]->GetWeight();
        } else if (((*IonCollection)[i]->GetZ() == Zr) && ((*IonCollection)[i]->GetA() == Ar)) {
          rTOut_target[flag - TARGET_LAYER_OUT_FLAG].x =
              (*IonCollection)[i]->GetPos().getX() / mm;
          rTOut_target[flag - TARGET_LAYER_OUT_FLAG].y =
              (*IonCollection)[i]->GetPos().getY() / mm;
          rTOut_target[flag - TARGET_LAYER_OUT_FLAG].z =
              (*IonCollection)[i]->GetPos().getZ() / mm;
          rTOut_target[flag - TARGET_LAYER_OUT_FLAG].px =
              (*IonCollection)[i]->GetMom().getX() / MeV;
          rTOut_target[flag - TARGET_LAYER_OUT_FLAG].py =
              (*IonCollection)[i]->GetMom().getY() / MeV;
          rTOut_target[flag - TARGET_LAYER_OUT_FLAG].pz =
              (*IonCollection)[i]->GetMom().getZ() / MeV;
          rTOut_target[flag - TARGET_LAYER_OUT_FLAG].b = (*IonCollection)[i]->GetBeta();
          rTOut_target[flag - TARGET_LAYER_OUT_FLAG].E = (*IonCollection)[i]->GetKE() / MeV;
          rTOut_target[flag - TARGET_LAYER_OUT_FLAG].t = (*IonCollection)[i]->GetTime() / ns;
          rTOut_target[flag - TARGET_LAYER_OUT_FLAG].tROffset =
              rTOut_target[flag - TARGET_LAYER_OUT_FLAG].t - pRIn.t;
          rTOut_target[flag - TARGET_LAYER_OUT_FLAG].theta =
              acos(((*IonCollection)[i]->GetMom().getZ()) /
                    ((*IonCollection)[i]->GetMom().mag())) /
              degree; // angle between (0,0,1) and momentum vector
          rTOut_target[flag - TARGET_LAYER_OUT_FLAG].phi =
              acos((*IonCollection)[i]->GetMom().getX() /
                    sqrt((*IonCollection)[i]->GetMom().getX() *
                            (*IonCollection)[i]->GetMom().getX() +
                        (*IonCollection)[i]->GetMom().getY() *
                            (*IonCollection)[i]->GetMom().getY())) /
              degree; // angle between (1,0,0) and momentum vector in x and y
          rTOut_target[flag - TARGET_LAYER_OUT_FLAG].w = (*IonCollection)[i]->GetWeight();
        }
      }
    }
  } // end of ion collection entry saving

  // record time offsets with respect to the reaction
  gun.tROffset = gun.t - pRIn.t;
  pBIn_plunger.tROffset = pBIn_plunger.t - pRIn.t;
  pTIn_plunger.tROffset = pTIn_plunger.t - pRIn.t;
  rTOut_plunger.tROffset = rTOut_plunger.t - pRIn.t;
  rDIn_plunger.tROffset = rDIn_plunger.t-pRIn.t;
  rDOut_plunger.tROffset = rDOut_plunger.t-pRIn.t;
  pTIn_dsam.tROffset = pTIn_dsam.t-pRIn.t;
  rBIn_dsam.tROffset = rBIn_dsam.t-pRIn.t;
  rBOut_dsam.tROffset = rBOut_dsam.t-pRIn.t;
  rROut.tROffset = rROut.t - pRIn.t;
  partROut.tROffset = partROut.t - pRIn.t;
  if (gun.tROffset < 0.)
    gun.tROffset = 0.;
  if (pBIn_plunger.tROffset < 0.)
    pBIn_plunger.tROffset = 0.;
   if (pTIn_plunger.tROffset < 0.)
    pTIn_plunger.tROffset = 0.;
  if (rTOut_plunger.tROffset < 0.)
    rTOut_plunger.tROffset = 0.;
  if (rDIn_plunger.tROffset < 0.)
    rDIn_plunger.tROffset = 0.;
  if (rDOut_plunger.tROffset < 0.)
    rDOut_plunger.tROffset = 0.;
  if (pTIn_dsam.tROffset < 0.)
    pTIn_dsam.tROffset = 0.;
  if (rBIn_dsam.tROffset < 0.)
    rBIn_dsam.tROffset = 0.;
  if (rBOut_dsam.tROffset < 0.)
    rBOut_dsam.tROffset = 0.;
  if (partROut.tROffset < 0.)
    partROut.tROffset = 0.;

  partHit.CsIfold = 0;
  memset(&partHit.x, 0, sizeof(partHit.x));
  memset(&partHit.y, 0, sizeof(partHit.y));
  memset(&partHit.z, 0, sizeof(partHit.z));
  memset(&partHit.px, 0, sizeof(partHit.px));
  memset(&partHit.pz, 0, sizeof(partHit.pz));
  memset(&partHit.b, 0, sizeof(partHit.b));
  memset(&partHit.E, 0, sizeof(partHit.E));
  memset(&partHit.dE, 0, sizeof(partHit.dE));
  memset(&partHit.w, 0, sizeof(partHit.w));
  memset(&partHit.A, 0, sizeof(partHit.A));
  memset(&partHit.Z, 0, sizeof(partHit.Z));
  memset(&partHit.Id, 0, sizeof(partHit.Id));
  memset(&partHit.r, 0, sizeof(partHit.r));
  memset(&partHit.path, 0, sizeof(partHit.path));
  memset(&partHit.dEdx, 0, sizeof(partHit.dEdx));
  memset(&partHit.dLdx, 0, sizeof(partHit.dLdx));
  memset(&partHit.LY, 0, sizeof(partHit.LY));

  G4int i, j, k;
  if (Np > 0) {
    for (j = 1; j < NCsISph + 1; j++) // loop through CsI detector IDs (1 indexed)
    {
      if ((j < NCsI + 1) || (theDetector->GetAncArrayType()==1)) // check whether index is valid for wall/ball
        if ((CsITrigId == 0) ||
            (CsITrigId == j)) // save only data for the detectors we want to see
          for (i = 0; i < Np; i++) // loop through all entries in the collection
          {
            if ((*CsICollection)[i]->GetDisabled() == 0) // don't save any
                                                         // entries which have
                                                         // been disabled due to
                                                         // trigger conditions
              if ((*CsICollection)[i]->GetId() == j)     // check whether entry
              // belongs to the detector
              // we are looking at
              {
                if ((partHit.E[partHit.CsIfold] == 0.) &&
                    ((*CsICollection)[i]->GetKE() > 0.)) // first entry for a
                                                         // given detector with
                                                         // nonzero energy
                {
                  partHit.x[partHit.CsIfold] =
                      (*CsICollection)[i]->GetPos().getX() / mm;
                  partHit.y[partHit.CsIfold] =
                      (*CsICollection)[i]->GetPos().getY() / mm;
                  partHit.z[partHit.CsIfold] =
                      (*CsICollection)[i]->GetPos().getZ() / mm;
                  partHit.px[partHit.CsIfold] =
                      (*CsICollection)[i]->GetMom().getX() / MeV;
                  partHit.py[partHit.CsIfold] =
                      (*CsICollection)[i]->GetMom().getY() / MeV;
                  partHit.pz[partHit.CsIfold] =
                      (*CsICollection)[i]->GetMom().getZ() / MeV;
                  partHit.b[partHit.CsIfold] = (*CsICollection)[i]->GetBeta();
                  partHit.E[partHit.CsIfold] =
                      (*CsICollection)[i]->GetKE() / MeV;
                  partHit.dE[partHit.CsIfold] =
                      (*CsICollection)[i]->GetKE() / MeV;
                  partHit.w[partHit.CsIfold] = (*CsICollection)[i]->GetWeight();
                  partHit.A[partHit.CsIfold] = (*CsICollection)[i]->GetA();
                  partHit.Z[partHit.CsIfold] = (*CsICollection)[i]->GetZ();
                  partHit.Id[partHit.CsIfold] = (*CsICollection)[i]->GetId();
                  partHit.r[partHit.CsIfold] = (*CsICollection)[i]->GetRingId();
                  // partHit.path=(*CsICollection)[i]->GetPathLength()/um; // in
                  // microns
                  // partHit.dEdx=((*CsICollection)[i]->GetKE()/MeV)/((*CsICollection)[i]->GetPathLength()/um);
                  partHit.path[partHit.CsIfold] =
                      ((*CsICollection)[i]->GetPathLength() / cm) * CsIDensity *
                      1000; // in mg/cm^2
                  partHit.dEdx[partHit.CsIfold] =
                      ((*CsICollection)[i]->GetKE() / MeV) /
                      (((*CsICollection)[i]->GetPathLength() / cm) *
                       CsIDensity * 1000);
                  partHit.dLdx[partHit.CsIfold] = CalculateBirksLawStep(
                      partHit.Id[partHit.CsIfold], partHit.dE[partHit.CsIfold],
                      partHit.dEdx[partHit.CsIfold]); // make sure to check
                                                      // units of kB!
                  partHit.LY[partHit.CsIfold] = partHit.dLdx[partHit.CsIfold];
                  // G4cout<<"CsI ID in tree: "<<partHit.Id<<G4endl;
                  // printf("particle: dE %9.3f path %9.3f  dE/dx %9.3f  dL
                  // %9.3f  LY
                  // %9.3f\n",partHit.E,partHit.path,partHit.dEdx,partHit.dLdx,partHit.LY);
                } else if ((*CsICollection)[i]->GetKE() > 0.) // later entries
                                                              // for a given
                                                              // detector with
                                                              // nonzero energy
                {
                  partHit.E[partHit.CsIfold] +=
                      (*CsICollection)[i]->GetKE() / MeV;
                  partHit.dE[partHit.CsIfold] =
                      (*CsICollection)[i]->GetKE() / MeV;
                  // partHit.path+=(*CsICollection)[i]->GetPathLength()/um; //
                  // in microns
                  // partHit.dEdx=((*CsICollection)[i]->GetKE()/MeV)/((*CsICollection)[i]->GetPathLength()/um);
                  partHit.path[partHit.CsIfold] +=
                      ((*CsICollection)[i]->GetPathLength() / cm) * CsIDensity *
                      1000; // in mg/cm^2
                  partHit.dEdx[partHit.CsIfold] =
                      ((*CsICollection)[i]->GetKE() / MeV) /
                      (((*CsICollection)[i]->GetPathLength() / cm) *
                       CsIDensity * 1000);
                  partHit.dLdx[partHit.CsIfold] = CalculateBirksLawStep(
                      partHit.Id[partHit.CsIfold], partHit.dE[partHit.CsIfold],
                      partHit.dEdx[partHit.CsIfold]); // make sure to check
                                                      // units of kB!
                  partHit.LY[partHit.CsIfold] += partHit.dLdx[partHit.CsIfold];
                  // printf("particle: dE %9.3f path %9.3f  dE/dx %9.3f  dL
                  // %9.3f  LY
                  // %9.3f\n",partHit.dE,partHit.path,partHit.dEdx,partHit.dLdx,partHit.LY);
                }
              }
            // getc(stdin);
          }
      if (partHit.E[partHit.CsIfold] > 0.)
        partHit.CsIfold++; // increase fold if energy in a given detector is
                           // greater than 0
    }
  } // end of CsI collection entry saving

  //TIGRESS/GRIFFIN event tracking
  GHit.Gfold = 0;
  GHit.GfoldAB = 0;
  memset(maxGe, 0, sizeof(maxGe));
  memset(&GHit.GId, 0, sizeof(GHit.GId));
  memset(&GHit.GCry, 0, sizeof(GHit.GCry));
  memset(&GHit.GE, 0, sizeof(GHit.GE));
  memset(&GHit.GT, 0, sizeof(GHit.GT));
  memset(&GHit.GIdAB, 0, sizeof(GHit.GIdAB));
  memset(&GHit.GCryAB, 0, sizeof(GHit.GCryAB));
  memset(&GHit.GRingAB, 0, sizeof(GHit.GRingAB));
  memset(&GHit.GEAB, 0, sizeof(GHit.GEAB));
  memset(&GHit.GxAB, 0, sizeof(GHit.GxAB));
  memset(&GHit.GyAB, 0, sizeof(GHit.GyAB));
  memset(&GHit.GzAB, 0, sizeof(GHit.GzAB));
  // non-addback
  for (i = 0; i < GN; i++)   // number of positions
    for (j = 0; j < GS; j++) // number of crystals
      if (gw[i][j] > 0) {
        // G4cout<<" i "<<i<<" j "<<j<<" w "<<gw[i][j]<<G4endl;
        GHit.GId[GHit.Gfold] = i + 1;
        GHit.GCry[GHit.Gfold] = j;
        GHit.GRing[GHit.Gfold] = RingMap(
            GHit.GId[GHit.Gfold],
            GHit.GCry[GHit.Gfold]); // get the ring in which the hit occured
        GHit.Gx[GHit.Gfold] = gp[i][j].getX();
        GHit.Gy[GHit.Gfold] = gp[i][j].getY();
        GHit.Gz[GHit.Gfold] = gp[i][j].getZ();
        GHit.GE[GHit.Gfold] = ge[i][j];
        GHit.GW[GHit.Gfold] = gw[i][j];
        GHit.GT[GHit.Gfold] = gt[i][j];
        GHit.Gfold++;
      }

  // addback
  for (i = 0; i < GN; i++)   // number of positions
    for (j = 0; j < GS; j++) // number of crystals
      if (ge[i][j] > maxGe[i]) {
        // assign position, ring, etc. of the addback hit
        GHit.GIdAB[GHit.GfoldAB] = i + 1;
        GHit.GCryAB[GHit.GfoldAB] = j;
        GHit.GRingAB[GHit.GfoldAB] = RingMap(
            GHit.GIdAB[GHit.GfoldAB],
            GHit.GCryAB[GHit.GfoldAB]); // get the ring in which the hit occured
        GHit.GxAB[GHit.GfoldAB] = gp[i][j].getX();
        GHit.GyAB[GHit.GfoldAB] = gp[i][j].getY();
        GHit.GzAB[GHit.GfoldAB] = gp[i][j].getZ();
        if (maxGe[i] ==
            0.) // no energy deposit in this detector prior to this hit
          GHit.GfoldAB++;
        maxGe[i] = ge[i][j];
      }

  // addback energy: sum deposits over all crystals in the detector with the
  // highest energy deposit
  for (i = 0; i < GHit.GfoldAB; i++) // number of addback events
    for (j = 0; j < GS; j++)         // number of crystals
      if (ge[(GHit.GIdAB[i]) - 1][j] > 0)
        GHit.GEAB[i] += ge[(GHit.GIdAB[i]) - 1][j];

  //TIGRESS segment event tracking
  if(theDetector->GetUseTIGRESSSegments()){
    G4int maxESeg;
    G4double segMaxE = 0.;
    SegHit.segfold = 0;
    memset(&SegHit.segId, 0, sizeof(SegHit.segId));
    memset(&SegHit.segNumHits, 0, sizeof(SegHit.segNumHits));
    memset(&SegHit.segx, 0, sizeof(SegHit.segx));
    memset(&SegHit.segy, 0, sizeof(SegHit.segy));
    memset(&SegHit.segz, 0, sizeof(SegHit.segz));
    memset(&SegHit.segCylr, 0, sizeof(SegHit.segCylr));
    memset(&SegHit.segCylrFrac, 0, sizeof(SegHit.segCylrFrac));
    memset(&SegHit.segCylphi, 0, sizeof(SegHit.segCylphi));
    memset(&SegHit.segCylz, 0, sizeof(SegHit.segCylz));
    memset(&SegHit.segE, 0, sizeof(SegHit.segE));
    memset(&SegHit.segw, 0, sizeof(SegHit.segw));
    SegHit.maxESegfold = 0;
    memset(&SegHit.maxESegId, 0, sizeof(SegHit.maxESegId));
    memset(&SegHit.maxESegNumHits, 0, sizeof(SegHit.maxESegNumHits));
    memset(&SegHit.maxESegCylr, 0, sizeof(SegHit.maxESegCylr));
    memset(&SegHit.maxESegCylrFrac, 0, sizeof(SegHit.maxESegCylrFrac));
    memset(&SegHit.maxESegCylphi, 0, sizeof(SegHit.maxESegCylphi));
    memset(&SegHit.maxESegCylz, 0, sizeof(SegHit.maxESegCylz));
    memset(&SegHit.maxESegE, 0, sizeof(SegHit.maxESegE));
    for (i = 0; i < GN; i++)   // number of positions
      for (j = 0; j < GS; j++) { // number of crystals
        maxESeg = -1;
        for (k = 0; k < TSEG; k++) { // number of segments
          if(tsw[i][j][k]>0){
            SegHit.segId[SegHit.segfold] = k+1;
            SegHit.segNumHits[SegHit.segfold] = tsh[i][j][k];
            SegHit.segx[SegHit.segfold] = tsp[i][j][k].getX();
            SegHit.segy[SegHit.segfold] = tsp[i][j][k].getY();
            SegHit.segz[SegHit.segfold] = tsp[i][j][k].getZ();
            SegHit.segCylr[SegHit.segfold] = tscp[i][j][k].getX();
            SegHit.segCylphi[SegHit.segfold] = tscp[i][j][k].getY();
            SegHit.segCylz[SegHit.segfold] = tscp[i][j][k].getZ();
            SegHit.segCylrFrac[SegHit.segfold] = SegHit.segCylr[SegHit.segfold]/theDetector->GetTIGRESSGermaniumRadius(k,SegHit.segCylz[SegHit.segfold],SegHit.segCylphi[SegHit.segfold]);
            SegHit.segE[SegHit.segfold] = tse[i][j][k];
            if(SegHit.segE[SegHit.segfold] > segMaxE){
              segMaxE = SegHit.segE[SegHit.segfold];
              maxESeg = k;
            }
            SegHit.segw[SegHit.segfold] = tsw[i][j][k];
            SegHit.segfold++;
          }
        }
        if(maxESeg >= 0){
          SegHit.maxESegId[SegHit.maxESegfold] = maxESeg+1;
          SegHit.maxESegNumHits[SegHit.maxESegfold] = tsh[i][j][maxESeg];
          SegHit.maxESegCylr[SegHit.maxESegfold] = tscp[i][j][maxESeg].getX();
          SegHit.maxESegCylphi[SegHit.maxESegfold] = tscp[i][j][maxESeg].getY();
          SegHit.maxESegCylz[SegHit.maxESegfold] = tscp[i][j][maxESeg].getZ();
          SegHit.maxESegCylrFrac[SegHit.maxESegfold] = SegHit.maxESegCylr[SegHit.maxESegfold]/theDetector->GetTIGRESSGermaniumRadius(maxESeg,SegHit.maxESegCylz[SegHit.maxESegfold],SegHit.maxESegCylphi[SegHit.maxESegfold]);
          SegHit.maxESegE[SegHit.maxESegfold] = tse[i][j][maxESeg];
          SegHit.maxESegfold++;
        }
      }     
  }

  // compute an approximate Doppler shift based on the specific detectors where
  // gamma and evaporated particles were seen
  Double_t beta; // speed of recoil (calculated)
  eStat.dsfold = 0;
  for (i = 0; i < GHit.GfoldAB; i++) // number of addback hits in the event
  {
    G4ThreeVector gammaVec = theDetector->GetDetectorCrystalPosition(
        GHit.GIdAB[eStat.dsfold] - 1, GHit.GCryAB[eStat.dsfold]);
    if (gammaVec.mag() != 0)
      gammaVec.setMag(1.0);
    // G4cout << "gammaVec: " << gammaVec << G4endl;
    G4ThreeVector resMom, partMom, partDir;
    resMom.setX(gun.px);
    resMom.setY(gun.py);
    resMom.setZ(gun.pz);
    // get recoil momentum by subtracting evaporated particle momenta from
    // beam momentum
    for (j = 0; j < partHit.CsIfold; j++) {
      partMom.setX(partHit.px[j]);
      partMom.setY(partHit.py[j]);
      partMom.setZ(partHit.pz[j]);
      partDir = PP[partHit.Id[j] - 1]; // get direction to CsI detector
      partDir.setMag(
          partMom.mag()); // turn direction vector into momentum vector
      resMom -= partDir;
    }
    eStat.calcERes[eStat.dsfold] = resMom * resMom / (2. * 931.45 * Ar);
    // Print debug
    /*G4cout<<"recoil momentum (calc), hit #"<<i+1<<": "<<resMom;
    G4cout<<", magnitude:"<<resMom.mag()<<G4endl;
    G4cout<<"Energy (calc): "<<resE/MeV<<", (sim): "<<rROut.E/MeV<<G4endl;*/
    beta = resMom.mag() / (931.45 * Ar);
    // G4cout<<"recoil beta (calc): "<<beta<<", (sim): "<<rROut.b<<G4endl;
    if (resMom.mag() != 0)
      resMom.setMag(1.0);

    eStat.ds[eStat.dsfold] =
        sqrt(1 - beta * beta) / (1 - beta * resMom * gammaVec);
    eStat.dsfold++;
  }
  // printf("Gun beta: %10.10f\nReaction out beta: %10.10f\n",gun.b,rROut.b);
  // printf("Gun momentum: [%10.10f %10.10f %10.10f]\n",gun.px,gun.py,gun.pz);
  // getc(stdin);
  tree->Fill();
}
//=====================================================================================
G4int Results::RingMap(G4int id, G4int seg) {
  G4int r, s;
  s = -1;
  if (seg == 0)
    s = 0;
  if (seg == 1)
    s = 1;
  if (seg == 2)
    s = 1;
  if (seg == 3)
    s = 0;
  if (s < 0)
    return -1;

  r = -1;
  switch (id) {
  case 1:
    r = 1;
    break;
  case 2:
    r = 1;
    break;
  case 3:
    r = 1;
    break;
  case 4:
    r = 1;
    break;
  case 5:
    r = 3;
    break;
  case 6:
    r = 3;
    break;
  case 7:
    r = 3;
    break;
  case 8:
    r = 3;
    break;
  case 9:
    r = 3;
    break;
  case 10:
    r = 3;
    break;
  case 11:
    r = 3;
    break;
  case 12:
    r = 3;
    break;
  case 13:
    r = 5;
    break;
  case 14:
    r = 5;
    break;
  case 15:
    r = 5;
    break;
  case 16:
    r = 5;
    break;
  default:
    break;
  }
  if (r < 0)
    return -1;

  return r + s;
}
//=====================================================================================
void Results::ReportCrystalPositions() {
  Double_t xx, yy, zz, rr, cc;
  printf("det cry ring     x        y        z        r       cos\n");
  for (Int_t det = 0; det < GN; det++)
    for (Int_t cry = 0; cry < GS; cry++) {
      xx = CP[det][cry].getX();
      yy = CP[det][cry].getY();
      zz = CP[det][cry].getZ();
      rr = sqrt(xx * xx + yy * yy + zz * zz);
      cc = zz / rr;
      printf(" %2d  %2d  %3d %8.3f %8.3f %8.3f %8.3f %8.3f\n", det + 1, cry,
             RingMap(det + 1, cry), xx, yy, zz, rr, cc);
    }
}
//=====================================================================================
void Results::GetCsIWallPositions() {
  Double_t xx, yy, zz;
  for (Int_t det = 0; det < NCsI; det++) {
    xx = theDetector->GetCsIWall()->GetXPos(det + 1);
    yy = theDetector->GetCsIWall()->GetYPos(det + 1);
    zz = theDetector->GetCsIWall()->GetZPos();
    PP[det].setX(xx);
    PP[det].setY(yy);
    PP[det].setZ(zz);
  }
}
//=====================================================================================
void Results::GetCsIBallPositions() {
  Double_t xx, yy, zz;
  for (Int_t det = 0; det < NCsISph; det++) {
    xx = theDetector->GetCsIBall()->GetXPos(det + 1);
    yy = theDetector->GetCsIBall()->GetYPos(det + 1);
    zz = theDetector->GetCsIBall()->GetZPos();
    PP[det].setX(xx);
    PP[det].setY(yy);
    PP[det].setZ(zz);
  }
}
//=====================================================================================
void Results::ReportCsIWallPositions() {
  Double_t xx, yy, zz, rr, cc;
  printf("pin      x        y        z        r       cos \n");
  for (Int_t det = 0; det < NCsI; det++) {
    xx = PP[det].getX();
    yy = PP[det].getY();
    zz = PP[det].getZ();
    rr = sqrt(xx * xx + yy * yy + zz * zz);
    cc = zz / rr;
    printf(" %2d  %8.3f %8.3f %8.3f %8.3f %8.3f\n", det + 1, xx, yy, zz, rr,
           cc);
  }
}
//=====================================================================================
void Results::GroupCosDist() {

  Int_t pin, det, cry;
  Double_t cos;

  c = (TCanvas *)gROOT->FindObject("StdCanv");
  if (c != NULL)
    c->Close();

  c = new TCanvas("StdCanv", "StdCanv", 700, 500);
  c->Clear();
  c->cd();

  h = (TH1D *)gROOT->FindObject("GroupCos");
  if (h == NULL)
    h = new TH1D("GroupCos", "GroupCos", 1000, 0.0, 1.0);
  h->Reset();

  for (pin = 0; pin < NCsI; pin++)
    for (det = 0; det < GN; det++)
      for (cry = 0; cry < GS; cry++) {
        cos = PP[pin].dot(CP[det][cry]) / PP[pin].mag() / CP[det][cry].mag();
        h->Fill(cos);
      }

  h->GetXaxis()->SetTitle("cos(theta)");
  h->GetYaxis()->SetTitle("Counts");
  h->SetLineColor(kRed);
  h->Draw();
}

//=====================================================================================
G4double Results::CalculatePath(G4ThreeVector iPos, G4ThreeVector Pos) {
  G4double xd, yd, zd;
  G4double dist;

  xd = Pos.getX() - iPos.getX();
  yd = Pos.getY() - iPos.getY();
  zd = Pos.getZ() - iPos.getZ();

  dist = sqrt(xd * xd + yd * yd + zd * zd);

  return dist;
}
//=====================================================================================
G4double Results::CalculateBirksLawStep(G4int id, G4double dE, G4double dEdx) {
  // G4double S=1.0; // absolute scinitallation yeild for CsI (can take from
  // arXiv 1502:03800v1 for low E heavy ions).
  G4double dL; // differential light yield

  //   printf("Birks constant for position %2d is %6.3f um/MeV %6.3f
  //   (mg/cm^2)/MeV\n",id,kB[id-1],kBm[id-1]);
  // getc(stdin);

  // dL = S*dE/(1+kB[id-1]*dEdx); // for dE in MeV/um
  dL = S[id - 1] * dE / (1 + kBm[id - 1] * dEdx); // for dE in MeV/(mg/cm^2)

  return dL;
}
