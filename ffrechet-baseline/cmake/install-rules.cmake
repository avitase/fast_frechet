set(
  CMAKE_INSTALL_INCLUDEDIR "include/ffrechet-baseline-${PROJECT_VERSION}"
  CACHE STRING ""
)
set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package ffrechet-baseline)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT ffrechet-baseline_Development
)

install(
    TARGETS ffrechet-baseline_ffrechet-baseline
    EXPORT ffrechet-baselineTargets
    RUNTIME #
    COMPONENT ffrechet-baseline_Runtime
    LIBRARY #
    COMPONENT ffrechet-baseline_Runtime
    NAMELINK_COMPONENT ffrechet-baseline_Development
    ARCHIVE #
    COMPONENT ffrechet-baseline_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    ffrechet-baseline_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE ffrechet-baseline_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(ffrechet-baseline_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${ffrechet-baseline_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT ffrechet-baseline_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${ffrechet-baseline_INSTALL_CMAKEDIR}"
    COMPONENT ffrechet-baseline_Development
)

install(
    EXPORT ffrechet-baselineTargets
    NAMESPACE ffrechet-baseline::
    DESTINATION "${ffrechet-baseline_INSTALL_CMAKEDIR}"
    COMPONENT ffrechet-baseline_Development
)

include(CPack)
