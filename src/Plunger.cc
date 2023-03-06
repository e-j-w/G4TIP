#include "Plunger.hh"

/*********************************************
target, stopper and holder geometry based on
drawings OutRib-Foil2 and InRib-Foil2
**********************************************/

Plunger::Plunger(G4LogicalVolume* experimentalHall_log,Materials* mat)
{
  materials=mat;
  expHall_log=experimentalHall_log;

  // stopper
  Stopper_radius=9.017*mm;
  Stopper_thickness=0.001*mm;
  StopperA=197;
  StopperZ=79;
  // target
  Target_radius=6.477*mm;
  Target_thickness=0.001*mm;
  TargetA=1;
  TargetZ=1;
  // backing
  Backing_radius=6.477*mm;
  Backing_thickness=0.001*mm;

  Pos = new G4ThreeVector();
  Pos->setX(0.00*mm);
  Pos->setY(0.00*mm);
  Pos->setZ(0.00*mm);
  D=1.0*mm; // default separation

  // materials
  StopperMaterial = materials->FindMaterial("G4_Cu");
  TargetMaterial  = materials->FindMaterial("G4_Al");
  PlungerMaterial = materials->FindMaterial("G4_Galactic");
  PostMaterial    = materials->FindMaterial("G4_Galactic");
  BackingMaterial = materials->FindMaterial("G4_Galactic");

  NstepTar=50;
  NstepDeg=10;
  NstepBck=10;

  // holder thicknesses
  DHt=3.048*mm;
  DHFRingt=1.016*mm;
  THt=2.54*mm;

  // holder ring thicknesses
  DHRingt=2.54*mm;
  THRingt=3.048*mm;  
}

