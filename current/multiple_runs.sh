#!/bin/bash

#This script runs the specified GEANT4 macro repeatedly, saving data in root files labelled run1, run2, run3, etc.

#argument 1: GEANT4 macro file to run (saved ROOT file should have 'run1' in its name for this script to work) 
#argument 2: number of runs to do

RUN=0
for ((RUN = 1; RUN <= $2; RUN++)); do

    if [ $RUN>1 ]
      then
        RUNNAME=run
        RUNMINUS=$(($RUN-1))
	      sed -i 's/'"$RUNNAME$RUNMINUS"'/'"$RUNNAME$RUN"'/g' $1
      fi

    TIP_FusEvapDSAM_CsIWall $1
    
done

#change the macro file back to its original state
sed -i 's/'run"$2"'/'run1'/g' $1
#for some reason this file gets generated... remove it
rm 1
