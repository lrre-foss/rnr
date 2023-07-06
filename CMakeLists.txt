cmake_minimum_required(VERSION 3.4)

project(Engine)
project(RBXNuServer)
project(RBXNuStudio)
project(RBXNuPlayer)

add_library(Engine STATIC
    roblox/engine/RBXNu.cpp
)

add_executable(RBXNuServer
    roblox/server/RBXNuServer.cpp
)

add_executable(RBXNuStudio 
    roblox/studio/RBXNuStudio.cpp
)

add_executable(RBXNuPlayer
    roblox/player/RBXNuPlayer.cpp
)

target_link_libraries(RBXNuServer
    Engine
)

target_link_libraries(RBXNuStudio
    Engine 
)

target_link_libraries(RBXNuPlayer
    Engine
)