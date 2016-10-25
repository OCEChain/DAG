include(CMakePackageConfigHelpers)
configure_file(cmake/dagConfig.cmake.in "${PROJECT_BINARY_DIR}/dagConfig.cmake" @ONLY)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/dagConfigVersion.cmake
                                 VERSION ${DAG_VERSION}
                                 COMPATIBILITY SameMajorVersion )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/dagConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/dagConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_PREFIX}/cmake )
