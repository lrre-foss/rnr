project(Studio)

create_resources(Resource ${CMAKE_BINARY_DIR}/StudioResources.hpp)

qt_add_executable(Studio
    Header/MainWindow.hpp

    Source/main.cpp
    Source/MainWindow.cpp
)

target_include_directories(Studio PRIVATE Header)
target_link_libraries(Studio PRIVATE Common Engine)