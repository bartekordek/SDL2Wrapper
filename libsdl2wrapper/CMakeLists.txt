#cmake -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.0.0)

project(sdlwrapper LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(EXEC sdlwrapper)

#include_directories( SYSTEM "../deps/spdlog/include" )


if( MSVC )
    # warning level 4 and all warnings as errors
    add_compile_options( /W4 /WX )
else()
    # lots of warnings and all warnings as errors
    #add_compile_options(-Wall -Wextra -pedantic -Werror)
    add_compile_options( -Wall -Wextra -pedantic -Werror )
    add_definitions( -Wfatal-errors )
endif()

add_library( sdlwrapper SHARED
    src/Input/IKey.cpp
    src/Input/KeySDL.cpp
    src/Input/MouseDataSDL.cpp
    src/IRender.cpp
    src/ISDL2Wrapper.cpp
    src/ISprite.cpp
    src/IWindow.cpp
    src/IWindowFactory.cpp
    src/RegularSDL2Window.cpp
    src/SDL2Wrapper.cpp
    src/SDL2WrapperImpl.cpp
    src/SimpleUtils.cpp
    src/Sprite.cpp
    src/TextureSDL.cpp
    src/WindowFactoryConcrete.cpp
)

set_target_properties(sdlwrapper PROPERTIES PUBLIC_HEADER
    inc/SDL2Wrapper/Gui/IGui.hpp
    inc/SDL2Wrapper/Gui/IWindowEventObservable.hpp
    inc/SDL2Wrapper/IEventLoop.hpp
    inc/SDL2Wrapper/Import.hpp
    inc/SDL2Wrapper/IMPORT_SDL.hpp
    inc/SDL2Wrapper/IMPORT_SDL_renderer.hpp
    inc/SDL2Wrapper/IMPORT_SDL_video.hpp
    inc/SDL2Wrapper/Input/IKey.hpp
    inc/SDL2Wrapper/Input/IKeyboardObservable.hpp
    inc/SDL2Wrapper/Input/IKeyboardObserver.hpp
    inc/SDL2Wrapper/Input/IMouseData.hpp
    inc/SDL2Wrapper/Input/IMouseObservable.hpp
    inc/SDL2Wrapper/Input/IMouseObserver.hpp
    inc/SDL2Wrapper/IRender.hpp
    inc/SDL2Wrapper/ISDL2Wrapper.hpp
    inc/SDL2Wrapper/ISprite.hpp
    inc/SDL2Wrapper/IWindow.hpp
    inc/SDL2Wrapper/IWindowEventListener.hpp
    inc/SDL2Wrapper/IWindowFactory.hpp
)

link_directories(${CMAKE_SOURCE_DIR}/lib)

find_package(SDL2 REQUIRED)
if( SDL2_FOUND )
    include_directories( sdlwrapper ${SDL2_INCLUDE_DIRS} )
    message( "SDL2_LIBRARIES: ${SDL2_LIBRARIES}" )
    link_directories( "/usr/lib" )
    target_link_libraries( ${EXEC} ${SDL2_LIBRARIES} stdc++fs )
endif()

#find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
#find_library(SDL2_LIBRARY NAME SDL2)
#add_executable(sdlwrapper main.cpp)
#target_include_directories(sdlwrapper ${SDL2_INCLUDE_DIR})
#target_link_libraries(${EXEC} ${SDL2_LIBRARY} stdc++fs )

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../deps/CUL ${CMAKE_CURRENT_BINARY_DIR}/../deps/CUL)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../deps/CUL/libcul/inc)

target_include_directories(sdlwrapper PUBLIC inc)
target_include_directories(sdlwrapper PRIVATE src)