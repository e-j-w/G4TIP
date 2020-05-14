# TIP Fusion-Evaporation Code

Maintainer: Jonathan Williams

## Description

GEANT4 code implementing TIP/TIGRESS DSAM/RDM using a fusion-evaporation reaction process.

At present, the TIP CsI wall/ball and GRIFFIN/TIGRESS array geometries are implemented.  Step-wise decay of the residual nucleus (gamma ray cascade) is also availaible.

## Installation

This code has been tested on Ubuntu 14.04/16.04, CentOS 7, and Arch Linux (as of May 2020).  Follow the instructions below to set up the required dependencies.

### ROOT

ROOT trees are used to store simulated data.  The code is tested with v6.x, but earlier versions may work.  You may already have this set up (in that case just make sure that the environment variables are correctly defined). If not, ROOT should be built from source:

[ROOT source code](https://root.cern.ch/downloading-root)

[ROOT build and install guide](https://root.cern.ch/building-root)

Set up environment variables for ROOT by adding the following lines to your `~/.bashrc` (substituting the appropriate paths):

```
#ROOT configuration
export ROOTSYS=/path/to/root
export ROOTINC=/path/to/root/include
export ROOTLIB=/path/to/root/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ROOTLIB
export PATH=$PATH:$ROOTSYS/bin
```

### GEANT4

The code is tested with GEANT4 v10.6.  It may still work with older versions.

[GEANT4 source code](https://geant4.web.cern.ch/support/download)

[GEANT4 build and install guide](https://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/InstallationGuide/html/installguide.html)

GEANT4 should be built with its data files, using the `-DGEANT4_INSTALL_DATA=ON` switch specified in its install guide.  Set up environment variables for GEANT4 by adding the following lines to your `~/.bashrc` (substituting the appropriate paths):

```
#for GEANT4
export G4INSTALL=/path/to/geant4_install_directory
source $G4INSTALL/bin/geant4.sh
#substitute GEANT4_VERSION in the next line with the appropriate directory
source $G4INSTALL/share/GEANT4_VERSION/geant4make/geant4make.sh
```

### Redacted files

This program requires secret files describing the GRIFFIN geometry (`DetectionSystemGriffinSuppressed.cc` and `DetectorConstructionSuppressed.cc`).  To get them, ask a collaborator or your boss.  After obtaining these files, copy them to the `src` directory.

### Build the simulation code

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
| /Construction/UseDSAMTarget | Use the DSAM reaction target.  This is the default option. |
| /Construction/UsePlunger | Use the TIP plunger as the reaction target. |
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
| /Reaction/MaxNumAttempts NUMBER | When simulating, the program will discard any reactions which are non-physical (eg. residual nucleus not excited high enough to emit the gamma rays requested) and re-attempt the reaction.  This sets the maximum number of times to re-attempt the reaction before giving an error.  Default value is 1000. |
| /CompoundFormation/Q NUMBER | The reaction Q value, in MeV, of the fusion reaction forming the compound system from the beam and target species, based on the difference in mass between the beam + target and the compound nucleus. |
| /ParticleEvaporation/Q1 NUMBER | The reaction Q value, in MeV, of the first particle evaporation from the compund nucleus, based on the difference in mass between the compound system and the particle + remaining nucleus. |
| /ParticleEvaporation/Q2 NUMBER | Same as above, except for the second particle evaporation (if applicable).  Use Q3 and Q4 for the third and fourth particle evaporations, if necessary. |
| /ParticleEvaporation/Centroid NUMBER | When using a Gaussian+exponential distribution for the evaporated particle excitation energies, this command is used to specify the centroid of the Gaussian distribution. |
| /ParticleEvaporation/Width NUMBER | When using a Gaussian+exponential distribution for the evaporated particle excitation energies, this command is used to specify the width of the Gaussian distribution. |
| /ParticleEvaporation/Tau NUMBER | When using a Gaussian+exponential distribution for the evaporated particle excitation energies, this command is used to specify the decay constant of the exponential distribution. |
| /ParticleEvaporation/DistFile FILENAME | Specifies a file containing the desired centre-of-mass energy distribution for evaporated particles.  The format of the file is two columns for the start-of-bin energy in MeV and the number of counts in the bin, respectively.  Using this command **overrides** the default Gaussian+exponential distribution (and the associated Centroid, Width, and Tau parameters listed above). |
| /Reaction/P0 | Sets the angular distribution of emitted gamma rays to be isotropic (default). |
| /Reaction/P2 | Sets the angular distribution of emitted gamma rays to a 2nd order legendre polynomial in cos(theta). |
| /Reaction/P4 | Sets the angular distribution of emitted gamma rays to a 4th order legendre polynomial in cos(theta). |

### Trigger Parameters

|**Command**|**Effect**|
|:---:|:---:|
| /Trigger/GammaSingles | Trigger on events containing at least one hit in the TIGRESS/GRIFFIN array. |
| /Trigger/A NUMBER | If using a particle trigger, this is the mass number of the particle to trigger on<sup>1</sup>. |
| /Trigger/Z NUMBER | If using a particle trigger, this is the proton number of the particle to trigger on<sup>1</sup>. |
| /Trigger/ARange MIN MAX | If using a particle trigger, this is the range of mass number of the particle(s) which may be triggered on<sup>1</sup>. |
| /Trigger/ZRange MIN MAX | If using a particle trigger, this is the range of proton numbers of the particle(s) which may be triggered on<sup>1</sup>. |
| /Trigger/DefinedParticleSingles | Trigger on events containing at least one hit with the particle defined by /Trigger/A and /Trigger/Z. |
| /Trigger/DefinedParticleCoincAndGamma | Trigger on events containing at least two hits with the particle defined by /Trigger/A and /Trigger/Z, and one gamma ray. |
| /Trigger/DefinedParticleCoincAnd2GammaCores | Trigger on events containing at least two hits with the particle defined by /Trigger/A and /Trigger/Z (or any particle if those commands are not used), and two hits in the TIGRESS/GRIFFIN array. |
| /Trigger/DisableGriffin NUM | Removes the TIGRESS/GRIFFIN detector with index NUM from the trigger. |
| /Trigger/DisableGriffinDetCol DET COL | Removes the TIGRESS/GRIFFIN detector core with detector index DET and core index COL from the trigger. |
| /Trigger/DisableCsI NUM | Removes the CsI detector with index NUM from the trigger. |
| /Trigger/DisableCsIRange LOW HIGH | Removes CsI detectors with index between LOW and HIGH (inclusive) from the trigger. |

<sup>1</sup>If none of /Trigger/A, /Trigger/Z, /Trigger/ARange, and /Trigger/ZRange are set, the particle trigger will be applied to any charged particle.

### Data Generation and Saving

|**Command**|**Effect**|
|:---:|:---:|
| /run/beamOn NUMBER | Runs the simulation for the specified number of events (primary beam tracks). |
| /Results/Tree/Save FILENAME | Saves the results of the simulation to a ROOT tree in the specified file. |


## Other Notes

Some GEANT4 classes have been backported from version 9.4 for use in this code:

G4IonStoppingData (from GEANT4.9.4) - modified to allow for user defined stopping powers.

G4NuclearDecayChannel (from GEANT4.9.4) - reimplemented as GammaDecayChannel, a decay channel with only gamma decay.  This is done to properly compute properties of daughter nuclei and emitted gammas when considering a cascade of internal conversion decays.

G4Decay (from GEANT4.10.3) - modified to suppress warnings.

## Acknowledgements

A. Chester - CsI wall code.

T. Ma - CsI ball code.

C. Morse - Finding and fixing memory leaks.

K. Starosta - Initial TIP codebase, RDM implementation.

F. Wu - Reaction code work and auditing.

GRIFFIN/TIGRESS code based on code provided by the GRIFFIN collaboration, available at: https://github.com/GRIFFINCollaboration/detectorSimulations
