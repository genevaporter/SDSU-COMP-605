#!/bin/sh

#PBS -V
#PBS -S /bin/bash
#PBS -q batch
#PBS -l nodes=node10:ppn=16:mpi+node11:ppn=16:mpi
#PBS -N porter_final_tests
#PBS -l walltime=00:15:00

SIZE_I="$1"
SIZE_J="$2"
SIZE_K="$3"
BLOCK_SIZE="$4"

if (( $# < 4 ))
then
    echo "Invalid/missing arguements. Defaults: i=3, j=4, k=5, block size=32."
    SIZE_I=3
    SIZE_J=4
    SIZE_K=5
    BLOCK_SIZE=2
fi

mpic++ -c mpi_code.cpp -o a.o
nvcc -arch=sm_30 -c cuda_code.cu -o b.o
mpic++ a.o b.o -lcudart -L/usr/local/cuda/lib64 -o final_project

#./final_project $SIZE_I $SIZE_J $SIZE_K $BLOCK_SIZE

#rm *.o final_project
