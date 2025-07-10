cmake_minimum_required(VERSION 3.31)

# Set the project name and version
project(Plat_Engine LANGUAGES CXX)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#! ! ! ! ! ! !
#set this to true to ship the game!
#basically this will change the RESOURCES_PATH to be the local path
#! ! ! ! ! ! !
#DELETE THE OUT FOLDER AFTER CHANGING THIS BECAUSE VISUAL STUDIO DOESN'T SEEM TO
#RECOGNIZE THIS CHANGE AND REBUILD!
option(PRODUCTION_BUILD "Make this a production build!" OFF)
#DELETE THE OUT FOLDER AFTER CHANGING THIS BECAUSE VISUAL STUDIO DOESN'T SEEM TO
#RECOGNIZE THIS CHANGE AND REBUILD!

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Build Libraries Statically
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build as static libraries" FORCE)

# SFML specific static build settings - MUST be set before add_subdirectory
set(SFML_BUILD_SHARED_LIBS OFF CACHE BOOL "Build SFML as static libraries" FORCE)
set(SFML_USE_STATIC_STD_LIBS ON CACHE BOOL "Use static standard libraries" FORCE)
set(SFML_STATIC_LIBRARIES TRUE CACHE BOOL "Link SFML statically" FORCE)

# Box2D static build settings
set(BOX2D_BUILD_SHARED OFF CACHE BOOL "Build Box2D as static library" FORCE)
set(BOX2D_BUILD_STATIC ON CACHE BOOL "Build Box2D as static library" FORCE)

# ImGui-SFML static build settings
set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "Let ImGui-SFML find SFML" FORCE)
set(IMGUI_SFML_IMGUI_DEMO OFF CACHE BOOL "Build ImGui demo" FORCE)
set(IMGUI_SFML_BUILD_EXAMPLES OFF CACHE BOOL "Build ImGui-SFML examples" FORCE)
set(IMGUI_SFML_LINK_SYSTEM_DEPS OFF CACHE BOOL "Let ImGui-SFML link system deps" FORCE)
set(IMGUI_SFML_STATIC ON CACHE BOOL "Build ImGui-SFML statically" FORCE)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" CACHE STRING "" FORCE)
endif()

# Add external libraries
add_subdirectory(external/SFML)
add_subdirectory(external/box2d)
add_subdirectory(external/imgui)
add_subdirectory(external/spdlog)

# ImGui-SFML setup
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui)
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO OFF)
add_subdirectory(external/imgui-sfml)

# Gather source files
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Set the Executable target
add_executable(${CMAKE_PROJECT_NAME}
        ${SRC_FILES}
)

# Include directories
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        include
        external/SFML/include
        external/box2d/include
        ${IMGUI_DIR}
        external/imgui-sfml
        external/spdlog/include
)

# Set the C++ standard and link SFML libraries
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_20)
# Add static linking definitions
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
        SFML_STATIC
        SPDLOG_COMPILED_LIB
        IMGUI_SFML_STATIC
)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Audio
        SFML::Network
        box2d::box2d
        imgui
        ImGui-SFML::ImGui-SFML
        spdlog::spdlog
)

# Set RESOURCES_PATH macro based on build type
if (PRODUCTION_BUILD)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC RESOURCES_PATH="./assets/")
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC PRODUCTION_BUILD=1)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
else ()
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC RESOURCES_PATH="${CMAKE_SOURCE_DIR}/assets/")
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC PRODUCTION_BUILD=0)
endif ()

# MSVC specific options
if (MSVC)
    set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC _CRT_SECURE_NO_WARNINGS)
    add_compile_options(/arch:AVX2)
endif()

# Turn off console and logs in production mode
if(WIN32 AND PRODUCTION_BUILD)
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE TRUE
            LINK_FLAGS "/SUBSYSTEM:WINDOWS"
    )
    # Alternative for MinGW
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_options(${CMAKE_PROJECT_NAME} PRIVATE "-Wl,--subsystem,windows")
    endif()
endif()
