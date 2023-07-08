if(COMPILE_PLAYER OR COMPILE_STUDIO)
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