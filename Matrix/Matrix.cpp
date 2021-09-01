#include "Matrix.h"

template<typename T>
typename Matrix<T>::MatrixRowIterator::reference Matrix<T>::MatrixRowIterator::operator*() const {
    reference temp;
    int colCount = matrix.getColumnCount();
    for (int i = 0; i < colCount; i++)
    {
        temp.push_back(std::ref(matrix.at(index, i)));
    }

    return temp;
}

template<typename T>
typename Matrix<T>::MatrixRowIterator::pointer Matrix<T>::MatrixRowIterator::operator->() {
    pointer temp;
    int colCount = matrix.getColumnCount();
    for (int i = 0; i < colCount; i++)
    {
        temp.push_back(matrix.ptrAt(index, i));
    }

    return temp;
}

template<typename T>
int Matrix<T>::MatrixRowIterator::getIndex() {
    return index;
}

template<typename T>
typename Matrix<T>::MatrixColumnIterator::reference Matrix<T>::MatrixColumnIterator::operator*() const {
    reference temp;
    int colCount = matrix.getColumnCount();
    for (int i = 0; i < colCount; i++)
    {
        temp.push_back(std::ref(matrix.at(i, index)));
    }

    return temp;
}

template<typename T>
typename Matrix<T>::MatrixColumnIterator::pointer Matrix<T>::MatrixColumnIterator::operator->() {
    pointer temp;
    int colCount = matrix.getColumnCount();
    for (int i = 0; i < colCount; i++)
    {
        temp.push_back(matrix.ptrAt(i, index));
    }

    return temp;
}

template<typename T>
int Matrix<T>::MatrixColumnIterator::getIndex() {
    return index;
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

template<typename T>
int Matrix<T>::refCount() {
    return impl->getRefCount();
}

template<typename T>
typename Matrix<T>::rowIterator Matrix<T>::eraseRow(Matrix::rowIterator rowIter) {
    MatrixImpl<T>* temp = new MatrixImpl<T>*(impl->getRowCount() - 1, impl->getColumnCount());

    try {
        for (auto iter = this->beginRow(); iter != this->endRow(); iter++) {
            if (iter == rowIter) {
                continue;
            } else {
                temp->setRowDirect(iter);
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
    impl = temp;

    rowIter++;
    return rowIter;
}

template<typename T>
typename Matrix<T>::columnIterator Matrix<T>::eraseColumn(Matrix::columnIterator columnIter) {
    MatrixImpl<T>* temp = new MatrixImpl<T>*(impl->getRowCount(), impl->getColumnCount() - 1);

    try {
        for (auto iter = this->beginColumn(); iter != this->endColumn(); iter++) {
            if (iter == columnIter) {
                continue;
            } else {
                temp->setColumnDirect(iter);
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
    impl = temp;

    columnIter++;
    return columnIter;
}

template<typename T>
void Matrix<T>::swap(Matrix &other) {
    MatrixImpl<T>* temp = other.impl;
    other.impl = this->impl;
    this->impl = temp;
}

template<typename T>
void Matrix<T>::insertRow(std::vector<T *> row, int newRowIndex) {
    MatrixImpl<T>* temp = new MatrixImpl<T>*(impl->getRowCount() + 1, impl->getColumnCount());

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
    impl = temp;
}

template<typename T>
void Matrix<T>::insertColumn(std::vector<T *> column, int newColIndex) {
    MatrixImpl<T>* temp = new MatrixImpl<T>*(impl->getRowCount() + 1, impl->getColumnCount());

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

template<typename T>
int Matrix<T>::getColumnCount() {
    return impl->getColumnCount();
}

template<typename T>
int Matrix<T>::getRowCount() {
    return impl->getRowCount();
}

template<typename T>
T &Matrix<T>::at(int row, int column) {
    MatrixImpl<T>* temp;
        if(impl->getRefCount() != 1)
        {
            temp = new MatrixImpl<T>(impl);
            impl = temp;
        }
    return impl->at(row,column);
}

template<typename T>
T &Matrix<T>::ptrAt(int row, int column) {
    MatrixImpl<T>* temp;
    if(impl->getRefCount() != 1)
    {
        temp = new MatrixImpl<T>(impl);
        impl = temp;
    }
    return impl->ptrAt(row,column);;
}

template<typename T>
typename Matrix<T>::rowIterator Matrix<T>::beginRow() {
    return Matrix<T>::rowIterator(0,*this);
}

template<typename T>
typename Matrix<T>::rowIterator Matrix<T>::endRow() {
    return Matrix::rowIterator(this->getRowCount(), *this);
}

template<typename T>
typename Matrix<T>::const_rowIterator Matrix<T>::beginConstRow() {
    return Matrix::const_rowIterator(0, *this);
}

template<typename T>
typename Matrix<T>::const_rowIterator Matrix<T>::endConstRow() {
    return Matrix::const_rowIterator(this->getRowCount(), *this);
}

template<typename T>
typename Matrix<T>::columnIterator Matrix<T>::beginColumn() {
    return Matrix<T>::columnIterator(0,*this);
}

template<typename T>
typename Matrix<T>::columnIterator Matrix<T>::endColumn() {
    return Matrix::columnIterator(this->getColumnCount(), *this);
}

template<typename T>
typename Matrix<T>::const_columnIterator Matrix<T>::beginConstColumn() {
    return Matrix::const_columnIterator(0, *this);
}

template<typename T>
typename Matrix<T>::const_columnIterator Matrix<T>::endConstColumn() {
    return Matrix::const_columnIterator(this->getColumnCount(), *this);
}




