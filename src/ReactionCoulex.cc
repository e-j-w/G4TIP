//First order Coulex E2 excitation based on Rev. Mod. Phys. 28 (1956) 432, mostly page 457
#include "ReactionCoulex.hh"

ReactionCoulex::ReactionCoulex(Projectile* Proj, Recoil* Rec, const G4String& aName)
  : G4VProcess(aName), theRecoil(Rec),theProjectile(Proj) {
  dcmin=0.; // minimum allowed distance of closest approach

  reaction_here=false;
  if (verboseLevel>1) {
    G4cout <<GetProcessName() << " is created "<< G4endl;};
 
  // 18 May 2016: ksi values 1.2-2.0 added
  // 16 Oct 2018: ksi = 4.0 added
  // Table II.8
  ksiArray.push_back(0.0);
  ksiArray.push_back(0.1);
  ksiArray.push_back(0.2);
  ksiArray.push_back(0.3);
  ksiArray.push_back(0.4);
  ksiArray.push_back(0.5);
  ksiArray.push_back(0.6);
  ksiArray.push_back(0.7);
  ksiArray.push_back(0.8);
  ksiArray.push_back(0.9);
  ksiArray.push_back(1.0);
  ksiArray.push_back(1.2);
  ksiArray.push_back(1.4);
  ksiArray.push_back(1.6);
  ksiArray.push_back(1.8);
  ksiArray.push_back(2.0);
  ksiArray.push_back(4.0);

  fksiArray.push_back(0.895);
  fksiArray.push_back(0.859);
  fksiArray.push_back(0.729);
  fksiArray.push_back(0.561);
  fksiArray.push_back(0.4046);
  fksiArray.push_back(0.2781);
  fksiArray.push_back(0.1844);
  fksiArray.push_back(0.1189);
  fksiArray.push_back(7.510E-02);
  fksiArray.push_back(4.663E-02);
  fksiArray.push_back(2.855E-02);
  fksiArray.push_back(1.035E-02);
  fksiArray.push_back(3.628E-03);
  fksiArray.push_back(1.238E-03);
  fksiArray.push_back(4.143E-04);
  fksiArray.push_back(1.363E-04);
  fksiArray.push_back(1.247E-09);

  thetaArray.push_back(0.);
  thetaArray.push_back(10.);
  thetaArray.push_back(20.);
  thetaArray.push_back(30.);
  thetaArray.push_back(40.);
  thetaArray.push_back(50.);
  thetaArray.push_back(60.);
  thetaArray.push_back(70.);
  thetaArray.push_back(80.);
  thetaArray.push_back(90.);
  thetaArray.push_back(100.);
  thetaArray.push_back(110.);
  thetaArray.push_back(120.);
  thetaArray.push_back(130.);
  thetaArray.push_back(140.);
  thetaArray.push_back(150.);
  thetaArray.push_back(160.);
  thetaArray.push_back(170.);
  thetaArray.push_back(180.);

  th000.push_back(1.676E-01);
  th000.push_back(0.000E+00);
  th000.push_back(0.000E+00);
  th000.push_back(0.000E+00);
  th000.push_back(0.000E+00);
  th000.push_back(0.000E+00);
  th000.push_back(0.000E+00);
  th000.push_back(0.000E+00);
  th000.push_back(0.000E+00);
  th000.push_back(0.000E+00);
  th000.push_back(0.000E+00);
  th000.push_back(0.000E+00);
  th000.push_back(0.000E+00);
  th000.push_back(0.000E+00);
  th000.push_back(0.000E+00);
  th000.push_back(0.000E+00);
  th000.push_back(0.000E+00);

  th010.push_back(1.385E-01);
  th010.push_back(1.403E-01);
  th010.push_back(5.210E-02);
  th010.push_back(1.110E-02);
  th010.push_back(1.788E-03);
  th010.push_back(2.443E-04);
  th010.push_back(2.996E-05);
  th010.push_back(3.403E-06);
  th010.push_back(3.652E-07);
  th010.push_back(3.750E-08);
  th010.push_back(3.719E-09);
  th010.push_back(3.374E-11);
  th010.push_back(2.824E-13);
  th010.push_back(2.227E-15);
  th010.push_back(1.679E-17);
  th010.push_back(1.220E-19);
  th010.push_back(1.750E-41);

  th020.push_back(1.178E-01);
  th020.push_back(1.286E-01);
  th020.push_back(1.016E-01);
  th020.push_back(5.780E-02);
  th020.push_back(2.678E-02);
  th020.push_back(1.085E-02);
  th020.push_back(4.005E-03);
  th020.push_back(1.382E-03);
  th020.push_back(4.531E-04);
  th020.push_back(1.427E-04);
  th020.push_back(4.351E-05);
  th020.push_back(3.752E-06);
  th020.push_back(2.998E-07);
  th020.push_back(2.265E-08);
  th020.push_back(1.638E-09);
  th020.push_back(1.144E-10);
  th020.push_back(1.134E-22);

  th030.push_back(1.027E-01);
  th030.push_back(1.087E-01);
  th030.push_back(9.810E-02);
  th030.push_back(7.160E-02);
  th030.push_back(4.474E-02);
  th030.push_back(2.508E-02);
  th030.push_back(1.300E-02);
  th030.push_back(6.350E-03);
  th030.push_back(2.960E-03);
  th030.push_back(1.331E-03);
  th030.push_back(5.810E-04);
  th030.push_back(1.032E-04);
  th030.push_back(1.708E-05);
  th030.push_back(2.680E-06);
  th030.push_back(4.032E-07);
  th030.push_back(5.870E-08);
  th030.push_back(0.929E-16);

  th040.push_back(9.160E-02);
  th040.push_back(9.430E-02);
  th040.push_back(8.730E-02);
  th040.push_back(6.940E-02);
  th040.push_back(4.895E-02);
  th040.push_back(3.154E-02);
  th040.push_back(1.899E-02);
  th040.push_back(1.085E-02);
  th040.push_back(5.950E-03);
  th040.push_back(3.159E-03);
  th040.push_back(1.631E-03);
  th040.push_back(4.076E-04);
  th040.push_back(9.530E-05);
  th040.push_back(2.118E-05);
  th040.push_back(4.523E-06);
  th040.push_back(9.360E-07);
  th040.push_back(0.518E-13);

  th050.push_back(8.320E-02);
  th050.push_back(8.370E-02);
  th050.push_back(7.720E-02);
  th050.push_back(6.340E-02);
  th050.push_back(4.715E-02);
  th050.push_back(3.251E-02);
  th050.push_back(2.113E-02);
  th050.push_back(1.311E-02);
  th050.push_back(7.840E-03);
  th050.push_back(4.553E-03);
  th050.push_back(2.577E-03);
  th050.push_back(7.770E-04);
  th050.push_back(2.203E-04);
  th050.push_back(5.950E-05);
  th050.push_back(1.549E-05);
  th050.push_back(3.913E-06);
  th050.push_back(1.643E-12);

  th060.push_back(7.680E-02);
  th060.push_back(7.580E-02);
  th060.push_back(6.900E-02);
  th060.push_back(5.700E-02);
  th060.push_back(4.341E-02);
  th060.push_back(3.095E-02);
  th060.push_back(2.095E-02);
  th060.push_back(1.361E-02);
  th060.push_back(8.550E-03);
  th060.push_back(5.230E-03);
  th060.push_back(3.123E-03);
  th060.push_back(1.054E-03);
  th060.push_back(3.356E-04);
  th060.push_back(1.022E-04);
  th060.push_back(3.001E-05);
  th060.push_back(8.570E-06);
  th060.push_back(1.269E-11);

  th070.push_back(7.190E-02);
  th070.push_back(6.970E-02);
  th070.push_back(6.240E-02);
  th070.push_back(5.130E-02);
  th070.push_back(3.932E-02);
  th070.push_back(2.846E-02);
  th070.push_back(1.967E-02);
  th070.push_back(1.311E-02);
  th070.push_back(8.470E-03);
  th070.push_back(5.340E-03);
  th070.push_back(3.294E-03);
  th070.push_back(1.191E-03);
  th070.push_back(4.079E-04);
  th070.push_back(1.339E-04);
  th070.push_back(4.249E-05);
  th070.push_back(1.312E-05);
  th070.push_back(4.434E-11);

  th080.push_back(6.800E-02);
  th080.push_back(6.490E-02);
  th080.push_back(5.700E-02);
  th080.push_back(4.643E-02);
  th080.push_back(3.549E-02);
  th080.push_back(2.579E-02);
  th080.push_back(1.798E-02);
  th080.push_back(1.213E-02);
  th080.push_back(7.960E-03);
  th080.push_back(5.100E-03);
  th080.push_back(3.211E-03);
  th080.push_back(1.211E-03);
  th080.push_back(4.338E-04);
  th080.push_back(1.494E-04);
  th080.push_back(4.985E-05);
  th080.push_back(1.621E-05);
  th080.push_back(0.950E-10);

  th090.push_back(6.500E-02);
  th090.push_back(6.120E-02);
  th090.push_back(5.270E-02);
  th090.push_back(4.234E-02);
  th090.push_back(3.210E-02);
  th090.push_back(2.326E-02);
  th090.push_back(1.624E-02);
  th090.push_back(1.100E-02);
  th090.push_back(7.270E-03);
  th090.push_back(4.700E-03);
  th090.push_back(2.986E-03);
  th090.push_back(1.153E-03);
  th090.push_back(4.245E-04);
  th090.push_back(1.506E-04);
  th090.push_back(5.190E-05);
  th090.push_back(1.743E-05);
  th090.push_back(1.477E-10);

  th100.push_back(6.270E-02);
  th100.push_back(5.830E-02);
  th100.push_back(4.930E-02);
  th100.push_back(3.895E-02);
  th100.push_back(2.920E-02);
  th100.push_back(2.100E-02);
  th100.push_back(1.460E-02);
  th100.push_back(9.880E-03);
  th100.push_back(6.530E-03);
  th100.push_back(4.232E-03);
  th100.push_back(2.699E-03);
  th100.push_back(1.054E-03);
  th100.push_back(3.936E-04);
  th100.push_back(1.420E-04);
  th100.push_back(4.983E-05);
  th100.push_back(1.708E-05);
  th100.push_back(1.842E-10);

  th110.push_back(6.080E-02);
  th110.push_back(5.590E-02);
  th110.push_back(4.651E-02);
  th110.push_back(3.617E-02);
  th110.push_back(2.676E-02);
  th110.push_back(1.905E-02);
  th110.push_back(1.314E-02);
  th110.push_back(8.840E-03);
  th110.push_back(5.820E-03);
  th110.push_back(3.769E-03);
  th110.push_back(2.402E-03);
  th110.push_back(9.390E-04);
  th110.push_back(3.526E-04);
  th110.push_back(1.282E-04);
  th110.push_back(4.538E-05);
  th110.push_back(1.572E-05);
  th110.push_back(1.964E-10);

  th120.push_back(5.930E-02);
  th120.push_back(5.410E-02);
  th120.push_back(4.428E-02);
  th120.push_back(3.391E-02);
  th120.push_back(2.475E-02);
  th120.push_back(1.741E-02);
  th120.push_back(1.190E-02);
  th120.push_back(7.940E-03);
  th120.push_back(5.200E-03);
  th120.push_back(3.345E-03);
  th120.push_back(2.123E-03);
  th120.push_back(8.260E-04);
  th120.push_back(3.904E-04);
  th120.push_back(1.125E-04);
  th120.push_back(3.990E-05);
  th120.push_back(1.387E-05);
  th120.push_back(1.869E-10);

  th130.push_back(5.820E-02);
  th130.push_back(5.260E-02);
  th130.push_back(4.252E-02);
  th130.push_back(3.210E-02);
  th130.push_back(2.311E-02);
  th130.push_back(1.606E-02);
  th130.push_back(1.086E-02);
  th130.push_back(7.180E-03);
  th130.push_back(4.660E-03);
  th130.push_back(2.979E-03);
  th130.push_back(1.879E-03);
  th130.push_back(7.240E-04);
  th130.push_back(2.691E-04);
  th130.push_back(9.730E-05);
  th130.push_back(3.439E-05);
  th130.push_back(1.193E-05);
  th130.push_back(1.640E-10);

  th140.push_back(5.730E-02);
  th140.push_back(5.150E-02);
  th140.push_back(4.115E-02);
  th140.push_back(3.068E-02);
  th140.push_back(2.182E-02);
  th140.push_back(1.499E-02);
  th140.push_back(1.003E-02);
  th140.push_back(6.570E-03);
  th140.push_back(4.224E-03);
  th140.push_back(2.678E-03);
  th140.push_back(1.677E-03);
  th140.push_back(6.370E-04);
  th140.push_back(2.344E-04);
  th140.push_back(8.400E-05);
  th140.push_back(2.947E-05);
  th140.push_back(1.016E-05);
  th140.push_back(1.364E-10);

  th150.push_back(5.660E-02);
  th150.push_back(5.070E-02);
  th150.push_back(4.013E-02);
  th150.push_back(2.961E-02);
  th150.push_back(2.085E-02);
  th150.push_back(1.418E-02);
  th150.push_back(9.390E-03);
  th150.push_back(6.090E-03);
  th150.push_back(3.888E-03);
  th150.push_back(2.445E-03);
  th150.push_back(1.519E-03);
  th150.push_back(5.690E-04);
  th150.push_back(2.069E-04);
  th150.push_back(7.330E-05);
  th150.push_back(2.546E-05);
  th150.push_back(8.700E-06);
  th150.push_back(1.106E-10);

  th160.push_back(5.620E-02);
  th160.push_back(5.010E-02);
  th160.push_back(3.942E-02);
  th160.push_back(2.887E-02);
  th160.push_back(2.017E-02);
  th160.push_back(1.361E-02);
  th160.push_back(8.950E-03);
  th160.push_back(5.760E-03);
  th160.push_back(3.650E-03);
  th160.push_back(2.280E-03);
  th160.push_back(1.407E-03);
  th160.push_back(5.210E-04);
  th160.push_back(1.870E-04);
  th160.push_back(6.560E-05);
  th160.push_back(2.254E-05);
  th160.push_back(7.630E-06);
  th160.push_back(0.904E-10);

  th170.push_back(5.590E-02);
  th170.push_back(4.980E-02);
  th170.push_back(3.900E-02);
  th170.push_back(2.844E-02);
  th170.push_back(1.977E-02);
  th170.push_back(1.328E-02);
  th170.push_back(8.690E-03);
  th170.push_back(5.570E-03);
  th170.push_back(3.509E-03);
  th170.push_back(2.181E-03);
  th170.push_back(1.340E-03);
  th170.push_back(4.918E-04);
  th170.push_back(1.751E-04);
  th170.push_back(6.090E-05);
  th170.push_back(2.078E-05);
  th170.push_back(6.980E-06);
  th170.push_back(0.779E-10);

  th180.push_back(5.580E-02);
  th180.push_back(4.969E-02);
  th180.push_back(3.887E-02);
  th180.push_back(2.829E-02);
  th180.push_back(1.963E-02);
  th180.push_back(1.316E-02);
  th180.push_back(8.600E-03);
  th180.push_back(5.500E-03);
  th180.push_back(3.462E-03);
  th180.push_back(2.148E-03);
  th180.push_back(1.318E-03);
  th180.push_back(4.822E-04);
  th180.push_back(1.712E-04);
  th180.push_back(5.930E-05);
  th180.push_back(2.019E-05);
  th180.push_back(6.760E-06);
  th180.push_back(0.737E-10);

  fthksi.push_back(th000);
  fthksi.push_back(th010);
  fthksi.push_back(th020);
  fthksi.push_back(th030);
  fthksi.push_back(th040);
  fthksi.push_back(th050);
  fthksi.push_back(th060);
  fthksi.push_back(th070);
  fthksi.push_back(th080);
  fthksi.push_back(th090);
  fthksi.push_back(th100);
  fthksi.push_back(th110);
  fthksi.push_back(th120);
  fthksi.push_back(th130);
  fthksi.push_back(th140);
  fthksi.push_back(th150);
  fthksi.push_back(th160);
  fthksi.push_back(th170);
  fthksi.push_back(th180);

}
//---------------------------------------------------------------------
ReactionCoulex::~ReactionCoulex() { ; }
//---------------------------------------------------------------------
G4VParticleChange* ReactionCoulex::PostStepDoIt(const G4Track& aTrack, const G4Step&) {

  aParticleChange.Initialize(aTrack);
  //
  // Stop the current particle, if requested by G4UserLimits 
  // 
  if(reaction_here) {
    reaction_here=false;
    G4DynamicParticle* ProjectileOut;
    G4DynamicParticle* RecoilOut;
    ProjectileOut =new G4DynamicParticle();
    RecoilOut =new G4DynamicParticle();
    
    if(SetupReactionProducts(aTrack,ProjectileOut,RecoilOut)) {
      aParticleChange.ProposeTrackStatus(fStopAndKill);
      aParticleChange.SetNumberOfSecondaries(2);    
      aParticleChange.AddSecondary(ProjectileOut,posIn,true);
      aParticleChange.AddSecondary(RecoilOut,posIn,true);
      aParticleChange.GetSecondary(0)->SetWeight(theWeight);
      aParticleChange.GetSecondary(1)->SetWeight(theWeight);
      sumWeights += theWeight;
      sumProj++;
    }
  }
  
  return &aParticleChange;
}
//-----------------------------------------------------------------
G4double ReactionCoulex::PostStepGetPhysicalInteractionLength(const G4Track& aTrack, G4double, G4ForceCondition* condition) {
  reaction_here=false;
  *condition=NotForced;
  
  G4String name=aTrack.GetVolume()->GetLogicalVolume()->GetName();
  
  if(name=="target_log") {
    G4UserLimits* pUserLimits = aTrack.GetVolume()->GetLogicalVolume()->GetUserLimits();
    G4double ZReaction=pUserLimits->GetUserMinRange(aTrack);
    G4double ZCurrent=aTrack.GetPosition().getZ();
    G4double Z=ZReaction-ZCurrent;
    if(Z<0) {
      // G4cout<<" Past the reaction point"<<G4endl;
      // G4cout<<" Volume "<<name<<G4endl;
      // G4cout<<" Z[mm]: reaction "<<ZReaction/mm<<" current "<<ZCurrent/mm<<" DZ "<<Z/mm<<G4endl;
      // getc(stdin);
      return DBL_MAX;
    }
    if(Z>eps)	{
      G4ThreeVector dir=aTrack.GetDynamicParticle()->GetMomentumDirection();
	      
      dir*=(ZReaction-ZCurrent);
      // G4cout<<" Before the reaction point"<<G4endl;
      // G4cout<<" Volume "<<name<<G4endl;
      // G4cout<<" Z[mm]: reaction "<<ZReaction/mm<<" current "<<ZCurrent/mm<<" DZ "<<Z/mm<<G4endl;
      // getc(stdin);
      return dir.mag();
    }
    if(Z<=eps) {	   
      reaction_here=true;
      // G4cout<<setprecision(6)<<"ZReaction: "<<ZReaction<<G4endl;
      // getc(stdin);
      aTrack.GetVolume()->GetLogicalVolume()->GetUserLimits()->SetUserMinRange(-DBL_MAX);
      return 0.;
    }
  }  
  return DBL_MAX;
}

