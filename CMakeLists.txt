project(Matrix)

add_subdirectory(Matrix)
add_subdirectory(Main)

set_property(TARGET Main PROPERTY CXX_STANDARD 20)
set_property(TARGET matrixlib PROPERTY CXX_STANDARD 20)