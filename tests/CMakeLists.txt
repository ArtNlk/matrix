project(Matrix C CXX)

enable_testing()

add_executable(MatrixTests matrixTests.cc)

include_directories(../Matrix)
target_link_libraries(MatrixTests gtest_main)
target_link_libraries(MatrixTests matrixlib)

include(GoogleTest)
gtest_discover_tests(MatrixTests)