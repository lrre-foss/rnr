cmake_minimum_required(VERSION 3.4)

project(engine)
project(player)
project(server)
project(studio)

find_package(Qt6 REQUIRED COMPONENTS Core)
qt_standard_project_setup()

add_library(engine STATIC
    src/engine/app/humanoid/Humanoid.cpp
    src/include/engine/app/humanoid/Humanoid.hpp

    src/engine/app/v8/tree/Instance.cpp
    src/include/engine/app/v8/tree/Instance.hpp

    src/engine/app/Name.cpp
    src/include/engine/app/Name.hpp
)

qt_add_executable(player
    src/client/player/main.cpp
)

add_executable(server
    src/client/server/main.cpp
)

qt_add_executable(studio 
    src/client/studio/main.cpp
)

target_include_directories(engine PUBLIC include)

target_link_libraries(player PRIVATE Qt6::Core engine)
target_link_libraries(studio PRIVATE Qt6::Core engine)
target_link_libraries(server PRIVATE engine)