#include <stdio.h>
#include <cuda.h>

__global__ void vector_add(int *a, int *b, int *c)
{
    /* insert code to calculate the index properly using blockIdx.x, blockDim.x, threadIdx.x */
	int index = threadIdx.x;
	c[index] = a[index] + b[index];
}

/* experiment with N */
/* how large can it be? */
#define N 256
#define THREADS_PER_BLOCK 256

int main()
{
    int *a, *b, *c;
	int *d_a, *d_b, *d_c;
	int size = N * sizeof( int );

	/* allocate space for device copies of a, b, c */

	cudaMalloc( (void **) &d_a, size );
	cudaMalloc( (void **) &d_b, size );
	cudaMalloc( (void **) &d_c, size );

	/* allocate space for host copies of a, b, c and setup input values */

	a = (int *)malloc( size );
	b = (int *)malloc( size );
	c = (int *)malloc( size );

	for( int i = 0; i < N; i++ )
	{
		a[i] = b[i] = i;
		c[i] = 0;
	}

	/* copy inputs to device */
	/* fix the parameters needed to copy data to the device */
	cudaMemcpy( d_a, a, size, cudaMemcpyHostToDevice );
	cudaMemcpy( d_b, b, size, cudaMemcpyHostToDevice );

	/* launch the kernel on the GPU */
	/* insert the launch parameters to launch the kernel properly using blocks and threads */ 
	vector_add<<< 1, THREADS_PER_BLOCK >>>( d_a, d_b, d_c );

	/* copy result back to host */
	/* fix the parameters needed to copy data back to the host */
	cudaMemcpy( c, d_c, size, cudaMemcpyDeviceToHost );


	printf( "c[%d] = %d\n",0,c[0] );
	printf( "c[%d] = %d\n",N-1, c[N-1] );

	/* clean up */

	free(a);
	free(b);
	free(c);
	cudaFree( d_a );
	cudaFree( d_b );
	cudaFree( d_c );
	
	return 0;
} /* end main */
