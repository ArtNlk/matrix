project(Matrix C CXX)

set(SOURCES_MATRIX Matrix.h MatrixImpl.h)

add_library(matrixlib STATIC ${SOURCES_MATRIX})
set_target_properties(matrixlib PROPERTIES LINKER_LANGUAGE CXX)