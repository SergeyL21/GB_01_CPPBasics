cmake_minimum_required(VERSION 3.1.0)

project(app)

set(SOURCE_FILES
  main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)
target_link_libraries(${PROJECT_NAME} PRIVATE hw)
