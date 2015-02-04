#!/bin/csh

rm *.txt

ls /volatile/clas/claseg4/pass2/1p1gev/carb/root/ > ./temp_1p1_carb.txt
ls /volatile/clas/claseg4/pass2/1p1gev/emp/root/ > ./temp_1p1_emp.txt
ls /volatile/clas/claseg4/pass2/1p1gev/nh3/root/ > ./temp_1p1_nh3.txt
ls /volatile/clas/claseg4/pass2/1p1gev/nd3/root/ > ./temp_1p1_nd3.txt

ls /volatile/clas/claseg4/pass2/1p3gev/carb/root/ > ./temp_1p3_carb.txt
ls /volatile/clas/claseg4/pass2/1p3gev/emp/root/ > ./temp_1p3_emp.txt
ls /volatile/clas/claseg4/pass2/1p3gev/nh3/root/ > ./temp_1p3_nh3.txt
ls /volatile/clas/claseg4/pass2/1p3gev/nd3/root/ > ./temp_1p3_nd3.txt

ls /volatile/clas/claseg4/pass2/1p5gev/carb/root/ > ./temp_1p5_carb.txt
ls /volatile/clas/claseg4/pass2/1p5gev/emp/root/ > ./temp_1p5_emp.txt
ls /volatile/clas/claseg4/pass2/1p5gev/nh3/root/ > ./temp_1p5_nh3.txt
ls /volatile/clas/claseg4/pass2/1p5gev/nd3/root/ > ./temp_1p5_nd3.txt

ls /volatile/clas/claseg4/pass2/2gev/carb/root/ > ./temp_2p0_carb.txt
ls /volatile/clas/claseg4/pass2/2gev/emp/root/ > ./temp_2p0_emp.txt
ls /volatile/clas/claseg4/pass2/2gev/nh3/root/ > ./temp_2p0_nh3.txt
ls /volatile/clas/claseg4/pass2/2gev/nd3/root/ > ./temp_2p0_nd3.txt

ls /volatile/clas/claseg4/pass2/2p2gev/carb/root/ > ./temp_2p2_carb.txt
ls /volatile/clas/claseg4/pass2/2p2gev/emp/root/ > ./temp_2p2_emp.txt
ls /volatile/clas/claseg4/pass2/2p2gev/nh3/root/ > ./temp_2p2_nh3.txt
ls /volatile/clas/claseg4/pass2/2p2gev/nd3/root/ > ./temp_2p2_nd3.txt

ls /volatile/clas/claseg4/pass2/3gev/carb/root/ > ./temp_3p0_carb.txt
ls /volatile/clas/claseg4/pass2/3gev/emp/root/ > ./temp_3p0_emp.txt
ls /volatile/clas/claseg4/pass2/3gev/nh3/root/ > ./temp_3p0_nh3.txt
ls /volatile/clas/claseg4/pass2/3gev/nd3/root/ > ./temp_3p0_nd3.txt

sed -i -e "s/root_//" *.txt
sed -i -e "s/_pass2\.a..\.root//" *.txt

sort temp_1p1_carb.txt | uniq | sort -n > 1p1_carb.txt
sort temp_1p1_emp.txt | uniq | sort -n > 1p1_emp.txt
sort temp_1p1_nd3.txt | uniq | sort -n > 1p1_nd3.txt
sort temp_1p1_nh3.txt | uniq | sort -n > 1p1_nh3.txt

sort temp_1p3_carb.txt | uniq | sort -n > 1p3_carb.txt
sort temp_1p3_emp.txt | uniq | sort -n > 1p3_emp.txt
sort temp_1p3_nd3.txt | uniq | sort -n > 1p3_nd3.txt
sort temp_1p3_nh3.txt | uniq | sort -n > 1p3_nh3.txt

sort temp_1p5_carb.txt | uniq | sort -n > 1p5_carb.txt
sort temp_1p5_emp.txt | uniq | sort -n > 1p5_emp.txt
sort temp_1p5_nd3.txt | uniq | sort -n > 1p5_nd3.txt
sort temp_1p5_nh3.txt | uniq | sort -n > 1p5_nh3.txt

sort temp_2p0_carb.txt | uniq | sort -n > 2p0_carb.txt
sort temp_2p0_emp.txt | uniq | sort -n > 2p0_emp.txt
sort temp_2p0_nd3.txt | uniq | sort -n > 2p0_nd3.txt
sort temp_2p0_nh3.txt | uniq | sort -n > 2p0_nh3.txt

sort temp_2p2_carb.txt | uniq | sort -n > 2p2_carb.txt
sort temp_2p2_emp.txt | uniq | sort -n > 2p2_emp.txt
sort temp_2p2_nd3.txt | uniq | sort -n > 2p2_nd3.txt
sort temp_2p2_nh3.txt | uniq | sort -n > 2p2_nh3.txt

sort temp_3p0_carb.txt | uniq | sort -n > 3p0_carb.txt
sort temp_3p0_emp.txt | uniq | sort -n > 3p0_emp.txt
sort temp_3p0_nd3.txt | uniq | sort -n > 3p0_nd3.txt
sort temp_3p0_nh3.txt | uniq | sort -n > 3p0_nh3.txt


find . -size 0 -type f -delete
rm temp*

cat *.txt > all_runs.txt
echo "52080" > test.txt
