set(
  CMAKE_INSTALL_INCLUDEDIR "include/ffrechet-cwrapper-${PROJECT_VERSION}"
  CACHE STRING ""
)
set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)

# Project is configured with no languages, so tell GNUInstallDirs the lib dir
set(CMAKE_INSTALL_LIBDIR lib CACHE PATH "")

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package ffrechet-cwrapper)

install(
    DIRECTORY include/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT ffrechet-cwrapper_Development
)

install(
    TARGETS ffrechet-cwrapper_ffrechet-cwrapper
    EXPORT ffrechet-cwrapperTargets
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
    ARCH_INDEPENDENT
)

# Allow package maintainers to freely override the path for the configs
set(
    ffrechet-cwrapper_INSTALL_CMAKEDIR "${CMAKE_INSTALL_DATADIR}/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE ffrechet-cwrapper_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(ffrechet-cwrapper_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${ffrechet-cwrapper_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT ffrechet-cwrapper_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${ffrechet-cwrapper_INSTALL_CMAKEDIR}"
    COMPONENT ffrechet-cwrapper_Development
)

install(
    EXPORT ffrechet-cwrapperTargets
    NAMESPACE ffrechet-cwrapper::
    DESTINATION "${ffrechet-cwrapper_INSTALL_CMAKEDIR}"
    COMPONENT ffrechet-cwrapper_Development
)

include(CPack)
