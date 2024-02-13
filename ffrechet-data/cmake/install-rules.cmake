set(
  CMAKE_INSTALL_INCLUDEDIR "include/ffrechet-data-${PROJECT_VERSION}"
  CACHE STRING ""
)
set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)

# Project is configured with no languages, so tell GNUInstallDirs the lib dir
set(CMAKE_INSTALL_LIBDIR lib CACHE PATH "")

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package ffrechet-data)

install(
    DIRECTORY include/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT ffrechet-data_Development
)

install(
    TARGETS ffrechet-data_ffrechet-data
    EXPORT ffrechet-dataTargets
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
    ARCH_INDEPENDENT
)

# Allow package maintainers to freely override the path for the configs
set(
    ffrechet-data_INSTALL_CMAKEDIR "${CMAKE_INSTALL_DATADIR}/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE ffrechet-data_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(ffrechet-data_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${ffrechet-data_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT ffrechet-data_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${ffrechet-data_INSTALL_CMAKEDIR}"
    COMPONENT ffrechet-data_Development
)

install(
    EXPORT ffrechet-dataTargets
    NAMESPACE ffrechet-data::
    DESTINATION "${ffrechet-data_INSTALL_CMAKEDIR}"
    COMPONENT ffrechet-data_Development
)

include(CPack)
