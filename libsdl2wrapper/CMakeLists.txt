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
    set_target_properties(SDL2-static PROPERTIES
        COMPILE_FLAGS "/MP" # Adjust as needed
    )
else()
    add_compile_options( -Wall -Wextra -pedantic -Werror -fPIC )
    add_definitions( -Wfatal-errors )
endif()

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SDL2W_OUTPUT_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SDL2W_OUTPUT_DIR} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SDL2W_OUTPUT_DIR} )

#include_directories( ${SDL2W_ROOT}/deps/CUL/libcul/inc )

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
    list(APPEND LIBS libvcruntimed )
    target_link_libraries( ${EXEC} ${LIBS} )
else()
    target_link_libraries( ${EXEC} ${LIBS} stdc++fs  )
endif()

target_include_directories(${EXEC} PUBLIC inc)
target_include_directories(${EXEC} PRIVATE src)


if (MSVC)
    set_target_properties(${EXEC} PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")

    CmakeToWindow( ${SDL2W_BINARY_DIRECTORY} SDL2W_BINARY_DIRECTORY_WINDOWS )
    CmakeToWindow( ${cul_LIBRARY} cul_LIBRARY_WINDOWS )
    CmakeToWindow( ${cul_BINARY} cul_BINARY_WINDOWS )
    CmakeToWindow( ${cul_SYMBOLS} cul_SYMBOLS_WINDOWS )
    CMakeToWindow( ${sdl2_binary_dir} sdl2_binary_dir_WINDOWS )

    message( "sdl2_binary_dir: ${sdl2_binary_dir}" )

    set( CopyCommand xcopy /s /f /d /y )
    add_custom_command(TARGET ${EXEC} POST_BUILD
        COMMAND ${CopyCommand} ${cul_LIBRARY_WINDOWS} ${SDL2W_BINARY_DIRECTORY_WINDOWS}
        COMMAND ${CopyCommand} ${cul_BINARY_WINDOWS} ${SDL2W_BINARY_DIRECTORY_WINDOWS}
        COMMAND ${CopyCommand} ${cul_SYMBOLS_WINDOWS} ${SDL2W_BINARY_DIRECTORY_WINDOWS}

        COMMAND ${CopyCommand} ${sdl2_binary_dir_WINDOWS}\\*.dll ${SDL2W_BINARY_DIRECTORY_WINDOWS}
        COMMAND ${CopyCommand} ${sdl2_binary_dir_WINDOWS}\\*.pdb ${SDL2W_BINARY_DIRECTORY_WINDOWS}
    )
endif()
