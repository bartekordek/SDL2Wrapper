#pragma once

#include "SDL2Wrapper/IWindowFactory.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"

NAMESPACE_BEGIN( SDL2W )

class WindowCreatorConcrete final:
    public IWindowFactory
{
public:
    explicit WindowCreatorConcrete();

    IWindow* createWindow( const WindowData& winData ) override;

    ~WindowCreatorConcrete();

protected:
private:
    WindowCreatorConcrete( const WindowCreatorConcrete& rhv ) = delete;
    WindowCreatorConcrete& operator=( WindowCreatorConcrete& rhv ) = delete;

};

NAMESPACE_END( SDL2W )