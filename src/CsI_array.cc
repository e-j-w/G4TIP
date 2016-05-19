#include "CsI_array.hh"

CsI_array::CsI_array(G4LogicalVolume* experimentalHall_log,Materials* mat)
{
  //zpos=5.7*mm + 1.5*mm;
  //zpos=28.7*mm + 1.5*mm;
  zpos=51.7*mm + 1.5*mm;//1.5mm is half-length of the detector 
  materials=mat;
  expHall_log=experimentalHall_log;
  id[ 0]= 1;pos[ 0].setX( 15.2*mm);pos[ 0].setY( 00.0*mm);pos[ 0].setZ(zpos);ring[ 0]=1;kB[ 0]=17.077;S[ 0]=1513.105;
  id[ 1]= 2;pos[ 1].setX( 15.2*mm);pos[ 1].setY( 16.7*mm);pos[ 1].setZ(zpos);ring[ 1]=2;kB[ 1]=15.179;S[ 1]=1437.750;
  id[ 2]= 3;pos[ 2].setX( 00.0*mm);pos[ 2].setY( 16.7*mm);pos[ 2].setZ(zpos);ring[ 2]=1;kB[ 2]=14.791;S[ 2]=1546.911;
  id[ 3]= 4;pos[ 3].setX(-15.2*mm);pos[ 3].setY( 16.7*mm);pos[ 3].setZ(zpos);ring[ 3]=2;kB[ 3]=14.791;S[ 3]=1546.911;//kB not measured, inferred from 28Mg 3-alpha data to be similar to detector 3
  id[ 4]= 5;pos[ 4].setX(-15.2*mm);pos[ 4].setY( 00.0*mm);pos[ 4].setZ(zpos);ring[ 4]=1;kB[ 4]=14.622;S[ 4]=1534.862;
  id[ 5]= 6;pos[ 5].setX(-15.2*mm);pos[ 5].setY(-16.7*mm);pos[ 5].setZ(zpos);ring[ 5]=2;kB[ 5]=6.393;S[ 5]=982.583;
  id[ 6]= 7;pos[ 6].setX( 00.0*mm);pos[ 6].setY(-16.7*mm);pos[ 6].setZ(zpos);ring[ 6]=1;kB[ 6]=14.849;S[ 6]=1439.469;
  id[ 7]= 8;pos[ 7].setX( 15.2*mm);pos[ 7].setY(-16.7*mm);pos[ 7].setZ(zpos);ring[ 7]=2;kB[ 7]=15.438;S[ 7]=1392.760;
  id[ 8]= 9;pos[ 8].setX( 30.4*mm);pos[ 8].setY( 00.0*mm);pos[ 8].setZ(zpos);ring[ 8]=3;kB[ 8]=14.532;S[ 8]=1506.327;//kB not measured, kB and S taken as the average of all other detectors
  id[ 9]=10;pos[ 9].setX( 30.4*mm);pos[ 9].setY( 16.7*mm);pos[ 9].setZ(zpos);ring[ 9]=4;kB[ 9]=12.883;S[ 9]=1417.196;
  id[10]=11;pos[10].setX( 30.4*mm);pos[10].setY( 33.4*mm);pos[10].setZ(zpos);ring[10]=5;kB[10]=15.874;S[10]=1539.676;
  id[11]=12;pos[11].setX( 15.2*mm);pos[11].setY( 33.4*mm);pos[11].setZ(zpos);ring[11]=4;kB[11]=15.140;S[11]=1615.318;
  id[12]=13;pos[12].setX( 00.0*mm);pos[12].setY( 33.4*mm);pos[12].setZ(zpos);ring[12]=3;kB[12]=15.102;S[12]=1589.526;
  id[13]=14;pos[13].setX(-15.2*mm);pos[13].setY( 33.4*mm);pos[13].setZ(zpos);ring[13]=4;kB[13]=12.183;S[13]=1520.829;
  id[14]=15;pos[14].setX(-30.4*mm);pos[14].setY( 33.4*mm);pos[14].setZ(zpos);ring[14]=5;kB[14]=13.108;S[14]=1534.609;
  id[15]=16;pos[15].setX(-30.4*mm);pos[15].setY( 16.7*mm);pos[15].setZ(zpos);ring[15]=4;kB[15]=12.720;S[15]=1391.263;
  id[16]=17;pos[16].setX(-30.4*mm);pos[16].setY( 00.0*mm);pos[16].setZ(zpos);ring[16]=3;kB[16]=14.769;S[16]=1358.237;
  id[17]=18;pos[17].setX(-30.4*mm);pos[17].setY(-16.7*mm);pos[17].setZ(zpos);ring[17]=4;kB[17]=16.481;S[17]=1598.195;
  id[18]=19;pos[18].setX(-30.4*mm);pos[18].setY(-33.4*mm);pos[18].setZ(zpos);ring[18]=5;kB[18]=15.573;S[18]=1720.591;
  id[19]=20;pos[19].setX(-15.2*mm);pos[19].setY(-33.4*mm);pos[19].setZ(zpos);ring[19]=4;kB[19]=16.031;S[19]=1646.501;
  id[20]=21;pos[20].setX( 00.0*mm);pos[20].setY(-33.4*mm);pos[20].setZ(zpos);ring[20]=3;kB[20]=13.669;S[20]=1515.649;
  id[21]=22;pos[21].setX( 15.2*mm);pos[21].setY(-33.4*mm);pos[21].setZ(zpos);ring[21]=4;kB[21]=16.856;S[21]=1702.649;
  id[22]=23;pos[22].setX( 30.4*mm);pos[22].setY(-33.4*mm);pos[22].setZ(zpos);ring[22]=5;kB[22]=16.814;S[22]=1638.268;
  id[23]=24;pos[23].setX( 30.4*mm);pos[23].setY(-16.7*mm);pos[23].setZ(zpos);ring[23]=4;kB[23]=14.148;S[23]=1503.235;

  /*//some hacked together code for running at constant kB
  G4double constKb=1.0;
  id[ 0]= 1;pos[ 0].setX( 15.2*mm);pos[ 0].setY( 00.0*mm);pos[ 0].setZ(zpos);ring[ 0]=1;kB[ 0]=constKb;S[ 0]=1.0;
  id[ 1]= 2;pos[ 1].setX( 15.2*mm);pos[ 1].setY( 16.7*mm);pos[ 1].setZ(zpos);ring[ 1]=2;kB[ 1]=constKb;S[ 1]=1.0;
  id[ 2]= 3;pos[ 2].setX( 00.0*mm);pos[ 2].setY( 16.7*mm);pos[ 2].setZ(zpos);ring[ 2]=1;kB[ 2]=constKb;S[ 2]=1.0;
  id[ 3]= 4;pos[ 3].setX(-15.2*mm);pos[ 3].setY( 16.7*mm);pos[ 3].setZ(zpos);ring[ 3]=2;kB[ 3]=constKb;S[ 3]=1.0;
  id[ 4]= 5;pos[ 4].setX(-15.2*mm);pos[ 4].setY( 00.0*mm);pos[ 4].setZ(zpos);ring[ 4]=1;kB[ 4]=constKb;S[ 4]=1.0;
  id[ 5]= 6;pos[ 5].setX(-15.2*mm);pos[ 5].setY(-16.7*mm);pos[ 5].setZ(zpos);ring[ 5]=2;kB[ 5]=constKb;S[ 5]=1.0;
  id[ 6]= 7;pos[ 6].setX( 00.0*mm);pos[ 6].setY(-16.7*mm);pos[ 6].setZ(zpos);ring[ 6]=1;kB[ 6]=constKb;S[ 6]=1.0;
  id[ 7]= 8;pos[ 7].setX( 15.2*mm);pos[ 7].setY(-16.7*mm);pos[ 7].setZ(zpos);ring[ 7]=2;kB[ 7]=constKb;S[ 7]=1.0;
  id[ 8]= 9;pos[ 8].setX( 30.4*mm);pos[ 8].setY( 00.0*mm);pos[ 8].setZ(zpos);ring[ 8]=3;kB[ 8]=constKb;S[ 8]=1.0;
  id[ 9]=10;pos[ 9].setX( 30.4*mm);pos[ 9].setY( 16.7*mm);pos[ 9].setZ(zpos);ring[ 9]=4;kB[ 9]=constKb;S[ 9]=1.0;
  id[10]=11;pos[10].setX( 30.4*mm);pos[10].setY( 33.4*mm);pos[10].setZ(zpos);ring[10]=5;kB[10]=constKb;S[10]=1.0;
  id[11]=12;pos[11].setX( 15.2*mm);pos[11].setY( 33.4*mm);pos[11].setZ(zpos);ring[11]=4;kB[11]=constKb;S[11]=1.0;
  id[12]=13;pos[12].setX( 00.0*mm);pos[12].setY( 33.4*mm);pos[12].setZ(zpos);ring[12]=3;kB[12]=constKb;S[12]=1.0;
  id[13]=14;pos[13].setX(-15.2*mm);pos[13].setY( 33.4*mm);pos[13].setZ(zpos);ring[13]=4;kB[13]=constKb;S[13]=1.0;
  id[14]=15;pos[14].setX(-30.4*mm);pos[14].setY( 33.4*mm);pos[14].setZ(zpos);ring[14]=5;kB[14]=constKb;S[14]=1.0;
  id[15]=16;pos[15].setX(-30.4*mm);pos[15].setY( 16.7*mm);pos[15].setZ(zpos);ring[15]=4;kB[15]=constKb;S[15]=1.0;
  id[16]=17;pos[16].setX(-30.4*mm);pos[16].setY( 00.0*mm);pos[16].setZ(zpos);ring[16]=3;kB[16]=constKb;S[16]=1.0;
  id[17]=18;pos[17].setX(-30.4*mm);pos[17].setY(-16.7*mm);pos[17].setZ(zpos);ring[17]=4;kB[17]=constKb;S[17]=1.0;
  id[18]=19;pos[18].setX(-30.4*mm);pos[18].setY(-33.4*mm);pos[18].setZ(zpos);ring[18]=5;kB[18]=constKb;S[18]=1.0;
  id[19]=20;pos[19].setX(-15.2*mm);pos[19].setY(-33.4*mm);pos[19].setZ(zpos);ring[19]=4;kB[19]=constKb;S[19]=1.0;
  id[20]=21;pos[20].setX( 00.0*mm);pos[20].setY(-33.4*mm);pos[20].setZ(zpos);ring[20]=3;kB[20]=constKb;S[20]=1.0;
  id[21]=22;pos[21].setX( 15.2*mm);pos[21].setY(-33.4*mm);pos[21].setZ(zpos);ring[21]=4;kB[21]=constKb;S[21]=1.0;
  id[22]=23;pos[22].setX( 30.4*mm);pos[22].setY(-33.4*mm);pos[22].setZ(zpos);ring[22]=5;kB[22]=constKb;S[22]=1.0;
  id[23]=24;pos[23].setX( 30.4*mm);pos[23].setY(-16.7*mm);pos[23].setZ(zpos);ring[23]=4;kB[23]=constKb;S[23]=1.0;*/
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

