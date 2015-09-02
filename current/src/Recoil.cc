#include "Recoil.hh"
#include "G4ProcessManager.hh"

Recoil::Recoil()
{
  RecoilA=12;
  RecoilZ=6;
  RecoilEx=0.*MeV;
  RecoilTau=0.*ns;
}

Recoil::~Recoil()
{
  ;
}

//-----------------------------------------------------------------------------
void Recoil::Report()
{
  G4cout<<"----> Recoil A set to              "<<RecoilA<< G4endl; 
  G4cout<<"----> Recoil Z set to              "<<RecoilZ<< G4endl; 
  G4cout<<"----> Recoil Ex set to             "<<RecoilEx/MeV<<" MeV"<< G4endl;
  G4cout<<"----> Recoil decay lifetime set to "<<RecoilTau/ns*1000.<<" ps "<< G4endl;
}


