cmake_minimum_required(VERSION 3.14)

project(
    ffrechet-simd
    VERSION 0.1.0
    DESCRIPTION "SIMD implementation of the Fast Frechet algorithm"
    HOMEPAGE_URL "https://github.com/avitase/fast_frechet/tree/main/ffrechet-simd"
    LANGUAGES CXX
)

# ---- Declare library ----

add_library(
    ffrechet-simd_ffrechet-simd
    source/ffrechet-simd.cpp
)
add_library(ffrechet-simd::ffrechet-simd ALIAS ffrechet-simd_ffrechet-simd)

include(GenerateExportHeader)
generate_export_header(
    ffrechet-simd_ffrechet-simd
    BASE_NAME ffrechet-simd
    EXPORT_FILE_NAME export/ffrechet-simd/ffrechet-simd_export.hpp
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(ffrechet-simd_ffrechet-simd PUBLIC FFRECHET_SIMD_STATIC_DEFINE)
endif()

set_target_properties(
    ffrechet-simd_ffrechet-simd PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME ffrechet-simd
    OUTPUT_NAME ffrechet-simd
)

target_include_directories(
    ffrechet-simd_ffrechet-simd
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    ffrechet-simd_ffrechet-simd SYSTEM
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(ffrechet-simd_ffrechet-simd PUBLIC cxx_std_17)

set(FFRECHET_SIMD_LANE_MULTIPLIER 1 CACHE STRING "SIMD lane size multiplier")
target_compile_definitions(ffrechet-simd_ffrechet-simd PUBLIC FFRECHET_SIMD_LANE_MULTIPLIER=${FFRECHET_SIMD_LANE_MULTIPLIER})

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

option(ffrechet-simd_DEVELOPER_MODE "Enable developer mode" OFF)
if(ffrechet-simd_DEVELOPER_MODE)
  include(cmake/dev-mode.cmake)
endif()

