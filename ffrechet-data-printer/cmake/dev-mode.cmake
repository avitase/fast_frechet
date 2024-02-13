include(cmake/folders.cmake)

add_custom_target(
    run-exe
    COMMAND ffrechet-data-printer
    VERBATIM
)
add_dependencies(run-exe ffrechet-data-printer)

include(cmake/lint-targets.cmake)

add_folders(Project)
