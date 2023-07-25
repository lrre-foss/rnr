add_library(Engine STATIC
    # ArkNet
    Header/Network/ArkNet/ArkStream.hpp         
    Header/Network/ArkNet/ArkSocket.hpp         
    Header/Network/ArkNet/ArkServer.hpp
    Header/Network/ArkNet/ArkAddress.hpp
    Header/Network/ArkNet/ArkPacket.hpp
    Header/Network/ArkNet/ArkPacketFactory.hpp
    Header/Network/ArkNet/ArkPeer.hpp
    Header/Network/ArkNet/Packets.hpp
    Header/Network/ArkNet/PlatformNeutralSockets.hpp

    Source/Network/ArkNet/ArkStream.cpp
    Source/Network/ArkNet/ArkSocket.cpp
    Source/Network/ArkNet/ArkServer.cpp
    Source/Network/ArkNet/ArkAddress.cpp
    Source/Network/ArkNet/ArkPacket.cpp
    Source/Network/ArkNet/ArkPacketFactory.cpp
    Source/Network/ArkNet/ArkPeer.cpp
    Source/Network/ArkNet/Packets.cpp

    # Engine
    Header/Helpers/Name.hpp
    Header/Helpers/Strings.hpp
    Header/Helpers/XML.hpp
    Header/Helpers/NormalId.hpp
    Header/Helpers/Bullet.hpp
    Header/Helpers/Lock.hpp
    Header/App/Script/ReflectionProperty.hpp
    Header/App/Script/Script.hpp
    Header/App/Script/ScriptContext.hpp
    Header/App/GUI/GuiBase3d.hpp
    Header/App/GUI/InstanceAdornment.hpp
    Header/App/GUI/SelectionBox.hpp
    Header/App/GUI/TopMenuBar.hpp
    Header/App/Humanoid/Humanoid.hpp
    Header/App/V8/DataModel/Camera.hpp
    Header/App/V8/DataModel/DataModel.hpp
    Header/App/V8/DataModel/ForceField.hpp
    Header/App/V8/DataModel/PartInstance.hpp
    Header/App/V8/DataModel/Light.hpp
    Header/App/V8/DataModel/Lighting.hpp
    Header/App/V8/DataModel/FaceInstance.hpp
    Header/App/V8/DataModel/RunService.hpp
    Header/App/V8/DataModel/Workspace.hpp
    Header/App/V8/Tree/Instance.hpp
    Header/App/V8/Tree/InstanceFactory.hpp
    Header/App/V8/Tree/PVInstance.hpp
    Header/App/V8/Tree/ModelInstance.hpp
    Header/App/V8/World/World.hpp
    Header/App/V8/World/Weld.hpp
    Header/App/V8/World/JointsService.hpp
    Header/App/V8/World/JointInstance.hpp    
    Header/App/V8/World/ComPlicitNgine.hpp
    Header/App/CoordinateFrame.hpp
    Header/App/BrickColor.hpp
    Header/App/InputManager.hpp
    Header/Network/NetworkPeer.hpp
    Header/Network/NetworkClient.hpp
    Header/Network/NetworkServer.hpp
    Header/Network/GUID.hpp
    Header/Network/Player.hpp
    Header/Network/Players.hpp
    Header/Rendering/Adorn.hpp

    Source/Helpers/Name.cpp
    Source/Helpers/Strings.cpp
    Source/Helpers/XML.cpp
    Source/Helpers/NormalId.cpp
    Source/Helpers/Bullet.cpp
    Source/App/Script/ReflectionProperty.cpp
    Source/App/Script/Script.cpp
    Source/App/GUI/GuiBase3d.cpp
    Source/App/GUI/InstanceAdornment.cpp
    Source/App/GUI/SelectionBox.cpp
    Source/App/GUI/TopMenuBar.cpp
    Source/App/Humanoid/Humanoid.cpp
    Source/App/V8/DataModel/Camera.cpp
    Source/App/V8/DataModel/DataModel.cpp
    Source/App/V8/DataModel/ForceField.cpp
    Source/App/V8/DataModel/PartInstance.cpp
    Source/App/V8/DataModel/Light.cpp
    Source/App/V8/DataModel/Lighting.cpp
    Source/App/V8/DataModel/FaceInstance.cpp
    Source/App/V8/DataModel/RunService.cpp
    Source/App/V8/DataModel/Workspace.cpp
    Source/App/V8/Tree/Instance.cpp
    Source/App/V8/Tree/InstanceFactory.cpp
    Source/App/V8/Tree/PVInstance.cpp    
    Source/App/V8/Tree/ModelInstance.cpp    
    Source/App/CoordinateFrame.cpp
    Source/App/BrickColor.cpp
    Source/App/InputManager.cpp
    Source/App/V8/World/World.cpp
    Source/App/V8/World/Weld.cpp
    Source/App/V8/World/JointsService.cpp
    Source/App/V8/World/JointInstance.cpp    
    Source/App/V8/World/ComPlicitNgine.cpp
    Source/Network/NetworkPeer.cpp
    Source/Network/NetworkClient.cpp
    Source/Network/NetworkServer.cpp
    Source/Network/GUID.cpp
    Source/Network/Player.cpp
    Source/Network/Players.cpp
    Source/Rendering/Adorn.cpp
)

if(WIN32)
    set(SOCKET_LIBRARIES wsock32 ws2_32)
endif()
target_include_directories(Engine PUBLIC ${Boost_INCLUDE_DIRS} ${BULLET_ROOT_DIR}/${BULLET_INCLUDE_DIR} Header/)
target_compile_definitions(Engine PUBLIC ${BULLET_DEFINITIONS})
target_link_directories(Engine PUBLIC ${Bullet_DIR}/${BULLET_ROOT_DIR}/${BULLET_LIBRARY_DIRS})
target_link_libraries(Engine PUBLIC ${Boost_LIBRARIES} ${RNR_BULLET_LIBRARIES} pugixml OgreBites Luau.Analysis Luau.Ast Luau.Compiler Luau.VM ${SOCKET_LIBRARIES})