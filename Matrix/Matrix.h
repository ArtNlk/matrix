#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H_H

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
    protected:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = std::vector<T>;
        using pointer           = std::vector<T*>;  // or also value_type*
        using reference         = std::vector<std::reference_wrapper<T>>;  // or also value_type&
        int index;
        Matrix<T>* matrix;

    public:
        MatrixRowIterator(int _index, Matrix<T> *_impl): index(_index), matrix(_impl){};
        ~MatrixRowIterator() = default;

        MatrixRowIterator& operator++() {index++; return *this;};
        MatrixRowIterator operator++(int) {Matrix::MatrixRowIterator temp = *this; index++; return temp;};
        reference operator*() const;
        pointer operator->();
        int getIndex();
        friend bool operator== (const MatrixRowIterator& lhs, const MatrixRowIterator& rhs) {return lhs.index == rhs.index;};
        friend bool operator!= (const MatrixRowIterator& lhs, const MatrixRowIterator& rhs) {return lhs.index != rhs.index;};
    };

    class ConstMatrixRowIterator{
    protected:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = std::vector<T>;
        using pointer           = std::vector<const T*>;  // or also value_type*
        using reference         = std::vector<std::reference_wrapper<const T>>;  // or also value_type&
        int index;
        Matrix<T>* matrix;

    public:
        ConstMatrixRowIterator(int _index, Matrix<T> *_impl): index(_index), matrix(_impl){};
        ~ConstMatrixRowIterator() = default;

        ConstMatrixRowIterator& operator++() {index++; return *this;};
        ConstMatrixRowIterator operator++(int) {Matrix::ConstMatrixRowIterator temp = *this; index++; return temp;};
        reference operator*() const;
        pointer operator->();
        int getIndex() {return index;};
        friend bool operator== (const ConstMatrixRowIterator& lhs, const ConstMatrixRowIterator& rhs) {return lhs.index == rhs.index;};
        friend bool operator!= (const ConstMatrixRowIterator& lhs, const ConstMatrixRowIterator& rhs) {return lhs.index != rhs.index;};
    };

    ///@brief Iterates over columns of the matrix
    class MatrixColumnIterator{
    protected:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = std::vector<T>;
        using pointer           = std::vector<T*>;  // or also value_type*
        using reference         = std::vector<std::reference_wrapper<T>>;  // or also value_type&
        int index;
        Matrix<T>* matrix;

    public:
        MatrixColumnIterator(int _index, Matrix<T>* _impl): index(_index), matrix(_impl){};
        ~MatrixColumnIterator() = default;

        MatrixColumnIterator& operator++() {index++; return *this;};
        MatrixColumnIterator operator++(int) {Matrix::MatrixColumnIterator temp = *this; index++; return temp;};
        reference operator*() const;
        pointer operator->();
        int getIndex();
        friend bool operator== (const MatrixColumnIterator& lhs, const MatrixColumnIterator& rhs) {return lhs.index == rhs.index;};
        friend bool operator!= (const MatrixColumnIterator& lhs, const MatrixColumnIterator& rhs) {return lhs.index != rhs.index;};
    };

    class ConstMatrixColumnIterator{
    protected:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = std::vector<T>;
        using pointer           = std::vector<const T*>;  // or also value_type*
        using reference         = std::vector<std::reference_wrapper<const T>>;  // or also value_type&
        int index;
        Matrix<T>* matrix;

    public:
        ConstMatrixColumnIterator(int _index, Matrix<T>* _impl): index(_index), matrix(_impl){};
        ~ConstMatrixColumnIterator() = default;

        ConstMatrixColumnIterator& operator++() {index++; return *this;};
        ConstMatrixColumnIterator operator++(int) {Matrix::ConstMatrixColumnIterator temp = *this; index++; return temp;};
        reference operator*() const;
        pointer operator->();
        int getIndex() {return index;};
        friend bool operator== (const ConstMatrixColumnIterator& lhs, const ConstMatrixColumnIterator& rhs) {return lhs.index == rhs.index;};
        friend bool operator!= (const ConstMatrixColumnIterator& lhs, const ConstMatrixColumnIterator& rhs) {return lhs.index != rhs.index;};
    };

    typedef MatrixRowIterator rowIterator;
    typedef MatrixColumnIterator columnIterator;
    typedef ConstMatrixRowIterator const_rowIterator;
    typedef ConstMatrixColumnIterator const_columnIterator;

    Matrix<T>(int row, int col);
    Matrix<T>(Matrix&& other) noexcept; //Move constructor
    Matrix<T>(Matrix& other); //Copy constructor
    ~Matrix();
    int refCount();
    rowIterator eraseRow(rowIterator rowIter);
    columnIterator eraseColumn(columnIterator columnIter);
    void swap(Matrix& other);
    void insertRow(std::vector<T*> row, int newRowIndex);
    void insertColumn(std::vector<T*> column, int newColIndex);
    void insertRow(std::vector<T> row, int newRowIndex);
    void insertColumn(std::vector<T> column, int newColIndex);
    int getColumnCount();
    int getRowCount();
    T& at(int row, int column);
    T * ptrAt(int row, int column);

    Matrix<T>& operator=(Matrix<T> &&other) noexcept;
    Matrix<T>& operator=(Matrix<T> const &other);

    rowIterator beginRow();
    rowIterator endRow();
    const_rowIterator beginConstRow();
    const_rowIterator endConstRow();

    columnIterator beginColumn();
    columnIterator endColumn();
    const_columnIterator beginConstColumn();
    const_columnIterator endConstColumn();
};

