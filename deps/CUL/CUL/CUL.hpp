#pragma once
#if defined CULLib_EXPORT && defined CUL_DYNAMIC
#define CULLib_API __declspec(dllexport)
#define CULLib_API_TEMPLATE
#elif defined CULLib_EXPORT
#define CULLib_API
#define CULLib_API_TEMPLATE
#else
#define CULLib_API __declspec(dllimport)
#define CULLib_API_TEMPLATE extern
#endif
/*TODO: Find a way to tell library name.
#if defined _MSC_VER && defined CUL_DYNAMIC
#pragma comment(lib, "CULdynamic.lib")
#elif _MSC_VER
#pragma comment(lib, "CULstatic.lib")
#else
#pragma comment(lib, "libcul.a")
#endif
*/