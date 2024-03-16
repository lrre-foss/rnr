cmake_minimum_required(VERSION 3.14)

add_subdirectory(ext/luau)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

project(rnr)

add_library(rnr-app OBJECT
	app/v8tree/Instance.hpp
	app/v8tree/Instance.cpp
	app/Logger.hpp
	app/Logger.cpp
)

target_include_directories(rnr-app PUBLIC
	app
)

target_link_libraries(rnr-app PUBLIC
	Luau.Common Luau.Ast Luau.Compiler Luau.Config Luau.Analysis Luau.CodeGen Luau.VM
)

project(rnr-client)

add_executable(rnr-client
	client/Client.cpp
)

target_link_libraries(rnr-client PRIVATE
	rnr-app
	${SDL2_LIBRARIES}
)