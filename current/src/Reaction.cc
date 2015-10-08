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
      killTrack=false;

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

      G4ThreeVector pIn=aTrack.GetMomentum();
      G4ThreeVector cmv = GetCMVelocity(aTrack);
      //G4cout << "Center of mass velocity: " << cmv << " c" << G4endl;

      if(SetupReactionProducts(aTrack,RecoilOut))
	{
	  aParticleChange.ProposeTrackStatus(fStopAndKill);
          aParticleChange.SetNumberOfSecondaries(1+nP+nN+nA);

          //generate the secondaries (alphas, protons, neutrons) from fusion evaporation
          //and correct the momentum of the recoiling nucleus
          for(int i=0; i<nP; i++) //protons
            {
              if (i==0)
                  evapdeltaExi = CLHEP::RandGauss::shoot(evapdeltaEximean[i],evapdeltaExistdev[i]); //set the energy of the evaporated particle
              else if (i<MAXNUMEVAP)
                  evapdeltaExi = CLHEP::RandGauss::shoot(evapdeltaEximean[i],evapdeltaExistdev[i]) - CLHEP::RandGauss::shoot(evapdeltaEximean[0],evapdeltaExistdev[0]); //energy is difference of total and first particle distributions
              if((i<MAXNUMEVAP)&&((evapdeltaExi+QEvap[i]) > 0.0)) //check that the particle can be evaporated
                {
                  EvaporateWithMomentumCorrection(RecoilOut, RecoilOut, EvapP[i], proton, evapdeltaExi, QEvap[i],cmv);
                  aParticleChange.AddSecondary(EvapP[i],posIn,true); //evaporate the particle (momentum determined by EvaporateWithMomentumCorrection function)
                }
              else
                killTrack=true; //this is no longer the desired reaction channel, kill it
            }
          for(int i=0; i<nN; i++) //neutrons
            {
              if (i==0)
                  evapdeltaExi = CLHEP::RandGauss::shoot(evapdeltaEximean[i],evapdeltaExistdev[i]); //set the energy of the evaporated particle
              else if (i<MAXNUMEVAP)
                  evapdeltaExi = CLHEP::RandGauss::shoot(evapdeltaEximean[i],evapdeltaExistdev[i]) - CLHEP::RandGauss::shoot(evapdeltaEximean[0],evapdeltaExistdev[0]); //energy is difference of total and first particle distributions
              if((i<MAXNUMEVAP)&&((evapdeltaExi+QEvap[i]) > 0.0)) //check that the particle can be evaporated
                {
                  EvaporateWithMomentumCorrection(RecoilOut, RecoilOut, EvapN[i], neutron, evapdeltaExi, QEvap[i],cmv);
                  aParticleChange.AddSecondary(EvapN[i],posIn,true); //evaporate the particle (momentum determined by EvaporateWithMomentumCorrection function)
                }
              else
                killTrack=true; //this is no longer the desired reaction channel, kill it
            }
          for(int i=0; i<nA; i++) //alphas
            {
              if (i==0)
                  evapdeltaExi = CLHEP::RandGauss::shoot(evapdeltaEximean[i],evapdeltaExistdev[i]); //set the energy of the evaporated particle
              else if (i<MAXNUMEVAP)
                  evapdeltaExi = CLHEP::RandGauss::shoot(evapdeltaEximean[i],evapdeltaExistdev[i]) - CLHEP::RandGauss::shoot(evapdeltaEximean[0],evapdeltaExistdev[0]); //energy is difference of total and first particle distributions
              if((i<MAXNUMEVAP)&&((evapdeltaExi+QEvap[i]) > 0.0)) //check that the particle can be evaporated
                {
                  EvaporateWithMomentumCorrection(RecoilOut, RecoilOut, EvapA[i], alpha, evapdeltaExi, QEvap[i],cmv);
                  aParticleChange.AddSecondary(EvapA[i],posIn,true); //evaporate the particle (momentum determined by EvaporateWithMomentumCorrection function)
                }
              else
                killTrack=true; //this is no longer the desired reaction channel, kill it
            }

          //generate the recoiling nucleus
          RecoilOut->SetDefinition(residual); //give the residual the gamma decay process specified in TargetFaceCrossSection()
	  aParticleChange.AddSecondary(RecoilOut,posIn,true);

          //debug
          //G4cout << "Recoil type: " <<  RecoilOut->GetDefinition()->GetParticleType() << G4endl;

          //get rid of the track if neccessary
          if(killTrack==true)
          	aParticleChange.ProposeTrackStatus(fKillTrackAndSecondaries);

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
  //G4cout << "At compound formation - Recoil momentum: " << RecoilOut->GetMomentum() << ", Recoil KE: " << RecoilOut->GetKineticEnergy() << G4endl;

  return TRUE;
}
//---------------------------------------------------------------------
//Computes the momentum of the recoil system after the compund has emitted a particle.
//particleEnergy in MeV.
void Reaction::EvaporateWithMomentumCorrection(G4DynamicParticle* Compound, G4DynamicParticle* ResidualOut, G4DynamicParticle* EvaporatedParticle, G4ParticleDefinition* EvaporatedParticleDef, G4double deltaExi,  G4double Qevap, G4ThreeVector cmv)
{

  G4ThreeVector pRec, pParticle; //momenta
  G4ThreeVector vParticle; //velocity
  //G4ThreeVector cmv=(Compound->GetMomentum()) / (Compound->GetDefinition()->GetPDGMass()); //center of mass velocity (ie. initial compound velocity in the lab frame) 
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
  if(deltaExi<0.0)
    {
      G4cout << "ERROR!  Excitation energy is smaller than the Q value!  Evaporation should not occur!" << G4endl;
      G4cout << "Please check the reaction PostStepDoIt code and correct this!" << G4endl;
    }

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


  //determine the momentum of the residual particle
  pRec = Compound->GetMomentum(); //initially, residual has the same momentum as the compound system
  //G4cout << "Initial recoil momentum: " << pRec << G4endl;
  //G4cout << "Initial recoil KE: " << Compound->GetKineticEnergy() << G4endl;
  pRec -= pParticle; //subtract momentum of the emitted particle from the residual


  //set properties of the recoil and evaporated particle
  EvaporatedParticle->SetDefinition(EvaporatedParticleDef);
  EvaporatedParticle->SetMomentum(pParticle);
  ResidualOut->SetDefinition(RecoilResidual);
  ResidualOut->SetMomentum(pRec);

  /*if(ResidualOut->GetKineticEnergy() == 0)
    {
       G4cout << "cmv: " <<  cmv << ", deltaExi: " << deltaExi << ", Q: " << Qevap << G4endl;
       G4cout << "vParticleMag: " <<  vParticleMag << ", particleCMEnergy: " << particleCMEnergy << G4endl;
       G4cout << "Evaporated particle PDG mass: " << EvaporatedParticleDef->GetPDGMass() << G4endl << G4endl;
    }*/

}
//---------------------------------------------------------------------
//Returns the center of mass velocity of the beam-target system
G4ThreeVector Reaction::GetCMVelocity(const G4Track & aTrack)
{
  G4ThreeVector pIn = aTrack.GetMomentum(); //momentum of incoming particle
  return pIn/(compound->GetPDGMass()); //center of mass velocity
}
//---------------------------------------------------------
void Reaction::TargetFaceCrossSection()
{

  G4int DA=0,DZ=0;
  A1=theProjectile->getA();
  Z1=theProjectile->getZ(); 
  
  //set properties of the compound (which we assume does not gamma decay) 
  compound=G4ParticleTable::GetParticleTable()->GetIon(Z1+Z2,A1+A2,0); //Z2,A2 are set to target charge and mass as defined in Target.cc 

  //set properties (including gamma decay processes) of the residual
  DA=nN*neutron->GetAtomicMass()+nP*proton->GetAtomicMass()+nA*alpha->GetAtomicMass();
  DZ=nN*neutron->GetAtomicNumber()+nP*proton->GetAtomicNumber()+nA*alpha->GetAtomicNumber();
  residual=G4ParticleTable::GetParticleTable()->GetIon(Z1+Z2-DZ,A1+A2-DA,Egamma);
  
  residual->SetPDGStable(false);
  residual->SetPDGLifeTime(tau);
  G4cout << "Decay lifetime of the residual species: " << tau << " ns, gamma energy " << Egamma << " MeV." <<G4endl;
  G4DecayTable *ResDecTab = residual->GetDecayTable(); 
  if (ResDecTab == NULL) {
    ResDecTab = new G4DecayTable();
    residual->SetDecayTable(ResDecTab);
  }
  GammaDecayChannel *ResDec = new GammaDecayChannel(-1,residual,1,Egamma);
  ResDecTab->Insert(ResDec);
  //RecDecTab->DumpInfo();
  // make sure that the residual has the decay process in its manager
  G4ProcessManager *residual_pm = residual->GetProcessManager();
  if (residual_pm == NULL) {
    G4cerr << "Could not find process manager for the residual nucleus." << G4endl;
    exit(EXIT_FAILURE);
  }
  if (residual_pm->GetProcessActivation(&decay) == false) {
    G4cout<<"-> adding the residual nucleus decay process."<<G4endl;
    residual_pm->AddProcess(&decay,1,-1,5);
  }
  //residual_pm->DumpInfo();
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
