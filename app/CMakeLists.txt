cmake_minimum_required(VERSION 3.1.0)

project(app)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(MOC_HEADER_FILES
  main_window.h
)

set(MOC_UI_FILES
  main_window.ui
)

set(SOURCE_FILES
  main.cpp
  main_window.cpp
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${MOC_HEADER_FILES} ${MOC_UI_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE
  Qt5::Widgets
  hw
)
