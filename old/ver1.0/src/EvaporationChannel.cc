
#include "EvaporationChannel.hh"


EvaporationChannel::EvaporationChannel()
{
  theEntryRegionEnergy=8*MeV;
  theEntryRegionWidth=3*MeV;
  nN=0;
  nP=2;
  nA=0;
  Egamma=1473.54*keV;
  tau=0.00173*ns;
}

EvaporationChannel::~EvaporationChannel()
{;}
//---------------------------------------------------------
void EvaporationChannel::Report()
{

  
}


