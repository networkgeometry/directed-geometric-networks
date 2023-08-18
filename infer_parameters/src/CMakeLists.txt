add_executable(generating_directedS1 generating_directedS1_unix.cpp)
target_link_libraries(generating_directedS1 ${CMAKE_SOURCE_DIR}/src/BaseGraph/src/libBaseGraph.a)

add_executable(fitting_directedS1 fitting_directedS1_unix.cpp)
target_link_libraries(fitting_directedS1 ${CMAKE_SOURCE_DIR}/src/BaseGraph/src/libBaseGraph.a)
