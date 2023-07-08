project(Server)

create_resources(Resources ${CMAKE_BINARY_DIR}/ServerResources.hpp)

add_executable(Server
    Source/main.cpp
)

target_include_directories(Server PRIVATE Header)
target_link_libraries(Server PRIVATE Engine)