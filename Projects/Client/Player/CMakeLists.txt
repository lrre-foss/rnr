create_resources(Resource ${CMAKE_BINARY_DIR}/Resource/Player.hpp)

set(CMAKE_AUTOMOC ON)

list(APPEND SOURCE 
    Source/main.cpp
    Source/MainWindow.cpp
)

list(APPEND HEADER 
    ${CMAKE_BINARY_DIR}/Resource/Player.hpp
    Header/MainWindow.hpp
)

if(WIN32)
    list(APPEND HEADER Resource/Windows/Script.rc)
endif()

qt_add_executable(Player ${SOURCE} ${HEADER})

if(WIN32 OR MINGW)
    add_custom_command(TARGET Player POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:Player> $<TARGET_RUNTIME_DLLS:Player>
        COMMAND_EXPAND_LISTS
    )
endif()

target_include_directories(Player PRIVATE Header)
target_link_libraries(Player PRIVATE Common Engine)

set_target_properties(Player PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)