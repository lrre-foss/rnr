add_library(Engine STATIC
    Header/Helpers/Name.hpp
    Header/Helpers/Strings.hpp
    Header/App/GUI/GuiBase3d.hpp
    Header/App/GUI/InstanceAdornment.hpp
    Header/App/GUI/SelectionBox.hpp
    Header/App/Humanoid/Humanoid.hpp
    Header/App/V8/DataModel/ForceField.hpp
    Header/App/V8/DataModel/BasePart.hpp
    Header/App/V8/DataModel/Workspace.hpp
    Header/App/V8/Tree/Instance.hpp
    Header/App/V8/Tree/PVInstance.hpp
    Header/App/V8/Tree/Model.hpp
    Header/App/V8/World/World.hpp
    Header/App/CoordinateFrame.hpp
    Header/Network/GUID.hpp
    Header/Rendering/Adorn.hpp

    Source/Helpers/Name.cpp
    Source/Helpers/Strings.cpp
    Source/App/GUI/GuiBase3d.cpp
    Source/App/GUI/InstanceAdornment.cpp
    Source/App/GUI/SelectionBox.cpp
    Source/App/Humanoid/Humanoid.cpp
    Source/App/V8/DataModel/ForceField.cpp
    Source/App/V8/DataModel/BasePart.cpp
    Source/App/V8/DataModel/Workspace.cpp
    Source/App/V8/Tree/Instance.cpp
    Source/App/V8/Tree/PVInstance.cpp    
    Source/App/V8/Tree/Model.cpp    
    Source/App/CoordinateFrame.cpp
    Source/App/V8/World/World.cpp
    Source/Network/GUID.cpp
    Source/Rendering/Adorn.cpp
)

target_include_directories(Engine PUBLIC ${BOOST_INCLUDE_DIRS} Header/)
target_link_libraries(Engine PUBLIC ${BOOST_LIBRARIES} OgreBites Luau.Analysis Luau.Ast Luau.Compiler Luau.VM)

if(WIN32 OR MINGW)
    file(COPY ${CMAKE_SOURCE_DIR}/Content/win32_plugins.cfg DESTINATION ${CMAKE_BINARY_DIR})
    file(RENAME ${CMAKE_BINARY_DIR}/win32_plugins.cfg ${CMAKE_BINARY_DIR}/plugins.cfg)
elseif(UNIX)
    file(COPY ${CMAKE_SOURCE_DIR}/Content/linux_plugins.cfg DESTINATION ${CMAKE_BINARY_DIR})
    file(RENAME ${CMAKE_BINARY_DIR}/linux_plugins.cfg ${CMAKE_BINARY_DIR}/plugins.cfg)
endif()

file(COPY ${CMAKE_SOURCE_DIR}/Content/RNR/ DESTINATION ${CMAKE_BINARY_DIR}/content)
file(COPY ${OGRE_MEDIA_DIR}/Main/ DESTINATION ${CMAKE_BINARY_DIR}/shaders)
file(COPY ${OGRE_MEDIA_DIR}/RTShaderLib/ DESTINATION ${CMAKE_BINARY_DIR}/shaders)
file(COPY ${OGRE_PLUGIN_DIR}/ DESTINATION ${CMAKE_BINARY_DIR}/plugins)