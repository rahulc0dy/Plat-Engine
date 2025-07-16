cmake_minimum_required(VERSION 3.31)

# Set the project name and version
project(PlatEditor LANGUAGES CXX)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Gather source files
file(GLOB_RECURSE EDITOR_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Set the Executable target
add_executable(PlatEditor
        ${EDITOR_SRC}
)

# Include directories
target_include_directories(PlatEditor PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/external/SFML/include
        ${CMAKE_SOURCE_DIR}/external/box2d/include
        ${CMAKE_SOURCE_DIR}/external/imgui
        ${CMAKE_SOURCE_DIR}/external/imgui-sfml
        ${CMAKE_SOURCE_DIR}/external/spdlog/include
)

# Link dependencies
target_link_libraries(PlatEditor PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Audio
        SFML::Network
        box2d::box2d
        imgui
        ImGui-SFML::ImGui-SFML
        spdlog::spdlog

        PlatEngine
)

# Set the C++ standard and link SFML libraries
target_compile_features(PlatEditor PRIVATE cxx_std_20)
# Add static linking definitions
target_compile_definitions(PlatEditor PRIVATE
        SFML_STATIC
        SPDLOG_COMPILED_LIB
        IMGUI_SFML_STATIC
)

# Set RESOURCES_PATH macro based on build type
if (PRODUCTION_BUILD)
    target_compile_definitions(PlatEditor PUBLIC RESOURCES_PATH="./assets/")
    target_compile_definitions(PlatEditor PUBLIC PRODUCTION_BUILD=1)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
else ()
    target_compile_definitions(PlatEditor PUBLIC RESOURCES_PATH="${CMAKE_SOURCE_DIR}/assets/")
    target_compile_definitions(PlatEditor PUBLIC PRODUCTION_BUILD=0)
endif ()

# MSVC specific options
if (MSVC)
    set_property(TARGET PlatEditor PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    target_compile_definitions(PlatEditor PUBLIC _CRT_SECURE_NO_WARNINGS)
    add_compile_options(/arch:AVX2)
endif ()

# Turn off console and logs in production mode
if (WIN32 AND PRODUCTION_BUILD)
    set_target_properties(PlatEditor PROPERTIES
            WIN32_EXECUTABLE TRUE
            LINK_FLAGS "/SUBSYSTEM:WINDOWS"
    )
    # Alternative for MinGW
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_options(PlatEditor PRIVATE "-Wl,--subsystem,windows")
    endif ()
endif ()
