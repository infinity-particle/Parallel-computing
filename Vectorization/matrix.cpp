#include "matrix.h"

Matrix::Matrix(){
    data = nullptr;
}

Matrix::Matrix(int row, int column, int elementRow, int elementColumn){
    /*data = (double****)malloc(row * sizeof(double***));
    for(int  i = 0; i < row; i++){
        *(data + i) = (double***)malloc(column * sizeof(double**));
    }

    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            *(*(data + i) + j) = (double**)malloc(elementRow * sizeof(double*));
        }
    }

    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            for(int k = 0; k < elementRow; k++){
                *(*(*(data + i) + j) + k) = (double*)malloc(elementColumn * sizeof(double));
            }
        }
    }
*/
    rowCount = row;
    columnCount = column;
    elementRowCount = elementRow;
    elementColumnCount = elementColumn;

    int memorySize = elementRow * elementColumn * row * column;

    data = new double[memorySize];
}

Matrix::~Matrix(){
    /*for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            for(int k = 0; k < elementRow; k++){
                free(*(*(*(data + i) + j) + k));
                *(*(*(data + i) + j) + k) = nullptr;
            }
        }
    }

    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            free(*(*(data + i) + j));
            *(*(data + i) + j) = nullptr;
        }
    }

    for(int  i = 0; i < row; i++){
        free(*(data + i));
        *(data + i) = nullptr;
    }

    free(data);
    data = nullptr;*/
    free(data);
    data = nullptr;
}

void Matrix::fill(double number){
    for(int i = 0; i < rowCount; i++){
        for(int j = 0; j < columnCount; j++){
            for(int k = 0; k < elementRowCount; k++){
                for(int n = 0; n < elementColumnCount; n++){
                    *(data + i * rowCount + j * columnCount + k * elementRowCount + n * elementColumnCount) = number;
                }
            }
        }
    }
}

void Matrix::fillRandom(double range){
    for(int i = 0; i < rowCount; i++){
        for(int j = 0; j < columnCount; j++){
            for(int k = 0; k < elementRowCount; k++){
                for(int n = 0; n < elementColumnCount; n++){
                    int index = 0;
                    index += i * rowCount;
                    index += j * columnCount;
                    index += k * elementRowCount;
                    index += n * elementColumnCount;
                    *(data + index) = (double)rand()/(double)(RAND_MAX) * range;
                }
            }
        }
    }
}

double Matrix::getElement(int row, int column, int elementRow, int elementColumn){
    int index = 0;
    index += row * rowCount;
    index += column * columnCount;
    index += elementRow * elementRowCount;
    index += elementColumn * elementColumnCount;
    return *(data + index);
}

void Matrix::setElement(int row, int column, int elementRow, int elementColumn, int number){
    int index = 0;
    index += row  * rowCount;
    index += column * columnCount;
    index += elementRow * elementRowCount;
    index += elementColumn * elementColumnCount;
    *(data + index) = number;
}

Matrix& multiplication(const Matrix& A, const Matrix& B){
    Matrix result(A.rowCount, B.columnCount, A.elementRowCount, B.elementColumnCount);
    for(int row = 0; row < A.rowCount; row++){
        for(int column = 0; column < B.columnCount; column++){
            for(int i = 0; i < A.columnCount; i++){
                for(int elementRow = 0; elementRow < A.elementRowCount; elementRow++){
                    for(int elementColumn = 0; elementColumn < B.elementColumnCount; elementColumn++){
                        for(int j = 0; j < A.elementColumnCount; j++){
                            *(result.data + row * result.rowCount + column * result.columnCount + elementRow * result.elementRowCount + elementColumn * result.elementColumnCount) +=
                            *(A.data + row * A.rowCount + i * A.columnCount + elementRow * A.elementRowCount + j * A.elementColumnCount) *
                            *(B.data + i * B.rowCount + column * B.columnCount + j * B.elementRowCount + elementColumn * B.elementColumnCount);
                        }
                    }
                }
            }
        }
    }
}
