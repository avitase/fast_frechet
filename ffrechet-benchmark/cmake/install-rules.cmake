set_target_properties(ffrechet-benchmark PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

install(
    TARGETS ffrechet-benchmark
    RUNTIME COMPONENT ffrechet-benchmark_Runtime
)

include(CPack)
