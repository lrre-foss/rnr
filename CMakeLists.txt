cmake_minimum_required(VERSION 3.4)

project(RNR)

set(CMAKE_CXX_STANDARD 23)

include(CMake/CreateResources.cmake)

option(COMPILE_PLAYER "Compile the RNR player" ON)
option(COMPILE_STUDIO "Compile the RNR studio" ON)
option(COMPILE_SERVER "Compile the RNR server" ON)

set(DEPENDENCIES_DIR ${CMAKE_SOURCE_DIR}/Dependencies)

find_package(Boost REQUIRED)
find_package(cglm REQUIRED CONFIG)

add_subdirectory(Projects)