cmake_minimum_required(VERSION 4.0)
project(sonya)

set(CMAKE_CXX_STANDARD 26)

add_executable(sonya src/main.cpp
        src/win_utils.cpp
        src/linux_utils.cpp
        src/sonya_utils.cpp)

target_include_directories(sonya PUBLIC include)

include(cmake/CPM.cmake)

CPMAddPackage(
    NAME SDL3
    GITHUB_REPOSITORY libsdl-org/SDL
    GIT_TAG release-3.2.26
)

target_link_libraries(sonya SDL3::SDL3)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(sonya X11)
    target_link_libraries(sonya Xfixes)
    target_compile_definitions(sonya PUBLIC "SONYA_LINUX")
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(sonya PUBLIC "SONYA_WINDOWS")
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message("macOS is currently unsupported in sonya. You are on your own.")
    target_compile_definitions(sonya PUBLIC "SONYA_MACOS")
endif()