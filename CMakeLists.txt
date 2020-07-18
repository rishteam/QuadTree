cmake_minimum_required(VERSION 3.16)
project(QuadTree)

set(CMAKE_CXX_STANDARD 17)

add_executable(QuadTree main.cpp helper.cpp helper.h quadtree.cpp quadtree.h shape.cpp shape.h Body.cpp Body.h)

find_package(fmt REQUIRED)
target_link_libraries(QuadTree fmt::fmt)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(QuadTree sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

find_package(ImGui-SFML REQUIRED)
target_link_libraries(QuadTree ImGui-SFML::ImGui-SFML)

find_package(glm REQUIRED)
target_link_libraries(QuadTree glm)