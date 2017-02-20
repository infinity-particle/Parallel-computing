#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#ifdef __AVX__
	#include <immintrin.h>
#else
	#include <xmmintrin.h>
#endif

#define MATRIX_SIZE 8
#define ELEMENT_SIZE 4

typedef struct matrix{
	#ifdef __AVX__
		double elements[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE] __attribute__((aligned(32)));
	#else
		double elements[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE] __attribute__((aligned(16)));
	#endif
}matrix;

void printMatrix(const matrix* matrix);
bool check(const matrix* standartMatrix, const matrix* matrix);
unsigned long long rdtsc();

#pragma GCC push_options
#pragma GCC optimize ("-O0")
unsigned long long vectorMultiplication(const matrix* matrixA,const matrix* matrixB, matrix* matrixC){
	unsigned long long startNumberOfCycles, endNumberOfCycles;

	startNumberOfCycles = rdtsc();

	for(int row = 0; row < MATRIX_SIZE; row++){
		for(int column = 0; column < MATRIX_SIZE; column++){
			#ifdef __AVX__
				__m256d cRow0 = _mm256_load_pd(&matrixC->elements[row][column][0][0]);
				__m256d cRow1 = _mm256_load_pd(&matrixC->elements[row][column][1][0]);
				__m256d cRow2 = _mm256_load_pd(&matrixC->elements[row][column][2][0]);
				__m256d cRow3 = _mm256_load_pd(&matrixC->elements[row][column][3][0]);
			#else
				__m128d C00_01 = _mm_load_pd(&matrixC->elements[row][column][0][0]);
				__m128d C02_03 = _mm_load_pd(&matrixC->elements[row][column][0][2]);

				__m128d C10_11 = _mm_load_pd(&matrixC->elements[row][column][1][0]);
				__m128d C12_13 = _mm_load_pd(&matrixC->elements[row][column][1][2]);

				__m128d C20_21 = _mm_load_pd(&matrixC->elements[row][column][2][0]);
				__m128d C22_23 = _mm_load_pd(&matrixC->elements[row][column][2][2]);

				__m128d C30_31 = _mm_load_pd(&matrixC->elements[row][column][3][0]);
				__m128d C32_33 = _mm_load_pd(&matrixC->elements[row][column][3][2]);
			#endif
			for(int inner = 0; inner < MATRIX_SIZE; inner++){
				#ifdef __AVX__
					__m256d bRow0 = _mm256_load_pd(&matrixB->elements[inner][column][0][0]);
					__m256d bRow1 = _mm256_load_pd(&matrixB->elements[inner][column][1][0]);
					__m256d bRow2 = _mm256_load_pd(&matrixB->elements[inner][column][2][0]);
					__m256d bRow3 = _mm256_load_pd(&matrixB->elements[inner][column][3][0]);


					__m256d A00 = _mm256_load1_pd(&matrixA->elements[row][inner][0][0]);
					__m256d A01 = _mm256_load1_pd(&matrixA->elements[row][inner][0][1]);
					__m256d A02 = _mm256_load1_pd(&matrixA->elements[row][inner][0][2]);
					__m256d A03 = _mm256_load1_pd(&matrixA->elements[row][inner][0][3]);

					__m256d A10 = _mm256_load1_pd(&matrixA->elements[row][inner][1][0]);
					__m256d A11 = _mm256_load1_pd(&matrixA->elements[row][inner][1][1]);
					__m256d A12 = _mm256_load1_pd(&matrixA->elements[row][inner][1][2]);
					__m256d A13 = _mm256_load1_pd(&matrixA->elements[row][inner][1][3]);

					__m256d A20 = _mm256_load1_pd(&matrixA->elements[row][inner][2][0]);
					__m256d A21 = _mm256_load1_pd(&matrixA->elements[row][inner][2][1]);
					__m256d A22 = _mm256_load1_pd(&matrixA->elements[row][inner][2][2]);
					__m256d A23 = _mm256_load1_pd(&matrixA->elements[row][inner][2][3]);

					__m256d A30 = _mm256_load1_pd(&matrixA->elements[row][inner][3][0]);
					__m256d A31 = _mm256_load1_pd(&matrixA->elements[row][inner][3][1]);
					__m256d A32 = _mm256_load1_pd(&matrixA->elements[row][inner][3][2]);
					__m256d A33 = _mm256_load1_pd(&matrixA->elements[row][inner][3][3]);

					cRow0 = _mm256_add_pd(cRow0, _mm256_mul_pd(A00, bRow0));
					cRow0 = _mm256_add_pd(cRow0, _mm256_mul_pd(A01, bRow1));
					cRow0 = _mm256_add_pd(cRow0, _mm256_mul_pd(A02, bRow2));
					cRow0 = _mm256_add_pd(cRow0, _mm256_mul_pd(A03, bRow3));

					cRow1 = _mm256_add_pd(cRow1, _mm256_mul_pd(A10, bRow0));
					cRow1 = _mm256_add_pd(cRow1, _mm256_mul_pd(A11, bRow1));
					cRow1 = _mm256_add_pd(cRow1, _mm256_mul_pd(A12, bRow2));
					cRow1 = _mm256_add_pd(cRow1, _mm256_mul_pd(A13, bRow3));

					cRow2 = _mm256_add_pd(cRow2, _mm256_mul_pd(A20, bRow0));
					cRow2 = _mm256_add_pd(cRow2, _mm256_mul_pd(A21, bRow1));
					cRow2 = _mm256_add_pd(cRow2, _mm256_mul_pd(A22, bRow2));
					cRow2 = _mm256_add_pd(cRow2, _mm256_mul_pd(A23, bRow3));

					cRow3 = _mm256_add_pd(cRow3, _mm256_mul_pd(A30, bRow0));
					cRow3 = _mm256_add_pd(cRow3, _mm256_mul_pd(A31, bRow1));
					cRow3 = _mm256_add_pd(cRow3, _mm256_mul_pd(A32, bRow2));
					cRow3 = _mm256_add_pd(cRow3, _mm256_mul_pd(A33, bRow3));

					_mm256_store_pd(&matrixC->elements[row][column][0][0],cRow0);
					_mm256_store_pd(&matrixC->elements[row][column][1][0],cRow1);
					_mm256_store_pd(&matrixC->elements[row][column][2][0],cRow2);
					_mm256_store_pd(&matrixC->elements[row][column][3][0],cRow3);
				#else
					__m128d B00_B01 = _mm_load_pd(&matrixB->elements[inner][column][0][0]);
					__m128d B02_B03 = _mm_load_pd(&matrixB->elements[inner][column][0][2]);
					__m128d B10_B11 = _mm_load_pd(&matrixB->elements[inner][column][1][0]);
					__m128d B12_B13 = _mm_load_pd(&matrixB->elements[inner][column][1][2]);
					__m128d B20_B21 = _mm_load_pd(&matrixB->elements[inner][column][2][0]);
					__m128d B22_B23 = _mm_load_pd(&matrixB->elements[inner][column][2][2]);
					__m128d B30_B31 = _mm_load_pd(&matrixB->elements[inner][column][3][0]);
					__m128d B32_B33 = _mm_load_pd(&matrixB->elements[inner][column][3][2]);

					__m128d A00 = _mm_load1_pd(&matrixA->elements[row][inner][0][0]);
					__m128d A01 = _mm_load1_pd(&matrixA->elements[row][inner][0][1]);
					__m128d A02 = _mm_load1_pd(&matrixA->elements[row][inner][0][2]);
					__m128d A03 = _mm_load1_pd(&matrixA->elements[row][inner][0][3]);

					__m128d A10 = _mm_load1_pd(&matrixA->elements[row][inner][1][0]);
					__m128d A11 = _mm_load1_pd(&matrixA->elements[row][inner][1][1]);
					__m128d A12 = _mm_load1_pd(&matrixA->elements[row][inner][1][2]);
					__m128d A13 = _mm_load1_pd(&matrixA->elements[row][inner][1][3]);

					__m128d A20 = _mm_load1_pd(&matrixA->elements[row][inner][2][0]);
					__m128d A21 = _mm_load1_pd(&matrixA->elements[row][inner][2][1]);
					__m128d A22 = _mm_load1_pd(&matrixA->elements[row][inner][2][2]);
					__m128d A23 = _mm_load1_pd(&matrixA->elements[row][inner][2][3]);

					__m128d A30 = _mm_load1_pd(&matrixA->elements[row][inner][3][0]);
					__m128d A31 = _mm_load1_pd(&matrixA->elements[row][inner][3][1]);
					__m128d A32 = _mm_load1_pd(&matrixA->elements[row][inner][3][2]);
					__m128d A33 = _mm_load1_pd(&matrixA->elements[row][inner][3][3]);

					


					C00_01 = _mm_add_pd(C00_01, _mm_mul_pd(A00, B00_B01));
					C00_01 = _mm_add_pd(C00_01, _mm_mul_pd(A01, B10_B11));
					C00_01 = _mm_add_pd(C00_01, _mm_mul_pd(A02, B20_B21));
					C00_01 = _mm_add_pd(C00_01, _mm_mul_pd(A03, B30_B31));

					C02_03 = _mm_add_pd(C02_03, _mm_mul_pd(A00, B02_B03));
					C02_03 = _mm_add_pd(C02_03, _mm_mul_pd(A01, B12_B13));
					C02_03 = _mm_add_pd(C02_03, _mm_mul_pd(A02, B22_B23));
					C02_03 = _mm_add_pd(C02_03, _mm_mul_pd(A03, B32_B33));

					C10_11 = _mm_add_pd(C10_11, _mm_mul_pd(A10, B00_B01));
					C10_11 = _mm_add_pd(C10_11, _mm_mul_pd(A11, B10_B11));
					C10_11 = _mm_add_pd(C10_11, _mm_mul_pd(A12, B20_B21));
					C10_11 = _mm_add_pd(C10_11, _mm_mul_pd(A13, B30_B31));

					C12_13 = _mm_add_pd(C12_13, _mm_mul_pd(A10, B02_B03));
					C12_13 = _mm_add_pd(C12_13, _mm_mul_pd(A11, B12_B13));
					C12_13 = _mm_add_pd(C12_13, _mm_mul_pd(A12, B22_B23));
					C12_13 = _mm_add_pd(C12_13, _mm_mul_pd(A13, B32_B33));

					C20_21 = _mm_add_pd(C20_21, _mm_mul_pd(A20, B00_B01));
					C20_21 = _mm_add_pd(C20_21, _mm_mul_pd(A21, B10_B11));
					C20_21 = _mm_add_pd(C20_21, _mm_mul_pd(A22, B20_B21));
					C20_21 = _mm_add_pd(C20_21, _mm_mul_pd(A23, B30_B31));

					C22_23 = _mm_add_pd(C22_23, _mm_mul_pd(A20, B02_B03));
					C22_23 = _mm_add_pd(C22_23, _mm_mul_pd(A21, B12_B13));
					C22_23 = _mm_add_pd(C22_23, _mm_mul_pd(A22, B22_B23));
					C22_23 = _mm_add_pd(C22_23, _mm_mul_pd(A23, B32_B33));

					C30_31 = _mm_add_pd(C30_31, _mm_mul_pd(A30, B00_B01));
					C30_31 = _mm_add_pd(C30_31, _mm_mul_pd(A31, B10_B11));
					C30_31 = _mm_add_pd(C30_31, _mm_mul_pd(A32, B20_B21));
					C30_31 = _mm_add_pd(C30_31, _mm_mul_pd(A33, B30_B31));

					C32_33 = _mm_add_pd(C32_33, _mm_mul_pd(A30, B02_B03));
					C32_33 = _mm_add_pd(C32_33, _mm_mul_pd(A31, B12_B13));
					C32_33 = _mm_add_pd(C32_33, _mm_mul_pd(A32, B22_B23));
					C32_33 = _mm_add_pd(C32_33, _mm_mul_pd(A33, B32_B33));


					_mm_store_pd(&matrixC->elements[row][column][0][0], C00_01);
					_mm_store_pd(&matrixC->elements[row][column][0][2], C02_03);

					_mm_store_pd(&matrixC->elements[row][column][1][0], C10_11);
					_mm_store_pd(&matrixC->elements[row][column][1][2], C12_13);

					_mm_store_pd(&matrixC->elements[row][column][2][0], C20_21);
					_mm_store_pd(&matrixC->elements[row][column][2][2], C22_23);

					_mm_store_pd(&matrixC->elements[row][column][3][0], C30_31);
					_mm_store_pd(&matrixC->elements[row][column][3][2], C32_33);

					#endif
			}
		}
	}

	endNumberOfCycles = rdtsc();
	return endNumberOfCycles - startNumberOfCycles;
}
#pragma GCC pop_options


