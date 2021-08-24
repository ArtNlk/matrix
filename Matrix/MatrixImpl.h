#ifndef MATRIX_MATRIXIMPL_H
#define MATRIX_MATRIXIMPL_H

#include <cstdlib>
#include <iterator> //std::forward_iterator_tag
#include <cstddef>  //std::ptrdiff_t

template <typename T>
class MatrixImpl {
private:
    int dataAllocated;
    int refCount;
    int row;
    int col;
    bool shareable;
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

    void reserve(int row, int col);
};

#endif //MATRIX_MATRIXIMPL_H
