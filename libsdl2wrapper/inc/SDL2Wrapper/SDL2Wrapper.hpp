#pragma once

#if defined SDL2W_EXPORT && defined SDL2W_LINUX
#define SDL2WrapperAPI
#define SDL2Wrapper_TEMPLATE
#elif SDL2W_EXPORT
#define SDL2WrapperAPI __declspec(dllexport)
#define SDL2Wrapper_TEMPLATE
#else
#define SDL2WrapperAPI __declspec(dllimport)
#define SDL2Wrapper_TEMPLATE extern
#endif
/*TODO: Find a way to tell library name.

#ifdef _MSC_VER && SDL2Wrapper_DYNAMIC
#pragma comment(lib, "SDL2WrapperDynamic.lib")
#elif  MSC_VER
#pragma comment(lib, "SDL2WrapperStatic.lib")
#else
#pragma comment(lib, "libsdl2wrapper.a")
#endif
*/