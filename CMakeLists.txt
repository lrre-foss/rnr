cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)

project(rnr)

if(WIN32)
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)

set(LUAU_BUILD_CLI OFF CACHE BOOL "" FORCE)
set(LUAU_BUILD_TESTS OFF CACHE BOOL "" FORCE)

add_subdirectory(deps/luau)
add_subdirectory(deps/glad)

add_library(rnr-app OBJECT
	src/app/v8tree/_InstanceTable.cpp

	src/app/reflection/Method.cpp
	src/app/reflection/Method.hpp
	src/app/reflection/Property.cpp
	src/app/reflection/Property.hpp
	src/app/reflection/Table.cpp
	src/app/reflection/Table.hpp 
	src/app/reflection/Variant.cpp
	src/app/reflection/Variant.hpp
	src/app/script/Script.cpp
	src/app/script/Script.hpp
	src/app/script/ScriptContext.cpp
	src/app/script/ScriptContext.hpp
	src/app/v8datamodel/BasePart.cpp
	src/app/v8datamodel/BasePart.hpp
	src/app/v8datamodel/DataModel.cpp
	src/app/v8datamodel/DataModel.hpp
	src/app/v8datamodel/Model.cpp
	src/app/v8datamodel/Model.hpp
	src/app/v8tree/Instance.hpp
	src/app/v8tree/Instance.cpp
	src/app/Logger.hpp
	src/app/Logger.cpp
)

add_library(rnr-rendering OBJECT
	src/rendering/pipeline/View.cpp
	src/rendering/pipeline/View.hpp
	src/rendering/SkyBox.cpp
	src/rendering/SkyBox.hpp
)

target_include_directories(rnr-app PUBLIC
	src/app
)

target_link_libraries(rnr-app PUBLIC
	Luau.Common Luau.Ast Luau.Compiler Luau.Config Luau.Analysis Luau.CodeGen Luau.VM
)

target_include_directories(rnr-rendering PUBLIC
	src/rendering
	deps/glad/include
)

target_link_libraries(rnr-rendering PUBLIC
	glm
	rnr-app
)

project(rnr-client)

add_executable(rnr-client
	src/client/Client.cpp
)

target_link_libraries(rnr-client PRIVATE
	rnr-app
	rnr-rendering
	${SDL2_LIBRARIES}
	glad
)