int main(){
	static matrix matrixA;
	static matrix matrixB;
	static matrix standartMatrix;
	static matrix matrixC;

	unsigned long long startNumberOfCycles, endNumberOfCycles;

	srand(time(NULL));

	for(int i = 0; i < MATRIX_SIZE; i++){
		for(int j = 0; j < MATRIX_SIZE; j++){
			for(int k = 0; k < ELEMENT_SIZE; k++){
				for(int n = 0; n < ELEMENT_SIZE; n++){
					matrixA.elements[i][j][k][n] = (double)rand()/(double)(RAND_MAX) * 2048.0;
					matrixB.elements[i][j][k][n] = (double)rand()/(double)(RAND_MAX) * 2048.0;
					standartMatrix.elements[i][j][k][n] = 0.0;
					matrixC.elements[i][j][k][n] = 0.0;
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
							standartMatrix.elements[row][column][elementRow][elementColumn] += matrixA.elements[row][i][elementRow][j] * matrixB.elements[i][column][j][elementColumn];
						}
					}
				}
			}
		}
	}

	endNumberOfCycles = rdtsc();

	printf("Standart multiplication - Number of CPU cycles: %llu\n", endNumberOfCycles - startNumberOfCycles);

	unsigned long long numberOfCycles = vectorMultiplication(&matrixA,&matrixB,&matrixC);
	if(check(&standartMatrix, &matrixC)){
		printf("Manual vectorized multiplication - Number of CPU cycles: %llu\n\n", numberOfCycles);
	}else{
		printf("The multiplication result is not equal to the standart! - Number of CPU cycles: %llu\n\n", numberOfCycles);
	}

	return 0;
}