template<typename T>
typename Matrix<T>::MatrixRowIterator::reference Matrix<T>::MatrixRowIterator::operator*() const {
    reference temp;
    int colCount = matrix->getColumnCount();
    for (int i = 0; i < colCount; i++)
    {
        temp.push_back(std::ref(matrix->at(index,i)));
    }

    return temp;
}

template<typename T>
typename Matrix<T>::MatrixRowIterator::pointer Matrix<T>::MatrixRowIterator::operator->() {
    pointer temp;
    int colCount = matrix->getColumnCount();
    for (int i = 0; i < colCount; i++)
    {
        temp.push_back(matrix->ptrAt(index,i));
    }

    return temp;
}

template<typename T>
int Matrix<T>::MatrixRowIterator::getIndex() {
    return index;
}

template<typename T>
typename Matrix<T>::ConstMatrixRowIterator::reference Matrix<T>::ConstMatrixRowIterator::operator*() const {
    reference temp;
    int colCount = this->matrix->getColumnCount();
    for (int i = 0; i < colCount; i++)
    {
        temp.push_back(std::cref(this->matrix->at(this->index,i)));
    }

    return temp;
}

template<typename T>
typename Matrix<T>::ConstMatrixRowIterator::pointer Matrix<T>::ConstMatrixRowIterator::operator->() {
    pointer temp;
    int colCount = this->matrix->getColumnCount();
    for (int i = 0; i < colCount; i++)
    {
        temp.push_back(this->matrix->ptrAt(this->index,i));
    }

    return temp;
}

template<typename T>
typename Matrix<T>::MatrixColumnIterator::reference Matrix<T>::MatrixColumnIterator::operator*() const {
    reference temp;
    int colCount = matrix->getColumnCount();
    for (int i = 0; i < colCount; i++)
    {
        temp.push_back(std::ref(matrix->at(i,index)));
    }

    return temp;
}

template<typename T>
typename Matrix<T>::MatrixColumnIterator::pointer Matrix<T>::MatrixColumnIterator::operator->() {
    pointer temp;
    int colCount = matrix->getColumnCount();
    for (int i = 0; i < colCount; i++)
    {
        temp.push_back(matrix->ptrAt(i,index));
    }

    return temp;
}

template<typename T>
int Matrix<T>::MatrixColumnIterator::getIndex() {
    return index;
}

