# define RBG_CHANNELS 3

__global__ void rbg_to_grayscale(unsigned char * grayscale_image, unsigned char * rbg_image, int width, int height)
{
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < width && y < height) 
    {   
        int grayscale_offset = y*width + x;
        int rgb_offset = grayscale_offset * CHANNELS;

        unsigned char R = rgb_image[rgb_offset];
        unsigned char G = rgb_image[rgb_offset + 1]; 
        unsigned char B = rgb_image[rgb_offset + 2]; 

        grayscale_image[grayscale_offset] = 0.3f*R + 0.59f*G + 0.11f*B;
    }   
}

int main(int argc, char **argv)
{
    // Allocate memory for image

    // Import image to convert

    // Duplicate image for conversion?

    // Find width/height of image (in pixels)
    // N = number of elements to process * 3???

    //Allocate memory for arrays on host
    size_t bytes = N*sizeof(int);
    int *size_x = (int*)malloc(bytes);
    int *size_y = (int*)malloc(bytes);

    // Allocate memory for arrays on device
    int x, y;
    cudaMallocManaged(&x, N*sizeof(float));    cudaMallocManaged(&y, N*sizeof(float));

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

    rgb_to_grayscale<< number_of_blocks, threads_per_block>>();
    cudaDeviceSynchroonize();

    // Copy data from device array to host array??

    // Check data for correctness??


    // Free host memory
    free(size_x);
    free(size_y);

    // Free device memory
    cudaFree(x);
    cudaFree(y);

    return 0;

}
                                                      

