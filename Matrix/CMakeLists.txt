project(Matrix)

set(SOURCES_MATRIX Matrix.cpp MatrixImpl.cpp MatrixImpl.h)

add_library(matrixlib STATIC ${SOURCES_MATRIX})