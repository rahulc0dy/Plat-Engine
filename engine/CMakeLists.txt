cmake_minimum_required(VERSION 3.31)

# Set the project name and version
project(PlatEngine LANGUAGES CXX)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Gather source files
file(GLOB_RECURSE ENGINE_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Set the Executable target
add_library(PlatEngine STATIC
        ${ENGINE_SRC}
)

# Include directories
target_include_directories(PlatEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Set RESOURCES_PATH macro based on build type
if (PRODUCTION_BUILD)
    target_compile_definitions(PlatEngine PUBLIC RESOURCES_PATH="./assets/")
    target_compile_definitions(PlatEngine PUBLIC PRODUCTION_BUILD=1)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
else ()
    target_compile_definitions(PlatEngine PUBLIC RESOURCES_PATH="${CMAKE_SOURCE_DIR}/assets/")
    target_compile_definitions(PlatEngine PUBLIC PRODUCTION_BUILD=0)
endif ()

# MSVC specific options
if (MSVC)
    set_property(TARGET PlatEngine PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    target_compile_definitions(PlatEngine PUBLIC _CRT_SECURE_NO_WARNINGS)
    add_compile_options(/arch:AVX2)
endif()
