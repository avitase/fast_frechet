set(
  CMAKE_INSTALL_INCLUDEDIR "include/ffrechet-vanilla-${PROJECT_VERSION}"
  CACHE STRING ""
)
set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package ffrechet-vanilla)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT ffrechet-vanilla_Development
)

install(
    TARGETS ffrechet-vanilla_ffrechet-vanilla
    EXPORT ffrechet-vanillaTargets
    RUNTIME #
    COMPONENT ffrechet-vanilla_Runtime
    LIBRARY #
    COMPONENT ffrechet-vanilla_Runtime
    NAMELINK_COMPONENT ffrechet-vanilla_Development
    ARCHIVE #
    COMPONENT ffrechet-vanilla_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    ffrechet-vanilla_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE ffrechet-vanilla_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(ffrechet-vanilla_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${ffrechet-vanilla_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT ffrechet-vanilla_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${ffrechet-vanilla_INSTALL_CMAKEDIR}"
    COMPONENT ffrechet-vanilla_Development
)

install(
    EXPORT ffrechet-vanillaTargets
    NAMESPACE ffrechet-vanilla::
    DESTINATION "${ffrechet-vanilla_INSTALL_CMAKEDIR}"
    COMPONENT ffrechet-vanilla_Development
)

include(CPack)
