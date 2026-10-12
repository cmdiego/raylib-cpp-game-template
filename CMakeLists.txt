cmake_minimum_required(VERSION 3.20)
project(raylib-cpp-game-template LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Warnings
if (MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Source files
file(GLOB_RECURSE GAME_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE GAME_HEADERS "${CMAKE_SOURCE_DIR}/include/*.hpp")

add_executable(${PROJECT_NAME} ${GAME_SOURCES} ${GAME_HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")

# --- Raylib ---
set(RAYLIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(RAYLIB_LIBRARY     "${CMAKE_SOURCE_DIR}/lib/libraylib.a")

if (NOT EXISTS "${RAYLIB_INCLUDE_DIR}/raylib.h")
    message(FATAL_ERROR "raylib.h not found in inc/")
endif()
if (NOT EXISTS "${RAYLIB_LIBRARY}")
    message(FATAL_ERROR "libraylib.a not found in lib/")
endif()

add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES
    IMPORTED_LOCATION "${RAYLIB_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${RAYLIB_INCLUDE_DIR}"
)

# Link platform-specific
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib
        -static-libgcc -static-libstdc++
        opengl32 gdi32 winmm
    )
elseif (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else() # Linux/Unix
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib
        m pthread dl rt X11
    )
endif()
