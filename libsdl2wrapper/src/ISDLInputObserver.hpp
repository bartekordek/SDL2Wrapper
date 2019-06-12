#pragma once

#include "CUL/UselessMacros.hpp"
#include "IMPORT_SDL_events.hpp"

NAMESPACE_BEGIN( SDL2W )

class ISDLInputObserver
{
public:
    ISDLInputObserver() = default;
    virtual ~ISDLInputObserver() = default;

    virtual void handleEvent( const SDL_Event& event ) = 0;

protected:
private:
    ISDLInputObserver( const ISDLInputObserver& arg ) = delete;
    ISDLInputObserver& operator=( const ISDLInputObserver& rhv ) = delete;

};

NAMESPACE_END( SDL2W )