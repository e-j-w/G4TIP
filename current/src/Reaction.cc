//inelastic collision followed by parametrized evaporation 
#include "Reaction.hh"



Reaction::Reaction(Projectile* Proj,  const G4String& aName)
  : G4VProcess(aName), theProjectile(Proj)
{
  proton=G4Proton::ProtonDefinition();
  neutron=G4Neutron::NeutronDefinition();
  alpha=G4Alpha::AlphaDefinition();
  reaction_here=false;
  if (verboseLevel>1) {
    G4cout <<GetProcessName() << " is created "<< G4endl;};
 
  
}
//---------------------------------------------------------------------
Reaction::~Reaction() 
{
  ;                                     
}  
//---------------------------------------------------------------------
G4Decay Reaction::decay;                                    
//---------------------------------------------------------------------
G4VParticleChange* Reaction::PostStepDoIt(
			     const G4Track& aTrack,
			     const G4Step& 
			    )
			    			    			    
{


  aParticleChange.Initialize(aTrack);
//
// Stop the current particle, if requested by G4UserLimits 
// 
  if(reaction_here)
    {
      reaction_here=false;
      G4DynamicParticle* RecoilOut;
      G4DynamicParticle* EvapP [8];
      G4DynamicParticle* EvapN [8];
      G4DynamicParticle* EvapA [8];
      RecoilOut =new G4DynamicParticle();
      for(int i=0; i<8; i++)
        {
          EvapP[i]=new G4DynamicParticle();
          EvapN[i]=new G4DynamicParticle();
          EvapA[i]=new G4DynamicParticle();
        }
      if(SetupReactionProducts(aTrack,RecoilOut))
	{
	  aParticleChange.ProposeTrackStatus(fStopAndKill);
          aParticleChange.SetNumberOfSecondaries(1+nP+nN+nA);

          //generate the secondaries (alphas, protons, neutrons) from fusion evaporation
          //and correct the momentum of the recoiling nucleus
          for(int i=0; i<nP; i++)
            if (i<8)
              {
                EvaporateWithMomentumCorrection(RecoilOut, RecoilOut, EvapP[i], proton, 5.0); //for now, evaporate 5 MeV particles
                aParticleChange.AddSecondary(EvapP[i],posIn,true); //evaporate the particle (momentum determined by EvaporateWithMomentumCorrection function)
              }
          for(int i=0; i<nN; i++)
            if (i<8)
              {
                EvaporateWithMomentumCorrection(RecoilOut, RecoilOut, EvapN[i], neutron, 5.0); //for now, evaporate 5 MeV particles
                aParticleChange.AddSecondary(EvapN[i],posIn,true); //evaporate the particle (momentum determined by EvaporateWithMomentumCorrection function)
              }
          for(int i=0; i<nA; i++)
            if (i<8)
              {
                EvaporateWithMomentumCorrection(RecoilOut, RecoilOut, EvapA[i], alpha, 5.0); //for now, evaporate 5 MeV particles
                aParticleChange.AddSecondary(EvapA[i],posIn,true); //evaporate the particle (momentum determined by EvaporateWithMomentumCorrection function)
              }

          //generate the recoiling nucleus
	  aParticleChange.AddSecondary(RecoilOut,posIn,true);
	}
    }


   
  return &aParticleChange;
}
//-----------------------------------------------------------------
G4double Reaction::PostStepGetPhysicalInteractionLength(
                             const G4Track& aTrack,
                             G4double,
                             G4ForceCondition* condition
                            )
{


  reaction_here=false;
  *condition=NotForced;

  
  G4String name=aTrack.GetVolume()->GetLogicalVolume()->GetName();
  
  if(name=="target_log")
    {
      G4UserLimits* pUserLimits = aTrack.GetVolume()->GetLogicalVolume()->GetUserLimits();
      G4double ZReaction=pUserLimits->GetUserMinRange(aTrack);
      G4double ZCurrent=aTrack.GetPosition().getZ();
      G4double Z=ZReaction-ZCurrent;
      if(Z<0)
	{
	  // 	      G4cout<<" Past the reaction point"<<G4endl;
	  // 	      G4cout<<" Volume "<<name<<G4endl;
	  // 	      G4cout<<" Z[mm]: reaction "<<ZReaction/mm<<" current "<<ZCurrent/mm<<" DZ "<<Z/mm<<G4endl;
	  return DBL_MAX;
	}
      if(Z>eps)
	{
	  G4ThreeVector dir=aTrack.GetDynamicParticle()->GetMomentumDirection();
	      
	  dir*=(ZReaction-ZCurrent);
	  // 	      G4cout<<" Before the reaction point"<<G4endl;
	  // 	      G4cout<<" Volume "<<name<<G4endl;
	  // 	      G4cout<<" Z[mm]: reaction "<<ZReaction/mm<<" current "<<ZCurrent/mm<<" DZ "<<Z/mm<<G4endl;
	  return dir.mag();
	}
      if(Z<=eps)
	{	   
	  reaction_here=true;
	  aTrack.GetVolume()->GetLogicalVolume()->GetUserLimits()->SetUserMinRange(-DBL_MAX);
	  return 0.;
	}
    }
  

  return DBL_MAX;
}
/*============================================================================*/
G4bool Reaction::SetupReactionProducts(const G4Track & aTrack,G4DynamicParticle* RecoilOut)
{


  G4double Ain;
  G4double Zin;
  G4ThreeVector dirIn;
  G4ThreeVector pIn;
  G4double      tauIn;
  G4double      KEIn;
  G4double      betaIn;

  Ain=aTrack.GetDynamicParticle()->GetDefinition()->GetAtomicMass();
  if(Ain!=A1) return FALSE;
  Zin=aTrack.GetDynamicParticle()->GetDefinition()->GetAtomicNumber();
  if(Zin!=Z1) return FALSE;

  dirIn=aTrack.GetMomentumDirection();
  posIn=aTrack.GetPosition();
  betaIn=aTrack.GetVelocity();
  KEIn=aTrack.GetDynamicParticle()->GetKineticEnergy();
  pIn=aTrack.GetMomentum(); 
  tauIn=aTrack.GetProperTime();

  G4DynamicParticle* Compound=new G4DynamicParticle();
  Compound->SetDefinition(compound);
  Compound->SetMomentum(pIn);

  RecoilOut->SetDefinition(rec);
  RecoilOut->SetMomentum(pIn);

  return TRUE;
}
//---------------------------------------------------------------------
//Computes the momentum of the recoil system after the compund has emitted a particle.
//particleEnergy in MeV.
void Reaction::EvaporateWithMomentumCorrection(G4DynamicParticle* Compound, G4DynamicParticle* RecoilOut, G4DynamicParticle* EvaporatedParticle, G4ParticleDefinition* EvaporatedParticleDef, G4double particleEnergy)
{
  G4ThreeVector pRec, pParticle; //momenta

  //set up the momentum of the emitted particle
  G4double pParticleMag = sqrt(2.0*particleEnergy*EvaporatedParticleDef->GetAtomicMass()*931.494); //set magnitude of the emitted particle's momentum
  pParticle=G4RandomDirection(); //generate a unit vector in a random direction
  pParticle=pRec*pParticleMag;

  //Initially, recoil has the same momentum as the compund system
  pRec = Compound->GetMomentum();
  //subtract momentum of the emitted particle
  pRec -= pParticle;

  //set properties of the recoil and evaporated particle
  EvaporatedParticle->SetDefinition(EvaporatedParticleDef);
  EvaporatedParticle->SetMomentum(pParticle);
  RecoilOut->SetDefinition(rec);
  RecoilOut->SetMomentum(pRec);

}
//---------------------------------------------------------
void Reaction::TargetFaceCrossSection()
{

  G4int DA=0,DZ=0;

  A1=theProjectile->getA();
  Z1=theProjectile->getZ(); 
  
  compound=G4ParticleTable::GetParticleTable()->GetIon(Z1+Z2,A1+A2,0);

 
  DA=nN*neutron->GetAtomicMass()+nP*proton->GetAtomicMass()+nA*alpha->GetAtomicMass();
  DZ=nN*neutron->GetAtomicNumber()+nP*proton->GetAtomicNumber()+nA*alpha->GetAtomicNumber();
  rec=G4ParticleTable::GetParticleTable()->GetIon(Z1+Z2-DZ,A1+A2-DA,Egamma);
  
  rec->SetPDGStable(false);
  rec->SetPDGLifeTime(tau);
  G4DecayTable *RecDecTab = rec->GetDecayTable(); 
  if (RecDecTab == NULL) {
    RecDecTab = new G4DecayTable();
    rec->SetDecayTable(RecDecTab);
  }
  GammaDecayChannel *RecDec = new GammaDecayChannel(-1,rec,1,Egamma);
  RecDecTab->Insert(RecDec);
  // RecDecTab->DumpInfo();
  // make sure that the recoil has the decay process in its manager
  G4ProcessManager *rec_pm = rec->GetProcessManager();
  if (rec_pm == NULL) {
    G4cerr << "Could not find process manager for the recoil." << G4endl;
    exit(EXIT_FAILURE);
  }
  if (rec_pm->GetProcessActivation(&decay) == false) {
    G4cout<<"-> adding the recoil decay process"<<G4endl;
    rec_pm->AddProcess(&decay,1,-1,5);
  }
  // rec_pm->DumpInfo();
  // getc(stdin);

}
//---------------------------------------------------------------------
void Reaction::AddEvaporation(G4String particle, G4double energy, G4double fwhm)
{
  evaporation *ev;
  
  ev=new evaporation;

  ev->particle=particle;
  ev->energy=energy;
  ev->fwhm=fwhm;
  history->push_back(*ev);

}  
