
#include "Projectile.hh"


Projectile::Projectile()
{
  A=18;
  Z=8;
  KE=100*MeV;
  fcX=0.*mm;
  fcDX=0.0*mm;
  fcY=0.*mm;
  fcDY=0.0*mm;
  fcZ=-100.*cm;
  maxAta=0*mrad;
  maxBta=0*mrad;
  ata0=0.*mrad;
  bta0=0.*mrad;
  f=new vector <G4double>;
  th=new vector <G4double>;
  for(G4int i=0;i<=18;i++)
    {
      th->push_back(0.);
      f->push_back(0.);
    }
}

Projectile::~Projectile()
{;}
//---------------------------------------------------------
void Projectile::Report()
{

  G4cout<<"----> Z of the projectile set to  "<<Z<< G4endl;
  G4cout<<"----> A of the projectile set to  "<<A<< G4endl;
  G4cout<<"----> Kin. En. of the projectile set to "<<KE/MeV<<" MeV"<<G4endl;
  G4cout<<"----> focal point X position for the projectile set to  "<<G4BestUnit(fcX,"Length")<< G4endl;
  G4cout<<"----> focal point DX size for the projectile set to  "<<G4BestUnit(fcDX,"Length")<< G4endl;
  G4cout<<"----> focal point Y position for the projectile set to  "<<G4BestUnit(fcY,"Length")<< G4endl;
  G4cout<<"----> focal point DY size for the projectile set to  "<<G4BestUnit(fcDY,"Length")<< G4endl;
  G4cout<<"----> focal point Z position for the projectile set to  "<<G4BestUnit(fcZ,"Length")<< G4endl;
  G4cout<<"----> angular divergence in the x direction for the projectile set to  "<<maxAta/mrad<<" mrad = "<<maxAta/deg<<" deg"<< G4endl;
  G4cout<<"----> angular divergence in the y direction for the projectile set to  "<<maxBta/mrad<<" mrad = "<<maxBta/deg<<" deg"<< G4endl;
}
//---------------------------------------------------------
void Projectile::setA(G4int Ain)
{

  A=Ain;
  G4cout<<"----> A of the projectile set to  "<<A<< G4endl;
  
}
//---------------------------------------------------------
void Projectile::setZ(G4int Zin)
{

  Z=Zin;
  G4cout<<"----> Z of the projectile set to  "<<Z<< G4endl;
  
}

//---------------------------------------------------------
void Projectile::setfcX(G4double d)
{

  fcX=d;
  G4cout<<"----> focal point X position for the projectile set to  "<<G4BestUnit(fcX,"Length")<< G4endl;
}
//---------------------------------------------------------
void Projectile::setfcDX(G4double d)
{

  fcDX=d;
  G4cout<<"----> focal point DX size for the projectile set to  "<<G4BestUnit(fcDX,"Length")<< G4endl;
}
//---------------------------------------------------------
void Projectile::setfcDY(G4double d)
{

  fcDY=d;
  G4cout<<"----> focal point DY size for the projectile set to  "<<G4BestUnit(fcDY,"Length")<< G4endl;
}
//---------------------------------------------------------
void Projectile::setfcY(G4double d)
{

  fcY=d;
  G4cout<<"----> focal point Y position for the projectile set to  "<<G4BestUnit(fcY,"Length")<< G4endl;
}
//---------------------------------------------------------
void Projectile::setfcZ(G4double d)
{

  fcZ=d;
  G4cout<<"----> focal point Z position for the projectile set to  "<<G4BestUnit(fcZ,"Length")<< G4endl;
}
//---------------------------------------------------------
void Projectile::setmaxAta(G4double d)
{

  maxAta=d;
  G4cout<<"----> angular divergence in the x direction for the projectile set to  "<<maxAta/mrad<<" mrad = "<<maxAta/deg<<" deg"<< G4endl;
}
//---------------------------------------------------------
void Projectile::setmaxBta(G4double d)
{

  maxBta=d;
  G4cout<<"----> angular divergence in the y direction for the projectile set to  "<<maxBta/mrad<<" mrad = "<<maxBta/deg<<" deg"<< G4endl;
}
//---------------------------------------------------------
void Projectile::setKE(G4double KEin)
{

  KE=KEin;
G4cout<<"----> Kin. En. of the projectile set to "<<
 G4BestUnit(KE,"Energy")<<G4endl;

}
//---------------------------------------------------------
G4ThreeVector Projectile::getDirection()
{
  G4ThreeVector direction;
  G4double x,y,z,a,b,r,phi;
  //  r1=G4UniformRand();
  //   r2=G4UniformRand();
  
  //   z=r1+cos(maxTh)*(1-r1);
  //   x=sqrt(1-z*z)*sin(2*pi*r2);
  //   y=sqrt(1-z*z)*cos(2*pi*r2);

  phi=G4UniformRand()*8.*atan(1.);
  r=G4UniformRand()+G4UniformRand();
  if(r>=1) r=-(r-2.);

  a=r*cos(phi)*maxAta;
  b=r*sin(phi)*maxBta; 
  z=1./sqrt(1.+tan(a)*tan(a)+tan(b)*tan(b));
  y=z*tan(b);
  x=z*tan(a);
  direction.setX(x);
  direction.setY(y);
  direction.setZ(z);
  direction.rotateY(ata0);
  direction.rotateX(-bta0);
  return direction;
  
}
//---------------------------------------------------------
G4ThreeVector Projectile::getPosition()
{
  G4ThreeVector position;
  G4double x,y;
  G4double r,phi;
  
  phi=G4UniformRand()*8.*atan(1.); //2*pi*random number
  r=G4UniformRand()+G4UniformRand();
  if(r>=1) r=-(r-2.);

 
  x=fcX+r*cos(phi)*fcDX/2.;
  y=fcY+r*sin(phi)*fcDY/2.;
 
  position.setX(x);
  position.setY(y);
  position.setZ(fcZ);
  return position;
  
}

