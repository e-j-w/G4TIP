#include "Results_Messenger.hh"


Results_Messenger::Results_Messenger(Results* Res) :results(Res) 
{ 

  ResDir = new G4UIdirectory("/Results/");
  ResDir->SetGuidance("Output control.");

 
  TreDir = new G4UIdirectory("/Results/Tree/");
  TreDir->SetGuidance("Root tree control.");

  ProjDir = new G4UIdirectory("/Results/Projectile/");
  ProjDir->SetGuidance("Projectile spectra");

  GDir = new G4UIdirectory("/Results/Gamma/");
  GDir->SetGuidance("Gamma-ray spectra");

  PDir = new G4UIdirectory("/Results/PIN/");
  PDir->SetGuidance("PIN diode spectra");

  GRDir = new G4UIdirectory("/Results/Groups/");
  GRDir->SetGuidance("Gamma-ray - PIN detector grouping");
  

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

  //this is for the projectile spectra
  PLSACmd = new G4UIcmdWithoutParameter("/Results/Projectile/LabScatteringAngle",this);
  PLSACmd->SetGuidance("Examine projectile scattering angle in the lab frame");


  //this is for gamma-ray spectra
  GRSCmd = new G4UIcmdWithAnInteger("/Results/Gamma/RingSpectrum",this);
  GRSCmd->SetGuidance("Gamma-ray spectrum for a selected ring");  
  GRSCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  GRSCmd->SetDefaultValue(1);

 
  //this is for groups
  RCSPCmd = new G4UIcmdWithoutParameter("/Results/Groups/CalculateCrystalPositions",this);
  RCSPCmd->SetGuidance("Calculates position of TIGRESS crystals");

  RRSPCmd = new G4UIcmdWithoutParameter("/Results/Groups/ReportCrystalPositions",this);
  RRSPCmd->SetGuidance("Reports position of TIGRESS crystals");


}

Results_Messenger::~Results_Messenger()
{

  // this is for the directories
  delete ResDir;
  delete TreDir;
  delete ProjDir;
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
 
  //this is for gamma-ray spectrum
  delete GRSCmd;

  //this is for the groups
  delete RCSPCmd;
  delete RRSPCmd;
 
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


 //this is for gamma-ray spectra
 if( command == GRSCmd )
   { results->GammaRingSpectrum(GRSCmd->GetNewIntValue(newValue));}
 
 
 //this is for the groups
if( command == RCSPCmd )
    { results->CalculateCrystalPositions();}

 if( command == RRSPCmd )
    { results->ReportCrystalPositions();}




}
