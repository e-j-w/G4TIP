//CsI ball code
//original code by T. Ma

#include "CsI_array_spherical.hh"

CsI_array_spherical::CsI_array_spherical(G4LogicalVolume *experimentalHall_log,
                                         Materials *mat) {
  // zpos=0.0*mm;
  materials = mat;
  expHall_log = experimentalHall_log;

  // spherical array attributes
  // From P.Voss et al, "The TIGRESS Integrated Plunger ancillary systems for
  // electromagnetic transition rate studies at TRIUMF", Nuclear Instruments and
  // Methods in Physics Research A 746 (2014) 87-97, Table 3.
  G4int detectors_per_ring[10];
  G4double det_radialdist_per_ring[10]; // To crystal-light guide interface
  G4double det_thickness_per_ring[10];
  G4double det_avgdegree_per_ring[10]; // Average azimuthal degree position
  G4double det_widdegree_per_ring[10]; // Half-width of crystal
  detectors_per_ring[0] = 4;
  det_radialdist_per_ring[0] = 92.0 * mm;
  det_thickness_per_ring[0] = 5.0 * mm;
  det_avgdegree_per_ring[0] = 8.0 * deg;
  det_widdegree_per_ring[0] = 4.00 * deg;
  detectors_per_ring[1] = 6;
  det_radialdist_per_ring[1] = 57.2 * mm;
  det_thickness_per_ring[1] = 2.6 * mm;
  det_avgdegree_per_ring[1] = 17.5 * deg;
  det_widdegree_per_ring[1] = 7.75 * deg;
  detectors_per_ring[2] = 12;
  det_radialdist_per_ring[2] = 57.2 * mm;
  det_thickness_per_ring[2] = 2.3 * mm;
  det_avgdegree_per_ring[2] = 33.0 * deg;
  det_widdegree_per_ring[2] = 7.75 * deg;
  detectors_per_ring[3] = 16;
  det_radialdist_per_ring[3] = 57.2 * mm;
  det_thickness_per_ring[3] = 2.0 * mm;
  det_avgdegree_per_ring[3] = 48.5 * deg;
  det_widdegree_per_ring[3] = 7.75 * deg;
  detectors_per_ring[4] = 20;
  det_radialdist_per_ring[4] = 57.2 * mm;
  det_thickness_per_ring[4] = 1.7 * mm;
  det_avgdegree_per_ring[4] = 64.0 * deg;
  det_widdegree_per_ring[4] = 7.75 * deg;
  detectors_per_ring[5] = 18;
  det_radialdist_per_ring[5] = 57.2 * mm;
  det_thickness_per_ring[5] = 1.5 * mm;
  det_avgdegree_per_ring[5] = 79.5 * deg;
  det_widdegree_per_ring[5] = 7.75 * deg;
  detectors_per_ring[6] = 18;
  det_radialdist_per_ring[6] = 57.2 * mm;
  det_thickness_per_ring[6] = 1.3 * mm;
  det_avgdegree_per_ring[6] = 95.0 * deg;
  det_widdegree_per_ring[6] = 7.75 * deg;
  detectors_per_ring[7] = 14;
  det_radialdist_per_ring[7] = 57.2 * mm;
  det_thickness_per_ring[7] = 1.2 * mm;
  det_avgdegree_per_ring[7] = 111.9 * deg;
  det_widdegree_per_ring[7] = 9.15 * deg;
  detectors_per_ring[8] = 12;
  det_radialdist_per_ring[8] = 57.2 * mm;
  det_thickness_per_ring[8] = 1.2 * mm;
  det_avgdegree_per_ring[8] = 130.2 * deg;
  det_widdegree_per_ring[8] = 9.15 * deg;
  detectors_per_ring[9] = 8;
  det_radialdist_per_ring[9] = 57.2 * mm;
  det_thickness_per_ring[9] = 1.2 * mm;
  det_avgdegree_per_ring[9] = 148.5 * deg;
  det_widdegree_per_ring[9] = 9.15 * deg;

  G4int ndet_cumulative = 0;
  for (G4int i = 0; i < 10; i++) {
    G4int ndet_ring = detectors_per_ring[i];
    G4double radial = det_radialdist_per_ring[i];
    G4double thick = det_thickness_per_ring[i];
    G4double avgdeg = det_avgdegree_per_ring[i]; // (180*deg) * PI;
    G4double widdeg = det_widdegree_per_ring[i]; // (180*deg) * PI;
    for (G4int j = 0; j < ndet_ring; j++) {
      G4int curr_det = ndet_cumulative + j;
      id[curr_det] = curr_det + 1;
      ring[curr_det] = i;
      G4double phideg = 180 * deg / ndet_ring;
      // Position vector
      pos[curr_det].setRThetaPhi(radial, avgdeg, 2 * phideg * j);
      // Crystal size attributes
      dim[curr_det].setRThetaPhi(thick, widdeg,
                                 phideg); // Only angles are half-width
      // G4cout << "printing for ring (" << i << "), element (" << j << ")" <<
      // endl;
      // G4cout << "position vector (" << radial << ", " << avgdeg << ", " <<
      // 2*phideg*j << ")" << endl;
      // G4cout << "dimension vector (" << thick << ", " << widdeg << ", " <<
      // phideg << ")" << endl;
    }
    ndet_cumulative = ndet_cumulative + ndet_ring;
  }
}

CsI_array_spherical::~CsI_array_spherical() { ; }
//-----------------------------------------------------------------------------
void CsI_array_spherical::Construct() {
  G4int i;

  vector<CsI_detector_spherical *>::iterator itPos = aCsI_array.begin();
  // clear all elements from the array
  for (; itPos < aCsI_array.end(); itPos++)
    delete *itPos; // free the element from memory
                   // finally, clear all elements from the array
  aCsI_array.clear();

  for (i = 0; i < NCsISph; i++)
    aCsI_array.push_back(new CsI_detector_spherical(expHall_log, materials));

  itPos = aCsI_array.begin();
  for (i = 0; i < NCsISph; i++) {
    (*itPos)->Construct(pos[i], dim[i]);
    (*itPos)->Place(pos[i]);
    (*itPos)->setId(id[i]);
    (*itPos)->setRingId(ring[i]);
    (*itPos)->setName();
    itPos++;
  }
}

//-----------------------------------------------------------------------------
void CsI_array_spherical::Report() {
  G4cout << "CsI ball constructed." << endl;
  /*G4cout << "Ball detector positions:" << endl;
  G4cout << "pos x y z" << endl;
  for(int i=0;i<NCsISph;i++)
          G4cout << i+1 << " " << pos[i].getX() << " " << pos[i].getY() << " "
  << pos[i].getZ() << endl;*/
}
//-----------------------------------------------------------------------------
void CsI_array_spherical::MakeSensitive(TrackerCsISD *TrackerCsI) {

  vector<CsI_detector_spherical *>::iterator itPos = aCsI_array.begin();

  for (; itPos < aCsI_array.end(); itPos++)
    (*itPos)->GetLog()->SetSensitiveDetector(TrackerCsI);
}
