cmake_minimum_required(VERSION 3.0.0)
project(fft_algo VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories ("${PROJECT_SOURCE_DIR}/include")
message(${PROJECT_SOURCE_DIR})
set(CMAKE_C_COMPILER "C:\\MinGW\\bin\\gcc.exe")
set(CMAKE_C_FLAGS "-std=c11")
set(INCLUDE_DIR "include")

add_library(
    fft_algo
    ${INCLUDE_DIR}/fft_algo.h
    src/fft_algo.c
)

add_executable(fft_algo_test test/fft_algo_test.c)
target_link_libraries(fft_algo_test fft_algo)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
