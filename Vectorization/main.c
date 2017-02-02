#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct matrixElement{
	double** data;
	int rowCount;
	int columnCount;
}matrixElement;

struct matrix{
	struct matrixElement** elements;
	int rowCount;
	int columnCount;
}matrix;

double**** initMatrix(int matrixSize, int elementSize);
void fillMatrix(double ****matrix, int matrixSize, int elementSize);
void printMatrix(double ****matrix , int matrixSize, int elementSize);
void multiplicateMatrix(double**** A, double**** B, double**** C, int matrixSize, int elementSize);

int main(){
	int rowCount = 0, columnCount = 0;
	//static double ****A = NULL, ****B = NULL, ****C = NULL;
	static matrix A, B, C;

	srand(time(NULL));

	printf("Enter A matrix row count: ");
	scanf("%d", &rowCount);

	printf("Enter A column count: ");
	scanf("%d", &columnCount);

	if(rowCount && columnCount){
		A.rowCount = rowCount;
		A.columnCount = columnCount;
	}

	rowCount = 0;
	columnCount = 0;

	printf("Enter B matrix row count: ");
	scanf("%d", &rowCount);

	printf("Enter B column count: ");
	scanf("%d", &columnCount);

	if(rowCount && columnCount){
		B.rowCount = rowCount;
		B.columnCount = columnCount;
	}

	A.data = (struct element**)malloc(A.rowCount * sizeof(struct matrixElement*));

	for(int i = 0; i < A.rowCount; i++){
		*(A + i) = (struct element)malloc(A.columnCount * sizeof(struct matrixElement));
	}

	fillMatrix(A,matrixSize,elementSize);
	fillMatrix(B,matrixSize,elementSize);

	printf("\nMatrix A: \n\n");
	printMatrix(A,matrixSize,elementSize);

	printf("\nMatrix B: \n\n");
	printMatrix(B,matrixSize,elementSize);

	printf("Multiplication start\n");

	multiplicateMatrix(A, B, C, matrixSize, elementSize);

	printf("Multiplication complete!\n");

	printf("\nMatrix C: \n\n");
	printMatrix(C,matrixSize,elementSize);

	return 0;
}

double**** initMatrix(int matrixSize, int elementSize){
	double**** matrix = NULL;

	matrix = (double****)malloc(matrixSize * sizeof(double***));

	for(int i = 0; i < matrixSize; i++){
		*(matrix + i) = (double***)malloc(matrixSize * sizeof(double**));

		for(int j = 0; j < matrixSize; j++){
			*(*(matrix + i) + j) = (double**)malloc(elementSize * sizeof(double*));
			for(int k = 0; k < elementSize; k++){
				*(*(*(matrix + i) + j) + k) = (double*)malloc(elementSize * sizeof(double));
				for(int n = 0; n < elementSize; n++){
					*(*(*(*(matrix + i) + j) + k) + n) = 0.0;
				}
			}
		}
	}

	return matrix;
}

void fillMatrix(double ****matrix, int matrixSize, int elementSize){
	for(int i = 0; i < matrixSize; i++){
		for(int j = 0; j < matrixSize; j++){
			for(int k = 0; k < elementSize; k++){
				for(int n = 0; n < elementSize; n++){
					*(*(*(*(matrix + i) + j) + k) + n) = (double)rand()/(double)(RAND_MAX) * 2048.0;
					//*(*(*(*(matrix + i) + j) + k) + n) = rand() % 10;
				}
			}
		}
	}
}

void printMatrix(double ****matrix, int matrixSize, int elementSize){
	for(int i = 0; i < matrixSize; i++){
		//for(int k = 0; k < elementSize; k++){
			for(int j = 0; j < matrixSize; j++){
				for(int k = 0; k < elementSize; k++){
					for(int n = 0; n < elementSize; n++){
						printf("%7.3f ", *(*(*(*(matrix + i) + j) + k) + n));
					}
				//printf("\t");
				printf("\n");
			}
			printf("\n");
		}
		//printf("\n\n");
	}
}

void multiplicateMatrix(double**** restrict A, double**** restrict B, double**** restrict C, int matrixSize, int elementSize){
	for(int row = 0; row < matrixSize; row++){
		for(int column = 0; column < matrixSize; column++){
			for(int i = 0; i < matrixSize; i++){
				for(int elementRow = 0; elementRow < elementSize; elementRow++){
					for(int elementColumn = 0; elementColumn < elementSize; elementColumn++){
						for(int j = 0; j < elementSize; j++){
							*(*(*(*(C + row) + column) + elementRow) + elementColumn) += (*(*(*(*(A + row) + i) + elementRow) + j)) * (*(*(*(*(B + i) + column) + j) + elementColumn));
						}
					}
				}
			}
		}
	}
}