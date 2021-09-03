#include <Matrix.h>
#include <gtest/gtest.h>
#include <vector>

class MatrixTest : public ::testing::Test {
protected:
    MatrixTest() :
    matrix1x1(1,1),
    matrix3x3(3,3),
    matrixVectors(3,3)
    {

    }

    void SetUp() override {
        matrix1x1.at(0,0) = 1;

        int i = 1;
        for(int row = 0; row < matrix3x3.getColumnCount(); row++) {
            for(int col = 0; col < matrix3x3.getRowCount(); col++)
            {
            matrix3x3.at(row, col) = i;
            matrixVectors.at(row, col).push_back(i);
            i++;
            }
        }
    }
    Matrix<int> matrix1x1;
    Matrix<int> matrix3x3;
    Matrix<std::vector<int>> matrixVectors;
};

TEST_F(MatrixTest,ElementAccess)
{
    EXPECT_EQ(matrix1x1.at(0,0),1);
    EXPECT_EQ(*matrix1x1.ptrAt(0,0),1);
    int i = 1;
    for(int row = 0; row < matrix3x3.getColumnCount(); row++)
    {
        for(int col = 0; col < matrix3x3.getRowCount(); col++)
        {
            EXPECT_EQ(matrix3x3.at(row,col),i);
            EXPECT_EQ(*matrix3x3.ptrAt(row,col),i);
            EXPECT_EQ(matrixVectors.at(row,col).at(0),i);
            EXPECT_EQ(matrixVectors.ptrAt(row,col)->at(0),i);
            i++;
        }
    }
}

TEST_F(MatrixTest, RowIteratorAccessPtr)
{
    Matrix<int>::rowIterator iter =matrix3x3.beginRow();
    EXPECT_EQ(*(iter.operator->().at(0)),1);
    EXPECT_EQ(*(iter.operator->().at(1)),2);
    EXPECT_EQ(*(iter.operator->().at(2)),3);
    *iter.operator->().at(0) = 11;
    *iter.operator->().at(1) = 12;
    *iter.operator->().at(2) = 13;
    EXPECT_EQ(*(iter.operator->().at(0)),11);
    EXPECT_EQ(*(iter.operator->().at(1)),12);
    EXPECT_EQ(*(iter.operator->().at(2)),13);
    iter++;
    EXPECT_EQ(*(iter.operator->().at(0)),4);
    EXPECT_EQ(*(iter.operator->().at(1)),5);
    EXPECT_EQ(*(iter.operator->().at(2)),6);
    iter++;
    EXPECT_EQ(*(iter.operator->().at(0)),7);
    EXPECT_EQ(*(iter.operator->().at(1)),8);
    EXPECT_EQ(*(iter.operator->().at(2)),9);
    iter++;
    EXPECT_EQ(iter,matrix3x3.endRow());
}

TEST_F(MatrixTest, RowIteratorAccessRef)
{
    Matrix<int>::rowIterator iter = matrix3x3.beginRow();
    EXPECT_EQ(iter.operator*().at(0).get(),1);
    EXPECT_EQ(iter.operator*().at(1).get(),2);
    EXPECT_EQ(iter.operator*().at(2).get(),3);
    iter.operator*().at(0).get() = 11;
    iter.operator*().at(1).get() = 12;
    iter.operator*().at(2).get() = 13;
    EXPECT_EQ(iter.operator*().at(0).get(),11);
    EXPECT_EQ(iter.operator*().at(1).get(),12);
    EXPECT_EQ(iter.operator*().at(2).get(),13);
    iter++;
    EXPECT_EQ(iter.operator*().at(0).get(),4);
    EXPECT_EQ(iter.operator*().at(1).get(),5);
    EXPECT_EQ(iter.operator*().at(2).get(),6);
    iter++;
    EXPECT_EQ(iter.operator*().at(0).get(),7);
    EXPECT_EQ(iter.operator*().at(1).get(),8);
    EXPECT_EQ(iter.operator*().at(2).get(),9);
    iter++;
    EXPECT_EQ(iter,matrix3x3.endRow());
}

