project(Matrix)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_subdirectory(Matrix)
add_subdirectory(Main)

set_property(TARGET Main PROPERTY CXX_STANDARD 20)
set_property(TARGET matrixlib PROPERTY CXX_STANDARD 20)