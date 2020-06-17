#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <mpi.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <math.h>

#include "./my_cuda_header.h"

using namespace std;



// Function: Creates a 1D array with m x n elements.
void make_matrix(int m, int n, double **matrix, bool zeros)
{
    double *temp_matrix = (double *)malloc(m * n * sizeof(double));
    for(int idx = 0; idx < m*n; idx++)
    {
        if (zeros == 0)
           temp_matrix[idx] =(double) rand()/RAND_MAX;
        else
           temp_matrix[idx] = 0.0f;
    }
    *matrix = temp_matrix;
}

// Function: Reads an input matrix to calculate (instead of random matrix). 
void read_matrix()
{
    // Did not have time to make this function
}

// Function: Saves the random matricies A and B and the result C to "output.txt".
void write_matrix(double *matrixA,double *matrixB, double *matrixC, int i_total, int j_total, int k_total)
{
    ofstream output("output.txt");
    output << "\n" << i_total << " " << j_total << " " << k_total << "\n\n";

    cout << "Writing matricies to text file . . . ";
    for (int i = 0; i < i_total; i++)
    {
        for (int j = 0; j < j_total; j++)
            output << fixed << setprecision(5) << matrixA[j_total*i+j] << " ";
        output << "\n";
    }
    
    for (int j = 0; j < j_total; j++)
    {
        for (int k = 0; k < k_total; k++)
            output << fixed << setprecision(5) << matrixB[k_total*j+k] << " ";
        output << "\n";
    }
    
    for (int i = 0; i < i_total; i++)
    {
        for (int k = 0; k < k_total; k++)
            output << fixed << setprecision(5) << matrixC[k_total*i+k] << " ";
        output << "\n";
    }
    cout << "Done! \nAll matricies written to output.txt.\n\n";
}




int main(int argc, char **argv)
{
    // Declaring Variables
    int mpi_rank, mpi_processors;
    int Index, Status = 1;

    int i_total, j_total, k_total, rows_per_processor;
    int threads_per_block, number_of_blocks;
    double *matrixA, *matrixB, *matrixC;
    double *host_matrixA, *host_matrixC, *cpu_matrixC;
    double *device_matrixA, *device_matrixB, *device_matrixC;
    double start_time = 0;
    double mpi_cuda_time = 0;
    double cpu_time = 0;

    // MPI Intialization.
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_processors);

    // Checking if valid number of arguements have been passed.
    if(argc < 5)
    {
        if(mpi_rank == 0)
            cout << "Invalid/missing input. Input i j k and block size.\n";
        MPI_Finalize();
        exit(-1);
    }
    
    // Assigning values for matrix sizes from the arguements passed
    i_total = atoi( argv[1] );
    j_total = atoi( argv[2] );
    k_total = atoi( argv[3] );
    threads_per_block = atoi( argv[4]);

    if (mpi_rank == 0)
        cout << "\nMatrix A is " << i_total << " x " << j_total << ", "
             << "matrix B is " << j_total << " x " << k_total << ", "
             << "and matrix C is " << i_total << " x " << k_total << ".\n\n";

    if(i_total % mpi_processors != 0)
    {
        if(mpi_rank == 0)
            printf("The Rows of the matrix can not be distributed evenly among processors \n");
        MPI_Finalize();
        exit(-1);
    }

    // Initializing the matricies
    if (mpi_rank == 0);
    {
        srand(time(0));
        make_matrix(i_total, j_total, &matrixA, 0);
        make_matrix(j_total, k_total, &matrixB, 0);
        make_matrix(i_total, k_total, &matrixC, 1);
    }

    MPI_Barrier(MPI_COMM_WORLD);
	
    //Allocating memory for matrix B by all nodes expect root node
    if(mpi_rank != 0)
        matrixB = (double *)malloc(j_total * k_total * sizeof(double));

    //Broadcasting the Vector to all the nodes from root node
    MPI_Bcast(matrixB, j_total * k_total, MPI_FLOAT, 0, MPI_COMM_WORLD);

    //Calculating how elements will be distributed to each processor
    int A_elements_per_processor = i_total * j_total / mpi_processors;
    int C_elements_per_processor = i_total * k_total / mpi_processors;

    //Allocating the chuncks of memory on the host by  all nodes
    host_matrixA = (double*)malloc(A_elements_per_processor * sizeof(double) );
    host_matrixC = (double*)malloc(C_elements_per_processor * sizeof(double));

    // Distributing chuncks of the matrix among all nodes
    MPI_Scatter(matrixA, A_elements_per_processor, MPI_DOUBLE,
                host_matrixA, A_elements_per_processor, MPI_DOUBLE,
                0, MPI_COMM_WORLD);

    // Performing matrix multiplication.
    number_of_blocks = i_total*j_total*k_total / threads_per_block + 1;
    start_time = MPI_Wtime();
    implement_cuda_code(mpi_rank, mpi_processors,
                        i_total, j_total, k_total,
                        device_matrixA, device_matrixB, device_matrixC,
                        host_matrixA, matrixB, host_matrixC,
                        threads_per_block, number_of_blocks);
    mpi_cuda_time = MPI_Wtime() - start_time;
	
    MPI_Barrier(MPI_COMM_WORLD);
	
    //Root processor gathering from all nodes to get the final result vector
    MPI_Gather(host_matrixC,C_elements_per_processor, MPI_DOUBLE, 
               matrixC, C_elements_per_processor, MPI_DOUBLE, 
               0, MPI_COMM_WORLD);

    // Compare CPU computation
    int error_count = 0; 
    start_time = MPI_Wtime();
    if (mpi_rank == 0)
    {
        cpu_matrixC = (double *)malloc(i_total * k_total * sizeof(double));
        for (int i = 0; i < i_total; i++) 
        {
            for (int j = 0; j < j_total; j++) 
            {
                for (int k = 0; k < k_total; k++)
                {
                    cpu_matrixC[i * k_total + k] += matrixA[i * j_total + j] * 
                                                   matrixB[j * k_total + k];
                }
            }
        }
    cpu_time = MPI_Wtime() - start_time;

        for(int idx = 0; idx < i_total * k_total; idx++)
        {
            int device_computation = matrixC[idx];
            int cpu_computation = cpu_matrixC[idx];
            if (device_computation != cpu_computation)
                error_count++;
        }
        if (error_count == 0)
            cout << "Multiplication check verified, all entries correct.\n"
                 << "Time using " << mpi_processors << " processors with "
                 << threads_per_block << " threads per block and "
                 << number_of_blocks << " blocks for the grid: "
                 << mpi_cuda_time << " milliseconds.\n"
                 << "Time using normal CPU processor: "
                 << cpu_time << " milliseconds.\n\n";
        else
            cout << "Error! Matrix multiplication is incorrect!\n\n";

    }


    MPI_Finalize();
    
    // Writing matricies to text file
//    if (error_count == 0)
        write_matrix(matrixA, matrixB, matrixC, i_total, j_total, k_total);

    //Freeing the host memory	
    free(matrixA);
    free(matrixB);
    free(matrixC);
    free(host_matrixA);
    free(host_matrixC);
    free(cpu_matrixC);
    free(device_matrixA);
    free(device_matrixB);
    free(device_matrixC);
    // Freeing device memory
    free_device_memory(&device_matrixA, &device_matrixB, &device_matrixC);
	
    return(0);
}