Plunger::~Plunger()
{}
//-----------------------------------------------------------------------------
void Plunger::Construct()
{
 theStopper = new G4Tubs("degrader",0.,Stopper_radius,Stopper_thickness/2.,-1.*deg,361.*deg);
 Stopper_log = new G4LogicalVolume(theStopper,StopperMaterial,"degrader_log",0,0,0);
 degrader_limits= new G4UserLimits();
 degrader_limits->SetMaxAllowedStep(Stopper_thickness/NstepDeg); 
 Stopper_log->SetUserLimits(degrader_limits);
 Stopper_phys = new G4PVPlacement(G4Transform3D(NoRot,*Pos),Stopper_log,"degrader",expHall_log,false,0,true);
 
 theTarget = new G4Tubs("target",0.,Target_radius,Target_thickness/2.,-1.*deg,361.*deg);
 Target_log = new G4LogicalVolume(theTarget,TargetMaterial,"target_log",0,0,0);
 target_limits= new G4UserLimits();
 target_limits->SetMaxAllowedStep(Target_thickness/NstepTar);
 Target_log->SetUserLimits(target_limits);
 Pos->setZ(-10*D);
 Target_phys = new G4PVPlacement(G4Transform3D(NoRot,*Pos),Target_log,"target",expHall_log,false,0,true);
 Pos->setZ(0.*mm);

 theBacking = new G4Tubs("backing",0.,Backing_radius,Backing_thickness/2.,-1.*deg,361.*deg);
 Backing_log = new G4LogicalVolume(theBacking,BackingMaterial,"backing_log",0,0,0);
 backing_limits= new G4UserLimits();
 backing_limits->SetMaxAllowedStep(Backing_thickness/NstepBck);
 Backing_log->SetUserLimits(backing_limits);
 Pos->setZ(-10*D-Target_thickness/2-Backing_thickness/2);
 Backing_phys = new G4PVPlacement(G4Transform3D(NoRot,*Pos),Backing_log,"backing",expHall_log,false,0,true);
 Pos->setZ(0.*mm);
 
 // degrader holder
 DHCone = new G4Cons("DHCone",9.017*mm,9.292*mm,9.017*mm,12.573*mm,DHt/2.,-1.*deg,361*deg);
 G4LogicalVolume *DHCone_log = new G4LogicalVolume(DHCone,PlungerMaterial,"DHCone_log",0,0,0);
 //DHCone_phys = new G4PVPlacement(G4Transform3D(NoRot,*Pos),DHCone_log,"DHCone",expHall_log,false,0,true);
 G4ThreeVector DHCone_Pos;
 DHCone_Pos.setX(Pos->getX());
 DHCone_Pos.setY(Pos->getY());
 DHCone_Pos.setZ(DHt/2.+Stopper_thickness/2.+0.0001*mm+Pos->getZ());
 DHCone_phys = new G4PVPlacement(G4Transform3D(NoRot,DHCone_Pos),DHCone_log,"DHCone",expHall_log,false,0,true);
 //DHCone_phys->SetTranslation(DHCone_Pos);

 // degrader frame ring
 DHFRing = new G4Tubs("DHFRing",12.573*mm,15.494*mm,DHFRingt/2.,-1.*deg,361*deg);
 G4LogicalVolume *DHFRing_log = new G4LogicalVolume(DHFRing,PlungerMaterial,"DHFRing_log",0,0,0);
 //DHFRing_phys = new G4PVPlacement(G4Transform3D(NoRot,*Pos),DHFRing_log,"DHFRing",expHall_log,false,0,true);
 G4ThreeVector DHFRing_Pos;
 DHFRing_Pos.setX(Pos->getX());
 DHFRing_Pos.setY(Pos->getY());
 DHFRing_Pos.setZ(DHt/2.+2.*DHFRingt+Stopper_thickness/2.+0.0001*mm+Pos->getZ());
 DHFRing_phys = new G4PVPlacement(G4Transform3D(NoRot,DHFRing_Pos),DHFRing_log,"DHFRing",expHall_log,false,0,true);
 //DHFRing_phys->SetTranslation(DHFRing_Pos);

 // degrader ring
 DHRing = new G4Tubs("DHRing",12.954*mm,15.494*mm,DHRingt/2.,-1*deg,361*deg);
 G4LogicalVolume *DHRing_log = new G4LogicalVolume(DHRing,PlungerMaterial,"DHRing_log",0,0,0);
 //DHRing_phys = new G4PVPlacement(G4Transform3D(NoRot,*Pos),DHRing_log,"DHRing",expHall_log,false,0,true);
 G4ThreeVector DHRing_Pos;
 DHRing_Pos.setX(Pos->getX());
 DHRing_Pos.setY(Pos->getY());
 DHRing_Pos.setZ(DHRingt/2.+Stopper_thickness/2.+0.0001*mm+Pos->getZ());
 DHRing_phys = new G4PVPlacement(G4Transform3D(NoRot,DHRing_Pos),DHRing_log,"DHRing",expHall_log,false,0,true);
 //DHRing_phys->SetTranslation(DHRing_Pos);

 G4RotationMatrix Rot0;
 Rot0.rotateZ(0*deg);
 G4RotationMatrix Rot1;
 Rot1.rotateZ(120*deg);
 G4RotationMatrix Rot2;
 Rot2.rotateZ(240*deg);

 // target holder
 THCone = new G4Cons("THCone",6.477*mm,9.017*mm,6.477*mm,6.752*mm,THt/2.,-1.*deg,361.*deg);
 G4LogicalVolume *THCone_log = new G4LogicalVolume(THCone,PlungerMaterial,"THCone_log",0,0,0); 
 //THCone_phys = new G4PVPlacement(G4Transform3D(NoRot,*Pos),THCone_log,"THCone",expHall_log,false,0,true); 
 G4ThreeVector THCone_Pos;
 THCone_Pos.setX(Pos->getX());
 THCone_Pos.setY(Pos->getY());
 THCone_Pos.setZ(Pos->getZ()-Target_thickness-Backing_thickness-Stopper_thickness/2.-D-0.0001*mm-THt/2.);
 THCone_phys = new G4PVPlacement(G4Transform3D(NoRot,THCone_Pos),THCone_log,"THCone",expHall_log,false,0,true);
 //THCone_phys->SetTranslation(THCone_Pos);

 // target ring
 THRing = new G4Tubs("THRing",6.477*mm,9.017*mm,THRingt/2.,-1*deg,361*deg);
 G4LogicalVolume *THRing_log = new G4LogicalVolume(THRing,PlungerMaterial,"THRing_log",0,0,0);
 //THRing_phys = new G4PVPlacement(G4Transform3D(NoRot,*Pos),THRing_log,"THRing",expHall_log,false,0,true);
 G4ThreeVector THRing_Pos;
 THRing_Pos.setX(Pos->getX());
 THRing_Pos.setY(Pos->getY());
 THRing_Pos.setZ(Pos->getZ()-Target_thickness-Backing_thickness-Stopper_thickness/2.-D-0.0001*mm-THt-THRingt/2.);
 THRing_phys = new G4PVPlacement(G4Transform3D(NoRot,THRing_Pos),THRing_log,"THRing",expHall_log,false,0,true);
 //THRing_phys->SetTranslation(THRing_Pos);

 // posts for target holder
 G4double TTh=45*deg;
 THPost = new G4Tubs("THPost",Target_radius-THt+tan(TTh)*THt,Target_radius+tan(TTh)*THt,4.*cm,60.*deg-THt/(Target_radius+tan(TTh)*THt)/2.,THt/(Target_radius+tan(TTh)*THt));
 G4LogicalVolume *THPost0_log = new G4LogicalVolume(THPost,PostMaterial,"THPost0_log",0,0,0);
 //THPost0_phys = new G4PVPlacement(G4Transform3D(Rot0,*Pos),THPost0_log,"THPost0",expHall_log,false,0,true);
 G4LogicalVolume *THPost1_log = new G4LogicalVolume(THPost,PostMaterial,"THPost1_log",0,0,0);
 //THPost1_phys = new G4PVPlacement(G4Transform3D(Rot1,*Pos),THPost1_log,"THPost1",expHall_log,false,0,true);
 G4LogicalVolume *THPost2_log = new G4LogicalVolume(THPost,PostMaterial,"THPost2_log",0,0,0); 
 //THPost2_phys = new G4PVPlacement(G4Transform3D(Rot2,*Pos),THPost2_log,"THPost2",expHall_log,false,0,true);
 G4ThreeVector THPost_Pos;
 THPost_Pos.setX(THRing_Pos.getX());
 THPost_Pos.setY(THRing_Pos.getY());
 THPost_Pos.setZ(THRing_Pos.getZ()-4*cm-THRingt/2.);
 THPost0_phys = new G4PVPlacement(G4Transform3D(Rot0,THPost_Pos),THPost0_log,"THPost0",expHall_log,false,0,true);
 THPost1_phys = new G4PVPlacement(G4Transform3D(Rot1,THPost_Pos),THPost1_log,"THPost1",expHall_log,false,0,true);
 THPost2_phys = new G4PVPlacement(G4Transform3D(Rot2,THPost_Pos),THPost2_log,"THPost2",expHall_log,false,0,true);
 //THPost0_phys->SetTranslation(THPost_Pos);
 //THPost1_phys->SetTranslation(THPost_Pos);
 //THPost2_phys->SetTranslation(THPost_Pos);

 // posts for degrader holder
 Rot0.rotateZ(45.*deg);
 Rot1.rotateZ(45.*deg);
 Rot2.rotateZ(45.*deg);
 DHPost = new G4Tubs("DHPost",12.954*mm-DHt+tan(TTh)*DHt,12.954*mm+tan(TTh)*DHt,4.*cm,60.*deg-DHt/(12.954*mm+tan(TTh)*DHt)/2.,DHt/(12.954*mm+tan(TTh)*DHt));
 G4LogicalVolume *DHPost0_log = new G4LogicalVolume(DHPost,PostMaterial,"DHPost0_log",0,0,0);
 //DHPost0_phys = new G4PVPlacement(G4Transform3D(Rot0,*Pos),DHPost0_log,"DHPost0",expHall_log,false,0,true);
 G4LogicalVolume *DHPost1_log = new G4LogicalVolume(DHPost,PostMaterial,"DHPost1_log",0,0,0);
 //DHPost1_phys = new G4PVPlacement(G4Transform3D(Rot1,*Pos),DHPost1_log,"DHPost1",expHall_log,false,0,true);
 G4LogicalVolume *DHPost2_log = new G4LogicalVolume(DHPost,PostMaterial,"DHPost2_log",0,0,0); 
 //DHPost2_phys = new G4PVPlacement(G4Transform3D(Rot2,*Pos),DHPost2_log,"DHPost2",expHall_log,false,0,true);
 G4ThreeVector DHPost_Pos;
 DHPost_Pos.setX(DHRing_Pos.getX());
 DHPost_Pos.setY(DHRing_Pos.getY());
 DHPost_Pos.setZ(DHRing_Pos.getZ()-4*cm-DHRingt/2.);
 DHPost0_phys = new G4PVPlacement(G4Transform3D(Rot0,DHPost_Pos),DHPost0_log,"DHPost0",expHall_log,false,0,true);
 DHPost1_phys = new G4PVPlacement(G4Transform3D(Rot1,DHPost_Pos),DHPost1_log,"DHPost1",expHall_log,false,0,true);
 DHPost2_phys = new G4PVPlacement(G4Transform3D(Rot2,DHPost_Pos),DHPost2_log,"DHPost2",expHall_log,false,0,true);
 //DHPost0_phys->SetTranslation(DHPost_Pos);
 //DHPost1_phys->SetTranslation(DHPost_Pos);
 //DHPost2_phys->SetTranslation(DHPost_Pos);
 
 G4Colour dgreen (0.0,0.6,0.0);
 G4VisAttributes* Vis = new G4VisAttributes(dgreen);
 Vis->SetVisibility(true);
 Vis->SetForceSolid(true); 
 Target_log->SetVisAttributes(Vis);

 G4Colour gold (0.831,0.686,0.216);
 G4VisAttributes* Vis_1 = new G4VisAttributes(gold);
 Vis_1->SetVisibility(true);
 Vis_1->SetForceSolid(true); 
 Stopper_log->SetVisAttributes(Vis_1); 

 G4Colour lblue (0.0,1.0,1.0); 
 G4VisAttributes* Vis_2 = new G4VisAttributes(lblue);
 Vis_2->SetVisibility(true);
 Vis_2->SetForceSolid(true);
 DHCone_log->SetVisAttributes(Vis_2); 
 DHFRing_log->SetVisAttributes(Vis_2); 
 DHRing_log->SetVisAttributes(Vis_2); 
 THCone_log->SetVisAttributes(Vis_2);
 THRing_log->SetVisAttributes(Vis_2);

 G4Colour orange (1.0,0.65,0); 
 G4VisAttributes* Vis_3 = new G4VisAttributes(orange);
 Vis_3->SetVisibility(true);
 Vis_3->SetForceSolid(true);
 THPost0_log->SetVisAttributes(Vis_3);
 THPost1_log->SetVisAttributes(Vis_3);
 THPost2_log->SetVisAttributes(Vis_3);
 DHPost0_log->SetVisAttributes(Vis_3);
 DHPost1_log->SetVisAttributes(Vis_3);
 DHPost2_log->SetVisAttributes(Vis_3);
 
 G4Colour blue (0.0,0.0,1.0); 
 G4VisAttributes* Vis_4 = new G4VisAttributes(blue);
 Vis_4->SetVisibility(false);
 Vis_4->SetForceSolid(true);
 Backing_log->SetVisAttributes(Vis_4);

 SetSeparation(D);
 }
