#include <stdio.h>
#include <mpi.h>
#include <string.h>
#include <cstdlib>

/* 
 * MPI_INIT :           Initiate an MPI computation 
 * MPI_COMM_SIZE :      Determine the number of processes
 * MPI_COMM_RANK :      Determine my process identifier
 * MPI_SEND :           Send a message
 * MPI_RECV :           Receive a message
 * MPI_FINALIZE :       Terminat a computation
 *
 */

using namespace std;

int main(int argc, char *argv[])
{

        double start_time, end_time;
        int x, num_bytes, process_rank, process_size, tag = 99;
    	int msg_size = atoi(argv[1]);
    	int num_iterations = atoi(argv[2]);
        char message[msg_size]; // should be pointer??
        //strcpy(message, "abcdef");

        MPI_Init(&argc, &argv);
        MPI_Status status;
        MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
        MPI_Comm_size(MPI_COMM_WORLD, &process_size);



        if (process_rank == 0) {

                start_time = MPI_Wtime();

                for (x = 1; x < num_iterations; x++) {
                        MPI_Send(message, msg_size, MPI_CHAR,
                                         1, tag, MPI_COMM_WORLD);
                        MPI_Recv(message, msg_size, MPI_CHAR,
                                         1, tag, MPI_COMM_WORLD, &status);
                }

                num_bytes = 2*x*sizeof(message);

                end_time = MPI_Wtime() - start_time;
                cout << endl << "Running porter_pingpong : " << endl
                         << num_bytes << " bytes in " << end_time << " seconds = "
                         << num_bytes / 1000000 / end_time << " Mbit/sec" << endl
                         << num_iterations << " iters in " << end_time << " seconds = "
                         << num_iterations * end_time << " usec/iter" << endl << endl;

        } else {

                for (x = 1; x < num_iterations; x++) {
                        MPI_Recv(message, msg_size, MPI_CHAR,
                                         0, tag, MPI_COMM_WORLD, &status);

                        MPI_Send(message, msg_size, MPI_CHAR,
                                         0, tag, MPI_COMM_WORLD);
                }

        }

        MPI_Finalize();

        return 0;
}


