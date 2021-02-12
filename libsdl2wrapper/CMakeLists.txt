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
    # lots of warnings and all warnings as errors
    #add_compile_options(-Wall -Wextra -pedantic -Werror)
    add_compile_options( -Wall -Wextra -pedantic -Werror )
    add_definitions( -Wfatal-errors )
endif()

message( "[libsdlwrapper] Setting CMAKE_ARCHIVE_OUTPUT_DIRECTORY to: ${SDL2W_OUTPUT_DIR}" )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SDL2W_OUTPUT_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SDL2W_OUTPUT_DIR} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SDL2W_OUTPUT_DIR} )

find_package( glm REQUIRED )

add_library( ${EXEC} SHARED
src/Sprite.cpp
src/TextureSDL.cpp
src/RegularSDL2Window.cpp
src/ISprite.cpp
src/SDL2Wrapper.cpp
src/IWindow.cpp
src/SimpleUtils.cpp
src/ISDL2Wrapper.cpp
src/IRender.cpp
src/SDL2WrapperImpl.cpp
src/Input/MouseData.cpp
src/Input/IKey.cpp
src/Input/KeySDL.cpp
src/WindowFactoryConcrete.cpp
src/IWindowFactory.cpp
)

#set_target_properties(cul PROPERTIES PUBLIC_HEADER
set( HEADERS_PUBLIC
src/SimpleUtils.hpp
src/IMPORT_SDL_opengl.hpp
src/Sprite.hpp
src/SDL2WrapperImpl.hpp
src/WindowFactoryConcrete.hpp
src/IMPORT_SDL_events.hpp
src/Input/KeySDL.hpp
src/TextureSDL.hpp
src/RegularSDL2Window.hpp
inc/SDL2Wrapper/ISprite.hpp
inc/SDL2Wrapper/IWindow.hpp
inc/SDL2Wrapper/IRender.hpp
inc/SDL2Wrapper/IMPORT_SDL_renderer.hpp
inc/SDL2Wrapper/IMPORT_SDL_video.hpp
inc/SDL2Wrapper/IWindowEventListener.hpp
inc/SDL2Wrapper/IWindowFactory.hpp
inc/SDL2Wrapper/IEventLoop.hpp
inc/SDL2Wrapper/Input/IMouseObservable.hpp
inc/SDL2Wrapper/Input/IKey.hpp
inc/SDL2Wrapper/Input/IKeyboardObserver.hpp
inc/SDL2Wrapper/Input/IMouseObserver.hpp
inc/SDL2Wrapper/Input/IKeyboardObservable.hpp
inc/SDL2Wrapper/Input/MouseData.hpp
inc/SDL2Wrapper/ISDL2Wrapper.hpp
inc/SDL2Wrapper/Import.hpp
inc/SDL2Wrapper/Gui/IGui.hpp
inc/SDL2Wrapper/Gui/IWindowEventObservable.hpp
inc/SDL2Wrapper/IMPORT_SDL.hpp
inc/SDL2Wrapper/ISDLEventObserver.hpp
)

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

if (MSVC)
    # Copy SDL2
    CmakeToWindow( "SDL2W_OUTPUT_DIR" SDL2W_OUTPUT_DIR_WINDOWS )
    CmakeToWindow( "${SDL2W_DEPS}" SDL2W_DEPS_WINDOWS )

    CmakeToWindow( "${SDL2W_TESTS_RUN_DIR}" SDL2W_RUN_DIR_WINDOWS )

    set( CopyCommand ${SDL2W_DEPS}\\helpers\\CopyLibraryBinaryAndSymbolsRecursive.bat )
    add_custom_command(TARGET ${EXEC} POST_BUILD
        COMMAND ${CopyCommand} ${SDL2W_OUTPUT_DIR_WINDOWS} ${SDL2W_RUN_DIR_WINDOWS}
        COMMAND ${CopyCommand} ${SDL2W_DEPS_WINDOWS} ${SDL2W_RUN_DIR_WINDOWS}
    )
endif()