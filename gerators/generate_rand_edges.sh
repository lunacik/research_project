#!/bin/bash

if [ $# -lt 2 ]
then
    echo usage: generate_rand_edges.sh output_file edges_count [vertex range]
    exit 1
fi

fileName=$1
edgesCount=$2

if [ -z $3 ]
then
    edgesRange=$2
else
    edgesRange=$3
fi

if [ -f $fileName ]
then
    rm $fileName
fi

echo "$edgesCount " > $fileName


for (( i=0; i <= $edgesCount; i++ ))
do
    number1=$[$RANDOM % $edgesRange]
    number2=$[$RANDOM % $edgesRange]
    if [ $number1 == $number2 ]
    then
         i=$(($i-1))
         continue
    fi
    grep "$number1 $number2" $fileName > /dev/null
    if [ $? == 0 ]
    then
        i=$(($i-1))
        continue
    fi 
    grep "$number2 $number1" $fileName > /dev/null
    if [ $? != 0 ] 
    then
        echo "$number1 $number2"  >> $fileName
    else
        i=$(($i-1))
        continue
    fi

done


