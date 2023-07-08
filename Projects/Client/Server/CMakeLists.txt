project(Server)

create_resources(Resource ${CMAKE_BINARY_DIR}/Resources/ServerResources.hpp)

add_executable(Server
    ${CMAKE_BINARY_DIR}/Resources/ServerResources.hpp
    
    Source/main.cpp
)

target_include_directories(Server PRIVATE Header)
target_link_libraries(Server PRIVATE Engine)