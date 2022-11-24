# basic information
cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
project(CLiTBot VERSION 1.0)

# source directories
aux_source_directory(./src DIR_SRCS)
add_subdirectory(./include)
include_directories(./include)

# find packages used in our project
find_package(PkgConfig REQUIRED)
pkg_check_modules(raylib REQUIRED IMPORTED_TARGET raylib)

# generate the executable
add_executable(${PROJECT_NAME} ${DIR_SRCS})

# link instructions
target_link_libraries(${PROJECT_NAME} PUBLIC PkgConfig::raylib)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/src)
