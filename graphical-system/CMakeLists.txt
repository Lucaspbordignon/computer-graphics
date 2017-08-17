cmake_minimum_required(VERSION 2.8)
project(graphical_system)

# Libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Headers
include_directories(include)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

# Sources
set(SOURCES main.cpp src/ViewPort.cpp)
set(CMAKE_BUILD_TYPE Debug)

# General settings
add_executable(sgi ${SOURCES})
target_link_libraries(sgi ${GTK3_LIBRARIES})

set_target_properties( sgi
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/.."
)
