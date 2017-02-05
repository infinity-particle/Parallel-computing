#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <stdlib.h>

class Matrix{
    public:
        Matrix();
        Matrix(int row, int column);

        void fill(double number);
        void fillRandom(double range);

        int getRowCount();
        int getColumnCount();
        void setElement(int row, int column, int number);

        Matrix& operator = (const Matrix& matrix);

        class Proxy{
            public:
                Proxy(double* array);
                double operator[](int index) const;
                double& operator[](int index);
            private:
                double* array;
        };

        Proxy operator [](int index) const;
        Proxy& operator [](int index);

        ~Matrix();
    private:
        double** matrix;
        int rowCount;
        int columnCount;
};

#endif //MATRIX_H
