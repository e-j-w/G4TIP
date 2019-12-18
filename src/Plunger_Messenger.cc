#include "Plunger_Messenger.hh"


Plunger_Messenger::Plunger_Messenger(Plunger* Plun)
:thePlunger(Plun)
{ 
  PlungerDir = new G4UIdirectory("/Plunger/");
  PlungerDir->SetGuidance("Plunger control.");
 
  StopperDir = new G4UIdirectory("/Plunger/Stopper/");
  StopperDir->SetGuidance("Stopper control.");

  TargetDir = new G4UIdirectory("/Plunger/Target/");
  TargetDir->SetGuidance("Target control.");

  BackingDir = new G4UIdirectory("/Plunger/Backing/");
  BackingDir->SetGuidance("Backing control.");

  PosCmd = new G4UIcmdWithADoubleAndUnit("/Plunger/SetZ",this);
  PosCmd->SetGuidance("Set the position of the plunger along the z (beam) axis");
  PosCmd->SetParameterName("choice",false);
  PosCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SepCmd = new G4UIcmdWithADoubleAndUnit("/Plunger/Separation",this);
  SepCmd->SetGuidance("Set the target/degrader separation");
  SepCmd->SetParameterName("choice",false);
  SepCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  MatDegCmd = new G4UIcmdWithAString("/Plunger/Stopper/Material",this);
  MatDegCmd->SetGuidance("Select material for the degrader.");
  MatDegCmd->SetParameterName("choice",false);
  MatDegCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ScDDegCmd = new G4UIcmdWithADouble("/Plunger/Stopper/ScaleDensity",this);
  ScDDegCmd->SetGuidance("Scale degrader density/stopping powers.");
  ScDDegCmd->SetParameterName("choice",false);
  ScDDegCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  RDegCmd = new G4UIcmdWithADoubleAndUnit("/Plunger/Stopper/Radius",this);
  RDegCmd->SetGuidance("Select the radius for the degrader");
  RDegCmd->SetParameterName("choice",false);
  RDegCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ZDegCmd = new G4UIcmdWithADoubleAndUnit("/Plunger/Stopper/Thickness",this);
  ZDegCmd->SetGuidance("Select the thickness for the degrader");
  ZDegCmd->SetParameterName("choice",false);
  ZDegCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  NSDegCmd = new G4UIcmdWithAnInteger("/Plunger/Stopper/NStep",this);
  NSDegCmd->SetGuidance("Select the number of steps in the degrader");
  NSDegCmd->SetParameterName("choice",false);
  NSDegCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  MatTarCmd = new G4UIcmdWithAString("/Plunger/Target/Material",this);
  MatTarCmd->SetGuidance("Select material for the target.");
  MatTarCmd->SetParameterName("choice",false);
  MatTarCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ATarCmd = new G4UIcmdWithAnInteger("/Plunger/Target/SetA",this);
  ATarCmd->SetGuidance("Set the mass number for the target reactant");
  ATarCmd->SetParameterName("choice",false);
  ATarCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ZTarCmd = new G4UIcmdWithAnInteger("/Plunger/Target/SetZ",this);
  ZTarCmd->SetGuidance("Set the atomic number for the target reactant");
  ZTarCmd->SetParameterName("choice",false);
  ZTarCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  RTarCmd = new G4UIcmdWithADoubleAndUnit("/Plunger/Target/Radius",this);
  RTarCmd->SetGuidance("Select the radius for the target");
  RTarCmd->SetParameterName("choice",false);
  RTarCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  XTarCmd = new G4UIcmdWithADoubleAndUnit("/Plunger/Target/Thickness",this);
  XTarCmd->SetGuidance("Select the thickness for the target");
  XTarCmd->SetParameterName("choice",false);
  XTarCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TTarCmd = new G4UIcmdWithADouble("/Plunger/Target/ThicknessMgCm3",this);
  TTarCmd->SetGuidance("Select the thickness for the target in mg/cm^3");
  TTarCmd->SetParameterName("choice",false);
  TTarCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  NSTarCmd = new G4UIcmdWithAnInteger("/Plunger/Target/NStep",this);
  NSTarCmd->SetGuidance("Select the number of steps in the target");
  NSTarCmd->SetParameterName("choice",false);
  NSTarCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  ScDTarCmd = new G4UIcmdWithADouble("/Plunger/Target/ScaleDensity",this);
  ScDTarCmd->SetGuidance("Scale target density/stopping powers.");
  ScDTarCmd->SetParameterName("choice",false);
  ScDTarCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  MatBckCmd = new G4UIcmdWithAString("/Plunger/Backing/Material",this);
  MatBckCmd->SetGuidance("Select material for the backing.");
  MatBckCmd->SetParameterName("choice",false);
  MatBckCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  RBckCmd = new G4UIcmdWithADoubleAndUnit("/Plunger/Backing/Radius",this);
  RBckCmd->SetGuidance("Select the radius for the backing");
  RBckCmd->SetParameterName("choice",false);
  RBckCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ZBckCmd = new G4UIcmdWithADoubleAndUnit("/Plunger/Backing/Thickness",this);
  ZBckCmd->SetGuidance("Select the thickness for the backing");
  ZBckCmd->SetParameterName("choice",false);
  ZBckCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  NSBckCmd = new G4UIcmdWithAnInteger("/Plunger/Backing/NStep",this);
  NSBckCmd->SetGuidance("Select the number of steps in the backing");
  NSBckCmd->SetParameterName("choice",false);
  NSBckCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  ScDBckCmd = new G4UIcmdWithADouble("/Plunger/Backing/ScaleDensity",this);
  ScDBckCmd->SetGuidance("Scale backing density/stopping powers.");
  ScDBckCmd->SetParameterName("choice",false);
  ScDBckCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  RepCmd = new G4UIcmdWithoutParameter("/Plunger/Report",this);
  RepCmd->SetGuidance("Report plunger parameters");  

}



