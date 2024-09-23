
#ifndef TrackerCsISD_h
#define TrackerCsISD_h 1

#include "G4VSensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4VTouchable.hh"
#include <string.h>
#include <stdio.h>
#include "TrackerCsIHit.hh"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class G4Step;
class G4HCofThisEvent;


class TrackerCsISD : public G4VSensitiveDetector
{
  public:
      TrackerCsISD(G4String);
     ~TrackerCsISD();

  void SetPrint(){
    G4cout<<"----> CsI track data set to print at the end of event"<<G4endl;
    print=true;}
      void UnSetPrint(){
	G4cout<<"----> CsI track data set not to print at the end of event"<<G4endl;
	print=false;}

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);

      char name[132],s1[10],s2[10],s3[10];

  private:
      TrackerCsIHitsCollection* CsICollection;
      G4bool print;


};


#endif

