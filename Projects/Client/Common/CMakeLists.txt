add_subdirectory(${DEPENDENCIES_DIR}/GLAD ${CMAKE_BINARY_DIR}/Dependencies/GLAD)

project(Common)

qt_standard_project_setup()
qt_add_library(Common STATIC
    Header/GL/Adorn.hpp
    Header/GL/RenderContext.hpp
    Header/OgreWidget.hpp

    Source/GL/Adorn.cpp
    Source/OgreWidget.cpp
)

target_include_directories(Common PUBLIC Header)
target_link_libraries(Common PUBLIC ${QT6_LIBRARIES_INCL} Engine)