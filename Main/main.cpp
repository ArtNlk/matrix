#include <MatrixImpl.h>

int main()
{
    MatrixIterator<int> itr1(nullptr);
    MatrixIterator<int> itr2(nullptr);

    bool res = itr1 == itr2;
}