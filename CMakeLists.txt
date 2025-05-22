cmake_minimum_required(VERSION 3.16)
project(Boulder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# macOS: Add /Library/Frameworks for framework-based SDL installs
if(APPLE)
    set(CMAKE_FRAMEWORK_PATH "/Library/Frameworks" ${CMAKE_FRAMEWORK_PATH})
endif()

# Use the official SDL3 CMake config (system install or vcpkg)
find_package(SDL3 REQUIRED CONFIG)

add_executable(Boulder main.cpp)

# Link the SDL3 target
target_link_libraries(Boulder PRIVATE SDL3::SDL3)
