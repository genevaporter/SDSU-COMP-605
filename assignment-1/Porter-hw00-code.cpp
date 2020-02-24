/*
 * Homework 0:
 * 1. Use strictly serial computations (matrix-vactor, vector-matrix)
 * 2. Measure execution times of multiplication
 * 3. Make FAST and ELEGANT!
 * 4. Check for memory leaks with valgrind:
 *    >> valgrind --tool=memcheck --leak-check=yes ./assignment-1.cpp
 * 5. Compile with and without optimization flags:
 *    >> g++ -O3 assignment-1.cpp
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
    double sum;
    double time[2], average[2];
    struct timeval start[2], end[2];
    int number_of_multiplications, i, j, k, m, n, w, x, y, z;
    int ijk[3];

    // Allocate memory for A, B, C    
    int mem = 2000;
    double *A = (double *)malloc(mem * mem * sizeof(double)); 
    double *B = (double *)malloc(mem * mem * sizeof(double));
    double *C = (double *)malloc(mem * mem * sizeof(double));

    // Reading input file, determining how many matrix multiplications are needed.
    ifstream all_matricies("input2.txt");
    all_matricies >> number_of_multiplications;
    ofstream solution("output-solutions.txt");

    // Total matrix multiplication loop
    for (w = 1; w <= number_of_multiplications; w++) {

	// Finding needed dimensions for A, B, and C
	for (x = 0; x < 3; x++) {
	    all_matricies >> ijk[x];
	}	

	// Creating matrix A
	for (y=0; y < ijk[0]; y++) {
	    for (z=0; z < ijk[1]; z++) {
		all_matricies >> *(A + y * mem + z);
	    }
	}

	// Creating matrix B
	for (y=0; y < ijk[1]; y++) {
	    for (z=0; z < ijk[2]; z++) {
		all_matricies >> *(B + y * mem + z);;
	    }
	}

	// ijk row form matrix multiplication loop
	for (m=1; m <= 100; m++) { 
	    gettimeofday(&start[0], NULL);
	    for (i = 0; i < ijk[0]; i++) {
		for (j = 0; j < ijk[2]; j++) {
		    *(C + i * mem + j) = 0;
		    for (k = 0; k < ijk[1]; k++) {
			*(C + i * mem + j) += *(A + i * mem + k) * *(B + k * mem + j);
		    }
		}		
	    }
	    gettimeofday(&end[0], NULL);
	    time[0] = ((end[0].tv_sec - start[0].tv_sec)*1000000 + end[0].tv_usec - start[0].tv_usec)/2; 
	    if (time[0] < 0) { // Sometimes negative numbers are spit out??
		m -= 1;
	    } else {
	        average[0] += time[0];
	    }
	}
	average[0] = average[0] / (100000*m);

	// jki-form matrix multiplication loop
	for (n=1; n <= 100; n++) { 
	    gettimeofday(&start[1], NULL);
	    for (j = 0; j < ijk[2]; j++) {
		for (i = 0; i < ijk[0]; i++) {
		    *(C + i * mem + j) = 0;
		}
		for (k = 0; k < ijk[1]; k++) {
		    for (i = 0; i < ijk[0]; i++) {			
			*(C + i * mem + j) += *(A + i * mem + k) * *(B + k * mem + j);
		    }
		}		
	    }
	    gettimeofday(&end[1], NULL);
	    time[1] = ((end[1].tv_sec - start[1].tv_sec)*1000000 + end[1].tv_usec - start[1].tv_usec)/2; 
	    if (time[1] < 0) { // Sometimes negative numbers are spit out??
		n -= 1;
	    } else {
	        average[1] += time[1];
	    }
	}
	average[1] = average[1] / (100000*n);

	// Store matrix C into output_solutuons.txt
	for (i=0; i < ijk[0]; i++) {
	    for (j=0; j < ijk[2]; j++) {
		if (j == ijk[2]-1) {
		    solution << fixed << setprecision(5) << *(C + i * mem + j) << '\n';
		} else {
		    solution << fixed << setprecision(5) << *(C + i * mem + j) << " ";
		}
	    }
	}
	solution << '\n';	    

	cout << '\n' << "For matrix C_" << w << " with dimensions ";
	cout << ijk[0] << " x " << ijk[2] << ":\n";
	cout << "The average time elapsed for the ijk-form was "; 
	cout << average[0] << " seconds.\n";
	cout << "The average time elapsed for the jki-form was "; 
	cout << average[1] << " seconds.\n\n";
	
	average[0] = 0; average[1] = 0;
    }	

    // Deallocate memory
    delete[] A;
    delete[] B;
    delete[] C;

    solution.close();
    return 0;
}


















