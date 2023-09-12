#include "Target.hh"

Target::Target(G4LogicalVolume* experimentalHall_log,Materials* mat)
{
  materials=mat;
  expHall_log=experimentalHall_log;
  Target_radius=6*mm;
  Target_thickness=1*um;
  Backing_radius=6*mm;
  Backing_thickness=5*um;
  BackingZ=79;
  BackingA=197;
  BackingEx=547.5*keV;
  BackingTau=6.65/1000.*ns;//4.61 ps half life
  TargetZ=6;
  TargetA=40;
  TargetEx=4.43891*MeV;
  TargetTau=1e-9*ns;
  Pos = new G4ThreeVector(0.,0.,0.);
  TargetMaterial = materials->FindMaterial("Ca40");//calcium-40
  BackingMaterial = materials->FindMaterial("G4_Au");//gold
  NTStep=20;
  NBStep=20;
  fracReactionBacking=1.;
}

Target::~Target()
{ delete target_limits;}
//-----------------------------------------------------------------------------
G4VPhysicalVolume* Target::Construct()
{
  
  G4ThreeVector shift;

  aTarget = new G4Tubs("target",0.,Target_radius,Target_thickness/2.,-1.*deg,361.*deg);

  Target_log = new G4LogicalVolume(aTarget,TargetMaterial,"target_log",0,0,0);
  target_limits= new G4UserLimits();
  target_limits->SetMaxAllowedStep(Target_thickness/NTStep);
  Target_log->SetUserLimits(target_limits);
  Target_phys = new G4PVPlacement(G4Transform3D(NoRot,*Pos),Target_log,"target",expHall_log,false,0,true);
  shift.setX(0.);
  shift.setY(0.);
  shift.setZ(-0.5*Target_thickness);
  Target_phys->SetTranslation(shift);

  aBacking = new G4Tubs("backing",0.,Backing_radius,Backing_thickness/2.,-1.*deg,361.*deg);
  Backing_log = new G4LogicalVolume(aBacking,BackingMaterial,"backing_log",0,0,0);
  backing_limits= new G4UserLimits();
  backing_limits->SetMaxAllowedStep(Backing_thickness/NBStep);
  Backing_log->SetUserLimits(backing_limits);

  Backing_phys = new G4PVPlacement(G4Transform3D(NoRot,*Pos),Backing_log,"backing",expHall_log,false,0,true);
  shift.setZ(0.5*Backing_thickness);
  Backing_phys->SetTranslation(shift);

  G4Colour lightblue (0.0,1.0, 1.0); 
  G4VisAttributes* Vis_6 = new G4VisAttributes(lightblue);
  Vis_6->SetVisibility(true);
  Vis_6->SetForceSolid(true);
  Target_log->SetVisAttributes(Vis_6);

  G4Colour white (1.0,1.0,1.0); 
  G4VisAttributes* Vis_5 = new G4VisAttributes(white);
  Vis_5->SetVisibility(true);
  Vis_5->SetForceSolid(true);
  Backing_log->SetVisAttributes(Vis_5);
 
  return Target_phys;
}

