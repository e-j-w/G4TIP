#include "ArbitraryTarget.hh"

ArbitraryTarget::ArbitraryTarget(G4LogicalVolume* experimentalHall_log,Materials* mat)
{
  materials=mat;
  expHall_log=experimentalHall_log;
  Target_radius=6*mm;
  TargetEx=4.43891*MeV;
  TargetTau=1e-9*ns;
  for(int i=0;i<NATARGETLAYERS;i++){
    Target_thickness[i]=1*um;
    TargetZ[i]=20;
    TargetA[i]=40;
    TargetLayerPosition[i]=0.0*mm;
    TargetMaterial[i] = materials->FindMaterial("Ca");//carbon
  }
  TargetExLayer=0;
  Pos = new G4ThreeVector(0.,0.,0.);
  NTStep=20;
  numTargetLayers=0;
}

ArbitraryTarget::~ArbitraryTarget()
{ 
  for(int i=0;i<numTargetLayers;i++)
    delete target_limits[i];
}
//-----------------------------------------------------------------------------
G4VPhysicalVolume* ArbitraryTarget::Construct()
{
  
  G4ThreeVector shift;

  aTargetLayer[0] = new G4Tubs("targetlayer0",0.,Target_radius,Target_thickness[0]/2.,-1.*deg,361.*deg);

  Target_log[0] = new G4LogicalVolume(aTargetLayer[0],TargetMaterial[0],"target_log",0,0,0);
  target_limits[0] = new G4UserLimits();
  target_limits[0]->SetMaxAllowedStep(Target_thickness[0]/NTStep);
  Target_log[0]->SetUserLimits(target_limits[0]);
  Target_phys[0] = new G4PVPlacement(G4Transform3D(NoRot,*Pos),Target_log[0],"targetlayer0",expHall_log,false,0);
  shift.setX(0.);
  shift.setY(0.);
  shift.setZ(-0.5*Target_thickness[0] + TargetLayerPosition[0]);
  Target_phys[0]->SetTranslation(shift);

  G4Colour lightblue (0.0,1.0, 1.0); 
  G4VisAttributes* Vis_6 = new G4VisAttributes(lightblue);
  Vis_6->SetVisibility(true);
  Vis_6->SetForceSolid(true);
  Target_log[0]->SetVisAttributes(Vis_6);

  numTargetLayers=1;
 
  return Target_phys[0];
}

//-----------------------------------------------------------------------------
void ArbitraryTarget::setTargetR(G4double X)
{
  Target_radius=X;
  for(int i=0;i<numTargetLayers;i++){
    aTargetLayer[i]->SetOuterRadius(Target_radius);
  }
  G4cout << "----> Target radius is set to " << G4BestUnit(2.*aTargetLayer[0]->GetOuterRadius(),"Length") << G4endl;
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}
//-----------------------------------------------------------------------------
void ArbitraryTarget::setTargetZ(G4int layer, G4double Z)
{
  if((layer<0)&&(layer>=NATARGETLAYERS)){
    G4cout << "ERROR: attempted to adjust thickness for invalid target layer (" << layer << ")" << G4endl;
    exit(-1);
  }
  G4ThreeVector d;
  Target_thickness[layer]=Z;
  aTargetLayer[layer]->SetZHalfLength(Target_thickness[layer]/2.);
  d.setX(Pos->getX());
  d.setY(Pos->getY());
  d.setZ(Pos->getZ() - 0.5*Z + TargetLayerPosition[layer]);
  Target_phys[layer]->SetTranslation(d);
  target_limits[layer]->SetMaxAllowedStep(Target_thickness[layer]/NTStep);
  Target_log[layer]->SetUserLimits(target_limits[layer]);
  G4cout << "----> Target layer " << layer << " thickness is set to "<<G4BestUnit(2.*aTargetLayer[layer]->GetZHalfLength(),"Length") << G4endl;
   G4RunManager::GetRunManager()->GeometryHasBeenModified();
}
//-----------------------------------------------------------------------------
void ArbitraryTarget::setNTStep(G4int n)
{
  NTStep=n;
  for(int i=0;i<numTargetLayers;i++){
    target_limits[i]->SetMaxAllowedStep(Target_thickness[i]/NTStep);
    Target_log[i]->SetUserLimits(target_limits[i]);
  }
  G4cout << "----> Number of simulation steps in the target is set to " << NTStep << G4endl;
}

