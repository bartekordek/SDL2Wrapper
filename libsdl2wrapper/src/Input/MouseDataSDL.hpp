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
    MouseDataSDL();
    virtual ~MouseDataSDL();

    Cunt getMouseButtonCount()const override;
    const bool isButtonDown( const MouseButtonIndex buttonIndex )const override;
    Cint getX()const override;
    Cint getY()const override;

    Cint getWheelX()const override;
    Cint getWheelY()const override;
    const WheelDirection getWheelDirection()const override;

    void setPos( Cint x, Cint y );
    void setState( const MouseButtonIndex buttonIndex, const bool isUp );
    void setWheel( Cint x, Cint y, const WheelDirection direction );

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