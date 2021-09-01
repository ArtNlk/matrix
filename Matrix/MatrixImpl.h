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

#endif //MATRIX_MATRIXIMPL_H
