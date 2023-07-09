include_directories(${CMAKE_BINARY_DIR})

if(COMPILE_PLAYER OR COMPILE_STUDIO)
    find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets)
    add_subdirectory(Common)
    
    if(COMPILE_PLAYER)
        add_subdirectory(Player)
    endif()
    
    if(COMPILE_STUDIO)
        add_subdirectory(Studio)
    endif()
endif()

if(COMPILE_SERVER)
    add_subdirectory(Server)
endif()