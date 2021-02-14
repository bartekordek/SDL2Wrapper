#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

project(sdl2wrapperTestApp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(EXEC ${PROJECT_NAME})

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
    add_compile_options( /MP )
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
    add_definitions(-Wfatal-errors)
endif()

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SDL2W_OUTPUT_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SDL2W_OUTPUT_DIR} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SDL2W_OUTPUT_DIR} )

file( GLOB SOURCES *.cpp )

add_executable(${EXEC} ${SOURCES})

if (MSVC)
    set_target_properties(
        ${EXEC}
        PROPERTIES
            OUTPUT_NAME ${EXEC}
            SUFFIX ".exe"
    )
else()
    set_target_properties(
        ${EXEC}
        PROPERTIES
            OUTPUT_NAME ${EXEC}
            SUFFIX ".bin"
    )
endif()

IF(NOT APPLE AND NOT MSVC)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
ENDIF()

set( DEPENDENCIES
cul
sdl2wrapper
AdditionalDeps
)

if( MSVC )
    target_link_libraries( ${EXEC} ${DEPENDENCIES} )
else()
    target_link_libraries( ${EXEC} ${DEPENDENCIES} stdc++fs  )
endif()

target_include_directories(${EXEC} PRIVATE inc)
target_include_directories(${EXEC} PRIVATE src)

if( MSVC )
    set_property(TARGET ${EXEC} PROPERTY "VS_DEBUGGER_WORKING_DIRECTORY" "${SDL2W_TESTS_RUN_DIR}")
endif()

if (MSVC)
    CmakeToWindow( ${SDL2W_TESTS_RUN_DIR} SDL2W_TESTS_RUN_DIR_WINDOWS )
    CmakeToWindow( ${SDL2W_OUTPUT_DIR} SDL2W_OUTPUT_DIR_WINDOWS )
    CmakeToWindow( ${SDL2W_DEPS} SDL2W_DEPS_WINDOWS )


    set( CleanCommand ${SDL2W_DEPS}\\helpers\\RemoveBinAndSymbols.bat )
    add_custom_command(TARGET ${EXEC} PRE_BUILD
        COMMAND ${CleanCommand} ${SDL2W_TESTS_RUN_DIR_WINDOWS}
    )

    set( CopyCommand ${SDL2W_DEPS}\\helpers\\CopyLibraryBinaryAndSymbolsRecursive.bat )
    add_custom_command(TARGET ${EXEC} POST_BUILD
        COMMAND ${CopyCommand} ${SDL2W_OUTPUT_DIR_WINDOWS} ${SDL2W_TESTS_RUN_DIR_WINDOWS}
        COMMAND ${CopyCommand} ${SDL2W_DEPS_WINDOWS} ${SDL2W_TESTS_RUN_DIR_WINDOWS}
    )
endif()