TEST_F(MatrixTest, RowIteratorAccessConst)
{
    Matrix<int>::const_rowIterator iter = matrix3x3.beginConstRow();
    EXPECT_EQ(iter.operator*().at(0).get(),1);
    EXPECT_EQ(iter.operator*().at(1).get(),2);
    EXPECT_EQ(iter.operator*().at(2).get(),3);
    iter++;
    EXPECT_EQ(iter.operator*().at(0).get(),4);
    EXPECT_EQ(iter.operator*().at(1).get(),5);
    EXPECT_EQ(iter.operator*().at(2).get(),6);
    iter++;
    EXPECT_EQ(iter.operator*().at(0).get(),7);
    EXPECT_EQ(iter.operator*().at(1).get(),8);
    EXPECT_EQ(iter.operator*().at(2).get(),9);
    iter++;
    EXPECT_EQ(iter,matrix3x3.endConstRow());
}

TEST_F(MatrixTest, ColumnIteratorAccessPtr)
{
    Matrix<int>::columnIterator iter =matrix3x3.beginColumn();
    EXPECT_EQ(*(iter.operator->().at(0)),1);
    EXPECT_EQ(*(iter.operator->().at(1)),4);
    EXPECT_EQ(*(iter.operator->().at(2)),7);
    *iter.operator->().at(0) = 11;
    *iter.operator->().at(1) = 12;
    *iter.operator->().at(2) = 13;
    EXPECT_EQ(*(iter.operator->().at(0)),11);
    EXPECT_EQ(*(iter.operator->().at(1)),12);
    EXPECT_EQ(*(iter.operator->().at(2)),13);
    iter++;
    EXPECT_EQ(*(iter.operator->().at(0)),2);
    EXPECT_EQ(*(iter.operator->().at(1)),5);
    EXPECT_EQ(*(iter.operator->().at(2)),8);
    iter++;
    EXPECT_EQ(*(iter.operator->().at(0)),3);
    EXPECT_EQ(*(iter.operator->().at(1)),6);
    EXPECT_EQ(*(iter.operator->().at(2)),9);
    iter++;
    EXPECT_EQ(iter,matrix3x3.endColumn());
}

TEST_F(MatrixTest, ColumnIteratorAccessRef)
{

    Matrix<int>::columnIterator iter = matrix3x3.beginColumn();
    EXPECT_EQ(iter.operator*().at(0).get(),1);
    EXPECT_EQ(iter.operator*().at(1).get(),4);
    EXPECT_EQ(iter.operator*().at(2).get(),7);
    iter.operator*().at(0).get() = 11;
    iter.operator*().at(1).get() = 12;
    iter.operator*().at(2).get() = 13;
    EXPECT_EQ(iter.operator*().at(0).get(),11);
    EXPECT_EQ(iter.operator*().at(1).get(),12);
    EXPECT_EQ(iter.operator*().at(2).get(),13);
    iter++;
    EXPECT_EQ(iter.operator*().at(0).get(),2);
    EXPECT_EQ(iter.operator*().at(1).get(),5);
    EXPECT_EQ(iter.operator*().at(2).get(),8);
    iter++;
    EXPECT_EQ(iter.operator*().at(0).get(),3);
    EXPECT_EQ(iter.operator*().at(1).get(),6);
    EXPECT_EQ(iter.operator*().at(2).get(),9);
    iter++;
    EXPECT_EQ(iter,matrix3x3.endColumn());
}

TEST_F(MatrixTest, ColumnIteratorAccessConst)
{
    Matrix<int>::const_columnIterator iter = matrix3x3.beginConstColumn();
    EXPECT_EQ(iter.operator*().at(0).get(),1);
    EXPECT_EQ(iter.operator*().at(1).get(),4);
    EXPECT_EQ(iter.operator*().at(2).get(),7);
    iter++;
    EXPECT_EQ(iter.operator*().at(0).get(),2);
    EXPECT_EQ(iter.operator*().at(1).get(),5);
    EXPECT_EQ(iter.operator*().at(2).get(),8);
    iter++;
    EXPECT_EQ(iter.operator*().at(0).get(),3);
    EXPECT_EQ(iter.operator*().at(1).get(),6);
    EXPECT_EQ(iter.operator*().at(2).get(),9);
    iter++;
    EXPECT_EQ(iter,matrix3x3.endConstColumn());
}

