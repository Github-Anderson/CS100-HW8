cmake_minimum_required(VERSION 3.16)

add_library(
  Object
  STATIC
  Sun.hpp
  Sun.cpp
  Seed.hpp
  Seed.cpp
  Plant.hpp
  Plant.cpp
  Zombie.hpp
  Zombie.cpp
  UI.hpp
  UI.cpp
  ${CMAKE_SOURCE_DIR}/src/utils.hpp
)

target_link_libraries(
  Object
  PRIVATE
  GameObject
)

target_include_directories(
  Object
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/Framework/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
  ${CMAKE_SOURCE_DIR}/src/GameWorld/
)