cmake_minimum_required(VERSION 3.14)

project(
    ffrechet-baseline
    VERSION 0.1.0
    DESCRIPTION "Baseline implementation for measuring the performance of the Fast Frechet algorithm"
    HOMEPAGE_URL "https://github.com/avitase/fast_frechet/tree/main/ffrechet-baseline"
    LANGUAGES CXX
)

# ---- Declare library ----

add_library(
    ffrechet-baseline_ffrechet-baseline
    source/ffrechet-baseline.cpp
)
add_library(ffrechet-baseline::ffrechet-baseline ALIAS ffrechet-baseline_ffrechet-baseline)

include(GenerateExportHeader)
generate_export_header(
    ffrechet-baseline_ffrechet-baseline
    BASE_NAME ffrechet-baseline
    EXPORT_FILE_NAME export/ffrechet-baseline/ffrechet-baseline_export.hpp
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(ffrechet-baseline_ffrechet-baseline PUBLIC FFRECHET_BASELINE_STATIC_DEFINE)
endif()

set_target_properties(
    ffrechet-baseline_ffrechet-baseline PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME ffrechet-baseline
    OUTPUT_NAME ffrechet-baseline
)

target_include_directories(
    ffrechet-baseline_ffrechet-baseline
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    ffrechet-baseline_ffrechet-baseline SYSTEM
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(ffrechet-baseline_ffrechet-baseline PUBLIC cxx_std_17)

set(FFRECHET_SIMD_LANE_MULTIPLIER 1 CACHE STRING "SIMD lane size multiplier")
target_compile_definitions(ffrechet-baseline_ffrechet-baseline PUBLIC FFRECHET_SIMD_LANE_MULTIPLIER=${FFRECHET_SIMD_LANE_MULTIPLIER})

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

option(ffrechet-baseline_DEVELOPER_MODE "Enable developer mode" OFF)
if(ffrechet-baseline_DEVELOPER_MODE)
  include(cmake/dev-mode.cmake)
endif()

