cmake_minimum_required(VERSION 3.10)
project(t_clibs LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Build compile_commands.json

add_subdirectory(slib)

#
#
# set(CMAKE_C_STANDARD 99)
# set(LIB_NAME t_clibs)
#
# file(GLOB_RECURSE SRC_FILES 
#     "source/slib/*.c"
# )
#
# # 添加库目标（静态库）
# add_library(${LIB_NAME} STATIC ${SRC_FILES})
#
# target_include_directories(${LIB_NAME} PUBLIC 
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
# )
#
# set_target_properties(${LIB_NAME} PROPERTIES
#     C_STANDARD 99
#     C_STANDARD_REQUIRED ON
# )
#
