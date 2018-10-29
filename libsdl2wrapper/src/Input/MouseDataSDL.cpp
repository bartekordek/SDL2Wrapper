#include "Input/MouseDataSDL.hpp"

using MouseDataSDL = SDL2W::MouseDataSDL;
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
    return cunt();
}

const bool MouseDataSDL::isButtonDown( cunt buttonIndex ) const
{
    return false;
}

cint MouseDataSDL::getX() const
{
    return cint();
}

cint MouseDataSDL::getY() const
{
    return cint();
}

void MouseDataSDL::setPos( cint x, cint y )
{
}

void MouseDataSDL::setState( const short buttonIndex, const bool isUp )
{
}
#ifdef _MSC_VER
#pragma warning( pop )
#endif