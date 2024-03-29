#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>

#define FIELD_WIDTH 7

class Matrix{
    public:
        Matrix();
        Matrix(int row, int column);
        Matrix(const Matrix& copy);

        void fill(double number);
        void fillRandom(double range);

        int getRowCount() const;
        int getColumnCount() const;
        void setElement(int row, int column, int number);

        Matrix& operator = (const Matrix& matrix);
        Matrix& operator += (const Matrix& matrix);
        friend std::ostream& operator << (std::ostream& output, const Matrix& matrix);
        friend std::istream& operator >> (std::istream& input, Matrix& matrix);
        friend Matrix operator * (const Matrix& A, const Matrix& B);
        friend Matrix operator + (const Matrix& A, const Matrix& B);

        double& at(int row, int column);
        double value(int row, int column) const;

        ~Matrix();
    private:
        double** elements;
        int rowCount;
        int columnCount;
};

#endif //MATRIX_H
