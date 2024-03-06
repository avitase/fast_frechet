cmake_minimum_required(VERSION 3.14)

project(
    ffrechet-benchmark
    LANGUAGES CXX
)

# ---- Declare executable ----

add_executable(ffrechet-benchmark source/main.cpp)

find_package(benchmark REQUIRED)
find_package(ffrechet-data REQUIRED)
find_package(ffrechet-baseline REQUIRED)
find_package(ffrechet-vanilla REQUIRED)
find_package(ffrechet-linear REQUIRED)
find_package(ffrechet-simd REQUIRED)
find_package(ffrechet-cuda REQUIRED)
find_package(ffrechet-cwrapper REQUIRED)

target_link_libraries(
    ffrechet-benchmark
    PUBLIC
    benchmark::benchmark
    PRIVATE
    ffrechet-data::ffrechet-data
    ffrechet-baseline::ffrechet-baseline
    ffrechet-vanilla::ffrechet-vanilla
    ffrechet-linear::ffrechet-linear
    ffrechet-simd::ffrechet-simd
    ffrechet-cuda::ffrechet-cuda
    ffrechet-cwrapper::ffrechet-cwrapper
)

target_compile_features(ffrechet-benchmark PRIVATE cxx_std_20)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

option(ffrechet-benchmark_DEVELOPER_MODE "Enable developer mode" OFF)
if(ffrechet-benchmark_DEVELOPER_MODE)
  include(cmake/dev-mode.cmake)
endif()
