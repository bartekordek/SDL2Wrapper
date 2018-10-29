#pragma once

#include "SDL2Wrapper/Input/IMouseData.hpp"
#include "CUL/STD_map.hpp"

NAMESPACE_BEGIN( SDL2W )

class MouseDataSDL:
    public IMouseData
{
public:
    MouseDataSDL( void );
    virtual ~MouseDataSDL( void );

    cunt getMouseButtonCount()const override;
    const bool isButtonDown( cunt buttonIndex )const override;
    cint getX()const override;
    cint getY()const override;

    void setPos( cint x, cint y );
    void setState( const short buttonIndex, const bool isUp );

protected:
private:
    std::map<short, bool> m_buttonStates;
    int m_x = 0;
    int m_y = 0;

};

NAMESPACE_END( SDL2W )