#! /bin/bash
#PBS -k o
#PBS -l nodes=1:ppn=16:core16, walltime=30:00
#PBS -N hw2
#PBS -j oe

BLOCK_SIZE="$1"

if [ -z "$1" ]
then 
	echo "Invalid/missing argument. Block size will set to 256."
	BLOCK_SIZE="256"
fi

# connect to node 10/11 first!!
nvcc -Wno-deprecated-gpu-targets hw4.cu -o hw4
./hw4 $BLOCK_SIZE

