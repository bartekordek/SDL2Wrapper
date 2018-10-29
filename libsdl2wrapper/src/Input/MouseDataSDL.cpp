#include "Input/MouseDataSDL.hpp"
#include "CUL/STD_iostream.hpp"

using MouseDataSDL = SDL2W::MouseDataSDL;
using MouseButtonIndex = SDL2W::MouseButtonIndex;
using WheelDirection = SDL2W::WheelDirection;

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4100 )
#endif

MouseDataSDL::MouseDataSDL( void )
{

}

MouseDataSDL::~MouseDataSDL( void )
{
}

cunt MouseDataSDL::getMouseButtonCount() const
{
    return static_cast<unsigned>( this->m_buttonStates.size() );
}

const bool MouseDataSDL::isButtonDown( const MouseButtonIndex buttonIndex ) const
{
    if( this->m_buttonStates.size() < buttonIndex )
    {
        return this->m_buttonStates.at( buttonIndex );
    }
    return false;
}

cint MouseDataSDL::getX() const
{
    return this->m_x;
}

cint MouseDataSDL::getY() const
{
    return this->m_y;
}

cint MouseDataSDL::getWheelX() const
{
    return this->m_wheelX;
}

cint MouseDataSDL::getWheelY() const
{
    return this->m_wheelY;
}

const WheelDirection MouseDataSDL::getWheelDirection() const
{
    return this->m_wheelDirection;
}

void MouseDataSDL::setPos( cint x, cint y )
{
    std::cout << "MOUSE STATE: X = " << x << ", Y: " << y << "\n";
    this->m_x = x;
    this->m_y = y;
}

void MouseDataSDL::setState( const MouseButtonIndex buttonIndex, const bool isUp )
{
    std::cout << "MOUSE STATE: INDEX = " << buttonIndex << ", IS UP: " << isUp << "\n";
    this->m_buttonStates[ buttonIndex ] = isUp;
}
void MouseDataSDL::setWheel( cint x, cint y, const WheelDirection direction )
{
    std::cout << "MOUSE WHEEL STATE: X = " << x << ", Y: " << y << "\n";
    this->m_wheelX = x;
    this->m_wheelY = y;
    this->m_wheelDirection = direction;
}
#ifdef _MSC_VER
#pragma warning( pop )
#endif