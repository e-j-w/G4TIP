# TIP Fusion-Evaporation DSAM GEANT4 Code

Maintainer: Jonathan Williams

## Description

GEANT4 code implementing TIP/TIGRESS DSAM using a fusion-evaporation reaction process.

At present, the TIP CsI wall/ball and GRIFFIN/TIGRESS array geometries are implemented.  Step-wise decay of the residual nucleus (gamma ray cascade) is also availaible.

This code requires GEANT4 version 10.x (see the version 9.4 branch for the most recent code compatible with version 9).  If the ROOT interface is needed, the code in the version 9.4 branch should be used instead. 

## Installation

This code has been tested with GEANT4.10.3 on Ubuntu 16.04.

This program depends on GEANT4.10.3, ROOT v5.x (results are saved to ROOT tree files), and cmake.  These programs should be compiled from source and installed according to the install guides on their respective websites.  GEANT4 should be built with its data files, using the `-DGEANT4_INSTALL_DATA=ON` switch specified in its install guide.

Environment variables must be properly set up for all dependencies, for example by adding the following lines to ~/.bashrc (substituting the appropriate paths):

```
#ROOT configuration
export ROOTSYS=/path/to/root
export ROOTINC=/path/to/root/include
export ROOTLIB=/path/to/root/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ROOTLIB
export PATH=$PATH:$ROOTSYS/bin
```

```
#for GEANT4
export G4INSTALL=/path/to/geant4_install_directory
source $G4INSTALL/bin/geant4.sh
#substitute GEANT4_VERSION in the next line with the appropriate directory
source $G4INSTALL/share/GEANT4_VERSION/geant4make/geant4make.sh
```

The program is then compiled from source using the following commands (substituting the appropriate directories):

```
cmake -DGeant4_DIR=/path/to/geant4_install_directory/lib/GEANT4_VERSION
make
```

## Using the program

The program `TIP_Fusion_Evaporation` is run from the command line and takes a batch file as its only argument.  The batch file contains a list of commands which are executed in order by the program.  See the included sample batch files `1274level.mac` and `3357cascade.mac` for examples of commands that can be used in the simulation.  A table explaining some (but not all) of the available commands follows:

### Detectors and Geometry

|**Command**|**Effect**|
|:---:|:---:|
| /Construction/UseCsIBall | Use the CsI ball array for charged particle detection.  If this command is not set, the wall array will be used instead. |
| /Target/ThicknessMgCm2 NUMBER | The thickness of the reaction target, in mg/cm^2. |
| /Target/Thickness NUMBER um | The thickness of the reaction target, in micrometers (can be used instead of /Target/ThicknessMgCm2). |
| /Backing/Thickness NUMBER um | The thickness of the reaction target backing, in micrometers. |
| /Target/A NUMBER | The mass number of the reaction target (number of nucleons). |
| /Target/Z NUMBER | The proton number of the reaction target. |
| /Backing/A NUMBER | The mass number of the target backing (number of nucleons). |
| /Backing/Z NUMBER | The proton number of the target backing. |

### Physics Parameters

|**Command**|**Effect**|
|:---:|:---:|
| /Physics/IgnoreNeutrons | Ignore neutron interactions in the simulation.  Useful if there are no neutrons produced in the reaction and you want to speed up the simulation. |
| /Physics/StoppingTable PATH | Use custom stopping power tables from the directory specified by PATH.  The format of the tables is expected to be the same as those provided in the default GEANT4 dataset.  If not set, GEANT4 will use its default ICRU73-based stopping power tables. |

### Reaction Parameters

|**Command**|**Effect**|
|:---:|:---:|
| /Projectile/A NUMBER | The mass number of the beam species (number of nucleons). |
| /Projectile/Z NUMBER | The proton number of the beam species. |
| /Reaction/N_protons | In fusion-evaporation, the number of protons (promptly) emitted from the compound nucleus in order to form the residual nucleus. |
| /Reaction/N_neutrons | In fusion-evaporation, the number of neutrons (promptly) emitted from the compound nucleus in order to form the residual nucleus. |
| /Reaction/N_alpha | In fusion-evaporation, the number of alpha particles (promptly) emitted from the compound nucleus in order to form the residual nucleus. |
| /Reaction/AddDecay ENERGY LIFETIME | Adds a decay (emits a gamma-ray from the residual nucleus) with energy specified in MeV, and lifetime specified in ns.  More than 1 decay may be added, in which case the decays occur sequentially (in a cascade). |

### Trigger Parameters

|**Command**|**Effect**|
|:---:|:---:|
| /Trigger/GammaSingles | Trigger on events containing at least one hit in the TIGRESS/GRIFFIN array. |
| /Trigger/A NUMBER | If using a particle trigger, this is the mass number of the particle to trigger on. |
| /Trigger/Z NUMBER | If using a particle trigger, this is the proton number of the particle to trigger on. |
| /Trigger/DefinedParticleSingles | Trigger on events containing at least one hit with the particle defined by /Trigger/A and /Trigger/Z. |
| /Trigger/DefinedParticleCoincAndGamma | Trigger on events containing at least two hits with the particle defined by /Trigger/A and /Trigger/Z, and one gamma ray. |
| /Trigger/DefinedParticleCoincAnd2GammaCores | Trigger on events containing at least two hits with the particle defined by /Trigger/A and /Trigger/Z, and two hits in the TIGRESS/GRIFFIN array. |
| /Trigger/DisableGriffin NUM | Removes the TIGRESS/GRIFFIN detector with index NUM from the trigger. |
| /Trigger/DisableGriffinDetCol DET COL | Removes the TIGRESS/GRIFFIN detector core with detector index DET and core index COL from the trigger. |
| /Trigger/DisableCsI NUM | Removes the CsI detector with index NUM from the trigger. |
| /Trigger/DisableCsIRange LOW HIGH | Removes CsI detectors with index between LOW and HIGH (inclusive) from the trigger. |

### Data Generation and Saving

|**Command**|**Effect**|
|:---:|:---:|
| /run/beamOn NUMBER | Runs the simulation for the specified number of events (primary beam tracks). |
| /Results/Tree/Save FILENAME | Saves the results of the simulation to a ROOT tree in the specified file. |


## Other Notes

Some GEANT4 classes have been backported from version 9.4 for use in this code:

G4IonParametrisedLossModel (from GEANT4.9.4) - modified to allow for user defined stopping powers.

G4IonStoppingData (from GEANT4.9.4) - modified to allow for user defined stopping powers.

G4NuclearDecayChannel (from GEANT4.9.4) - reimplemented as GammaDecayChannel, a decay channel with only internal conversion.  This is done to properly compute properties of daughter nuclei and emitted gammas when considering a cascade of internal conversion decays.

G4Decay (from GEANT4.10.3) - modified to suppress warnings.

## Acknowledgements

A. Chester - CsI wall code.

T. Ma - CsI ball code.

C. Morse - Finding and fixing memory leaks.

K. Starosta - Initial TIP codebase.

GRIFFIN/TIGRESS code based on code provided by the GRIFFIN collaboration, available at: https://github.com/GRIFFINCollaboration/detectorSimulations
