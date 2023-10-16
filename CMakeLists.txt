cmake_minimum_required(VERSION 3.16.3)

project(nv_ecs VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(
  -fsanitize=address
  -g
)
add_link_options(
  -fsanitize=address
)

add_library(ecs STATIC)
target_sources(ecs PUBLIC
  Component/IComponentBucket.cpp
  System/System.cpp
  World.cpp
)

target_include_directories(ecs PUBLIC
  Component
  Entity
)

add_executable(test)
target_sources(test PUBLIC test.cpp System/PrintSystem.cpp)
target_link_libraries(test PUBLIC ecs)
