cmake_minimum_required(VERSION 3.0.0)
project(Face VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(opencv REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(Face main.cpp)

target_link_libraries( Face ${OpenCV_LIBS} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)