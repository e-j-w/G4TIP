#include "TrackerCsISD_Messenger.hh"


TrackerCsISD_Messenger::TrackerCsISD_Messenger(TrackerCsISD* TCSD)
:tracker(TCSD) 
{ 
 
 
  PrtDir = new G4UIdirectory("/Print/");
  PrtDir->SetGuidance("Event by event print control for.");
  
  PrtSCmd = new G4UIcmdWithoutParameter("/Print/CsI_Track_Set",this);
  PrtSCmd->SetGuidance("Sets printing of track CsI results.");

  PrtUCmd = new G4UIcmdWithoutParameter("/Print/CsI_Track_UnSet",this);
  PrtUCmd->SetGuidance("Un sets printing of track CsI results.");

 
  
}



TrackerCsISD_Messenger::~TrackerCsISD_Messenger()
{
  
  delete PrtDir;
  delete PrtSCmd;
  delete PrtUCmd;
}



void TrackerCsISD_Messenger::SetNewValue(G4UIcommand* command,G4String)
{ 


  if( command == PrtSCmd )
    {tracker ->SetPrint();}

  if( command == PrtUCmd )
    {tracker ->UnSetPrint();}



}

