#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

project(sdl2wrapper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(EXEC ${PROJECT_NAME})

if( MSVC )
    add_compile_options( /Wall /WX )
    add_compile_options( /MP )
    add_compile_options( "/wd4266" )
    add_compile_options( "/wd4514" )
    add_compile_options( "/wd4820" )
    set_target_properties(SDL2 PROPERTIES
        COMPILE_FLAGS "/MP" # Adjust as needed
    )
else()
    add_compile_options( -Wall -Wextra -pedantic -Werror -fPIC )
    add_definitions( -Wfatal-errors )
endif()

find_package( glm REQUIRED )
find_package( cul REQUIRED )
find_package( sdl2 REQUIRED )

file( GLOB_RECURSE SOURCES inc/*.hpp src/*.hpp src/*.cpp )
source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} )
add_library( ${EXEC} SHARED ${SOURCES} )

set( LIBS
AdditionalDeps
cul
SDL2
SDL2main
)

if( MSVC )
    target_link_libraries( ${EXEC} ${LIBS} )
else()
    target_link_libraries( ${EXEC} ${LIBS} stdc++fs  )
endif()

target_include_directories(${EXEC} PUBLIC inc)
target_include_directories(${EXEC} PRIVATE src)

if (MSVC)
    set_target_properties(${EXEC} PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")
endif()