TEST_F(MatrixTest, RefCounter)
{
    Matrix<int> copy = Matrix(matrix3x3);
    EXPECT_EQ(copy.refCount(),2);
    EXPECT_EQ(matrix3x3.refCount(),2);
    for(int row = 0; row < matrix3x3.getColumnCount(); row++)
    {
        for(int col = 0; col < matrix3x3.getRowCount(); col++)
        {
            EXPECT_EQ(copy.at(row,col),matrix3x3.at(row,col));
            EXPECT_EQ(*copy.ptrAt(row,col),*matrix3x3.ptrAt(row,col));
        }
    }
    //EXPECT_EQ(copy.refCount(),1);
    EXPECT_EQ(matrix3x3.refCount(),1);
}

TEST_F(MatrixTest,CopyOnWrite)
{
    Matrix<int> copy = Matrix(matrix3x3);
    EXPECT_EQ(copy.refCount(),2);
    EXPECT_EQ(matrix3x3.refCount(),2);
    copy.at(0,0) = 100;
    EXPECT_EQ(copy.refCount(),1);
    EXPECT_EQ(matrix3x3.refCount(),1);

    EXPECT_EQ(copy.at(0,0),100);
    EXPECT_EQ(matrix3x3.at(0,0),1);
}

TEST_F(MatrixTest,Swap)
{
    Matrix<int> copy = Matrix(matrix3x3);
    EXPECT_EQ(copy.refCount(),2);
    EXPECT_EQ(matrix3x3.refCount(),2);
    copy.at(0,0) = 100;
    EXPECT_EQ(copy.at(0,0),100);
    EXPECT_EQ(matrix3x3.at(0,0),1);

    copy.swap(matrix3x3);
    EXPECT_EQ(copy.at(0,0),1);
    EXPECT_EQ(matrix3x3.at(0,0),100);
}

TEST_F(MatrixTest, InsertRowValue)
{
    std::vector<int> row;
    row.push_back(10);
    row.push_back(11);
    row.push_back(12);

    EXPECT_EQ(matrix3x3.at(1,0),4);
    EXPECT_EQ(matrix3x3.at(1,1),5);
    EXPECT_EQ(matrix3x3.at(1,2),6);

    matrix3x3.insertRow(row,1);
    EXPECT_EQ(matrix3x3.getRowCount(),4);
    EXPECT_EQ(matrix3x3.getColumnCount(),3);

    EXPECT_EQ(matrix3x3.at(0,0),1);
    EXPECT_EQ(matrix3x3.at(0,1),2);
    EXPECT_EQ(matrix3x3.at(0,2),3);

    EXPECT_EQ(matrix3x3.at(1,0),10);
    EXPECT_EQ(matrix3x3.at(1,1),11);
    EXPECT_EQ(matrix3x3.at(1,2),12);

    EXPECT_EQ(matrix3x3.at(2,0),4);
    EXPECT_EQ(matrix3x3.at(2,1),5);
    EXPECT_EQ(matrix3x3.at(2,2),6);

    EXPECT_EQ(matrix3x3.at(3,0),7);
    EXPECT_EQ(matrix3x3.at(3,1),8);
    EXPECT_EQ(matrix3x3.at(3,2),9);
}

TEST_F(MatrixTest, InsertRowPtr)
{
    std::vector<int*> row;
    int one = 10;
    int two = 11;
    int three = 12;
    row.push_back(&one);
    row.push_back(&two);
    row.push_back(&three);

    EXPECT_EQ(matrix3x3.at(1,0),4);
    EXPECT_EQ(matrix3x3.at(1,1),5);
    EXPECT_EQ(matrix3x3.at(1,2),6);

    matrix3x3.insertRow(row,1);
    EXPECT_EQ(matrix3x3.getRowCount(),4);
    EXPECT_EQ(matrix3x3.getColumnCount(),3);

    EXPECT_EQ(matrix3x3.at(0,0),1);
    EXPECT_EQ(matrix3x3.at(0,1),2);
    EXPECT_EQ(matrix3x3.at(0,2),3);

    EXPECT_EQ(matrix3x3.at(1,0),10);
    EXPECT_EQ(matrix3x3.at(1,1),11);
    EXPECT_EQ(matrix3x3.at(1,2),12);

    EXPECT_EQ(matrix3x3.at(2,0),4);
    EXPECT_EQ(matrix3x3.at(2,1),5);
    EXPECT_EQ(matrix3x3.at(2,2),6);

    EXPECT_EQ(matrix3x3.at(3,0),7);
    EXPECT_EQ(matrix3x3.at(3,1),8);
    EXPECT_EQ(matrix3x3.at(3,2),9);
}

