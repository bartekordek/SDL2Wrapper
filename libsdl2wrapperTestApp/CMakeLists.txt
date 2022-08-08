#cmake -DCMAKE_BUILD_TYPE=Debug

get_filename_component( basename ${CMAKE_CURRENT_SOURCE_DIR} NAME )
project( ${basename} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(EXEC ${PROJECT_NAME})

set(EXEC_DYNAMIC "${EXEC}_dynamic")
set(EXEC_STATIC "${EXEC}_static")

message( "DEBUG: ${EXEC}" )
message( "00 DEBUG: ${EXEC_DYNAMIC}" )
message( "01 DEBUG: ${EXEC_STATIC}" )

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
    add_compile_options( /MP )
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
    add_definitions(-Wfatal-errors)
endif()

include_directories( $ENV{cul_INCLUDE_DIR} )
find_package( cul REQUIRED )

file( GLOB SOURCES *.cpp )

add_executable(${EXEC_DYNAMIC} ${SOURCES})
add_executable(${EXEC_STATIC} ${SOURCES})

if (MSVC)
    set_target_properties(
        ${EXEC_DYNAMIC}
        PROPERTIES
            OUTPUT_NAME ${EXEC_DYNAMIC}
            SUFFIX ".exe"
    )

    set_target_properties(
        ${EXEC_STATIC}
        PROPERTIES
            OUTPUT_NAME ${EXEC_STATIC}
            SUFFIX ".exe"
    )
else()
    set_target_properties(
        ${EXEC_STATIC}
        PROPERTIES
            OUTPUT_NAME ${EXEC_STATIC}
            SUFFIX ".bin"
    )
endif()

IF(NOT APPLE AND NOT MSVC)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
ENDIF()

set( DEPENDENCIES_STATIC
    PRIVATE sdl2wrapper_static
)

set( DEPENDENCIES_DYNAMIC
    PRIVATE sdl2wrapper
)


if( MSVC )
    target_link_libraries( ${EXEC_DYNAMIC} ${DEPENDENCIES_DYNAMIC} )
    target_link_libraries( ${EXEC_STATIC} ${DEPENDENCIES_STATIC} )
else()
    target_link_libraries( ${EXEC_DYNAMIC} ${DEPENDENCIES_DYNAMIC} stdc++fs  )
    target_link_libraries( ${EXEC_STATIC} ${DEPENDENCIES_DYNAMIC} stdc++fs  )
endif()

add_dependencies( ${EXEC_DYNAMIC} libculTests )
add_dependencies( ${EXEC_STATIC} libculTests )

target_include_directories(${EXEC_DYNAMIC} PRIVATE inc)
target_include_directories(${EXEC_DYNAMIC} PRIVATE src)

target_include_directories(${EXEC_STATIC} PRIVATE inc)
target_include_directories(${EXEC_STATIC} PRIVATE src)

if( MSVC )
    set_property(TARGET ${EXEC_DYNAMIC} PROPERTY "VS_DEBUGGER_WORKING_DIRECTORY" "${SDL2W_TESTS_RUN_DIR}")
    set_property(TARGET ${EXEC_STATIC} PROPERTY "VS_DEBUGGER_WORKING_DIRECTORY" "${SDL2W_TESTS_RUN_DIR}")
endif()
