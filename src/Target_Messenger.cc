#include "Target_Messenger.hh"


Target_Messenger::Target_Messenger(Target* Tar)
:aTarget(Tar)
{ 
 
  DSAMTargetDir = new G4UIdirectory("/DSAMTarget/");
  DSAMTargetDir->SetGuidance("DSAM Target control.");
  
  TargetDir = new G4UIdirectory("/DSAMTarget/Target/");
  TargetDir->SetGuidance("Target control.");
 
  BackingDir = new G4UIdirectory("/DSAMTarget/Backing/");
  BackingDir->SetGuidance("Backing control.");
  
  TMatCmd = new G4UIcmdWithAString("/DSAMTarget/Target/Material",this);
  TMatCmd->SetGuidance("Select material for the target.");
  TMatCmd->SetParameterName("choice",false);
  TMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TMCmd = new G4UIcmdWithAnInteger("/DSAMTarget/Target/A",this);
  TMCmd->SetGuidance("Set the mass number A for the target");
  TMCmd->SetParameterName("choice",false);
  TMCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TQCmd = new G4UIcmdWithAnInteger("/DSAMTarget/Target/Z",this);
  TQCmd->SetGuidance("Set the atomic number Z for the target");
  TQCmd->SetParameterName("choice",false);
  TQCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TExCmd = new G4UIcmdWithADoubleAndUnit("/DSAMTarget/Target/Excitation",this);
  TExCmd->SetGuidance("Set energy for target recoil excitation");
  TExCmd->SetParameterName("choice",false);
  TExCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  TTauCmd = new G4UIcmdWithADoubleAndUnit("/DSAMTarget/Target/Lifetime",this);
  TTauCmd->SetGuidance("Set lifetime for target recoil excitation");
  TTauCmd->SetParameterName("choice",false);
  TTauCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TRCmd = new G4UIcmdWithADoubleAndUnit("/DSAMTarget/Target/Radius",this);
  TRCmd->SetGuidance("Select radius of the target");
  TRCmd->SetParameterName("choice",false);
  TRCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TZCmd = new G4UIcmdWithADoubleAndUnit("/DSAMTarget/Target/Thickness",this);
  TZCmd->SetGuidance("Select the thickness for the target");
  TZCmd->SetParameterName("choice",false);
  TZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TTarCmd = new G4UIcmdWithADouble("/DSAMTarget/Target/ThicknessMgCm2",this);
  TTarCmd->SetGuidance("Select the thickness for the target in mg/cm^2");
  TTarCmd->SetParameterName("choice",false);
  TTarCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  NTSCmd = new G4UIcmdWithAnInteger("/DSAMTarget/Target/NStep",this);
  NTSCmd->SetGuidance("Select the number of steps in the target");
  NTSCmd->SetParameterName("choice",false);
  NTSCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TRepCmd = new G4UIcmdWithoutParameter("/DSAMTarget/Target/Report",this);
  TRepCmd->SetGuidance("Report target and backing parameters");  

  BMatCmd = new G4UIcmdWithAString("/DSAMTarget/Backing/Material",this);
  BMatCmd->SetGuidance("Select material for the backing.");
  BMatCmd->SetParameterName("choice",false);
  BMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  BMCmd = new G4UIcmdWithAnInteger("/DSAMTarget/Backing/A",this);
  BMCmd->SetGuidance("Set the mass number A for the target");
  BMCmd->SetParameterName("choice",false);
  BMCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  BQCmd = new G4UIcmdWithAnInteger("/DSAMTarget/Backing/Z",this);
  BQCmd->SetGuidance("Set the atomic number Z for the backing");
  BQCmd->SetParameterName("choice",false);
  BQCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  BExCmd = new G4UIcmdWithADoubleAndUnit("/DSAMTarget/Backing/Excitation",this);
  BExCmd->SetGuidance("Set energy for backing recoil excitation");
  BExCmd->SetParameterName("choice",false);
  BExCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  BTauCmd = new G4UIcmdWithADoubleAndUnit("/DSAMTarget/Backing/Lifetime",this);
  BTauCmd->SetGuidance("Set lifetime for backing recoil excitation");
  BTauCmd->SetParameterName("choice",false);
  BTauCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  BRCmd = new G4UIcmdWithADoubleAndUnit("/DSAMTarget/Backing/Radius",this);
  BRCmd->SetGuidance("Select radius of the backing");
  BRCmd->SetParameterName("choice",false);
  BRCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  BZCmd = new G4UIcmdWithADoubleAndUnit("/DSAMTarget/Backing/Thickness",this);
  BZCmd->SetGuidance("Select the thickness for the backing");
  BZCmd->SetParameterName("choice",false);
  BZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  BTarCmd = new G4UIcmdWithADouble("/DSAMTarget/Backing/ThicknessMgCm2",this);
  BTarCmd->SetGuidance("Select the thickness for the backing in mg/cm^2");
  BTarCmd->SetParameterName("choice",false);
  BTarCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  BOCmd = new G4UIcmdWithADoubleAndUnit("/DSAMTarget/Backing/Offset",this);
  BOCmd->SetGuidance("Specify an offset for the backing (for use as a degrader)");
  BOCmd->SetParameterName("choice",false);
  BOCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  NBSCmd = new G4UIcmdWithAnInteger("/DSAMTarget/Backing/NStep",this);
  NBSCmd->SetGuidance("Select the number of steps in the backing");
  NBSCmd->SetParameterName("choice",false);
  NBSCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
 
  BRepCmd = new G4UIcmdWithoutParameter("/DSAMTarget/Backing/Report",this);
  BRepCmd->SetGuidance("Report target and backing parameters");  
}



