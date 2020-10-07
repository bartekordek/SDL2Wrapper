#pragma once

#include "CUL/Log/ILogContainer.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"

NAMESPACE_BEGIN( SDL2W )

void Assert( const bool result, CUL::CsStr& msg );

NAMESPACE_END( SDL2W )