#!/bin/bash


./Gnm.py $1 $2
fileName=$1x$2.txt

#converting to adjacency list
if [ $# -eq 3 ]
then
    if [ $3 == 'a' ]
    then
        ./to_adj_list.py $fileName $fileName-a
    else
        ./prune.py $fileName $fileName-p
    fi
fi

