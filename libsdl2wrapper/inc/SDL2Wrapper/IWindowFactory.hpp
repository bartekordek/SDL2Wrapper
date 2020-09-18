#pragma once

#include "SDL2Wrapper/IWindow.hpp"

#include "CUL/String.hpp"
#include "CUL/GenericUtils/IConfigFile.hpp"

NAMESPACE_BEGIN( SDL2W )

class SDL2WAPI IWindowFactory
{
public:
    IWindowFactory();
    IWindowFactory( const IWindowFactory& rhv ) = delete;
    virtual ~IWindowFactory();

    IWindowFactory& operator=( const IWindowFactory& rhv ) = delete;

    virtual IWindow* createWindow( const WindowData& winData, ISDL2Wrapper* wrapper ) = 0;

protected:
private:
};

NAMESPACE_END( SDL2W )