//---------------------------------------------------------
G4bool ReactionCoulex::SetupReactionProducts(const G4Track & aTrack,G4DynamicParticle* ProjectileOut, G4DynamicParticle* RecoilOut) {
  G4double Ain;
  G4double Zin;
  G4ThreeVector dirIn,pdir,rdir,perpIn1,perpIn2;
  G4ThreeVector pIn;
  G4double KEIn;
  G4double theta;
  G4double Eprime;
  G4double t,tbar;
  G4double phi;
  G4double sint,cost,sinp,cosp;
  G4double p_par1,p_par2,p_perp,r;
  G4double ksi,fksi;
  G4double dc; // distance of closest approach in fm
  G4double sigmaRatio; // rxn depth/face
  G4double rand; // uniform RNG

  Ain=aTrack.GetDynamicParticle()->GetDefinition()->GetAtomicMass();
  if(Ain != A1) 
    return FALSE;

  Zin=aTrack.GetDynamicParticle()->GetDefinition()->GetAtomicNumber();
  if(Zin != Z1) 
    return FALSE;
  
  ProjectileOut->SetDefinition(proj);
  RecoilOut->SetDefinition(rec);

  // check if energy in LAB is sufficienct for excitation
  // if so check that ksi and f(ksi) are good values
  // for good ksi and f(ksi) calculate ratio of XC at reaction energy
  // to ratio on face and use RNG to determine if reaction goes
  KEIn = aTrack.GetDynamicParticle()->GetKineticEnergy(); // energy of the incident particle
  if(KEIn > DEp) {
    Eprime = KEIn-DE*(A1+A2)/A2; // internal energy of the center of mass 1/2*mu*Vrel^2
    ksi = GetKsi(KEIn);
    fksi = GetfKsi(ksi);
    if(fksi > 0.0) {
      sigmaRatio = Eprime*fksi/(EprimeFace*thef);
      rand = G4UniformRand();
      if(rand < sigmaRatio) {
	// printf(" KEIn: %10.4f\n c: %10.4f\n ce: %10.4f\n xi: %10.4f\n f(xi): %10.4e\n",KEIn,c,ce,ksi,fksi);
	// printf("Cross section at reaction depth          : %10.4e b\n",sigma);
	// printf("Cross section at face                    : %10.4e b\n",sigmaFace);
	// printf("Cross section ratio at reaction depth    : %10.4e\n",sigmaRatio);
	// printf("For rand %10.4e and ratio %10.4e we will run a reaction!\n",rand,sigmaRatio);
      } 
      else {
	// printf("For rand %10.4e and ratio %10.4e skipping event... \n",rand,sigmaRatio);
	dropRand++;
	return FALSE;
      }
    } 
    else {
      // printf("f(ksi) = %.2f --> sigma = 0 due to ksi = %.4f out of range (0,4)\n",fksi,ksi);
      dropKsi++;
      return FALSE;
    }
  }
  else {
    // printf("KEIn: %10.4f\n Not enough energy to excite projectile with DEp = %.4f! Skipping event...\n",KEIn,DEp);
    dropE++;
    return FALSE;
  }
  // getc(stdin);

  //clear vectors needed
  thefth.clear();
  thbin.clear();
  fbin.clear();
  thlookup.clear();

  // setup lookup table for angular distribution of rxn products
  Calcfthksi(ksi, &thefth); 
  SetupLookupGenerator(fksi); 

  // vector<G4double>::iterator it;
  // G4cout << "For ksi at reaction depth: " << ksi << G4endl;
  // G4cout<<"Printing thefth"<<G4endl;
  // it=thefth.begin();
  // for(;it<thefth.end();it++)
  //   G4cout<<(*it)<<G4endl;

  // getc(stdin);

  // G4cout<<"Printing thbin"<<G4endl;
  // it=thbin.begin();
  // for(;it<thbin.end();it++)
  //   G4cout<<(*it)<<G4endl;

  // getc(stdin);

  // G4cout<<"Printing fbin"<<G4endl;
  // it=fbin.begin();
  // for(;it<fbin.end();it++)
  //   G4cout<<(*it)<<G4endl;

  // getc(stdin);

  // G4cout<<"Printing thlookup with size " << thlookup.size() << G4endl;
  // vector<G4int>::iterator it2;
  // it2=thlookup.begin();
  // for(;it2<thlookup.end();it2++)
  //   G4cout<<(*it2)<<G4endl;

  // getc(stdin);
  
  dirIn = aTrack.GetMomentumDirection();
  posIn = aTrack.GetPosition();
  pIn = aTrack.GetMomentum(); 

  tbar = sqrt(KEIn/Eprime);
  t = A1/A2*tbar;
  // printf("tbar %f t %f\n",tbar,t);
  // getc(stdin);
  
  theta = GetTheta(); // in the CM
  // printf("theta = %.2f\n",theta);
  // getc(stdin);
  
  dc = 0.5*AHC*Z1*Z2/KEIn*(1+A1/A2)*(1+1/sin(0.5*theta*DEG2RAD));
  // printf("dc %.4f\n",dc);
  // getc(stdin);
  
  if(dc > dcmin) {      
    sint=sin(theta*DEG2RAD);
    cost=cos(theta*DEG2RAD);
    phi=TWOPI*G4UniformRand();
    sinp=sin(phi);
    cosp=cos(phi);
      
    //this is momentum in the lab assuming the z axis as the beam axis
    r=A2/(A1+A2)*pIn.mag()/tbar;
    p_perp=r*sint;
    p_par1=r*(cost+t);
    p_par2=r*(tbar-cost);
      
    //this is the rotation on the z-axis defined by the direction of the incoming projectile 
    perpIn1.setX(dirIn.getY());
    perpIn1.setY(dirIn.getX());
    perpIn1.setZ(0.);
    if(perpIn1.mag()==0.) {
      perpIn1.setX(1.);
      perpIn1.setY(0.);
      perpIn1.setZ(0.);
      perpIn2.setX(0.);
      perpIn2.setY(1.);
      perpIn2.setZ(0.);
    } 
    else {
      perpIn1.setMag(1.);
      perpIn2=dirIn.cross(perpIn1);
    }
      
    pdir=p_par1*dirIn+p_perp*cosp*perpIn1+p_perp*sinp*perpIn2;
    rdir=p_par2*dirIn-p_perp*cosp*perpIn1-p_perp*sinp*perpIn2;
      
    ProjectileOut->SetMomentum(pdir); 
    RecoilOut->SetMomentum(rdir);

    theWeight = 1.0; // "weighted" by XC selection above, kept for ease-of-use

    return TRUE;
  }  
  else
    return FALSE;
}
//---------------------------------------------------------
void ReactionCoulex::TargetFaceCrossSection() {
  
  G4cout << "---------- SETUP OF DECAY PRODUCTS ----------" << G4endl;
  G4double T1,T2;
  G4double  KE;
  G4double  c,ce;
  
  A1=theProjectile->getA();
  Z1=theProjectile->getZ(); 
  Ex1=theProjectile->getEx()/MeV;
  T1=theProjectile->getTau()/ns*1000.; // in ps
  
  A2=theRecoil->getA();
  Z2=theRecoil->getZ();
  Ex2=theRecoil->getEx()/MeV;
  T2=theRecoil->getTau()/ns*1000.; // in ps
  
  printf("\nMinimum distance of closest approach: %5.2f fm\n",dcmin);
  
  if(Ex1*Ex2 != 0.0) {
    printf("Simultaneous excitation of the projectile and target are not handled\n");
    exit(0);	     
  }
  if(Ex1+Ex2 == 0.0) {
    printf("Excitation of either the projectile or the target has to be defined\n");
    exit(0);	     
  }
  
  if( (Ex1 > 0.0) && (Ex2 == 0.0) ) {
    ProjEx = true;
    printf("Projectile excitation\n");
    if(T1 > 0)
      BE2=5.0*0.08162025/T1/pow(Ex1,5.0); // from Eq. II A.56 multiplied by ahc (a = fine struct. const.)
    else {
      printf("Projectile de-excitation lifetime not defined %4.2f\n",T1);
      exit(0);
    }
  }
  else {
    ProjEx=false;
    printf("Target recoil excitation\n");
    if(T2 > 0)
      BE2=5.0*0.08162025/T2/pow(Ex2,5.0); // from Eq. II A.56 multiplied by ahc (a = fine struct. const.)
    else {
      printf("Target recoil de-excitation lifetime not defined %4.2f\n",T2);
      exit(0);
    }
  }  
  
  printf("Projectile A                        : %5d\n",(int)A1);
  printf("Projectile Z                        : %5d\n",(int)Z1);
  if(ProjEx) {
    printf("Projectile excitation energy        : %5.3f MeV\n",Ex1);
    printf("Projectile deexcitation lifetime    : %5.2f ps\n",T1);
    printf("Projectile B(E2,0+=>2+)             : %5.2f e^2b^2\n",BE2);
  }
  printf("Target recoil A                     : %5d\n",(int)A2);
  printf("Target recoil Z                     : %5d\n",(int)Z2);
  if(!ProjEx) {
    printf("Target recoil excitation energy     : %5.3f MeV\n",Ex2);
    printf("Target recoil deexcitation lifetime : %5.2f ps\n",T2);
    printf("Target recoil B(E2,0+=>2+)          : %5.2f e^2b^2\n",BE2);
  }
  
  if(ProjEx)
    DE = Ex1;
  else
    DE = Ex2;

  KE = theProjectile->getKE(); // this is the kinetic energy of the projectile in the lab used to get the vi two lines down
  DEp = (1.0+A1/A2)*DE;  // Eq. II C.4 and explanation below (CM internal energy 1/2*mu*Vrel^2)
  EprimeFace = KE-DEp;
  ksiFace = GetKsi(KE);
  c = 4.819*A1/Z1/Z1/(1.0+A1/A2)/(1.0+A1/A2); // Eq. II C.17 the case of E2 with Z1 instead of Z2, see Sec. II A.6
  ce = c*(KE-DEp)*BE2; // Part of Eq. II C.15
  thef = GetfKsi(ksiFace); // from lookup table
  
  //clear vectors needed
  thefth.clear();
  thbin.clear();
  fbin.clear();
  thlookup.clear();

  Calcfthksi(ksiFace, &thefth); 
  SetupLookupGenerator(thef); 

  // vector<G4double>::iterator it;
  // G4cout << "For ksi at face: " << ksiFace << G4endl;
  // G4cout<<"Printing thefth"<<G4endl;
  // it=thefth.begin();
  // for(;it<thefth.end();it++)
  //   G4cout<<(*it)<<G4endl;

  // G4cout<<"Printing thbin"<<G4endl;
  // it=thbin.begin();
  // for(;it<thbin.end();it++)
  //   G4cout<<(*it)<<G4endl;

  // G4cout<<"Printing fbin"<<G4endl;
  // it=fbin.begin();
  // for(;it<fbin.end();it++)
  //   G4cout<<(*it)<<G4endl;

  // G4cout<<"Printing thlookup with size " << thlookup.size() << G4endl;
  // vector<G4int>::iterator it2;
  // it2=thlookup.begin();
  // for(;it2<thlookup.end();it2++)
  //   G4cout<<(*it2)<<G4endl;

  // getc(stdin);

  sigmaFace = ce*thef; // Full Eq. II C.15, cross section on the target face in barns
  printf("Target face xi                      :%10.4f\n",ksiFace);
  printf("Target face f(xi)                   :%10.4f\n",thef);
  printf("Target face cross section           :%10.4f b\n",sigmaFace);

  proj = G4IonTable::GetIonTable()->GetIon(Z1,A1,Ex1);
  rec = G4IonTable::GetIonTable()->GetIon(Z2,A2,Ex2);

  if (proj == NULL) {
    G4cerr << "Could not find outgoing projectile in the particle table "
           << Z1 << " " << A1 << G4endl;
    exit(EXIT_FAILURE);
  }

  if (rec == NULL) {
    G4cerr << "Could not find outgoing recoil in the particle table "
           << Z2 << " " << A2 << G4endl;
    exit(EXIT_FAILURE);
  }
  
  if(ProjEx) {
    rec->SetPDGStable(true);
    proj->SetPDGStable(false);
    proj->SetPDGLifeTime(theProjectile->getTau());
    G4DecayTable *ProjDecTab = proj->GetDecayTable(); 
    if (ProjDecTab == NULL) {
      ProjDecTab = new G4DecayTable();
      proj->SetDecayTable(ProjDecTab);
    }
    GammaDecayChannel *ProjDec = new GammaDecayChannel(-1,proj,1,Ex1,Ex1,0); // single step
    ProjDecTab->Insert(ProjDec);
    // ProjDecTab->DumpInfo();
    // getc(stdin);
    // make sure that the projectile has the decay process in its manager
    G4ProcessManager *proj_pm = proj->GetProcessManager();
    if (proj_pm == NULL) {
      G4cerr << "Could not find process manager for the projectile." << G4endl;
      exit(EXIT_FAILURE);
    }
    decay = new G4Decay();      
    if (proj_pm->GetProcessActivation(decay) == false) {
      G4cout<<"-> adding the projectile decay process"<<G4endl;
      proj_pm->SetParticleType(proj);
      proj_pm->AddProcess(decay,1,-1,5);
    }      
    // proj_pm->DumpInfo();
    // getc(stdin);      
  }
  else {
    proj->SetPDGStable(true);
    rec->SetPDGStable(false);
    rec->SetPDGLifeTime(theRecoil->getTau());
    G4DecayTable *RecDecTab = rec->GetDecayTable(); 
    if (RecDecTab == NULL) {
      RecDecTab = new G4DecayTable();
      rec->SetDecayTable(RecDecTab);
    }
    GammaDecayChannel *RecDec = new GammaDecayChannel(-1,rec,1,Ex2,Ex2,0); // single step
    RecDecTab->Insert(RecDec);
    // RecDecTab->DumpInfo();
    // getc(stdin);
    // make sure that the recoil has the decay process in its manager
    G4ProcessManager *rec_pm = rec->GetProcessManager();
    if (rec_pm == NULL) {
      G4cerr << "Could not find process manager for the recoil." << G4endl;
      exit(EXIT_FAILURE);
    }
    decay = new G4Decay();
    if (rec_pm->GetProcessActivation(decay) == false) {
      G4cout<<"-> adding the recoil decay process"<<G4endl;
      rec_pm->SetParticleType(rec);
      rec_pm->AddProcess(decay,1,-1,5);
    }
    // rec_pm->DumpInfo();
    // getc(stdin);
  }
  
  sumWeights = 0.0;
  sumProj = 0; // good events
  dropRand = 0; // dropped due to RNG < XC ratio
  dropE = 0; // droppd due to energy requirement
  dropKsi = 0; // dropped due to ksi limits

  // some legacy stuff?
  // not sure what the purpose is
  vector <G4double> *f=theProjectile->getf();
  vector <G4double> *th=theProjectile->getth();
  for(unsigned i=0;i<thetaArray.size();i++) {
    (*th)[i] = thetaArray[i];
    (*f)[i] = dfofTheta(thetaArray[i],&thefth);
  }
  theProjectile->setthef(thef);

  G4cout << "---------- END OF DECAY PRODUCT SETUP ----------" << G4endl;
}

