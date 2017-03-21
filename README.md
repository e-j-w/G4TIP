# TIP Fusion-Evaporation DSAM GEANT4 Code

Maintainer: Jonathan Williams

## Description

GEANT4 code implementing TIP/TIGRESS DSAM using a fusion-evaporation reaction process.

At present, the TIP CsI wall/ball and GRIFFIN/TIGRESS array geometries are implemented.  Step-wise decay of the residual nucleus (gamma ray cascade) is also availaible.

## Installation

This code has been tested with GEANT4.9.4 on Scientific Linux 6, Ubuntu 14.04, Ubuntu 15.10, and Ubuntu 16.04.  On Ubuntu 16.04 this program throws memory allocation errors when compiled using the default version of the `g++` compiler, it is recommended to install and use `g++-4.8` instead.

This program depends on GEANT4.9.4, CLHEP 2.1.0.1, and ROOT v5.x (results are saved to ROOT tree files), and requires proper setup of environment variables for each, for example by adding the follwing lines to ~/.bashrc (substituting the appropriate paths):

```
#ROOT configuration
export ROOTSYS=/path/to/root
export ROOTINC=/path/to/root/include
export ROOTLIB=/path/to/root/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ROOTLIB
export PATH=$PATH:$ROOTSYS/bin
```

```
#CLHEP configuration
export CLHEPSYS=/path/to/clhep
export PATH=$PATH:$CLHEPSYS/bin:$CLHEPSYS/lib
```

```
#for GEANT4
#the next line should point to the env.sh file generated upon installation/configuration of GEANT4
source /path/to/env.sh
export G4INSTALL=/path/to/geant4_install_directory
```

Modified GEANT4 classes included in this code:

G4IonParametrisedLossModel (from GEANT4.9.4) - modified to allow for user defined stopping powers.

G4IonStoppingData (from GEANT4.9.4) - modified to allow for user defined stopping powers.

G4NuclearDecayChannel (from GEANT4.9.4) - reimplemented as GammaDecayChannel, a decay channel with only internal conversion.  This is done to properly compute properties of daughter nuclei and emitted gammas when considering a cascade of internal conversion decays.

## Using the program

The program `TIP_Fusion_Evaporation` is run from the command line and takes a batch file as its only argument.  The batch file contains a list of commands which are executed in order by the program.  See the included sample batch file `1274level.mac` for an example of commands that can be used in the simulation.  A table explaining some (but not all) of the available commands follows:

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

## Acknowledgements

A. Chester - CsI wall code.

T. Ma - CsI ball code.

C. Morse - Finding and fixing memory leaks.

K. Starosta - Initial TIP codebase.

GRIFFIN/TIGRESS code based on code provided by the GRIFFIN collaboration, available at: https://github.com/GRIFFINCollaboration/detectorSimulations
