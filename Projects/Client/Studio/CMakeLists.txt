project(Studio)

create_resources(Resource ${CMAKE_BINARY_DIR}/Resources/StudioResources.hpp)

set(CMAKE_AUTOMOC ON)

qt_add_executable(Studio
    ${CMAKE_BINARY_DIR}/Resources/StudioResources.hpp

    Header/MainWindow.hpp

    Source/main.cpp
    Source/MainWindow.cpp
)

target_include_directories(Studio PRIVATE Header)
target_link_libraries(Studio PRIVATE Common Engine)

set_target_properties(Studio PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)