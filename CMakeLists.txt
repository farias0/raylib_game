# https://github.com/raysan5/raylib/wiki/Working-with-CMake


cmake_minimum_required(VERSION 3.15) # required by raylib

project(space_invaders)

find_package(raylib 4.5 REQUIRED)

set(CMAKE_C_STANDARD 11) # required by raylib

add_executable(${PROJECT_NAME} src/game.c src/player.c src/bullet.c src/enemy.c)

set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

# required by raylib
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()