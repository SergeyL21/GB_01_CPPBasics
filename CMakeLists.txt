cmake_minimum_required(VERSION 3.1.0)

project(GB_CppBasics)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
  main.cpp
  game.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
