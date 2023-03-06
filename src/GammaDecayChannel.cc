//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// MODULES:              GammaDecayChannel.cc (Derived from G4NuclearDecayChannel.cc)
//
// Version:             0.b.4
// Date:                14/04/00
// Author:              F Lei & P R Truscott
// Organisation:        DERA UK
// Customer:            ESA/ESTEC, NOORDWIJK
// Contract:            12115/96/JG/NL Work Order No. 3
//
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// CHANGE HISTORY
// --------------
//
// 29 February 2000, P R Truscott, DERA UK
// 0.b.3 release.
//
// 18 October 2002, F Lei
//            modified link metheds in DecayIt() to G4PhotoEvaporation() in order to
//            use the new Internal Coversion feature.      
// 13 April 2000, F Lei, DERA UK
//            Changes made are:
//            1) Use PhotonEvaporation instead of DiscreteGammaDeexcitation
//            2) verbose control
//
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
///////////////////////////////////////////////////////////////////////////////
//
//#include "G4NuclearLevelManager.hh"
//#include "G4NuclearLevelStore.hh"
#include "GammaDecayChannel.hh"
#include "G4DynamicParticle.hh"
#include "G4DecayProducts.hh"
#include "G4DecayTable.hh"
#include "G4PhysicsLogVector.hh"
#include "G4ParticleChangeForRadDecay.hh"
#include "G4IonTable.hh"

#include "G4BetaFermiFunction.hh"
#include "G4PhotonEvaporation.hh"
#include "G4AtomicTransitionManager.hh"
#include "G4AtomicShell.hh"
#include "G4AtomicDeexcitation.hh"

#include "G4Gamma.hh"

const G4double GammaDecayChannel:: pTolerance = 0.001;
const G4double GammaDecayChannel:: levelTolerance = 2.0*keV;
//const G4bool GammaDecayChannel:: FermiOn = true;


///////////////////////////////////////////////////////////////////////////////
//
//
// Constructor for a daughter nucleus and a gamma ray (IT).
// Derived from G4NuclearDecayChannel constuctors by J. Williams 
//
GammaDecayChannel::GammaDecayChannel (G4int Verbose,
		const G4ParticleDefinition *theParentNucleus,
		G4double theBR, G4double Egamma,G4double EexcitInitial,G4int gammaDist) :
			G4GeneralPhaseSpaceDecay(Verbose), decayMode(IT)
{
#ifdef G4VERBOSE
  if (GetVerboseLevel()>1)
    {G4cout <<"GammaDecayChannel constructor for " <<G4int(IT) <<G4endl;}
#endif
	E=Egamma;
  SetParent (theParentNucleus);
  CheckAndFillParent();
  G4MT_parent_mass = theParentNucleus->GetPDGMass();
  SetBR (theBR);
  SetNumberOfDaughters (2);
  SetDaughter(0, "gamma");
  FillDaughterNucleus (1, theParentNucleus->GetBaryonNumber(), int(theParentNucleus->GetPDGCharge()/eplus), EexcitInitial-Egamma);
  Qtransition = Egamma;
  halflifethreshold = 1e-6*second;
  applyICM = true;
  applyARM = true;
  gammaAngDist = gammaDist;
}



////////////////////////////////////////////////////////////////////////////////
//
#include "G4HadTmpUtil.hh"

