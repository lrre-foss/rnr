add_subdirectory(${DEPENDENCIES_DIR}/GLAD Build)

project(Common)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets)
set(QT6_LIBRARIES_INCL Qt6::Core Qt6::Gui Qt6::Widgets Qt6::OpenGLWidgets glad)

qt_standard_project_setup()
qt_add_library(Common STATIC
    Header/GL/Adorn.hpp
    Header/GL/RenderContext.hpp
    Header/GL/Widget.hpp

    Source/GL/Adorn.cpp
    Source/GL/Widget.cpp
)

include_directories(Header)
target_link_libraries(Common PUBLIC ${QT6_LIBRARIES_INCL} Engine)