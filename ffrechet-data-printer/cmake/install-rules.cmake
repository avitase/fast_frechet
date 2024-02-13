set_target_properties(ffrechet-data-printer PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

install(
    TARGETS ffrechet-data-printer
    RUNTIME COMPONENT ffrechet-data-printer_Runtime
)

include(CPack)
