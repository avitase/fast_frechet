cmake_minimum_required(VERSION 3.14)

project(
    ffrechet-vanilla
    VERSION 1.0.0
    LANGUAGES CXX
)

# ---- Declare library ----

add_library(
    ffrechet-vanilla_ffrechet-vanilla
    source/ffrechet-vanilla.cpp
)
add_library(ffrechet-vanilla::ffrechet-vanilla ALIAS ffrechet-vanilla_ffrechet-vanilla)

include(GenerateExportHeader)
generate_export_header(
    ffrechet-vanilla_ffrechet-vanilla
    BASE_NAME ffrechet-vanilla
    EXPORT_FILE_NAME export/ffrechet-vanilla/ffrechet-vanilla_export.hpp
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(ffrechet-vanilla_ffrechet-vanilla PUBLIC FFRECHET_VANILLA_STATIC_DEFINE)
endif()

set_target_properties(
    ffrechet-vanilla_ffrechet-vanilla PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME ffrechet-vanilla
    OUTPUT_NAME ffrechet-vanilla
)

target_include_directories(
    ffrechet-vanilla_ffrechet-vanilla
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    ffrechet-vanilla_ffrechet-vanilla SYSTEM
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(ffrechet-vanilla_ffrechet-vanilla PUBLIC cxx_std_17)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

option(ffrechet-vanilla_DEVELOPER_MODE "Enable developer mode" OFF)
if(ffrechet-vanilla_DEVELOPER_MODE)
  include(cmake/dev-mode.cmake)
endif()

