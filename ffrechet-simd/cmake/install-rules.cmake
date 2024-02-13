set(
  CMAKE_INSTALL_INCLUDEDIR "include/ffrechet-simd-${PROJECT_VERSION}"
  CACHE STRING ""
)
set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package ffrechet-simd)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT ffrechet-simd_Development
)

install(
    TARGETS ffrechet-simd_ffrechet-simd
    EXPORT ffrechet-simdTargets
    RUNTIME #
    COMPONENT ffrechet-simd_Runtime
    LIBRARY #
    COMPONENT ffrechet-simd_Runtime
    NAMELINK_COMPONENT ffrechet-simd_Development
    ARCHIVE #
    COMPONENT ffrechet-simd_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    ffrechet-simd_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE ffrechet-simd_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(ffrechet-simd_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${ffrechet-simd_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT ffrechet-simd_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${ffrechet-simd_INSTALL_CMAKEDIR}"
    COMPONENT ffrechet-simd_Development
)

install(
    EXPORT ffrechet-simdTargets
    NAMESPACE ffrechet-simd::
    DESTINATION "${ffrechet-simd_INSTALL_CMAKEDIR}"
    COMPONENT ffrechet-simd_Development
)

include(CPack)