template<typename T>
typename Matrix<T>::ConstMatrixColumnIterator::reference Matrix<T>::ConstMatrixColumnIterator::operator*() const {
    reference temp;
    int colCount = this->matrix->getColumnCount();
    for (int i = 0; i < colCount; i++)
    {
        temp.push_back(std::cref(this->matrix->at(i,this->index)));
    }

    return temp;
}

template<typename T>
typename Matrix<T>::ConstMatrixColumnIterator::pointer Matrix<T>::ConstMatrixColumnIterator::operator->() {
    pointer temp;
    int colCount = this->matrix->getColumnCount();
    for (int i = 0; i < colCount; i++)
    {
        temp.push_back(this->matrix->ptrAt(i,this->index));
    }

    return temp;
}

template<typename T>
Matrix<T>::Matrix(int row, int col) {
    this->impl = new MatrixImpl<T>(row,col);
}

template<typename T>
Matrix<T>::Matrix(Matrix &&other) noexcept {
    this->impl = other.impl;
    other.impl = new MatrixImpl<T>(other.getRowCount(), other.getColumnCount());
}

template<typename T>
Matrix<T>::Matrix(Matrix &other) {
    this->impl = other.impl;
    impl->addRef();
}

template<typename T>
Matrix<T>::~Matrix() {
    if(impl->getRefCount() == 1)
    {
        delete this->impl;
    }
    else
    {
        impl->removeRef();
    }
}

///@brief Gets current matrix data reference count
///@retval Current matrix data reference count
template<typename T>
int Matrix<T>::refCount() {
    return impl->getRefCount();
}

///@brief Erases matrix row by iterator
///@param rowIter Iterator that points to removed row
///@retval Iterator pointing to next row or endRow()
template<typename T>
typename Matrix<T>::rowIterator Matrix<T>::eraseRow(Matrix::rowIterator rowIter) {
    MatrixImpl<T>* temp = new MatrixImpl<T>(impl->getRowCount() - 1, impl->getColumnCount());

    int offset = 0;
    try {
        for (auto iter = this->beginRow(); iter != this->endRow(); iter++) {
            if (iter == rowIter) {
                offset = -1;
                continue;
            } else {
                temp->setRowDirect(iter.getIndex() + offset,iter.operator*());
            }
        }
    } catch(...)
    {
        delete temp;
        throw;
    }

    if(impl->getRefCount() == 1)
    {
        delete impl;
    }
    else
    {
        impl->removeRef();
    }
    impl = temp;

    return rowIter;
}

///@brief Erases matrix column by iterator
///@param columnIter Iterator that points to removed column
///@retval Iterator pointing to next column or endColumn()
template<typename T>
typename Matrix<T>::columnIterator Matrix<T>::eraseColumn(Matrix::columnIterator columnIter) {
    MatrixImpl<T>* temp = new MatrixImpl<T>(impl->getRowCount(), impl->getColumnCount() - 1);

    int offset = 0;
    try {
        for (auto iter = this->beginColumn(); iter != this->endColumn(); iter++) {
            if (iter == columnIter) {
                offset = -1;
                continue;
            } else {
                temp->setColumnDirect(iter.getIndex() + offset,iter.operator->());
            }
        }
    } catch(...)
    {
        delete temp;
        throw;
    }

    if(impl->getRefCount() == 1)
    {
        delete impl;
    }
    else
    {
        impl->removeRef();
    }
    impl = temp;

    return columnIter;
}

///@brief Swaps matrix data with other matrix instance
///@param other Matrix to swap data with
template<typename T>
void Matrix<T>::swap(Matrix &other) {
    MatrixImpl<T>* temp = other.impl;
    other.impl = this->impl;
    this->impl = temp;
}

