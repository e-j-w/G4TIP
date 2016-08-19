# TIP Fusion-Evaporation DSAM GEANT4 Code

Maintainer: Jonathan Williams

## Description

GEANT4 code implementing TIP/TIGRESS DSAM using a fusion-evaporation reaction process.

## Installation

This code has been tested with GEANT4.9.4 on Scientific Linux 6, Ubuntu 14.04, and Ubuntu 15.10.

Depends on GEANT4, CLHEP, and ROOT v5.x (results are saved to ROOT tree files).  Requires proper setup of environment variables for each, for example by adding the follwing lines to ~/.bashrc (substituting the appropriate paths):

```#ROOT configuration
export ROOTSYS=/path/to/root
export ROOTINC=/path/to/root/include
export ROOTLIB=/path/to/root/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ROOTSYS/lib/
export PATH=$PATH:$ROOTSYS/bin
```

```#CLHEP configuration
export CLHEPSYS=/path/to/clhep
export PATH=$PATH:$CLHEPSYS/bin:$CLHEPSYS/lib
```

```#for GEANT4
#the next line should point to the env.sh file generated upon installation/configuration of GEANT4
source /path/to/env.sh
export G4INSTALL=/path/to/geant4_install_directory
```


Modified GEANT4 classes included in this code:
G4IonParametrisedLossModel (GEANT4.9.4) - modified to allow for user defined stopping powers
G4IonStoppingData (GEANT4.9.4) - modified to allow for user defined stopping powers
G4NuclearDecayChannel (GEANT4.9.4) - minimally modified to allow gamma cascades

## Acknowledgements

A. Chester - CsI array code.

C. Morse - Finding and fixing memory leaks.

K. Starosta - Initial TIP codebase.

GRIFFIN/TIGRESS code based on code provided by the GRIFFIN collaboration, available at: https://github.com/GRIFFINCollaboration/detectorSimulations
