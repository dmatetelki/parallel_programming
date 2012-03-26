#!/bin/bash

MAP_DATASIZE=6000000
THREADS="10"
ITERATIONS="3"

echo "Thread numbers: $THREAD_NUMBERS"
echo "Iteration number of each binary: $ITERATIONS"
echo "Map data size: $MAP_DATASIZE"


echo -e "\nsort algorithms:"
for map in $(ls *_sort* | grep -v '\.cpp')
do
	echo "Running $map ..."
  for threadnum in `seq 1 $THREADS`
	do
		echo "Number of threads: $threadnum"
		for i in `seq 1 $ITERATIONS` 
		do
			./$map $threadnum $MAP_DATASIZE
		done
	done
done
	
