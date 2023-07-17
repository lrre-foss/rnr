create_resources(Resource ${CMAKE_BINARY_DIR}/Resource/Studio.hpp)

set(CMAKE_AUTOMOC ON)

list(APPEND SOURCE
    Source/main.cpp
    Source/MainWindow.cpp
)

list(APPEND HEADER
    ${CMAKE_BINARY_DIR}/Resource/Studio.hpp
    Header/MainWindow.hpp
)

if(WIN32)
    list(APPEND HEADER Resource/Windows/Script.rc)
endif()

qt_add_executable(Studio ${SOURCE} ${HEADER})


target_include_directories(Studio PRIVATE Header)
target_link_libraries(Studio PRIVATE Common Engine)

set_target_properties(Studio PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

install(TARGETS Studio 
        RUNTIME_DEPENDENCIES)