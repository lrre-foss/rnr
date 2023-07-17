create_resources(Resource ${CMAKE_BINARY_DIR}/Resource/Server.hpp)

list(APPEND SOURCE Source/main.cpp)
list(APPEND HEADER ${CMAKE_BINARY_DIR}/Resource/Server.hpp)

if(WIN32)
    list(APPEND HEADER Resource/Windows/Script.rc)
endif()

add_executable(Server ${SOURCE} ${HEADER})

if(MINGW)
    add_custom_command(TARGET Server POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:Server> $<TARGET_RUNTIME_DLLS:Server>
        COMMAND_EXPAND_LISTS
    )
endif()

target_include_directories(Server PRIVATE Header)
target_link_libraries(Server PRIVATE Engine)