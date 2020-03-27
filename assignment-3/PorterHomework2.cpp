/* Homework 2, COMP 605
 * Geneva Porter
 * March 26, 2020
 *
 * This assignment approximates pi using the random point ratio method and utilizing OpenMP.
 */

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <math.h>

using namespace std;

static long MULTIPLIER = 1366;
static long ADDEND = 150889;
static long PMOD = 714025;
long random_last = 0;



// Function to find random number between 0 and 1
#pragma omp threadprivate(random_last)
double random2 () {
    long random_next;
    random_next = (MULTIPLIER*random_last + ADDEND)%PMOD;
    random_last = random_next;
    return ((double)random_next/(double)PMOD);
}



int main(/*int argc, char **argv*/) {

    // Deciding number of iterations
    int N = 100000000;
    double distance, squared, ratio, interior = 0;
    int mod_step = N/10;

    // Setting up time measurement variables
    int gettimeofday(struct timeval *tv, struct timezone *tz);
    int settimeofday(const struct timeval *tv, const struct timezone *tz);
    double time_now, time_check;
    struct timeval start, end;
    gettimeofday(&start, NULL);

    // Opening iteration table .txt file
    //ofstream solution("solution-table.txt");
    //solution << "Iterations Approximation";
    //solution << '\n';
    cout << setw(15) << left << "Iterations" 
	 << setw(15) << left << "Approximation"  
	 << setw(15) << left << "Thread ID" << '\n'; 
	 


    // Allocating Memory
    double *d, *x, *y, *p;
    d = new double[N];
    x = new double[N];
    y = new double[N];
    p = new double[N];

    
    // Loop to find ratio
    #pragma omp parallel for
    for(int i = 0; i <= N; i++) {
	x[i] = random2();
	y[i] = random2();
    }

    #pragma omp parallel for
    for(int i = 0; i <= N; i++) {
	d[i] = pow(x[i]*x[i] + y[i]*y[i], 0.5);
    }

    //#pragma omp parallel for
    for(int i = 0; i <= N; i++) {
	if (d[i] <= 1) {
	    interior ++;
	}
	p[i] = 4 * interior / (i+1);
    }

    gettimeofday(&end, NULL);
    time_now = ((end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec)/2;
    time_check = time_now / 60000000;
    if (time_check >= 30) {
	cout << "Run time has exceeded 30 minutes. Ending program now.";
	return 0;
    }

    for(int i = 1; i <= N; i++) {

	// Printing Pi approximations at regular intervals for comparison
        if (i == 10     || i == 100     || i == 1000 || i == 10000 || 
	    i == 100000 || i == 1000000 || i % mod_step == 0) {
            //solution << i << '\t' << ratio << '\n';
	    cout << setw(15) << left << i 
	 	 << setw(15) << left << setprecision(10) << p[i-1] 
		 << setw(15) << left << "thread_id" << '\n'; 
	}

    }


    // Deallocating memory
    delete [] p;
    delete [] x;
    delete [] y;

    //solution.close();

    return 0;
}

