//inelastic collision followed by parametrized evaporation 
#include "Reaction.hh"



Reaction::Reaction(Projectile* Proj, const G4String& aName)
  : G4VProcess(aName),theProjectile(Proj)
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

      //define all dynamic particles
      G4DynamicParticle* RecoilOut;
      G4DynamicParticle* EvapP [MAXNUMEVAP];
      G4DynamicParticle* EvapN [MAXNUMEVAP];
      G4DynamicParticle* EvapA [MAXNUMEVAP];
      RecoilOut =new G4DynamicParticle();
      for(int i=0; i<MAXNUMEVAP; i++)
        {
          EvapP[i]=new G4DynamicParticle();
          EvapN[i]=new G4DynamicParticle();
          EvapA[i]=new G4DynamicParticle();
        }

      //G4ThreeVector cmv = GetCMVelocity(aTrack);
      //G4cout << "Center of mass velocity: " << cmv << " c" << G4endl;

      if(SetupReactionProducts(aTrack,RecoilOut))
	{
	  aParticleChange.ProposeTrackStatus(fStopAndKill);
          aParticleChange.SetNumberOfSecondaries(1+nP+nN+nA);

          //generate the secondaries (alphas, protons, neutrons) from fusion evaporation
          //and correct the momentum of the recoiling nucleus
          for(int i=0; i<nP; i++) //protons
            if (i==0)
              {
                evapdeltaExi = CLHEP::RandGauss::shoot(evapdeltaEximean[0],evapdeltaExistdev[0]); //set the energy of the evaporated particle
                EvaporateWithMomentumCorrection(RecoilOut, RecoilOut, EvapP[i], proton, evapdeltaExi, QEvap[0]);
                aParticleChange.AddSecondary(EvapP[i],posIn,true); //evaporate the particle (momentum determined by EvaporateWithMomentumCorrection function)
              }
            else if (i<MAXNUMEVAP)
              {
                evapdeltaExi = CLHEP::RandGauss::shoot(evapdeltaEximean[1],evapdeltaExistdev[1]) - CLHEP::RandGauss::shoot(evapdeltaEximean[0],evapdeltaExistdev[0]); //energy is difference of total and first particle distributions
                EvaporateWithMomentumCorrection(RecoilOut, RecoilOut, EvapP[i], proton, evapdeltaExi, QEvap[1]);
                aParticleChange.AddSecondary(EvapP[i],posIn,true); //evaporate the particle (momentum determined by EvaporateWithMomentumCorrection function)
              }
          for(int i=0; i<nN; i++) //neutrons
            if (i==0)
              {
                evapdeltaExi = CLHEP::RandGauss::shoot(evapdeltaEximean[0],evapdeltaExistdev[0]); //set the energy of the evaporated particle
                EvaporateWithMomentumCorrection(RecoilOut, RecoilOut, EvapN[i], neutron, evapdeltaExi, QEvap[0]);
                aParticleChange.AddSecondary(EvapN[i],posIn,true); //evaporate the particle (momentum determined by EvaporateWithMomentumCorrection function)
              }
            else if (i<MAXNUMEVAP)
              {
                evapdeltaExi = CLHEP::RandGauss::shoot(evapdeltaEximean[1],evapdeltaExistdev[1]) - CLHEP::RandGauss::shoot(evapdeltaEximean[0],evapdeltaExistdev[0]); //energy is difference of total and first particle distributions
                EvaporateWithMomentumCorrection(RecoilOut, RecoilOut, EvapN[i], neutron, evapdeltaExi, QEvap[1]);
                aParticleChange.AddSecondary(EvapN[i],posIn,true); //evaporate the particle (momentum determined by EvaporateWithMomentumCorrection function)
              }
          for(int i=0; i<nA; i++) //alphas
            if (i==0)
              {
                evapdeltaExi = CLHEP::RandGauss::shoot(evapdeltaEximean[0],evapdeltaExistdev[0]); //set the energy of the evaporated particle
                EvaporateWithMomentumCorrection(RecoilOut, RecoilOut, EvapA[i], alpha, evapdeltaExi, QEvap[0]);
                aParticleChange.AddSecondary(EvapA[i],posIn,true); //evaporate the particle (momentum determined by EvaporateWithMomentumCorrection function)
              }
            else if (i<MAXNUMEVAP)
              {
                evapdeltaExi = CLHEP::RandGauss::shoot(evapdeltaEximean[1],evapdeltaExistdev[1]) - CLHEP::RandGauss::shoot(evapdeltaEximean[0],evapdeltaExistdev[0]); //energy is difference of total and first particle distributions
                EvaporateWithMomentumCorrection(RecoilOut, RecoilOut, EvapA[i], alpha, evapdeltaExi, QEvap[1]);
                aParticleChange.AddSecondary(EvapA[i],posIn,true); //evaporate the particle (momentum determined by EvaporateWithMomentumCorrection function)
              }

          //generate the recoiling nucleus
	  aParticleChange.AddSecondary(RecoilOut,posIn,true);

          //debug
          //G4cout << "Recoil type: " <<  RecoilOut->GetDefinition()->GetParticleType() << G4endl;
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
  G4ThreeVector pIn; //momentum of incoming particle

  //G4DynamicParticle* Compound=new G4DynamicParticle();
  //Compound->SetDefinition(compound);

  Ain=aTrack.GetDynamicParticle()->GetDefinition()->GetAtomicMass();
  if(Ain!=A1) return FALSE;
  Zin=aTrack.GetDynamicParticle()->GetDefinition()->GetAtomicNumber();
  if(Zin!=Z1) return FALSE;

  dirIn=aTrack.GetMomentumDirection();
  posIn=aTrack.GetPosition();
  pIn=aTrack.GetMomentum();
  //G4cout << "KE of beam: " <<  aTrack.GetKineticEnergy() << G4endl;

  //Compound->SetMomentum(pIn);
  //Compound->SetMomentumDirection(dirIn);
  //Compound->SetKineticEnergy(aTrack.GetKineticEnergy() + Q - excitation);
  //G4cout << "KE of compound: " << Compound->GetKineticEnergy() << G4endl;

  RecoilOut->SetDefinition(compound);
  RecoilOut->SetKineticEnergy(aTrack.GetKineticEnergy() + QRxn - initExi);
  RecoilOut->SetMomentumDirection(dirIn);
  //G4cout << "Before Evaporation - Recoil momentum: " << RecoilOut->GetMomentum() << ", Recoil KE: " << RecoilOut->GetKineticEnergy() << G4endl;

  return TRUE;
}
//---------------------------------------------------------------------
//Computes the momentum of the recoil system after the compund has emitted a particle.
//particleEnergy in MeV.
void Reaction::EvaporateWithMomentumCorrection(G4DynamicParticle* Compound, G4DynamicParticle* RecoilOut, G4DynamicParticle* EvaporatedParticle, G4ParticleDefinition* EvaporatedParticleDef, G4double deltaExi,  G4double Qevap)
{

  G4ThreeVector pRec, pParticle; //momenta
  G4ThreeVector vParticle; //velocity
  G4ThreeVector cmv=(Compound->GetMomentum()) / (Compound->GetDefinition()->GetPDGMass()); //center of mass velocity (ie. initial compound velocity in the lab frame) 
  //G4double Qevap; //Q of the evaporation process 
  //G4cout << "cmv: " <<  cmv << G4endl;
  //G4cout << "Q: " <<  Qevap << ", deltaExi: " << deltaExi << G4endl;
  //G4cout << "Before Evaporation - Compound momentum: " << Compound->GetMomentum() << ", Compound KE: " << Compound->GetKineticEnergy() << G4endl;
  //G4cout << "Compound mass: " << Compound->GetDefinition()->GetPDGMass() << G4endl;


  //define the recoil particle after evaporation
  G4ParticleDefinition* RecoilResidual;
  G4int rrecA=Compound->GetDefinition()->GetAtomicMass() - EvaporatedParticleDef->GetAtomicMass();
  G4int rrecZ=Compound->GetDefinition()->GetAtomicNumber() - EvaporatedParticleDef->GetAtomicNumber();
  RecoilResidual=G4ParticleTable::GetParticleTable()->GetIon(rrecZ,rrecA,0);//3rd parameter is excitation energy - what does this do?
  //G4cout << "Residual mass: " << RecoilResidual->GetPDGMass() << G4endl;

  deltaExi = deltaExi + Qevap; //amount of the excitation energy that goes into KE of the products

  //derive the center of mass energy of the evaporated particle from the change in excitation energy of the compound
  //G4double particleCMEnergy = deltaExi - ( deltaExi / ( ((RecoilResidual->GetAtomicMass()) / (EvaporatedParticleDef->GetAtomicMass())) + 1.0));
  G4double particleCMEnergy = deltaExi * ( 1.0 / ( ((EvaporatedParticleDef->GetAtomicMass()) / (RecoilResidual->GetAtomicMass())) + 1.0));
  //G4cout << "CM energy of evaporated particle: " << particleCMEnergy << " MeV." << G4endl;
  //G4cout << "CM energy of recoil particle: " << deltaExi - particleCMEnergy << " MeV." << G4endl;
  

  //set up the momentum of the evaporated particle
  G4double vParticleMag = sqrt(2.0*particleCMEnergy/(EvaporatedParticleDef->GetPDGMass())); //set magnitude of the emitted particle's velocity (center of mass frame)
  vParticle=G4RandomDirection(); //generate a unit vector in a random direction (direction of evaporated particle's momentum in the center of mass)
  vParticle=vParticle*vParticleMag;
  vParticle += cmv; //boost velocity to lab frame
  pParticle = vParticle*EvaporatedParticleDef->GetPDGMass(); //get lab frame momentum
  //G4cout << "Evaporated particle momentum magnitude: " <<  pParticleMag << G4endl;
  //G4cout << "Evaporated particle momentum: " <<  pParticle << G4endl;


  //determine the momentum of the recoil particle
  pRec = Compound->GetMomentum(); //initially, recoil has the same momentum as the compound system
  //G4cout << "Initial recoil momentum: " << pRec << G4endl;
  //G4cout << "Initial recoil KE: " << Compound->GetKineticEnergy() << G4endl;
  pRec -= pParticle; //subtract momentum of the emitted particle from the recoil


  //set properties of the recoil and evaporated particle
  EvaporatedParticle->SetDefinition(EvaporatedParticleDef);
  EvaporatedParticle->SetMomentum(pParticle);
  RecoilOut->SetDefinition(RecoilResidual);
  RecoilOut->SetMomentum(pRec);

  //G4cout << "After evaporaton - Recoil Z: " <<  rrecZ << ", Recoil A: "<< rrecA << G4endl;
  //G4cout << "After evaporaton - Recoil momentum: " << pRec << ", Recoil KE: " << RecoilOut->GetKineticEnergy() << " MeV" << G4endl;

}
//---------------------------------------------------------------------
//Returns the center of mass velocity of the beam-target system
/*G4ThreeVector Reaction::GetCMVelocity(const G4Track & aTrack)
{
  G4ThreeVector pIn = aTrack.GetMomentum(); //momentum of incoming particle
  return pIn/((A1+A2)*931.494); //center of mass velocity
}*/
//---------------------------------------------------------
void Reaction::TargetFaceCrossSection()
{

  G4int DA=0,DZ=0;

  A1=theProjectile->getA();
  Z1=theProjectile->getZ(); 
  
  compound=G4ParticleTable::GetParticleTable()->GetIon(Z1+Z2,A1+A2,0); //Z2,A2 are set to target charge and mass as defined in Target.cc 

 
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
