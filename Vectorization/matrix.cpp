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

int Matrix::getRowCount() const{
    return rowCount;
}

int Matrix::getColumnCount() const{
    return columnCount;
}

void Matrix::setElement(int row, int column, int number){
    *(*(matrix + row) + column) = number;
}

Matrix& Matrix::operator = (const Matrix& matrix){
    if(&matrix == this){
        return *this;
    }
}

std::ostream& operator << (std::ostream& output, const Matrix& matrix){
    for(int row = 0; row < matrix.getRowCount(); row++){
        for(int column = 0; column < matrix.getColumnCount(); column++){
            output << std::setfill(' ') << std::setw(7) << std::left << *(*(matrix.matrix + row) + column) << "\t";
        }
        output << std::endl;
    }
    return output;
}

std::istream& operator >> (std::istream& input, Matrix& matrix){
    for(int row = 0; row < matrix.getRowCount(); row++){
        for(int column = 0; column < matrix.getColumnCount(); column++){
            input >> *(*(matrix.matrix + row) + column);
        }
    }
    return input;
}

Proxy Matrix::operator [](int index){
    //Proxy tmp(*(matrix + index));
    //return tmp;
    return Proxy(*(matrix + index));
}
