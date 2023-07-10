project(Server)

create_resources(Resource ${CMAKE_BINARY_DIR}/Resources/ServerResources.hpp)

add_executable(Server
    ${CMAKE_BINARY_DIR}/Resources/ServerResources.hpp
    
    Source/main.cpp
)

add_custom_command(TARGET Server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:Server> $<TARGET_RUNTIME_DLLS:Server>
    COMMAND_EXPAND_LISTS
)

target_include_directories(Server PRIVATE Header)
target_link_libraries(Server PRIVATE Engine)