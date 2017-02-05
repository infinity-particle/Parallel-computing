#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <stdlib.h>

class Matrix{
    public:
        Matrix();
        Matrix(int row, int column, int elementRow, int elementColumn);
        void fill(double number);
        void fillRandom(double range);
        double getElement(int row, int column, int elementRow, int elemenColumn);
        void setElement(int row, int column, int elementRow, int elemenColumn, int number);
        friend Matrix& multiplication(const Matrix& A, const Matrix& B);
        ~Matrix();
    private:
        double* data;
        int rowCount;
        int columnCount;
        int elementRowCount;
        int elementColumnCount;
};

#endif MATRIX_H
