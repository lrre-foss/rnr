cmake_minimum_required(VERSION 3.4)

project(player)
project(server)
project(studio)

add_executable(player
    src/client/player/main.cpp
)

add_executable(server
    src/client/server/main.cpp
)

add_executable(studio 
    src/client/studio/main.cpp
)