#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

project(sdl2wrapper_main)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Add sub directories
add_subdirectory( deps/CUL )
add_subdirectory( deps/sdl2-repo )
add_subdirectory( libsdl2wrapper )
add_subdirectory( libsdl2wrapperTestApp )