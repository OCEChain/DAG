#Set compiler flags

#Set compiler flags

#mkdir build
#cd build
#cmake -G Xcode ..
#cmake ..

cmake_minimum_required(VERSION 3.3)
project(DAG_examples)

#Set compiler flags
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/papas
        ${CMAKE_CURRENT_SOURCE_DIR}/examples
)
#file(GLOB headers examples/*.h papas/DirectedAcyclicGraph.h)
add_executable(DAG_id examples/DAG_example_longidnode.cpp   examples/simpleidentifier.cpp )
add_executable(DAG_poly examples/DAG_example_polymorphic.cpp )
add_executable(DAG_pair examples/example_dag_pair.cpp )

target_link_libraries(DAG_id )
target_link_libraries(DAG_poly )
target_link_libraries(DAG_pair )

#If the Boost Package is found then the fianl example can be compiled.
#this should come from env variables
#set(BOOST_ROOT /usr/local/boost_1_59_0)
find_package(Boost)
if (Boost_FOUND)
include_directories( ${Boost_INCLUDE_DIRS} )
add_executable(DAG_any examples/DAG_example_boostany.cpp  )
target_link_libraries(DAG_any )
endif()

