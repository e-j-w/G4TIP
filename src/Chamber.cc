#include "Chamber.hh"

Chamber::Chamber(G4LogicalVolume* experimentalHall_log,Materials* mat)
{
  materials=mat;
  expHall_log=experimentalHall_log;
  portOpening=2*cm;
  BTrmin=10.00*cm;
  BTrmax=10.15*cm;
  BTSPhi=0.*deg;
  BTDPhi=361*deg;
  BTSTheta=0.*deg;
  BTDTheta=181*deg; 
  Pos0 = new G4ThreeVector(0.,0.,0.);
  Chamber_Material = materials->FindMaterial("G4_Al");
}

Chamber::~Chamber()
{;}
//-----------------------------------------------------------------------------
G4VPhysicalVolume* Chamber::Construct()
{
  shell = new G4Sphere("shell",BTrmin,BTrmax,BTSPhi,BTDPhi,BTSTheta,BTDTheta);
  pipe= new G4Tubs("pipe",0.,portOpening,2.*(BTrmax+1),BTSPhi,BTDPhi);

  Chamber_shell=new G4SubtractionSolid("Chamber_shell",shell,pipe,G4Transform3D(G4RotationMatrix(),G4ThreeVector(0.*cm,0.*cm,0.*cm)));

  Chamber_log = new G4LogicalVolume(Chamber_shell,Chamber_Material,"Chamber_log",0,0,0);

  Chamber_phys = new G4PVPlacement(G4Transform3D(NoRot,*Pos0),
	  Chamber_log,"Chamber",expHall_log,false,0);

  //Visualization Attributes
  setInvisible();
 
  return Chamber_phys;
}
// //-----------------------------------------------------------------------------
// void Chamber::setRmin(G4double Rmin)
// {
//   if(Rmin<BTrmax)
//     {
//       BTrmin=Rmin;
//       G4cout<<"----> Chamber shell inner radius set to "<<G4BestUnit(BTrmin,"Length")<< G4endl;;
//       Chamber_shell->SetInsideRadius(BTrmin);
//     }
//   else
//     G4cout<<"----> inner radius "<<G4BestUnit(Rmin,"Length")<<" has to be smaller than the outer radius of "<<G4BestUnit(BTrmax,"Length")<<G4endl;
// }
// //-----------------------------------------------------------------------------
// void Chamber::setRmax(G4double Rmax)
// {
//   if(Rmax>BTrmin)
//     {
//       BTrmax=Rmax;
//       G4cout<<"----> Chamber shell outer radius set to "<<G4BestUnit(BTrmax,"Length")<< G4endl;;
//       Chamber_shell->SetOuterRadius(BTrmax);
//     }
//   else
//     G4cout<<"----> outer radius "<<G4BestUnit(Rmax,"Length")<<" has to be larger than the inner radius of "<<G4BestUnit(BTrmin,"Length")<<G4endl;
// }

//-----------------------------------------------------------------------------
void Chamber::Report()
{
//      BTrmin=Chamber_shell->GetInsideRadius();
//      BTrmax=Chamber_shell->GetOuterRadius();
     G4cout<<"----> Chamber shell material set to     "<<Chamber_Material->GetName()<< G4endl;     
     G4cout<<"----> Chamber shell inner radius set to "<<G4BestUnit(BTrmin,"Length")<< G4endl;
     G4cout<<"----> Chamber shell outer radius set to "<<G4BestUnit(BTrmax,"Length")<< G4endl;
     G4cout<<"----> Chamber position set to " <<"("<<Pos0->getX()/mm<<","<<Pos0->getY()/mm<<","<<Pos0->getZ()/mm<<") mm"<<G4endl;
}
//---------------------------------------------------------------------
void Chamber::setMaterial(G4String materialName)
{
  // search the material by its name 
  Chamber_Material = materials->FindMaterial(materialName);  
  Chamber_log->SetMaterial(Chamber_Material);
  G4cout<<"----> Chamber shell material set to     "<<Chamber_log->GetMaterial()->GetName()<< G4endl;                 
}
//-----------------------------------------------------------------------------
void Chamber::setInvisible()
{
  Chamber_log-> SetVisAttributes (G4VisAttributes::Invisible);
   G4cout<<"Chamber is invisible"<<G4endl;
}
//-----------------------------------------------------------------------------
void Chamber::setVisible()
{
  G4Colour lblue (0.0, 1.0, 1.0); 
  G4VisAttributes* Vis = new G4VisAttributes(lblue);
  Vis->SetVisibility(true);
  Vis->SetForceSolid(false);

  Chamber_log->SetVisAttributes(Vis);
  G4cout<<"Chamber is visible"<<G4endl;
}

//-----------------------------------------------------------------------------
void Chamber::SetPosZ(G4double z)
{
  G4ThreeVector P;
  Pos0->setZ(z);
  P.setX(Pos0->getX());
  P.setY(Pos0->getY());
  P.setZ(Pos0->getZ());
  Chamber_phys->SetTranslation(P);  
  G4cout<<"----> Chamber Z position set to "<<G4BestUnit(Chamber_phys->GetTranslation().getZ(),"Length")<<G4endl;
}

//-----------------------------------------------------------------------------
G4double Chamber::GetPosZ()
{
  G4ThreeVector P = Chamber_phys->GetTranslation();
  return P.getZ();
}
