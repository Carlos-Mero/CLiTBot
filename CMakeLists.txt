# basic information
cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
project(CLiTBot VERSION 1.0)

# source directories
aux_source_directory(./src DIR_SRCS)
include_directories(./include)
include_directories(./include/raylib-cpp)
include_directories(./include/raygui)

# find packages used in our project
if(APPLE)
	find_package(PkgConfig REQUIRED)
	pkg_check_modules(raylib REQUIRED IMPORTED_TARGET raylib)
endif()

if(Unix)
	find_package(PkgConfig REQUIRED)
	pkg_check_modules(raylib REQUIRED IMPORTED_TARGET raylib)
endif()

if(WIN32)
	find_package(raylib CONFIG REQUIRED)
endif()

# generate the executable
add_executable(${PROJECT_NAME} ${DIR_SRCS})

# link instructions
if(APPLE)
	target_link_libraries(${PROJECT_NAME} PUBLIC PkgConfig::raylib)
endif()

if(UNIX)
	target_link_libraries(${PROJECT_NAME} PUBLIC PkgConfig::raylib)
endif()

if(WIN32)
	target_link_libraries(${PROJECT_NAME} PUBLIC raylib::raylib)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
