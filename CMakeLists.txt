cmake_minimum_required(VERSION 3.5)
project(MusicPlayer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core WebEngineWidgets REQUIRED)

add_executable(MusicPlayer main.cpp)

target_link_libraries(MusicPlayer PRIVATE 
    Qt6::Core 
    Qt6::WebEngineWidgets
)

if(WIN32)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

    add_custom_command(TARGET MusicPlayer POST_BUILD
        COMMAND ${Qt6_DIR}/../../../bin/windeployqt.exe
        --verbose 1
        --no-compiler-runtime
        --no-webkit2
        --no-angle
        --no-opengl-sw
        "$<TARGET_FILE:MusicPlayer>"
        COMMENT "Deploying Qt libraries..."
    )
endif()
