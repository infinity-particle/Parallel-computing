#include "matrix.h"

Matrix::Matrix(){
    matrix = nullptr;
    rowCount = 0;
    columnCount = 0;
}

Matrix::Matrix(int row, int column){
    rowCount = row;
    columnCount = column;

    matrix = new double* [row];
    for(int i = 0; i < row; i++){
        *(matrix + i) = new double [column];
    }
}

Matrix::Matrix(const Matrix& copy){
    if(this->matrix != nullptr){
        for(int i = 0; i < this->rowCount; i++){
            delete [] (*(matrix + i));
            *(this->matrix + i) = nullptr;
        }
        delete [] this->matrix;
        this->matrix = nullptr;
    }

    this->rowCount = copy.getRowCount();
    this->columnCount = copy.getColumnCount();

    this->matrix = new double* [this->rowCount];

    for(int i = 0; i < this->rowCount; i++){
        *(this->matrix + i) = new double [this->columnCount];
    }

    for(int row = 0; row < this->rowCount; row++){
        for(int column = 0; column < this->columnCount; column++){
            *(*(this->matrix + row) + column) = *(*(copy.matrix + row) + column);
        }
    }
}

Matrix::~Matrix(){
    if(matrix){
        for(int i = 0; i < rowCount; i++){
            delete [] *(matrix + i);
            *(matrix + i) = nullptr;
        }
        delete [] matrix;
        matrix = nullptr;
    }
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

    if(this->matrix){
        for(int row = 0; row < this->rowCount; row++){
            delete [] (*(this->matrix + row));
            *(this->matrix + row) = nullptr;
        }
        delete [] this->matrix;
        this->matrix = nullptr;
    }

    this->rowCount = matrix.getRowCount();
    this->columnCount = matrix.getColumnCount();

    this->matrix = new double* [this->rowCount];

    for(int i = 0; i < this->rowCount; i++){
        *(this->matrix + i) = new double [this->columnCount];
    }

    for(int row = 0; row < this->rowCount; row++){
        for(int column = 0; column < this->columnCount; column++){
            *(*(this->matrix + row) + column) = *(*(matrix.matrix + row) + column);
        }
    }

    return *this;
}

std::ostream& operator << (std::ostream& output, const Matrix& matrix){
    for(int row = 0; row < matrix.rowCount; row++){
        for(int column = 0; column < matrix.columnCount; column++){
            output << std::setfill(' ') << std::setw(FIELD_WIDTH) << std::left << *(*(matrix.matrix + row) + column) << "\t";
        }
        output << std::endl;
    }
    return output;
}

std::istream& operator >> (std::istream& input, Matrix& matrix){
    for(int row = 0; row < matrix.rowCount; row++){
        for(int column = 0; column < matrix.columnCount; column++){
            input >> *(*(matrix.matrix + row) + column);
        }
    }
    return input;
}

double& Matrix::at(int row, int column){
    return *(*(matrix + row) + column);
}

double Matrix::value(int row, int column) const{
    return *(*(matrix + row) + column);
}

Matrix operator * (const Matrix& A, const Matrix& B){
    Matrix result(A.rowCount, B.columnCount);
    result.fill(0);
    for(int row = 0; row < A.rowCount; row++){
        for(int column = 0; column < B.columnCount; column++){
            for(int inner = 0; inner < A.columnCount; inner++){
                result(row,column) += (*(*(A.matrix + row) + inner)) *
                (*(*(B.matrix + inner) + column));
            }
        }
    }

    return result;
}
