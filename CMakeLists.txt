cmake_minimum_required(VERSION 3.10.0) 
project(bisakol)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

file(GLOB SRCS
    "${PROJECT_SOURCE_DIR}/include/*"
    "${PROJECT_SOURCE_DIR}/src/*"
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
add_executable(app ${SRCS})
