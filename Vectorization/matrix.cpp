#include "matrix.h"

Matrix::Matrix(){
    elements = nullptr;
    rowCount = 0;
    columnCount = 0;
}

Matrix::Matrix(int row, int column){
    rowCount = row;
    columnCount = column;

    elements = new double* [row];
    for(int i = 0; i < row; i++){
        *(elements + i) = new double [column];
    }
}

Matrix::Matrix(const Matrix& copy){
    if(this->elements != nullptr){
        for(int i = 0; i < this->rowCount; i++){
            delete [] (*(elements + i));
            *(this->elements + i) = nullptr;
        }
        delete [] this->elements;
        this->elements = nullptr;
    }

    this->rowCount = copy.getRowCount();
    this->columnCount = copy.getColumnCount();

    this->elements = new double* [this->rowCount];

    for(int i = 0; i < this->rowCount; i++){
        *(this->elements + i) = new double [this->columnCount];
    }

    for(int row = 0; row < this->rowCount; row++){
        for(int column = 0; column < this->columnCount; column++){
            *(*(this->elements + row) + column) = *(*(copy.elements + row) + column);
        }
    }
}

Matrix::~Matrix(){
    if(elements){
        for(int i = 0; i < rowCount; i++){
            delete [] *(elements + i);
            *(elements + i) = nullptr;
        }
        delete [] elements;
        elements = nullptr;
    }
}

void Matrix::fill(double number){
    for(int i = 0; i < rowCount; i++){
        for(int j = 0; j < columnCount; j++){
            *(*(elements + i) + j) = number;
        }
    }
}

void Matrix::fillRandom(double range){
    for(int i = 0; i < rowCount; i++){
        for(int j = 0; j < columnCount; j++){
            *(*(elements + i) + j) = (double)rand()/(double)(RAND_MAX) * range;
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
    *(*(elements + row) + column) = number;
}

Matrix& Matrix::operator = (const Matrix& matrix){
    if(&matrix == this){
        return *this;
    }

    if(this->elements){
        for(int row = 0; row < this->rowCount; row++){
            delete [] (*(this->elements + row));
            *(this->elements + row) = nullptr;
        }
        delete [] this->elements;
        this->elements = nullptr;
    }

    this->rowCount = matrix.getRowCount();
    this->columnCount = matrix.getColumnCount();

    this->elements = new double* [this->rowCount];

    for(int i = 0; i < this->rowCount; i++){
        *(this->elements + i) = new double [this->columnCount];
    }

    for(int row = 0; row < this->rowCount; row++){
        for(int column = 0; column < this->columnCount; column++){
            *(*(this->elements + row) + column) = *(*(matrix.elements + row) + column);
        }
    }

    return *this;
}

std::ostream& operator << (std::ostream& output, const Matrix& matrix){
    for(int row = 0; row < matrix.rowCount; row++){
        for(int column = 0; column < matrix.columnCount; column++){
            output << std::setfill(' ') << std::setw(FIELD_WIDTH) << std::left << *(*(matrix.elements + row) + column) << "\t";
        }
        output << std::endl;
    }
    return output;
}

std::istream& operator >> (std::istream& input, Matrix& matrix){
    for(int row = 0; row < matrix.rowCount; row++){
        for(int column = 0; column < matrix.columnCount; column++){
            input >> *(*(matrix.elements + row) + column);
        }
    }
    return input;
}

double& Matrix::at(int row, int column){
    return *(*(elements + row) + column);
}

double Matrix::value(int row, int column) const{
    return *(*(elements + row) + column);
}

Matrix operator * (const Matrix& A, const Matrix& B){
    Matrix result(A.rowCount, B.columnCount);
    result.fill(0);
    for(int row = 0; row < A.rowCount; row++){
        for(int column = 0; column < B.columnCount; column++){
            for(int inner = 0; inner < A.columnCount; inner++){
                *(*(result.elements + row) + column) += (*(*(A.elements + row) + inner)) *
                (*(*(B.elements + inner) + column));
            }
        }
    }

    return result;
}

Matrix operator + (const Matrix& A, const Matrix& B){
    Matrix result(A.rowCount, A.columnCount);
    result.fill(0.0);
    for(int row = 0; row < A.rowCount; row++){
        for(int column = 0; column < A.columnCount; column++){
            *(*(result.elements + row) + column) = *(*(A.elements + row) + column) +
            *(*(B.elements + row) + column);
        }
    }
    return result;
}

Matrix& Matrix::operator += (const Matrix& matrix){
    for(int row = 0; row < rowCount; row++){
        for(int column = 0; column < columnCount; column++){
            *(*(this->elements + row) + column) = *(*(this->elements + row) + column) +
            *(*(matrix.elements + row) + column);
        }
    }

    return *this;
}
