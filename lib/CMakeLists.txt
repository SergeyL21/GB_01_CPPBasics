cmake_minimum_required(VERSION 3.1.0)

project(lib VERSION 1.0.0)

set(LIBRARY_NAME hw)

set(SOURCE_LIB
  hw.cpp
)

add_library(${LIBRARY_NAME} SHARED ${SOURCE_LIB})

target_compile_definitions(${LIBRARY_NAME} PRIVATE LIB_EXPORTS)
target_include_directories(${LIBRARY_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
