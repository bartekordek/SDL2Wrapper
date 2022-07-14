#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME_DYNAMIC sdl2wrapper)
set(PROJECT_NAME_DYNAMIC_STATIC sdl2wrapper_static)
set(EXEC ${PROJECT_NAME_DYNAMIC})

project(sdl2wrapper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)


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

add_library( ${PROJECT_NAME_DYNAMIC} SHARED ${SOURCES} )
add_library( ${PROJECT_NAME_STATIC} STATIC ${SOURCES} )

set( DEPENDENCIES
cul-static
SDL2main
SDL2-static
)

set_property( TARGET ${PROJECT_NAME_DYNAMIC} PROPERTY "LINK_LIBRARY_DEPENDENCIES" true )
set_property( TARGET ${PROJECT_NAME_STATIC} PROPERTY "LINK_LIBRARY_DEPENDENCIES" true )

if( MSVC )
    list(APPEND LIBS msvcmrtd )


    target_link_libraries( ${PROJECT_NAME_DYNAMIC} ${DEPENDENCIES} )


    target_link_libraries( ${PROJECT_NAME_STATIC} ${DEPENDENCIES} )
else()
    target_link_libraries( ${PROJECT_NAME_DYNAMIC} ${DEPENDENCIES} stdc++fs )
    target_link_libraries( ${PROJECT_NAME_STATIC} ${DEPENDENCIES} stdc++fs )
endif()

target_include_directories(${EXEC} PUBLIC inc)
target_include_directories(${EXEC} PRIVATE src)

if (MSVC)
    set_target_properties(${EXEC} PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")
endif()