Plunger_Messenger::~Plunger_Messenger()
{
 
  delete SepCmd;
  delete PosCmd;

  delete RDegCmd;
  delete ZDegCmd;
  delete NSDegCmd; 
  delete MatDegCmd;
  delete ScDDegCmd;

  delete RTarCmd;
  delete ATarCmd;
  delete ZTarCmd;
  delete XTarCmd;
  delete TTarCmd;
  delete NSTarCmd;
  delete MatTarCmd;
  delete ScDTarCmd;
 
  delete RBckCmd;
  delete ZBckCmd;
  delete NSBckCmd;
  delete MatBckCmd;
  delete ScDBckCmd;
 

  delete TargetDir;
  delete StopperDir;
  delete BackingDir;
  delete RepCmd;
 
}


void Plunger_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
 
  if( command == SepCmd )
   { thePlunger->SetSeparation(SepCmd->GetNewDoubleValue(newValue));} 
  if( command == PosCmd )
   { thePlunger->SetPosZ(PosCmd->GetNewDoubleValue(newValue));} 

  if( command == MatDegCmd )
   { thePlunger->SetDegMaterial(newValue);} 
  
 if( command == ScDDegCmd )
   { thePlunger->ScaleDegDensity(ScDDegCmd->GetNewDoubleValue(newValue));} 
  if( command == RDegCmd )
   { thePlunger->SetDegR(RDegCmd->GetNewDoubleValue(newValue));}
  if( command == ZDegCmd )
   { thePlunger->SetDegZ(ZDegCmd->GetNewDoubleValue(newValue));}
  if( command == NSDegCmd )
   { thePlunger->SetNstepDeg(NSDegCmd->GetNewIntValue(newValue));}

 if( command == ScDTarCmd )
   { thePlunger->ScaleTarDensity(ScDTarCmd->GetNewDoubleValue(newValue));} 
  if( command == MatTarCmd )
   { thePlunger->SetTarMaterial(newValue);} 
  if( command == RTarCmd )
   { thePlunger->SetTarR(RTarCmd->GetNewDoubleValue(newValue));}
  if( command == XTarCmd )
   { thePlunger->SetTarZ(XTarCmd->GetNewDoubleValue(newValue));}
  if( command == TTarCmd )
   { thePlunger->SetTarThickness(TTarCmd->GetNewDoubleValue(newValue));}
  if( command == NSTarCmd )
   { thePlunger->SetNstepTar(NSTarCmd->GetNewIntValue(newValue));}
  if( command == ATarCmd )
   { thePlunger->setTargetMass(ATarCmd->GetNewIntValue(newValue));}
  if( command == ZTarCmd )
   { thePlunger->setTargetCharge(ZTarCmd->GetNewIntValue(newValue));}

  

 if( command == ScDBckCmd )
   { thePlunger->ScaleBckDensity(ScDBckCmd->GetNewDoubleValue(newValue));} 
  if( command == MatBckCmd )
   { thePlunger->SetBckMaterial(newValue);} 
  if( command == RBckCmd )
   { thePlunger->SetBckR(RBckCmd->GetNewDoubleValue(newValue));}
  if( command == ZBckCmd )
   { thePlunger->SetBckZ(ZBckCmd->GetNewDoubleValue(newValue));}
  if( command == NSBckCmd )
   { thePlunger->SetNstepBck(NSBckCmd->GetNewIntValue(newValue));}

  if( command == RepCmd )
   { thePlunger->Report();}


}

