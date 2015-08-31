#include "EventAction.hh"

 
EventAction::EventAction(Results* RE,RunAction* RA): results(RE),run_action(RA)
{ 

  ionCollectionID=-1;
  PINCollectionID=-1;
  soa=16*4*sizeof(G4double);
  sov=16*4*sizeof(G4ThreeVector);
  SetTriggerGammaPinCoinc();
}


EventAction::~EventAction()
{
  ;
}

void EventAction::BeginOfEventAction(const G4Event*)
{
 
  G4SDManager * SDman = G4SDManager::GetSDMpointer();

  if(ionCollectionID<0)
    ionCollectionID=SDman->GetCollectionID("ionCollection");

  if(PINCollectionID<0)
    PINCollectionID=SDman->GetCollectionID("PINCollection");
 
  memset(GriffinCrystEnergyDet,0,soa);
  memset(GriffinCrystWeightDet,0,soa);
  memset(GriffinCrystPosDet,0,sov);
  GriffinFold=0;
  // G4cout<<"+++++ Begin of event "<<evt->GetEventID()<<G4endl;

}


 
void EventAction::EndOfEventAction(const G4Event* evt)
{
  // G4cout<<"+++++ End of event "<<evt->GetEventID()<<G4endl;

  G4int evtNb=evt->GetEventID();

  if (evtNb%1000 == 0) 
    {
      gettimeofday(&tc,NULL);
      ts=run_action->GetStartTime();
      timersub(&tc,&ts,&td);
      t=td.tv_sec;
      rate=(float)evtNb/t;
      G4cout<<" Number of processed events "<<std::setw(9)<<evtNb<<" in "<<std::setw(9)<<t<<" sec. at "<<std::fixed<<std::setw(9)<<std::setprecision(2)<<rate<<" events per second\r"<<std::flush;

  }

  eventTrigger=0;

  G4HCofThisEvent * HCE = evt->GetHCofThisEvent();
  TrackerPINHitsCollection* PIN=new TrackerPINHitsCollection();
  TrackerIonHitsCollection* HI=new TrackerIonHitsCollection();
  G4int Np;

  if(HCE!=NULL) {    
    PIN=(TrackerPINHitsCollection*) HCE->GetHC(PINCollectionID); 
    Np=PIN->entries();
    if(Np>0) 
      eventTrigger|=2;  
    HI=(TrackerIonHitsCollection*)(HCE->GetHC(ionCollectionID));
  }


  if(GriffinFold>0)
       eventTrigger|=1;


  //  if((eventTrigger&setTrigger)==setTrigger)
      {
	if(GriffinFold>0)
	  for(G4int det=0;det<16;det++)
	    for(G4int cry=0;cry<4;cry++)
	      if( GriffinCrystEnergyDet[det][cry]>0)
		GriffinCrystPosDet[det][cry]/=GriffinCrystEnergyDet[det][cry];

	results->FillTree(evtNb,HI,PIN,GriffinCrystWeightDet,GriffinCrystEnergyDet,GriffinCrystPosDet);
      }
  
}
//*********************************************************************//
void EventAction::AddGriffinCrystDet(G4double de, G4double w, G4ThreeVector pos, G4int det, G4int cry) 
{
  if(GriffinCrystWeightDet[det][cry]==0.)
    {
      GriffinCrystWeightDet[det][cry]=w;
      GriffinCrystEnergyDet[det][cry]= de;
      GriffinCrystPosDet[det][cry]= de*pos;
      GriffinFold++;
      return;
    }

  if(GriffinCrystWeightDet[det][cry]==w)
    {
      GriffinCrystEnergyDet[det][cry]+=de;
      GriffinCrystPosDet[det][cry]+= de*pos;
    }
  else
    {
      G4cout<<G4endl;
      G4cout<<" Bad weight: detector "<<det<<" crystal "<<cry<<" weight "<<w<<" old weight "<<GriffinCrystWeightDet[det][cry]<<G4endl;
      G4cout<<" Terminating execution "<<G4endl;
      G4cout<<" Find the reason, make a fix "<<G4endl;
      G4cout<<" Resist a temptation to patch or swipe under a carpet "<<G4endl;
      G4cout<<" May the force be with you, press ENTER "<<G4endl;
      getc(stdin);
      exit(0);
    }
}
