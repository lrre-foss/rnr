add_library(Engine STATIC
    Header/Helpers/Name.hpp
    Header/Helpers/Strings.hpp
    Header/App/Humanoid/Humanoid.hpp
    Header/App/V8/DataModel/ForceField.hpp
    Header/App/V8/DataModel/BasePart.hpp
    Header/App/V8/Tree/Instance.hpp
    Header/App/V8/Tree/PVInstance.hpp
    Header/App/V8/Tree/Model.hpp
    Header/App/V8/World/World.hpp
    Header/App/V8/World/Workspace.hpp
    Header/App/CoordinateFrame.hpp
    Header/Network/GUID.hpp
    Header/Rendering/Adorn.hpp

    Source/Helpers/Name.cpp
    Source/Helpers/Strings.cpp
    Source/App/Humanoid/Humanoid.cpp
    Source/App/V8/DataModel/ForceField.cpp
    Source/App/V8/DataModel/BasePart.cpp
    Source/App/V8/Tree/Instance.cpp
    Source/App/V8/Tree/PVInstance.cpp    
    Source/App/V8/Tree/Model.cpp    
    Source/App/CoordinateFrame.cpp
    Source/App/V8/World/World.cpp
    Source/App/V8/World/Workspace.cpp
    Source/Network/GUID.cpp
    Source/Rendering/Adorn.cpp
)

target_include_directories(Engine PUBLIC ${BOOST_INCLUDE_DIRS} Header/)
target_link_libraries(Engine PUBLIC ${BOOST_LIBRARIES} OgreBites Luau.Analysis Luau.Ast Luau.Compiler Luau.VM)

file(COPY ${OGRE_CONFIG_DIR}/plugins.cfg ${OGRE_CONFIG_DIR}/resources.cfg
     DESTINATION ${CMAKE_BINARY_DIR})
