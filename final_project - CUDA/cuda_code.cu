#include <cuda.h>
#include <cuda_runtime.h>
#include <stdio.h>

#include "./my_cuda_header.h"

#define BLOCKSIZE 16

//Kernel that performs Matrix Vector Multiplication
__global__ void MatrixVectorMultiplication(double *matrixA,
                                           double *matrixB,
                                           double *matrixC, 
                                           int i_total, 
                                           int j_total, 
                                           int k_total, 
                                           int NumberofProcessors)
{ 	
    for (int i = 0; i < i_total / NumberofProcessors + 1; i++) 
    {
        for (int k = 0; k < k_total; k++) 
        {
            double sum = 0.0;
            for (int j = 0; j < j_total; j++)
                sum += matrixA[i * j_total + j] * matrixB[j * k_total + k];
		
            matrixC[i * k_total + k] = sum;
        }
    }
    __syncthreads();
}

    
void implement_cuda_code(int mpi_rank, int mpi_processors,
                         int i_total, int j_total, int k_total,
                         double *device_matrixA,
                         double *device_matrixB,
                         double *device_matrixC,
                         double *host_matrixA,
                         double *host_matrixB,
                         double *host_matrixC,
                         int threads_per_block, int number_of_blocks)
{
    cudaSetDevice(mpi_rank);

    //Allocating the Memory on the device memory
    cudaHostAlloc( (void **)&device_matrixA, 
                   i_total * j_total / mpi_processors * sizeof(double), 
                   cudaHostAllocDefault );
    cudaHostAlloc( (void **)&device_matrixB, 
                   j_total * k_total*sizeof(double), 
                   cudaHostAllocDefault);
    cudaHostAlloc( (void **)&device_matrixC, 
                   i_total * k_total / mpi_processors * sizeof(double), 
                   cudaHostAllocDefault );

    //Copying the data from host to device
    cudaMemcpyAsync( (void *)device_matrixA, 
                     (void *)host_matrixA, 
                     i_total * j_total / mpi_processors * sizeof(double), 
                     cudaMemcpyHostToDevice );
    cudaMemcpyAsync( (void *)device_matrixB, 
                     (void *)host_matrixB,  
                     j_total * k_total * sizeof(double), 
                     cudaMemcpyHostToDevice );
    
    cudaSetDevice(mpi_rank);

    //Calling the kernel which performs Matrix Vector Product
    MatrixVectorMultiplication<<<number_of_blocks, threads_per_block>>>(device_matrixA, device_matrixB, device_matrixC, i_total, j_total, k_total, mpi_processors);		

    //Copying the value of patial result vector from device to host
    cudaMemcpy( (void *)host_matrixC, 
                (void *)device_matrixC, 
                i_total * k_total / mpi_processors * sizeof(double), 
                cudaMemcpyDeviceToHost );
    
}

void free_device_memory(double **device_matrixA, 
                        double **device_matrixB, 
                        double **device_matrixC)
{
    cudaFree( *device_matrixA );
    cudaFree( *device_matrixB );
    cudaFree( *device_matrixC );
}




