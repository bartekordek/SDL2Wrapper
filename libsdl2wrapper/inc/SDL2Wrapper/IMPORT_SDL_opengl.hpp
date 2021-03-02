#pragma once
#if _MSC_VER
#pragma warning( push, 0 )
#pragma warning( disable: 4668 )
#endif
#define SDL_MAIN_HANDLED
#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>
#include <SDL_video.h>
#define SDL_MAIN_HANDLED
#undef ABSOLUTE
#ifdef _MSC_VER
#pragma warning( pop )
#endif