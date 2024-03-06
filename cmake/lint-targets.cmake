set(
    FORMAT_PATTERNS
    ffrechet-baseline/include/*.hpp
    ffrechet-baseline/source/*.cpp ffrechet-baseline/source/*.hpp
    ffrechet-benchmark/source/*.cpp ffrechet-benchmark/source/*.hpp
    ffrechet-cuda/include/*.hpp
    ffrechet-cuda/source/*.cpp ffrechet-cuda/*.cu ffrechet-cuda/source/*.hpp
    ffrechet-cwrapper/include/*.hpp
    ffrechet-data/include/ffrechet-data/ffrechet-data.hpp
    ffrechet-data-printer/include/*.hpp
    ffrechet-data-printer/source/*.cpp ffrechet-data-printer/source/*.hpp
    ffrechet-linear/include/*.hpp
    ffrechet-linear/source/*.cpp ffrechet-linear/source/*.hpp
    ffrechet-simd/include/*.hpp
    ffrechet-simd/source/*.cpp ffrechet-simd/source/*.hpp
    ffrechet-vanilla/include/*.hpp
    ffrechet-vanilla/source/*.cpp ffrechet-vanilla/source/*.hpp
    ffrechet-test/source/*.cpp ffrechet-test/source/*.hpp
    CACHE STRING
    "; separated patterns relative to the project source dir to format"
)

set(FORMAT_COMMAND clang-format CACHE STRING "Formatter to use")

add_custom_target(
    format-check
    COMMAND "${CMAKE_COMMAND}"
    -D "FORMAT_COMMAND=${FORMAT_COMMAND}"
    -D "PATTERNS=${FORMAT_PATTERNS}"
    -P "${PROJECT_SOURCE_DIR}/cmake/lint.cmake"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Linting the code"
    VERBATIM
)

add_custom_target(
    format-fix
    COMMAND "${CMAKE_COMMAND}"
    -D "FORMAT_COMMAND=${FORMAT_COMMAND}"
    -D "PATTERNS=${FORMAT_PATTERNS}"
    -D FIX=YES
    -P "${PROJECT_SOURCE_DIR}/cmake/lint.cmake"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Fixing the code"
    VERBATIM
)
