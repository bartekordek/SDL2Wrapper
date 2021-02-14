#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

project(sdl2wrapper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(EXEC ${PROJECT_NAME})

if( MSVC )
    # warning level 4 and all warnings as errors
    add_compile_options( /W4 /WX )
    add_compile_options( /MP )
    set_target_properties(SDL2 PROPERTIES
        COMPILE_FLAGS "/MP" # Adjust as needed
    )
else()
    add_compile_options( -Wall -Wextra -pedantic -Werror )
    add_definitions( -Wfatal-errors )
endif()

message( "[libsdlwrapper] Setting CMAKE_ARCHIVE_OUTPUT_DIRECTORY to: ${SDL2W_OUTPUT_DIR}" )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SDL2W_OUTPUT_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SDL2W_OUTPUT_DIR} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SDL2W_OUTPUT_DIR} )

find_package( glm REQUIRED )

file( GLOB_RECURSE SOURCES inc/*.hpp src/*.hpp src/*.cpp )
source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} )
add_library( ${EXEC} SHARED ${SOURCES} )

set( LIBS
SDL2
cul
AdditionalDeps
)

if( MSVC )
    target_link_libraries( ${EXEC} ${LIBS} )
else()
    target_link_libraries( ${EXEC} ${LIBS} stdc++fs  )
endif()

target_include_directories(${EXEC} PUBLIC inc)
target_include_directories(${EXEC} PRIVATE src)