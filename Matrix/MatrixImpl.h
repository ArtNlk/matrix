#ifndef MATRIX_MATRIXIMPL_H
#define MATRIX_MATRIXIMPL_H

#include <cstdlib>
#include <iterator> //std::forward_iterator_tag
#include <cstddef>  //std::ptrdiff_t
#include <functional>

template <typename T>
class MatrixImpl {
private:
    int dataAllocated;
    int refCount;
    int rowCount;
    int colCount;
    T* data;

public:
    MatrixImpl(int _row, int _col);
    MatrixImpl(MatrixImpl& other); //Copy constructor
    MatrixImpl(MatrixImpl&& other) noexcept; //Move constructor
    ~MatrixImpl();
    void addRef();
    void removeRef();
    int getRefCount();
    void markUnshareable();
    void markShareable();
    bool isShareable();
    int getRowCount();
    int getColumnCount();
    T& at(int row, int col);
    T* ptrAt(int row, int col);
    void setRow(int newRowIndex, std::vector<T*> row);
    void setRow(int newRowIndex, std::vector<std::reference_wrapper<T>> row);
    void setColumn(int newColumnIndex, std::vector<T*> column);
    void setColumn(int newColumnIndex, std::vector<std::reference_wrapper<T>> column);
    void setRowDirect(int newRowIndex, std::vector<T*> row);
    void setRowDirect(int newRowIndex, std::vector<std::reference_wrapper<T>> row);
    void setColumnDirect(int newColumnIndex, std::vector<T*> column);
    void setColumnDirect(int newColumnIndex, std::vector<std::reference_wrapper<T>> column);

    friend bool operator==(MatrixImpl &lhs, MatrixImpl &rhs) {return lhs.data == rhs.data;};

    void reserve(int row, int col);
};

#include "MatrixImpl.h"

template<typename T>
MatrixImpl<T>::MatrixImpl(int _row, int _col) :
        dataAllocated(_row*_col),
        refCount(1),
        rowCount(_row),
        colCount(_col),
        data(nullptr)
{
    data = new T[dataAllocated];
}

//Copy constructor
template<typename T>
MatrixImpl<T>::MatrixImpl(MatrixImpl &other) :
        dataAllocated(other.dataAllocated),
        refCount(1),
        rowCount(other.rowCount),
        colCount(other.colCount),
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
    data = tempData;
}

//Move constructor
template<typename T>
MatrixImpl<T>::MatrixImpl(MatrixImpl &&other) noexcept :
        dataAllocated(rowCount * colCount),
        refCount(1),
        rowCount(other.rowCount),
        colCount(other.colCount),
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

///@brief Gets a pointer to element at specified row and column
///@note Indexes row and col are zero-based
///@param row Zero-based row index
///@param col Zero-based column index
template<typename T>
T *MatrixImpl<T>::ptrAt(int row, int col) {
    if (row >= rowCount || col >= colCount) {
        throw std::out_of_range("Matrix::ptrAt - index out of range");
    }
    return &data[colCount * row + col];
}

///@brief Sets row at specified index with objects from row
///@param newRowIndex Index at which row will be set
///@param row Vector holding pointers to objects that will be set to matrix row
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

///@brief Sets row at specified index with objects from row
///@param newRowIndex Index at which row will be set
///@param row Vector holding references to objects that will be set to matrix row
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

///@brief Sets column at specified index with objects from column
///@param newColumnIndex Index at which column will be set
///@param column Vector holding pointers to objects that will be set to matrix column
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

///@brief Sets column at specified index with objects from column
///@param newColumnIndex Index at which column will be set
///@param column Vector holding references to objects that will be set to matrix column
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

///@brief Sets row at specified index with objects from row directly
///@warning This method is not strong exception-safe and should only be used on temporary objects
///@param newRowIndex Index at which row will be set
///@param row Vector holding references to objects that will be set to matrix row
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

///@brief Sets row at specified index with objects from row directly
///@warning This method is not strong exception-safe and should only be used on temporary objects
///@param newRowIndex Index at which row will be set
///@param row Vector holding pointers to objects that will be set to matrix row
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

///@brief Sets column at specified index with objects from column directly
///@warning This method is not strong exception-safe and should only be used on temporary objects
///@param newColumnIndex Index at which column will be set
///@param column Vector holding pointers to objects that will be set to matrix column
template<typename T>
void MatrixImpl<T>::setColumnDirect(int newColumnIndex, std::vector<T *> column) {
    if(column.size() != this->rowCount)
    {
        throw std::out_of_range("MatrixImpl::setColumnDirect row vector size > ");
    }

    if(newColumnIndex > this->rowCount || newColumnIndex < 0)
    {
        throw std::out_of_range("MatrixImpl::setColumnDirect row index out of range");
    }

    for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
        this->data[colCount * rowIndex + newColumnIndex] = *column.at(rowIndex);
    }
}
///@brief Sets column at specified index with objects from column directly
///@warning This method is not strong exception-safe and should only be used on temporary objects
///@param newColumnIndex Index at which column will be set
///@param column Vector holding references to objects that will be set to matrix column
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


#endif //MATRIX_MATRIXIMPL_H