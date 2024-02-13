cmake_minimum_required(VERSION 3.14)

project(ffrechet)

# ---- Super build ----

set(FFRECHET_DATA_PRINTER_BUILD_TYPE "Release" CACHE STRING "Build type of ffrechet-data-printer")
set(FFRECHET_VANILLA_BUILD_TYPE "Release" CACHE STRING "Build type of ffrechet-vanilla")
set(FFRECHET_LINEAR_BUILD_TYPE "Release" CACHE STRING "Build type of ffrechet-linear")
set(FFRECHET_SIMD_BUILD_TYPE "Release" CACHE STRING "Build type of ffrechet-simd")
set(FFRECHET_CUDA_BUILD_TYPE "Release" CACHE STRING "Build type of ffrechet-cuda")
set(FFRECHET_TEST_BUILD_TYPE "Debug" CACHE STRING "Build type of ffrechet-test")
set(FFRECHET_BENCHMARK_BUILD_TYPE "Release" CACHE STRING "Build type of ffrechet-benchmark")

set(FFRECHET_SIMD_LANE_MULTIPLIER 1 CACHE STRING "SIMD lane size multiplier")

include(ExternalProject)

ExternalProject_Add(ffrechet-data
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/ffrechet-data
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

ExternalProject_Add(ffrechet-data-printer
    DEPENDS ffrechet-data 
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/ffrechet-data-printer
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_CURRENT_LIST_DIR}/ffrechet-data-printer/ffrechet-data-printer_toolchain.cmake
        -DCMAKE_PREFIX_PATH:PATH=<INSTALL_DIR>
        -DCMAKE_BUILD_TYPE=${FFRECHET_DATA_PRINTER_BUILD_TYPE}
)

ExternalProject_Add(ffrechet-vanilla
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/ffrechet-vanilla
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_CURRENT_LIST_DIR}/ffrechet-vanilla/ffrechet-vanilla_toolchain.cmake
        -DCMAKE_BUILD_TYPE=${FFRECHET_VANILLA_BUILD_TYPE}
        -DBUILD_SHARED_LIBS=ON
)

ExternalProject_Add(ffrechet-linear
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/ffrechet-linear
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_CURRENT_LIST_DIR}/ffrechet-linear/ffrechet-linear_toolchain.cmake
        -DCMAKE_BUILD_TYPE=${FFRECHET_LINEAR_BUILD_TYPE}
        -DBUILD_SHARED_LIBS=ON
)

ExternalProject_Add(ffrechet-simd
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/ffrechet-simd
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_CURRENT_LIST_DIR}/ffrechet-simd/ffrechet-simd_toolchain.cmake
        -DCMAKE_BUILD_TYPE=${FFRECHET_SIMD_BUILD_TYPE}
        -DFFRECHET_SIMD_LANE_MULTIPLIER=${FFRECHET_SIMD_LANE_MULTIPLIER}
        -DBUILD_SHARED_LIBS=ON
)

ExternalProject_Add(ffrechet-cuda
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/ffrechet-cuda
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_CURRENT_LIST_DIR}/ffrechet-cuda/ffrechet-cuda_toolchain.cmake
        -DCMAKE_BUILD_TYPE=${FFRECHET_CUDA_BUILD_TYPE}
        -DBUILD_SHARED_LIBS=ON
)

ExternalProject_Add(ffrechet-cwrapper
    DEPENDS ffrechet-data ffrechet-vanilla ffrechet-linear ffrechet-simd ffrechet-cuda
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/ffrechet-cwrapper
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

ExternalProject_Add(google-test
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/google-test
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
        -DCMAKE_PREFIX_PATH:PATH=<INSTALL_DIR>
        -DCMAKE_BUILD_TYPE=Release
)

ExternalProject_Add(ffrechet-test
    DEPENDS ffrechet-data ffrechet-cwrapper google-test
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/ffrechet-test
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install
    TEST_AFTER_INSTALL ON
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_CURRENT_LIST_DIR}/ffrechet-test/ffrechet-test_toolchain.cmake
        -DCMAKE_PREFIX_PATH:PATH=<INSTALL_DIR>
        -DCMAKE_BUILD_TYPE=${FFRECHET_TEST_BUILD_TYPE}
)

ExternalProject_Add(google-benchmark
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/google-benchmark
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
        -DCMAKE_PREFIX_PATH:PATH=<INSTALL_DIR>
        -DCMAKE_BUILD_TYPE=Release
        -DBENCHMARK_ENABLE_GTEST_TESTS=OFF
)

ExternalProject_Add(ffrechet-benchmark
    DEPENDS ffrechet-data ffrechet-cwrapper google-benchmark
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/ffrechet-benchmark
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_CURRENT_LIST_DIR}/ffrechet-benchmark/ffrechet-benchmark_toolchain.cmake
        -DCMAKE_PREFIX_PATH:PATH=<INSTALL_DIR>
        -DCMAKE_BUILD_TYPE=${FFRECHET_BENCHMARK_BUILD_TYPE}
)

# ---- Developer mode ----

option(ffrechet_DEVELOPER_MODE "Enable developer mode" OFF)
if(ffrechet_DEVELOPER_MODE)
  include(cmake/dev-mode.cmake)
endif()
