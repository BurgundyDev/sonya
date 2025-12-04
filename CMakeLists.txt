cmake_minimum_required(VERSION 4.0)
project(sonya)

set(CMAKE_CXX_STANDARD 26)

add_executable(sonya src/main.cpp)

target_include_directories(sonya PUBLIC include)

include(cmake/CPM.cmake)

CPMAddPackage(
    NAME SDL3
    GITHUB_REPOSITORY libsdl-org/SDL
    GIT_TAG release-3.2.26
)

target_link_libraries(sonya SDL3::SDL3)
target_link_libraries(sonya X11)
target_link_libraries(sonya Xfixes)