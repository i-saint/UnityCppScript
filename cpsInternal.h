#ifndef cpsInternal_h
#define cpsInternal_h

#define cpsBuildDLL
#define cpsAPI __declspec(dllexport)

#if defined(_WIN32) && !defined(cpsWithoutDbgHelp)
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")
#endif

#include "monoAPI.h"

#endif // cpsInternal_h
