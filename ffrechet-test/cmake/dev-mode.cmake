include(cmake/folders.cmake)

add_custom_target(
    run-exe
    COMMAND ffrechet-test
    VERBATIM
)
add_dependencies(run-exe ffrechet-test)

include(cmake/lint-targets.cmake)

add_folders(Project)
