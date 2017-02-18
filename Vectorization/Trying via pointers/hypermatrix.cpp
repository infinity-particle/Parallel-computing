#include "hypermatrix.h"

Hypermatrix::Hypermatrix(){
    elements = nullptr;
    rowCount = 0;
    columnCount = 0;
    elementRowCount = 0;
    elementColumnCount = 0;
}

Hypermatrix::Hypermatrix(int row, int column, int elementRow, int elementColumn){
    rowCount = row;
    columnCount = column;
    elementRowCount = elementRow;
    elementColumnCount = elementColumn;

    elements = new Matrix* [row];
    for(int i = 0; i < row; i++){
        *(elements + i) = new Matrix [column];
    }

    for(int row = 0; row < rowCount; row++){
        for(int column = 0; column < columnCount; column++){
            *(*(elements + row) + column) = Matrix(elementRow, elementColumn);
        }
    }
}

void Hypermatrix::fill(double number){
    for(int row = 0; row < rowCount; row++){
        for(int column = 0; column < columnCount; column++){
            (*(elements + row) + column)->fill(number);
        }
    }
}

void Hypermatrix::fillRandom(double range){
    for(int row = 0; row < rowCount; row++){
        for(int column = 0; column < columnCount; column++){
            (*(elements + row) + column)->fillRandom(range);
        }
    }
}

Hypermatrix operator * (const Hypermatrix& A, const Hypermatrix& B){
    Hypermatrix result(A.rowCount, B.columnCount, A.elementRowCount, B.elementColumnCount);
    result.fill(0);

    for(int row = 0; row < A.rowCount; row++){
        for(int column = 0; column < B.columnCount; column++){
            for(int inner = 0; inner < A.columnCount; inner++){
                *(*(result.elements + row) + column) += *(*(A.elements + row) + inner) *
                *(*(B.elements + inner) + column);
            }
        }
    }

    return result;
}

std::ostream& operator << (std::ostream& output, const Hypermatrix& hypermatrix){
    for(int row = 0; row < hypermatrix.rowCount; row++){
        for(int column = 0; column < hypermatrix.columnCount; column++){
            output << *(*(hypermatrix.elements + row) + column) << std::endl;
        }
    }

    return output;
}
