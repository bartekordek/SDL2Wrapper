#pragma once

#include "CUL/GenericUtils/DisableErros.hpp"

#define _HAS_STD_BYTE 0
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <dxerr.h>

#ifdef _MSC_VER
#pragma warning( pop )
#endif