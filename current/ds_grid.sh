#!/bin/bash

#Script to run the lifetime vs. plunger offset grid with tree info allowing ds gating

./multiple_runs.sh 5910level.mac 100
mkdir treefiles/5910/ICRU/4635gamma_ds/51fs_minus5mmshift/
mv run*.root treefiles/5910/ICRU/4635gamma_ds/51fs_minus5mmshift/
cp 5910level.mac treefiles/5910/ICRU/4635gamma_ds/51fs_minus5mmshift/
sed -i 's/'5.1e-5'/'5.6e-5'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 100
mkdir treefiles/5910/ICRU/4635gamma_ds/56fs_minus5mmshift/
mv run*.root treefiles/5910/ICRU/4635gamma_ds/56fs_minus5mmshift/
cp 5910level.mac treefiles/5910/ICRU/4635gamma_ds/56fs_minus5mmshift/
sed -i 's/'"-5.0 mm"'/'"-7.5 mm"'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 100
mkdir treefiles/5910/ICRU/4635gamma_ds/56fs_minus7.5mmshift/
mv run*.root treefiles/5910/ICRU/4635gamma_ds/56fs_minus7.5mmshift/
cp 5910level.mac treefiles/5910/ICRU/4635gamma_ds/56fs_minus7.5mmshift/
sed -i 's/'"-7.5 mm"'/'"-10.0 mm"'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 100
mkdir treefiles/5910/ICRU/4635gamma_ds/56fs_minus10mmshift/
mv run*.root treefiles/5910/ICRU/4635gamma_ds/56fs_minus10mmshift/
cp 5910level.mac treefiles/5910/ICRU/4635gamma_ds/56fs_minus10mmshift/
sed -i 's/'5.6e-5'/'5.1e-5'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 100
mkdir treefiles/5910/ICRU/4635gamma_ds/51fs_minus10mmshift/
mv run*.root treefiles/5910/ICRU/4635gamma_ds/51fs_minus10mmshift/
cp 5910level.mac treefiles/5910/ICRU/4635gamma_ds/51fs_minus10mmshift/
sed -i 's/'"-10.0 mm"'/'"-7.5 mm"'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 100
mkdir treefiles/5910/ICRU/4635gamma_ds/51fs_minus7.5mmshift/
mv run*.root treefiles/5910/ICRU/4635gamma_ds/51fs_minus7.5mmshift/
cp 5910level.mac treefiles/5910/ICRU/4635gamma_ds/51fs_minus7.5mmshift/
sed -i 's/'"-7.5 mm"'/'"-2.5 mm"'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 100
mkdir treefiles/5910/ICRU/4635gamma_ds/51fs_minus2.5mmshift/
mv run*.root treefiles/5910/ICRU/4635gamma_ds/51fs_minus2.5mmshift/
cp 5910level.mac treefiles/5910/ICRU/4635gamma_ds/51fs_minus2.5mmshift/
sed -i 's/'5.1e-5'/'5.6e-5'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 100
mkdir treefiles/5910/ICRU/4635gamma_ds/56fs_minus2.5mmshift/
mv run*.root treefiles/5910/ICRU/4635gamma_ds/56fs_minus2.5mmshift/
cp 5910level.mac treefiles/5910/ICRU/4635gamma_ds/56fs_minus2.5mmshift/
sed -i 's/'5.6e-5'/'4.6e-5'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 100
mkdir treefiles/5910/ICRU/4635gamma_ds/46fs_minus2.5mmshift/
mv run*.root treefiles/5910/ICRU/4635gamma_ds/46fs_minus2.5mmshift/
cp 5910level.mac treefiles/5910/ICRU/4635gamma_ds/46fs_minus2.5mmshift/
sed -i 's/'"-2.5 mm"'/'"-5.0 mm"'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 100
mkdir treefiles/5910/ICRU/4635gamma_ds/46fs_minus5mmshift/
mv run*.root treefiles/5910/ICRU/4635gamma_ds/46fs_minus5mmshift/
cp 5910level.mac treefiles/5910/ICRU/4635gamma_ds/46fs_minus5mmshift/
sed -i 's/'"-5.0 mm"'/'"-7.5 mm"'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 100
mkdir treefiles/5910/ICRU/4635gamma_ds/46fs_minus7.5mmshift/
mv run*.root treefiles/5910/ICRU/4635gamma_ds/46fs_minus7.5mmshift/
cp 5910level.mac treefiles/5910/ICRU/4635gamma_ds/46fs_minus7.5mmshift/
sed -i 's/'"-7.5 mm"'/'"-10.0 mm"'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 100
mkdir treefiles/5910/ICRU/4635gamma_ds/46fs_minus10mmshift/
mv run*.root treefiles/5910/ICRU/4635gamma_ds/46fs_minus10mmshift/
cp 5910level.mac treefiles/5910/ICRU/4635gamma_ds/46fs_minus10mmshift/
