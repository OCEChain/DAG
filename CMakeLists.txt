
cmake_minimum_required(VERSION 3.3)
project(dag)

set(DAG_MAJOR_VERSION 1)
set(DAG_MINOR_VERSION 0)
set(DAG_PATCH_VERSION 0)
set(DAG_VERSION
  ${DAG_MAJOR_VERSION}.${DAG_MINOR_VERSION}.${DAG_PATCH_VERSION})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(APPLE)
  set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
  set(CMAKE_MACOSX_RPATH 1)
  set(CMAKE_OSX_DEPLOYMENT_TARGET 10.10)
endif(APPLE)

#--- Declare options -----------------------------------------------------------
#option(dag_documentation "Whether or not to create doxygen doc target.")
#option(dag_example "Whether or not to create examples")

add_definitions(-Wno-unused-variable -Wno-unused-parameter)
#
#--- enable unit testing capabilities ------------------------------------------
include(CTest)

add_subdirectory(dag)
add_subdirectory(tests)

if(dag_example)
  add_subdirectory(examples)
endif(dag_example)

if(dag_documentation)
  include(cmake/dagDoxygen.cmake)
endif()

#--- add version files ---------------------------------------------------------
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dagVersion.h
               ${CMAKE_CURRENT_BINARY_DIR}/dagVersion.h )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/dagVersion.h
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/dag/ )

#--- add CMake infrastructure --------------------------------------------------
include(cmake/dagCreateConfig.cmake)




# CMake files
# ===============================
#set(DEF_INSTALL_CMAKE_DIR cmake)
#set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
#  "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
#foreach(p INCLUDE CMAKE)
#  set(var INSTALL_${p}_DIR)
#  if(NOT IS_ABSOLUTE "${${var}}")
#    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
#  endif()
#endforeach()
#
## Export the package for use from the build-tree
## (this registers the build-tree with a global CMake-registry)
##export(PACKAGE dag)
#
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/DagVersion.h
#               ${CMAKE_CURRENT_BINARY_DIR}/DagVersion.h )
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/DagVersion.h
#        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/dag )
#
# ## Create the dagConfig.cmake and dagConfigVersion files
# #file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
# #   "${INSTALL_INCLUDE_DIR}")
# ## ... for the build tree
# #set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
# #configure_file(dagConfig.cmake.in
# #  "${PROJECT_BINARY_DIR}/dagConfig.cmake" @ONLY)
# ## ... for the install tree
#
#set(CONF_INCLUDE_DIRS "${CMAKE_INSTALL_PREFIX}/include/")
#configure_file(dagConfig.cmake.in
#  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/dagConfig.cmake" @ONLY)
## ... for both
#configure_file(dagConfigVersion.cmake.in
#  "${PROJECT_BINARY_DIR}/dagConfigVersion.cmake" @ONLY)
#
## Install the dagConfig.cmake and dagConfigVersion.cmake
#install(FILES
#  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/dagConfig.cmake"
#  "${PROJECT_BINARY_DIR}/dagConfigVersion.cmake"
#  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)






