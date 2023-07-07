cmake_minimum_required(VERSION 3.4)

project(engine)
project(player)
project(server)
project(studio)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets)
find_package(Boost REQUIRED)
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
    src/client/studio/studiowindow.cpp
    src/client/studio/studiowindow.hpp
    src/client/studio/main.cpp
)

target_include_directories(engine PUBLIC src/include)
target_link_libraries(engine PUBLIC ${BOOST_LIBRARIES})

set(QT6_LIBRARIES_INCL Qt6::Core Qt6::Gui Qt6::Widgets Qt6::OpenGLWidgets)
target_link_libraries(player PRIVATE ${QT6_LIBRARIES_INCL} engine)
target_link_libraries(studio PRIVATE ${QT6_LIBRARIES_INCL} engine)
target_link_libraries(server PRIVATE engine)