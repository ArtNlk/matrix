#include "MatrixImpl.h"

template<typename T>
MatrixImpl<T>::MatrixImpl(int _row, int _col) :
    rowCount(_row),
    colCount(_col),
    refCount(1),
    dataAllocated(_row*_col),
    shareable(true),
    data(nullptr)
{
    data = new T[dataAllocated];
}

//Copy constructor
template<typename T>
MatrixImpl<T>::MatrixImpl(MatrixImpl &other) :
    rowCount(other.rowCount),
    colCount(other.colCount),
    refCount(1),
    dataAllocated(other.dataAllocated),
    shareable(true),
    data(nullptr)
{
    T* tempData = new T[rowCount * colCount];
    try
    {
        std::copy( other.data, other.data + dataAllocated, tempData);
    }
    catch(...)
    {
        delete[] data;
        throw;
    }
}

//Move constructor
template<typename T>
MatrixImpl<T>::MatrixImpl(MatrixImpl &&other) noexcept :
    rowCount(other.rowCount),
    colCount(other.colCount),
    refCount(1),
    dataAllocated(rowCount * colCount),
    shareable(true),
    data(other.data)
{
    other.data = nullptr;
}

template<typename T>
MatrixImpl<T>::~MatrixImpl() {
    delete[] data;
}

///@brief Increments current reference counter
template<typename T>
void MatrixImpl<T>::addRef() {
    refCount++;
}

///@brief Decrements current reference counter
template<typename T>
void MatrixImpl<T>::removeRef() {
    refCount--;
}

///@brief Gets current reference count
template<typename T>
int MatrixImpl<T>::getRefCount() {
    return refCount;
}

///@brief Marks this matrixImpl unshareable
template<typename T>
void MatrixImpl<T>::markUnshareable() {
    shareable = false;
}

///@brief Marks this matrixImpl shareable
template<typename T>
void MatrixImpl<T>::markShareable() {
    shareable = true;
}

///@brief Is matrixImpl shareable?
template<typename T>
bool MatrixImpl<T>::isShareable() {
    return shareable;
}

///@brief Gets row count
template<typename T>
int MatrixImpl<T>::getRowCount() {
    return rowCount;
}

///@brief Gets column count
template<typename T>
int MatrixImpl<T>::getColumnCount() {
    return colCount;
}

///@brief Gets a reference to element at specified row and column
///@note Indexes row and col are zero-based
///@param row Zero-based row index
///@param col Zero-based column index
template<typename T>
T& MatrixImpl<T>::at(int row, int col) {
    if(row >= rowCount || col >= colCount)
    {
        throw std::out_of_range("Matrix::at - index out of range");
    }
    return data[colCount * row + col];
}

template<typename T>
T *MatrixImpl<T>::ptrAt(int row, int col) {
    if (row >= rowCount || col >= colCount) {
        throw std::out_of_range("Matrix::ptrAt - index out of range");
    }
    return &data[colCount * row + col];
}

template<typename T>
void MatrixImpl<T>::setRow(int newRowIndex, std::vector<T *> row) {
    if(row.size() != this->colCount)
    {
        throw std::out_of_range("MatrixImpl::setRow row vector does not match internal row size");
    }

    if(newRowIndex >= this->rowCount || newRowIndex < 0)
    {
        throw std::out_of_range("MatrixImpl::setRow column index out of range");
    }

    T* temp = new T[this->rowCount * this->colCount];

    try
    {
        for(int rowIndex = 0; rowIndex < rowCount; rowIndex++)
        {
            if(rowIndex == newRowIndex)
            {
                for (int colIndex = 0; colIndex < colCount; colIndex++) {
                    temp[colCount * rowIndex + colIndex] = *row.at(colIndex);
                }
            }
            else
            {
                for (int colIndex = 0; colIndex < colCount; colIndex++) {
                    temp[colCount * rowIndex + colIndex] = this->at(rowIndex,colIndex);
                }
            }
        }
    }
    catch (...)
    {
        delete[] temp;
        throw;
    }

    delete[] this->data;
    this->data = temp;
}

template<typename T>
void MatrixImpl<T>::setRow(int newRowIndex, std::vector<std::reference_wrapper<T>> row) {
    if(row.size() != this->colCount)
    {
        throw std::out_of_range("MatrixImpl::setRow row vector does not match internal row size");
    }

    if(newRowIndex >= this->rowCount || newRowIndex < 0)
    {
        throw std::out_of_range("MatrixImpl::setRow column index out of range");
    }

    T* temp = new T[this->rowCount * this->colCount];

    try
    {
        for(int rowIndex = 0; rowIndex < rowCount; rowIndex++)
        {
            if(rowIndex == newRowIndex)
            {
                for (int colIndex = 0; colIndex < colCount; colIndex++) {
                    temp[colCount * rowIndex + colIndex] = row.at(colIndex);
                }
            }
            else
            {
                for (int colIndex = 0; colIndex < colCount; colIndex++) {
                    temp[colCount * rowIndex + colIndex] = this->at(rowIndex,colIndex);
                }
            }
        }
    }
    catch (...)
    {
        delete[] temp;
        throw;
    }

    delete[] this->data;
    this->data = temp;
}