//-----------------------------------------------------------------------------
void Target::setTargetR(G4double X)
{
   Target_radius=X;
   aTarget->SetOuterRadius(Target_radius);
   G4cout<<"----> Target radius is set to "<<G4BestUnit(2.*aTarget->GetOuterRadius(),"Length")<<G4endl;
   G4RunManager::GetRunManager()->GeometryHasBeenModified();
}
//-----------------------------------------------------------------------------
void Target::setBackingR(G4double X)
{
   Backing_radius=X;
   aBacking->SetOuterRadius(Backing_radius);
   G4cout<<"----> Backing radius is set to "<<G4BestUnit(2.*aBacking->GetOuterRadius(),"Length")<<G4endl;
   G4RunManager::GetRunManager()->GeometryHasBeenModified();
}
//-----------------------------------------------------------------------------
void Target::setTargetZ(G4double Z)
{
  G4ThreeVector d;
  Target_thickness=Z;
  aTarget->SetZHalfLength(Target_thickness/2.);
  d.setX(Pos->getX());
  d.setY(Pos->getY());
  d.setZ(Pos->getZ()-0.5*Z);
  Target_phys->SetTranslation(d);
  target_limits->SetMaxAllowedStep(Target_thickness/NTStep);
  Target_log->SetUserLimits(target_limits);
  G4cout<<"----> Target thickness is set to "<<G4BestUnit(2.*aTarget->GetZHalfLength(),"Length")<<G4endl;
   G4RunManager::GetRunManager()->GeometryHasBeenModified();
}
//-----------------------------------------------------------------------------
void Target::setBackingZ(G4double Z)
{
  G4ThreeVector d;
  Backing_thickness=Z;
  aBacking->SetZHalfLength(Backing_thickness/2.);
  d.setX(Pos->getX());
  d.setY(Pos->getY());
  d.setZ(Pos->getZ()+0.5*Z);
  Backing_phys->SetTranslation(d);
  backing_limits->SetMaxAllowedStep(Backing_thickness/NBStep);
  Backing_log->SetUserLimits(backing_limits);
  G4cout<<"----> Backing thickness is set to "<<G4BestUnit(2.*aBacking->GetZHalfLength(),"Length")<<G4endl;
   G4RunManager::GetRunManager()->GeometryHasBeenModified();
}
//-----------------------------------------------------------------------------
void Target::setBackingOffset(G4double Z)
{
  G4ThreeVector d;
  d.setX(Pos->getX());
  d.setY(Pos->getY());
  d.setZ(Pos->getZ() + 0.5*aBacking->GetZHalfLength() + Z);
  Backing_phys->SetTranslation(d);
  backing_limits->SetMaxAllowedStep(Backing_thickness/NBStep);
  Backing_log->SetUserLimits(backing_limits);
  G4cout<<"----> Backing offset set to "<< G4BestUnit(Backing_phys->GetTranslation().getZ(),"Length")<<G4endl;
   G4RunManager::GetRunManager()->GeometryHasBeenModified();
}
//-----------------------------------------------------------------------------
void Target::setNTStep(G4int n)
{
   NTStep=n;
   target_limits->SetMaxAllowedStep(Target_thickness/NTStep);
   Target_log->SetUserLimits(target_limits);
   G4cout<<"----> Number of simulation steps in the target is set to "<<NTStep<<G4endl;
}
//-----------------------------------------------------------------------------
void Target::setNBStep(G4int n)
{
   NBStep=n;
   backing_limits->SetMaxAllowedStep(Backing_thickness/NBStep);
   Backing_log->SetUserLimits(backing_limits);
   G4cout<<"----> Number of simulation steps in the backing is set to "<<NBStep<<G4endl;
}

