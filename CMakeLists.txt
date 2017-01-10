# version information for cmake
cmake_minimum_required(VERSION 3.3)

# Project Name
project(Ludo)
set(PROJECT_LONGNAME "Ludo")
set(PROJECT_VERSION "1.0.0")

if (UNIX)
  set (CMAKE_CXX_FLAGS "-g3 -Wall -O3")
endif ()

# Include the build directory contents
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Automatically handle MOC headers
set(CMAKE_AUTOMOC ON)

# Automatically handle RCC files
set(CMAKE_AUTORCC ON)

# Automatically handle ui files
set(CMAKE_AUTOUIC ON)

# Find Qt5
find_package(Qt5Widgets REQUIRED)

# add src folder for cpp files
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_subdirectory(src)
