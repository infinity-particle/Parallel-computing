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

double Matrix::operator [](int index){
    return *(data + index);
}