TEST_F(MatrixTest, InsertColumnValue)
{
    std::vector<int> col;
    col.push_back(10);
    col.push_back(11);
    col.push_back(12);

    EXPECT_EQ(matrix3x3.at(1,0),4);
    EXPECT_EQ(matrix3x3.at(1,1),5);
    EXPECT_EQ(matrix3x3.at(1,2),6);

    matrix3x3.insertColumn(col,1);
    EXPECT_EQ(matrix3x3.getRowCount(),3);
    EXPECT_EQ(matrix3x3.getColumnCount(),4);

    EXPECT_EQ(matrix3x3.at(0,0),1);
    EXPECT_EQ(matrix3x3.at(1,0),4);
    EXPECT_EQ(matrix3x3.at(2,0),7);

    EXPECT_EQ(matrix3x3.at(0,1),10);
    EXPECT_EQ(matrix3x3.at(1,1),11);
    EXPECT_EQ(matrix3x3.at(2,1),12);

    EXPECT_EQ(matrix3x3.at(0,2),2);
    EXPECT_EQ(matrix3x3.at(1,2),5);
    EXPECT_EQ(matrix3x3.at(2,2),8);

    EXPECT_EQ(matrix3x3.at(0,3),3);
    EXPECT_EQ(matrix3x3.at(1,3),6);
    EXPECT_EQ(matrix3x3.at(2,3),9);
}

TEST_F(MatrixTest, InsertColumnPtr)
{
    std::vector<int*> col;
    int one = 10;
    int two = 11;
    int three = 12;
    col.push_back(&one);
    col.push_back(&two);
    col.push_back(&three);

    EXPECT_EQ(matrix3x3.at(1,0),4);
    EXPECT_EQ(matrix3x3.at(1,1),5);
    EXPECT_EQ(matrix3x3.at(1,2),6);

    matrix3x3.insertColumn(col,1);
    EXPECT_EQ(matrix3x3.getRowCount(),3);
    EXPECT_EQ(matrix3x3.getColumnCount(),4);

    EXPECT_EQ(matrix3x3.at(0,0),1);
    EXPECT_EQ(matrix3x3.at(1,0),4);
    EXPECT_EQ(matrix3x3.at(2,0),7);

    EXPECT_EQ(matrix3x3.at(0,1),10);
    EXPECT_EQ(matrix3x3.at(1,1),11);
    EXPECT_EQ(matrix3x3.at(2,1),12);

    EXPECT_EQ(matrix3x3.at(0,2),2);
    EXPECT_EQ(matrix3x3.at(1,2),5);
    EXPECT_EQ(matrix3x3.at(2,2),8);

    EXPECT_EQ(matrix3x3.at(0,3),3);
    EXPECT_EQ(matrix3x3.at(1,3),6);
    EXPECT_EQ(matrix3x3.at(2,3),9);
}

TEST_F(MatrixTest,RemoveRowByIter)
{
    Matrix<int>::rowIterator iter = matrix3x3.beginRow();
    iter++;
    matrix3x3.eraseRow(iter);

    EXPECT_EQ(matrix3x3.getRowCount(),2);

    EXPECT_EQ(matrix3x3.at(0,0),1);
    EXPECT_EQ(matrix3x3.at(0,1),2);
    EXPECT_EQ(matrix3x3.at(0,2),3);

    EXPECT_EQ(matrix3x3.at(1,0),7);
    EXPECT_EQ(matrix3x3.at(1,1),8);
    EXPECT_EQ(matrix3x3.at(1,2),9);
}

TEST_F(MatrixTest,RemoveColumnByIter)
{
    Matrix<int>::columnIterator iter = matrix3x3.beginColumn();
    iter++;
    matrix3x3.eraseColumn(iter);

    EXPECT_EQ(matrix3x3.getColumnCount(),2);

    EXPECT_EQ(matrix3x3.at(0,0),1);
    EXPECT_EQ(matrix3x3.at(1,0),4);
    EXPECT_EQ(matrix3x3.at(2,0),7);

    EXPECT_EQ(matrix3x3.at(0,1),3);
    EXPECT_EQ(matrix3x3.at(1,1),6);
    EXPECT_EQ(matrix3x3.at(2,1),9);
}