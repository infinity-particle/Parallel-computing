#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <xmmintrin.h>
#include <immintrin.h>

#define MATRIX_SIZE 40
#define ELEMENT_SIZE 10

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

	/*
	begin = clock();

	for(int row = 0; row < MATRIX_SIZE; row++){
		for(int column = 0; column < MATRIX_SIZE; column++){
			__m256 aColumn0 = _mm_setr_pd(A[row][column][0][0], A[row][column][1][0], A[row][column][2][0], A[row][column][3][0]);
			__m256 aColumn1 = _mm_setr_pd(A[row][column][0][1], A[row][column][1][1], A[row][column][2][1], A[row][column][3][1]);
			__m256 aColumn2 = _mm_setr_pd(A[row][column][0][2], A[row][column][1][2], A[row][column][2][2], A[row][column][3][2]);
			__m256 aColumn3 = _mm_setr_pd(A[row][column][0][3], A[row][column][1][3], A[row][column][2][3], A[row][column][3][3]);

			for(int i = 0;  i < ELEMENT_SIZE; i++){
				__m256 bRow0 = _mm_set1_pd(B[row][column][0][i]);
				__m256 bRow1 = _mm_set1_pd(B[row][column][1][i]);
				__m256 bRow2 = _mm_set1_pd(B[row][column][2][i]);
				__m256 bRow3 = _mm_set1_pd(B[row][column][3][i]);

				__m256 cResult = _mm_set1_pd(0.0);

				_mm_add_pd(cResult, _mm_mul_pd(aColumn0, bRow0));
				_mm_add_pd(cResult, _mm_mul_pd(aColumn1, bRow1));
				_mm_add_pd(cResult, _mm_mul_pd(aColumn2, bRow2));
				_mm_add_pd(cResult, _mm_mul_pd(aColumn3, bRow3));


			}

			}
		}
	}

	end = clock();
	printf("Elapsed time - Hand vectorization: %f\n", (double)(end - begin)/CLOCKS_PER_SEC);*/
	return 0;
}
