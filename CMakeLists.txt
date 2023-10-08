cmake_minimum_required(VERSION 3.27.7)
set(CMAKE_CXX_STANDARD 17)

project(Boulder)

file(GLOB_RECURSE MY_SOURCES "src/*.cpp")

find_package(SDL2 REQUIRED COMPONENTS SDL2)
find_package(SDL2_ttf REQUIRED)

add_executable(boulder ${MY_SOURCES})
target_link_libraries(boulder PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf)

set_target_properties(boulder PROPERTIES
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH "/Library/Frameworks"
)