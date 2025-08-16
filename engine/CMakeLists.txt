cmake_minimum_required(VERSION 3.31)

# Set the project name and version
project(PlatEngine)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Gather source files
file(GLOB_RECURSE ENGINE_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Set the Executable target
add_library(${PROJECT_NAME} STATIC
        ${ENGINE_SRC}
)

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

include(FetchContent)

# SDL 3
fetchcontent_declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.2.20
        GIT_SHALLOW TRUE
)

fetchcontent_makeavailable(SDL3)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

# Spdlog
fetchcontent_declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.15.3
        GIT_SHALLOW TRUE
)

fetchcontent_makeavailable(spdlog)

target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)

# Set RESOURCES_PATH macro based on build type
if (PRODUCTION_BUILD)
    target_compile_definitions(${PROJECT_NAME} PUBLIC RESOURCES_PATH="./assets/")
    target_compile_definitions(${PROJECT_NAME} PUBLIC PRODUCTION_BUILD=1)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
else ()
    target_compile_definitions(${PROJECT_NAME} PUBLIC RESOURCES_PATH="${CMAKE_SOURCE_DIR}/assets/")
    target_compile_definitions(${PROJECT_NAME} PUBLIC PRODUCTION_BUILD=0)
endif ()

# MSVC specific options
if (MSVC)
    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    target_compile_definitions(${PROJECT_NAME} PUBLIC _CRT_SECURE_NO_WARNINGS)
    add_compile_options(/arch:AVX2)
endif ()
