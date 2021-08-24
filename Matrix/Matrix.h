#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <vector>

#include "MatrixImpl.h"

template <typename T>
class Matrix {
private:
    MatrixImpl<T>* impl;

public:
    class MatrixIterator{
    private:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;  // or also value_type*
        using reference         = T&;  // or also value_type&
        MatrixImpl<T>* impl;
        int index;

    public:
        MatrixIterator(int _index, MatrixImpl<T>* _impl): index(_index), impl(_impl){};
        ~MatrixIterator();

        MatrixIterator& operator++();
        MatrixIterator operator++(int);
        reference operator*() const;
        pointer operator->();

        friend bool operator== (const MatrixIterator& lhs, const MatrixIterator& rhs) {return lhs.index == rhs.index;};
        friend bool operator!= (const MatrixIterator& lhs, const MatrixIterator& rhs) {return lhs.index != rhs.index;};
    };

    class MatrixRowIterator {

    };

    class MatrixColumnIterator {

    };

    typedef MatrixRowIterator rowIterator;
    typedef MatrixColumnIterator columnIterator;
    typedef MatrixRowIterator const_rowIterator;
    typedef MatrixColumnIterator const_columnIterator;

    Matrix(int row, int col);
    Matrix(Matrix&& other); //Move constructor
    Matrix(Matrix& other); //Copy constructor
    ~Matrix();
    int refCount();
    rowIterator erase(rowIterator rowIter);
    columnIterator erase(columnIterator rowIter);
    void swap(Matrix& other);
    void insertRow(std::vector<T*> row, int rowIndex);
    void insertColumn(std::vector<T*> column, int columnIndex);

    rowIterator beginRow();
    rowIterator endRow();
    const const_rowIterator beginConstRow();
    const const_rowIterator endConstRow();

    columnIterator beginColumn();
    columnIterator endColumn();
    const const_columnIterator beginConstColumn();
    const const_columnIterator endConstColumn();
};


#endif //MATRIX_MATRIX_H
