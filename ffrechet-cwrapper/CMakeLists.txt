cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    ffrechet-cwrapper
    LANGUAGES NONE
)

# ---- Declare library ----

add_library(ffrechet-cwrapper_ffrechet-cwrapper INTERFACE)
add_library(ffrechet-cwrapper::ffrechet-cwrapper ALIAS ffrechet-cwrapper_ffrechet-cwrapper)

set_property(
    TARGET ffrechet-cwrapper_ffrechet-cwrapper PROPERTY
    EXPORT_NAME ffrechet-cwrapper
)

target_include_directories(
    ffrechet-cwrapper_ffrechet-cwrapper
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

find_package(ffrechet-data REQUIRED)
find_package(ffrechet-baseline REQUIRED)
find_package(ffrechet-vanilla REQUIRED)
find_package(ffrechet-linear REQUIRED)
find_package(ffrechet-simd REQUIRED)
find_package(ffrechet-cuda REQUIRED)

target_link_libraries(
    ffrechet-cwrapper_ffrechet-cwrapper
    INTERFACE
    ffrechet-data::ffrechet-data
    ffrechet-baseline::ffrechet-baseline
    ffrechet-vanilla::ffrechet-vanilla
    ffrechet-linear::ffrechet-linear
    ffrechet-simd::ffrechet-simd
    ffrechet-cuda::ffrechet-cuda
)

target_compile_features(ffrechet-cwrapper_ffrechet-cwrapper INTERFACE cxx_std_17)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

option(ffrechet-cwrapper_DEVELOPER_MODE "Enable developer mode" OFF)
if(ffrechet-cwrapper_DEVELOPER_MODE)
  include(cmake/dev-mode.cmake)
endif()

