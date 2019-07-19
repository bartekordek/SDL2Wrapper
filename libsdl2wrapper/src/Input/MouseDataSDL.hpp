#pragma once

#include "SDL2Wrapper/Input/IMouseData.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"

NAMESPACE_BEGIN( SDL2W )
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif
class MouseDataSDL:
    public IMouseData
{
public:
    MouseDataSDL( void );
    virtual ~MouseDataSDL( void );

    cunt getMouseButtonCount()const override;
    const bool isButtonDown( const MouseButtonIndex buttonIndex )const override;
    cint getX()const override;
    cint getY()const override;

    cint getWheelX()const override;
    cint getWheelY()const override;
    const WheelDirection getWheelDirection()const override;

    void setPos( cint x, cint y );
    void setState( const MouseButtonIndex buttonIndex, const bool isUp );
    void setWheel( cint x, cint y, const WheelDirection direction );

protected:
private:
    std::map<MouseButtonIndex, bool> m_buttonStates;
    int m_x = 0;
    int m_y = 0;
    int m_wheelX = 0;
    int m_wheelY = 0;
    WheelDirection m_wheelDirection = WheelDirection::NONE;

};
#ifdef _MSC_VER
#pragma warning( pop )
#endif
NAMESPACE_END( SDL2W )