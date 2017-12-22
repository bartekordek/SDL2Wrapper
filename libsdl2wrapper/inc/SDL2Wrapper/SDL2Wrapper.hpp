#pragma once
/*
#ifdef _MSC_VER && SDL2Wrapper_DYNAMIC
#pragma comment(lib, "SDL2WrapperDynamic.lib")
#elif  MSC_VER
#pragma comment(lib, "SDL2WrapperStatic.lib")
#else
#pragma comment(lib, "libsdl2wrapper.a")
#endif
*/

#ifdef SDL2Wrapper_DYNAMIC
#define SDL2WrapperAPI __declspec(dllexport)
#define SDL2Wrapper_TEMPLATE
#else
#define SDL2WrapperAPI __declspec(dllimport)
#define SDL2Wrapper_TEMPLATE extern
#endif