//---------------------------------------------------------
// for total XC fksi at given adiabaticity ksi, create a 
// lookup table of the differential XC as a function of 
// theta and ksi from previously determined differential 
// XC values as well as table of bin #s which samples this
// distribution
//---------------------------------------------------------
void ReactionCoulex::SetupLookupGenerator(G4double fksi)
{
  unsigned i;
  G4int k;
  G4double F,slope;
  vector<G4int> limits;

  for(i=1;i<thetaArray.size();i++) {
    thbin.push_back(0.5*(thetaArray[i-1]+thetaArray[i]));
    F=thefth[i-1]*cos(thetaArray[i-1]*DEG2RAD);
    F-=thefth[i]*cos(thetaArray[i]*DEG2RAD);
    slope=thefth[i]-thefth[i-1];
    slope/=(thetaArray[i]-thetaArray[i-1]);
    slope/=DEG2RAD;
    F+=slope*(sin(thetaArray[i]*DEG2RAD)-sin(thetaArray[i-1]*DEG2RAD));
    F*=TWOPI;
    fbin.push_back(F);
  }

  limits.push_back(0);
  F=0.;
  for(i=0;i<thbin.size();i++) {
    F+=fbin[i];
    limits.push_back(G4int(10000.*F/fksi));
  }

  for(i=1;i<limits.size();i++)
    for(k=limits[i-1];k<limits[i];k++)
      thlookup.push_back(i-1);
    
}
//---------------------------------------------------------
// minimal possible calculation for determining ksi
//---------------------------------------------------------
G4double ReactionCoulex::GetKsi(G4double KE)
{
  G4double zeta,sqz,eti,etf,ksi;
  zeta = DEp/KE; // Eq. II C.5 dimensionless
  sqz = sqrt(1.0-zeta);
  eti = 0.5*Z1*Z2*sqrt(A1/10.008/KE); // Eq. II C.8
  etf = eti/sqz; // Eq. II C.9
  ksi = etf-eti; // by definition
  return ksi;
}
//---------------------------------------------------------
G4double ReactionCoulex::GetTheta() {
  //returns the scattering angle in the CM according to Tab. II.8 p. 464
  G4double xeps=0.0001;
  G4int bin;
  G4double th1,th2,f1,f2,F,r,x1,x2,y1,y2,y;
  G4double th;
  //first look up the bin
  bin = thlookup[(G4int)(G4UniformRand()*thlookup.size())];
  th1 = thetaArray[bin];
  th2 = thetaArray[bin+1];
  f1 = thefth[bin];
  f2 = thefth[bin+1];

  F = fbin[bin]/TWOPI;
  r = G4UniformRand();
 
  x1 = th1;
  y1 = FineThetaFunction(x1,th1,th2,f1,f2,F,r);
  if(fabs(y1) < xeps) return th1;

  x2 = th2;
  y2 = FineThetaFunction(x2,th1,th2,f1,f2,F,r);
  if(fabs(y2) < xeps) return th2;

  th = thbin[bin];
  while(fabs(y = FineThetaFunction(th,th1,th2,f1,f2,F,r)) > xeps) {
    if(y < 0) { 
      x1 = th;
      y1 = y;
    }
    if(y >= 0) {
      x2 = th;
      y2 = y;
    }
    th = x1-y1*(x2-x1)/(y2-y1);
  }
  return th;
}
//---------------------------------------------------------
G4double ReactionCoulex::FineThetaFunction(G4double th,G4double th1, G4double th2, G4double f1, G4double f2, G4double F, G4double r)
{
  G4double f,g,dth,df;
  dth = th2-th1;
  df = f2-f1;
  f = f1+(th-th1)*df/dth;
  g = f1*cos(th1*DEG2RAD)-f*cos(th*DEG2RAD)+df/dth/DEG2RAD*(sin(th*DEG2RAD)-sin(th1*DEG2RAD));
  return g/F-r;
}
//---------------------------------------------------------
G4double ReactionCoulex::dfdOmega(G4double ksi,G4double theta)
{
  vector<G4double>* fth=new vector<G4double>;
  if(Calcfthksi(ksi,fth)) { // 0 if ksi out of range
    G4double dfT = dfofTheta(theta,fth);
    delete fth; // free the memory!
    return dfT;
  }
  else {
    delete fth;
    return 0.0;
  }
}
//---------------------------------------------------------
G4double ReactionCoulex::dfofTheta(G4double theta,vector<G4double>* fth)
{
  unsigned i;
  G4double x1,y1,x2,y2,x,y;

  // G4cout<<"Printing thefth"<<G4endl;
  // vector<G4double>::iterator it;
  // it=fth->begin();
  // for(;it<fth->end();it++)
  //   G4cout<<(*it)<<G4endl;
  // getc(stdin);

  for(i=1;i<thetaArray.size();i++)
    if((theta>=thetaArray[i-1])&&(theta<thetaArray[i]))
      break;
  x1 = thetaArray[i-1];
  y1 = (*fth)[i-1];
  x2 = thetaArray[i];
  y2 = (*fth)[i];
  x = theta;
  y = y1+(y2-y1)*(x-x1)/(x2-x1);
  return y;
}
//---------------------------------------------------------
G4int ReactionCoulex::Calcfthksi(G4double ksi,vector<G4double>* fth)
{
  G4int shift;
  G4double x1,x2,y1,y2,y,dx;

  // return 0 if out of range of lookup table
  if( (ksi <= 0.0) || (ksi >= 4.0) ) return 0;

  shift=0;
  vector<G4double>::iterator itksi = ksiArray.begin();
  for(;itksi<ksiArray.end()-1;itksi++) {
      if((ksi>=(*itksi))&&(ksi<=(*(itksi+1))))
	break;
      shift++;
    }
  x1=*itksi;
  x2=*(itksi+1);
  dx=x2-x1;

  vector<G4double>::iterator it;
  vector<vector<G4double> >::iterator itfthksi = fthksi.begin();
  for(;itfthksi<fthksi.end();itfthksi++) {
      it = (*itfthksi).begin();
      y1=*(it+shift);
      y2=*(it+shift+1);
      y=y1+(y2-y1)/dx*(ksi-x1);
      fth->push_back(y);
    }

  // G4cout<<"Printing thefth for ksi "<<ksi<<G4endl;
  // it=fth.begin();
  // for(;it<fth.end();it++)
  //   G4cout<<(*it)<<G4endl;
  // getc(stdin);

  return 1;
}

