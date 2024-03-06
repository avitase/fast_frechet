cmake_minimum_required(VERSION 3.14)

project(
    ffrechet-data-printer
    LANGUAGES CXX
)

# ---- Declare executable ----

add_executable(ffrechet-data-printer source/main.cpp)

find_package(ffrechet-data REQUIRED)

target_link_libraries(
    ffrechet-data-printer
    PRIVATE
    ffrechet-data::ffrechet-data
)

target_compile_features(ffrechet-data-printer PRIVATE cxx_std_20)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

option(ffrechet-data-printer_DEVELOPER_MODE "Enable developer mode" OFF)
if(ffrechet-data-printer_DEVELOPER_MODE)
  include(cmake/dev-mode.cmake)
endif()
