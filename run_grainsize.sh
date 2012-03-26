#!/bin/bash

MILLION="1000000"
DATASIZE=100
THREADS=10
ITERATIONS=3
GRAINSIZE_POWEROFTEN="8"

echo "Thread numbers: 1 .. $THREADS"
echo "Iteration number of each binary: $ITERATIONS"
echo "Map data size: " $DATASIZE

let subba=10^7
./itbb_grainsize $THREADS $DATASIZE pow(10,3)

#for grainsize in `seq 0 $GRAINSIZE_POWEROFTEN`
#do
#  echo "Grainsize: 10^$grainsize"
#  for threadnum in `seq 1 $THREADS`
#  do
#    echo "Number of threads: $threadnum"
#    for i in `seq 1 $ITERATIONS`
#    do
#      ./itbb_grainsize $threadnum $DATASIZE 10^$grainsize
#    done
#  done
#done
