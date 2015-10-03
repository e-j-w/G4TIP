#include "EventAction.hh"

 
EventAction::EventAction(Results* RE,RunAction* RA,Projectile* proj):results(RE),run_action(RA),theProjectile(proj)
//EventAction::EventAction(Results* RE,RunAction* RA):results(RE),run_action(RA)
{ 

  ionCollectionID=-1;
  CsICollectionID=-1;
  soa=16*4*sizeof(G4double);
  sov=16*4*sizeof(G4ThreeVector);
  At=4;
  Zt=2;
  SetTriggerParticleSing();
  CsIThreshold=2*MeV;

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

  if(CsICollectionID<0)
    CsICollectionID=SDman->GetCollectionID("CsICollection");
 
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
  TrackerCsIHitsCollection* CsI=new TrackerCsIHitsCollection();
  TrackerIonHitsCollection* HI=new TrackerIonHitsCollection();
  G4int Np;



  // CsI trigger
  if(HCE!=NULL) 
    {  
      CsI=(TrackerCsIHitsCollection*)(HCE->GetHC(CsICollectionID)); 
      HI=(TrackerIonHitsCollection*)(HCE->GetHC(ionCollectionID));
      Np=CsI->entries();

      if(Np>0) 
	{
	  G4double partECsI=0.; //energy of user defined particle
	  for(int i=0;i<Np;i++)
	    {
              if((CsIIDTrigger==0)||((*CsI)[i]->GetId()==CsIIDTrigger)) //CsI detector ID trigger
		if((*CsI)[i]->GetA()==At) // user defined particle trigger
		  if((*CsI)[i]->GetZ()==Zt)
		    {
		      partECsI+=(*CsI)[i]->GetKE();
		      //printf("particle A=%i Z=%i   CsI partial energy deposit is %9.3f in detector ID %i \n",At,Zt,partECsI,(*CsI)[i]->GetId());
		    }
	    }

	  if(partECsI>CsIThreshold)
	    eventTrigger|=10;

          /* 
            ASC notes 27 Aug 2015:
            Bitwise OR assignment x|=y -> x = x|y. 
            eventTrigger 8 is CsI system trigger i.e. trigger on recoil OR projectile
          */  

	  //if((eventTrigger&2)||(eventTrigger&4)) //for more complicated triggering schemes see Aaron's code
	  //  eventTrigger|=8;
	  
          /*printf("recoil CsI total energy deposit is %9.3f\n",rECsI);
          printf("proj   CsI total energy deposit is %9.3f\n",pECsI);
          printf("CsI eventTrigger is %d\n",eventTrigger);
          getc(stdin);*/
	  
	}   
    }
  // end CsI trigger
  
  // HPGe trigger
  if(GriffinFold>0)
    eventTrigger|=1;
  // end HPGe trigger

  /*printf("HPGe fold is %d\n",GriffinFold);
  printf("HPGe eventTrigger is %d\n",eventTrigger);
  printf("eventTrigger is %d setTrigger is %d\n",eventTrigger,setTrigger);*/
  
  if((eventTrigger&setTrigger)==setTrigger)
      {
	if(GriffinFold>0)
	  for(G4int det=0;det<16;det++)
	    for(G4int cry=0;cry<4;cry++)
	      if( GriffinCrystEnergyDet[det][cry]>0)
		GriffinCrystPosDet[det][cry]/=GriffinCrystEnergyDet[det][cry];
	results->FillTree(evtNb,HI,CsI,GriffinCrystWeightDet,GriffinCrystEnergyDet,GriffinCrystPosDet);
	//printf("Event fulfills trigger condition %d\n",eventTrigger&setTrigger);
      }
    // getc(stdin);
}
//*********************************************************************//
void EventAction::AddGriffinCrystDet(G4double de, G4double w, G4ThreeVector pos, G4int det, G4int cry) 
{
  //G4cout<<" Detector "<<det<<" crystal "<<cry<<" weight "<<w<<G4endl;
  if(GriffinCrystWeightDet[det][cry]==0.)
    {
      GriffinCrystWeightDet[det][cry]=w;
      GriffinCrystEnergyDet[det][cry]=de;
      GriffinCrystPosDet[det][cry]=de*pos;
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
//---------------------------------------------------------
void EventAction::setTriggerA(G4int Ain)
{

  At=Ain;
  G4cout<<"----> A of the particle to trigger on set to  "<<At<< G4endl;
  
}
//---------------------------------------------------------
void EventAction::setTriggerZ(G4int Zin)
{

  Zt=Zin;
  G4cout<<"----> Z of the particle to trigger on set to  "<<Zt<< G4endl;
  
}
