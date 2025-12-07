cmake_minimum_required(VERSION 3.10)

add_library(slib SHARED)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.c"
)

target_sources(slib PRIVATE ${SRC_FILES})

target_include_directories(slib PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

set_target_properties(slib PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
    VERSION 1.0
    SOVERSION 1
)
