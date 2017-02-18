#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <immintrin.h>

#define MATRIX_SIZE 8
#define ELEMENT_SIZE 4

void printMatrix(double matrix[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE]);

int main(){

	static double A[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE];
	static double B[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE];
	static double C[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE];

	srand(time(NULL));

	for(int i = 0; i < MATRIX_SIZE; i++){
		for(int j = 0; j < MATRIX_SIZE; j++){
			for(int k = 0; k < ELEMENT_SIZE; k++){
				for(int n = 0; n < ELEMENT_SIZE; n++){
					A[i][j][k][n] = (double)rand()/(double)(RAND_MAX) * 2048.0;
					B[i][j][k][n] = (double)rand()/(double)(RAND_MAX) * 2048.0;
				}
			}
		}
	}

	clock_t begin = clock();

	for(int row = 0; row < MATRIX_SIZE; row++){
		for(int column = 0; column < MATRIX_SIZE; column++){
			for(int i = 0; i < MATRIX_SIZE; i++){
				for(int elementRow = 0; elementRow < ELEMENT_SIZE; elementRow++){
					for(int elementColumn = 0; elementColumn < ELEMENT_SIZE; elementColumn++){
						for(int j = 0; j < ELEMENT_SIZE; j++){
							C[row][column][elementRow][elementColumn] += A[row][i][elementRow][j] * B[i][column][j][elementColumn];
						}
					}
				}
			}
		}
	}

	clock_t end = clock();

	printf("Elapsed time: %f\n", (double)(end - begin)/CLOCKS_PER_SEC);

	begin = clock();

	double* temp = (double*)aligned_alloc(16, sizeof(double) * ELEMENT_SIZE);
	for(int row = 0; row < MATRIX_SIZE; row++){
		for(int column = 0; column < MATRIX_SIZE; column++){
			__m256d aColumn0 = _mm256_setr_pd(A[row][column][0][0], A[row][column][1][0], A[row][column][2][0], A[row][column][3][0]);
			__m256d aColumn1 = _mm256_setr_pd(A[row][column][0][1], A[row][column][1][1], A[row][column][2][1], A[row][column][3][1]);
			__m256d aColumn2 = _mm256_setr_pd(A[row][column][0][2], A[row][column][1][2], A[row][column][2][2], A[row][column][3][2]);
			__m256d aColumn3 = _mm256_setr_pd(A[row][column][0][3], A[row][column][1][3], A[row][column][2][3], A[row][column][3][3]);

			for(int i = 0;  i < ELEMENT_SIZE; i++){
				__m256d bRow0 = _mm256_set1_pd(B[row][column][0][i]);
				__m256d bRow1 = _mm256_set1_pd(B[row][column][1][i]);
				__m256d bRow2 = _mm256_set1_pd(B[row][column][2][i]);
				__m256d bRow3 = _mm256_set1_pd(B[row][column][3][i]);

				__m256d cResult = _mm256_set1_pd(0.0);

				cResult = _mm256_add_pd(cResult, _mm256_mul_pd(aColumn0, bRow0));
				cResult = _mm256_add_pd(cResult, _mm256_mul_pd(aColumn1, bRow1));
				cResult = _mm256_add_pd(cResult, _mm256_mul_pd(aColumn3, bRow3));
				cResult = _mm256_add_pd(cResult, _mm256_mul_pd(aColumn2, bRow2));

				_mm256_store_pd(temp,cResult);

				C[row][column][0][i] = *(temp + 0);
				C[row][column][1][i] = *(temp + 1);
				C[row][column][2][i] = *(temp + 2);
				C[row][column][3][i] = *(temp + 3);
			}

			}
	}

	end = clock();
	printMatrix(C);
	printf("Elapsed time - Hand vectorization: %f\n", (double)(end - begin)/CLOCKS_PER_SEC);
	return 0;
}

void printMatrix(double matrix[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE]){
	for(int i = 0; i < MATRIX_SIZE; i++){
		for(int j = 0; j < MATRIX_SIZE; j++){
			for(int k = 0; k < ELEMENT_SIZE; k++){
				for(int n = 0; n < ELEMENT_SIZE; n++){
					printf("%.3f ", matrix[i][j][k][n]);
				}
				printf("\n");
			}
			printf("\n\n\n");
		}
	}
}
