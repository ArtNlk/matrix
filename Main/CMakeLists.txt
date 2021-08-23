project(Matrix)

set(SOURCES_MAIN main.cpp)

include_directories(../Matrix)

add_executable(Main ${SOURCES_MAIN})

target_link_libraries(Main matrixlib)