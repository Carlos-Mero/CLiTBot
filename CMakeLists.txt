cmake_minimum_required(VERSION 3.10)

project(CLitBot VERSION 1.0)

aux_source_directory(./src DIR_SRCS)

find_package(PkgConfig REQUIRED)

pkg_check_modules(pkg REQUIRED IMPORTED_TARGET raylib)

add_executable(${PROJECT_NAME} ${DIR_SRCS})

target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::pkg)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/src)
