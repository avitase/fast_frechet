set(
  CMAKE_INSTALL_INCLUDEDIR "include/ffrechet-cuda-${PROJECT_VERSION}"
  CACHE STRING ""
)
set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package ffrechet-cuda)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT ffrechet-cuda_Development
)

install(
    TARGETS ffrechet-cuda_ffrechet-cuda
    EXPORT ffrechet-cudaTargets
    RUNTIME #
    COMPONENT ffrechet-cuda_Runtime
    LIBRARY #
    COMPONENT ffrechet-cuda_Runtime
    NAMELINK_COMPONENT ffrechet-cuda_Development
    ARCHIVE #
    COMPONENT ffrechet-cuda_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    ffrechet-cuda_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE ffrechet-cuda_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(ffrechet-cuda_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${ffrechet-cuda_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT ffrechet-cuda_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${ffrechet-cuda_INSTALL_CMAKEDIR}"
    COMPONENT ffrechet-cuda_Development
)

install(
    EXPORT ffrechet-cudaTargets
    NAMESPACE ffrechet-cuda::
    DESTINATION "${ffrechet-cuda_INSTALL_CMAKEDIR}"
    COMPONENT ffrechet-cuda_Development
)

include(CPack)
