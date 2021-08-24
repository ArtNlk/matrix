#include "MatrixImpl.h"

template<typename T>
MatrixImpl<T>::MatrixImpl(int _row, int _col) :
    row(_row),
    col(_col),
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
    row(other.row),
    col(other.col),
    refCount(1),
    dataAllocated(other.dataAllocated),
    shareable(true),
    data(nullptr)
{
    T* tempData = new T[row*col];
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
    row(other.row),
    col(other.col),
    refCount(1),
    dataAllocated(row*col),
    shareable(true),
    data(other.data)
{
    other.data = nullptr;
}

template<typename T>
MatrixImpl<T>::~MatrixImpl() {
    delete[] data;
}

template<typename T>
void MatrixImpl<T>::addRef() {
    refCount++;
}

template<typename T>
void MatrixImpl<T>::removeRef() {
    refCount--;
}

template<typename T>
int MatrixImpl<T>::getRefCount() {
    return refCount;
}

template<typename T>
void MatrixImpl<T>::markUnshareable() {
    shareable = false;
}

template<typename T>
void MatrixImpl<T>::markShareable() {
    shareable = true;
}

template<typename T>
bool MatrixImpl<T>::isShareable() {
    return shareable;
}
