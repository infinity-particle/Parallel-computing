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
void checkCUDAStatus(cudaError_t cudaStatus);
bool compareResults(int cudaMultiplicationResult[][MATRIX_SIZE],int cpuMultiplicationResult[][MATRIX_SIZE]);

__global__ void matrixMultiplicationKernel(int *A, int *B, int *C)
{
	int result = 0;
	int column = blockIdx.x * blockDim.x + threadIdx.x;
	int row = blockIdx.y * blockDim.y + threadIdx.y;


	if (row > MATRIX_SIZE || column > MATRIX_SIZE) return;

	for (int i = 0; i < MATRIX_SIZE; i++){
		result += A[row*MATRIX_SIZE + i] * B[i*MATRIX_SIZE + column];
	}
	C[row*MATRIX_SIZE + column] = result;
}

int main()
{
    srand(time(0));
	auto matrixA = new int[MATRIX_SIZE][MATRIX_SIZE];
	auto matrixB = new int[MATRIX_SIZE][MATRIX_SIZE];
	auto cudaMultiplicationResult = new int[MATRIX_SIZE][MATRIX_SIZE];
	auto cpuMultiplicationResult = new int[MATRIX_SIZE][MATRIX_SIZE];

	for (int i = 0; i<MATRIX_SIZE; i++){
		for (int j = 0; j < MATRIX_SIZE; j++){
			matrixA[i][j] = rand() % 2048;
			matrixB[i][j] = rand() % 2048;
			cpuMultiplicationResult[i][j] = 0;
		}
	}
	

	matrixMultiplicationWithCuda(matrixA, matrixB, cudaMultiplicationResult);
	matrixMultiplicationCPU(matrixA, matrixB, cpuMultiplicationResult);
	if(compareResults(cudaMultiplicationResult, cpuMultiplicationResult)){
		printf("Results are equals!\n");
	}else{
		printf("Results are NOT equals!\n");
	}
	system("pause");
	delete[] matrixA;
	delete[] matrixB;
	delete[] cudaMultiplicationResult;
	delete[] cpuMultiplicationResult;
}

void matrixMultiplicationWithCuda(int A[][MATRIX_SIZE],int B[][MATRIX_SIZE],int C[][MATRIX_SIZE])
{
    int *dev_a, *dev_b, *dev_c;
	clock_t begin, end;
	cudaError_t cudaStatus;

	cudaStatus = cudaMalloc((void**)&dev_a, ((MATRIX_SIZE)*(MATRIX_SIZE))*sizeof(int));
	checkCUDAStatus(cudaStatus);
	cudaStatus = cudaMalloc((void**)&dev_b, ((MATRIX_SIZE)*(MATRIX_SIZE))*sizeof(int));
	checkCUDAStatus(cudaStatus);
	cudaStatus = cudaMalloc((void**)&dev_c, ((MATRIX_SIZE)*(MATRIX_SIZE))*sizeof(int));



	cudaStatus = cudaMemcpy(dev_a, A, ((MATRIX_SIZE*MATRIX_SIZE))*sizeof(int), cudaMemcpyHostToDevice);
	checkCUDAStatus(cudaStatus);
	cudaStatus = cudaMemcpy(dev_b, B, ((MATRIX_SIZE*MATRIX_SIZE))*sizeof(int), cudaMemcpyHostToDevice);
	checkCUDAStatus(cudaStatus);

	dim3 dimBlock(BlockSize, BlockSize);
	dim3 dimGrid((MATRIX_SIZE + dimBlock.x - 1) / dimBlock.x, (MATRIX_SIZE + dimBlock.y - 1) / dimBlock.y);
	
	begin = clock();
	matrixMultiplicationKernel <<< dimGrid, dimBlock >>>(dev_a, dev_b, dev_c);
	cudaDeviceSynchronize();
	end = clock();

	cudaStatus = cudaGetLastError();
	checkCUDAStatus(cudaStatus);

	cudaStatus = cudaMemcpy(C, dev_c, ((MATRIX_SIZE*MATRIX_SIZE))*sizeof(int), cudaMemcpyDeviceToHost);
	checkCUDAStatus(cudaStatus);
	printf("CUDA time: %lf seconds\n", (double)(end - begin)/CLOCKS_PER_SEC);

	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);
}

void matrixMultiplicationCPU(int A[][MATRIX_SIZE],int B[][MATRIX_SIZE],int C[][MATRIX_SIZE]){
	clock_t begin, end;
	begin = clock();
	for (int row = 0; row < MATRIX_SIZE; row++) {  
		for (int col = 0; col < MATRIX_SIZE; col++) {  
			for (int inner = 0; inner < MATRIX_SIZE; inner++) {  
				C[row][col] += A[row][inner] * B[inner][col];  
			}   
		}  
	} 
	end = clock();
	printf("CPU time: %lf seconds\n", (double)(end - begin)/CLOCKS_PER_SEC);
}

void checkCUDAStatus(cudaError_t cudaStatus){
	if(cudaStatus != cudaSuccess){
		printf("CUDA return error code: %d", cudaStatus);
		exit(-1);
	}
}

bool compareResults(int cudaMultiplicationResult[][MATRIX_SIZE],int cpuMultiplicationResult[][MATRIX_SIZE]){
	for(int row = 0; row < MATRIX_SIZE; row++){
		for(int column = 0; column < MATRIX_SIZE; column++){
			if(cudaMultiplicationResult[row][column] != cpuMultiplicationResult[row][column]){
				return false;
			}
		}
	}
	return true;
}