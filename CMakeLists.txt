#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

project(sdl2wrapper_main)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set( SDL2W_ROOT ${CMAKE_CURRENT_SOURCE_DIR} )
if( MSVC )
    set( SDL2W_OUTPUT_DIR ${SDL2W_ROOT}/Build-Windows )
else()
    set( SDL2W_OUTPUT_DIR ${SDL2W_ROOT}/Build-Linux )
endif()
message( "Setting SDL2W_OUTPUT_DIR to: ${SDL2W_OUTPUT_DIR}" )

set( SDL2W_TESTS_RUN_DIR ${SDL2W_ROOT}/runDir )
message( "Setting SDL2W_TESTS_RUN_DIR to: ${SDL2W_TESTS_RUN_DIR}" )

# Add sub directories
add_subdirectory( deps/CUL )
add_subdirectory( deps/sdl2-repo )
add_subdirectory( libsdl2wrapper )
add_subdirectory( libsdl2wrapperTestApp )

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/deps/sdl2-repo )