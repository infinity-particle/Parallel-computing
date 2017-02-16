#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <xmmintrin.h>

#define MATRIX_SIZE 8
#define ELEMENT_SIZE 4

// double A[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE];
// double B[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE];
// double C[MATRIX_SIZE][MATRIX_SIZE][ELEMENT_SIZE][ELEMENT_SIZE];

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

	int j = 0;
	int i = 0;
	begin = clock();

	for(int row = 0; row < MATRIX_SIZE; row++){
		for(int column = 0; column < MATRIX_SIZE; column++){
			for(int elementRow = 0; elementRow < ELEMENT_SIZE; elementRow++){
				
			}
		}
	}

	end = clock();
	printf("Elapsed time: %f\n", (double)(end - begin)/CLOCKS_PER_SEC);
	return 0;
}

/*
__m128d A00_A10 = _mm_setr_pd(A[row][column][0][0],A[row][column][1][0]);
__m128d A01_A11 = _mm_setr_pd(A[row][column][0][1],A[row][column][1][1]);

__m128d A02_A12 = _mm_setr_pd(A[row][column][0][2], A[row][column][1][2]);
__m128d A03_A13 = _mm_setr_pd(A[row][column][0][3], A[row][column][1][3]);

__m128d A20_A30 = _mm_setr_pd(A[row][column][2][0], A[row][column][3][0]);
__m128d A21_A31 = _mm_setr_pd(A[row][column][2][1], A[row]column][3][1]);

__m128d A22_A32 = _mm_setr_pd(A[row][column][2][2], A[row][column][3][2]);
__m128d A23_A33 = _mm_setr_pd(A[row][column][2][3], A[row][column][3][3]);

__m128d b00 = _mm_set1_pd(B[row][column][0][0]);
__m128d b10 = _mm_set1_pd(B[row][column][1][0]);
__m128d b20 = _mm_set1_pd(B[row][column][2][0]);
__m128d b30 = _mm_set1_pd(B[row][column][3][0]);

__m128d b01 = _mm_set1_pd(B[row][column][0][1]);
__m128d b11 = _mm_set1_pd(B[row][column][1][1]);
__m128d b21 = _mm_set1_pd(B[row][column][2][1]);
__m128d b31 = _mm_set1_pd(B[row][column][3][1]);
*/
