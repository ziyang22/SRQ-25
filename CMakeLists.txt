cmake_minimum_required(VERSION 3.10)

project(MatrixMultiplication C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(OpenMP REQUIRED)
if (OpenMP_C_FOUND)
    message(STATUS "OpenMP found, enabling C support.")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif()

# 编译两个源文件
add_executable(run_matrix_multiplication
    src/main.c
    src/task.c
)

target_link_libraries(run_matrix_multiplication m)