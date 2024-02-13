include(cmake/folders.cmake)

add_custom_target(
    run-exe
    COMMAND ffrechet-benchmark
    VERBATIM
)
add_dependencies(run-exe ffrechet-benchmark)

include(cmake/lint-targets.cmake)

add_folders(Project)
