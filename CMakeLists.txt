cmake_minimum_required(VERSION 3.31)
project(sonya)

set(CMAKE_CXX_STANDARD 23)

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

CPMAddPackage(
    NAME SDL3_image
    GITHUB_REPOSITORY libsdl-org/SDL_image
    GIT_TAG release-3.2.4
)

CPMAddPackage(
    NAME fmt
    GITHUB_REPOSITORY fmtlib/fmt
    GIT_TAG 12.1.0
)

target_link_libraries(sonya SDL3::SDL3 SDL3_image::SDL3_image fmt::fmt)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(sonya X11)
    target_link_libraries(sonya Xfixes)
    target_compile_definitions(sonya PUBLIC "SONYA_LINUX")
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(sonya PUBLIC "SONYA_WINDOWS")
    if(MSVC)
        set(SUBSYSTEM_LINKER_OPTIONS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    elseif(MINGW)
        set(SUBSYSTEM_LINKER_OPTIONS "-mwindows")
        target_link_options(sonya PUBLIC
            "-static-libgcc"
            "-static-libstdc++"
        )
    endif()
    target_link_options(sonya PRIVATE ${SUBSYSTEM_LINKER_OPTIONS})
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message("macOS is currently unsupported in sonya. You are on your own.")
    target_compile_definitions(sonya PUBLIC "SONYA_MACOS")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    target_compile_definitions(sonya PUBLIC "SONYA_DEBUG")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(sonya PUBLIC "SONYA_RELEASE")
endif()