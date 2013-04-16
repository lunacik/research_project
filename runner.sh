#!/bin/bash

outputFolder=crossings
sleepDelay=1

function getCrossings {
    fileName=`basename $1`
    outputFile=$outputFolder/${fileName%.*}
    echo > $outputFile
    for((it=1; it <=$2; it++)); do
        echo "$it iteration" >> $outputFile
        greedy/./greedy $1 >> $outputFile
        echo "----------------------------" >> $outputFile
        sleep $sleepDelay
    done
}



for item in "${@:2}"
do
        getCrossings $item $1
done
