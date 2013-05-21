#!/bin/bash

outputFolder=crossings/$1x$2
if [ -d $outputFolder ]; then
    rm $outputFolder -r
fi

mkdir $outputFolder


function getCrossings {
    fileName=`basename $1`
    echo processing $fileName
    outputFile=$outputFolder/$fileName
    #outputFile=$outputFolder/${fileName%.*}
    echo -n > $outputFile
    greedy/./greedy -f $1 -i $2 -t -n $3 -d -e >> $outputFile
}



for item in "${@:3}"
do
        getCrossings $item $1 $2
done
