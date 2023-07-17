list(APPEND SOURCE
    Source/GL/Adorn.cpp
    Source/OgreWidget.cpp
)

list(APPEND HEADER
    Header/GL/Adorn.hpp
    Header/GL/RenderContext.hpp
    Header/OgreWidget.hpp
)

qt_standard_project_setup()
qt_add_library(Common STATIC ${SOURCE} ${HEADER})

if(WIN32)
    add_custom_command(TARGET Common POST_BUILD
        COMMAND ${TOOL_WINDEPLOYQT}
                $<TARGET_FILE:Common>
        COMMENT "Running windeployqt..."
    )
endif()

target_include_directories(Common PUBLIC Header)
target_link_libraries(Common PUBLIC ${QT6_LIBRARIES_INCL} Engine)