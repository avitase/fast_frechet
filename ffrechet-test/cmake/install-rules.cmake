set_target_properties(ffrechet-test PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

install(
    TARGETS ffrechet-test
    RUNTIME COMPONENT ffrechet-test_Runtime
)

include(CPack)
