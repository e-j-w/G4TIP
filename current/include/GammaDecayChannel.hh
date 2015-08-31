
#ifndef GammaDecayChannel_h
#define GammaDecayChannel_h 1

#include "globals.hh"
#include "G4NuclearDecayChannel.hh"
////////////////////////////////////////////////////////////////////////////////
//
class GammaDecayChannel : public G4NuclearDecayChannel 
{
  
  // class description 
  //
  //   Derived class from G4NuclearDecayChannel.  It is specific for
  //   Isomeric Transitions 
  //
  // class  description - end
  public:
    GammaDecayChannel (G4int Verbose,
                      const G4ParticleDefinition *theParentNucleus,
                      G4double theBR, G4double Egamma) :
      G4NuclearDecayChannel (IT, Verbose, theParentNucleus, theBR, Egamma,
			     theParentNucleus->GetBaryonNumber(),
			     int(theParentNucleus->GetPDGCharge()/eplus),
			     0,"gamma")
    {
#ifdef G4VERBOSE
      if (GetVerboseLevel()>1)
         G4cout <<"GammaDecayChannel constructor" << G4endl;
#endif
    }
    ~GammaDecayChannel () {;}
};
#endif