//---------------------------------------------------------
G4double ReactionCoulex::GetfKsi(G4double ksi)
{
  G4int shift = 0;
  G4double fksi = 0.0;
  G4double x1 = 0.0, x2 = 0.0,y1 = 0.0, y2 = 0.0, dx = 0.0, dy = 0.0;

  // return 0 if out of range of lookup table
  if( (ksi <= 0.0) && (ksi >= 4.0) ) return 0;
  
  vector<G4double>::iterator it = ksiArray.begin();
  for(; it<ksiArray.end()-1; it++) {
    if( (ksi >= (*it)) && (ksi <= (*(it+1))) )
      break;
    shift++;
  }
  x1 = *it;
  x2 = *(it+1);
  dx = x2-x1;
  it = fksiArray.begin();
  y1 = *(it+shift);
  y2 = *(it+shift+1);
  dy = y2-y1;    
  fksi = y1+(ksi-x1)*dy/dx;    
  // G4cout << setprecision(6);
  // G4cout << "ksi: " << ksi << G4endl;
  // G4cout << "x1: " << x1 << " x2: " << x2 << " dx: " << dx << " shift: " << shift << G4endl;
  // G4cout << "y1: " << y1 << " y2: " << y2 << " dy: " << dy << G4endl;
  // G4cout << "fksi: " << fksi << G4endl;
  // getc(stdin);
  
  return fksi;
}
