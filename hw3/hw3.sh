#!/bin/sh

#PBS -V
#PBS -S /bin/bash
#PBS -q batch
#PBS -l nodes=node10:ppn=16:mpi+node11:ppn=16:mpi
#PBS -N porter_hw3_pingpong
#PBS -e /home/605/porter/hw3/error32.txt
#PBS -o /home/605/porter/hw3/output.txt

MESSAGE_SIZE=1000000
ITERATIONS=1000

cd /home/605/porter/hw3/
mpic++ -Wall -o porter_pingpong hw3.cpp
mpirun -np 2 ./porter_pingpong $MESSAGE_SIZE $ITERATIONS

