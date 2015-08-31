#include "TrackerIonSD_Messenger.hh"


TrackerIonSD_Messenger::TrackerIonSD_Messenger(TrackerIonSD* TISD)
:tracker(TISD) 
{ 
 
 
  PrtDir = new G4UIdirectory("/Print/");
  PrtDir->SetGuidance("Event by event print control for.");
  
  PrtSCmd = new G4UIcmdWithoutParameter("/Print/Track_Set",this);
  PrtSCmd->SetGuidance("Sets printing of track ion results.");

  PrtUCmd = new G4UIcmdWithoutParameter("/Print/Track_UnSet",this);
  PrtUCmd->SetGuidance("Un sets printing of track ion results.");

 
  
}



TrackerIonSD_Messenger::~TrackerIonSD_Messenger()
{
  
  delete PrtDir;
  delete PrtSCmd;
  delete PrtUCmd;
}



void TrackerIonSD_Messenger::SetNewValue(G4UIcommand* command,G4String)
{ 


  if( command == PrtSCmd )
    {tracker ->SetPrint();}

  if( command == PrtUCmd )
    {tracker ->UnSetPrint();}



}

