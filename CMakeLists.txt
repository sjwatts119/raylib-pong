cmake_minimum_required(VERSION 3.20)
project(RaylibPong)

set(CMAKE_CXX_STANDARD 17)

if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES arm64)
endif()

include(cmake/CPM.cmake)

CPMAddPackage(
        NAME raylib
        GITHUB_REPOSITORY raysan5/raylib
        GIT_TAG 5.5
        OPTIONS
        "BUILD_EXAMPLES OFF"
        "BUILD_GAMES OFF"
)

include_directories(includes)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES}
        includes/board.h
        src/board.cpp
        src/ball.cpp
        includes/ball.h
        includes/side.h)
target_link_libraries(${PROJECT_NAME} raylib)

if (APPLE AND NOT CMAKE_SYSTEM STRLESS "Darwin-18.0.0")
    add_definitions(-DGL_SILENCE_DEPRECATION)
endif()