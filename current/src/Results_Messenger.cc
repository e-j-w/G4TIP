#include "Results_Messenger.hh"


Results_Messenger::Results_Messenger(Results* Res) :results(Res) 
{ 

  ResDir = new G4UIdirectory("/Results/");
  ResDir->SetGuidance("Output control.");

 
  TreDir = new G4UIdirectory("/Results/Tree/");
  TreDir->SetGuidance("Root tree control.");

  ProjDir = new G4UIdirectory("/Results/Projectile/");
  ProjDir->SetGuidance("Projectile spectra");
 
  RecDir = new G4UIdirectory("/Results/Recoil/");
  RecDir->SetGuidance("Recoil spectra");

  CSDir = new G4UIdirectory("/Results/CrossSection/");
  CSDir->SetGuidance("CrossSection spectra");

  GDir = new G4UIdirectory("/Results/Gamma/");
  GDir->SetGuidance("Gamma-ray spectra");

  PDir = new G4UIdirectory("/Results/CsI/");
  PDir->SetGuidance("CsI diode spectra");

  GRDir = new G4UIdirectory("/Results/Groups/");
  GRDir->SetGuidance("Gamma-ray - CsI detector grouping");
  

  TRepCmd = new G4UIcmdWithoutParameter("/Results/Tree/Report",this);
  TRepCmd->SetGuidance("Report parameters for the Root tree");

  TVCmd = new G4UIcmdWithoutParameter("/Results/Tree/View",this);
  TVCmd->SetGuidance("View and inspect the ROOT tree of simulated parameters");  
  TCCmd = new G4UIcmdWithoutParameter("/Results/Tree/Clear",this);
  TCCmd->SetGuidance("Clears the ROOT tree of simulated parameters");  

  TSCmd = new G4UIcmdWithAString("/Results/Tree/Save",this);
  TSCmd->SetGuidance("Save the ROOT tree of simulated parameters");
  TSCmd->SetParameterName("file name",false);
  TSCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  TSCmd->SetDefaultValue("test.root");

  // TRCmd = new G4UIcmdWithAString("/Results/Tree/Read",this);
  // TRCmd->SetGuidance("Read the ROOT tree of simulated parameters");
  // TRCmd->SetParameterName("file name",false);
  // TRCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  // TRCmd->SetDefaultValue("test.root");

  // TACmd = new G4UIcmdWithAString("/Results/Tree/Add",this);
  // TACmd->SetGuidance("Read tree entries from file and add them to the current ROOT tree of simulated parameters");
  // TACmd->SetParameterName("file name",false);
  // TACmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  // TACmd->SetDefaultValue("test.root");

  /*//this is for the projectile spectra
  PLSACmd = new G4UIcmdWithoutParameter("/Results/Projectile/LabScatteringAngle",this);
  PLSACmd->SetGuidance("Examine projectile scattering angle in the lab frame");

 //this is for the recoil spectra
  RLSACmd = new G4UIcmdWithoutParameter("/Results/Recoil/LabScatteringAngle",this);
  RLSACmd->SetGuidance("Examine recoil scattering angle in the lab frame");*/


 //this is for the cross section
  CSZCmd = new G4UIcmdWithoutParameter("/Results/CrossSection/ZProfile",this);
  CSZCmd->SetGuidance("Cross section vs. z profile");
  /*FCMCmd = new G4UIcmdWithoutParameter("/Results/CrossSection/FCM",this);
  FCMCmd->SetGuidance("Centre of mass f(theta) function for the gun conditions");*/

  //this is for gamma-ray spectra
  GRSCmd = new G4UIcmdWithAnInteger("/Results/Gamma/RingSpectrum",this);
  GRSCmd->SetGuidance("Gamma-ray spectrum for a selected ring");  
  GRSCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  GRSCmd->SetDefaultValue(1);

  DCPCmd = new G4UIcmdWith3Vector("/Results/Gamma/DetCryCsISpectrum",this);
  DCPCmd->SetGuidance("Gamma-ray spectrum for a selected detector, crystal and CsI");  
  DCPCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  G4ThreeVector v;
  v.setX(1);v.setY(0);v.setZ(1);
  DCPCmd->SetDefaultValue(v);
  DCPCmd->SetParameterName("Detector Id","Crystal Id","CsI Id",true,false);

  DRPRCmd = new G4UIcmdWith3Vector("/Results/Gamma/DetRingCsIRingSpectrum",this);
  DRPRCmd->SetGuidance("Gamma-ray spectrum for a selected detector and CsI rings");  
  DRPRCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  v.setX(1);v.setY(1);v.setZ(0);
  DRPRCmd->SetDefaultValue(v);
  DRPRCmd->SetParameterName("Detector Ring","CsI Ring","Unused",true,false);

  //this is for CsI diode spectra
  PRSCmd = new G4UIcmdWithAnInteger("/Results/CsI/RingSpectrum",this);
  PRSCmd->SetGuidance("CsI-diode spectrum for a selected ring");  
  PRSCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  PRSCmd->SetDefaultValue(1);

  //this is for groups
  RCSPCmd = new G4UIcmdWithoutParameter("/Results/Groups/CalculateCrystalPositions",this);
  RCSPCmd->SetGuidance("Calculates position of TIGRESS crystals");

  RRSPCmd = new G4UIcmdWithoutParameter("/Results/Groups/ReportCrystalPositions",this);
  RRSPCmd->SetGuidance("Reports position of TIGRESS crystals");

  PCSPCmd = new G4UIcmdWithoutParameter("/Results/Groups/CalculateCsIPositions",this);
  PCSPCmd->SetGuidance("Calculates position of CsI diodes");

  PRSPCmd = new G4UIcmdWithoutParameter("/Results/Groups/ReportCsIPositions",this);
  PRSPCmd->SetGuidance("Reports position of CsI diodes");

  RCSDCmd = new G4UIcmdWithoutParameter("/Results/Groups/CosineDistribution",this);
  RCSDCmd->SetGuidance("Histogram of cosines between CsI and TIGRESS crystals");

}

