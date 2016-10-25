
cmake_minimum_required(VERSION 2.8)
project(DAG_examples)


include_directories(
        ${CMAKE_SOURCE_DIR}/dag/
        ${CMAKE_CURRENT_SOURCE_DIR}
)
file(GLOB headers *.h)

add_executable(DAG_id DAG_example_idnode.cpp   ${headers})
add_executable(DAG_poly DAG_example_polymorphic.cpp )
add_executable(DAG_pair example_dag_pair.cpp )

target_link_libraries(DAG_id )
target_link_libraries(DAG_poly )
target_link_libraries(DAG_pair )

