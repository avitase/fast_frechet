cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    ffrechet-data
    VERSION 1.0.0
    LANGUAGES NONE
)

# ---- Declare library ----

add_library(ffrechet-data_ffrechet-data INTERFACE)
add_library(ffrechet-data::ffrechet-data ALIAS ffrechet-data_ffrechet-data)

set_property(
    TARGET ffrechet-data_ffrechet-data PROPERTY
    EXPORT_NAME ffrechet-data
)

target_include_directories(
    ffrechet-data_ffrechet-data
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(ffrechet-data_ffrechet-data INTERFACE cxx_std_17)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

option(ffrechet-data_DEVELOPER_MODE "Enable developer mode" OFF)
if(ffrechet-data_DEVELOPER_MODE)
  include(cmake/dev-mode.cmake)
endif()
