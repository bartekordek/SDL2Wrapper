#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

project(sdl2wrapper_main)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory( deps/CUL )

list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/deps/CUL/cmake_modules )
list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules )

# PARENT_SCOPE!!!!!!!!!
# https://stackoverflow.com/questions/6891447/cmake-variable-scope-add-subdirectory

set( SDL2W_ROOT ${CMAKE_CURRENT_SOURCE_DIR} )
set( ENV{SDL2W_ROOT} ${CMAKE_CURRENT_SOURCE_DIR} )
set( SDL2W_BUILD_ROOT ${CMAKE_SOURCE_DIR} )
message( "SDL2W_BUILD_ROOT: ${SDL2W_BUILD_ROOT}" )
if( MSVC )
    set( SDL2W_OUTPUT_DIR ${SDL2W_BUILD_ROOT}/Build-Windows )
    set( MAIN_OUTPUT_DIR ${SDL2W_BUILD_ROOT}/Build-Windows )
else()
    set( SDL2W_OUTPUT_DIR ${SDL2W_BUILD_ROOT}/Build-Linux )
    set( MAIN_OUTPUT_DIR ${SDL2W_BUILD_ROOT}/Build-Linux )
endif()

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SDL2W_OUTPUT_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SDL2W_OUTPUT_DIR} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SDL2W_OUTPUT_DIR} )


set( SDL2W_BINARY_DIRECTORY ${SDL2W_OUTPUT_DIR}/${CMAKE_BUILD_TYPE} )
set( ENV{SDL2W_BINARY_DIRECTORY} ${SDL2W_BINARY_DIRECTORY} )

set( SDL2W_TESTS_RUN_DIR ${SDL2W_ROOT}/runDir )
set( ENV{SDL2W_TESTS_RUN_DIR} ${SDL2W_TESTS_RUN_DIR} )
set( ENV{SDL2W_ROOT} ${SDL2W_ROOT} )
set( ENV{SDL2W_DLL} ${SDL2W_TESTS_RUN_DIR} )
message( "[sdl2wrapper] Setting SDL2W_TESTS_RUN_DIR to: ${SDL2W_TESTS_RUN_DIR}" )

set( SDL2W_DEPS ${SDL2W_ROOT}/deps )

#option( LIBC "Use the system C library" true )
option( SDL_STATIC_PIC "PIC for SDL" true )
add_subdirectory( deps/sdl2-repo )
add_subdirectory( libsdl2wrapper )
add_subdirectory( libsdl2wrapperTestApp )