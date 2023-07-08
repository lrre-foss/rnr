project(Player)

create_resources(Resource ${CMAKE_BINARY_DIR}/PlayerResources.hpp)

qt_add_executable(Player
    Header/MainWindow.hpp

    Source/main.cpp
    Source/MainWindow.cpp
)

target_include_directories(Player PRIVATE Header)
target_link_libraries(Player PRIVATE Common Engine)