//-----------------------------------------------------------------------------
void Plunger::SetSeparation(G4double d)
{
  D=d;
  G4ThreeVector Sep,Stop;
  Sep.setX(Pos->getX());
  Sep.setY(Pos->getY());
  Sep.setZ(Pos->getZ());

  // set degrader
  Stopper_phys->SetTranslation(Sep);

  // set target
  Sep.setZ(Pos->getZ()-(Target_thickness/2.+Stopper_thickness/2.+D));
  Target_phys->SetTranslation(Sep);

  // set degrader frame
  Sep.setZ(DHt/2.+Stopper_thickness/2.+0.0001*mm+Pos->getZ());
  DHCone_phys->SetTranslation(Sep);
  Sep.setZ(DHt/2.+2.*DHFRingt+Stopper_thickness/2.+0.0001*mm+Pos->getZ());
  DHFRing_phys->SetTranslation(Sep);  
  Sep.setZ(DHRingt/2.+Stopper_thickness/2.+0.0001*mm+Pos->getZ());
  DHRing_phys->SetTranslation(Sep);

  // set target frame
  Sep.setZ(Pos->getZ()-Target_thickness-Backing_thickness-Stopper_thickness/2.-D-0.0001*mm-THt/2.);
  THCone_phys->SetTranslation(Sep);

  //set target ring
  Sep.setZ(Pos->getZ()-Target_thickness-Backing_thickness-Stopper_thickness/2.-D-0.0001*mm-THt-THRingt/2.);
  THRing_phys->SetTranslation(Sep);


  //set target posts
  Sep.setZ(Sep.getZ()-4*cm-THRingt/2.);
  THPost0_phys->SetTranslation(Sep);
  THPost1_phys->SetTranslation(Sep);
  THPost2_phys->SetTranslation(Sep);

  //set degrader posts
  Sep.setZ(DHRingt/2.+Stopper_thickness/2.+0.0001*mm+Pos->getZ()-4*cm-DHRingt/2.);
  DHPost0_phys->SetTranslation(Sep);
  DHPost1_phys->SetTranslation(Sep);
  DHPost2_phys->SetTranslation(Sep);
  
  // set backing
  Sep.setZ(Pos->getZ()-(Backing_thickness/2.+Target_thickness+Stopper_thickness/2.+D));
  Backing_phys->SetTranslation(Sep);
  
  Sep=Target_phys->GetTranslation();
  Stop=Stopper_phys->GetTranslation();

  d=-Sep.getZ()+Stop.getZ()-Target_thickness/2.-Stopper_thickness/2.;

  G4RunManager::GetRunManager()->GeometryHasBeenModified();

 G4cout<<"----> Stopper/Target separation is set to "<<G4BestUnit(d,"Length")<<G4endl;
}
//-----------------------------------------------------------------------------
void Plunger::SetDegR(G4double X)
{
   Stopper_radius=X;
   theStopper->SetOuterRadius(X);
   G4RunManager::GetRunManager()->GeometryHasBeenModified();
   G4cout<<"----> Stopper radius is set to "<<G4BestUnit(theStopper->GetOuterRadius(),"Length")<<G4endl;
}

