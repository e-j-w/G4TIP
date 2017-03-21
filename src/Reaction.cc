//Fusion-Evaporation reaction process code
//Jonathan W.
//inelastic collision followed by parametrized evaporation 
#include "Reaction.hh"


Reaction::Reaction(Projectile* Proj, const G4String& aName)
  : G4VProcess(aName),theProjectile(Proj)
{
  proton=G4Proton::ProtonDefinition();
  neutron=G4Neutron::NeutronDefinition();
  alpha=G4Alpha::AlphaDefinition();
  numDecays=0;
  memset(Egamma,0,sizeof(Egamma));
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
G4VParticleChange* Reaction::PostStepDoIt(const G4Track& aTrack,const G4Step&)
{

  aParticleChange.Initialize(aTrack);

  //define all dynamic particles
  G4DynamicParticle* RecoilOut;
  G4DynamicParticle* EvapP [MAXNUMEVAP];
  G4DynamicParticle* EvapN [MAXNUMEVAP];
  G4DynamicParticle* EvapA [MAXNUMEVAP];
  RecoilOut =new G4DynamicParticle();
  for(int i=0; i<nP; i++) //protons
    if(i<MAXNUMEVAP)
      EvapP[i]=new G4DynamicParticle();
  for(int i=0; i<nN; i++) //neutrons
    if(i<MAXNUMEVAP)
      EvapN[i]=new G4DynamicParticle();
  for(int i=0; i<nA; i++) //alphas
    if(i<MAXNUMEVAP)
      EvapA[i]=new G4DynamicParticle();

  if(reaction_here)
    {
      reaction_here=false;
      killTrack=false;

      //get properties of the beam-target system
      G4ThreeVector pIn=aTrack.GetMomentum();
      G4ThreeVector cmv = GetCMVelocity(aTrack); //center of mass velocity

      //generate delta Exi values for each particle to be evaporated  
      for(int i=0; i<(nP+nN+nA); i++)
        if(i<MAXNUMEVAP)
          {
            evapdeltaExi[i]=0.;
            while(((evapdeltaExi[i]+QEvap[i]) <= 0.0) || ((evapdeltaExi[i]+QEvap[i]) > initExi)) //clamp delta Exi values to physically possible values
              evapdeltaExi[i]=getExi(exix0,exiw,exitau);
              //evapdeltaExi[i]=dExiShift+(CLHEP::RandGamma::shoot(rho,lambda));
          }
          
      //check that sum of delta Exi values is in bounds
      totalEvapdeltaExi=0;
      for(int i=0; i<(nP+nN+nA); i++)
        if(i<MAXNUMEVAP)
          totalEvapdeltaExi+=evapdeltaExi[i];
      if(totalEvapdeltaExi>initExi) //not physically possible!
        killTrack=true;
      if((initExi-totalEvapdeltaExi)<Egammatot) //not enough energy to emit gamma cascade
        killTrack=true;
      
      if(killTrack==false)  
        if(SetupReactionProducts(aTrack,RecoilOut))
	        {
	          aParticleChange.ProposeTrackStatus(fStopAndKill);
            aParticleChange.SetNumberOfSecondaries(1+nP+nN+nA);

            //generate the secondaries (alphas, protons, neutrons) from fusion evaporation
            //and correct the momentum of the recoiling nucleus
            for(int i=0; i<nP; i++) //protons
              if(i<MAXNUMEVAP) //check that the particle can be evaporated
                {
                  EvaporateWithMomentumCorrection(RecoilOut, RecoilOut, EvapP[i], proton, evapdeltaExi[i], QEvap[i],cmv);
                  aParticleChange.AddSecondary(EvapP[i],posIn,true); //evaporate the particle (momentum determined by EvaporateWithMomentumCorrection function)
                }
              else
                killTrack=true; //this is no longer the desired reaction channel, kill it
            for(int i=0; i<nN; i++) //neutrons
              if(i<MAXNUMEVAP) //check that the particle can be evaporated
                {
                  EvaporateWithMomentumCorrection(RecoilOut, RecoilOut, EvapN[i], neutron, evapdeltaExi[i+nP], QEvap[i],cmv);
                  aParticleChange.AddSecondary(EvapN[i],posIn,true); //evaporate the particle (momentum determined by EvaporateWithMomentumCorrection function)
                }
              else
                killTrack=true; //this is no longer the desired reaction channel, kill it
            for(int i=0; i<nA; i++) //alphas
              if(i<MAXNUMEVAP) //check that the particle can be evaporated
                {
                  EvaporateWithMomentumCorrection(RecoilOut, RecoilOut, EvapA[i], alpha, evapdeltaExi[i+nP+nN], QEvap[i],cmv);
                  aParticleChange.AddSecondary(EvapA[i],posIn,true); //evaporate the particle (momentum determined by EvaporateWithMomentumCorrection function)
                }
              else
                killTrack=true; //this is no longer the desired reaction channel, kill it

            //Check that the angle of at least one of the evaporated particles (in the lab frame) in in the user specified range.
            //Otherwise, kill the track.
            if((constrainedAngle==true)&&(killTrack==false))
              {
                G4bool goodEvapAngle=false;
                for(int i=0; i<nP; i++)
                  if(goodEvapAngle==false)
                    if(EvapP[i]->GetMomentumDirection().getTheta()<maxEvapAngle)
                      if(EvapP[i]->GetMomentumDirection().getTheta()>minEvapAngle)
                        goodEvapAngle=true;//at least one of the emitted particles satisfies the specified angular range
                for(int i=0; i<nN; i++)
                  if(goodEvapAngle==false)
                    if(EvapN[i]->GetMomentumDirection().getTheta()<maxEvapAngle)
                      if(EvapN[i]->GetMomentumDirection().getTheta()>minEvapAngle)
                        goodEvapAngle=true;//at least one of the emitted particles satisfies the specified angular range
                for(int i=0; i<nA; i++)
                  if(goodEvapAngle==false)    
                    if(EvapA[i]->GetMomentumDirection().getTheta()<maxEvapAngle)
                      if(EvapA[i]->GetMomentumDirection().getTheta()>minEvapAngle)
                        goodEvapAngle=true;//at least one of the emitted particles satisfies the specified angular range
                if(goodEvapAngle==false)
                  killTrack=true;
              }
            
            if(killTrack==false)
              {
								//generate the residual nucleus
								RecoilOut->SetDefinition(residual[0]); //give the residual the gamma decay process specified in TargetFaceCrossSection()
								aParticleChange.AddSecondary(RecoilOut,posIn,true);
								//debug
								//G4cout << "Residual type: " <<  RecoilOut->GetDefinition()->GetParticleType() << G4endl;
								//G4cout << "Residual KE: " << RecoilOut->GetKineticEnergy()/MeV << " MeV."<<G4endl;
								//G4cout << "Residual A: " << RecoilOut->GetMass()/931.5 << ", Residual Z: " << RecoilOut->GetCharge() <<G4endl;
								//G4cout << "Residual stability: " << RecoilOut->GetDefinition()->GetPDGStable() << ", Residual lifetime: " << std::setprecision(10) << RecoilOut->GetDefinition()->GetPDGLifeTime()/ns << " ns" << G4endl; 
              }
          }
        
      //get rid of the track if neccessary
      if(killTrack==true)
        aParticleChange.ProposeTrackStatus(fKillTrackAndSecondaries);
      
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
  //G4cout << "At compound formation - Recoil momentum: " << RecoilOut->GetMomentum() << ", Recoil KE: " << RecoilOut->GetKineticEnergy()/MeV << " MeV."<<G4endl;

  return TRUE;
}
//---------------------------------------------------------------------
//Computes the momentum of the recoil system after the compund has emitted a particle.
//particleEnergy in MeV.

//cmv: center of mass velocity vector for the beam-target system
//vParticle: unit vector specifying evaporated particle's emission direction in the CM frame.

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
      G4cerr << "ERROR!  Excitation energy is smaller than the Q value!  Evaporation should not occur!" << G4endl;
      G4cerr << "Please check the reaction PostStepDoIt code and correct this!" << G4endl;
    }

  //derive the center of mass energy of the evaporated particle from the change in excitation energy of the compound
  //G4double particleCMEnergy = deltaExi - ( deltaExi / ( ((RecoilResidual->GetAtomicMass()) / (EvaporatedParticleDef->GetAtomicMass())) + 1.0));
  G4double particleCMEnergy = deltaExi * ( 1.0 / ( ((EvaporatedParticleDef->GetAtomicMass()) / (RecoilResidual->GetAtomicMass())) + 1.0));
  //G4cout << "CM energy of evaporated particle: " << particleCMEnergy << " MeV." << G4endl;
  //G4cout << "CM energy of recoil particle: " << deltaExi - particleCMEnergy << " MeV." << G4endl;
  

  //set up the momentum of the evaporated particle
  G4double vParticleMag = sqrt(2.0*particleCMEnergy/(EvaporatedParticleDef->GetPDGMass())); //set magnitude of the emitted particle's velocity (center of mass frame)
  vParticle=G4RandomDirection(); //generate a unit vector in a random direction (direction of particle emission)
  vParticle=vParticle*vParticleMag; //calculate velocity vector of emitted particle in CM frame
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

  //G4cout << "Evaporated particle energy (MeV): " << EvaporatedParticle->GetKineticEnergy() << ", angle (deg): " << acos((EvaporatedParticle->GetMomentum().getZ())/(EvaporatedParticle->GetMomentum().mag()))/degree << G4endl;
  //G4cout << "0 0 0 0 0 0 0 0 0 0 0 0 0 0 " << EvaporatedParticle->GetKineticEnergy() << " " << acos((EvaporatedParticle->GetMomentum().getZ())/(EvaporatedParticle->GetMomentum().mag()))/degree << G4endl; //formatted like PACE4 .patricles files
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
//Sets up the decay products of the compound nucleus, including 
//any gammas emitted in the residual nucleus cascade.
//CHECK WHETHER CASCADE IS WORKING CORRECTLY
//NUCLEI WITH PROPER EXCITATION ENERGY APPEAR PRESENT WHEN PRINTING TRACK INFO
//BUT IT LOOKS AS THOUGH GAMMAS ARE NOT BEING EMITTED AT THE PROPER TIME
//OR PERHAPS GAMMAS ARE BEING EMITTED WITH LIFETIME FROM A DIFFERENT STEP IN THE
//CASCADE (OR PERHAPS A MIXTURE OF THE LIFETIMES OF THE DIFFERENT STEPS?)
//actually, it still happens even with 1 gamma
//the lifetime appears to match the 1st excited state of 22Ne.  Perhaps Geant4 is automatically inserting the decay from a table somewhere?
//cheesing excitation energy of residual to 0 doesn't seem to get rid of the 2nd peak
//check other nuclei?
//possibly the time recorded in the feature is simply the time of the final step in the ion track?
//When changing the backing to G4_C, 2nd peak seems to go away
void Reaction::TargetFaceCrossSection()
{
  G4cout << "---------- SETUP OF DECAY PRODUCTS ----------" << G4endl;
  
  Eexcit=0.;
  for(int i=0;i<numDecays;i++)
    Eexcit+=Egamma[i];
  Egammatot=Eexcit;//store the total energy used by gamma emission

  G4int DA=0,DZ=0;
  A1=theProjectile->getA();
  Z1=theProjectile->getZ();
  
  //set properties of the compound (which we assume does not gamma decay)
  compound=G4ParticleTable::GetParticleTable()->GetIon(Z1+Z2,A1+A2,0); //Z2,A2 are set to target charge and mass as defined in Target.cc 

  DA=nN*neutron->GetAtomicMass()+nP*proton->GetAtomicMass()+nA*alpha->GetAtomicMass();
  DZ=nN*neutron->GetAtomicNumber()+nP*proton->GetAtomicNumber()+nA*alpha->GetAtomicNumber();
  
  //set properties (including gamma decay processes) of the residual species in the cascade
  if(numDecays>0)
    for(int i=0;i<numDecays;i++)
      {
        
				//define the residual species
				//residual[i]=G4ParticleTable::GetParticleTable()->GetIon(Z1+Z2-DZ,A1+A2-DA,Eexcit);
				residual[i]=G4ParticleTable::GetParticleTable()->GetIonTable()->GetIon(Z1+Z2-DZ,A1+A2-DA,Eexcit);
				if(i>0)
					residual[i]=ResDec[i-1]->GetDaughterNucleus(); //the next residual nucleus is the daughter of the previous one
            
				//set up lifetime
				residual[i]->SetPDGStable(false);
				residual[i]->SetPDGLifeTime(tau[i]);

				//set up gamma decay channel
				ResDecTab[i] = new G4DecayTable();
				residual[i]->SetDecayTable(ResDecTab[i]);
				ResDec[i] = new GammaDecayChannel(-1,residual[i],1,Egamma[i],Eexcit);
				ResDecTab[i]->Insert(ResDec[i]);
				//ResDecTab[i]->DumpInfo();
				
        //make sure that the residual has the decay process in its manager
        if (residual[i]->GetProcessManager() == NULL) {
          G4cerr << "Could not find process manager for gamma cascade step " << i+1 << " of the residual nucleus." << G4endl;
          exit(EXIT_FAILURE);
        }
        decay[i] = new G4Decay();
        /*if(i>0)
        	if (residual[i]->GetProcessManager()->GetProcessActivation(decay[i-1]) == true)
        		printf("WARNING: previous decay present!!\n");*/
        if (residual[i]->GetProcessManager()->GetProcessActivation(decay[i]) == false) {
          G4cout<<"-> adding the residual nucleus decay process for step "<< i+1 <<" of the cascade."<<G4endl;
          residual[i]->GetProcessManager()->AddProcess(decay[i],1,-1,5);
        }
        //residual[i]->GetProcessManager()->DumpInfo();
        
        Eexcit-=Egamma[i];//modify total excitation energy for the next residual species     
      }
  else
    {
      G4cout << "No decay process specified for the residual nucleus!" << G4endl;
    }
  
  //print cascade info
  for(int i=0;i<numDecays;i++)
  	{
  		//Print info
  		G4cout << "STEP " << i+1 << " OF THE CASCADE" << G4endl << "Residual lifetime: " << residual[i]->GetPDGLifeTime()/ns << " ns" << G4endl << "Initial excitation energy: " << ((G4Ions*)residual[i])->GetExcitationEnergy()/keV << " keV" << G4endl << "Gamma decay energy: " << ResDec[i]->GetEGamma()/keV << " keV" << G4endl << "Final excitation energy: " << ResDec[i]->GetDaughterExcitation()/keV << " keV" << G4endl;
  		//ResDecTab[i]->DumpInfo();
  		//residual[i]->GetProcessManager()->DumpInfo();
  	}

  G4cout << "---------- END OF DECAY PRODUCT SETUP ----------" << G4endl;

}
//---------------------------------------------------------
//Adds a decay to the residual nucleus gamma cascade.  Must be called before TargetFaceCrossSection()
void Reaction::AddDecay(G4double E,G4double T)
{
  if(numDecays<MAXNUMDECAYS)
    {
      Egamma[numDecays]=E;
      tau[numDecays]=T;
      numDecays++;
    }
  else
    {
      G4cout << "WARNING: Too many gammas added to the residual nucleus cascade, maximum number is " << MAXNUMDECAYS << " (change in Reaction.hh)." << G4endl;
      getc(stdin);
    }
}
//---------------------------------------------------------
//Computes an Exi value based on a Gaussian distribution with high energy exponential tail
G4double Reaction::getExi(G4double x0,G4double w,G4double tau)
{  
  G4double exi=CLHEP::RandGauss::shoot(x0,w);
  exi+=CLHEP::RandExponential::shoot(tau);  
  return exi;
}
