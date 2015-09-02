#include "Results.hh"

Results::Results(Projectile* proj):theProjectile(proj)
{
  h=NULL;
  g=NULL;  
  c=NULL;
  TreeCreate();  
  IonFill=0;
  soi=sizeof(gun);
  sos=sizeof(stat);
  memset(CP,0,sizeof(CP));

  F=1.25;
  G=2.00;
  H=0.00;

  A=0.0;
  B=1.0;
  C=0;
}

Results::~Results()
{
tree->Delete();
}
//---------------------------------------------------------
void Results::SetupRun(G4int DA, G4int DZ)
{
  Ap=theProjectile->getA();
  Zp=theProjectile->getZ();

  Ar=Ap+DA;
  Zr=Zp+DZ;
  
}
//---------------------------------------------------------
void Results::TreeCreate()
{
 if(tree==NULL)
    {
      tree= new TTree("tree","tree");
      tree->Branch("Gfold",&Gfold,"Gfold/I");
      tree->Branch("GId",GId,"GId[Gfold]/I");
      tree->Branch("GSeg",GSeg,"GSeg[Gfold]/I");
      tree->Branch("Gx",Gx,"Gx[Gfold]/D");
      tree->Branch("Gy",Gy,"Gy[Gfold]/D");
      tree->Branch("Gz",Gz,"Gz[Gfold]/D");
      tree->Branch("GE",GE,"GE[Gfold]/D");
      tree->Branch("GW",GW,"GW[Gfold]/D");
      tree->Branch("stat",&stat,"evNb/I:Ap/I:Zp/I");

      tree->Branch("projGun",&gun,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:w/D");
      tree->Branch("projTargetIn",&pTIn,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:w/D");
      tree->Branch("projReactionIn",&pRIn,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:w/D");
        
      tree->Branch("recReactionOut",&rROut,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:w/D");
      tree->Branch("recBackingIn",&rBIn,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:w/D");
      tree->Branch("recBackingOut",&rBOut,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:w/D");
      tree->Branch("recDec",&rDec,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:w/D");
   }

}
//---------------------------------------------------------
void Results::TreeClear()
{
  tree->Delete("all");
  tree=NULL;
  TreeCreate();
}
//---------------------------------------------------------
void Results::TreeReport()
{
  tree->Print(); 
}
//---------------------------------------------------------
void Results::TreeView()
{
  gStyle->SetPalette(1);
  tree->StartViewer(); 
}
//---------------------------------------------------------
void Results::TreeSave(G4String name)
{
  TDirectory *dir=new TDirectory();
  dir=gDirectory;
  TFile f(name,"recreate");
  f.cd();
  tree->AutoSave();
  tree->SetDirectory(dir);
  f.Close();
  dir->cd();
  G4cout<<"Tree of simulated parameters saved in file "<<name<<G4endl;
  
}
//---------------------------------------------------------
void Results::TreeRead(G4String)
{
 
}

//---------------------------------------------------------
void Results::TreeAdd(G4String )
{

 

}
//---------------------------------------------------------
void Results::FillTree(G4int evtNb, TrackerIonHitsCollection* IonCollection,TrackerPINHitsCollection* PINCollection,G4double gw[GN][GS],G4double ge[GN][GS],G4ThreeVector gp[GN][GS])
{


 
 G4int Nt=IonCollection->entries();

 memset(&stat,0,sos); 
 memset(&gun,0,soi);
 memset(&pTIn,0,soi);
 memset(&pRIn,0,soi);
 memset(&rROut,0,soi);
 memset(&rBIn,0,soi);
 memset(&rBOut,0,soi);
 memset(&rDec,0,soi);
 if(Nt>0) 
   {
      
     stat.evNb=evtNb;
     stat.Ap=Ap;
     stat.Zp=Zp;
 
     for(Int_t i=0;i<Nt;i++)
       switch((*IonCollection)[i]->GetFlag())
	 {
	 case GUN_FLAG:
	   if((*IonCollection)[i]->GetA()==Ap)
	     if((*IonCollection)[i]->GetZ()==Zp)
	       {
		 gun.x=(*IonCollection)[i]->GetPos().getX()/mm;
		 gun.y=(*IonCollection)[i]->GetPos().getY()/mm;
		 gun.z=(*IonCollection)[i]->GetPos().getZ()/mm;
		 gun.px=(*IonCollection)[i]->GetMom().getX()/MeV;
		 gun.py=(*IonCollection)[i]->GetMom().getY()/MeV;
		 gun.pz=(*IonCollection)[i]->GetMom().getZ()/MeV;
		 gun.b=(*IonCollection)[i]->GetBeta();
		 gun.E=(*IonCollection)[i]->GetKE()/MeV;		 
		 gun.w=(*IonCollection)[i]->GetWeight();

	       }
	   break;

	 case TARGET_IN_FLAG:
	   if((*IonCollection)[i]->GetA()==Ap)
	     if((*IonCollection)[i]->GetZ()==Zp)
	       {
		 pTIn.x=(*IonCollection)[i]->GetPos().getX()/mm;
		 pTIn.y=(*IonCollection)[i]->GetPos().getY()/mm;
		 pTIn.z=(*IonCollection)[i]->GetPos().getZ()/mm;
		 pTIn.px=(*IonCollection)[i]->GetMom().getX()/MeV;
		 pTIn.py=(*IonCollection)[i]->GetMom().getY()/MeV;
		 pTIn.pz=(*IonCollection)[i]->GetMom().getZ()/MeV;
		 pTIn.b=(*IonCollection)[i]->GetBeta();
		 pTIn.E=(*IonCollection)[i]->GetKE()/MeV;		 
		 pTIn.w=(*IonCollection)[i]->GetWeight();
	       }
	   break;
	 case BACKING_IN_FLAG:
	   if((*IonCollection)[i]->GetA()==Ar)
	     if((*IonCollection)[i]->GetZ()==Zr)
	       {
		 rBIn.x=(*IonCollection)[i]->GetPos().getX()/mm;
		 rBIn.y=(*IonCollection)[i]->GetPos().getY()/mm;
		 rBIn.z=(*IonCollection)[i]->GetPos().getZ()/mm;
		 rBIn.px=(*IonCollection)[i]->GetMom().getX()/MeV;
		 rBIn.py=(*IonCollection)[i]->GetMom().getY()/MeV;
		 rBIn.pz=(*IonCollection)[i]->GetMom().getZ()/MeV;
		 rBIn.b=(*IonCollection)[i]->GetBeta();
		 rBIn.E=(*IonCollection)[i]->GetKE()/MeV;		 
		 rBIn.w=(*IonCollection)[i]->GetWeight();
	       }
	   break;
	 case BACKING_OUT_FLAG:
	   if((*IonCollection)[i]->GetA()==Ar)
	     if((*IonCollection)[i]->GetZ()==Zr)
	       {
		 rBOut.x=(*IonCollection)[i]->GetPos().getX()/mm;
		 rBOut.y=(*IonCollection)[i]->GetPos().getY()/mm;
		 rBOut.z=(*IonCollection)[i]->GetPos().getZ()/mm;
		 rBOut.px=(*IonCollection)[i]->GetMom().getX()/MeV;
		 rBOut.py=(*IonCollection)[i]->GetMom().getY()/MeV;
		 rBOut.pz=(*IonCollection)[i]->GetMom().getZ()/MeV;
		 rBOut.b=(*IonCollection)[i]->GetBeta();
		 rBOut.E=(*IonCollection)[i]->GetKE()/MeV;		 
		 rBOut.w=(*IonCollection)[i]->GetWeight();
	       }
	   break;

	 default:
	   break;
	 }

    for(Int_t i=0;i<Nt;i++)
       switch((*IonCollection)[i]->GetPFlag())
	 {
	 case REACTION_IN_FLAG:
	   if((*IonCollection)[i]->GetA()==Ap)
	     if((*IonCollection)[i]->GetZ()==Zp)
	       {
		 pRIn.x=(*IonCollection)[i]->GetPos().getX()/mm;
		 pRIn.y=(*IonCollection)[i]->GetPos().getY()/mm;
		 pRIn.z=(*IonCollection)[i]->GetPos().getZ()/mm;
		 pRIn.px=(*IonCollection)[i]->GetMom().getX()/MeV;
		 pRIn.py=(*IonCollection)[i]->GetMom().getY()/MeV;
		 pRIn.pz=(*IonCollection)[i]->GetMom().getZ()/MeV;
		 pRIn.b=(*IonCollection)[i]->GetBeta();
		 pRIn.E=(*IonCollection)[i]->GetKE()/MeV;		 
		 pRIn.w=(*IonCollection)[i]->GetWeight();
	       }
	   break;
	 case REACTION_OUT_FLAG:
	   if((*IonCollection)[i]->GetA()==Ar)
	     if((*IonCollection)[i]->GetZ()==Zr)
	       {
		 rROut.x=(*IonCollection)[i]->GetPos().getX()/mm;
		 rROut.y=(*IonCollection)[i]->GetPos().getY()/mm;
		 rROut.z=(*IonCollection)[i]->GetPos().getZ()/mm;
		 rROut.px=(*IonCollection)[i]->GetMom().getX()/MeV;
		 rROut.py=(*IonCollection)[i]->GetMom().getY()/MeV;
		 rROut.pz=(*IonCollection)[i]->GetMom().getZ()/MeV;
		 rROut.b=(*IonCollection)[i]->GetBeta();
		 rROut.E=(*IonCollection)[i]->GetKE()/MeV;		 
		 rROut.w=(*IonCollection)[i]->GetWeight();
	       }
	   break;
	 case DECAY_FLAG:	   
	   if((*IonCollection)[i]->GetA()==Ar)
	     if((*IonCollection)[i]->GetZ()==Zr)
	       {
		 rDec.x=(*IonCollection)[i]->GetPos().getX()/mm;
		 rDec.y=(*IonCollection)[i]->GetPos().getY()/mm;
		 rDec.z=(*IonCollection)[i]->GetPos().getZ()/mm;
		 rDec.px=(*IonCollection)[i]->GetMom().getX()/MeV;
		 rDec.py=(*IonCollection)[i]->GetMom().getY()/MeV;
		 rDec.pz=(*IonCollection)[i]->GetMom().getZ()/MeV;
		 rDec.b=(*IonCollection)[i]->GetBeta();
		 rDec.E=(*IonCollection)[i]->GetKE()/MeV;		 
		 rDec.w=(*IonCollection)[i]->GetWeight();
	       }
	   break;

	 default:
	   break;
	 }
   }       
   
 
     G4int i,j;
     Gfold=0;
     memset(GId,0,sizeof(GId));
     memset(GSeg,0,sizeof(GSeg));
     memset(GE,0,sizeof(GE));
     for(i=0;i<GN;i++)
       for(j=0;j<GS;j++)
	 if(gw[i][j]>0)
	   {
	     GId[Gfold]=i+1;
	     GSeg[Gfold]=j;
	     Gx[Gfold]=gp[i][j].getX();
	     Gy[Gfold]=gp[i][j].getY();
	     Gz[Gfold]=gp[i][j].getZ();
	     GE[Gfold]=ge[i][j];
	     GW[Gfold]=gw[i][j];
	     Gfold++;
	   }
     

   
     tree->Fill();
     
     IonFill++;
    
 
}

//=====================================================================================
G4int Results::RingMap(G4int id,G4int seg)
 {
   G4int r,s;
   s=-1;
   if(seg==0) s=0;
   if(seg==1) s=1;
   if(seg==2) s=1;
   if(seg==3) s=0;
   if(s<0) return -1;

   r=-1;
   switch (id)
     {
     case  1:r=1;break;
     case  2:r=1;break;
     case  3:r=1;break;
     case  4:r=1;break;
     case  5:r=3;break;
     case  6:r=3;break;
     case  7:r=3;break;
     case  8:r=3;break;
     case  9:r=3;break;
     case 10:r=3;break;
     case 11:r=3;break;
     case 12:r=3;break;
     case 13:r=5;break;
     case 14:r=5;break;
     case 15:r=5;break;
     case 16:r=5;break;
     default:break;
     }
   if(r<0) return -1;

   return r+s;
 }

//=====================================================================================
void Results::GammaRingSpectrum(G4int ring)
 {
 
   G4double ene;

   c=(TCanvas *)gROOT->FindObject("StdCanv");
   if(c!=NULL)
     c->Close();

   c=new TCanvas("StdCanv","StdCanv",700,500);
   c->Clear();
   c->cd();
 
   h=(TH1D *)gROOT->FindObject("Gamma");
   if(h==NULL)
     h=new TH1D("Gamma","Gamma",4096,0,4096);
   h->Reset();

   g=(TH1D *)gROOT->FindObject("Gamma W");
   if(g==NULL)
     g=new TH1D("Gamma W","Gamma W",4096,0,4096);
   g->Reset();

   Int_t N=tree->GetEntries();
  
   for(Int_t i=0;i<N;i++)
     {
       tree->GetEntry(i);
       for(Int_t j=0;j<Gfold;j++)
	 if(RingMap(GId[j],GSeg[j])==ring)
	   {
	     ene=FWHM_response(GE[j]);
	     h->Fill(ene);     
	     g->Fill(ene,GW[j]);
	   }
     }
	   
   h->GetXaxis()->SetTitle("Energy [keV]");
   h->GetYaxis()->SetTitle("Counts");
   h->SetLineColor(kBlue);
   h->Draw();
   g->SetLineColor(kRed);
   g->Draw("same");

 }

//=====================================================================================
void Results::CalculateCrystalPositions()
 {
   Double_t x[GN][GS],y[GN][GS],z[GN][GS],n[GN][GS];
   Double_t xx,yy,zz;
   size_t sod=GN*4*sizeof(Double_t);
   memset(x,0,sod);
   memset(y,0,sod);
   memset(z,0,sod);
   memset(n,0,sod);
   Int_t N=tree->GetEntries();
  
   for(Int_t i=0;i<N;i++)
     {
       tree->GetEntry(i);
       for(Int_t j=0;j<Gfold;j++)
	 {
	   x[GId[j]-1][GSeg[j]]+=Gx[j];
	   y[GId[j]-1][GSeg[j]]+=Gy[j];
	   z[GId[j]-1][GSeg[j]]+=Gz[j];
	   n[GId[j]-1][GSeg[j]]++;
	 }
     }

   for(Int_t det=0;det<GN;det++)
     for(Int_t cry=0;cry<GS;cry++)
       {
	 xx=x[det][cry]/n[det][cry];
	 yy=y[det][cry]/n[det][cry];
	 zz=z[det][cry]/n[det][cry];
	 CP[det][cry].setX(xx);
	 CP[det][cry].setY(yy);
	 CP[det][cry].setZ(zz);
       }
   ReportCrystalPositions();
 }
//=====================================================================================
void Results::ReportCrystalPositions()
 {
   Double_t xx,yy,zz,rr,cc;
   printf("det cry ring     x        y        z        r       cos\n");
   for(Int_t det=0;det<GN;det++)
     for(Int_t cry=0;cry<GS;cry++)
       {
	 xx=CP[det][cry].getX();
	 yy=CP[det][cry].getY();
	 zz=CP[det][cry].getZ();
	 rr=sqrt(xx*xx+yy*yy+zz*zz);
	 cc=zz/rr;
	 printf(" %2d  %2d  %3d %8.3f %8.3f %8.3f %8.3f %8.3f\n",det+1,cry,RingMap(det+1,cry),xx,yy,zz,rr,cc);
       }
       
 } 

//---------------------------------------------------------------------
G4double Results::FWHM_response(G4double e)
{
  G4double e_out,fwhm,sigma,ex,channel;
  ex=e/1000.;
  fwhm=sqrt(F+G*ex+H*ex*ex);
  sigma=fwhm/2.35482;
 
  if(sigma>0)
    e_out=CLHEP::RandGauss::shoot(e,sigma);
  else
    e_out=e;

  channel=A+B*e_out+C*e_out*e_out;
  return channel;
}
