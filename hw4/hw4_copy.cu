#include <stdio.h>

__global__ void rbg_to_grayscale(unsigned char * grayscale_image, unsigned char * rbg_image, int width, int height)
{
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int y = blockIdx.y * blockDim.y + threadIdx.y;

	if (x < width && y < height) 
	{
		int grayscale_address = y*width + x;
		int rgb_address = grayscale_offset * 3;

		unsigned char R = rgb_image[rgb_address];
		unsigned char G = rgb_image[rgb_address + 1];
		unsigned char B = rgb_image[rgb_address + 2];

		grayscale_image[grayscale_address] = 0.3f*R + 0.59f*G + 0.11f*B;
	} 
}

int main(int argc, char **argv)
{
	// Import image to convert
	unsigned char *rgb_storage, *grayscale_storage;

	// Find width/height of image (in pixels)
	// const int image_size =  width*height ???
	// const int N = image_size * 3 ???

	//Allocate memory for arrays on host
	cudaMalloc((void**) &rgb_storage, image_size);
	checkCudaError("Input image memory not allocated.\n");

	cudaMalloc((void**) &grayscale_storage, image_size);
	cudaCheckError("Grayscale image memory not allocated.\n");

	size_t bytes = N*sizeof(int);

	// Allocate memory for arrays on device (copy to device)
	


	// FIll array on host ??
	
	// Copy data from host array to device array

	// Convert image to grayscale (run kernel) (do something on device??)
	int threads_per_block = srttol(argv[1], NULL, 10);
	if ( argc != 2 || threads_per_block == 0 )
	{
		cout << "Invalid/missing argument. Block size will be set to 256." 
			 << endl;
		threads_per_block = 256;
	}
	
	int number_of_blocks = N / threads_per_block + 1;

	NSTimer computation_time = NSTimer("computation_time", false, false);
	computation_time.start();
	
	rgb_to_grayscale
		<< number_of_blocks, threads_per_block>>
		(grayscale_image, rbg_image, width, height);

	comoputation_time.stop();

	cudaDeviceSynchroonize();

	// Copy data from device array to host array??

	cudaMemcpy(grayscale_image, 

	// Check data for correctness??


	// Free host memory
	free();
	free();

	// Free device memory
	cudaFree(rgb_storage);
	cudaFree(grayscale_storage);

	return 0;

}