Target_Messenger::~Target_Messenger()
{
  delete TRCmd;
  delete TZCmd;
  delete TMatCmd;
  delete TMCmd;
  delete TQCmd;
  delete TExCmd;
  delete TTarCmd;
  delete TTauCmd;
  delete BMCmd;
  delete BQCmd;
  delete BExCmd;
  delete BTauCmd;
  delete BRCmd;
  delete BZCmd;
  delete BTarCmd;
  delete BOCmd;
  delete BMatCmd;
  delete TargetDir;
  delete BackingDir;
  delete DSAMTargetDir;
  delete TRepCmd;
  delete BRepCmd;
  delete NTSCmd;
  delete NBSCmd;
}


void Target_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == TMatCmd )
   { aTarget->setTargetMaterial(newValue);} 

 if( command == TMCmd )
   { aTarget->setTargetMass(TMCmd->GetNewIntValue(newValue));}
 if( command == TQCmd )
   { aTarget->setTargetCharge(TQCmd->GetNewIntValue(newValue));}
  if( command == TExCmd )
   { aTarget->setTargetEx(TExCmd->GetNewDoubleValue(newValue));}
 if( command == TTauCmd )
   { aTarget->setTargetTau(TTauCmd->GetNewDoubleValue(newValue));}
 if( command == TTarCmd )
   { aTarget->SetTarThickness(TTarCmd->GetNewDoubleValue(newValue));}


 if( command == BMCmd )
   { aTarget->setBackingMass(BMCmd->GetNewIntValue(newValue));}
 if( command == BQCmd )
   { aTarget->setBackingCharge(BQCmd->GetNewIntValue(newValue));}
  if( command == BExCmd )
   { aTarget->setBackingEx(BExCmd->GetNewDoubleValue(newValue));}
 if( command == BTauCmd )
   { aTarget->setBackingTau(BTauCmd->GetNewDoubleValue(newValue));}

  if( command == TRCmd )
   { aTarget->setTargetR(TRCmd->GetNewDoubleValue(newValue));}
  if( command == TZCmd )
   { aTarget->setTargetZ(TZCmd->GetNewDoubleValue(newValue));}
  if( command == NTSCmd )
   { aTarget->setNTStep(NTSCmd->GetNewIntValue(newValue));}
 if( command == NBSCmd )
   { aTarget->setNBStep(NBSCmd->GetNewIntValue(newValue));}
  if( command == TRepCmd )
   { aTarget->Report();}
 if( command == BRepCmd )
   { aTarget->Report();}

  if( command == BMatCmd )
   { aTarget->setBackingMaterial(newValue);} 
  if( command == BRCmd )
   { aTarget->setBackingR(BRCmd->GetNewDoubleValue(newValue));}
  if( command == BZCmd )
   { aTarget->setBackingZ(BZCmd->GetNewDoubleValue(newValue));}
  if( command == BTarCmd )
   { aTarget->SetBacThickness(BTarCmd->GetNewDoubleValue(newValue));}
  if( command == BOCmd )
   { aTarget->setBackingOffset(BZCmd->GetNewDoubleValue(newValue));}

}

