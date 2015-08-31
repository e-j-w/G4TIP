#include "PIN_array.hh"

PIN_array::PIN_array(G4LogicalVolume* experimentalHall_log,Materials* mat)
{
  zpos=40.9*mm;
  materials=mat;
  expHall_log=experimentalHall_log;
  id[ 0]= 1;pos[ 0].setX( 15.5*mm);pos[ 0].setY( 00.0*mm);pos[ 0].setZ(zpos);ring[ 0]=1;//17
  id[ 1]= 2;pos[ 1].setX( 11.1*mm);pos[ 1].setY( 12.9*mm);pos[ 1].setZ(zpos);ring[ 1]=1;//16
  id[ 2]= 3;pos[ 2].setX( 00.0*mm);pos[ 2].setY( 15.9*mm);pos[ 2].setZ(zpos);ring[ 2]=1;//15
  id[ 3]= 4;pos[ 3].setX(-11.1*mm);pos[ 3].setY( 12.9*mm);pos[ 3].setZ(zpos);ring[ 3]=1;//14
  id[ 4]= 5;pos[ 4].setX(-15.5*mm);pos[ 4].setY( 00.0*mm);pos[ 4].setZ(zpos);ring[ 4]=1;//13
  id[ 5]= 6;pos[ 5].setX(-11.1*mm);pos[ 5].setY(-12.9*mm);pos[ 5].setZ(zpos);ring[ 5]=1;//12
  id[ 6]= 7;pos[ 6].setX( 00.0*mm);pos[ 6].setY(-15.9*mm);pos[ 6].setZ(zpos);ring[ 6]=1;//11
  id[ 7]= 8;pos[ 7].setX( 11.1*mm);pos[ 7].setY(-12.9*mm);pos[ 7].setZ(zpos);ring[ 7]=1;//10

  id[ 8]= 9;pos[ 8].setX( 26.6*mm);pos[ 8].setY( 00.0*mm);pos[ 8].setZ(zpos);ring[ 8]=2;// 7
  id[ 9]=10;pos[ 9].setX( 22.2*mm);pos[ 9].setY( 12.9*mm);pos[ 9].setZ(zpos);ring[ 9]=2;// 6
  id[10]=11;pos[10].setX( 11.1*mm);pos[10].setY( 25.8*mm);pos[10].setZ(zpos);ring[10]=2;// 5
  id[11]=12;pos[11].setX( 00.0*mm);pos[11].setY( 28.8*mm);pos[11].setZ(zpos);ring[11]=2;// 4
  id[12]=13;pos[12].setX(-11.1*mm);pos[12].setY( 25.8*mm);pos[12].setZ(zpos);ring[12]=2;// 3
  id[13]=14;pos[13].setX(-22.2*mm);pos[13].setY( 12.9*mm);pos[13].setZ(zpos);ring[13]=2;// 2
  id[14]=15;pos[14].setX(-26.6*mm);pos[14].setY( 00.0*mm);pos[14].setZ(zpos);ring[14]=2;// 1
  id[15]=16;pos[15].setX(-22.2*mm);pos[15].setY(-12.9*mm);pos[15].setZ(zpos);ring[15]=2;// 0

  id[16]=17;pos[16].setX(-11.1*mm);pos[16].setY(-25.8*mm);pos[16].setZ(zpos);ring[16]=2;//77
  id[17]=18;pos[17].setX( 00.0*mm);pos[17].setY(-28.8*mm);pos[17].setZ(zpos);ring[17]=2;//76
  id[18]=19;pos[18].setX( 11.1*mm);pos[18].setY(-25.8*mm);pos[18].setZ(zpos);ring[18]=2;//75
  id[19]=20;pos[19].setX( 22.2*mm);pos[19].setY(-12.9*mm);pos[19].setZ(zpos);ring[19]=2;//74
  id[20]=21;pos[20].setX( 37.7*mm);pos[20].setY( 00.0*mm);pos[20].setZ(zpos);ring[20]=3;//73
  id[21]=22;pos[21].setX( 33.3*mm);pos[21].setY( 12.9*mm);pos[21].setZ(zpos);ring[21]=3;//72
  id[22]=23;pos[22].setX( 22.2*mm);pos[22].setY( 25.8*mm);pos[22].setZ(zpos);ring[22]=3;//71
  id[23]=24;pos[23].setX(-22.2*mm);pos[23].setY( 25.8*mm);pos[23].setZ(zpos);ring[23]=3;//70

  id[24]=25;pos[24].setX(-33.3*mm);pos[24].setY( 12.9*mm);pos[24].setZ(zpos);ring[24]=3;//67  
  id[25]=26;pos[25].setX(-37.7*mm);pos[25].setY( 00.0*mm);pos[25].setZ(zpos);ring[25]=3;//66
  id[26]=27;pos[26].setX(-33.3*mm);pos[26].setY(-12.9*mm);pos[26].setZ(zpos);ring[26]=3;//65
  id[27]=28;pos[27].setX(-22.2*mm);pos[27].setY(-25.8*mm);pos[27].setZ(zpos);ring[27]=3;//64
  id[28]=29;pos[28].setX( 22.2*mm);pos[28].setY(-25.8*mm);pos[28].setZ(zpos);ring[28]=3;//63
  id[29]=30;pos[29].setX( 33.3*mm);pos[29].setY(-12.9*mm);pos[29].setZ(zpos);ring[29]=3;//62
  id[30]=31;pos[30].setX( 33.3*mm);pos[30].setY( 25.8*mm);pos[30].setZ(zpos);ring[30]=3;//61
  id[31]=32;pos[31].setX( 22.2*mm);pos[31].setY( 38.7*mm);pos[31].setZ(zpos);ring[31]=4;//60

  id[32]=33;pos[32].setX( 11.1*mm);pos[32].setY( 38.7*mm);pos[32].setZ(zpos);ring[32]=4;//97  
  id[33]=34;pos[33].setX( 00.0*mm);pos[33].setY( 41.7*mm);pos[33].setZ(zpos);ring[33]=4;//96
  id[34]=35;pos[34].setX(-11.1*mm);pos[34].setY( 38.7*mm);pos[34].setZ(zpos);ring[34]=4;//95
  id[35]=36;pos[35].setX(-22.2*mm);pos[35].setY( 38.7*mm);pos[35].setZ(zpos);ring[35]=4;//94
  id[36]=37;pos[36].setX(-33.3*mm);pos[36].setY( 25.8*mm);pos[36].setZ(zpos);ring[36]=4;//93
  id[37]=38;pos[37].setX(-33.3*mm);pos[37].setY(-25.8*mm);pos[37].setZ(zpos);ring[37]=4;//92
  id[38]=39;pos[38].setX(-22.2*mm);pos[38].setY(-38.7*mm);pos[38].setZ(zpos);ring[38]=4;//91
  id[39]=40;pos[39].setX(-11.1*mm);pos[39].setY(-38.7*mm);pos[39].setZ(zpos);ring[39]=4;//90

  id[40]=41;pos[40].setX( 00.0*mm);pos[40].setY(-41.7*mm);pos[40].setZ(zpos);ring[40]=4;//87
  id[41]=42;pos[41].setX( 11.1*mm);pos[41].setY(-38.7*mm);pos[41].setZ(zpos);ring[41]=4;//86
  id[42]=43;pos[42].setX( 22.2*mm);pos[42].setY(-38.7*mm);pos[42].setZ(zpos);ring[42]=4;//85
  id[43]=44;pos[43].setX( 33.3*mm);pos[43].setY(-25.8*mm);pos[43].setZ(zpos);ring[43]=4;//84
 
}

PIN_array::~PIN_array()
{;}
//-----------------------------------------------------------------------------
void PIN_array::Construct()
{
  G4int i;

  vector<PIN_diode*>::iterator itPos = aPIN_array.begin();
  // clear all elements from the array
  for(; itPos < aPIN_array.end(); itPos++)
    delete *itPos;    // free the element from memory
   // finally, clear all elements from the array
  aPIN_array.clear();

  for(i=0;i<NPIN;i++) 
    aPIN_array.push_back(new PIN_diode(expHall_log,materials));   

  itPos = aPIN_array.begin();
  for(i=0;i<NPIN;i++) 
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
void PIN_array::Report()
{
;
 
}
//-----------------------------------------------------------------------------
void PIN_array::MakeSensitive(TrackerPINSD* TrackerPIN)
{

   vector<PIN_diode*>::iterator itPos = aPIN_array.begin();
  
  for(; itPos < aPIN_array.end(); itPos++)
      (*itPos)->GetLog()->SetSensitiveDetector(TrackerPIN);
    
}