//-----------------------------------------------------------------------------
void Target::Report()
{
  G4cout<<""<<G4endl;
  G4cout<<"---->                 Target material set to "<<Target_log->GetMaterial()->GetName()<< G4endl; 
  G4cout<<"---->            Target mass number A set to "<<TargetA<< G4endl; 
  G4cout<<"---->          Target atomic number Z set to "<<TargetZ<< G4endl; 
  G4cout<<"----> Target recoil excitation energy set to "<<TargetEx/keV<<" keV"<<G4endl;    
  G4cout<<"---->                Target radius is set to "<<G4BestUnit(aTarget->GetOuterRadius(),"Length")<<G4endl;
  G4cout<<"---->             Target thickness is set to "<<G4BestUnit(2.*aTarget->GetZHalfLength(),"Length")<<G4endl;
  G4cout<<"---->             Target density is set to "<<Target_log->GetMaterial()->GetDensity()/(g/cm3)<<" g/cm3."<<G4endl;
  G4cout<<"---->  Fraction of reaction on target set to "<<1.-fracReactionBacking<<G4endl;  
  G4cout<<"----> Number of simulation steps in the target is set to "<<NTStep<<G4endl;

  G4cout<<"---->                Backing material set to "<<Backing_log->GetMaterial()->GetName()<< G4endl;   
  G4cout<<"---->           Backing mass number A set to "<<BackingA<< G4endl; 
  G4cout<<"---->         Backing atomic number Z set to "<<BackingZ<< G4endl;  
  G4cout<<"---->Backing recoil excitation energy set to "<<BackingEx/keV<<" keV"<<G4endl;   
  G4cout<<"---->               Backing radius is set to "<<G4BestUnit(aBacking->GetOuterRadius(),"Length")<<G4endl;
  G4cout<<"---->            Backing thickness is set to "<<G4BestUnit(2.*aBacking->GetZHalfLength(),"Length")<<G4endl;
  G4cout<<"----> Fraction of reaction on backing set to "<<fracReactionBacking<<G4endl;  
  G4cout<<"----> Number of simulation steps in the backing is set to "<<NBStep<<G4endl;
}
//---------------------------------------------------------------------
void Target::setTargetMaterial(G4String materialName)
{
  // search the material by its name 
  TargetMaterial = materials->FindMaterial(materialName);  
  Target_log->SetMaterial(TargetMaterial);
  TargetZ=TargetMaterial->GetZ();
  TargetA=TargetMaterial->GetA();
  G4cout<<"----> Target material set to     "<<Target_log->GetMaterial()->GetName()<< G4endl;         
}
//---------------------------------------------------------------------
void Target::setBackingMaterial(G4String materialName)
{
  // search the material by its name 
  BackingMaterial = materials->FindMaterial(materialName);  
  Backing_log->SetMaterial(BackingMaterial);
  BackingZ=BackingMaterial->GetZ();
  BackingA=BackingMaterial->GetA();
  G4cout<<"----> Backing material set to     "<<Backing_log->GetMaterial()->GetName()<< G4endl;                 
}
//-------------------------------------------------------------------
void Target::setTargetReactionDepth(G4double depth)
{
  //  G4cout<<"\n----> The depht is "<<G4BestUnit(depth,"Length")<< G4endl;;
  target_limits->SetUserMinRange(depth);
}
//-------------------------------------------------------------------
void Target::setBackingReactionDepth(G4double depth)
{
  //  G4cout<<"\n----> The depht is "<<G4BestUnit(depth,"Length")<< G4endl;;
  backing_limits->SetUserMinRange(depth);
}
//-----------------------------------------------------------------------------
void Target::setTargetMass(G4int n)
{
  TargetA=n;
  G4cout<<"---->  Target mass number A set to "<<TargetA<< G4endl;  
}
//-----------------------------------------------------------------------------
void Target::setTargetCharge(G4int n)
{
  TargetZ=n;
  G4cout<<"---->Target atomic number A set to "<<TargetZ<< G4endl;  
}
//-----------------------------------------------------------------------------
void Target::setBackingMass(G4int n)
{
  BackingA=n;
  G4cout<<"---->  Backing mass number A set to "<<BackingA<< G4endl;  
}
//-----------------------------------------------------------------------------
void Target::setBackingCharge(G4int n)
{
  BackingZ=n;
  G4cout<<"---->Backing atomic number A set to "<<BackingZ<< G4endl;  
}
//-----------------------------------------------------------------------------
void Target::setBackingEx(G4double x)
{
  BackingEx=x;
  G4cout<<"---->Backing recoil excitation energy set to "<<BackingEx/keV<<" keV"<<G4endl;  
}
//-----------------------------------------------------------------------------
void Target::setTargetEx(G4double x)
{
  TargetEx=x;
  G4cout<<"---->Target recoil excitation energy set to "<<TargetEx/keV<<" keV"<<G4endl;  
}
//-----------------------------------------------------------------------------
void Target::setBackingTau(G4double x)
{
  BackingTau=x;
  G4cout<<"---->Backing recoil lifetime energy set to "<<BackingTau/1000./ns<<" ps"<<G4endl;  
}
//-----------------------------------------------------------------------------
void Target::setTargetTau(G4double x)
{
  TargetTau=x;
  G4cout<<"---->Target recoil lifetime energy set to "<<TargetTau/1000./ns<<" ps"<<G4endl;  
}
//-----------------------------------------------------------------------------
void Target::setFracReactionBacking(G4double x)
{
  if(x<0.) x=0.;
  if(x>1.) x=1.;
  fracReactionBacking=x;
  G4cout<<"---->Fraction of reaction on backing set to "<<fracReactionBacking<<G4endl;  
}
//-----------------------------------------------------------------------------
void Target::setFracReactionTarget(G4double x)
{
  x=1.-x;
  if(x<0.) x=0.;
  if(x>1.) x=1.;
  fracReactionBacking=x;
  G4cout<<"---->Fraction of reaction on target set to "<<1.-fracReactionBacking<<G4endl;  
}
//-----------------------------------------------------------------------------
G4double Target::GetTargetNV(G4int Z)
{
  const G4ElementVector* theElementVector = Target_log->GetMaterial()->GetElementVector();
  const G4double* NbOfAtomsPerVolume = Target_log->GetMaterial()->GetVecNbOfAtomsPerVolume();
  const size_t NumberOfElements=Target_log->GetMaterial()->GetNumberOfElements();

  for(size_t i=0; i < NumberOfElements; i++){
    const G4Element* element = (*theElementVector)[i];
    if(element->GetZ()==Z)
      return 1000.*NbOfAtomsPerVolume[i];//per cubic centimeter, factor of 1000 is unexpected but necessary
  }
  
  return 0.; 
}
//-----------------------------------------------------------------------------
void Target::SetTarThickness(G4double Z)
{
 
  G4double density;
  Z/=1000.;
  Z*=g;
  Z/=cm2;
  density=Target_log->GetMaterial()->GetDensity();
  Target_thickness=Z/density;
  aTarget->SetZHalfLength(Target_thickness/2.);
  G4ThreeVector shift;
  shift.setX(0.);
  shift.setY(0.);
  shift.setZ(-0.5*Target_thickness);
  Target_phys->SetTranslation(shift);
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
  target_limits->SetMaxAllowedStep(Target_thickness/NTStep);
  Target_log->SetUserLimits(target_limits);
  G4cout<<"----> Target thickness is set to   "<<G4BestUnit(2.*aTarget->GetZHalfLength(),"Length")<<2.*aTarget->GetZHalfLength()/cm*Target_log->GetMaterial()->GetDensity()/g*cm3*1000<<" mg/cm^2"<<G4endl;
}
//-----------------------------------------------------------------------------
void Target::SetBacThickness(G4double Z)
{
 
  G4double density;
  Z/=1000.;
  Z*=g;
  Z/=cm2;
  density=Backing_log->GetMaterial()->GetDensity();
  Backing_thickness=Z/density;
  aBacking->SetZHalfLength(Backing_thickness/2.);
  G4ThreeVector shift;
  shift.setX(0.);
  shift.setY(0.);
  shift.setZ(0.5*Backing_thickness);
  Backing_phys->SetTranslation(shift);
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
  backing_limits->SetMaxAllowedStep(Backing_thickness/NBStep);
  Backing_log->SetUserLimits(backing_limits);
  G4cout<<"----> Backing thickness is set to   "<<G4BestUnit(2.*aBacking->GetZHalfLength(),"Length")<<2.*aBacking->GetZHalfLength()/cm*Backing_log->GetMaterial()->GetDensity()/g*cm3*1000<<" mg/cm^2"<<G4endl;

}
