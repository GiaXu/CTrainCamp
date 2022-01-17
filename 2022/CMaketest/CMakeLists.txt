cmake_minimum_required(VERSION 3.0.0)
project(CMaketest VERSION 0.1.0)

IF(APPLE)
  SET(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "Build architectures for Mac OS X" FORCE)
ENDIF(APPLE)

#include(CTest)
#enable_testing()
add_library(HW HelloWorld.c)

add_executable(CMaketest main.c)

target_link_libraries(CMaketest HW)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
