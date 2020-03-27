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

//using namespace std;

int gettimeofday(struct timeval *tv, struct timezone *tz);
int settimeofday(const struct timeval *tv, const struct timezone *tz);

struct timeval {
	time_t tv_sec;
	suseconds_t tv_usec;
};

struct timezone {
	int tz_minutesweat;
	int tz_dsttime;
};


int main(int argc, char **argv) {
	
struct timeval start1, start2, end1, end2;
double sum;
double t1, t2, a1, a2; // for measuring averages

// Allocate memory for A, B, C (transpose?) for up to 40,000 32-bit real values each.



// Read A and B values from .txt file



length_i = ;
length_j = ;
length_k = ;

for (int n=1; n <= 100, n++) { // ijk form
	gettimeofday(&start1, NULL);	

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			sum = 0;
			for (int k = 0; k < 100; k++)
			{
				sum += A[i][k] * B[k][j];
			}
		C[i][j] = sum;
		}		
	}
	gettimeofday(&end1, NULL);

	t1 = ((end1.tv_sec - start1.tv_sec)*100000 + end1.tv_usec - start1.tv_usec)/1000000.0;
	a1 += t1;

} // end ijk-form loop

for (int m=1; m <= 100, m++) { // jki form
	gettimeofday(&start2, NULL);	

	for (j = 0; j < 100; j++)
	{
		for (i = 0; i < 100; i++)
		{
			sum = 0;
		}
		for (k = 0; k < 100; k++)
			for (i = 0; i < 100; i++)
			{
				sum += A[i][k] * B[k][j];
			}
		C[i][j] = sum;
		}		
	}
	gettimeofday(&end2, NULL);

	t2 = ((end2.tv_sec - start2.tv_sec)*100000 + end2.tv_usec - start2.tv_usec)/1000000.0;
	a2 += t2;

} // end jki-form loop

	// Print matrix C
	// deallocate memory
	
	a1 /= n;
	printf("Average time elapsed for ijk-form: %.5fs\n", a1)

	a2 /= m;
	printf("Average time elapsed for jki-form: %.5fs\n", a2)

	return 0;
}

// use 

