Results_Messenger::~Results_Messenger()
{

  // this is for the directories
  delete ResDir;
  delete TreDir;
  delete ProjDir;
  delete RecDir;
  delete CSDir;
  delete GDir;
  delete PDir;
  delete GRDir;
  // this is for the tree access
  delete TRCmd;
  delete TRepCmd;
  delete TVCmd;
  delete TSCmd;
  delete TACmd;
  delete TCCmd;
  //this is for the projectile spectra
 
  delete PLSACmd;
 //this is for the recoil spectra
  delete RLSACmd;

  //this is for the cross section
  delete CSZCmd;
  delete FCMCmd;
  //this is for gamma-ray spectrum
  delete GRSCmd;
  delete DCPCmd;
  delete DRPRCmd;
 //this is for CsI-diode spectrum
  delete PRSCmd;
  //this is for the groups
  delete RCSPCmd;
  delete RRSPCmd;
  delete PCSPCmd;
  delete PRSPCmd;
  delete RCSDCmd;
}



void Results_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 

  // this is for the tree access
 if( command == TRepCmd )
    { results->TreeReport();}

 if( command == TVCmd )
    { results->TreeView();}

 if( command == TCCmd )
    { results->TreeClear();}
 
 if( command == TSCmd )
    { results->TreeSave(newValue);}

 if( command == TRCmd )
    { results->TreeRead(newValue);}

 if( command == TACmd )
    { results->TreeAdd(newValue);}

 /*//this is for the projectile spectra
 if( command == PLSACmd )
    { results->ProjLabScattAngle();}

 //this is for the recoil spectra
 if( command == RLSACmd )
    { results->RecLabScattAngle();}*/

 //this is for the cross section
 if( command == CSZCmd )
    { results->CrossSectionZProfile();}
 /*if( command == FCMCmd )
   { results->TargetFaceF_CM();}*/
 //this is for gamma-ray spectra
 if( command == GRSCmd )
   { results->GammaRingSpectrum(GRSCmd->GetNewIntValue(newValue));}
 if( command == DCPCmd )
   { 
     G4ThreeVector v=DCPCmd->GetNew3VectorValue(newValue);
     G4int det=(G4int)v.getX();
     G4int seg=(G4int)v.getY();
     G4int pin=(G4int)v.getZ();
     results->DetCryCsIGammaSpectrum(det,seg,pin);
   }
 if( command == DRPRCmd )
   { 
     G4ThreeVector v=DCPCmd->GetNew3VectorValue(newValue);
     v=DRPRCmd->GetNew3VectorValue(newValue);
     G4int det=(G4int)v.getX();
     G4int pin=(G4int)v.getY();
     G4double coeff=(G4double)v.getZ();
     results->DetRingCsIRingGammaSpectrum(det,pin,coeff);
   }
 //this is for CsI-dide spectra
 if( command == PRSCmd )
   { results->CsIRingSpectrum(PRSCmd->GetNewIntValue(newValue));}
 //this is for the groups
if( command == RCSPCmd )
    { results->CalculateCrystalPositions();}

 if( command == RRSPCmd )
    { results->ReportCrystalPositions();}

if( command == PCSPCmd )
    { results->CalculateCsIPositions();}

 if( command == PRSPCmd )
    { results->ReportCsIPositions();}

 if( command == RCSDCmd )
    { results->GroupCosDist();}



}
