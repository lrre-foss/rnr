project(GLAD)

add_library(GLAD STATIC
    Header/glad/glad.h
    Header/KHR/khrplatform.h

    Source/glad.c
)

target_include_directories(GLAD PUBLIC Header)