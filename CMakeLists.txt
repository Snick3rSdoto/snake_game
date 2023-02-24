cmake_minimum_required(VERSION 3.0.0)
project(CMakeT1 VERSION 0.1.0)

include(CTest)
enable_testing()
#4
add_executable(CMakeT1 main.cpp)
target_link_libraries(CMakeT1 sfml-graphics sfml-window sfml-system)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