//-----------------------------------------------------------------------------
void Plunger::SetDegZ(G4double Z)
{
   Stopper_thickness=Z;
   theStopper->SetZHalfLength(Stopper_thickness/2.);
   degrader_limits->SetMaxAllowedStep(Stopper_thickness/NstepDeg);
   Stopper_log->SetUserLimits(degrader_limits);
   G4cout<<"----> Stopper thickness is set to "<<G4BestUnit(2.*theStopper->GetZHalfLength(),"Length")<<G4endl;
   SetSeparation(D);
}
//-----------------------------------------------------------------------------
void Plunger::SetTarR(G4double X)
{
   Target_radius=X;
   theTarget->SetOuterRadius(Target_radius);
   G4RunManager::GetRunManager()->GeometryHasBeenModified();
   G4cout<<"----> Target radius is set to "<<G4BestUnit(theTarget->GetOuterRadius(),"Length")<<G4endl;
}
//-----------------------------------------------------------------------------
G4double Plunger::GetTargetThickness()
{
  return 2.*theTarget->GetZHalfLength()/cm;
}
//-----------------------------------------------------------------------------
G4double Plunger::GetTargetNV(G4int Z)
{
  const G4ElementVector* theElementVector = Target_log->GetMaterial()->GetElementVector();
  const G4double* NbOfAtomsPerVolume = Target_log->GetMaterial()->GetVecNbOfAtomsPerVolume();
  const size_t NumberOfElements=Target_log->GetMaterial()->GetNumberOfElements();

  for ( size_t i=0 ; i < NumberOfElements ; i++ )
  {
    G4Element* element = (*theElementVector)[i];
  
    if(element->GetZ()==Z)
      return 1000.*NbOfAtomsPerVolume[i];//per cubic centimeter, factor of 1000 is unexpected but necessary
   }
  return 0.; 
}
//-----------------------------------------------------------------------------
void Plunger::SetTarZ(G4double Z)
{
   Target_thickness=Z;
   theTarget->SetZHalfLength(Target_thickness/2.);
   target_limits->SetMaxAllowedStep(Target_thickness/NstepTar);
   Target_log->SetUserLimits(target_limits);
   SetSeparation(D);
  G4cout<<"----> Target thickness is set to   "<<G4BestUnit(2.*theTarget->GetZHalfLength(),"Length")<<2.*theTarget->GetZHalfLength()/cm*Target_log->GetMaterial()->GetDensity()/g*cm3*1000<<" mg/cm^2"<<G4endl;
}
//-----------------------------------------------------------------------------
void Plunger::SetTarThickness(G4double Z)
{
  G4double density;
  Z/=1000.;
  Z*=g;
  Z/=cm2;
  density=Target_log->GetMaterial()->GetDensity();
  Target_thickness=Z/density;
  theTarget->SetZHalfLength(Target_thickness/2.);
  target_limits->SetMaxAllowedStep(Target_thickness/NstepTar);
  Target_log->SetUserLimits(target_limits);
  SetSeparation(D);
  G4cout<<"----> Target thickness is set to   "<<G4BestUnit(2.*theTarget->GetZHalfLength(),"Length")<<2.*theTarget->GetZHalfLength()/cm*Target_log->GetMaterial()->GetDensity()/g*cm3*1000<<" mg/cm^2"<<G4endl;
}
//-----------------------------------------------------------------------------
void Plunger::SetBckR(G4double X)
{
   Backing_radius=X;
   theBacking->SetOuterRadius(Backing_radius);
   G4RunManager::GetRunManager()->GeometryHasBeenModified();
   G4cout<<"----> Backing radius is set to "<<G4BestUnit(theBacking->GetOuterRadius(),"Length")<<G4endl;
}
//-----------------------------------------------------------------------------
void Plunger::SetBckZ(G4double Z)
{
   Backing_thickness=Z;
   theBacking->SetZHalfLength(Backing_thickness/2.);
   backing_limits->SetMaxAllowedStep(Backing_thickness/NstepBck);
   Backing_log->SetUserLimits(backing_limits);
   G4cout<<"----> Backing thickness is set to "<<G4BestUnit(2.*theBacking->GetZHalfLength(),"Length")<<G4endl;
   SetSeparation(D);
}
//-----------------------------------------------------------------------------
void Plunger::SetPosZ(G4double z)
{
  G4ThreeVector P;
  Pos->setZ(z);
  P.setX(Pos->getX());
  P.setY(Pos->getY());
  P.setZ(Pos->getZ());
  G4cout<<"----> Plunger Z position set to "<<G4BestUnit(Stopper_phys->GetTranslation().getZ(),"Length")<<G4endl;
  SetSeparation(D);
}