///@brief Inserts row at specified index
///@param row Vector holding pointers to inserted elements
///@param newRowIndex Index at which new row will be inserted
template<typename T>
void Matrix<T>::insertRow(std::vector<T*> row, int newRowIndex) {
    MatrixImpl<T>* temp = new MatrixImpl<T>(impl->getRowCount() + 1, impl->getColumnCount());

    int offset = 0;

    for(int rowIndex = 0; rowIndex<temp->getRowCount(); rowIndex++)
    {
        if(rowIndex == newRowIndex)
        {
            for(int colIndex = 0; colIndex<temp->getColumnCount(); colIndex++)
            {
                temp->at(rowIndex,colIndex) = *row.at(colIndex);
                offset = -1; //Before row insertion impl is sampled at same row index, after insertion - one lower, since a new row has been inserted
            }
        } else{
            for(int colIndex = 0; colIndex<temp->getColumnCount(); colIndex++)
            {
                temp->at(rowIndex,colIndex) = impl->at(rowIndex+offset,colIndex);
            }
        }
    }

    if(impl->getRefCount() == 1)
    {
        delete impl;
    }
    else
    {
        impl->removeRef();
    }
    impl = temp;
}

///@brief Inserts row at specified index
///@param row Vector holding instances of inserted elements
///@param newRowIndex Index at which new row will be inserted
template<typename T>
void Matrix<T>::insertRow(std::vector<T> row, int newRowIndex) {
    MatrixImpl<T>* temp = new MatrixImpl<T>(impl->getRowCount() + 1, impl->getColumnCount());

    int offset = 0;

    for(int rowIndex = 0; rowIndex<temp->getRowCount(); rowIndex++)
    {
        if(rowIndex == newRowIndex)
        {
            for(int colIndex = 0; colIndex<temp->getColumnCount(); colIndex++)
            {
                temp->at(rowIndex,colIndex) = row.at(colIndex);
                offset = -1; //Before row insertion impl is sampled at same row index, after insertion - one lower, since a new row has been inserted
            }
        } else{
            for(int colIndex = 0; colIndex<temp->getColumnCount(); colIndex++)
            {
                temp->at(rowIndex,colIndex) = impl->at(rowIndex+offset,colIndex);
            }
        }
    }

    if(impl->getRefCount() == 1)
    {
        delete impl;
    }
    impl = temp;
}

///@brief Inserts column at specified index
///@param column Vector holding pointers to inserted elements
///@param newColIndex Index at which new column will be inserted
template<typename T>
void Matrix<T>::insertColumn(std::vector<T *> column, int newColIndex) {
    MatrixImpl<T>* temp = new MatrixImpl<T>(impl->getRowCount(), impl->getColumnCount() + 1);

    int offset = 0;

    for(int colIndex = 0; colIndex<temp->getColumnCount(); colIndex++)
    {
        if(colIndex == newColIndex)
        {
            for(int rowIndex = 0; rowIndex<temp->getRowCount(); rowIndex++)
            {
                temp->at(rowIndex,colIndex) = *column.at(rowIndex);
                offset = -1; //Before row insertion impl is sampled at same row index, after insertion - one lower, since a new row has been inserted
            }
        } else{
            for(int rowIndex = 0; rowIndex<temp->getRowCount(); rowIndex++)
            {
                temp->at(rowIndex,colIndex) = impl->at(rowIndex,colIndex+offset);
            }
        }
    }

    if(impl->getRefCount() == 1)
    {
        delete impl;
    }
    impl = temp;
}


///@brief Inserts column at specified index
///@param column Vector holding instances of inserted elements
///@param newColIndex Index at which new column will be inserted
template<typename T>
void Matrix<T>::insertColumn(std::vector<T> column, int newColIndex) {
    MatrixImpl<T>* temp = new MatrixImpl<T>(impl->getRowCount(), impl->getColumnCount() + 1);

    int offset = 0;

    for(int colIndex = 0; colIndex<temp->getColumnCount(); colIndex++)
    {
        if(colIndex == newColIndex)
        {
            for(int rowIndex = 0; rowIndex<temp->getRowCount(); rowIndex++)
            {
                temp->at(rowIndex,colIndex) = column.at(rowIndex);
                offset = -1; //Before row insertion impl is sampled at same row index, after insertion - one lower, since a new row has been inserted
            }
        } else{
            for(int rowIndex = 0; rowIndex<temp->getRowCount(); rowIndex++)
            {
                temp->at(rowIndex,colIndex) = impl->at(rowIndex,colIndex+offset);
            }
        }
    }

    if(impl->getRefCount() == 1)
    {
        delete impl;
    }
    impl = temp;
}
///@brief Gets matrix column count
///@retval Matrix column count
template<typename T>
int Matrix<T>::getColumnCount() {
    return impl->getColumnCount();
}

