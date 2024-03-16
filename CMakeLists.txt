cmake_minimum_required(VERSION 3.14)

add_subdirectory(ext/luau)
add_subdirectory(ext/glad)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

project(rnr)

add_library(rnr-app OBJECT
	app/v8datamodel/DataModel.cpp
	app/v8datamodel/DataModel.hpp
	app/v8tree/Instance.hpp
	app/v8tree/Instance.cpp
	app/Logger.hpp
	app/Logger.cpp
)

add_library(rnr-rendering OBJECT
	rendering/SkyBox.cpp
	rendering/SkyBox.hpp
)

target_include_directories(rnr-app PUBLIC
	app
)

target_link_libraries(rnr-app PUBLIC
	Luau.Common Luau.Ast Luau.Compiler Luau.Config Luau.Analysis Luau.CodeGen Luau.VM
)

target_include_directories(rnr-rendering PUBLIC
	rendering
)

target_link_libraries(rnr-rendering PUBLIC
	glad
)

project(rnr-client)

add_executable(rnr-client
	client/Client.cpp
)

target_link_libraries(rnr-client PRIVATE
	rnr-app
	rnr-rendering
	${SDL2_LIBRARIES}
	glad
)