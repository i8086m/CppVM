

cmake_minimum_required(VERSION 4.3)
project(CppVM)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cvm src/cvm.c
        src/cvm/fio.c
        src/cvm/fio.h
        src/cvm/config.h
        src/cvm/state.c
        src/cvm/state.h
        src/cvm/xplatformio.c
        src/cvm/xplatformio.h)

add_executable(asm src/asm.cpp)


target_link_options(cvm PRIVATE
        -static-libgcc
)

target_link_options(asm PRIVATE
        -static-libgcc
        -static-libstdc++
)

set_target_properties(cvm asm PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)