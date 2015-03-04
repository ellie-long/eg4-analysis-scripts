#!/bin/bash

# convert -delay 40 -loop 0 1.1\ GeV/emp/Sector\ 0/*.png 

pwd
ls
eval cd "${1}/Run_Checks"
pwd
ls
eBeam="1.1"
targ="emp"
eBeamDir="${eBeam}\ GeV"
eval cd ${eBeamDir}
cd $targ
for i in `seq 0 6`
do
	sectorDir="Sector\ $i"
	eval cd $sectorDir
	folder="*.png"
	gif="Run_Check_for_${targ}_Ebeam_${eBeam}GeV_Sector_${i}.gif"
	echo "Converting $folder to ${gif} for Ebeam=${eBeam}, ${targ}, Sector ${i}..."
	convert -delay 40 -loop 0 $folder $gif
	cd ..
done
cd ../..


pwd
ls
eBeam="1.1"
targ="nh3"
eBeamDir="${eBeam}\ GeV"
eval cd ${eBeamDir}
cd $targ
for i in `seq 0 6`
do
	sectorDir="Sector\ $i"
	eval cd $sectorDir
	folder="*.png"
	gif="Run_Check_for_${targ}_Ebeam_${eBeam}GeV_Sector_${i}.gif"
	echo "Converting $folder to ${gif} for Ebeam=${eBeam}, ${targ}, Sector ${i}..."
	convert -delay 40 -loop 0 $folder $gif
	cd ..
done
cd ../..

pwd
ls
eBeam="1.3"
targ="carb"
eBeamDir="${eBeam}\ GeV"
eval cd ${eBeamDir}
cd $targ
for i in `seq 0 6`
do
	sectorDir="Sector\ $i"
	eval cd $sectorDir
	folder="*.png"
	gif="Run_Check_for_${targ}_Ebeam_${eBeam}GeV_Sector_${i}.gif"
	echo "Converting $folder to ${gif} for Ebeam=${eBeam}, ${targ}, Sector ${i}..."
	convert -delay 40 -loop 0 $folder $gif
	cd ..
done
cd ../..

pwd
ls
eBeam="1.3"
targ="emp"
eBeamDir="${eBeam}\ GeV"
eval cd ${eBeamDir}
cd $targ
for i in `seq 0 6`
do
	sectorDir="Sector\ $i"
	eval cd $sectorDir
	folder="*.png"
	gif="Run_Check_for_${targ}_Ebeam_${eBeam}GeV_Sector_${i}.gif"
	echo "Converting $folder to ${gif} for Ebeam=${eBeam}, ${targ}, Sector ${i}..."
	convert -delay 40 -loop 0 $folder $gif
	cd ..
done
cd ../..

pwd
ls
eBeam="1.3"
targ="nd3"
eBeamDir="${eBeam}\ GeV"
eval cd ${eBeamDir}
cd $targ
for i in `seq 0 6`
do
	sectorDir="Sector\ $i"
	eval cd $sectorDir
	folder="*.png"
	gif="Run_Check_for_${targ}_Ebeam_${eBeam}GeV_Sector_${i}.gif"
	echo "Converting $folder to ${gif} for Ebeam=${eBeam}, ${targ}, Sector ${i}..."
	convert -delay 40 -loop 0 $folder $gif
	cd ..
done
cd ../..

pwd
ls
eBeam="1.3"
targ="nh3"
eBeamDir="${eBeam}\ GeV"
eval cd ${eBeamDir}
cd $targ
for i in `seq 0 6`
do
	sectorDir="Sector\ $i"
	eval cd $sectorDir
	folder="*.png"
	gif="Run_Check_for_${targ}_Ebeam_${eBeam}GeV_Sector_${i}.gif"
	echo "Converting $folder to ${gif} for Ebeam=${eBeam}, ${targ}, Sector ${i}..."
	convert -delay 40 -loop 0 $folder $gif
	cd ..
done
cd ../..

pwd
ls
eBeam="1.5"
targ="emp"
eBeamDir="${eBeam}\ GeV"
eval cd ${eBeamDir}
cd $targ
for i in `seq 0 6`
do
	sectorDir="Sector\ $i"
	eval cd $sectorDir
	folder="*.png"
	gif="Run_Check_for_${targ}_Ebeam_${eBeam}GeV_Sector_${i}.gif"
	echo "Converting $folder to ${gif} for Ebeam=${eBeam}, ${targ}, Sector ${i}..."
	convert -delay 40 -loop 0 $folder $gif
	cd ..
done
cd ../..

pwd
ls
eBeam="1.5"
targ="nh3"
eBeamDir="${eBeam}\ GeV"
eval cd ${eBeamDir}
cd $targ
for i in `seq 0 6`
do
	sectorDir="Sector\ $i"
	eval cd $sectorDir
	folder="*.png"
	gif="Run_Check_for_${targ}_Ebeam_${eBeam}GeV_Sector_${i}.gif"
	echo "Converting $folder to ${gif} for Ebeam=${eBeam}, ${targ}, Sector ${i}..."
	convert -delay 40 -loop 0 $folder $gif
	cd ..
done
cd ../..

