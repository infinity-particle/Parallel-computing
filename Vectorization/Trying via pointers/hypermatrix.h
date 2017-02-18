#ifndef HYPERMATRIX_H
#define HYPERMATRIX_H

#include "matrix.h"

class Hypermatrix{
    public:
        Hypermatrix();
        Hypermatrix(int row, int column, int elementRow, int elementColumn);

        void fill(double number);
        void fillRandom(double range);

        friend Hypermatrix operator * (const Hypermatrix& A, const Hypermatrix& B);

        friend std::ostream& operator << (std::ostream& output, const Hypermatrix& hypermatrix);
    private:
        Matrix** elements;
        int rowCount;
        int columnCount;
        int elementRowCount;
        int elementColumnCount;
};

#endif
