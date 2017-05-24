# TIP Fusion-Evaporation DSAM GEANT4 Code

Maintainer: Jonathan Williams

## Description

GEANT4 code implementing TIP/TIGRESS DSAM using a fusion-evaporation reaction process.

At present, the TIP CsI wall/ball and GRIFFIN/TIGRESS array geometries are implemented.  Step-wise decay of the residual nucleus (gamma ray cascade) is also availaible.

This version uses GEANT4 version 10.x, and is a work in progress that is still being evaluated (see the version 9.4 branch for the most recent stable version).  If the ROOT interface is needed, the code in the version 9.4 branch should be used instead. 

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

|**Command**|**Effect**|
|:---:|:---:|
| /Construction/UseCsIBall | Use the CsI ball array for charged particle detection.  If this command is not set, the wall array will be used instead. |
| /Projectile/A NUMBER | The mass number of the beam species. |
| /Projectile/Z NUMBER | The proton number of the beam species. |
| /Reaction/N_protons | In fusion-evaporation, the number of protons (promptly) emitted from the compound nucleus in order to form the residual nucleus. |
| /Reaction/N_neutrons | In fusion-evaporation, the number of neutrons (promptly) emitted from the compound nucleus in order to form the residual nucleus. |
| /Reaction/N_alpha | In fusion-evaporation, the number of alpha particles (promptly) emitted from the compound nucleus in order to form the residual nucleus. |
| /Reaction/AddDecay ENERGY LIFETIME | Adds a decay (emits a gamma-ray from the residual nucleus) with energy specified in MeV, and lifetime specified in ns.  More than 1 decay may be added, in which case the decays occur sequentially (in a cascade). |
| /run/beamOn NUMBER | Runs the simulation for the specified number of events (primary beam tracks). |
| /Results/Tree/Save FILENAME | Saves the results of the simulation to a ROOT tree in the specified file. |

## Other

Some GEANT4 classes have been backported from version 9.4 for use in this code:

G4IonParametrisedLossModel (from GEANT4.9.4) - modified to allow for user defined stopping powers.

G4IonStoppingData (from GEANT4.9.4) - modified to allow for user defined stopping powers.

G4NuclearDecayChannel (from GEANT4.9.4) - reimplemented as GammaDecayChannel, a decay channel with only internal conversion.  This is done to properly compute properties of daughter nuclei and emitted gammas when considering a cascade of internal conversion decays.

## Acknowledgements

A. Chester - CsI wall code.

T. Ma - CsI ball code.

C. Morse - Finding and fixing memory leaks.

K. Starosta - Initial TIP codebase.

GRIFFIN/TIGRESS code based on code provided by the GRIFFIN collaboration, available at: https://github.com/GRIFFINCollaboration/detectorSimulations