pwd
ls
eBeam="2.0"
targ="carb"
eBeamDir="${eBeam}\ GeV"
eval cd ${eBeamDir}
cd $targ
for i in `seq 0 6`
do
	sectorDir="Sector\ $i"
	eval cd $sectorDir
	folder="*.png"
	gif="Run_Check_for_${targ}_Ebeam_${eBeam}GeV_Sector_${i}.gif"
	echo "Converting $folder to ${gif} for Ebeam=${eBeam}, ${targ}, Sector ${i}..."
	convert -delay 40 -loop 0 $folder $gif
	cd ..
done
cd ../..

pwd
ls
eBeam="2.0"
targ="emp"
eBeamDir="${eBeam}\ GeV"
eval cd ${eBeamDir}
cd $targ
for i in `seq 0 6`
do
	sectorDir="Sector\ $i"
	eval cd $sectorDir
	folder="*.png"
	gif="Run_Check_for_${targ}_Ebeam_${eBeam}GeV_Sector_${i}.gif"
	echo "Converting $folder to ${gif} for Ebeam=${eBeam}, ${targ}, Sector ${i}..."
	convert -delay 40 -loop 0 $folder $gif
	cd ..
done
cd ../..

pwd
ls
eBeam="2.0"
targ="nd3"
eBeamDir="${eBeam}\ GeV"
eval cd ${eBeamDir}
cd $targ
for i in `seq 0 6`
do
	sectorDir="Sector\ $i"
	eval cd $sectorDir
	folder="*.png"
	gif="Run_Check_for_${targ}_Ebeam_${eBeam}GeV_Sector_${i}.gif"
	echo "Converting $folder to ${gif} for Ebeam=${eBeam}, ${targ}, Sector ${i}..."
	convert -delay 40 -loop 0 $folder $gif
	cd ..
done
cd ../..

pwd
ls
eBeam="2.0"
targ="nh3"
eBeamDir="${eBeam}\ GeV"
eval cd ${eBeamDir}
cd $targ
for i in `seq 0 6`
do
	sectorDir="Sector\ $i"
	eval cd $sectorDir
	folder="*.png"
	gif="Run_Check_for_${targ}_Ebeam_${eBeam}GeV_Sector_${i}.gif"
	echo "Converting $folder to ${gif} for Ebeam=${eBeam}, ${targ}, Sector ${i}..."
	convert -delay 40 -loop 0 $folder $gif
	cd ..
done
cd ../..

pwd
ls
eBeam="2.2"
targ="emp"
eBeamDir="${eBeam}\ GeV"
eval cd ${eBeamDir}
cd $targ
for i in `seq 0 6`
do
	sectorDir="Sector\ $i"
	eval cd $sectorDir
	folder="*.png"
	gif="Run_Check_for_${targ}_Ebeam_${eBeam}GeV_Sector_${i}.gif"
	echo "Converting $folder to ${gif} for Ebeam=${eBeam}, ${targ}, Sector ${i}..."
	convert -delay 40 -loop 0 $folder $gif
	cd ..
done
cd ../..

pwd
ls
eBeam="2.2"
targ="nh3"
eBeamDir="${eBeam}\ GeV"
eval cd ${eBeamDir}
cd $targ
for i in `seq 0 6`
do
	sectorDir="Sector\ $i"
	eval cd $sectorDir
	folder="*.png"
	gif="Run_Check_for_${targ}_Ebeam_${eBeam}GeV_Sector_${i}.gif"
	echo "Converting $folder to ${gif} for Ebeam=${eBeam}, ${targ}, Sector ${i}..."
	convert -delay 40 -loop 0 $folder $gif
	cd ..
done
cd ../..

pwd
ls
eBeam="3.0"
targ="carb"
eBeamDir="${eBeam}\ GeV"
eval cd ${eBeamDir}
cd $targ
for i in `seq 0 6`
do
	sectorDir="Sector\ $i"
	eval cd $sectorDir
	folder="*.png"
	gif="Run_Check_for_${targ}_Ebeam_${eBeam}GeV_Sector_${i}.gif"
	echo "Converting $folder to ${gif} for Ebeam=${eBeam}, ${targ}, Sector ${i}..."
	convert -delay 40 -loop 0 $folder $gif
	cd ..
done
cd ../..

pwd
ls
eBeam="3.0"
targ="emp"
eBeamDir="${eBeam}\ GeV"
eval cd ${eBeamDir}
cd $targ
for i in `seq 0 6`
do
	sectorDir="Sector\ $i"
	eval cd $sectorDir
	folder="*.png"
	gif="Run_Check_for_${targ}_Ebeam_${eBeam}GeV_Sector_${i}.gif"
	echo "Converting $folder to ${gif} for Ebeam=${eBeam}, ${targ}, Sector ${i}..."
	convert -delay 40 -loop 0 $folder $gif
	cd ..
done
cd ../..

pwd
ls
eBeam="3.0"
targ="nh3"
eBeamDir="${eBeam}\ GeV"
eval cd ${eBeamDir}
cd $targ
for i in `seq 0 6`
do
	sectorDir="Sector\ $i"
	eval cd $sectorDir
	folder="*.png"
	gif="Run_Check_for_${targ}_Ebeam_${eBeam}GeV_Sector_${i}.gif"
	echo "Converting $folder to ${gif} for Ebeam=${eBeam}, ${targ}, Sector ${i}..."
	convert -delay 40 -loop 0 $folder $gif
	cd ..
done
cd ../..











