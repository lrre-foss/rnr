project(Engine)

include_directories(Engine/Header)

add_library(Engine STATIC
    Header/Helpers/Name.hpp
    Header/Helpers/Strings.hpp
    Header/App/Humanoid/Humanoid.hpp
    Header/App/V8/DataModel/ForceField.hpp
    Header/App/V8/World/World.hpp
    Header/Network/GUID.hpp
    Header/Rendering/Adorn.hpp

    Source/Helpers/Name.cpp
    Source/Helpers/Strings.cpp
    Source/App/Humanoid/Humanoid.cpp
    Source/App/V8/DataModel/ForceField.cpp
    Source/App/V8/World/World.cpp
    Source/Network/GUID.cpp
    Source/Rendering/Adorn.cpp
)

target_include_directories(Engine PUBLIC Header)
target_link_libraries(Engine PUBLIC ${BOOST_LIBRARIES} cglm Luau.Analysis Luau.Ast Luau.Compiler Luau.VM)