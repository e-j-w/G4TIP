
#include "TrackerCsISD.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerCsISD::TrackerCsISD(G4String name)
:G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname="CsICollection");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerCsISD::~TrackerCsISD(){ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerCsISD::Initialize(G4HCofThisEvent*)
{


  CsICollection = new TrackerCsIHitsCollection
                          (SensitiveDetectorName,collectionName[0]); 
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool TrackerCsISD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
  G4double DE = - aStep->GetDeltaEnergy();
  if(DE<0.001*eV) return false;

  G4Track* theTrack=new G4Track();
  theTrack=aStep->GetTrack();
  const G4DynamicParticle* aParticle= theTrack->GetDynamicParticle();
  const G4String type =  aParticle->GetDefinition()->GetParticleType();
  const G4double len=aStep->GetStepLength();
  //G4cout << "Type: " << type << G4endl; //right now, always seems to be gamma or lepton

  //if(type=="nucleus")
  if((type=="nucleus")||(type=="baryon")) //some evaporated particles classified as baryons by GEANT4 
    {
      char name[132],s1[10],s2[10],s3[10];
      strcpy(name,aStep->GetPostStepPoint()->GetTouchable()->GetVolume()->GetName()); 
      sscanf(name,"%s %s %s",s1,s2,s3);

      G4StepPoint*   vi=new G4StepPoint();
      G4StepPoint*   vf=new G4StepPoint();

      vi=aStep->GetPreStepPoint(); 
      vf=aStep->GetPostStepPoint(); 
      if(strcmp(s1,"CsI")==0)
	{
	  if(len>0.)
	    {
	      TrackerCsIHit* newHitI = new TrackerCsIHit();
	      
	      newHitI->SetBeta(vi->GetBeta());
	      newHitI->SetKE(aStep->GetTotalEnergyDeposit());
	      newHitI->SetPos(vi->GetPosition());
	      newHitI->SetMom(vi->GetMomentum());
	      newHitI->SetA(aParticle->GetParticleDefinition()->GetAtomicMass());
	      newHitI->SetZ(aParticle->GetParticleDefinition()->GetAtomicNumber());
	      newHitI->SetWeight(aStep->GetTrack()->GetWeight());
	      newHitI->SetId(atoi(s2));
	      newHitI->SetRingId(atoi(s3));
	      CsICollection->insert( newHitI );
	      newHitI->Draw();
	      // printf("newHitI\n");
	      // newHitI->Print(); 
	      // getc(stdin);
	    }
	  G4TrackStatus TrackStatus;
	  TrackStatus=aStep->GetTrack()->GetTrackStatus();
	  if((TrackStatus==fStopButAlive) || (TrackStatus==fStopAndKill))
	    {
	      TrackerCsIHit* newHitF = new TrackerCsIHit();
	      newHitF->SetBeta(vf->GetBeta());
	      newHitF->SetKE(vf->GetKineticEnergy());
	      newHitF->SetMom(vf->GetMomentum());
	      newHitF->SetPos(vf->GetPosition());
	      newHitF->SetA(aParticle->GetParticleDefinition()->GetAtomicMass());
	      newHitF->SetZ(aParticle->GetParticleDefinition()->GetAtomicNumber());
	      newHitF->SetWeight(aStep->GetTrack()->GetWeight());
	      newHitF->SetId(atoi(s2));
	      newHitF->SetRingId(atoi(s3));
	      CsICollection->insert( newHitF );
	      newHitF->Draw();
	      // printf("newHitF\n");
	      // newHitF->Print(); 
	      // getc(stdin);
	    }

	    return true;
	}
      else
	{
	      //G4cout << "Energy deposit in the " << name << G4endl;
	      //G4cout << "E="<<G4BestUnit(edep,"Energy")<<G4endl;
	      //G4cout <<"Event ignored" <<G4endl;
	      //getc(stdin);
	  return false;
	}
    }
  return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerCsISD::EndOfEvent(G4HCofThisEvent* HCE)
{
   G4int i;
   G4int NbHits = CsICollection->entries();

        if (NbHits>0) 
	  if (false) 
	   { 
	   
	   G4cout << "\n-------->Hits Collection: in this event they are " << NbHits 
            << " hits for CsI tracking: " << G4endl;
	   for (i=0;i<NbHits;i++) (*CsICollection)[i]->Print();
	   //	   	    getc(stdin);
	   }


  static G4int HCID = -1;
  if(HCID<0)
  { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }
  HCE->AddHitsCollection( HCID, CsICollection ); 
 }


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

