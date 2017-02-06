#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include "proxy.h"

class Matrix{
    public:
        Matrix();
        Matrix(int row, int column);

        void fill(double number);
        void fillRandom(double range);

        int getRowCount() const;
        int getColumnCount() const;
        void setElement(int row, int column, int number);

        Matrix& operator = (const Matrix& matrix);
        friend std::ostream& operator << (std::ostream& output, const Matrix& matrix);
        friend std::istream& operator >> (std::istream& input, Matrix& matrix);

        Proxy operator [](int index);

        ~Matrix();
    private:
        double** matrix;
        int rowCount;
        int columnCount;
};

#endif //MATRIX_H
