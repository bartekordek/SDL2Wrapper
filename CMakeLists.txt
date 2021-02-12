#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

project(sdl2wrapper_main)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory( deps/CUL )
message( "[sdl2wrapper] CUL_ROOT_DIR = $ENV{CUL_ROOT_DIR}" )
message( "[sdl2wrapper] GLM_INCLUDE_DIR = $ENV{GLM_INCLUDE_DIR}" )
message( "[sdl2wrapper] GLM_INCLUDE_DIRS = $ENV{GLM_INCLUDE_DIRS}" )

message( "[sdl2wrapper] CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}" )
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/deps/sdl2-repo )
message( "[sdl2wrapper] CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}" )
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/deps/CUL/cmake_modules" )
message( "[sdl2wrapper] CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}" )

# PARENT_SCOPE!!!!!!!!!
# https://stackoverflow.com/questions/6891447/cmake-variable-scope-add-subdirectory


set( SDL2W_ROOT ${CMAKE_CURRENT_SOURCE_DIR} )
set( ENV{SDL2W_ROOT} ${CMAKE_CURRENT_SOURCE_DIR} )
if( MSVC )
    set( SDL2W_OUTPUT_DIR ${SDL2W_ROOT}/Build-Windows )
else()
    set( SDL2W_OUTPUT_DIR ${SDL2W_ROOT}/Build-Linux )
endif()
message( "[sdl2wrapper] Setting SDL2W_OUTPUT_DIR to: ${SDL2W_OUTPUT_DIR}" )

set( SDL2W_TESTS_RUN_DIR ${SDL2W_ROOT}/runDir )
set( ENV{SDL2W_TESTS_RUN_DIR} ${SDL2W_TESTS_RUN_DIR} )
set( ENV{SDL2W_ROOT} ${SDL2W_ROOT} )
set( ENV{SDL2W_DLL} ${SDL2W_TESTS_RUN_DIR} )
message( "[sdl2wrapper] Setting SDL2W_TESTS_RUN_DIR to: ${SDL2W_TESTS_RUN_DIR}" )

set( SDL2W_DEPS ${SDL2W_ROOT}/deps )

# Add sub directories

add_subdirectory( deps/sdl2-repo )
add_subdirectory( libsdl2wrapper )
add_subdirectory( libsdl2wrapperTestApp )