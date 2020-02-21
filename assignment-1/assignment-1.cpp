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
	struct timeval1 start, end;
	gettimeofday(&start, NULL);

	

	for (int i = 0; i < 100; i++)
	{
		
	}

	gettimeofday(&end, NULL);
	printf("ELapsed: %fs\n", ((ens.tv_sec - start.tv_sec)*100000 + end.tv_usec - start.tv_usec)/1000000.0);

	return 0;
}
