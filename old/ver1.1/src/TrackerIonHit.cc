
#include "TrackerIonHit.hh"

G4Allocator<TrackerIonHit> TrackerIonHitAllocator;


TrackerIonHit::TrackerIonHit() { flag=0;pflag=0;}



TrackerIonHit::~TrackerIonHit() {}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerIonHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(pos);
    circle.SetScreenSize(4);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,1.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerIonHit::Print()
{

  G4cout << std::setw(2)<< std::right <<flag<<" "<<pflag<<" "
   	     << std::setw(2)<< A<<" "
	  << std::setw(2)<< Z<<" "<<std::setw(7)
	  << std::setprecision(2)
	  <<std::setw(7)<< KE/MeV<<" "<<std::setprecision(5)
	  << beta<< " "<<std::setw(7)<<std::setprecision(4)<<std::right
   	     <<pos.getX()/mm<<" "<<std::setw(9)<<std::right
   	     <<pos.getY()/mm<<" "<<std::setw(9)<<std::right
   	     <<pos.getZ()/mm<<" "<<std::setw(9)<<std::right
   	     <<p.getX()/MeV<<" "<<std::setw(9)<<std::right
   	     <<p.getY()/MeV<<" "<<std::setw(9)<<std::right
	  <<p.getZ()/MeV<<" "<<std::setw(9)<<std::setprecision(6)<<std::right<<weight
   	     << G4endl;


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

