cmake_minimum_required(VERSION 3.14)

project(
    ffrechet-linear
    VERSION 0.1.0
    DESCRIPTION "Canonical implementation of the discrete Frechet distance algorithm"
    HOMEPAGE_URL "https://github.com/avitase/fast_frechet/tree/main/ffrechet-linear"
    LANGUAGES CXX
)

# ---- Declare library ----

add_library(
    ffrechet-linear_ffrechet-linear
    source/ffrechet-linear.cpp
)
add_library(ffrechet-linear::ffrechet-linear ALIAS ffrechet-linear_ffrechet-linear)

include(GenerateExportHeader)
generate_export_header(
    ffrechet-linear_ffrechet-linear
    BASE_NAME ffrechet-linear
    EXPORT_FILE_NAME export/ffrechet-linear/ffrechet-linear_export.hpp
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(ffrechet-linear_ffrechet-linear PUBLIC FFRECHET_LINEAR_STATIC_DEFINE)
endif()

set_target_properties(
    ffrechet-linear_ffrechet-linear PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME ffrechet-linear
    OUTPUT_NAME ffrechet-linear
)

target_include_directories(
    ffrechet-linear_ffrechet-linear
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    ffrechet-linear_ffrechet-linear SYSTEM
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(ffrechet-linear_ffrechet-linear PUBLIC cxx_std_17)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

option(ffrechet-linear_DEVELOPER_MODE "Enable developer mode" OFF)
if(ffrechet-linear_DEVELOPER_MODE)
  include(cmake/dev-mode.cmake)
endif()

