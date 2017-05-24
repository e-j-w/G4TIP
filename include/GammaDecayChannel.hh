// GammaDecayChannel is a modified version of Geant4.9.4's G4NuclearDecayChannel
// which only handles IT, but (probably) properly handles cascades.
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
#ifndef GammaDecayChannel_h
#define GammaDecayChannel_h 1

#include "globals.hh"
#include "G4VDecayChannel.hh"
#include "G4Ions.hh"
#include "G4IonTable.hh"
#include "G4DynamicParticle.hh"
#include "G4ParticleTable.hh"
#include "G4GeneralPhaseSpaceDecay.hh"
#include "G4RadioactiveDecayMode.hh"

//added by JW
#include "G4RandomDirection.hh"
#include "G4Gamma.hh"

#include <CLHEP/Random/RandGeneral.h>

using namespace CLHEP;

////////////////////////////////////////////////////////////////////////////////
//
class GammaDecayChannel : public G4GeneralPhaseSpaceDecay
{
  // class description 
  //
  //  GammaDecayChannel is a derived class from G4GeneralPhaseSpaceDecay,
  //  itself a derived class from G4VDecayChannel. It provides a
  //  decay channel for isomeric transitions, suitable for cascades 
  //  and through the DecayIt() member function returns the decay products.
  // 
  // class description - end
  
public: // with description

  GammaDecayChannel(const G4RadioactiveDecayMode&, G4int Verbose) :
    G4GeneralPhaseSpaceDecay(Verbose) {;}
  // default constructor
    
	GammaDecayChannel (G4int Verbose,
		const G4ParticleDefinition *theParentNucleus,
		G4double theBR, G4double Egamma,G4double EexcitInitial);
	//constructor for IT

  ~GammaDecayChannel(){;} 

  // destructor
  //
  G4DecayProducts* DecayIt(G4double theParentMass);
  // Returns the decay products
  //
  void SetHLThreshold(G4double hl) {halflifethreshold = hl;}
  // Set the half-life threshold for isomer production
  //
  void SetICM(G4bool icm) {applyICM = icm;}
  // Enable/disable ICM 
  //
  void SetARM (G4bool arm) {applyARM = arm;}
  // Enable/disable ARM
  // 
  inline G4RadioactiveDecayMode GetDecayMode () {return decayMode;}
  // Returns the decay mode
  //
  inline G4double GetDaughterExcitation () {return daughterExcitation;}
  // Returns the excitaion energy of the daughter nuclide
  //
  inline G4ParticleDefinition* GetDaughterNucleus () {return daughterNucleus;}
  // Returns the daughter nuclide.
  //
  
	G4double GetEGamma(){return E;}
	G4double E;
	
private:
  GammaDecayChannel(const G4String& theName, const G4String& theParentName,
                        G4double theBR, G4int theNumberOfDaughters,
                        const G4String theDaughterName1,
                        const G4String theDaughterName2,
                        const G4String theDaughterName3,
                        const G4String theDaughterName4);

  GammaDecayChannel(const G4String& theParentName,
                        G4double theBR, G4int theNumberOfDaughters,
                        const G4String& theDaughterName1,
                        const G4String& theDaughterName2 = "",
                        const G4String& theDaughterName3 = "");

  GammaDecayChannel(const G4String& theParentName,
                        G4double theParentMass, G4double theBR,
                        G4int theNumberOfDaughters,
                        const G4String& theDaughterName1,
                        const G4String& theDaughterName2 = "",
                        const G4String& theDaughterName3 = "");

  void FillDaughterNucleus(G4int index, G4int A, G4int Z,
                           G4double theDaughterExcitation);

  G4DecayProducts* BetaDecayIt();
  // to replace the ThreeBodyDecayIt() to generate the correct beta spectrum

protected:
  G4RadioactiveDecayMode decayMode;
  static const G4double  pTolerance;
  static const G4double  levelTolerance;
  G4double               daughterExcitation;
  G4int                  daughterA;
  G4int                  daughterZ;
  G4ParticleDefinition  *daughterNucleus;
  G4DynamicParticle     *dynamicDaughter;
  G4double               Qtransition;
  G4double               halflifethreshold;
  G4bool                 applyICM;
  G4bool                 applyARM;
  CLHEP::RandGeneral*    RandomEnergy;    
};
#endif



