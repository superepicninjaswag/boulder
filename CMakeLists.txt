cmake_minimum_required(VERSION 3.27.7)

project(Boulder)

file(GLOB_RECURSE MY_SOURCES "src/*.cpp")

find_package(SDL2 REQUIRED COMPONENTS SDL2)
add_executable(boulder ${MY_SOURCES})
target_link_libraries(boulder PRIVATE SDL2::SDL2)

set_target_properties(boulder PROPERTIES
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH "/Library/Frameworks"
)