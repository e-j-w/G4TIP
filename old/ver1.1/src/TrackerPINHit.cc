
#include "TrackerPINHit.hh"

G4Allocator<TrackerPINHit> TrackerPINHitAllocator;


TrackerPINHit::TrackerPINHit() {}



TrackerPINHit::~TrackerPINHit() {}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerPINHit::Draw()
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

void TrackerPINHit::Print()
{
  G4cout<<"  PIN diode hit - mass: "<<A<<" charge "<<Z<<
    "  energy deposit: " << G4BestUnit(KE,"Energy")
	<< "  position: " << G4BestUnit(pos,"Length") <<" id: "<<id<<" ring: "<<ring<<G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

