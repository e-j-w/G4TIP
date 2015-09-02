#include "CsI_array.hh"

CsI_array::CsI_array(G4LogicalVolume* experimentalHall_log,Materials* mat)
{
  //zpos=5.7*mm;
  //zpos=28.7*mm;
  zpos=51.7*mm;
  materials=mat;
  expHall_log=experimentalHall_log;
  id[ 0]= 1;pos[ 0].setX( 15.2*mm);pos[ 0].setY( 00.0*mm);pos[ 0].setZ(zpos);ring[ 0]=1;
  id[ 1]= 2;pos[ 1].setX( 15.2*mm);pos[ 1].setY( 16.7*mm);pos[ 1].setZ(zpos);ring[ 1]=2;
  id[ 2]= 3;pos[ 2].setX( 00.0*mm);pos[ 2].setY( 16.7*mm);pos[ 2].setZ(zpos);ring[ 2]=1;
  id[ 3]= 4;pos[ 3].setX(-15.2*mm);pos[ 3].setY( 16.7*mm);pos[ 3].setZ(zpos);ring[ 3]=2;
  id[ 4]= 5;pos[ 4].setX(-15.2*mm);pos[ 4].setY( 00.0*mm);pos[ 4].setZ(zpos);ring[ 4]=1;
  id[ 5]= 6;pos[ 5].setX(-15.2*mm);pos[ 5].setY(-16.7*mm);pos[ 5].setZ(zpos);ring[ 5]=2;
  id[ 6]= 7;pos[ 6].setX( 00.0*mm);pos[ 6].setY(-16.7*mm);pos[ 6].setZ(zpos);ring[ 6]=1;
  id[ 7]= 8;pos[ 7].setX( 15.2*mm);pos[ 7].setY(-16.7*mm);pos[ 7].setZ(zpos);ring[ 7]=2;

  id[ 8]= 9;pos[ 8].setX( 30.4*mm);pos[ 8].setY( 00.0*mm);pos[ 8].setZ(zpos);ring[ 8]=3;
  id[ 9]=10;pos[ 9].setX( 30.4*mm);pos[ 9].setY( 16.7*mm);pos[ 9].setZ(zpos);ring[ 9]=4;
  id[10]=11;pos[10].setX( 30.4*mm);pos[10].setY( 33.4*mm);pos[10].setZ(zpos);ring[10]=5;
  id[11]=12;pos[11].setX( 15.2*mm);pos[11].setY( 33.4*mm);pos[11].setZ(zpos);ring[11]=4;
  id[12]=13;pos[12].setX( 00.0*mm);pos[12].setY( 33.4*mm);pos[12].setZ(zpos);ring[12]=3;
  id[13]=14;pos[13].setX(-15.2*mm);pos[13].setY( 33.4*mm);pos[13].setZ(zpos);ring[13]=4;
  id[14]=15;pos[14].setX(-30.4*mm);pos[14].setY( 33.4*mm);pos[14].setZ(zpos);ring[14]=5;
  id[15]=16;pos[15].setX(-30.4*mm);pos[15].setY( 16.7*mm);pos[15].setZ(zpos);ring[15]=4;

  id[16]=17;pos[16].setX(-30.4*mm);pos[16].setY( 00.0*mm);pos[16].setZ(zpos);ring[16]=3;
  id[17]=18;pos[17].setX(-30.4*mm);pos[17].setY(-16.7*mm);pos[17].setZ(zpos);ring[17]=4;
  id[18]=19;pos[18].setX(-30.4*mm);pos[18].setY(-33.4*mm);pos[18].setZ(zpos);ring[18]=5;
  id[19]=20;pos[19].setX(-15.2*mm);pos[19].setY(-33.4*mm);pos[19].setZ(zpos);ring[19]=4;
  id[20]=21;pos[20].setX( 00.0*mm);pos[20].setY(-33.4*mm);pos[20].setZ(zpos);ring[20]=3;
  id[21]=22;pos[21].setX( 15.2*mm);pos[21].setY(-33.4*mm);pos[21].setZ(zpos);ring[21]=4;
  id[22]=23;pos[22].setX( 30.4*mm);pos[22].setY(-33.4*mm);pos[22].setZ(zpos);ring[22]=5;
  id[23]=24;pos[23].setX( 30.4*mm);pos[23].setY(-16.7*mm);pos[23].setZ(zpos);ring[23]=4;


 
}

CsI_array::~CsI_array()
{;}
//-----------------------------------------------------------------------------
void CsI_array::Construct()
{
  G4int i;

  vector<CsI_detector*>::iterator itPos = aCsI_array.begin();
  // clear all elements from the array
  for(; itPos < aCsI_array.end(); itPos++)
    delete *itPos;    // free the element from memory
   // finally, clear all elements from the array
  aCsI_array.clear();

  for(i=0;i<NCsI;i++) 
    aCsI_array.push_back(new CsI_detector(expHall_log,materials));   

  itPos = aCsI_array.begin();
  for(i=0;i<NCsI;i++) 
    {
      (*itPos)->Construct();
      pos[i].setZ(zpos);
      (*itPos)->Place(pos[i]);
      (*itPos)->setId(id[i]);
      (*itPos)->setRingId(ring[i]);
      (*itPos)->setName();     
      itPos++;
     
    }
 
}


//-----------------------------------------------------------------------------
void CsI_array::Report()
{
;
 
}
//-----------------------------------------------------------------------------
void CsI_array::MakeSensitive(TrackerCsISD* TrackerCsI)
{

   vector<CsI_detector*>::iterator itPos = aCsI_array.begin();
  
  for(; itPos < aCsI_array.end(); itPos++)
      (*itPos)->GetLog()->SetSensitiveDetector(TrackerCsI);
    
}

