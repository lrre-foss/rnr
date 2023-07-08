cmake_minimum_required(VERSION 3.4)

include(cmake/resource.cmake)

project(engine)
project(player)
project(server)
project(studio)

option(COMPILE_PLAYER "Compile the RNR Player" ON)
option(COMPILE_SERVER "Compile the RNR Server" ON)
option(COMPILE_STUDIO "Compile the RNR Studio" ON)

find_package(Boost REQUIRED)
find_package(cglm REQUIRED CONFIG)

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
    src/include/engine/rendering/TextureProxyBase.hpp
)

target_include_directories(engine PUBLIC src/include ${CMAKE_BINARY_DIR})
target_link_libraries(engine PUBLIC ${BOOST_LIBRARIES} cglm)

if(COMPILE_PLAYER OR COMPILE_STUDIO)
    project(glad)
    add_library(glad STATIC
        glad/src/glad.c
        glad/include/glad/glad.h 
        glad/include/KHR/khrplatform.h
    )
    target_include_directories(glad PUBLIC glad/include)
    project(qt_common)
    find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets)
    set(QT6_LIBRARIES_INCL Qt6::Core Qt6::Gui Qt6::Widgets Qt6::OpenGLWidgets glad)
    qt_standard_project_setup()

    qt_add_library(qt_common STATIC
        src/client/common/RNRGraphicsWidget.cpp
        src/include/client/common/RNRGraphicsWidget.hpp
        src/client/common/Adorn.cpp
        src/include/client/common/Adorn.hpp
    )
    target_link_libraries(qt_common PUBLIC ${QT6_LIBRARIES_INCL} engine)
endif()

if(COMPILE_PLAYER)
    create_resources(rsc/client ${CMAKE_BINARY_DIR}/player_rsc.h)
    qt_add_executable(player
        src/client/player/main.cpp

        ${CMAKE_BINARY_DIR}/player_rsc.h
    )
    target_link_libraries(player PRIVATE qt_common engine)
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
    create_resources(rsc/studio ${CMAKE_BINARY_DIR}/studio_rsc.h)
    qt_add_executable(studio 
        src/client/studio/StudioWindow.cpp
        src/include/client/studio/StudioWindow.hpp
        src/client/studio/main.cpp

        ${CMAKE_BINARY_DIR}/studio_rsc.h
    )
    target_link_libraries(studio PRIVATE qt_common engine)
endif()