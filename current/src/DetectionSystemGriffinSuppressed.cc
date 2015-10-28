#include "DetectorConstruction.hh"
#include "GriffinMessenger.hh"

#include "G4Material.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Sphere.hh" 
#include "G4Para.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4Trap.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4AssemblyVolume.hh"

#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"

#include "G4SDManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "DetectionSystemGriffin.hh"


///////////////////////////////////////////////////////////////////////
// The ::DetectionSystemGriffin constructor instatiates all the 
// Logical and Physical Volumes used in the detector geometery, and the
// ::~DetectionSystemGriffin destructor deletes them from the stack 
// when they go out of scope
///////////////////////////////////////////////////////////////////////
DetectionSystemGriffin::DetectionSystemGriffin( G4int sel, G4int suppSwitch, G4double detRad, G4int hevimetSel ):
    ///////////////////////////////////////////////////////////////////
    // LogicalVolumes
    ///////////////////////////////////////////////////////////////////
      
    // LogicalVolumes in ConstructComplexDetectorBlock
    germanium_block1_log(0), germanium_hole_log(0), inner_dead_layer_log(0),
    inner_dead_layer_cap_log(0), outer_dead_layer_log(0), inter_crystal_electrodeMat_back_log(0), 
    inter_crystal_electrodeMat_front_log(0),
      
    // LogicalVolumes in ConstructDetector
    front_face_log(0), right_bent_piece_log(0), left_bent_piece_log(0),
    top_bent_piece_log(0), bottom_bent_piece_log(0), right_wedge_log(0),
    left_wedge_log(0), top_wedge_log(0), bottom_wedge_log(0),
    upper_right_cone_log(0), lower_right_cone_log(0),
    upper_left_cone_log(0), lower_left_cone_log(0),
    upper_right_tube_log(0), lower_right_tube_log(0),
    upper_left_tube_log(0), lower_left_tube_log(0),
    right_side_panel_log(0), left_side_panel_log(0),
    top_side_panel_log(0), bottom_side_panel_log(0), 
    rear_plate_log(0), finger_shell_log(0), tank_log(0),

    // LogicalVolumes in ConstructBasicDetectorBlock    
    germanium_block_log(0),

    // LogicalVolumes in ConstructColdFinger
    end_plate_log(0), finger_log(0), extra_cold_block_log(0),
    triangle_post_log(0), fet_air_hole_log(0), cooling_bar_log(0),
    cooling_side_block_log(0), structureMat_cold_finger_log(0),

    // LogicalVolumes in ConstructBGOCasing
    back_BGO_log(0), BGO_casing_log(0),

    // LogicalVolumes in ConstructNewSuppressorCasing
    back_quarter_suppressor_shell_log(0),
    right_suppressor_shell_log(0),
    left_suppressor_shell_log(0),
    right_suppressor_shell_extension_log(0),
    left_suppressor_shell_extension_log(0),
    back_quarter_suppressor_log(0), right_suppressor_log(0),
    left_suppressor_log(0), right_suppressor_extension_log(0),
    left_suppressor_extension_log(0),

    // LogicalVolumes in ConstructNewHeavyMet 
    hevimet_log(0) 
{ 
  G4ThreeVector my_move_null(0, 0, 1);
  this->move_null = my_move_null * 0;
  G4RotationMatrix* my_rotate_null = new G4RotationMatrix;
  this->rotate_null = my_rotate_null;
  
  /////////////////////////////////////////////////////////////////////
  // Coords for GRIFFIN
  // Note that the GRIFFIN lampshade angles are rotated by 45 degrees with respect to those of TIGRESS.
  // Modified coords for TIGRESS are below!
  /////////////////////////////////////////////////////////////////////
  // theta
  this->coords[0][0] 	= 45.0;
  this->coords[1][0] 	= 45.0;
  this->coords[2][0] 	= 45.0;
  this->coords[3][0] 	= 45.0;
  this->coords[4][0] 	= 90.0;
  this->coords[5][0] 	= 90.0;
  this->coords[6][0] 	= 90.0;
  this->coords[7][0] 	= 90.0;
  this->coords[8][0] 	= 90.0;
  this->coords[9][0] 	= 90.0;
  this->coords[10][0] 	= 90.0;
  this->coords[11][0] 	= 90.0;
  this->coords[12][0] 	= 135.0;  
  this->coords[13][0] 	= 135.0;  
  this->coords[14][0] 	= 135.0;  
  this->coords[15][0] 	= 135.0;      
  // phi
  this->coords[0][1] 	= 67.5;
  this->coords[1][1] 	= 157.5;
  this->coords[2][1] 	= 247.5;
  this->coords[3][1] 	= 337.5;
  this->coords[4][1] 	= 22.5;
  this->coords[5][1] 	= 67.5;
  this->coords[6][1] 	= 112.5;
  this->coords[7][1] 	= 157.5;
  this->coords[8][1] 	= 202.5;
  this->coords[9][1] 	= 247.5;
  this->coords[10][1] 	= 292.5;
  this->coords[11][1] 	= 337.5;
  this->coords[12][1] 	= 67.5;
  this->coords[13][1] 	= 157.5;
  this->coords[14][1] 	= 247.5;
  this->coords[15][1] 	= 337.5;
  // yaw (alpha) 
  this->coords[0][2] 	= 0.0;
  this->coords[1][2] 	= 0.0;
  this->coords[2][2] 	= 0.0;
  this->coords[3][2] 	= 0.0;
  this->coords[4][2] 	= 0.0;
  this->coords[5][2] 	= 0.0;
  this->coords[6][2] 	= 0.0;
  this->coords[7][2] 	= 0.0;
  this->coords[8][2] 	= 0.0;
  this->coords[9][2] 	= 0.0;
  this->coords[10][2] 	= 0.0;
  this->coords[11][2] 	= 0.0;
  this->coords[12][2] 	= 0.0;  
  this->coords[13][2] 	= 0.0;  
  this->coords[14][2] 	= 0.0;  
  this->coords[15][2] 	= 0.0;    
  // pitch (beta)
  this->coords[0][3] 	= -45.0;
  this->coords[1][3] 	= -45.0;
  this->coords[2][3] 	= -45.0;
  this->coords[3][3] 	= -45.0;
  this->coords[4][3] 	= 0.0;
  this->coords[5][3] 	= 0.0;
  this->coords[6][3] 	= 0.0;
  this->coords[7][3] 	= 0.0;
  this->coords[8][3] 	= 0.0;
  this->coords[9][3] 	= 0.0;
  this->coords[10][3] 	= 0.0;
  this->coords[11][3] 	= 0.0;
  this->coords[12][3] 	= 45.0;  
  this->coords[13][3] 	= 45.0;  
  this->coords[14][3] 	= 45.0;  
  this->coords[15][3] 	= 45.0;   
  // roll (gamma)
  this->coords[0][4] 	= 67.5;
  this->coords[1][4] 	= 157.5;
  this->coords[2][4] 	= 247.5;
  this->coords[3][4] 	= 337.5;
  this->coords[4][4] 	= 22.5;
  this->coords[5][4] 	= 67.5;
  this->coords[6][4] 	= 112.5;
  this->coords[7][4] 	= 157.5;
  this->coords[8][4] 	= 202.5;
  this->coords[9][4] 	= 247.5;
  this->coords[10][4] 	= 292.5;
  this->coords[11][4] 	= 337.5;
  this->coords[12][4] 	= 67.5;
  this->coords[13][4] 	= 157.5;
  this->coords[14][4] 	= 247.5;
  this->coords[15][4] 	= 337.5;

  // Note that the GRIFFIN lampshade angles are rotated by 45 degrees with respect to those of TIGRESS.
  //  Uncomment this for TIGRESS!
  //
  // ASC 7 Oct 2015
  // useTigressPositions now does this when the detector is placed, leave this commented and set that 
  // variable to the proper value!
  //
  // phi
 // this->coords[0][1] 	= this->coords[0][1] - 45.0;
 // this->coords[1][1] 	= this->coords[1][1] - 45.0;
 // this->coords[2][1] 	= this->coords[2][1] - 45.0;
 // this->coords[3][1] 	= this->coords[3][1] - 45.0;
 // this->coords[12][1] 	= this->coords[12][1] - 45.0;
 // this->coords[13][1] 	= this->coords[13][1] - 45.0;
 // this->coords[14][1] 	= this->coords[14][1] - 45.0;
 // this->coords[15][1] 	= this->coords[15][1] - 45.0;
 // // roll (gamma)
 // this->coords[0][4] 	= this->coords[0][4] - 45.0;
 // this->coords[1][4] 	= this->coords[1][4] - 45.0;
 // this->coords[2][4] 	= this->coords[2][4] - 45.0;
 // this->coords[3][4] 	= this->coords[3][4] - 45.0;
 // this->coords[12][4] 	= this->coords[12][4] - 45.0;
 // this->coords[13][4] 	= this->coords[13][4] - 45.0;
 // this->coords[14][4] 	= this->coords[14][4] - 45.0;
 // this->coords[15][4] 	= this->coords[15][4] - 45.0;
  
  /////////////////////////////////////////////////////////////////////
  // GRIFFIN/TIGRESS Detector Properties 
  /////////////////////////////////////////////////////////////////////
  this->cut_clearance = 0.01*mm;
  this->extra_cut_length = 10.0*mm;

  // Killing Suppressors!
  this->include_extension_suppressors = true;
  this->include_side_suppressors      = true;
  this->include_back_suppressors      = true;		//BM: right place to turn on suppressors?

//////
  G4int can_pos                                = 1;
  G4int can_position_specifier                 = can_pos;  	// 1=fully forward, 2=flush with BGO, 3=fully back
  G4int detector_format                        = 2; 		// 1=simple, 2=complex, 3=none
  G4String include_detector_can                = "y"; 		// "y" or "n"
  G4String include_BGO                         = "y";
  G4String include_cold_finger                 = "y"; 
///// Included in new system

	if( suppSwitch )
		{ // Include Suppressors
			this->include_extension_suppressors = true;
			this->include_side_suppressors      = true;
			this->include_back_suppressors      = true;		
		}
	else 
		{ // Dont include Suppressors
			this->include_extension_suppressors = false;
			this->include_side_suppressors      = false;
			this->include_back_suppressors      = false;
			include_BGO													= "n" ; 
		}

  // GRIFFIN Dead Layers
  // Generated Oct 10th, 2013
  this->griffinDeadLayers[0][0] = 1.38*mm;
  this->griffinDeadLayers[0][1] = 1.30*mm;
  this->griffinDeadLayers[0][2] = 1.61*mm;
  this->griffinDeadLayers[0][3] = 1.84*mm;
  this->griffinDeadLayers[1][0] = 0.324*mm;
  this->griffinDeadLayers[1][1] = 0.506*mm;
  this->griffinDeadLayers[1][2] = 0.43*mm;
  this->griffinDeadLayers[1][3] = 0.40*mm;
  this->griffinDeadLayers[2][0] = 0.203*mm;
  this->griffinDeadLayers[2][1] = 0.457*mm;
  this->griffinDeadLayers[2][2] = 0.228*mm;
  this->griffinDeadLayers[2][3] = 0.614*mm;
  this->griffinDeadLayers[3][0] = 1.33*mm;
  this->griffinDeadLayers[3][1] = 1.17*mm;
  this->griffinDeadLayers[3][2] = 1.83*mm;
  this->griffinDeadLayers[3][3] = 1.38*mm;
  this->griffinDeadLayers[4][0] = 0.485*mm;
  this->griffinDeadLayers[4][1] = 0.488*mm;
  this->griffinDeadLayers[4][2] = 0.495*mm;
  this->griffinDeadLayers[4][3] = 0.508*mm;
  this->griffinDeadLayers[5][0] = 1.75*mm;
  this->griffinDeadLayers[5][1] = 1.48*mm;
  this->griffinDeadLayers[5][2] = 1.66*mm;
  this->griffinDeadLayers[5][3] = 1.47*mm;
  this->griffinDeadLayers[6][0] = 1.25*mm;
  this->griffinDeadLayers[6][1] = 1.31*mm;
  this->griffinDeadLayers[6][2] = 1.21*mm;
  this->griffinDeadLayers[6][3] = 1.35*mm;
  this->griffinDeadLayers[7][0] = 1.19*mm;
  this->griffinDeadLayers[7][1] = 2.07*mm;
  this->griffinDeadLayers[7][2] = 1.22*mm;
  this->griffinDeadLayers[7][3] = 1.39*mm;
  this->griffinDeadLayers[8][0] = 1.07*mm;
  this->griffinDeadLayers[8][1] = 1.07*mm;
  this->griffinDeadLayers[8][2] = 1.07*mm;
  this->griffinDeadLayers[8][3] = 1.07*mm;
  this->griffinDeadLayers[9][0] = 1.07*mm;
  this->griffinDeadLayers[9][1] = 1.07*mm;
  this->griffinDeadLayers[9][2] = 1.07*mm;
  this->griffinDeadLayers[9][3] = 1.07*mm;
  this->griffinDeadLayers[10][0] = 1.07*mm;
  this->griffinDeadLayers[10][1] = 1.07*mm;
  this->griffinDeadLayers[10][2] = 1.07*mm;
  this->griffinDeadLayers[10][3] = 1.07*mm;
  this->griffinDeadLayers[11][0] = 1.07*mm;
  this->griffinDeadLayers[11][1] = 1.07*mm;
  this->griffinDeadLayers[11][2] = 1.07*mm;
  this->griffinDeadLayers[11][3] = 1.07*mm;
  this->griffinDeadLayers[12][0] = 1.07*mm;
  this->griffinDeadLayers[12][1] = 1.07*mm;
  this->griffinDeadLayers[12][2] = 1.07*mm;
  this->griffinDeadLayers[12][3] = 1.07*mm;
  this->griffinDeadLayers[13][0] = 1.07*mm;
  this->griffinDeadLayers[13][1] = 1.07*mm;
  this->griffinDeadLayers[13][2] = 1.07*mm;
  this->griffinDeadLayers[13][3] = 1.07*mm;
  this->griffinDeadLayers[14][0] = 1.07*mm;
  this->griffinDeadLayers[14][1] = 1.07*mm;
  this->griffinDeadLayers[14][2] = 1.07*mm;
  this->griffinDeadLayers[14][3] = 1.07*mm;
  this->griffinDeadLayers[15][0] = 1.07*mm;
  this->griffinDeadLayers[15][1] = 1.07*mm;
  this->griffinDeadLayers[15][2] = 1.07*mm;
  this->griffinDeadLayers[15][3] = 1.07*mm;

  this->griffinCrystalColours[0] = G4Colour(0.0,0.0,1.0);
  this->griffinCrystalColours[1] = G4Colour(0.0,1.0,0.0);
  this->griffinCrystalColours[2] = G4Colour(1.0,0.0,0.0);
  this->griffinCrystalColours[3] = G4Colour(1.0,1.0,1.0);

  this->griffinDeadLayerColours[0] = G4Colour(0.0,0.0,0.50);
  this->griffinDeadLayerColours[1] = G4Colour(0.0,0.50,0.0);
  this->griffinDeadLayerColours[2] = G4Colour(0.50,0.0,0.0);
  this->griffinDeadLayerColours[3] = G4Colour(0.3,0.3,0.3);

  this->BGO_material                  = "G4_BGO";
  this->back_suppressor_material 	    = "G4_CESIUM_IODIDE";

  if( sel == 0 ) {
    sdName0 =               "/sd/allGriffinForward0";
    sdName1 =               "/sd/allGriffinForward1";
    sdName2 =               "/sd/allGriffinForward2";
    sdName3 =               "/sd/allGriffinForward3";
    sdName4 =               "/sd/allGriffinForward4";
    sdName5 =               "/sd/allGriffinForward5";

    colNameGe =             "CollectionGriffinForwardGe";
    colNameLeftCasing =     "CollectionGriffinForwardLeftCasing";
    colNameRightCasing =    "CollectionGriffinForwardRightCasing";
    colNameLeftExtension =  "CollectionGriffinForwardLeftExtension";
    colNameRightExtension = "CollectionGriffinForwardRightExtension";
    colNameBackPlug =       "CollectionGriffinForwardBackPlug";
  }
  else if( sel == 1 ) {
    sdName0 =               "/sd/allGriffinBack0";
    sdName1 =               "/sd/allGriffinBack1";
    sdName2 =               "/sd/allGriffinBack2";
    sdName3 =               "/sd/allGriffinBack3";
    sdName4 =               "/sd/allGriffinBack4";
    sdName5 =               "/sd/allGriffinBack5";

    colNameGe =             "CollectionGriffinBackGe";
    colNameLeftCasing =     "CollectionGriffinBackLeftCasing";
    colNameRightCasing =    "CollectionGriffinBackRightCasing";
    colNameLeftExtension =  "CollectionGriffinBackLeftExtension";
    colNameRightExtension = "CollectionGriffinBackRightExtension";
    colNameBackPlug =       "CollectionGriffinBackBackPlug";
  }
  else {
    G4cout << "Error: 123109812 " << G4endl;
    exit(1);
  }

  // These keep track of the number of sensitive detectors. Initialized to zero
  this->germanium_copy_number                  = 4000;
  this->left_suppressor_side_copy_number       = 4100;
  this->right_suppressor_side_copy_number      = 4200;
  this->left_suppressor_extension_copy_number  = 4300;
  this->right_suppressor_extension_copy_number = 4400;
  this->back_suppressor_copy_number            = 4500;

  this->suppressor_position_selector           = sel;  	// 0 = detector forward, 1 = detector back

  this->hevimet_selector                       = hevimetSel ;
  
  this->inner_dead_layer_thickness 	           = 1.0*mm;
  this->depth_segmentation_adjustment 	       = 0.0*cm;


	/* 
	In order to isolate the radial dependence of the detector from that of the extension suppressors, 
	two new variables were introduced. These are suppressor_forward_radius, and suppressor_back_radius. 
	These were used to replace any instance of forward_inner_radius and back_inner_radius (respectively) 
	that was found inside the code for the construction and placement of the extension suppressors. 
	forward_inner_radius and back_inner_radius are still used for the construction and placement
	of the detector assembly as well as the side and back suppressors. 	
	
	If a variable was found to be used in both the construction of the extension suppressors as well as
	the construction of the other assemblies, then a new variable was created with '_det' appended to the
	end (eg. air_box_front_width, air_box_front_width_det). 
	
	_det variables are dependent on forward_inner_radius and back_inner_radius. The others are dependent on 
	suppressor_forward_radius and suppressor_back_radius. 
	
	If the variable was only found to be used in the construction of the extension suppressors, but still carried
	a dependence on forward(back)_inner_radius, then the variable name was left unchanged and the dependence was changed
	to the appropriate static value. 
	*/
	
	// Used for detector and side/back suppressor placement
  this->forward_inner_radius 		         		= detRad ; 
  this->back_inner_radius 		          		= this->forward_inner_radius + 3.5*cm;
  
  
 	// Used for extension suppressor placement
  this->suppressor_forward_radius           = 11.0*cm ; 
  this->suppressor_back_radius              = this->suppressor_forward_radius + 3.5*cm ; 
  
  // "Outer" dead layer description: thickness determined from R.G.Helmer paper
  this->outer_dead_layer_thickness	           = 2.5*micrometer;
  
  //2.00 new: the thickness of the structureMat shell around the suppression material
  this->suppressor_shell_thickness 	           = 0.5*mm;
  
  //Jun 21, 2005: Epapr7.80: the suppressor extensions were accidentally made too large,
  //so they do not come as far forward as they should.  Shift for back, with hevimet was 1.0*cm
  //Jun 28, 2005: Just! for the back, no hevimet case, change this to 0.5*cm
  this->extension_accidental_back_shift        = 0.5*cm;
  //Set (in this) whether the structureMat shells around the suppressors will be included

  this->germanium_outer_radius 		           = 3.0*cm;	// Radius of the circular part of the germanium
  this->germanium_hole_radius 		           = 0.5*cm;
  this->germanium_length 		                 = 9.0*cm;
  this->germanium_hole_dist_from_face 	     = 1.5*cm;
  this->germanium_dist_from_can_face 	       = 0.55*cm;
  this->germanium_separation 		             = 0.6*mm;  	// Separation between quarter detectors: changed Jan 2005 from 0.7mm
  
  // This has been disabled Apr 11, 2005 for version 7.69: setting this
  this->inter_crystal_electrodeMat_thickness  = 0.6*mm;
  this->germanium_width 		                  = 56.5*mm;  	// Width of one quarter detector
  this->germanium_bent_length 		            = 3.62*cm;
  this->germanium_shift                       = 1.05*mm;  	// this can't be more than 2.75mm. It is the amount by which
                                                            // one side is cut closer to the center than the other
  this->germanium_corner_cone_end_length      = 3.0*cm; 	// the ending length of the cones

  this->electrodeMat_starting_depth            = this->germanium_corner_cone_end_length-1*micrometer;
  this->detector_block_length                  = 2.0*this->germanium_width; 	// Obsolete
  this->detector_block_height                  = this->germanium_length -this->germanium_bent_length;
  this->detector_total_width                   = 12.4*cm;             // Width of the detector can
  this->detector_total_length                  = 16.0*cm;             // Length of the detector can
  this->bent_end_angle                         = 22.5*M_PI/180;
  this->bent_end_length                        = 4.325*cm;
  this->can_face_thickness                     = 0.15*cm;
  this->can_side_thickness                     = 0.2*cm;
  this->detector_block_trapezoidal_height      = this->germanium_bent_length;
  
  this->cold_finger_outer_shell_radius         = 2.5*cm;
  this->cold_finger_shell_thickness            = 0.2*cm;
  this->cold_finger_shell_length               = 14.5*cm;

  // Values for the cold finger, and cooling structure (added Jan 2005)
  this->rear_plate_thickness                   = 0.2*cm;
  this->cold_finger_end_plate_thickness        = 10.0*mm; 	// Changed Jan 2005 from 9.0mm
  this->cold_finger_radius                     = 9.0*mm; 	// Changed Jan 2005 from 8.25mm
  this->cold_finger_space                      = 1.0*cm;  	// Space between the cold plate and the germanium crystals
  this->cold_finger_length                     = this->cold_finger_shell_length +this->detector_total_length
                                               - this->can_face_thickness -this->germanium_dist_from_can_face
                                               - this->germanium_length -this->cold_finger_space
                                               - this->cold_finger_end_plate_thickness;
  // New stuff
  this->extra_block_thickness                  = 9.0*mm;
  this->extra_block_distance_from_back_plate   = 10.0*mm;
  this->extra_block_inner_diameter             = 34.0*mm;
  
  this->triangle_posts_distance_from_crystals  = 2.0*mm;
  this->triangle_post_starting_depth           = 38.0*mm;
  this->fet_air_hole_radius                    = 26.0*mm/2.0;
  this->cooling_side_block_thickness           = 15.0*mm;
  this->cooling_side_block_width               = 20.0*mm;
  this->cooling_side_block_horizontal_depth    = 10.0*mm;
  this->structureMat_cold_finger_thickness     = 26.0*mm;
  this->structureMat_cold_finger_radius        = 22.0*mm/2.0;
  this->cooling_bar_thickness                  = 10.0*mm;
  this->cooling_bar_width                      = 8.0*mm ;
  
  // Liquid nitrogen tank stuff  
  this->coolant_length                         = 39.3*cm;   // Length of the Liquid Nitrogen tank
  this->coolant_radius                         = 12.5*cm;

  this->hevimet_tip_thickness                  = 1.27*cm;
//  this->hevimet_tip_angle                      = this->bent_end_angle -atan((this->germanium_width +0.5*this->germanium_separation
//                                               - this->germanium_bent_length*tan(this->bent_end_angle))/(this->back_inner_radius
//                                               + this->can_face_thickness +this->germanium_dist_from_can_face));

  this->hevimet_tip_angle                      = this->bent_end_angle -atan((this->germanium_width +0.5*this->germanium_separation
                                               - this->germanium_bent_length*tan(this->bent_end_angle))/( this->suppressor_back_radius
                                               + this->can_face_thickness +this->germanium_dist_from_can_face));

  // the difference between the 22.5 angle and the angle that the heavymet makes to the germanium
  this->back_BGO_thickness                     = 3.7*cm;    // 6.0*cm;
  this->BGO_chopped_tip                        = 5.0*mm;
  this->BGO_movable_space                      = 3.0*cm;  	// amount the can face can move back into the BGO
  this->side_suppressor_back_offset            = 1.0*cm;
  this->side_BGO_thickness                     = 2.0*cm;
  this->BGO_can_seperation                     = 0.5*mm;  	// Distance seperating the BGO and the detector can

  this->side_BGO_length                        = this->BGO_movable_space +this->detector_total_length
                                               + this->back_BGO_thickness +this->BGO_can_seperation;

  this->side_suppressor_length                 = this->detector_total_length -this->bent_end_length
                                               + this->BGO_can_seperation +this->back_BGO_thickness
                                               - this->side_suppressor_back_offset -(this->BGO_can_seperation
                                               + this->BGO_chopped_tip)/tan(this->bent_end_angle);

  this->BGO_trap_length                        = (this->side_BGO_thickness/tan(this->bent_end_angle))
                                               - (this->BGO_chopped_tip/tan(this->bent_end_angle));

  this->suppressor_extension_thickness         = 1.0*cm;


  this->suppressor_extension_length            = (this->suppressor_back_radius + this->bent_end_length
		                                             + (this->BGO_can_seperation + this->side_BGO_thickness)
		                                             / tan(this->bent_end_angle) - this->suppressor_extension_thickness
		                                             * sin(this->bent_end_angle)) / cos(this->bent_end_angle)
		                                             - this->hevimet_tip_thickness - this->suppressor_forward_radius; 

  this->suppressor_extension_length_det        = 	(this->back_inner_radius + this->bent_end_length
		                                              + (this->BGO_can_seperation + this->side_BGO_thickness)
		                                              / tan(this->bent_end_angle) - this->suppressor_extension_thickness
		                                              * sin(this->bent_end_angle)) / cos(this->bent_end_angle)
		                                              - this->hevimet_tip_thickness - this->forward_inner_radius; 


 this->suppressor_extension_angle 	           = atan(((this->suppressor_back_radius + this->bent_end_length + (this->BGO_can_seperation
		                                             + this->side_BGO_thickness) / tan(this->bent_end_angle)
		                                             - this->suppressor_extension_thickness *sin(this->bent_end_angle))
		                                             * tan(this->bent_end_angle) - (this->suppressor_forward_radius + this->hevimet_tip_thickness)
		                                             * sin(this->bent_end_angle)) / (this->suppressor_extension_length)); 

  this->HeavyMet_thickness                     = 3.0*cm;   	// This can't be more than bent_end_length +
                                                            // (chopped_tip+seperation)/tan(bent_angle)

  this->HeavyMet_inside_angle                  = atan((this->detector_total_width/2.0)/
		                                             ((this->detector_total_width/2.0 +this->BGO_chopped_tip
		                                             + this->BGO_can_seperation)/tan(this->bent_end_angle)
		                                             + this->BGO_movable_space +this->bent_end_length));

  // used only in new suppressor design, but don't affect old suppressor design

 
  this->air_box_front_width 		           		= 2.0*(this->detector_total_width/2.0 +this->BGO_can_seperation
                                               + (this->side_BGO_thickness + this->suppressor_shell_thickness*2.0)
                                               + ( this->suppressor_extension_length
                                               +  (this->suppressor_shell_thickness*2.0
                                               * (1.0/tan(this->bent_end_angle)-tan(this->bent_end_angle))) )
                                               * sin(this->bent_end_angle) +(this->suppressor_extension_thickness
                                               + this->suppressor_shell_thickness*2.0)/cos(this->bent_end_angle)) ;
                                               // the longer width of the box's trapezoid
	   
	this->air_box_front_width_det                = 2.0*(this->detector_total_width/2.0 +this->BGO_can_seperation
                                               + (this->side_BGO_thickness + this->suppressor_shell_thickness*2.0)
                                               + ( this->suppressor_extension_length_det
                                               +  (this->suppressor_shell_thickness*2.0
                                               * (1.0/tan(this->bent_end_angle)-tan(this->bent_end_angle))) )
                                               * sin(this->bent_end_angle) +(this->suppressor_extension_thickness
                                               + this->suppressor_shell_thickness*2.0)/cos(this->bent_end_angle)) ;
	   
  this->air_box_front_length                   = (this->air_box_front_width/2.0 - this->suppressor_forward_radius
	                                             * sin(this->bent_end_angle)) / tan(this->bent_end_angle); 

  this->air_box_front_length_det               =  (this->air_box_front_width_det/2.0 - this->forward_inner_radius
                                                  * sin(this->bent_end_angle)) / tan(this->bent_end_angle) ;
 
	this->air_box_back_length                    = this->detector_total_length + this->cold_finger_shell_length
                                               + this->coolant_length + ( this->suppressor_back_radius
                                               - this->suppressor_forward_radius * cos(this->bent_end_angle))
                                               - this->air_box_front_length; 

  this->air_box_back_length_det                = this->detector_total_length + this->cold_finger_shell_length
                                                + this->coolant_length + (this->back_inner_radius
                                                - this->forward_inner_radius * cos(this->bent_end_angle))
                                                - this->air_box_front_length_det;

  // shift" is applied to everything to place them relative to the front of the air_box
  // the negative is because the shift is along the -ive X-xis
 
  this->suppShift =                            - (this->air_box_back_length/2.0 + this->air_box_front_length
                                               - (this->suppressor_forward_radius * (1 - cos(this->bent_end_angle)))
                                               - this->can_face_thickness/2.0);

 
  this->shift =                                - (this->air_box_back_length_det/2.0 +this->air_box_front_length_det
                                               - (this->forward_inner_radius -this->forward_inner_radius*cos(this->bent_end_angle))
                                               - this->can_face_thickness/2.0); // Original

      
  this->depth_segmentation_adjustment          = depth_segmentation_adjustment;
  
  // Gives the proper diameter of the Tigress array based on can face length
  this->rhombi_diameter                        = this->detector_total_width
                                               - 2.0*this->bent_end_length
                                               * tan(this->bent_end_angle)
                                               + 2.0*(this->detector_total_width
                                               - 2.0*this->bent_end_length
                                               * tan(this->bent_end_angle))
                                               * cos(M_PI/4.0);

  // This ones used by the new suppressor design
  
  this->new_rhombi_radius_det                   = this->forward_inner_radius*cos(this->bent_end_angle); // Original
  
  this->new_rhombi_radius                      	= this->suppressor_forward_radius*cos(this->bent_end_angle);


  if (can_position_specifier == 1) {
    this->detector_position_shift              =  this->bent_end_length +(this->BGO_chopped_tip
                                               + this->BGO_can_seperation)/tan(this->bent_end_angle);
  }
  else if (can_position_specifier == 2) {
    this->detector_position_shift              = 0.0*cm;
  }
  else if (can_position_specifier == 3) {
    this->detector_position_shift              = -(this->BGO_movable_space);
  }
  else {
    this->detector_position_shift              = 0.0*cm;
  }
 
  // this is used to actually apply the necessary detector shift to all the pieces involved
  if(this->suppressor_position_selector == 0) {
    this->applied_back_shift                   = 0.0*cm;
  }
  else if( this->suppressor_position_selector && suppSwitch ) {
    this->applied_back_shift                   = this->back_inner_radius - this->forward_inner_radius; // 3.5cm
  }

  if(detector_format == 1) {
    this->germanium_selector                   = 0;
  }
  else if (detector_format == 2) {
    this->germanium_selector                   = 1;
  }
  else if(detector_format == 3) {
    this->germanium_selector                   = 2;
  }
  else {
    this->germanium_selector                   = 2;
  }
 
  if (include_detector_can == "y") {
    this->can_selector                         = 1;
  } 
  else if(include_detector_can == "n") {
    this->can_selector                         = 0;
  }
  else {
    this->can_selector                         = 0;
  }   
 
  if(include_BGO == "y") {
    this->BGO_selector                         = 1;
  }
  else if(include_BGO == "n") {
    this->BGO_selector                         = 0;
  }
  else {
    this->BGO_selector                         = 0;
  }
 
  if(include_cold_finger == "y") {
    this->cold_finger_selector                 = 1;
  }
  else if(include_cold_finger == "n") {
    this->cold_finger_selector                 = 0;
  }
  else {
    this->cold_finger_selector                 = 0;
  }
  
  if (this->suppressor_position_selector == 0) {
     crystal_dist_from_origin                  = this->forward_inner_radius
                                               + this->germanium_dist_from_can_face
                                               + this->can_face_thickness;
  }
  else if (this->suppressor_position_selector == 1) {
    crystal_dist_from_origin                   = this->back_inner_radius
                                               + this->germanium_dist_from_can_face
                                               + this->can_face_thickness;
  }  

  this->radial_distance                        = this->forward_inner_radius*cos(this->bent_end_angle)
                                               + this->air_box_back_length/2.0 +this->air_box_front_length;

  //Redacted parameters/////////////////////////////////////////////////////////////
  this->detectorPlacementCxn = 0.4*mm;
  this->trianglePostDim = 1.0*micrometer;

  this->suppressorExtRightX = -2.55*mm;
  this->suppressorExtRightY = 0.24*mm;
  this->suppressorExtRightZ = -0.095*mm;

  this->suppressorExtLeftX = -2.55*mm;
  this->suppressorExtLeftY = 0.24*mm;
  this->suppressorExtLeftZ = 0.1*mm;

  this->wedgeDim = 0.001*mm;

  this->quarterDetectorCxn = 0.01*mm;
  this->quarterDetectorCxnB = 0.1*mm;

  this->electrodeMaterial = "G4_Cu";
  this->structureMaterial = "G4_Al";

}// end ::DetectionSystemGriffin



