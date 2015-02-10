#!/bin/sh

i=1
#while [ $i -le 4 ]
while [ $i -le 2 ]
do
    echo ''
    echo -n 'Last 60 lines of '$1' at '; date +"%Y-%m-%d %H:%M:%S"
    tail -n60 $1
#   i=$(( $i + 1 ))
    sleep 30
done