//-----------------------------------------------------------------------------
void ArbitraryTarget::Report()
{
  G4cout<<""<<G4endl;
  for(int i=0;i<numTargetLayers;i++){
    G4cout << "----> Target layer " << i << ":" << G4endl;
    G4cout << "---->    material set to " <<Target_log[i]->GetMaterial()->GetName() << G4endl; 
    G4cout << "---->    mass number A set to " << TargetA[i] << G4endl; 
    G4cout << "---->    atomic number Z set to " << TargetZ[i] << G4endl;
    if(i==TargetExLayer)
      G4cout << "---->    recoil excitation energy set to " << TargetEx/keV << " keV" << G4endl;    
    G4cout << "---->    radius set to " << G4BestUnit(aTargetLayer[i]->GetOuterRadius(),"Length") << G4endl;
    G4cout << "---->    thickness set to " << G4BestUnit(2.*aTargetLayer[i]->GetZHalfLength(),"Length") << G4endl;
    G4cout << "---->    density set to " << Target_log[i]->GetMaterial()->GetDensity()/(g/cm3) << " g/cm3" << G4endl;
  }
  G4cout << "----> Number of simulation steps in the target is set to " << NTStep << G4endl;
}
//---------------------------------------------------------------------
void ArbitraryTarget::setTargetMaterial(G4int layer, G4String materialName)
{
  if((layer<0)&&(layer>=NATARGETLAYERS)){
    G4cout << "ERROR: attempted to adjust material for invalid target layer (" << layer << ")" << G4endl;
    exit(-1);
  }
  // search the material by its name 
  TargetMaterial[layer] = materials->FindMaterial(materialName);  
  Target_log[layer]->SetMaterial(TargetMaterial[layer]);
  TargetZ[layer]=TargetMaterial[layer]->GetZ();
  TargetA[layer]=TargetMaterial[layer]->GetA();
  G4cout << "----> Target layer " << layer << " material set to " << Target_log[layer]->GetMaterial()->GetName() << G4endl;         
}
//-------------------------------------------------------------------
void ArbitraryTarget::setTargetReactionDepth(G4int layer, G4double depth)
{
  if((layer<0)&&(layer>=NATARGETLAYERS)){
    G4cout << "ERROR: attempted to adjust material for invalid target layer (" << layer << ")" << G4endl;
    exit(-1);
  }
  target_limits[layer]->SetUserMinRange(depth);
}
//-----------------------------------------------------------------------------
void ArbitraryTarget::setTargetMass(G4int layer, G4int n)
{
  if((layer<0)&&(layer>=NATARGETLAYERS)){
    G4cout << "ERROR: attempted to adjust mass for invalid target layer (" << layer << ")" << G4endl;
    exit(-1);
  }
  TargetA[layer]=n;
  G4cout << "---->  Target layer " << layer << " mass number A set to " << TargetA[layer] << G4endl;  
}
//-----------------------------------------------------------------------------
void ArbitraryTarget::setTargetCharge(G4int layer, G4int n)
{
  if((layer<0)&&(layer>=NATARGETLAYERS)){
    G4cout << "ERROR: attempted to adjust charge for invalid target layer (" << layer << ")" << G4endl;
    exit(-1);
  }
  TargetZ[layer]=n;
  G4cout << "---->Target layer " << layer << " atomic number A set to " << TargetZ[layer] << G4endl;  
}
//-----------------------------------------------------------------------------
void ArbitraryTarget::setTargetEx(G4int layer, G4double x)
{
  if((layer<0)&&(layer>=NATARGETLAYERS)){
    G4cout << "ERROR: attempted to adjust excitation energy for invalid target layer (" << layer << ")" << G4endl;
    exit(-1);
  }
  TargetExLayer=layer;
  TargetEx=x;
  G4cout << "---->Target layer " << layer << " recoil excitation energy set to " << TargetEx/keV << " keV" << G4endl;
}
//-----------------------------------------------------------------------------
void ArbitraryTarget::setTargetTau(G4int layer, G4double x)
{
  if((layer<0)&&(layer>=NATARGETLAYERS)){
    G4cout << "ERROR: attempted to adjust lifetime for invalid target layer (" << layer << ")" << G4endl;
    exit(-1);
  }
  TargetExLayer=layer;
  TargetTau=x;
  G4cout << "---->Target layer " << layer << " recoil lifetime energy set to " << TargetTau/1000./ns << " ps" << G4endl;  
}
//-----------------------------------------------------------------------------
G4double ArbitraryTarget::GetTargetNV(G4int layer, G4int Z)
{
  if((layer<0)&&(layer>=NATARGETLAYERS)){
    G4cout << "ERROR: attempted to get NV for invalid target layer (" << layer << ")" << G4endl;
    exit(-1);
  }
  const G4ElementVector* theElementVector = Target_log[layer]->GetMaterial()->GetElementVector();
  const G4double* NbOfAtomsPerVolume = Target_log[layer]->GetMaterial()->GetVecNbOfAtomsPerVolume();
  const size_t NumberOfElements=Target_log[layer]->GetMaterial()->GetNumberOfElements();

  for ( size_t i=0 ; i < NumberOfElements ; i++ )
  {
    G4Element* element = (*theElementVector)[i];
  
    if(element->GetZ()==Z)
      return 1000.*NbOfAtomsPerVolume[i];//per cubic centimeter, factor of 1000 is unexpected but necessary
 
  }
  
   return 0.; 
}
//-----------------------------------------------------------------------------
void ArbitraryTarget::SetTarThickness(G4int layer, G4double Z)
{
  if((layer<0)&&(layer>=NATARGETLAYERS)){
    G4cout << "ERROR: attempted to set thickness for invalid target layer (" << layer << ")" << G4endl;
    exit(-1);
  }

  G4double density;
  Z/=1000.;
  Z*=g;
  Z/=cm2;
  density=Target_log[layer]->GetMaterial()->GetDensity();
  Target_thickness[layer]=Z/density;
  aTargetLayer[layer]->SetZHalfLength(Target_thickness[layer]/2.);
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
  target_limits[layer]->SetMaxAllowedStep(Target_thickness[layer]/NTStep);
  Target_log[layer]->SetUserLimits(target_limits[layer]);
  G4cout << "----> Target layer " << layer << " thickness is set to " << G4BestUnit(2.*aTargetLayer[layer]->GetZHalfLength(),"Length") << 2.*aTargetLayer[layer]->GetZHalfLength()/cm*Target_log[layer]->GetMaterial()->GetDensity()/g*cm3*1000 << " mg/cm^2" << G4endl;
}