///@brief Gets matrix row count
///@retval Matrix row count
template<typename T>
int Matrix<T>::getRowCount() {
    return impl->getRowCount();
}

///@brief Returns reference to object at specified row and column coordinates
///@param row Zero-base row index
///@param column Zero-base column index
///@retval Reference to object at specified coordinates
template<typename T>
T &Matrix<T>::at(int row, int column) {
    if(row >= this->getRowCount() || column >= this->getColumnCount())
    {
        throw std::out_of_range("Matrix::at - index out of range");
    }
    MatrixImpl<T>* temp;
    if(impl->getRefCount() != 1)
    {
        temp = new MatrixImpl<T>(*impl);
        impl->removeRef();
        impl = temp;
    }
    return impl->at(row,column);
}

///@brief Returns pointer to object at specified row and column coordinates
///@param row Zero-base row index
///@param column Zero-base column index
///@retval Pointer to object at specified coordinates
template<typename T>
T * Matrix<T>::ptrAt(int row, int column) {
    MatrixImpl<T>* temp;
    if(impl->getRefCount() != 1)
    {
        temp = new MatrixImpl<T>(*impl);
        impl->removeRef();
        impl = temp;
    }
    return impl->ptrAt(row,column);;
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> &&other) noexcept {
    if(impl->getRefCount() == 1)
    {
        delete impl;
    } else{
        impl->removeRef();
    }
    this->impl = other.impl;
    return *this;
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> const &other) {
    other.impl->addRef();
    if(impl->getRefCount() == 1)
    {
        delete impl;
    }else{
        impl->removeRef();
    }
    impl = other.impl;

    return *this;
}

///@brief Returns iterator pointing to top matrix row
template<typename T>
typename Matrix<T>::rowIterator Matrix<T>::beginRow() {
    return Matrix<T>::rowIterator(0, this);
}

///@brief Returns iterator pointing past bottom matrix row
template<typename T>
typename Matrix<T>::rowIterator Matrix<T>::endRow() {
    return Matrix::rowIterator(this->getRowCount(), this);
}

///@brief Returns constant iterator pointing to top matrix row
template<typename T>
typename Matrix<T>::const_rowIterator Matrix<T>::beginConstRow() {
    return Matrix::const_rowIterator(0, this);
}

///@brief Returns constant iterator pointing past bottom matrix row
template<typename T>
typename Matrix<T>::const_rowIterator Matrix<T>::endConstRow() {
    return Matrix::const_rowIterator(this->getRowCount(), this);
}

///@brief Returns iterator pointing to leftmost matrix column
template<typename T>
typename Matrix<T>::columnIterator Matrix<T>::beginColumn() {
    return Matrix<T>::columnIterator(0, this);
}

///@brief Returns iterator pointing past rightmost matrix column
template<typename T>
typename Matrix<T>::columnIterator Matrix<T>::endColumn() {
    return Matrix::columnIterator(this->getColumnCount(), this);
}

///@brief Returns constant iterator pointing to leftmost matrix column
template<typename T>
typename Matrix<T>::const_columnIterator Matrix<T>::beginConstColumn() {
    return Matrix::const_columnIterator(0, this);
}

///@brief Returns constant iterator pointing past rightmost matrix column
template<typename T>
typename Matrix<T>::const_columnIterator Matrix<T>::endConstColumn() {
    return Matrix::const_columnIterator(this->getColumnCount(), this);
}

#endif //MATRIX_MATRIX_H
