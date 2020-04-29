/* Homework 2, COMP 605
 * Geneva Porter
 * March 26, 2020
 *
 * This assignment approximates pi using the random point ratio method and utilizing OpenMP.
 */

#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <omp.h>

using namespace std;

static long MULTIPLIER = 1366;
static long ADDEND = 150889;
static long PMOD = 714025;
long random_last = 0;

#pragma omp threadprivate(random_last)
double find_random () {
    long random_next;
    random_next = (MULTIPLIER*random_last + ADDEND)%PMOD;
    random_last = random_next;
    return ((double)random_next/(double)PMOD);
}

void calculate_pi (int n) {

	double x, y;
	int interior = 0;	
	
	for (int i = 1; i <= n; i++) {
		x = find_random();
		y = find_random();		
		if (x*x + y*y < 1)
			interior ++;
	}
	
	cout << setw(15) << left << n-1
     	 << setw(15) << left << setprecision(10) << 4.0*interior/n
	 	 << setw(15) << left << omp_get_thread_num() << '\n'; 
}

int main(int argc, char **argv) {

	// Validating input arguments
	int thread_count = strtol(argv[1], NULL, 10);
	if ( argc != 2 || thread_count == 0) {
		cout << "Invalid/missing argument. Threads will be set to 2." << endl;
		thread_count = 2;
	}

    // Setting up table of values to print
    cout << setw(15) << left << "Iterations" 
	     << setw(15) << left << "Approximation"  
	     << setw(15) << left << "Thread #" << '\n';
    
	// Deciding number of iterations
	int N = 1000000;
	int mod_step = N/10;
	
    #pragma omp parallel for schedule(static) num_threads(thread_count) 
    for (int n = 1; n <= N; n += mod_step) {
    	calculate_pi(n);	
	}
    
    return 0;
}

