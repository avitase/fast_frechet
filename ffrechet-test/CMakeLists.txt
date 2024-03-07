cmake_minimum_required(VERSION 3.14)

project(
    ffrechet-test
    VERSION 1.0.0
    LANGUAGES CXX
)

# ---- Declare executable ----

add_executable(ffrechet-test source/main.cpp)

find_package(GTest REQUIRED)
find_package(ffrechet-data REQUIRED)
find_package(ffrechet-baseline REQUIRED)
find_package(ffrechet-vanilla REQUIRED)
find_package(ffrechet-linear REQUIRED)
find_package(ffrechet-simd REQUIRED)
find_package(ffrechet-cuda REQUIRED)
find_package(ffrechet-cwrapper REQUIRED)

target_link_libraries(
    ffrechet-test
    PUBLIC
    GTest::gtest_main
    PRIVATE
    ffrechet-cwrapper::ffrechet-cwrapper
)

target_compile_features(ffrechet-test PRIVATE cxx_std_20)

include(GoogleTest)
enable_testing()
gtest_discover_tests(ffrechet-test)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

option(ffrechet-test_DEVELOPER_MODE "Enable developer mode" OFF)
if(ffrechet-test_DEVELOPER_MODE)
  include(cmake/dev-mode.cmake)
endif()