template<typename T>
void MatrixImpl<T>::setColumn(int newColumnIndex, std::vector<T *> column) {
    if(column.size() != this->rowCount)
    {
        throw std::out_of_range("MatrixImpl::setColumn column vector does not match internal column size");
    }

    if(newColumnIndex >= this->colCount || newColumnIndex < 0)
    {
        throw std::out_of_range("MatrixImpl::setColumn column index out of range");
    }

    T* temp = new T[this->rowCount * this->colCount];

    try
    {
        for(int columnIndex = 0; columnIndex < rowCount; columnIndex++)
        {
            if(columnIndex == newColumnIndex)
            {
                for (int rowIndex = 0; rowIndex < colCount; rowIndex++) {
                    temp[colCount * rowIndex + columnIndex] = *column.at(rowIndex);
                }
            }
            else
            {
                for (int rowIndex = 0; rowIndex < colCount; rowIndex++) {
                    temp[colCount * rowIndex + columnIndex] = this->at(rowIndex,columnIndex);
                }
            }
        }
    }
    catch (...)
    {
        delete[] temp;
        throw;
    }

    delete[] this->data;
    this->data = temp;
}

template<typename T>
void MatrixImpl<T>::setColumn(int newColumnIndex, std::vector<std::reference_wrapper<T>> column) {
    if(column.size() != this->rowCount)
    {
        throw std::out_of_range("MatrixImpl::setColumn column vector does not match internal column size");
    }

    if(newColumnIndex >= this->colCount || newColumnIndex < 0)
    {
        throw std::out_of_range("MatrixImpl::setColumn column index out of range");
    }

    T* temp = new T[this->rowCount * this->colCount];

    try
    {
        for(int columnIndex = 0; columnIndex < rowCount; columnIndex++)
        {
            if(columnIndex == newColumnIndex)
            {
                for (int rowIndex = 0; rowIndex < colCount; rowIndex++) {
                    temp[colCount * rowIndex + columnIndex] = column.at(rowIndex);
                }
            }
            else
            {
                for (int rowIndex = 0; rowIndex < colCount; rowIndex++) {
                    temp[colCount * rowIndex + columnIndex] = this->at(rowIndex,columnIndex);
                }
            }
        }
    }
    catch (...)
    {
        delete[] temp;
        throw;
    }

    delete[] this->data;
    this->data = temp;
}

template<typename T>
void MatrixImpl<T>::setRowDirect(int newRowIndex, std::vector<T *> row) {
    if(row.size() != this->colCount)
    {
        throw std::out_of_range("MatrixImpl::setRowDirect row vector size > ");
    }

    if(newRowIndex > this->rowCount || newRowIndex < 0)
    {
        throw std::out_of_range("MatrixImpl::setRowDirect row index out of range");
    }

    for (int columnIndex = 0; columnIndex < colCount; columnIndex++) {
        this->data[colCount * newRowIndex + columnIndex] = *row.at(columnIndex);
    }
}

template<typename T>
void MatrixImpl<T>::setRowDirect(int newRowIndex, std::vector<std::reference_wrapper<T>> row) {
    if(row.size() != this->colCount)
    {
        throw std::out_of_range("MatrixImpl::setRowDirect row vector size > ");
    }

    if(newRowIndex > this->rowCount || newRowIndex < 0)
    {
        throw std::out_of_range("MatrixImpl::setRowDirect row index out of range");
    }

    for (int columnIndex = 0; columnIndex < colCount; columnIndex++) {
        this->data[colCount * newRowIndex + columnIndex] = row.at(columnIndex);
    }
}

template<typename T>
void MatrixImpl<T>::setColumnDirect(int newColumnIndex, std::vector<T *> column) {
    if(column.size() != this->colCount)
    {
        throw std::out_of_range("MatrixImpl::setRowDirect row vector size > ");
    }

    if(newColumnIndex > this->rowCount || newColumnIndex < 0)
    {
        throw std::out_of_range("MatrixImpl::setRowDirect row index out of range");
    }

    for (int rowIndex = 0; rowIndex < colCount; rowIndex++) {
        this->data[colCount * rowIndex + newColumnIndex] = *column.at(rowIndex);
    }
}

template<typename T>
void MatrixImpl<T>::setColumnDirect(int newColumnIndex, std::vector<std::reference_wrapper<T>> column) {
    if(column.size() != this->colCount)
    {
        throw std::out_of_range("MatrixImpl::setRowDirect row vector size > ");
    }

    if(newColumnIndex > this->rowCount || newColumnIndex < 0)
    {
        throw std::out_of_range("MatrixImpl::setRowDirect row index out of range");
    }

    for (int rowIndex = 0; rowIndex < colCount; rowIndex++) {
        this->data[colCount * rowIndex + newColumnIndex] = column.at(rowIndex);
    }
}
