cmake_minimum_required(VERSION 3.10)

project(CLitBot VERSION 1.0)

find_package(PkgConfig REQUIRED)

pkg_check_modules(pkg REQUIRED IMPORTED_TARGET raylib)

add_executable(${PROJECT_NAME} ./src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::pkg)

