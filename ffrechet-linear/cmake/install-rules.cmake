set(
  CMAKE_INSTALL_INCLUDEDIR "include/ffrechet-linear-${PROJECT_VERSION}"
  CACHE STRING ""
)
set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package ffrechet-linear)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT ffrechet-linear_Development
)

install(
    TARGETS ffrechet-linear_ffrechet-linear
    EXPORT ffrechet-linearTargets
    RUNTIME #
    COMPONENT ffrechet-linear_Runtime
    LIBRARY #
    COMPONENT ffrechet-linear_Runtime
    NAMELINK_COMPONENT ffrechet-linear_Development
    ARCHIVE #
    COMPONENT ffrechet-linear_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    ffrechet-linear_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE ffrechet-linear_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(ffrechet-linear_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${ffrechet-linear_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT ffrechet-linear_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${ffrechet-linear_INSTALL_CMAKEDIR}"
    COMPONENT ffrechet-linear_Development
)

install(
    EXPORT ffrechet-linearTargets
    NAMESPACE ffrechet-linear::
    DESTINATION "${ffrechet-linear_INSTALL_CMAKEDIR}"
    COMPONENT ffrechet-linear_Development
)

include(CPack)
