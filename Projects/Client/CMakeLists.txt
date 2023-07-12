include_directories(${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if(COMPILE_PLAYER OR COMPILE_STUDIO)
    if(LINUX)
        include(/usr/share/cmake/Modules/FindX11.cmake)
    endif()
    find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets)
    set(QT6_LIBRARIES_INCL Qt6::Core Qt6::Gui Qt6::Widgets Qt6::OpenGLWidgets Qt6::GuiPrivate ${X11_X11_LIB})
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