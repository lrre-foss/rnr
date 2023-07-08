include_directories(Engine/Header)

add_subdirectory(Engine)
add_subdirectory(Client)

add_subdirectory(${DEPENDENCIES_DIR}/Luau Build)
target_link_libraries(Engine Luau.Analysis)
target_link_libraries(Engine Luau.Ast)
target_link_libraries(Engine Luau.Compiler)
target_link_libraries(Engine Luau.VM)