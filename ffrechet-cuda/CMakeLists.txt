cmake_minimum_required(VERSION 3.14)

project(
    ffrechet-cuda
    LANGUAGES CUDA CXX
)

# ---- Declare library ----

add_library(
    ffrechet-cuda_ffrechet-cuda
    source/common.cu
    source/ffrechet-cuda.cu
)
add_library(ffrechet-cuda::ffrechet-cuda ALIAS ffrechet-cuda_ffrechet-cuda)

include(GenerateExportHeader)
generate_export_header(
    ffrechet-cuda_ffrechet-cuda
    BASE_NAME ffrechet-cuda
    EXPORT_FILE_NAME export/ffrechet-cuda/ffrechet-cuda_export.hpp
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(ffrechet-cuda_ffrechet-cuda PUBLIC FFRECHET_CUDA_STATIC_DEFINE)
endif()

set_target_properties(
    ffrechet-cuda_ffrechet-cuda PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME ffrechet-cuda
    OUTPUT_NAME ffrechet-cuda
)

target_include_directories(
    ffrechet-cuda_ffrechet-cuda
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    ffrechet-cuda_ffrechet-cuda SYSTEM
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(ffrechet-cuda_ffrechet-cuda PUBLIC cxx_std_11)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

option(ffrechet-cuda_DEVELOPER_MODE "Enable developer mode" OFF)
if(ffrechet-cuda_DEVELOPER_MODE)
  include(cmake/dev-mode.cmake)
endif()