void GammaDecayChannel::FillDaughterNucleus (G4int index, G4int A, G4int Z,
  G4double theDaughterExcitation)
{
  //J. Williams: get rid of rounding errors resulting in negative numbers
  if((theDaughterExcitation<0.0)&&(theDaughterExcitation>-0.00001))
    theDaughterExcitation=0.0;
  //
  //
  // Determine if the proposed daughter nucleus has a sensible A, Z and excitation
  // energy.
  //
  if (A<1 || Z<0 || theDaughterExcitation <0.0)
  {
    G4cerr <<"Error in GammaDecayChannel::FillDaughterNucleus";
    G4cerr <<"Inappropriate values of daughter A, Z or excitation" <<G4endl;
    G4cerr <<"A = " <<A <<" and Z = " <<Z;
    G4cerr <<" Ex = " <<theDaughterExcitation*MeV  <<"MeV" <<G4endl;
    G4Exception(__FILE__, G4inttostring(__LINE__), FatalException, "GammaDecayChannel::FillDaughterNucleus");
  }
  //
  //
  // Save A and Z to local variables.  Find the GROUND STATE of the daughter
  // nucleus and save this, as an ion, in the array of daughters.
  //
  daughterA = A;
  daughterZ = Z;
  if (Z == 1 && A == 1) {
    daughterNucleus = G4Proton::Definition();
  } else if (Z == 0 && A == 1) {
    daughterNucleus = G4Neutron::Definition();
  } else {
    G4IonTable *theIonTable = G4IonTable::GetIonTable();
    daughterNucleus = theIonTable->GetIon(daughterZ, daughterA, theDaughterExcitation*MeV);
  }
  daughterExcitation = theDaughterExcitation;
  SetDaughter(index, daughterNucleus);
}


///////////////////////////////////////////////////////////////////////////////
//
//
//
//
G4DecayProducts *GammaDecayChannel::DecayIt (G4double theParentMass)
{
  //
  //
  // Load-up the details of the parent and daughter particles if they have not
  // been defined properly.
  //
  if (G4MT_parent == 0) CheckAndFillParent();
  if (G4MT_daughters == 0) CheckAndFillDaughters();
  //
  //
  // We want to ensure that the difference between the total
  // parent and daughter masses equals the energy liberated by the transition.
  //
  theParentMass = 0.0;
  for( G4int index=0; index < numberOfDaughters; index++)
    {theParentMass += G4MT_daughters[index]->GetPDGMass();}
  theParentMass += Qtransition;
  
#ifdef G4VERBOSE
  if (GetVerboseLevel()>1) {
    G4cout << "GammaDecayChannel::DecayIt "<< G4endl;
    G4cout << "the decay mass = " << theParentMass << G4endl;
  }
#endif

  SetParentMass (theParentMass);
  
  //
  //
  // Define a product vector.
  //
  G4DecayProducts *products = 0;
  //
  //
  // Depending upon the number of daughters, select the appropriate decay
  // kinematics scheme.
  //
  //G4cout << "Number of daughters: " << numberOfDaughters << G4endl;
  switch (numberOfDaughters)
    {
    case 2:
      products =  TwoBodyDecayIt(); //IT decays go here, see G4GeneralPhaseSpaceDecay
      break;
    default:
      G4cerr <<"Error in GammaDecayChannel::DecayIt" <<G4endl;
      G4cerr <<"Number of daughters in decay = " <<numberOfDaughters <<G4endl;
      G4Exception(__FILE__, G4inttostring(__LINE__), FatalException,  "GammaDecayChannel::DecayIt");
    }
  if (products == 0) {
    G4cerr << "GammaDecayChannel::DecayIt ";
    G4cerr << *parent_name << " can not decay " << G4endl;
    DumpInfo();
  }
  //
  // If the decay is to an excited state of the daughter nuclide, we need
  // to apply the photo-evaporation process. This includes the IT decay mode itself.
  //
  /*G4ThreeVector dir=G4RandomDirection();
  G4double theta=dir.getTheta()*180./3.14;
  G4cout << "angle: " << theta << G4endl;
  G4cout << "daughter excitation: " << daughterExcitation << G4endl;*/
  if (daughterExcitation > 0.0) 
    {
      //
      // Pop the daughter nucleus off the product vector - we need to retain
      // the momentum of this particle.
      //
      dynamicDaughter = products->PopProducts();
      G4LorentzVector daughterMomentum = dynamicDaughter->Get4Momentum();
      G4ThreeVector const daughterMomentum1(static_cast<const G4LorentzVector> (daughterMomentum));
      //
      //
      // Now define a G4Fragment with the correct A, Z and excitation, and declare and
      // initialise a G4PhotonEvaporation object.
      //   
      G4Fragment nucleus(daughterA, daughterZ, daughterMomentum);
      
      

	    G4DynamicParticle *theGammaRay = new G4DynamicParticle (G4Gamma::GammaDefinition(),G4RandomDirection(),Qtransition);//JW: just make one gamma ray at each step
      //theGammaRay -> SetProperTime(gammas->operator[](ig)->GetCreationTime());
      products->PushProducts (theGammaRay);
	    
			// now the nucleus
			//J. Williams: added this to produce excited daughter nucleus (needed for cascades)
			G4double finalDaughterExcitation=GetDaughterExcitation();
			//G4cout << "Daughter excitation: " << finalDaughterExcitation << ", parent mass: " << theParentMass<< G4endl;
			//
			// f.lei (03/01/03) this is needed to fix the crach in test18 
			if (finalDaughterExcitation <= 1.0*keV) finalDaughterExcitation = 0 ;

			//J. Williams: commented out since this breaks cascades
			//// f.lei (07/03/05) added the delete to fix bug#711
			//if (dynamicDaughter) delete dynamicDaughter;
			G4IonTable *theIonTable =  G4IonTable::GetIonTable();      
			dynamicDaughter = new G4DynamicParticle(theIonTable->GetIon(daughterZ,daughterA,finalDaughterExcitation),daughterMomentum1);
			products->PushProducts (dynamicDaughter);
		}
  
  if(gammaAngDist!=0){
    //do biasing
    for(int i=0;i<products->entries();i++){
      if(products->operator[](i)->GetDefinition()==G4Gamma::Definition()){
        //products->operator[](i)->DumpInfo();
        //G4cout <<  products->operator[](i)->GetMomentum().getTheta()*180./3.14 << G4endl;
        G4double angle = products->operator[](i)->GetMomentum().getTheta();
        G4double cosangle = cos(angle);
        //G4cout <<  cosangle << G4endl;
        G4double lpval = 0.;
        if(gammaAngDist==1)
          lpval = 0.5*(3.*cosangle*cosangle - 1.); //2nd order legendre polynomial
        else if(gammaAngDist==2)
          lpval = 0.125*(35.*cosangle*cosangle*cosangle*cosangle - 30.*cosangle*cosangle + 3.); //4th order legendre polynomial
        else if(gammaAngDist==3)
          lpval = 0.0625*(231.*cosangle*cosangle*cosangle*cosangle*cosangle*cosangle - 315.*cosangle*cosangle*cosangle*cosangle + 105.*cosangle*cosangle - 5.); //6th order legendre polynomial
        else
          G4cout << "WARNING: bad angular distribution!" << G4endl;
        //generate random number between -1 and 1 to bias legendre polynomial against 
        G4double num = CLHEP::RandFlat::shoot()*2.0;
        num=num-1.0;
        //G4cout <<  num << G4endl;
        if(num>lpval){
          //G4cout << "Biasing..." << G4endl;
          //remove everything from products
          //products->G4DecayProductVector.erase(i);
          for(int j=0;j<=products->entries();j++){
            products->PopProducts();
          }
          //G4cout << "entries left: " << products->entries() << G4endl;
          break;
        }
      }
    }
  }
  
  
	//getc(stdin);


  //G4cout << "Gamma decay done!" << G4endl;
  return products;
}