bool check(const matrix* standartMatrix, const matrix* matrix){
	for(int row = 0; row < MATRIX_SIZE; row++){
		for(int column = 0; column < MATRIX_SIZE; column++){
			for(int elementRow = 0; elementRow < ELEMENT_SIZE; elementRow++){
				for(int elementColumn = 0; elementColumn < ELEMENT_SIZE; elementColumn++){
					if(standartMatrix->elements[row][column][elementRow][elementColumn] != matrix->elements[row][column][elementRow][elementColumn]){
						return false;
					}
				}
			}
		}
	}

	return true;
}

void printMatrix(const matrix* matrix){
	for(int row = 0; row < MATRIX_SIZE; row++){
		for(int column = 0; column < MATRIX_SIZE; column++){
			for(int elementRow = 0; elementRow < ELEMENT_SIZE; elementRow++){
				for(int elementColumn = 0; elementColumn < ELEMENT_SIZE; elementColumn++){
					printf("%.3f ", matrix->elements[row][column][elementRow][elementColumn]);
				}
				printf("\n");
			}
			printf("\n\n");
		}
	}
}

unsigned long long rdtsc(){
    unsigned int low,high;
    __asm__ __volatile__ ("rdtsc" : "=a" (low), "=d" (high));
    return ((unsigned long long)high << 32) | low;
}