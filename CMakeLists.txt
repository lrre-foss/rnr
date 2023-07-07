cmake_minimum_required(VERSION 3.4)

include(cmake/resource.cmake)

project(engine)
project(player)
project(server)
project(studio)

option(COMPILE_PLAYER "Compile the RBXNU Player" ON)
option(COMPILE_SERVER "Compile the RBXNU Server" ON)
option(COMPILE_STUDIO "Compile the RBXNU Studio" ON)

find_package(Boost REQUIRED)

add_library(engine STATIC
    src/engine/app/gui/Adorn.cpp
    src/include/engine/app/gui/Adorn.hpp
    src/engine/app/humanoid/Humanoid.cpp
    src/include/engine/app/humanoid/Humanoid.hpp
    src/engine/app/humanoid/Forcefield.cpp
    src/include/engine/app/humanoid/Forcefield.hpp
    src/engine/app/v8/tree/Instance.cpp
    src/include/engine/app/v8/tree/Instance.hpp
    src/engine/app/Name.cpp
    src/include/engine/app/Name.hpp
    src/engine/network/Guid.cpp
    src/include/engine/network/Guid.hpp
)

target_include_directories(engine PUBLIC src/include ${CMAKE_BINARY_DIR})
target_link_libraries(engine PUBLIC ${BOOST_LIBRARIES})

if(COMPILE_PLAYER)
    create_resources(rsc/client ${CMAKE_BINARY_DIR}/player_rsc.h)
    add_executable(player
        src/client/player/main.cpp

        ${CMAKE_BINARY_DIR}/player_rsc.h
    )
    target_link_libraries(player PRIVATE engine)
endif()

if(COMPILE_SERVER)
    create_resources(rsc/server ${CMAKE_BINARY_DIR}/server_rsc.h)
    add_executable(server
        src/client/server/main.cpp

        ${CMAKE_BINARY_DIR}/server_rsc.h
    )
    target_link_libraries(server PRIVATE engine)
endif()

if(COMPILE_STUDIO)
    find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets)
    qt_standard_project_setup()
    set(QT6_LIBRARIES_INCL Qt6::Core Qt6::Gui Qt6::Widgets Qt6::OpenGLWidgets)
    create_resources(rsc/studio ${CMAKE_BINARY_DIR}/studio_rsc.h)
    qt_add_executable(studio 
        src/client/studio/StudioWindow.cpp
        src/include/client/studio/StudioWindow.hpp
        src/client/studio/main.cpp

        ${CMAKE_BINARY_DIR}/studio_rsc.h
    )
    target_link_libraries(studio PRIVATE ${QT6_LIBRARIES_INCL} engine)
endif()
