#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <intrin.h>
#include <ctime>

using namespace std;

#define MATRIX_SIZE 1024
#define BlockSize 32

void matrixMultiplicationWithCuda(int A[][MATRIX_SIZE],int B[][MATRIX_SIZE],int C[][MATRIX_SIZE]);
void matrixMultiplicationCPU(int A[][MATRIX_SIZE],int B[][MATRIX_SIZE],int C[][MATRIX_SIZE]);

__global__ void matrixMultiplicationKernel(int *A, int *B, int *C)
{
	int result = 0;
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int row = blockIdx.y * blockDim.y + threadIdx.y;


	if (row > MATRIX_SIZE || col > MATRIX_SIZE) return;

	for (int i = 0; i < MATRIX_SIZE; i++){
		result += A[row*MATRIX_SIZE + i] * B[i*MATRIX_SIZE + col];
	}
	C[row*MATRIX_SIZE + col] = result;
}

int main()
{
    srand(time(0));
	auto A = new int[MATRIX_SIZE][MATRIX_SIZE];
	auto B = new int[MATRIX_SIZE][MATRIX_SIZE];
	auto C = new int[MATRIX_SIZE][MATRIX_SIZE];
	auto cpuMul = new int[MATRIX_SIZE][MATRIX_SIZE];

	for (int i = 0; i<MATRIX_SIZE; i++){
		for (int j = 0; j < MATRIX_SIZE; j++){
			A[i][j] = rand() % 100;
			B[i][j] = rand() % 100;
			cpuMul[i][j] = 0;
		}
	}
	

	matrixMultiplicationWithCuda(A,B,C);
	matrixMultiplicationCPU(A,B,cpuMul);
	system("pause");
	delete[]A;
	delete[]B;
	delete[]C;
}

// Helper function for using CUDA to add vectors in parallel.
void matrixMultiplicationWithCuda(int A[][MATRIX_SIZE],int B[][MATRIX_SIZE],int C[][MATRIX_SIZE])
{
    int *dev_a, *dev_b, *dev_c;
	unsigned long long begin, end;

	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	//allocate memory on global memory of gpu
	cudaError_t err = cudaMalloc((void**)&dev_a, ((MATRIX_SIZE)*(MATRIX_SIZE))*sizeof(int));
	printf("Cuda malloc A:%s \n", cudaGetErrorString(err));
	err = cudaMalloc((void**)&dev_b, ((MATRIX_SIZE)*(MATRIX_SIZE))*sizeof(int));
	printf("Cuda malloc B:%s \n", cudaGetErrorString(err));
	err = cudaMalloc((void**)&dev_c, ((MATRIX_SIZE)*(MATRIX_SIZE))*sizeof(int));
	printf("Cuda malloc C:%s \n", cudaGetErrorString(err));


	//Copy array A and B on device allocated memory
	err = cudaMemcpy(dev_a, A, ((MATRIX_SIZE*MATRIX_SIZE))*sizeof(int), cudaMemcpyHostToDevice);
	printf("Cuda memcpy to device A:%s \n", cudaGetErrorString(err));
	err = cudaMemcpy(dev_b, B, ((MATRIX_SIZE*MATRIX_SIZE))*sizeof(int), cudaMemcpyHostToDevice);
	printf("Cuda memcpy to device B:%s \n", cudaGetErrorString(err));

	//two dimension threads
	dim3 dimBlock(BlockSize, BlockSize);
	dim3 dimGrid((MATRIX_SIZE + dimBlock.x - 1) / dimBlock.x, (MATRIX_SIZE + dimBlock.y - 1) / dimBlock.y);
	
	//call the kernel function multi
	cudaEventRecord(start);
	matrixMultiplicationKernel <<< dimGrid, dimBlock >> >(dev_a, dev_b, dev_c);
	cudaEventRecord(stop);

	//retrieve array C from device memory
	err = cudaMemcpy(C, dev_c, ((MATRIX_SIZE*MATRIX_SIZE))*sizeof(int), cudaMemcpyDeviceToHost);
	printf("Cuda memcpy to HOST C:%s \n", cudaGetErrorString(err));
	cudaEventSynchronize(stop);
	float milliseconds = 0;
	cudaEventElapsedTime(&milliseconds, start, stop);
	printf("CUDA time: %f ms\n", milliseconds);

	/*for (int i = 0; i < MATRIX_SIZE; i++){
		for (int j = 0; j < MATRIX_SIZE; j++){
			printf("C(%d,%d) = %d \n", i, j, C[i][j]);
		}
	}*/

	//free the memory
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);
}

void matrixMultiplicationCPU(int A[][MATRIX_SIZE],int B[][MATRIX_SIZE],int C[][MATRIX_SIZE]){
	//clock_t begin, end;

	clock_t begin = clock();
	for (int row = 0; row < MATRIX_SIZE; row++) {  
		for (int col = 0; col < MATRIX_SIZE; col++) {  
			for (int inner = 0; inner < MATRIX_SIZE; inner++) {  
				C[row][col] += A[row][inner] * B[inner][col];  
			}   
		}  
	} 
	clock_t end = clock();
	printf("CPU time: %llf sec\n", (double)(end - begin)/CLOCKS_PER_SEC);
}