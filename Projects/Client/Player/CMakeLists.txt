create_resources(Resource ${CMAKE_BINARY_DIR}/Resources/PlayerResources.hpp)

set(CMAKE_AUTOMOC ON)

qt_add_executable(Player
    ${CMAKE_BINARY_DIR}/Resources/PlayerResources.hpp

    Header/MainWindow.hpp

    Source/main.cpp
    Source/MainWindow.cpp
)

add_custom_command(TARGET Player POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:Player> $<TARGET_RUNTIME_DLLS:Player>
    COMMAND_EXPAND_LISTS
)

target_include_directories(Player PRIVATE Header)
target_link_libraries(Player PRIVATE Common Engine)

set_target_properties(Player PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)