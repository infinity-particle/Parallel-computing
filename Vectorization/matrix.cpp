#include "matrix.h"

Matrix::Matrix(){
    matrix = nullptr;
}

Matrix::Matrix(int row, int column){
    rowCount = row;
    columnCount = column;

    matrix = new double*[row];
    for(int i = 0; i < row; i++){
        *(matrix + i) = new double[column];
    }
}

Matrix::~Matrix(){
    for(int i = 0; i < rowCount; i++){
        free(*(matrix + i));
        *(matrix + i) = nullptr;
    }
    free(matrix);
    matrix = nullptr;
}

void Matrix::fill(double number){
    for(int i = 0; i < rowCount; i++){
        for(int j = 0; j < columnCount; j++){
            *(*(matrix + i) + j) = number;
        }
    }
}

void Matrix::fillRandom(double range){
    for(int i = 0; i < rowCount; i++){
        for(int j = 0; j < columnCount; j++){
            *(*(matrix + i) + j) = (double)rand()/(double)(RAND_MAX) * range;
        }
    }
}

int Matrix::getRowCount(){
    return rowCount;
}

int Matrix::getColumnCount(){
    return columnCount;
}

void Matrix::setElement(int row, int column, int number){
    *(*(matrix + row) + column) = number;
}

Matrix& Matrix::operator = (const Matrix& matrix){
    this->rowCount = matrix.getRowCount();
    this->columnCount = matrix.getColumnCount();
    this->matrix = matrix.matrix;
    return *this;
}

Matrix::Proxy::Proxy(double* array) : array(array){

}

double Matrix::Proxy::operator [](int index) const{
    return *(array + index);
}

double& Matrix::Proxy::operator [](int index){
    return *(array + index);
}

Proxy Matrix::operator [](int index) const{
    return Proxy(matrix + index);
}

Proxy& Matrix::operator [](int index){
    return Proxy(matrix + index);
}
