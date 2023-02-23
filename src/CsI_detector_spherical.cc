//CsI ball code
//original code by T. Ma

#include "CsI_detector_spherical.hh"

CsI_detector_spherical::CsI_detector_spherical(
    G4LogicalVolume *experimentalHall_log, Materials *mat) {
  materials = mat;
  expHall_log = experimentalHall_log;
  CsI_mylar_thickness = 2.0 * um;
  CsI_absorber_thickness = 2.0 * um;
  CsI_Material = materials->FindMaterial("G4_CESIUM_IODIDE");
  CsI_mylar_Material = materials->FindMaterial("G4_MYLAR");
  CsI_absorber_Material = materials->FindMaterial("G4_Pb");
  //G4cout << "Absorber is lead." << G4endl;
  Pos = new G4ThreeVector(0., 0., 0.);
  Pos_abs = new G4ThreeVector(0., 0., 0.);
}

CsI_detector_spherical::~CsI_detector_spherical() { ; }
//-----------------------------------------------------------------------------
G4VPhysicalVolume *CsI_detector_spherical::Construct(G4ThreeVector pos,
                                                     G4ThreeVector dim) {

  G4cout << "Setting up CsI ball dectector at position " << pos << ", with absorber thickness " << CsI_absorber_thickness/um << " um." << G4endl;
  G4double radius, thick, theta, dtheta, phi, dphi;
  radius = pos.getR();
  thick = dim.getR();
  theta = pos.getTheta();
  dtheta = dim.getTheta();
  phi = pos.getPhi();
  dphi = dim.getPhi();
  G4double r0, r1, r2, r3, t1, p1, abs_deg;
  // G4double t2,p2;
  // G4double c1 = 100*nm, c2 = 0.001*deg;//clearance space
  r3 = radius / cos(dtheta) / cos(dtheta); // cover holes
  r2 = radius - thick;
  r1 = radius - thick - CsI_mylar_thickness;
  r0 = radius - thick - CsI_mylar_thickness - CsI_absorber_thickness;
  t1 = theta - dtheta; // t2 = theta + dtheta;
  p1 = phi - dphi;     // p2 = phi + dphi;
  abs_deg = CsI_mylar_thickness / r2 * 180 * deg;
  /*
  //For G4Trap
  G4double pDz, pTheta, pPhi, pDy1, pDx1, pDx2, pAlp1, pDy2, pDx3, pDx4, pAlp2;
  pTheta = 0*deg; pPhi = 0*deg; pAlp1 = 0*deg; pAlp2 = 0*deg;
  pDz = thick/2.;
  pDy1 = r2*sin(dtheta);       pDy2 = r3*sin(dtheta);      //azimuthal width
  pDx1 = r2*sin(t1)*sin(dphi); pDx2 = r2*sin(t2)*sin(dphi);//polar width
  pDx3 = r3*sin(t1)*sin(dphi); pDx4 = r3*sin(t2)*sin(dphi);
  pDy2 = pDy1; pDx3 = pDx1; pDx4 = pDx2;
  //mylars face inwards
  G4double aDz, aDy1, aDx1, aDx2, aDy2, aDx3, aDx4;
  aDz = CsI_mylar_thickness;
  aDy1 = (r2-aDz)*sin(dtheta);       aDy2 = r2*sin(dtheta);
  aDx1 = (r2-aDz)*sin(t1)*sin(dphi); aDx2 = (r2-aDz)*sin(t2)*sin(dphi);
  aDx3 = r2*sin(t1)*sin(dphi);     aDx4 = r2*sin(t2)*sin(dphi);
  aDy2 = aDy1; aDx3 = aDx1; aDx4 = aDx2;
  //Positional and rotational vector for this detector (from shape origin)
  G4double posX, posY, posZ, posR;
  posR = radius - thick/2.;
  posX = posR*sin(theta)*cos(phi);
  posY = posR*sin(theta)*sin(phi);
  posZ = posR*cos(theta);
  //Pos->setX(posX); Pos->setY(posY); Pos->setZ(posZ);
  posR = radius - thick - aDz/2.;
  posX = posR*sin(theta)*cos(phi);
  posY = posR*sin(theta)*sin(phi);
  posZ = posR*cos(theta);
  //Pos_abs->setX(posX); Pos_abs->setY(posY); Pos_abs->setZ(posZ);
  */
  G4RotationMatrix Rot;
  Rot.rotateY(theta);
  Rot.rotateZ(phi);

  // For spherical shells
  G4Sphere *xCsI_cut =
      new G4Sphere("xCsIcut", 0. * mm, 2. * r3, p1 + abs_deg,
                   2 * (dphi - abs_deg), t1 + abs_deg, 2 * (dtheta - abs_deg));
  G4Sphere *xCsI_detector =
      new G4Sphere("xCsIdetector", r2, r3, p1 + abs_deg, 2 * (dphi - abs_deg),
                   t1 + abs_deg, 2 * (dtheta - abs_deg));
  G4Sphere *xCsI_side =
      new G4Sphere("xCsIside", r1, r3, p1, 2 * dphi, t1, 2 * dtheta);
  G4Box *xCsI_face = new G4Box("xCsI_face", r2, r2, r2);
  G4Box *xMylar_face = new G4Box("xMylar_face", r1, r1, r1);
  G4Box *xAbsorber_face = new G4Box("xAbsorber_face", r0, r0, r0);

  // For trapezoids
  // G4Trap* xCsI_detector = new G4Trap("xCsI", pDz+aDz, pTheta, pPhi, pDy1-aDz,
  // pDx1-aDz, pDx2-aDz, pAlp1, pDy2-aDz, pDx3-aDz, pDx4-aDz, pAlp2);
  // G4Trap* aCsI_detector = new G4Trap("xCsI", pDz, pTheta, pPhi, pDy1-aDz,
  // pDx1-aDz, pDx2-aDz, pAlp1, pDy2-aDz, pDx3-aDz, pDx4-aDz, pAlp2);
  // G4Trap* xCsI_side_mylar = new G4Trap("xCsIside", pDz, pTheta, pPhi,
  // pDy1, pDx1, pDx2, pAlp1, pDy2, pDx3, pDx4, pAlp2);
  // G4Trap* aCsI_mylar = new G4Trap("CsImylar", aDz/2., pTheta, pPhi,
  // aDy1, aDx1, aDx2, pAlp1, aDy2, aDx3, aDx4, pAlp2);

  G4Transform3D transform(Rot, G4ThreeVector(0., 0., 0.));
  G4SubtractionSolid *xCsI_side_cut =
      new G4SubtractionSolid("xCsIsideCut", xCsI_side, xCsI_cut);
  G4SubtractionSolid *aCsI_side_mylar =
      new G4SubtractionSolid("aCsIside", xCsI_side_cut, xCsI_face, transform);
  G4SubtractionSolid *aCsI_detector = new G4SubtractionSolid(
      "aCsIdetector", xCsI_detector, xCsI_face, transform);

  // G4IntersectionSolid* xCsI_mylar_cut      = new
  // G4IntersectionSolid("xCsImylarCut", xCsI_side, xCsI_face, transform);
  // G4SubtractionSolid* aCsI_mylar      = new
  // G4SubtractionSolid("aCsImylar", xCsI_mylar_cut, xMylar_face, transform);
  G4SubtractionSolid *xCsI_mylar_cut =
      new G4SubtractionSolid("xCsImylarCut", xCsI_face, xMylar_face);
  G4IntersectionSolid *aCsI_mylar = new G4IntersectionSolid(
      "aCsImylar", xCsI_side, xCsI_mylar_cut, transform);
  G4SubtractionSolid *xCsI_absorber_cut =
      new G4SubtractionSolid("xCsIabsorberCut", xMylar_face, xAbsorber_face);
  G4IntersectionSolid *aCsI_absorber = new G4IntersectionSolid(
      "aCsIabsorber", xCsI_side, xCsI_absorber_cut, transform);
  /*/
  G4Sphere* aCsI_detector = new G4Sphere("aCsIdetector", r2, r3, p1+abs_deg,
  2*(dphi-abs_deg), t1+abs_deg, 2*(dtheta-abs_deg));
  G4Sphere* xCsI_side     = new G4Sphere("xCsIside", r2, r3, p1, 2*dphi, t1,
  2*dtheta);
  G4Sphere* aCsI_mylar = new G4Sphere("aCsImylar", r1, r2, p1, 2*dphi, t1,
  2*dtheta);
  G4SubtractionSolid* aCsI_side_mylar = new G4SubtractionSolid("aCsIside",
  xCsI_side, aCsI_detector);
  */
  CsI_detector_log =
      new G4LogicalVolume(aCsI_detector, CsI_Material, "CsI_log", 0, 0, 0);
  CsI_mylar_log = new G4LogicalVolume(aCsI_mylar, CsI_mylar_Material,
                                         "CsI_mylar_log", 0, 0, 0);
  CsI_side_mylar_log =
      new G4LogicalVolume(aCsI_side_mylar, CsI_mylar_Material,
                          "CsI_side_mylar_log", 0, 0, 0);
  CsI_absorber_log = new G4LogicalVolume(aCsI_absorber, CsI_absorber_Material,
                                         "CsI_absorber_log", 0, 0, 0);
  CsI_detector_phys =
      new G4PVPlacement(G4Transform3D(NoRot, *Pos), CsI_detector_log, "CsI",
                        expHall_log, true, 0);
  CsI_mylar_phys =
      new G4PVPlacement(G4Transform3D(NoRot, *Pos_abs), CsI_mylar_log,
                        "CsI_mylar", expHall_log, true, 0);
  CsI_side_mylar_phys =
      new G4PVPlacement(G4Transform3D(NoRot, *Pos), CsI_side_mylar_log,
                        "CsI_side_mylar", expHall_log, true, 0);
  CsI_absorber_phys =
      new G4PVPlacement(G4Transform3D(NoRot, *Pos_abs), CsI_absorber_log,
                        "CsI_absorber", expHall_log, true, 0);

  G4Colour yellow(1.0, 1.0, 0.0);
  G4VisAttributes *Vis_6 = new G4VisAttributes(yellow);
  Vis_6->SetVisibility(true);
  Vis_6->SetForceSolid(true);

  CsI_detector_log->SetVisAttributes(Vis_6);

  G4Colour blue(0.0, 0.0, 1.0);
  G4VisAttributes *Vis_7 = new G4VisAttributes(blue);
  Vis_7->SetVisibility(true);
  Vis_7->SetForceSolid(true);

  CsI_mylar_log->SetVisAttributes(Vis_7);
  CsI_side_mylar_log->SetVisAttributes(Vis_7);

  G4Colour gray(0.5, 0.5, 0.5);
  G4VisAttributes *Vis_8 = new G4VisAttributes(gray);
  Vis_8->SetVisibility(true);
  Vis_8->SetForceSolid(true);

  CsI_absorber_log->SetVisAttributes(Vis_8);

  return CsI_detector_phys;
}

//-----------------------------------------------------------------------------
void CsI_detector_spherical::Report() {
  G4cout << "----> CsI_detector material set to     "
         << CsI_detector_log->GetMaterial()->GetName() << G4endl;
}

//-----------------------------------------------------------------------------
void CsI_detector_spherical::Place(G4ThreeVector shift) {
  G4ThreeVector shift_abs;
  shift_abs += shift;
  // CsI_detector_phys->SetTranslation(shift);
  // CsI_side_mylar_phys->SetTranslation(shift);
  // CsI_mylar_phys->SetTranslation(shift_abs);
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}
//-----------------------------------------------------------------------------
void CsI_detector_spherical::setName() {
  char s[20];
  sprintf(s, "CsI %3d %1d", Id, RingId);
  CsI_detector_phys->SetName(s);
}
