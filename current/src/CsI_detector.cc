#include "CsI_detector.hh"

CsI_detector::CsI_detector(G4LogicalVolume* experimentalHall_log,Materials* mat)
{
  materials=mat;
  expHall_log=experimentalHall_log;
  CsI_detector_side_x=14.7*mm;
  CsI_detector_side_y=16.2*mm;
  CsI_detector_thickness=3.0*mm;
  CsI_absorber_thickness=2.0*um;
  CsI_Material = materials->FindMaterial("CesiumIodide");
  CsI_absorber_Material = materials->FindMaterial("mylar");
  Pos = new G4ThreeVector(0.,0.,0.);
  Pos_abs = new G4ThreeVector(0.,0.,0.);
  Pos_abs->setZ(-CsI_detector_thickness/2.-CsI_absorber_thickness/2.);
}

CsI_detector::~CsI_detector()
{;}
//-----------------------------------------------------------------------------
G4VPhysicalVolume* CsI_detector::Construct()
{

  G4Box* xCsI_detector = new G4Box("xCsI",(CsI_detector_side_x-2.*CsI_absorber_thickness)/2.,(CsI_detector_side_y-2.*CsI_absorber_thickness)/2.,CsI_detector_thickness);
  aCsI_detector = new G4Box("xCsI",(CsI_detector_side_x-2.*CsI_absorber_thickness)/2.,(CsI_detector_side_y-2.*CsI_absorber_thickness)/2.,CsI_detector_thickness/2.);
  G4Box* xCsI_side_absorber = new G4Box("xCsIside",CsI_detector_side_x/2.,CsI_detector_side_y/2.,CsI_detector_thickness/2.);
  aCsI_absorber = new G4Box("CsIabsorber",CsI_detector_side_x/2.,CsI_detector_side_y/2.,CsI_absorber_thickness/2.);

  aCsI_side_absorber=new G4SubtractionSolid("CsIside",xCsI_side_absorber,xCsI_detector);
  CsI_detector_log = new G4LogicalVolume(aCsI_detector,CsI_Material,"CsI_log",0,0,0);
  CsI_absorber_log = new G4LogicalVolume(aCsI_absorber,CsI_absorber_Material,"CsI_absorber_log",0,0,0);
  CsI_side_absorber_log = new G4LogicalVolume(aCsI_side_absorber,CsI_absorber_Material,"CsI_side_absorber_log",0,0,0);
 
  CsI_detector_phys = new G4PVPlacement(G4Transform3D(NoRot,*Pos),CsI_detector_log,"CsI",expHall_log,true,0);
  CsI_absorber_phys = new G4PVPlacement(G4Transform3D(NoRot,*Pos_abs),CsI_absorber_log,"CsI_absorber",expHall_log,true,0);
  CsI_side_absorber_phys = new G4PVPlacement(G4Transform3D(NoRot,*Pos),CsI_side_absorber_log,"CsI_side_absorber",expHall_log,true,0);

  G4Colour red (1.0,1.0, 0.0); 
  G4VisAttributes* Vis_6 = new G4VisAttributes(red);
  Vis_6->SetVisibility(true);
  Vis_6->SetForceSolid(true);

  CsI_detector_log->SetVisAttributes(Vis_6);

  G4Colour blue (0.0,0.0, 1.0); 
  G4VisAttributes* Vis_7 = new G4VisAttributes(blue);
  Vis_7->SetVisibility(true);
  Vis_7->SetForceSolid(true);

  CsI_absorber_log->SetVisAttributes(Vis_7);
  CsI_side_absorber_log->SetVisAttributes(Vis_7);
 
  return CsI_detector_phys;
}


//-----------------------------------------------------------------------------
void CsI_detector::Report()
{
  G4cout<<"----> CsI_detector material set to     "<<CsI_detector_log->GetMaterial()->GetName()<< G4endl;   
  G4cout<<"----> CsI_detector side X is set to "<<G4BestUnit(2.*aCsI_detector->GetXHalfLength(),"Length")<<G4endl;
  G4cout<<"----> CsI_detector side Y is set to "<<G4BestUnit(2.*aCsI_detector->GetYHalfLength(),"Length")<<G4endl;  
   G4cout<<"----> CsI_detector thickness is set to "<<G4BestUnit(2.*aCsI_detector->GetZHalfLength(),"Length")<<G4endl;
 
}

//-----------------------------------------------------------------------------
void CsI_detector::Place(G4ThreeVector shift)
{
  G4ThreeVector shift_abs;
  shift_abs.setZ(-CsI_detector_thickness/2.-CsI_absorber_thickness/2.);
  shift_abs+=shift;
  CsI_detector_phys->SetTranslation(shift);
  CsI_side_absorber_phys->SetTranslation(shift);
  CsI_absorber_phys->SetTranslation(shift_abs);
  G4RunManager::GetRunManager()->GeometryHasBeenModified();  
}
//-----------------------------------------------------------------------------
void CsI_detector::setName()
{
  char s[20];
  sprintf(s,"CsI %3d %1d",Id,RingId);
  CsI_detector_phys->SetName(s);
  
}