G4DecayProducts* GammaDecayChannel::BetaDecayIt()
{
  if (GetVerboseLevel()>1) G4cout << "G4Decay::BetaDecayIt()"<<G4endl;

  //daughters'mass
  G4double daughtermass[3];
  G4double sumofdaughtermass = 0.0;
  G4double pmass = GetParentMass();
  for (G4int index=0; index<3; index++)
    {
     daughtermass[index] = G4MT_daughters[index]->GetPDGMass();
     sumofdaughtermass += daughtermass[index];
    }

  //create parent G4DynamicParticle at rest
  G4ParticleMomentum dummy;
  G4DynamicParticle * parentparticle = new G4DynamicParticle( G4MT_parent, dummy, 0.0);

  //create G4Decayproducts
  G4DecayProducts *products = new G4DecayProducts(*parentparticle);
  delete parentparticle;

  G4double Q = pmass - sumofdaughtermass;  

  // faster method as suggested by Dirk Kruecker of FZ-Julich
  G4double daughtermomentum[3];
  G4double daughterenergy[3];
  // Use the histogram distribution to generate the beta energy
  daughterenergy[0] = RandomEnergy->shoot() * Q;
  daughtermomentum[0] = std::sqrt(daughterenergy[0]*daughterenergy[0] +
                        2.0*daughterenergy[0] * daughtermass[0]);

  // neutrino energy distribution is flat within the kinematical limits
  G4double rd = 2*G4UniformRand()-1;
  // limits
  G4double Mme=pmass-daughtermass[0];
  G4double K=0.5-daughtermass[1]*daughtermass[1]/(2*Mme*Mme-4*pmass*daughterenergy[0]);
	  
  daughterenergy[2]=K*(Mme-daughterenergy[0]+rd*daughtermomentum[0]);
  daughtermomentum[2] = daughterenergy[2] ; 
	  
  // the recoil nucleus
  daughterenergy[1] = Q-daughterenergy[0]-daughterenergy[2];
  G4double recoilmomentumsquared = daughterenergy[1]*daughterenergy[1] +
                             2.0*daughterenergy[1] * daughtermass[1];
  if (recoilmomentumsquared < 0.0) recoilmomentumsquared = 0.0;
  daughtermomentum[1] = std::sqrt(recoilmomentumsquared);
  
  // output message
  if (GetVerboseLevel()>1) {
    G4cout <<"     daughter 0:" <<daughtermomentum[0]/GeV <<"[GeV/c]" <<G4endl;
    G4cout <<"     daughter 1:" <<daughtermomentum[1]/GeV <<"[GeV/c]" <<G4endl;
    G4cout <<"     daughter 2:" <<daughtermomentum[2]/GeV <<"[GeV/c]" <<G4endl;
  }
  //create daughter G4DynamicParticle
  G4double costheta, sintheta, phi, sinphi, cosphi;
  G4double costhetan, sinthetan, phin, sinphin, cosphin;
  costheta = 2.*G4UniformRand()-1.0;
  sintheta = std::sqrt((1.0-costheta)*(1.0+costheta));
  phi  = twopi*G4UniformRand()*rad;
  sinphi = std::sin(phi);
  cosphi = std::cos(phi);
  G4ParticleMomentum direction0(sintheta*cosphi,sintheta*sinphi,costheta);
  G4DynamicParticle * daughterparticle
      = new G4DynamicParticle( G4MT_daughters[0], direction0*daughtermomentum[0]);
  products->PushProducts(daughterparticle);
    
  costhetan = (daughtermomentum[1]*daughtermomentum[1]-
               daughtermomentum[2]*daughtermomentum[2]-
               daughtermomentum[0]*daughtermomentum[0])/
        (2.0*daughtermomentum[2]*daughtermomentum[0]);
  // added the following test to avoid rounding erros. A problem
  // reported bye Ben Morgan of Uni.Warwick
  if (costhetan > 1.) costhetan = 1.;
  if (costhetan < -1.) costhetan = -1.;
  sinthetan = std::sqrt((1.0-costhetan)*(1.0+costhetan));
  phin  = twopi*G4UniformRand()*rad;
  sinphin = std::sin(phin);
  cosphin = std::cos(phin);
  G4ParticleMomentum direction2;
  direction2.setX(sinthetan*cosphin*costheta*cosphi - 
                  sinthetan*sinphin*sinphi + costhetan*sintheta*cosphi);
  direction2.setY(sinthetan*cosphin*costheta*sinphi +
                  sinthetan*sinphin*cosphi + costhetan*sintheta*sinphi);
  direction2.setZ(-sinthetan*cosphin*sintheta + costhetan*costheta);
  daughterparticle = new G4DynamicParticle(G4MT_daughters[2],
                          direction2*(daughtermomentum[2]/direction2.mag()));
  products->PushProducts(daughterparticle);
    
  daughterparticle =
    new G4DynamicParticle(G4MT_daughters[1],
                         (direction0*daughtermomentum[0] +
			  direction2*(daughtermomentum[2]/direction2.mag()))*(-1.0));
  products->PushProducts(daughterparticle);
  
  if (GetVerboseLevel()>1) {
    G4cout << "GammaDecayChannel::BetaDecayIt ";
    G4cout << "  create decay products in rest frame " <<G4endl;
    products->DumpInfo();
  }
  return products;
}
