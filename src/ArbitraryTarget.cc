#include "ArbitraryTarget.hh"

ArbitraryTarget::ArbitraryTarget(G4LogicalVolume* experimentalHall_log,Materials* mat)
{
  materials=mat;
  expHall_log=experimentalHall_log;
  
  Pos = new G4ThreeVector(0.,0.,0.);
  
}

ArbitraryTarget::~ArbitraryTarget()
{ 
  for(int i=0;i<numTargetLayers;i++)
    delete target_limits[i];
}
//-----------------------------------------------------------------------------
void ArbitraryTarget::Construct()
{
  //setup default values
  Target_radius=6*mm;
  TargetEx=0.0*MeV;
  TargetTau=1e-9*ns;
  TargetExLayer=0;
  NTStep=20;
  numTargetLayers=0;

  //setup logical volumes (all of them needed by DetectorConstruction class)
  for(int i=0;i<NATARGETLAYERS;i++){
    Target_thickness[i]=1*um;
    TargetLayerPosition[i]=0.0*mm;
    TargetA[i]=0;
    char layerName[30];
    snprintf(layerName,30,"targetlayer%i",i);
    aTargetLayer[i] = new G4Tubs(layerName,0.,Target_radius,Target_thickness[i]/2.,-1.*deg,361.*deg);
    Target_log[i] = new G4LogicalVolume(aTargetLayer[i],TargetMaterial[i],layerName,0,0,0);
    setTargetMaterial(i,"G4_Galactic"); //by default, all layers are vacuum unless otherwise specified by the user
  }
  
}
//-----------------------------------------------------------------------------
// Add a layer to the target.  This does not set properties of the layer 
// (thickness, position, material, etc.), that must be done using the other 
// available methods.
//-----------------------------------------------------------------------------
G4VPhysicalVolume* ArbitraryTarget::AddLayer()
{

  if(numTargetLayers>=NATARGETLAYERS){
    G4cout << "ERROR: cannot exceed the maximum number of target layers (" << NATARGETLAYERS << ")." << G4endl;
    getc(stdin);
  }
  
  G4ThreeVector d;

  char layerName[30];
  snprintf(layerName,30,"targetlayer%i",numTargetLayers);

  target_limits[numTargetLayers] = new G4UserLimits();
  target_limits[numTargetLayers]->SetMaxAllowedStep(Target_thickness[numTargetLayers]/NTStep);
  Target_log[numTargetLayers]->SetUserLimits(target_limits[numTargetLayers]);
  Target_phys[numTargetLayers] = new G4PVPlacement(G4Transform3D(NoRot,*Pos),Target_log[numTargetLayers],layerName,expHall_log,false,0);
  d.setX(Pos->getX());
  d.setY(Pos->getY());
  d.setZ(Pos->getZ() + TargetLayerPosition[numTargetLayers] + 0.5*Target_thickness[numTargetLayers]);
  Target_phys[numTargetLayers]->SetTranslation(d);

  G4Colour layerCol(0.0+0.1*numTargetLayers,1.0-0.1*numTargetLayers,1.0-0.1*numTargetLayers); 
  G4VisAttributes* Vis_a = new G4VisAttributes(layerCol);
  Vis_a->SetVisibility(true);
  Vis_a->SetForceSolid(true);
  Target_log[numTargetLayers]->SetVisAttributes(Vis_a);
  
  numTargetLayers++;

  return Target_phys[numTargetLayers];
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
void ArbitraryTarget::setTargetPosition(G4int layer, G4double pos){
  if((layer<0)&&(layer>=NATARGETLAYERS)){
    G4cout << "ERROR: attempted to adjust position for invalid target layer (" << layer << ")" << G4endl;
    exit(-1);
  }
  TargetLayerPosition[layer]=pos;
  G4ThreeVector d;
  d.setX(Pos->getX());
  d.setY(Pos->getY());
  d.setZ(Pos->getZ() + TargetLayerPosition[layer] + 0.5*Target_thickness[layer]);
  Target_phys[layer]->SetTranslation(d);
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
  d.setZ(Pos->getZ() + TargetLayerPosition[layer] + 0.5*Target_thickness[layer]);
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
  if(TargetA[layer]<=0){
    TargetA[layer]=TargetMaterial[layer]->GetA();
  }
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
  if(n<=0){
    G4cout << "ERROR: invalid mass for target layer (" << layer << ")" << G4endl;
    exit(-1);
  }
  TargetA[layer]=n;
  G4cout << "----> Target layer " << layer << " mass number A set to " << TargetA[layer] << G4endl;  
}
//-----------------------------------------------------------------------------
void ArbitraryTarget::setTargetCharge(G4int layer, G4int n)
{
  if((layer<0)&&(layer>=NATARGETLAYERS)){
    G4cout << "ERROR: attempted to adjust charge for invalid target layer (" << layer << ")" << G4endl;
    exit(-1);
  }
  if(n<0){
    G4cout << "ERROR: invalid charge for target layer (" << layer << ")" << G4endl;
    exit(-1);
  }
  TargetZ[layer]=n;
  G4cout << "----> Target layer " << layer << " atomic number A set to " << TargetZ[layer] << G4endl;  
}
//-----------------------------------------------------------------------------
void ArbitraryTarget::setTargetExAndLayer(G4int layer, G4double x)
{
  if((layer<0)&&(layer>=NATARGETLAYERS)){
    G4cout << "ERROR: attempted to adjust excitation energy for invalid target layer (" << layer << ")" << G4endl;
    exit(-1);
  }
  TargetExLayer=layer;
  TargetEx=x;

  //reset names
  char layerName[30];
  for(int i=0;i<numTargetLayers;i++){
    snprintf(layerName,30,"targetlayer%i",i);
    Target_log[layer]->SetName(layerName);
  }
  Target_log[layer]->SetName("target_log"); //reaction classes use this name to determine where the reaction takes place
  
  G4cout << "----> Target layer " << layer << " set to be where the reaction will take place." << G4endl;
  if(TargetEx>0.)
    G4cout << "----> Target layer " << layer << " recoil excitation energy set to " << TargetEx/keV << " keV" << G4endl;
}
//-----------------------------------------------------------------------------
void ArbitraryTarget::setTargetTau(G4double x)
{
  TargetTau=x;
  G4cout << "----> Target recoil lifetime energy set to " << TargetTau/1000./ns << " ps" << G4endl;  
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
    G4cout << "ERROR: attempted to set thickness in mg/cm^2 for invalid target layer (" << layer << ")" << G4endl;
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
//-----------------------------------------------------------------------------
// Checks whether the requested layer in the target exists.
// If it does, return true.  If it doesn't, try to make new layers until it 
// does, and return true if successful.
// If the process fails, error out (the user should know).
//-----------------------------------------------------------------------------
bool ArbitraryTarget::CheckAndAddLayers(int reqLayer)
{
  if(reqLayer < numTargetLayers){
    return true;
  }else{
    if(reqLayer < NATARGETLAYERS){
      //make new layers as neccesary
      while(numTargetLayers < (reqLayer+1)){
        AddLayer();
      }
      return true;
    }else{
      G4cout << "ERROR: requested target layer (" << reqLayer+1 << ") is larger than the maximum number of allowed target layers (" << NATARGETLAYERS << ")." << G4endl;
      exit(-1);
    }
  }
  G4cout << "WARNING: should not be here (CheckAndAddLayers), please fix this!" << G4endl;
  getc(stdin);
  return false;
}
//-----------------------------------------------------------------------------
void ArbitraryTarget::setTargetExLayer(G4int layer){
  setTargetExAndLayer(layer,TargetEx);
}
//-----------------------------------------------------------------------------
void ArbitraryTarget::setTargetEx(G4double e){
  setTargetExAndLayer(TargetExLayer,e);
}
