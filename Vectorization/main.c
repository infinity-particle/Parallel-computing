#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <immintrin.h>

#define MATRIX_SIZE 8
#define ELEMENT_SIZE 4

void printMatrix(double matrix[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE]);
bool check(double standartMatrix[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE], double matrix[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE]);
unsigned long long rdtsc();

int main(){
	#ifdef __AVX__
		double matrixA[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE] __attribute__((aligned(32)));
		double matrixB[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE] __attribute__((aligned(32)));
		double standartMatrix[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE] __attribute__((aligned(32)));
		double matrixC[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE] __attribute__((aligned(32)));
	#else
		double matrixA[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE] __attribute__((aligned(16)));
		double matrixB[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE] __attribute__((aligned(16)));
		double standartMatrix[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE] __attribute__((aligned(16)));
		double matrixC[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE] __attribute__((aligned(16)));
	#endif

	unsigned long long startNumberOfCycles, endNumberOfCycles;

	srand(time(NULL));

	for(int i = 0; i < MATRIX_SIZE; i++){
		for(int j = 0; j < MATRIX_SIZE; j++){
			for(int k = 0; k < ELEMENT_SIZE; k++){
				for(int n = 0; n < ELEMENT_SIZE; n++){
					matrixA[i][j][k][n] = (double)rand()/(double)(RAND_MAX) * 2048.0;
					matrixB[i][j][k][n] = (double)rand()/(double)(RAND_MAX) * 2048.0;
					standartMatrix[i][j][k][n] = 0.0;
					matrixC[i][j][k][n] = 0.0;
				}
			}
		}
	}

	startNumberOfCycles = rdtsc();

	for(int row = 0; row < MATRIX_SIZE; row++){
		for(int column = 0; column < MATRIX_SIZE; column++){
			for(int i = 0; i < MATRIX_SIZE; i++){
				for(int elementRow = 0; elementRow < ELEMENT_SIZE; elementRow++){
					for(int elementColumn = 0; elementColumn < ELEMENT_SIZE; elementColumn++){
						for(int j = 0; j < ELEMENT_SIZE; j++){
							standartMatrix[row][column][elementRow][elementColumn] += matrixA[row][i][elementRow][j] * matrixB[i][column][j][elementColumn];
						}
					}
				}
			}
		}
	}

	endNumberOfCycles = rdtsc();

	printf("standartMatrix multiplication - Number of CPU cycles: %llu\n\n", endNumberOfCycles - startNumberOfCycles);

	startNumberOfCycles = rdtsc();

	for(int row = 0; row < MATRIX_SIZE; row++){
		for(int column = 0; column < MATRIX_SIZE; column++){
			for(int inner = 0; inner < MATRIX_SIZE; inner++){
				#ifdef __AVX__
					__m256d B0x = _mm256_load_pd(&matrixB[inner][column][0][0]);
					__m256d B1x = _mm256_load_pd(&matrixB[inner][column][1][0]);
					__m256d B2x = _mm256_load_pd(&matrixB[inner][column][2][0]);
					__m256d B3x = _mm256_load_pd(&matrixB[inner][column][3][0]);
				#else
					__m128d B00_B01 = _mm_load_pd(&matrixB[inner][column][0][0]);
					__m128d B02_B03 = _mm_load_pd(&matrixB[inner][column][0][2]);
					__m128d B10_B11 = _mm_load_pd(&matrixB[inner][column][1][0]);
					__m128d B12_B13 = _mm_load_pd(&matrixB[inner][column][1][2]);
					__m128d B20_B21 = _mm_load_pd(&matrixB[inner][column][2][0]);
					__m128d B22_B23 = _mm_load_pd(&matrixB[inner][column][2][2]);
					__m128d B30_B31 = _mm_load_pd(&matrixB[inner][column][3][0]);
					__m128d B32_B33 = _mm_load_pd(&matrixB[inner][column][3][2]);
				#endif

				for(int i = 0;  i < ELEMENT_SIZE; i++){
					#ifdef __AVX__
						__m256d Ax0 = _mm256_set1_pd(matrixA[row][inner][i][0]);
						__m256d Ax1 = _mm256_set1_pd(matrixA[row][inner][i][1]);
						__m256d Ax2 = _mm256_set1_pd(matrixA[row][inner][i][2]);
						__m256d Ax3 = _mm256_set1_pd(matrixA[row][inner][i][3]);

						__m256d cResult = _mm256_load_pd(&matrixC[row][column][i][0]);

						cResult = _mm256_add_pd(cResult, _mm256_mul_pd(Ax0, B0x));
						cResult = _mm256_add_pd(cResult, _mm256_mul_pd(Ax1, B1x));
						cResult = _mm256_add_pd(cResult, _mm256_mul_pd(Ax2, B2x));
						cResult = _mm256_add_pd(cResult, _mm256_mul_pd(Ax3, B3x));

						_mm256_store_pd(&matrixC[row][column][i][0],cResult);
					#else
						__m128d Ax0 = _mm_load1_pd(&matrixA[row][inner][i][0]);
						__m128d Ax1 = _mm_load1_pd(&matrixA[row][inner][i][1]);
						__m128d Ax2 = _mm_load1_pd(&matrixA[row][inner][i][2]);
						__m128d Ax3 = _mm_load1_pd(&matrixA[row][inner][i][3]);

						__m128d cResult1 = _mm_load_pd(&matrixC[row][column][i][0]);
						__m128d cResult2 = _mm_load_pd(&matrixC[row][column][i][2]);

						cResult1 = _mm_add_pd(cResult1, _mm_mul_pd(Ax0, B00_B01));
						cResult1 = _mm_add_pd(cResult1, _mm_mul_pd(Ax1, B10_B11));
						cResult1 = _mm_add_pd(cResult1, _mm_mul_pd(Ax2, B20_B21));
						cResult1 = _mm_add_pd(cResult1, _mm_mul_pd(Ax3, B30_B31));

						cResult2 = _mm_add_pd(cResult2, _mm_mul_pd(Ax0, B02_B03));
						cResult2 = _mm_add_pd(cResult2, _mm_mul_pd(Ax1, B12_B13));
						cResult2 = _mm_add_pd(cResult2, _mm_mul_pd(Ax2, B22_B23));
						cResult2 = _mm_add_pd(cResult2, _mm_mul_pd(Ax3, B32_B33));

						_mm_store_pd(&matrixC[row][column][i][0],cResult1);
						_mm_store_pd(&matrixC[row][column][i][2],cResult2);
					#endif
				}
			}
		}
	}

	endNumberOfCycles = rdtsc();

	if(check(standartMatrix, matrixC)){
		printf("Vectorized multiplication - Number of CPU cycles: %llu\n\n", endNumberOfCycles - startNumberOfCycles);
	}else{
		printf("The multiplication result is not equal to the standart! - Number of CPU cycles: %llu\n\n", endNumberOfCycles - startNumberOfCycles);
	}

	return 0;
}

