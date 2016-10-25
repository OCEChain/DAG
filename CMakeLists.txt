
cmake_minimum_required(VERSION 2.8)
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
option(dag_documentation "Whether or not to create doxygen doc target.")
option(dag_example "Whether or not to create examples")

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

