#include "TrackerIonSD.hh"

//--------------------------------------------------------------------
TrackerIonSD::TrackerIonSD(G4String name)
  :G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname="ionCollection");

  print=false;
}

//--------------------------------------------------------------------

  TrackerIonSD::~TrackerIonSD()
{ 
  
}

//--------------------------------------------------------------------

void TrackerIonSD::Initialize(G4HCofThisEvent*)
{ 
 

    ionCollection = new TrackerIonHitsCollection
                          (SensitiveDetectorName,collectionName[0]);  
  
}
//--------------------------------------------------------------------


G4bool TrackerIonSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{

  G4Track* theTrack=new G4Track();
  theTrack=aStep->GetTrack();

  
 G4StepPoint*   vi;
 G4StepPoint*   vf;

 const G4DynamicParticle* aParticle= theTrack->GetDynamicParticle();
 const G4String type =  aParticle->GetDefinition()->GetParticleType();
 const G4double len=aStep->GetStepLength();

 G4String pName;
 if (theTrack->GetCreatorProcess()!=NULL)
    pName=theTrack->GetCreatorProcess()->GetProcessName();
  else
    pName="Unknown";


  if(type=="nucleus")
   {     

     vi=aStep->GetPreStepPoint(); 
     vf=aStep->GetPostStepPoint();   
     G4String vname=vi->GetPhysicalVolume()->GetName();
     if(len>0.)
	 {
	   TrackerIonHit* newIonHitI= new TrackerIonHit();         
	   
	   if(pName=="Reaction")
	    if(vi->GetLocalTime()==0.)
	      {
		newIonHitI->SetReactionOutFlag();
	      }
	   
	   newIonHitI->SetVolName(vname);
	   newIonHitI->SetBeta(vi->GetBeta());
	   newIonHitI->SetKE(vi->GetKineticEnergy());
	   newIonHitI->SetPos(vi->GetPosition());
	   newIonHitI->SetMom(vi->GetMomentum());
	   newIonHitI->SetA(aParticle->GetParticleDefinition()->GetAtomicMass());
	   newIonHitI->SetZ(aParticle->GetParticleDefinition()->GetAtomicNumber());
	   newIonHitI->SetWeight(aStep->GetTrack()->GetWeight());
	   newIonHitI->Draw();
	   ionCollection->insert(newIonHitI);
	 }

     G4TrackStatus TrackStatus;
     TrackStatus=aStep->GetTrack()->GetTrackStatus();
     if(TrackStatus==fStopButAlive||TrackStatus==fStopAndKill)
       {
	 TrackerIonHit* newIonHitF= new TrackerIonHit();   	
	 
         if(vf->GetProcessDefinedStep()->GetProcessName()=="Decay")
	   newIonHitF->SetDecayFlag();
         if(vf->GetProcessDefinedStep()->GetProcessName()=="Reaction")
	   newIonHitF->SetReactionInFlag();
	 newIonHitF->SetVolName(vname);
	 newIonHitF->SetBeta(vf->GetBeta());
	 newIonHitF->SetKE(vf->GetKineticEnergy());
	 newIonHitF->SetMom(vf->GetMomentum());
	 newIonHitF->SetPos(vf->GetPosition());
	 newIonHitF->SetA(aParticle->GetParticleDefinition()->GetAtomicMass());
	 newIonHitF->SetZ(aParticle->GetParticleDefinition()->GetAtomicNumber());
	 newIonHitF->SetWeight(aStep->GetTrack()->GetWeight());
	 newIonHitF->Draw();
	 ionCollection->insert(newIonHitF);
       }

   
   }

 
  
  return true;
}
//--------------------------------------------------------------------

void TrackerIonSD::EndOfEvent(G4HCofThisEvent* HCE)
{
 
 
  G4int i;
  G4int NbHits = ionCollection->entries();  

  if(NbHits>0)
    {
 
      (*ionCollection)[0]->SetGunFlag();

       for (i=0;i<NbHits-1;i++) 
	 {
	   if ((*ionCollection)[i]->GetA()==(*ionCollection)[i+1]->GetA())
	     if ((*ionCollection)[i]->GetZ()==(*ionCollection)[i+1]->GetZ())
	       if ((*ionCollection)[i]->GetVolName()=="expHall"&&(*ionCollection)[i+1]->GetVolName()=="target")
		 (*ionCollection)[i+1]->SetTargetInFlag();

	   if ((*ionCollection)[i]->GetA()==(*ionCollection)[i+1]->GetA())
	     if ((*ionCollection)[i]->GetZ()==(*ionCollection)[i+1]->GetZ())
	       if ((*ionCollection)[i]->GetVolName()=="target"&&(*ionCollection)[i+1]->GetVolName()=="backing")
		 (*ionCollection)[i+1]->SetBackingInFlag();
	 }

	

       for (i=1;i<NbHits;i++) 
	 {
	   
	   if ((*ionCollection)[i-1]->GetA()==(*ionCollection)[i]->GetA())
	     if ((*ionCollection)[i-1]->GetZ()==(*ionCollection)[i]->GetZ())
	       if ((*ionCollection)[i-1]->GetVolName()=="backing"&&(*ionCollection)[i]->GetVolName()=="expHall")
		 (*ionCollection)[i]->SetBackingOutFlag();

	 }

     if (print) 
     {	
       G4cout<<G4endl;
           G4cout << "-------->Hits Collection: in this event there are " << NbHits
            << " hits for ion tracking: " << G4endl;

      G4cout << " F  A  Z  KE/MeV   beta" <<" "
	     << std::setw(9)<<std::fixed
	     <<std::setprecision(4)<<std::right	 
	     <<" X/mm " <<" "<<std::setw(9)<<std::right
	     <<" Y/mm "<<" "<<std::setw(9)<<std::right
	     <<" Z/mm "<<" "<<std::setw(8)<<std::right
	     <<"px/MeV" <<" "<<std::setw(9)<<std::right
	     <<"py/MeV"<<" "<<std::setw(9)<<std::right
	     <<"pz/MeV"<<" "<<std::setw(8)<<std::right
	     <<"weight"<< G4endl;

           for (i=0;i<NbHits;i++) (*ionCollection)[i]->Print();
	   
     }

    }  
 
 static G4int HCID = -1;
  if(HCID<0)
  { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }
  HCE->AddHitsCollection( HCID, ionCollection ); 
 }


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

