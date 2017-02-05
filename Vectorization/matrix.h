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
        int calculateIndex(int row, int column, int elementRow, int elementColumn);
        double operator[](int index);
        ~Matrix();
    private:
        double* data;
        int rowCount;
        int columnCount;
        int elementRowCount;
        int elementColumnCount;
};

#endif MATRIX_H