bool check(double standartMatrix[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE], double matrix[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE]){
	for(int row = 0; row < MATRIX_SIZE; row++){
		for(int column = 0; column < MATRIX_SIZE; column++){
			for(int elementRow = 0; elementRow < ELEMENT_SIZE; elementRow++){
				for(int elementColumn = 0; elementColumn < ELEMENT_SIZE; elementColumn++){
					if(standartMatrix[row][column][elementRow][elementColumn] != matrix[row][column][elementRow][elementColumn]){
						return false;
					}
				}
			}
		}
	}

	return true;
}

void printMatrix(double matrix[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE]){
	for(int row = 0; row < MATRIX_SIZE; row++){
		for(int column = 0; column < MATRIX_SIZE; column++){
			for(int elementRow = 0; elementRow < ELEMENT_SIZE; elementRow++){
				for(int elementColumn = 0; elementColumn < ELEMENT_SIZE; elementColumn++){
					printf("%.3f ", matrix[row][column][elementRow][elementColumn]);
				}
				printf("\n");
			}
			printf("\n\n");
		}
	}
}

unsigned long long rdtsc(){
    unsigned int low,high;
    __asm__ __volatile__ ("rdtsc" : "=matrixA" (low), "=d" (high));
    return ((unsigned long long)high << 32) | low;
}
