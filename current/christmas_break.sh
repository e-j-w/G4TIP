#!/bin/bash

#Script to run the lifetime vs. plunger offset grid over Christmas break 2015

./multiple_runs.sh 5910level.mac 200
mkdir testfiles/5910/ICRU/4635gamma/51fs_minus10mmshift/
mv run*.root testfiles/5910/ICRU/4635gamma/51fs_minus10mmshift/
cp 5910level.mac testfiles/5910/ICRU/4635gamma/51fs_minus10mmshift/
sed -i 's/'5.1e-5'/'4.1e-5'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 200
mkdir testfiles/5910/ICRU/4635gamma/41fs_minus10mmshift/
mv run*.root testfiles/5910/ICRU/4635gamma/41fs_minus10mmshift/
cp 5910level.mac testfiles/5910/ICRU/4635gamma/41fs_minus10mmshift/
sed -i 's/'"-10.0 mm"'/'"-7.5 mm"'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 200
mkdir testfiles/5910/ICRU/4635gamma/41fs_minus7.5mmshift/
mv run*.root testfiles/5910/ICRU/4635gamma/41fs_minus7.5mmshift/
cp 5910level.mac testfiles/5910/ICRU/4635gamma/41fs_minus7.5mmshift/
sed -i 's/'"-7.5 mm"'/'"-5.0 mm"'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 200
mkdir testfiles/5910/ICRU/4635gamma/41fs_minus5mmshift/
mv run*.root testfiles/5910/ICRU/4635gamma/41fs_minus5mmshift/
cp 5910level.mac testfiles/5910/ICRU/4635gamma/41fs_minus5mmshift/
sed -i 's/'"-5.0 mm"'/'"-2.5 mm"'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 200
mkdir testfiles/5910/ICRU/4635gamma/41fs_minus2.5mmshift/
mv run*.root testfiles/5910/ICRU/4635gamma/41fs_minus2.5mmshift/
cp 5910level.mac testfiles/5910/ICRU/4635gamma/41fs_minus2.5mmshift/
sed -i 's/'"-2.5 mm"'/'"-0.0 mm"'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 200
mkdir testfiles/5910/ICRU/4635gamma/41fs/
mv run*.root testfiles/5910/ICRU/4635gamma/41fs/
cp 5910level.mac testfiles/5910/ICRU/4635gamma/41fs/
sed -i 's/'4.1e-5'/'5.1e-5'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 200
mkdir testfiles/5910/ICRU/4635gamma/51fs/
mv run*.root testfiles/5910/ICRU/4635gamma/51fs/
cp 5910level.mac testfiles/5910/ICRU/4635gamma/51fs/
sed -i 's/'"-0.0 mm"'/'"-2.5 mm"'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 200
mkdir testfiles/5910/ICRU/4635gamma/51fs_minus2.5mmshift/
mv run*.root testfiles/5910/ICRU/4635gamma/51fs_minus2.5mmshift/
cp 5910level.mac testfiles/5910/ICRU/4635gamma/51fs_minus2.5mmshift/
sed -i 's/'"-2.5 mm"'/'"-5.0 mm"'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 200
mkdir testfiles/5910/ICRU/4635gamma/51fs_minus5mmshift/
mv run*.root testfiles/5910/ICRU/4635gamma/51fs_minus5mmshift/
cp 5910level.mac testfiles/5910/ICRU/4635gamma/51fs_minus5mmshift/
sed -i 's/'"-5.0 mm"'/'"-7.5 mm"'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 200
mkdir testfiles/5910/ICRU/4635gamma/51fs_minus7.5mmshift/
mv run*.root testfiles/5910/ICRU/4635gamma/51fs_minus7.5mmshift/
cp 5910level.mac testfiles/5910/ICRU/4635gamma/51fs_minus7.5mmshift/
sed -i 's/'5.1e-5'/'4.6e-5'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 200
mkdir testfiles/5910/ICRU/4635gamma/46fs_minus7.5mmshift/
mv run*.root testfiles/5910/ICRU/4635gamma/46fs_minus7.5mmshift/
cp 5910level.mac testfiles/5910/ICRU/4635gamma/46fs_minus7.5mmshift/
sed -i 's/'"-7.5 mm"'/'"-2.5 mm"'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 200
mkdir testfiles/5910/ICRU/4635gamma/46fs_minus2.5mmshift/
mv run*.root testfiles/5910/ICRU/4635gamma/46fs_minus2.5mmshift/
cp 5910level.mac testfiles/5910/ICRU/4635gamma/46fs_minus2.5mmshift/
sed -i 's/'4.6e-5'/'5.6e-5'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 200
mkdir testfiles/5910/ICRU/4635gamma/56fs_minus2.5mmshift/
mv run*.root testfiles/5910/ICRU/4635gamma/56fs_minus2.5mmshift/
cp 5910level.mac testfiles/5910/ICRU/4635gamma/56fs_minus2.5mmshift/
sed -i 's/'"-2.5 mm"'/'"-5.0 mm"'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 200
mkdir testfiles/5910/ICRU/4635gamma/56fs_minus5mmshift/
mv run*.root testfiles/5910/ICRU/4635gamma/56fs_minus5mmshift/
cp 5910level.mac testfiles/5910/ICRU/4635gamma/56fs_minus5mmshift/
sed -i 's/'"-5.0 mm"'/'"-7.5 mm"'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 200
mkdir testfiles/5910/ICRU/4635gamma/56fs_minus7.5mmshift/
mv run*.root testfiles/5910/ICRU/4635gamma/56fs_minus7.5mmshift/
cp 5910level.mac testfiles/5910/ICRU/4635gamma/56fs_minus7.5mmshift/
sed -i 's/'"-7.5 mm"'/'"-10.0 mm"'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 200
mkdir testfiles/5910/ICRU/4635gamma/56fs_minus10mmshift/
mv run*.root testfiles/5910/ICRU/4635gamma/56fs_minus10mmshift/
cp 5910level.mac testfiles/5910/ICRU/4635gamma/56fs_minus10mmshift/
sed -i 's/'"-10.0 mm"'/'"-0.0 mm"'/g' 5910level.mac
./multiple_runs.sh 5910level.mac 200
mkdir testfiles/5910/ICRU/4635gamma/56fs/
mv run*.root testfiles/5910/ICRU/4635gamma/56fs/
cp 5910level.mac testfiles/5910/ICRU/4635gamma/56fs/


