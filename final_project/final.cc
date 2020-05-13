/*  
	Final Prohect for SDSU COMP-605
	Geneva Porter, 17 May 2020
	
	The following code implements matrix-matrix multiplication 
	using text files with the following format:
	
	n 					  > Number of matrix chunks to compute
	
	i j k				| > Beginning of first matrix chunk
						|
	a11 a12 ... a1j		| i, j, k are numbers that represent
	a21 a22 ... a2j		| the dimensions of the matrices. The
	... ...     ...		| first matrix is ixj and the second
	ai1 ai2 ... aij		| matrix is jxk.
						|
	b11 b12 ... b1k		|
	b21 b22 ... b2k		|
	... ...     ...		|
	bj1 bj2 ... bjk		| > End of first matrix chunk
	
	...					  > n-1 additional matrix chunk
	
	The following guidelines are met:
	1)  The code is written in C++
	2)  It performs matrix-matrix multiplication correctly
	3)  The code works for non-square matricies
	4)  The matricies contain floating-point numbers
	5)  Both MPI and CUDA are used
	6)  The code compiles and links with no errors
	7)  Performance speedup is at least quasi-linear
	8)  Performance is faster with parallelism "ON"
	9)  A PDF is included with the attained speedup, pseudo-
		code of the algorithm, and how work is divided.
	10) The report and code are deliverd by May 17.
	
*/

# include <stdio.h>
# include <fstream.h>

__global__ void kernel(void) 
{

}

int main(int argc, char *argv[])
{
	ifstream all_matricies(argv[1]);
	all_matricies >> number_of_multiplications;
	ofstream solution("output_solution.txt");
	
	
	
	return 0;

}
	   
	   
	   
	   
	   
	   
	   
	   
	   
	   
	   
	   
	   
	   
	   
	   
	