//-----------------------------------------------------------------------------
G4double Plunger::GetPosZ()
{
  G4ThreeVector P = Stopper_phys->GetTranslation();  
  // printf("P.getZ()/mm %f\n",P.getZ()/mm);
  // getc(stdin);
  return P.getZ();
}

//---------------------------------------------------------------------
void Plunger::SetDegMaterial(G4String materialName)
{
  // search the material by its name 
  StopperMaterial = materials->FindMaterial(materialName);  
  Stopper_log->SetMaterial(StopperMaterial);
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
  G4cout<<"----> Stopper material set to     "<<Stopper_log->GetMaterial()->GetName()<< G4endl; 
  G4cout<<"----> Stopper density  set to      "<<Stopper_log->GetMaterial()->GetDensity()/g*cm3<<" g/cm3"<<G4endl;            
}
//---------------------------------------------------------------------
void Plunger::SetTarMaterial(G4String materialName)
{
  // search the material by its name 
  TargetMaterial = materials->FindMaterial(materialName);  
  Target_log->SetMaterial(TargetMaterial);
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
  G4cout<<"----> Target material set to     "<<Target_log->GetMaterial()->GetName()<< G4endl;     
  G4cout<<"----> Target density  set to     "<<Target_log->GetMaterial()->GetDensity()/g*cm3<<" g/cm3"<<G4endl;            
}
//---------------------------------------------------------------------
void Plunger::SetBckMaterial(G4String materialName)
{
  // search the material by its name 
  BackingMaterial = materials->FindMaterial(materialName);  
  Backing_log->SetMaterial(BackingMaterial);
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
  G4cout<<"----> Backing material set to     "<<Backing_log->GetMaterial()->GetName()<< G4endl;
  G4cout<<"----> Backing density  set to     "<<Backing_log->GetMaterial()->GetDensity()/g*cm3<<" g/cm3"<<G4endl;            
}
//---------------------------------------------------------------------
void Plunger::ScaleTarDensity(G4double scale)
{
  // search the material by its name 
  G4String name=TargetMaterial->GetName();
  G4double Z=TargetMaterial->GetZ();
  G4double A=TargetMaterial->GetA();
  G4double density=TargetMaterial->GetDensity();
  density*=scale;
  TargetMaterial=new G4Material(name,Z,A,density);
  Target_log->SetMaterial(TargetMaterial);
  G4cout<<"----> Target material set to  "<<Target_log->GetMaterial()->GetName()<< G4endl;  
  G4cout<<"----> Target Z set to         "<<Target_log->GetMaterial()->GetZ()<< G4endl;  
  G4cout<<"----> Target mole mass set to "<<Target_log->GetMaterial()->GetA()/g*mole<<" g/mole"<< G4endl;  
  G4cout<<"----> Target density set to   "<<Target_log->GetMaterial()->GetDensity()/g*cm3<<" g/cm3"<< G4endl;     
}
//---------------------------------------------------------------------
void Plunger::ScaleDegDensity(G4double scale)
{
  // search the material by its name 
  G4String name=StopperMaterial->GetName();
  G4double Z=StopperMaterial->GetZ();
  G4double A=StopperMaterial->GetA();
  G4double density=StopperMaterial->GetDensity();
  density*=scale;
  StopperMaterial=new G4Material(name,Z,A,density);
  Stopper_log->SetMaterial(StopperMaterial);
  G4cout<<"----> Stopper material set to  "<<Stopper_log->GetMaterial()->GetName()<< G4endl;  
  G4cout<<"----> Stopper Z set to         "<<Stopper_log->GetMaterial()->GetZ()<< G4endl;  
  G4cout<<"----> Stopper mole mass set to "<<Stopper_log->GetMaterial()->GetA()/g*mole<<" g/mole"<< G4endl;  
  G4cout<<"----> Stopper density set to   "<<Stopper_log->GetMaterial()->GetDensity()/g*cm3<<" g/cm3"<< G4endl;     
}
//---------------------------------------------------------------------
void Plunger::ScaleBckDensity(G4double scale)
{
  // search the material by its name 
  G4String name=BackingMaterial->GetName();
  G4double Z=BackingMaterial->GetZ();
  G4double A=BackingMaterial->GetA();
  G4double density=BackingMaterial->GetDensity();
  density*=scale;
  BackingMaterial=new G4Material(name, Z,A,density);
  Backing_log->SetMaterial(BackingMaterial);
  G4cout<<"----> Backing material set to        "<<Backing_log->GetMaterial()->GetName()<< G4endl;  
  G4cout<<"----> Backing Z set to               "<<Backing_log->GetMaterial()->GetZ()<< G4endl;  
  G4cout<<"----> Backing mole mass set to       "<<Backing_log->GetMaterial()->GetA()/g*mole<<" g/mole"<< G4endl;  
  G4cout<<"----> Backing density set to         "<<Backing_log->GetMaterial()->GetDensity()/g*cm3<<" g/cm3"<< G4endl;
}

