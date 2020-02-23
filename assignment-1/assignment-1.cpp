/*
 * Homework 0:
 * 1. Use strictly serial computations (matrix-vactor, vector-matrix)
 * 2. Measure execution times of multiplication
 * 3. Make FAST and ELEGANT!
 * 4. Use <gprof> profiler and check for memory leaks with <valgrind>
 *
 * valgrind --tool=memcheck --leak-check=yes ./your_binary
 *
 * Check out compiler explorer at godbolt.org
 */


#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

#include <fstream>
#include <iostream>
#include <string>

#include <iomanip>

using namespace std;

int gettimeofday(struct timeval *tv, struct timezone *tz);
int settimeofday(const struct timeval *tv, const struct timezone *tz);

int main(int argc, char **argv) {

    // variables used in loops	
    struct timeval start1, start2, end1, end2;
    double sum;
    double t1, t2, a1, a2;
    int number_of_multiplications, i, j, k, m, n, w, x, y, z;
    int ijk[3];
    string temp;

    // Allocate memory for A, B, C (transpose?) for up to 40,000 32-bit real values each.

    // Reading input file, determining how many matrix multiplications are needed.
    ifstream all_matricies("input2.txt");
    all_matricies >> number_of_multiplications;
    cout << number_of_multiplications << "\n\n";
    ofstream solution("output_solution.txt");

//*
    // Total matrix multiplication loop
    for (w = 1; w < number_of_multiplications; w++) {

	// Finding needed dimensions for A, B, and C
	for (x = 0; x < 3; x++) {
	    all_matricies >> ijk[x];
	}

	double A[ijk[0]][ijk[1]], B[ijk[1]][ijk[2]], C[ijk[0]][ijk[2]];	

	// Creating matrix A
	for (y=0; y < ijk[0]; y++) {
	    for (z=0; z < ijk[1]; z++) {
		all_matricies >> A[y][z];
	    }
	}

	// Creating matrix B
	for (y=0; y < ijk[1]; y++) {
	    for (z=0; z < ijk[2]; z++) {
		all_matricies >> B[y][z];
	    }
	}

	// ijk-form matrix multiplication loop
	for (n=1; n <= 100; n++) { 
	    gettimeofday(&start1, NULL);	

	    for (i = 0; i < ijk[0]; i++) {
		for (j = 0; j < ijk[2]; j++) {
		    sum = 0;
		    for (k = 0; k < ijk[1]; k++) {
			sum += A[i][k] * B[k][j];
		    }
		    C[i][j] = sum;
		}		
	    }
	    gettimeofday(&end1, NULL);

	    t1 = ((end1.tv_sec - start1.tv_sec)*100000 + end1.tv_usec - start1.tv_usec)/1000000.0;
	    a1 += t1;
	}// end ijk-form loop

	// jki-form matrix multiplication loop
	for (m=1; m <= 100; m++) { 
	    gettimeofday(&start2, NULL);	

	    for (j = 0; j < ijk[2]; j++) {
		for (i = 0; i < ijk[0]; i++) {
		    sum = 0;
		}
		for (k = 0; k < ijk[1]; k++) {
		    for (i = 0; i < ijk[0]; i++) {
			sum += A[i][k] * B[k][j];
		    }
		    C[i][j] = sum;
		}		
	    }
	    gettimeofday(&end2, NULL);

	    t2 = ((end2.tv_sec - start2.tv_sec)*100000 + end2.tv_usec - start2.tv_usec)/1000000.0;
	    a2 += t2;
	}// end jki-form loop

	// Print and store matrix C
	
	for (i=0; i < ijk[0]; i++) {
	    for (j=0; j < ijk[2]; j++) {
		if (j == ijk[2]-1) {
		    solution << fixed << setprecision(5) << C[i][j] << '\n';
		} else {
		    solution << fixed << setprecision(5) << C[i][j] << " ";
		}
	    }
	}
	solution << '\n';	    
	
	// deallocate memory
	
	a1 /= n;
	printf("Average time elapsed for ijk-form: %.5fs\n", a1);

	a2 /= m;
	printf("Average time elapsed for jki-form: %.5fs\n", a2);

	return 0;
    } // end matrix multiplication loop

    solution.close();
}


















