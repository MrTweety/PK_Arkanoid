cmake_minimum_required(VERSION 3.9)
project(Arkanoid)

set(CMAKE_CXX_STANDARD 11)

add_executable(Arkanoid main.cpp Ball.cpp Ball.h Block.cpp Block.h Game.cpp Game.h Paddle.cpp Paddle.h)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Arkanoid ${SFML_LIBRARIES})
endif()