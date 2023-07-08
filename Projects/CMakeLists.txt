include_directories(Engine/Header)

add_subdirectory(${DEPENDENCIES_DIR}/Luau Build)

add_subdirectory(Engine)
add_subdirectory(Client)
