
#include "TrackerCsIHit.hh"

G4Allocator<TrackerCsIHit> TrackerCsIHitAllocator;


TrackerCsIHit::TrackerCsIHit() {}



TrackerCsIHit::~TrackerCsIHit() {}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerCsIHit::Draw()
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

void TrackerCsIHit::Print()
{
  G4cout<<"  CsI diode hit - mass: "<<A<<" charge "<<Z<<
    "  energy deposit: " << G4BestUnit(KE,"Energy")
	<< "  position: " << pos/um  << " um  id: "<<id<<" ring: "<<ring<<G4endl;

  //G4BestUnit(pos,"Length") // is in cm, ions stop on the um length scale
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