//-----------------------------------------------------------------------------
void Plunger::Report()
{
  G4cout<<"----> Stopper material set to     "<<Stopper_log->GetMaterial()->GetName()<< G4endl;  
  G4cout<<"----> Stopper Z set to            "<<Stopper_log->GetMaterial()->GetZ()<< G4endl;  
  // G4cout<<"----> Stopper A set to            "<<Stopper_log->GetMaterial()->GetA()<< G4endl;  
  G4cout<<"----> Stopper mole mass set to       "<<Stopper_log->GetMaterial()->GetA()/g*mole<<" g/mole"<< G4endl;  
  G4cout<<"----> Stopper density set to         "<<Stopper_log->GetMaterial()->GetDensity()/g*cm3<<" g/cm3"<< G4endl;     
  G4cout<<"----> Stopper radius is set to     "<<G4BestUnit(theStopper->GetOuterRadius(),"Length")<<G4endl;
  G4cout<<"----> Stopper thickness is set to "<<G4BestUnit(2.*theStopper->GetZHalfLength(),"Length")<<"  "<<2.*theStopper->GetZHalfLength()/cm*Stopper_log->GetMaterial()->GetDensity()/g*cm3*1000<<" mg/cm^2"<<G4endl;
  G4cout<<"----> Target material set to        "<<Target_log->GetMaterial()->GetName()<< G4endl;  
  if(Target_log->GetMaterial()->GetNumberOfElements()==1)
    {
      G4cout<<"----> Target Z set to               "<<Target_log->GetMaterial()->GetZ()<< G4endl;  
      // G4cout<<"----> Target A set to                "<<Target_log->GetMaterial()->GetA()<< G4endl;
    }  
  G4cout<<"----> Target density set to         "<<Target_log->GetMaterial()->GetDensity()/g*cm3<<" g/cm3"<< G4endl;           
  G4cout<<"----> Target radius is set to       "<<G4BestUnit(theTarget->GetOuterRadius(),"Length")<<G4endl;
  G4cout<<"----> Target thickness is set to   "<<G4BestUnit(2.*theTarget->GetZHalfLength(),"Length")<<2.*theTarget->GetZHalfLength()/cm*Target_log->GetMaterial()->GetDensity()/g*cm3*1000<<" mg/cm^2"<<G4endl;
  G4cout<<"----> Backing material set to        "<<Backing_log->GetMaterial()->GetName()<< G4endl;  
  G4cout<<"----> Backing Z set to               "<<Backing_log->GetMaterial()->GetZ()<< G4endl;  
  // G4cout<<"----> Backing A set to               "<<Backing_log->GetMaterial()->GetA()<< G4endl;  
  G4cout<<"----> Backing mole mass set to       "<<Backing_log->GetMaterial()->GetA()/g*mole<<" g/mole"<< G4endl;  
  G4cout<<"----> Backing density set to         "<<Backing_log->GetMaterial()->GetDensity()/g*cm3<<" g/cm3"<< G4endl;           
  G4cout<<"----> Backing radius is set to       "<<G4BestUnit(theBacking->GetOuterRadius(),"Length")<<G4endl;
  G4cout<<"----> Backing thickness is set to   "<<G4BestUnit(2.*theBacking->GetZHalfLength(),"Length")<<" "<<2.*theBacking->GetZHalfLength()/cm*Backing_log->GetMaterial()->GetDensity()/g*cm3*1000<<" mg/cm^2"<<G4endl;
   
 G4ThreeVector P;
 P=Stopper_phys->GetTranslation();
 G4cout<<"----> Plunger Z position set to "<<G4BestUnit(P.getZ(),"Length")<<G4endl;

 G4ThreeVector Sep;
 G4double d;

 Sep=Target_phys->GetTranslation();
 d=-Sep.getZ()+P.getZ()-theTarget->GetZHalfLength()-theStopper->GetZHalfLength();
 G4cout<<"----> Stopper/Target separation is set to "<<G4BestUnit(d,"Length")<<G4endl;
 d=P.getZ()-theStopper->GetZHalfLength();
 G4cout<<"----> Stopper back position at "<<d/um<<" um"<<G4endl;
 d=P.getZ()+theStopper->GetZHalfLength();
 G4cout<<"----> Stopper face position at "<<d/um<<" um"<<G4endl;
 d=Sep.getZ()+theTarget->GetZHalfLength();;
 G4cout<<"---->   Target back position at "<<d/um<<" um"<<G4endl;
 d=Sep.getZ()-theTarget->GetZHalfLength();
 G4cout<<"---->   Target face position at "<<d/um<<" um"<<G4endl;

 Sep=Backing_phys->GetTranslation();

 d=Sep.getZ()+theBacking->GetZHalfLength();;
 G4cout<<"---->   Backing back position at "<<d/um<<" um"<<G4endl;
 d=Sep.getZ()-theBacking->GetZHalfLength();
 G4cout<<"---->   Backing face position at "<<d/um<<" um"<<G4endl;
}
//-----------------------------------------------------------------------------
void Plunger::SetNstepTar(G4int n)
{
   NstepTar=n;
   target_limits->SetMaxAllowedStep(Target_thickness/NstepTar);
   Target_log->SetUserLimits(target_limits);
   G4cout<<"----> Number of simulation steps in the target is set to "<<NstepTar<<G4endl;
}
//-----------------------------------------------------------------------------
void Plunger::SetNstepDeg(G4int n)
{
   NstepDeg=n;
   degrader_limits->SetMaxAllowedStep(Stopper_thickness/NstepDeg);
   Stopper_log->SetUserLimits(degrader_limits);
   G4cout<<"----> Number of simulation steps in the stopper is set to "<<NstepDeg<<G4endl;
}
//-----------------------------------------------------------------------------
void Plunger::SetNstepBck(G4int n)
{
   NstepBck=n;
   backing_limits->SetMaxAllowedStep(Backing_thickness/NstepBck);
   Backing_log->SetUserLimits(backing_limits);
   G4cout<<"----> Number of simulation steps in the backing is set to "<<NstepBck<<G4endl;
}
