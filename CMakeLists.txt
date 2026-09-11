

cmake_minimum_required(VERSION 4.3)
project(CppVM)

set(CMAKE_CXX_STANDARD 20)

add_executable(cvm src/cvm.cpp)

add_executable(asm src/asm.cpp)

set_target_properties(cvm asm PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

target_link_options(cvm PRIVATE
        -static-libgcc
        -static-libstdc++
)

target_link_options(asm PRIVATE
        -static-libgcc
        -static-libstdc++
)
