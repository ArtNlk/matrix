#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <vector>
#include <functional>

#include "MatrixImpl.h"

template <typename T>
class Matrix {
private:
    MatrixImpl<T>* impl;

public:
    ///@brief Iterates over rows of the matrix
    class MatrixRowIterator{
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = std::vector<T>;
        using pointer           = std::vector<T*>;  // or also value_type*
        using reference         = std::vector<std::reference_wrapper<T>>;  // or also value_type&
        Matrix<T>& matrix;
        int index;

    public:
        MatrixRowIterator(int _index, Matrix<T> &_impl): index(_index), matrix(_impl){};
        ~MatrixRowIterator() = default;

        MatrixRowIterator& operator++() {index++; return *this;};
        MatrixRowIterator operator++(int) {Matrix::MatrixRowIterator temp = *this; index++; return temp;};
        reference operator*() const;
        pointer operator->();
        int getIndex();
        friend bool operator== (const MatrixRowIterator& lhs, const MatrixRowIterator& rhs) {return lhs.index == rhs.index;};
        friend bool operator!= (const MatrixRowIterator& lhs, const MatrixRowIterator& rhs) {return lhs.index != rhs.index;};
    };

    ///@brief Iterates over columns of the matrix
    class MatrixColumnIterator{
    private:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = std::vector<T>;
        using pointer           = std::vector<T*>;  // or also value_type*
        using reference         = std::vector<std::reference_wrapper<T>>;  // or also value_type&
        Matrix<T>& matrix;
        int index;

    public:
        MatrixColumnIterator(int _index, MatrixImpl<T>& _impl): index(_index), matrix(_impl){};
        ~MatrixColumnIterator() = default;

        MatrixColumnIterator& operator++() {index++; return *this;};
        MatrixColumnIterator operator++(int) {Matrix::MatrixColumnIterator temp = *this; index++; return temp;};
        reference operator*() const;
        pointer operator->();
        int getIndex();
        friend bool operator== (const MatrixColumnIterator& lhs, const MatrixColumnIterator& rhs) {return lhs.index == rhs.index;};
        friend bool operator!= (const MatrixColumnIterator& lhs, const MatrixColumnIterator& rhs) {return lhs.index != rhs.index;};
    };

    typedef MatrixRowIterator rowIterator;
    typedef MatrixColumnIterator columnIterator;
    typedef MatrixRowIterator const_rowIterator;
    typedef MatrixColumnIterator const_columnIterator;

    Matrix(int row, int col);
    Matrix(Matrix&& other) noexcept; //Move constructor
    Matrix(Matrix& other); //Copy constructor
    ~Matrix();
    int refCount();
    rowIterator eraseRow(rowIterator rowIter);
    columnIterator eraseColumn(columnIterator columnIter);
    void swap(Matrix& other);
    void insertRow(std::vector<T*> row, int newRowIndex);
    void insertColumn(std::vector<T*> column, int newColIndex);
    int getColumnCount();
    int getRowCount();
    T& at(int row, int column);
    T& ptrAt(int row, int column);

    rowIterator beginRow();
    rowIterator endRow();
    const_rowIterator beginConstRow();
    const_rowIterator endConstRow();

    columnIterator beginColumn();
    columnIterator endColumn();
    const_columnIterator beginConstColumn();
    const_columnIterator endConstColumn();
};


#endif //MATRIX_MATRIX_H
