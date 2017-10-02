
#include "TrackerPINSD.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerPINSD::TrackerPINSD(G4String name)
:G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname="PINCollection");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerPINSD::~TrackerPINSD(){ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerPINSD::Initialize(G4HCofThisEvent*)
{


  PINCollection = new TrackerPINHitsCollection
                          (SensitiveDetectorName,collectionName[0]); 
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool TrackerPINSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{

  G4double DE = aStep->GetPreStepPoint()->GetKineticEnergy() - aStep->GetPostStepPoint()->GetKineticEnergy();
  if(DE<0.001*eV) return false;

  G4Track* theTrack;
  theTrack=aStep->GetTrack();
  const G4DynamicParticle* aParticle= theTrack->GetDynamicParticle();
  const G4String type =  aParticle->GetDefinition()->GetParticleType();
  const G4double len=aStep->GetStepLength();

  if(type=="nucleus")
    {
    
      char name[132],s1[10],s2[10],s3[10];
      strcpy(name,aStep->GetPostStepPoint()->GetTouchable()->GetVolume()->GetName()); 
      sscanf(name,"%s %s %s",s1,s2,s3);

      G4StepPoint*   vi;
      G4StepPoint*   vf;

      vi=aStep->GetPreStepPoint(); 
      vf=aStep->GetPostStepPoint(); 
      if(strcmp(s1,"PIN")==0)
	{
	  if(len>0.)
	    {
	      TrackerPINHit* newHitI = new TrackerPINHit();
	      
	      newHitI->SetBeta(vi->GetBeta());
	      newHitI->SetKE(aStep->GetTotalEnergyDeposit());
	      newHitI->SetPos(vi->GetPosition());
	      newHitI->SetMom(vi->GetMomentum());
	      newHitI->SetA(aParticle->GetParticleDefinition()->GetAtomicMass());
	      newHitI->SetZ(aParticle->GetParticleDefinition()->GetAtomicNumber());
	      newHitI->SetWeight(aStep->GetTrack()->GetWeight());
	      newHitI->SetId(atoi(s2));
	      newHitI->SetRingId(atoi(s3));
	      PINCollection->insert( newHitI );
	      newHitI->Draw();
	    }
	  G4TrackStatus TrackStatus;
	  TrackStatus=aStep->GetTrack()->GetTrackStatus();
	  if(TrackStatus==fStopButAlive||TrackStatus==fStopAndKill)
	    {
	      TrackerPINHit* newHitF = new TrackerPINHit();
	      newHitF->SetBeta(vf->GetBeta());
	      newHitF->SetKE(vf->GetKineticEnergy());
	      newHitF->SetMom(vf->GetMomentum());
	      newHitF->SetPos(vf->GetPosition());
	      newHitF->SetA(aParticle->GetParticleDefinition()->GetAtomicMass());
	      newHitF->SetZ(aParticle->GetParticleDefinition()->GetAtomicNumber());
	      newHitF->SetWeight(aStep->GetTrack()->GetWeight());
	      newHitF->SetId(atoi(s2));
	      newHitF->SetRingId(atoi(s3));
	      PINCollection->insert( newHitF );
	      newHitF->Draw();
	    }
	    // newHit->Print(); 
	    // getc(stdin);
	    return true;
	}
      else
	{
	  //    G4cout << "Energy deposit in the " << name << G4endl;
	  //    G4cout << "E="<<G4BestUnit(edep,"Energy")<<G4endl;
	  //    G4cout <<"Event ignored" <<G4endl;
	  //	    getc(stdin);
	  return false;
	}
    }
  return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerPINSD::EndOfEvent(G4HCofThisEvent* HCE)
{
   G4int i;
   G4int NbHits = PINCollection->entries();

        if (NbHits>0) 
	  if (false) 
	   { 
	    
	   G4cout << "\n-------->Hits Collection: in this event they are " << NbHits 
            << " hits for PIN tracking: " << G4endl;
	   for (i=0;i<NbHits;i++) (*PINCollection)[i]->Print();
	   //	   	    getc(stdin);
	   }


  static G4int HCID = -1;
  if(HCID<0)
  { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }
  HCE->AddHitsCollection( HCID, PINCollection ); 
 }


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

