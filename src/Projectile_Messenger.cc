#include "Projectile_Messenger.hh"


Projectile_Messenger::Projectile_Messenger(Projectile* BI)
:theProjectile(BI)
{ 
 
  theProjectileDir = new G4UIdirectory("/Projectile/");
  theProjectileDir->SetGuidance("Incoming beam control.");

  fcDir = new G4UIdirectory("/Projectile/Focus/");
  fcDir->SetGuidance("Incoming beam focal point control.");
  
  ACmd = new G4UIcmdWithAnInteger("/Projectile/A",this);
  ACmd->SetGuidance("Select the mass number for the incoming beam.");
  ACmd->SetParameterName("Projectile A",false);
  ACmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ZCmd = new G4UIcmdWithAnInteger("/Projectile/Z",this);
  ZCmd->SetGuidance("Select the atomic number for the incoming beam.");
  ZCmd->SetParameterName("Projectile Z",false);
  ZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  KECmd = new G4UIcmdWithADoubleAndUnit("/Projectile/KE",this);
  KECmd->SetGuidance("Set kinetic energy for the incoming beam.");
  KECmd->SetParameterName("Projectile KE",false);
  KECmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fcXCmd = new G4UIcmdWithADoubleAndUnit("/Projectile/Focus/X",this);
  fcXCmd->SetGuidance("Set focal point X position for the incoming beam.");
  fcXCmd->SetParameterName("choice",false);
  fcXCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fcDXCmd = new G4UIcmdWithADoubleAndUnit("/Projectile/Focus/DX",this);
  fcDXCmd->SetGuidance("Set focal point DX size for the incoming beam.");
  fcDXCmd->SetParameterName("choice",false);
  fcDXCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fcYCmd = new G4UIcmdWithADoubleAndUnit("/Projectile/Focus/Y",this);
  fcYCmd->SetGuidance("Set focal point Y position for the incoming beam.");
  fcYCmd->SetParameterName("choice",false);
  fcYCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fcDYCmd = new G4UIcmdWithADoubleAndUnit("/Projectile/Focus/DY",this);
  fcDYCmd->SetGuidance("Set focal point DY size for the incoming beam.");
  fcDYCmd->SetParameterName("choice",false);
  fcDYCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fcZCmd = new G4UIcmdWithADoubleAndUnit("/Projectile/Focus/Z",this);
  fcZCmd->SetGuidance("Set focal point Z position for the incoming beam.");
  fcZCmd->SetParameterName("choice",false);
  fcZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  maxACmd = new G4UIcmdWithADoubleAndUnit("/Projectile/Focus/maxAta",this);
  maxACmd->SetGuidance("Angular divergence in the x direction for the incoming beam.");
  maxACmd->SetParameterName("choice",false);
  maxACmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  maxBCmd = new G4UIcmdWithADoubleAndUnit("/Projectile/Focus/maxBta",this);
  maxBCmd->SetGuidance("Angular divergence in the y direction for the incoming beam.");
  maxBCmd->SetParameterName("choice",false);
  maxBCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  RepCmd = new G4UIcmdWithoutParameter("/Projectile/Report",this);
  RepCmd->SetGuidance("Report parameters for the incoming beam");

  Ata0Cmd = new G4UIcmdWithADoubleAndUnit("/Projectile/Focus/Ata0",this);
  Ata0Cmd->SetGuidance("Set Ata angle on target for the incoming beam.");
  Ata0Cmd->SetParameterName("choice",false);
  Ata0Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  Bta0Cmd = new G4UIcmdWithADoubleAndUnit("/Projectile/Focus/Bta0",this);
  Bta0Cmd->SetGuidance("Set Bta angle on target for the incoming beam.");
  Bta0Cmd->SetParameterName("choice",false);
  Bta0Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
}



Projectile_Messenger::~Projectile_Messenger()
{
  delete maxACmd;
  delete maxBCmd;
  delete fcXCmd;
  delete fcYCmd;
  delete fcZCmd;
  delete fcDXCmd;
  delete fcDYCmd;
  delete KECmd;
  delete RepCmd;
  delete ZCmd;
  delete ACmd;
  delete Ata0Cmd;
  delete Bta0Cmd;
}


void Projectile_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 

  if( command == ACmd )
    { theProjectile->setA(ACmd->GetNewIntValue(newValue));}
  if( command == ZCmd )
    { theProjectile->setZ(ZCmd->GetNewIntValue(newValue));}
  if( command == KECmd )
    { theProjectile->setKE(KECmd->GetNewDoubleValue(newValue));}
  if( command == fcXCmd )
    { theProjectile->setfcX(fcXCmd->GetNewDoubleValue(newValue));}
  if( command == fcDXCmd )
    { theProjectile->setfcDX(fcDXCmd->GetNewDoubleValue(newValue));}
  if( command == fcYCmd )
    { theProjectile->setfcY(fcYCmd->GetNewDoubleValue(newValue));}
  if( command == fcDYCmd )
    { theProjectile->setfcDY(fcDYCmd->GetNewDoubleValue(newValue));}
  if( command == fcZCmd )
    { theProjectile->setfcZ(fcZCmd->GetNewDoubleValue(newValue));}
  if( command == maxACmd )
    { theProjectile->setmaxAta(maxACmd->GetNewDoubleValue(newValue));}
 if( command == maxBCmd )
    { theProjectile->setmaxBta(maxBCmd->GetNewDoubleValue(newValue));}
  if( command == Ata0Cmd )
    { theProjectile->setAta0(Ata0Cmd->GetNewDoubleValue(newValue));}
  if( command == Bta0Cmd )
    { theProjectile->setBta0(Bta0Cmd->GetNewDoubleValue(newValue));}
  if( command == RepCmd )
    { theProjectile->Report();}

}

